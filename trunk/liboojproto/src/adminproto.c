﻿/* adminproto.c
 * Source code file for administration client protocol implementation. */

#include "adminproto.h"

/* callback registration check function, return 1(true) if all functions has been registered */
static int adminproto_cbcheck( void );

/* callback functions */
void (*cb_account_info)( unsigned int account_id, unsigned int type, wchar_t *account )    = NULL;
void (*cb_problem_info)( unsigned int problem_id, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer )    = NULL;
void (*cb_problem_info_dlfin)( unsigned int problem_id, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer ) = NULL;

/* callback functions extern-ed from protointernal.c */
extern void (*cb_login_confirm)( int confirm_code, unsigned int account_id );
extern void (*cb_logout_confirm)( int confirm_code );
extern void (*cb_timer_set)( unsigned int hours, unsigned int minutes, unsigned int seconds );
extern void (*cb_contest_start)( void );
extern void (*cb_contest_stop)( void );
extern void (*cb_clar_request)( unsigned int clar_id, int private_byte, wchar_t *clarmsg );
extern void (*cb_sb_update)( unsigned int updated_account_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time );

/* thread function */
void *adminproto_reqhand_thread( void *args );

/* external sync variable (from proto_commonfunction.c) */
extern pthread_mutex_t proto_sockfd_pass_mutex;
extern pthread_cond_t proto_sockfd_pass_cv;

int adminproto_listen( char *localaddr )
{
	/* dont start listening if callback functions are not fully registered. */
	if( !adminproto_cbcheck() )
	{
#if PROTO_DBG > 0
		printf("[adminproto_listen()] All callbacks should be registered before start.\n");
#endif
		return -1;
	}

	if( proto_listen( localaddr, LISTEN_PORT_ADMIN, adminproto_reqhand_thread ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[adminproto_listen()] proto_listen() call failed.\n");
#endif
		return -1;
	}

	return 0;
}

int adminproto_stop_listen( void )
{
	if( proto_stop_listen() < 0 )
	{
#if PROTO_DBG > 0
		printf("[adminproto_stop_listen] proto_stop_listen() call failed.\n");
#endif
		return -1;
	}

	return 0;
}

int adminproto_active( void )
{
	return proto_active();
}

void *adminproto_reqhand_thread( void *args )
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
		if( RQID == OPID_CLAR_REQUEST )
		{
			proto_clar_request( msgptr );
		}
		else if( RQID == OPID_ACC_INFO )
		{
			char *account_id_str = proto_str_split( msgptr, &msgptr );
			char *type_str = proto_str_split( msgptr, &msgptr );
			char *account_mb = proto_str_split( msgptr, NULL );

			unsigned int account_id = atoi( account_id_str );
			unsigned int type = atoi( type_str );
			wchar_t *account = proto_str_postrecv( account_mb );

			(*cb_account_info)( account_id, type, account );

			free( account_id_str );
			free( type_str );
			free( account_mb );
			free( account );
		}
		else if( RQID == OPID_P_INFO )
		{
			char *problem_id_str = proto_str_split( msgptr, &msgptr );
			wchar_t *path_description = NULL, *path_input = NULL, *path_answer = NULL;

			unsigned int problem_id = atoi( problem_id_str );

			(*cb_problem_info)( problem_id, &path_description, &path_input, &path_answer );

			/* download files */
			filerecv( sockfd, path_description );
			filerecv( sockfd, path_input );
			filerecv( sockfd, path_answer );

			(*cb_problem_info_dlfin)( problem_id, path_description, path_input, path_answer );

			free( problem_id_str );
			free( path_description );
			free( path_input );
			free( path_answer );
		}
		else if( RQID == OPID_SB_UPDATE )
		{
			proto_sb_update( msgptr );
		}
		else
		{
#if PROTO_DBG > 0
		printf("[adminproto_reqhand_thread()] Inavlid SRID bytes.\n");
#endif
		}
	}
	else
	{
#if PROTO_DBG > 0
		printf("[adminproto_reqhand_thread()] Invalid SRID bytes.\n");
#endif
	}

	shutdown_wr_sp( sockfd );
	pthread_exit( NULL );
}

int adminproto_login( char *destip, wchar_t *account, char *password )
{
	return proto_login( destip, OPSR_ADMIN, account, password );
}

int adminproto_logout( char *destip, unsigned int account_id )
{
	return proto_logout( destip, OPSR_ADMIN, account_id );
}

int adminproto_account_add( char *destip, unsigned int type, wchar_t *account, char *password )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *acc_opid_str = uint2str( ACC_OPID_ADD );
	char *type_str = uint2str( type );
	char *account_mb = proto_str_presend( account );

	msgptr = proto_srid_comb( sendbuf, OPSR_ADMIN, OPID_ACC_MANAGE );
	msgptr = proto_str_comb( msgptr, acc_opid_str );
	msgptr = proto_str_comb( msgptr, type_str );
	msgptr = proto_str_comb( msgptr, account_mb );
	msgptr = proto_str_comb( msgptr, password );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[adminproto_account_add()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( acc_opid_str );
	free( type_str );
	free( account_mb );

	return 0;
}

int adminproto_account_del( char *destip, unsigned int account_id )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *acc_opid_str = uint2str( ACC_OPID_DEL );
	char *account_id_str = uint2str( account_id );

	msgptr = proto_srid_comb( sendbuf, OPSR_ADMIN, OPID_ACC_MANAGE );
	msgptr = proto_str_comb( msgptr, acc_opid_str );
	msgptr = proto_str_comb( msgptr, account_id_str );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[adminproto_account_del()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( acc_opid_str );
	free( account_id_str );

	return 0;
}

int adminproto_account_mod( char *destip, unsigned int account_id, wchar_t *new_account, char *new_password )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *acc_opid_str = uint2str( ACC_OPID_MOD );
	char *account_id_str = uint2str( account_id );
	char *new_account_mb = proto_str_presend( new_account );

	msgptr = proto_srid_comb( sendbuf, OPSR_ADMIN, OPID_ACC_MANAGE );
	msgptr = proto_str_comb( msgptr, acc_opid_str );
	msgptr = proto_str_comb( msgptr, account_id_str );
	msgptr = proto_str_comb( msgptr, new_account_mb );
	msgptr = proto_str_comb( msgptr, new_password );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[adminproto_account_mod()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( acc_opid_str );
	free( account_id_str );
	free( new_account_mb );

	return 0;
}

int adminproto_account_update( char *destip )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *acc_opid_str = uint2str( ACC_OPID_UPDATE );

	msgptr = proto_srid_comb( sendbuf, OPSR_ADMIN, OPID_ACC_MANAGE );
	msgptr = proto_str_comb( msgptr, acc_opid_str );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[adminproto_account_update()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( acc_opid_str );

	return 0;
}

int adminproto_problem_add( char *destip, unsigned int problem_id, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *p_opid_str = uint2str( P_OPID_ADD );
	char *problem_id_str = uint2str( problem_id );

	msgptr = proto_srid_comb( sendbuf, OPSR_ADMIN, OPID_P_MANAGE );
	msgptr = proto_str_comb( msgptr, p_opid_str );
	msgptr = proto_str_comb( msgptr, problem_id_str );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[adminproto_problem_add()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	/* upload files */
	filesend( sockfd, path_description );
	filesend( sockfd, path_input );
	filesend( sockfd, path_answer );

	shutdown_wr_sp( sockfd );
	free( p_opid_str );
	free( problem_id_str );

	return 0;
}

int adminproto_problem_del( char *destip, unsigned int problem_id )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *p_opid_str = uint2str( P_OPID_DEL );
	char *problem_id_str = uint2str( problem_id );

	msgptr = proto_srid_comb( sendbuf, OPSR_ADMIN, OPID_P_MANAGE );
	msgptr = proto_str_comb( msgptr, p_opid_str );
	msgptr = proto_str_comb( msgptr, problem_id_str );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[adminproto_problem_del()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( p_opid_str );
	free( problem_id_str );

	return 0;
}

int adminproto_problem_mod( char *destip, unsigned int problem_id, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *p_opid_str = uint2str( P_OPID_MOD );
	char *problem_id_str = uint2str( problem_id );

	msgptr = proto_srid_comb( sendbuf, OPSR_ADMIN, OPID_P_MANAGE );
	msgptr = proto_str_comb( msgptr, p_opid_str );
	msgptr = proto_str_comb( msgptr, problem_id_str );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[adminproto_problem_mod()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	/* upload files */
	filesend( sockfd, path_description );
	filesend( sockfd, path_input );
	filesend( sockfd, path_answer );

	shutdown_wr_sp( sockfd );
	free( p_opid_str );
	free( problem_id_str );

	return 0;
}

int adminproto_problem_update( char *destip )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *p_opid_str = uint2str( P_OPID_UPDATE );

	msgptr = proto_srid_comb( sendbuf, OPSR_ADMIN, OPID_P_MANAGE );
	msgptr = proto_str_comb( msgptr, p_opid_str );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[adminproto_problem_update()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( p_opid_str );

	return 0;
}

int adminproto_clar_result( char *destip, unsigned int clar_id, int private_byte, wchar_t *result_string )
{
	if( proto_clar_result( destip, OPSR_ADMIN, clar_id, private_byte, result_string ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[adminproto_clar_result] proto_clar_result() call failed.\n");
#endif
		return -1;
	}

	return 0;
}

int adminproto_timer_set( char *destip, unsigned int hours, unsigned int minutes, unsigned int seconds )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *hours_str = uint2str( hours );
	char *minutes_str = uint2str( minutes );
	char *seconds_str = uint2str( seconds );

	msgptr = proto_srid_comb( sendbuf, OPSR_ADMIN, OPID_TIMER_SET );
	msgptr = proto_str_comb( msgptr, hours_str );
	msgptr = proto_str_comb( msgptr, minutes_str );
	msgptr = proto_str_comb( msgptr, seconds_str );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[adminproto_timer_set()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( hours_str );
	free( minutes_str );
	free( seconds_str );

	return 0;

}

int adminproto_contest_start( char *destip )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;

	msgptr = proto_srid_comb( sendbuf, OPSR_ADMIN, OPID_CONTEST_START );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[adminproto_contest_start()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );

	return 0;

}

int adminproto_contest_stop( char *destip )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;

	msgptr = proto_srid_comb( sendbuf, OPSR_ADMIN, OPID_CONTEST_STOP );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[adminproto_contest_stop()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );

	return 0;
}

/* not implemented yet */
int adminproto_broadcast()
{
}


void adminproto_cbreg_login_confirm( void (*cbfunc)( int, unsigned int ) )                    { cb_login_confirm = cbfunc; }
void adminproto_cbreg_logout_confirm( void (*cbfunc)( int ) )                                 { cb_logout_confirm = cbfunc; }
void adminproto_cbreg_timer_set( void (*cbfunc)( unsigned int, unsigned int, unsigned int ) ) { cb_timer_set = cbfunc; }
void adminproto_cbreg_contest_start( void (*cbfunc)( void ) ) { cb_contest_start = cbfunc; }
void adminproto_cbreg_contest_stop( void (*cbfunc)( void ) )  { cb_contest_stop = cbfunc; }
void adminproto_cbreg_clar_request( void (*cbfunc)( unsigned int, int, wchar_t* ) )           { cb_clar_request = cbfunc; }
void adminproto_cbreg_account_info( void (*cbfunc)( unsigned int, unsigned int, wchar_t* ) )  { cb_account_info = cbfunc; }
void adminproto_cbreg_problem_info( void (*cbfunc)( unsigned int, wchar_t**, wchar_t**, wchar_t** ) ) { cb_problem_info = cbfunc; }
void adminproto_cbreg_problem_info_dlfin( void (*cbfunc)( unsigned int, wchar_t*, wchar_t*, wchar_t* ) ) { cb_problem_info_dlfin = cbfunc; }
void adminproto_cbreg_sb_update( void (*cbfunc)( unsigned int, wchar_t*, unsigned int, unsigned int ) )  { cb_sb_update = cbfunc; }

static int adminproto_cbcheck( void )
{
	if( cb_login_confirm == NULL || cb_logout_confirm == NULL ||
		cb_timer_set == NULL || cb_contest_start == NULL || cb_contest_stop == NULL ||
		cb_clar_request == NULL || cb_account_info == NULL || cb_problem_info == NULL ||
		cb_problem_info_dlfin == NULL )
		return 0;
	else
		return 1;
}
