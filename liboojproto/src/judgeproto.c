/* judgeproto.c
 * Source code file for judge client protocol implementation. */

#include "judgeproto.h"

/* callback registration check function, return 1(true) if all functions has been registered */
static int judgeproto_cbcheck( void );

/* callback functions */
void (*cb_run_request)( unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code )         = NULL;
void (*cb_run_request_dlfin)( unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code )    = NULL;
void (*cb_take_result)( unsigned int run_id, int success );

/* callback functions extern-ed from protointernal.c */
extern void (*cb_login_confirm)( int confirm_code, unsigned int account_id );
extern void (*cb_logout_confirm)( int confirm_code );
extern void (*cb_password_change_confirm)( int confirm_code );
extern void (*cb_timer_set)( unsigned int hours, unsigned int minutes, unsigned int seconds );
extern void (*cb_contest_start)( void );
extern void (*cb_contest_stop)( void );
extern void (*cb_clar_request)( unsigned int clar_id, unsigned int account_id, wchar_t *account, int private_byte, wchar_t *clarmsg );
extern void (*cb_clar_reply)( unsigned int clar_id, wchar_t *clarmsg, wchar_t *result_string );
extern void (*cb_problem_update)( unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer );
extern void (*cb_problem_update_dlfin)( unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer );
extern void (*cb_problem_remove)( unsigned int problem_id );

/* callback registration functions */
void judgeproto_cbreg_login_confirm( void (*cbfunc)( int, unsigned int ) ) { cb_login_confirm = cbfunc; }
void judgeproto_cbreg_logout_confirm( void (*cbfunc)( int ) )              { cb_logout_confirm = cbfunc; }
void judgeproto_cbreg_password_change_confirm( void (*cbfunc)( int ) ) { cb_password_change_confirm = cbfunc; }
void judgeproto_cbreg_timer_set( void (*cbfunc)( unsigned int, unsigned int, unsigned int ) ) { cb_timer_set = cbfunc; }
void judgeproto_cbreg_contest_start( void (*cbfunc)( void ) ) { cb_contest_start = cbfunc; }
void judgeproto_cbreg_contest_stop( void (*cbfunc)( void ) )  { cb_contest_stop = cbfunc; }
void judgeproto_cbreg_run_request( void (*cbfunc)( unsigned int, unsigned int, wchar_t*, wchar_t** ) )      { cb_run_request = cbfunc; }
void judgeproto_cbreg_run_request_dlfin( void (*cbfunc)( unsigned int, unsigned int, wchar_t*, wchar_t* ) ) { cb_run_request_dlfin = cbfunc; }
void judgeproto_cbreg_problem_update( void (*cbfunc)( unsigned int, wchar_t*, unsigned int, wchar_t**, wchar_t**, wchar_t** ) ) { cb_problem_update = cbfunc; }
void judgeproto_cbreg_problem_update_dlfin( void (*cbfunc)( unsigned int, wchar_t*, unsigned int, wchar_t*, wchar_t*, wchar_t* ) ) { cb_problem_update_dlfin = cbfunc;}
void judgeproto_cbreg_problem_remove( void (*cbfunc)( unsigned int problem_id ) ) { cb_problem_remove = cbfunc; }
void judgeproto_cbreg_take_result( void (*cbfunc)( unsigned int, int ) ) { cb_take_result = cbfunc; }
void judgeproto_cbreg_clar_request( void (*cbfunc)( unsigned int, unsigned int, wchar_t*, int, wchar_t* ) ) { cb_clar_request = cbfunc; }
void judgeproto_cbreg_clar_reply( void (*cbfunc)( unsigned int, wchar_t*, wchar_t* ) ) { cb_clar_reply = cbfunc; }

/* thread function */
void *judgeproto_reqhand_thread( void *args );

/* external sync variable (from proto_commonfunction.c) */
extern pthread_mutex_t proto_sockfd_pass_mutex;
extern pthread_cond_t proto_sockfd_pass_cv;

/* external download management mutex from protointernal_listen.c */
extern pthread_mutex_t proto_dlmgr_mutex;

/* callback registration check function */
static int judgeproto_cbcheck( void )
{
	if( cb_login_confirm == NULL || cb_logout_confirm == NULL || cb_password_change_confirm == NULL ||
		cb_timer_set == NULL || cb_contest_start == NULL || cb_contest_stop == NULL || cb_run_request == NULL ||
		cb_run_request_dlfin == NULL || cb_problem_update == NULL || cb_problem_update_dlfin == NULL ||
		cb_problem_remove == NULL || cb_take_result == NULL || cb_clar_request == NULL || cb_clar_reply == NULL )
		return 0;
	else
		return 1;
}

int judgeproto_listen( const char *localaddr )
{
	/* don't start listening if callback functions are not fully registered. */
	if( !judgeproto_cbcheck() )
	{
#if PROTO_DBG > 0
		printf("[judgeproto_listen()] All callbacks should be registered before start.\n");
#endif
		return -1;
	}

	if( proto_listen( localaddr, LISTEN_PORT_JUDGE, LISTEN_PORT_VSFTP_JUDGE, judgeproto_reqhand_thread ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[judgeproto_listen()] proto_listen() call failed.\n");
#endif
		return -1;
	}

	return 0;
}

int judgeproto_stop_listen( void )
{
	if( proto_stop_listen() < 0 )
	{
#if PROTO_DBG > 0
		printf("[judgeproto_stop_listen()] proto_stop_listen() call failed.\n");
#endif
		return -1;
	}

	return 0;
}

int judgeproto_active( void )
{
	return proto_active();
}

void *judgeproto_reqhand_thread( void *args )
{
	int sockfd;
	char *recvbuf = NULL;
	char *src_ipaddr;
	short RQSR, RQID;
	char *msgptr = NULL;

	/* get sockfd from listen thread */
	pthread_mutex_lock( &proto_sockfd_pass_mutex );
	sockfd = *((int *)args);
	pthread_cond_signal( &proto_sockfd_pass_cv );
	pthread_mutex_unlock( &proto_sockfd_pass_mutex );

	src_ipaddr = tcp_getaddr( sockfd );
	
	/* receive and interpret message */
	recv_sp( sockfd, &recvbuf );
	msgptr = proto_srid_split( recvbuf, &RQSR, &RQID );

	/* request handling -- if not common, go special */
	if( proto_commonreq( RQSR, RQID, msgptr ) == 0 && RQSR == OPSR_SERVER )
	{
		if( RQID == OPID_RUN_REQUEST )
		{
			char *run_id_str = proto_str_split( msgptr, &msgptr );
			char *problem_id_str = proto_str_split( msgptr, &msgptr );
			char *coding_language_mb = proto_str_split( msgptr, &msgptr );
			wchar_t *path_code = NULL;

			unsigned int run_id = atoi( run_id_str );
			unsigned int problem_id = atoi( problem_id_str );
			wchar_t *coding_language = proto_str_postrecv( coding_language_mb );

			/* mutex lock protection -- prevent concurrent downloading causing race condition */
			pthread_mutex_lock( &proto_dlmgr_mutex );
			send_sp( sockfd, "FSREADY", BUFLEN );
			
			(*cb_run_request)( run_id, problem_id, coding_language, &path_code );

			/* download file */
			filerecv( path_code );

			(*cb_run_request_dlfin)( run_id, problem_id, coding_language, path_code );
			
			/* mutex unlock */
			pthread_mutex_unlock( &proto_dlmgr_mutex );

			free( run_id_str );
			free( problem_id_str );
			free( coding_language_mb );
			free( path_code );
			free( coding_language );
		}
		else if( RQID == OPID_PUPDATE )
		{
			proto_problem_update( sockfd, msgptr );
		}
		else if( RQID == OPID_PREMOVE )
		{
			proto_problem_remove( msgptr );
		}
		else if( RQID == OPID_TAKE_RESULT )
		{
			char *run_id_str = proto_str_split( msgptr, &msgptr );
			char *success_str = proto_str_split( msgptr, NULL );


			unsigned int run_id = atoi( run_id_str );
			int success = atoi( success_str );

			(*cb_take_result)( run_id, success );

			free( run_id_str );
			free( success_str );
		}
		else if( RQID == OPID_CLAR_REQUEST )
		{
			proto_clar_request( msgptr );
		}
		else if( RQID == OPID_CLAR_REPLY )
		{
			proto_clar_reply( msgptr );
		}
		else
		{
#if PROTO_DBG > 0
			printf("[judgeproto_reqhand_thread()] Invalid SRID bytes.\n");
#endif
		}
	}

	free( src_ipaddr );
	free( recvbuf );
	shutdown_wr_sp( sockfd );
	pthread_exit( NULL );
	return NULL;
}


int judgeproto_login( const char *destip, const wchar_t *account, const char *password )
{
	return proto_login( destip, OPSR_JUDGE, account, password );
}

int judgeproto_logout( const char *destip, unsigned int account_id )
{
	return proto_logout( destip, OPSR_JUDGE, account_id );
}

int judgeproto_password_change( const char *destip, unsigned int account_id, const char *old_password, const char *new_password )
{
	return proto_password_change( destip, OPSR_JUDGE, account_id, old_password, new_password );
}

/* run result */
int judgeproto_judge_result( const char *destip, unsigned int run_id, const wchar_t *result_string )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *run_id_str = uint2str( run_id );
	char *result_string_mb = proto_str_presend( result_string );

	msgptr = proto_srid_comb( sendbuf, OPSR_JUDGE, OPID_RUN_RESULT );
	msgptr = proto_str_comb( msgptr, run_id_str );
	msgptr = proto_str_comb( msgptr, result_string_mb );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[judgeproto_judge_result()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( run_id_str );
	free( result_string_mb );

	return 0;
}

int judgeproto_run_sync( const char *destip )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;

	msgptr = proto_srid_comb( sendbuf, OPSR_JUDGE, OPID_RUN_SYNC );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[judgeproto_run_update()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );

	return 0;
}

int judgeproto_take_run( const char *destip, unsigned int run_id )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *run_id_str = uint2str( run_id );

	msgptr = proto_srid_comb( sendbuf, OPSR_JUDGE, OPID_TAKE_RUN );
	msgptr = proto_str_comb( msgptr, run_id_str );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[judgeproto_take_run()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( run_id_str );
	return 0;
}


int judgeproto_clar_result( const char *destip, unsigned int clar_id, int private_byte, const wchar_t *result_string )
{
	return proto_clar_result( destip, OPSR_JUDGE, clar_id, private_byte, result_string );
}

int judgeproto_timer_sync( const char *destip )
{
	return proto_timer_sync( destip, OPSR_JUDGE );
}

int judgeproto_contest_state_sync( const char *destip )
{
	return proto_contest_state_sync( destip, OPSR_JUDGE );
}

int judgeproto_clar_sync( const char *destip )
{
	return proto_clar_sync( destip, OPSR_JUDGE );
}

int judgeproto_problem_sync( const char *destip )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;

	msgptr = proto_srid_comb( sendbuf, OPSR_JUDGE, OPID_JPROBLEM_SYNC );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[judgeproto_problem_sync()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	return 0;
}
