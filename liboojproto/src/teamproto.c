/* teamproto.c
 * Source code file for team client protocol implementation. */

#include "teamproto.h"

/* callback registration check function, return 1(true) if all functions has been registered */
static int teamproto_cbcheck( void );

/* callback functions */
void (*cb_run_reply)( unsigned int run_id, wchar_t *result_string )   = NULL;
void (*cb_clar_reply)( unsigned int clar_id, wchar_t *result_string ) = NULL;
void (*cb_pu_request)( wchar_t **path_description )                   = NULL;
void (*cb_pu_request_dlfin)( wchar_t *path_description )              = NULL;

/* callback functions extern-ed from protointernal.c */
extern void (*cb_login_confirm)( int confirm_code, unsigned int account_id );
extern void (*cb_logout_confirm)( int confirm_code );
extern void (*cb_timer_set)( unsigned int hours, unsigned int minutes, unsigned int seconds );
extern void (*cb_contest_start)( void );
extern void (*cb_contest_stop)( void );
extern void (*cb_sb_update)( unsigned int updated_account_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time );

/* thread function */
void *teamproto_reqhand_thread( void *args );

/* external sync variable (from proto_commonfunction.c) */
extern pthread_mutex_t proto_sockfd_pass_mutex;
extern pthread_cond_t proto_sockfd_pass_cv;

int teamproto_listen( char *localaddr )
{
	/* don't start listening if callback functions are not fully registered. */
	if( !teamproto_cbcheck() )
	{
#if PROTO_DBG > 0
		printf("[teamproto_listen()] All callbacks should be registered before start.\n");
#endif
		return -1;
	}

	if( proto_listen( localaddr, LISTEN_PORT_TEAM, teamproto_reqhand_thread ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[teamproto_listen()] proto_listen() call failed.\n");
#endif
		return -1;
	}

	return 0;
}

int teamproto_stop_listen( void )
{
	if( proto_stop_listen() < 0 )
	{
#if PROTO_DBG > 0
		printf("[teamproto_stop_listen()] proto_stop_listen() call failed.\n");
#endif
		return -1;
	}

	return 0;
}

int teamproto_active( void )
{
	return proto_active();
}

void *teamproto_reqhand_thread( void *args )
{
	int sockfd;
	char recvbuf[BUFLEN];
//	char *src_ipaddr;
	short RQSR, RQID;
	char *msgptr = NULL;

	/* get sockfd from listen thread */
	pthread_mutex_lock( &proto_sockfd_pass_mutex );
	sockfd = *((int *)args);
	pthread_cond_signal( &proto_sockfd_pass_cv );
	pthread_mutex_unlock( &proto_sockfd_pass_mutex );

	/* receive and interpret message */
	recv( sockfd, recvbuf, BUFLEN, 0 );
	msgptr = proto_srid_split( recvbuf, &RQSR, &RQID );

	/* request handling -- if not common, go special */
	if( proto_commonreq( RQSR, RQID, msgptr ) == 0 && RQSR == OPSR_SERVER )
	{
		if( RQID == OPID_RUN_REPLY )
		{
			char *run_id_str = proto_str_split( msgptr, &msgptr );
			char *result_string_mb = proto_str_split( msgptr, NULL );

			unsigned int run_id = atoi( run_id_str );
			wchar_t *result_string = proto_str_postrecv( result_string_mb );

			(*cb_run_reply)( run_id, result_string );

			free( run_id_str );
			free( result_string_mb );
			free( result_string );
		}
		else if( RQID == OPID_CLAR_REPLY )
		{
			char *clar_id_str = proto_str_split( msgptr, &msgptr );
			char *result_string_mb = proto_str_split( msgptr, &msgptr );

			unsigned int clar_id = atoi( clar_id_str );
			wchar_t *result_string = proto_str_postrecv( result_string_mb );

			(*cb_clar_reply)( clar_id, result_string );

			free( clar_id_str );
			free( result_string_mb );
			free( result_string );
		}
		else if( RQID == OPID_SB_UPDATE )
		{
			proto_sb_update( msgptr );
		}
		else if( RQID == OPID_PUPLOAD )
		{
			wchar_t *path_description;

			(*cb_pu_request)( &path_description );

			/* download file */
			filerecv( sockfd, path_description );

			(*cb_pu_request_dlfin)( path_description );

			free( path_description );
		}
		else
		{
#if PROTO_DBG > 0
			printf("[teamproto_reqhand_thread()] Invalid SRID bytes.\n");
#endif
		}
	}
	else
	{
#if PROTO_DBG > 0
		printf("[teamproto_reqhand_thread()] Invalid SRID bytes.\n");
#endif
	}

	shutdown_wr_sp( sockfd );
	pthread_exit( NULL );
}

int teamproto_login( char *destip, wchar_t *account, char *password )
{
	return proto_login( destip, OPSR_TEAM, account, password );
}

int teamproto_logout( char *destip, unsigned int account_id )
{
	return proto_logout( destip, OPSR_TEAM, account_id );
}

int teamproto_submission( char *destip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *account_id_str = uint2str( account_id );
	char *problem_id_str = uint2str( problem_id );
	char *coding_language_mb = proto_str_presend( coding_language );

	msgptr = proto_srid_comb( sendbuf, OPSR_TEAM, OPID_SUBMISSION );
	msgptr = proto_str_comb( msgptr, account_id_str );
	msgptr = proto_str_comb( msgptr, problem_id_str );
	msgptr = proto_str_comb( msgptr, coding_language_mb );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[teamproto_submission()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	/* upload files */
	filesend( sockfd, path_code );

	shutdown_wr_sp( sockfd );
	free( account_id_str );
	free( problem_id_str );
	free( coding_language_mb );

	return 0;
}

int teamproto_clar( char *destip, unsigned int account_id, int private_byte, wchar_t *clarmsg )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *account_id_str = uint2str( account_id );
	char *private_byte_str = int2str( private_byte );
	char *clarmsg_mb = proto_str_presend( clarmsg );

	msgptr = proto_srid_comb( sendbuf, OPSR_TEAM, OPID_CLAR );
	msgptr = proto_str_comb( msgptr, account_id_str );
	msgptr = proto_str_comb( msgptr, private_byte_str );
	msgptr = proto_str_comb( msgptr, clarmsg_mb );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[teamproto_clar()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( account_id_str );
	free( private_byte_str );
	free( clarmsg_mb );

	return 0;
}

int teamproto_problem_download( char *destip, unsigned int account_id, unsigned int problem_id )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *account_id_str = uint2str( account_id );
	char *problem_id_str = uint2str( problem_id );

	msgptr = proto_srid_comb( sendbuf, OPSR_TEAM, OPID_PD_REQUEST );
	msgptr = proto_str_comb( msgptr, account_id_str );
	msgptr = proto_str_comb( msgptr, problem_id_str );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[teamproto_problem_download()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( account_id_str );
	free( problem_id_str );

	return 0;
}

void teamproto_cbreg_login_confirm( void (*cbfunc)( int, unsigned int ) ) { cb_login_confirm = cbfunc; }
void teamproto_cbreg_logout_confirm( void( *cbfunc )( int ) ) { cb_logout_confirm = cbfunc; }
void teamproto_cbreg_timer_set( void (*cbfunc)( unsigned int, unsigned int, unsigned int ) ) { cb_timer_set = cbfunc; }
void teamproto_cbreg_contest_start( void (*cbfunc)( void ) )  { cb_contest_start = cbfunc; }
void teamproto_cbreg_contest_stop( void (*cbfunc)( void ) )   { cb_contest_stop = cbfunc; }
void teamproto_cbreg_run_reply( void (*cbfunc)( unsigned int, wchar_t* ) )  { cb_run_reply = cbfunc; }
void teamproto_cbreg_clar_reply( void (*cbfunc)( unsigned int, wchar_t* ) ) { cb_clar_reply = cbfunc; }
void teamproto_cbreg_sb_update( void (*cbfunc)( unsigned int, wchar_t*, unsigned int, unsigned int ) ) { cb_sb_update = cbfunc; }
void teamproto_cbreg_pu_request( void (*cbfunc)( wchar_t** ) )     { cb_pu_request = cbfunc; }
void teamproto_cbreg_pu_request_dlfin( void (*cbfunc)( wchar_t*) ) { cb_pu_request_dlfin = cbfunc; }

static int teamproto_cbcheck( void )
{
	if( cb_login_confirm == NULL || cb_logout_confirm == NULL ||
		cb_timer_set == NULL || cb_contest_start == NULL || cb_contest_stop == NULL ||
		cb_run_reply == NULL || cb_clar_reply == NULL || cb_sb_update == NULL ||
		cb_pu_request == NULL || cb_pu_request_dlfin == NULL )
		return 0;
	else
		return 1;
}
