﻿/* judgeproto.c
 * Source code file for judge client protocol implementation. */

#include "judgeproto.h"

/* callback registration check function, return 1(true) if all functions has been registered */
static int judgeproto_cbcheck( void );

/* callback functions */
void (*cb_run_request)( unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code )         = NULL;
void (*cb_run_request_dlfin)( unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code )    = NULL;
void (*cb_problem_update)( unsigned int problem_id, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer )    = NULL;
void (*cb_problem_update_dlfin)( unsigned int problem_id, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer ) = NULL;
void (*cb_take_result)( unsigned int run_id, int success );

/* callback functions extern-ed from protointernal.c */
extern void (*cb_login_confirm)( int confirm_code, unsigned int account_id );
extern void (*cb_logout_confirm)( int confirm_code );
extern void (*cb_timer_set)( unsigned int hours, unsigned int minutes, unsigned int seconds );
extern void (*cb_contest_start)( void );
extern void (*cb_contest_stop)( void );
extern void (*cb_clar_request)( unsigned int clar_id, int private_byte, wchar_t *clarmsg );

/* thread function */
void *judgeproto_reqhand_thread( void *args );

/* external sync variable (from proto_commonfunction.c) */
extern pthread_mutex_t proto_sockfd_pass_mutex;
extern pthread_cond_t proto_sockfd_pass_cv;

int judgeproto_listen( char *localaddr )
{
	/* don't start listening if callback functions are not fully registered. */
	if( !judgeproto_cbcheck() )
	{
#if PROTO_DBG > 0
		printf("[judgeproto_listen()] All callbacks should be registered before start.\n");
#endif
		return -1;
	}

	if( proto_listen( localaddr, LISTEN_PORT_JUDGE, judgeproto_reqhand_thread ) < 0 )
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
//	char *src_ipaddr;
	short RQSR, RQID;
	char *msgptr = NULL;

	/* get sockfd from listen thread */
	pthread_mutex_lock( &proto_sockfd_pass_mutex );
	sockfd = *((int *)args);
	pthread_cond_signal( &proto_sockfd_pass_cv );
	pthread_mutex_unlock( &proto_sockfd_pass_mutex );

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

			(*cb_run_request)( run_id, problem_id, coding_language, &path_code );

			/* download file */
			filerecv( sockfd, path_code );

			(*cb_run_request_dlfin)( run_id, problem_id, coding_language, path_code );

			free( run_id_str );
			free( problem_id_str );
			free( coding_language_mb );
			free( path_code );
			free( coding_language );
		}
		else if( RQID == OPID_PUPDATE )
		{
			char *problem_id_str = proto_str_split( msgptr, &msgptr );
			wchar_t *path_description = NULL, *path_input = NULL, *path_answer = NULL;

			unsigned int problem_id = atoi( problem_id_str );

			(*cb_problem_update)( problem_id, &path_description, &path_input, &path_answer );

			/* download file */
			filerecv( sockfd, path_description );
			filerecv( sockfd, path_input );
			filerecv( sockfd, path_answer );

			(*cb_problem_update_dlfin)( problem_id, path_description, path_input, path_answer );

			free( problem_id_str );
			free( path_description );
			free( path_input );
			free( path_answer );
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
		else
		{
#if PROTO_DBG > 0
			printf("[judgeproto_reqhand_thread()] Invalid SRID bytes.\n");
#endif
		}
	}
	else
	{
#if PROTO_DBG > 0
		printf("[judgeproto_reqhand_thread()] Invalid SRID bytes.\n");
#endif
	}

	free( recvbuf );

	shutdown_wr_sp( sockfd );
	pthread_exit( NULL );
}

int judgeproto_login( char *destip, wchar_t *account, char *password )
{
	return proto_login( destip, OPSR_JUDGE, account, password );
}

int judgeproto_logout( char *destip, unsigned int account_id )
{
	return proto_logout( destip, OPSR_JUDGE, account_id );
}

/* run result */
int judgeproto_judge_result( char *destip, unsigned int run_id, wchar_t *result_string )
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

int judgeproto_run_update( char *destip )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	
	msgptr = proto_srid_comb( sendbuf, OPSR_JUDGE, OPID_UPDATE_RUN );

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

int judgeproto_take_run( char *destip, unsigned int run_id )
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

	return 0;
}

int judgeproto_clar_result( char *destip, unsigned int clar_id, int private_byte, wchar_t *result_string )
{
	if( proto_clar_result( destip, OPSR_JUDGE, clar_id, private_byte, result_string ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[judgeproto_clar_result()] proto_clar_result() call failed.\n");
#endif
		return -1;
	}

	return 0;
}


void judgeproto_cbreg_login_confirm( void (*cbfunc)( int, unsigned int ) ) { cb_login_confirm = cbfunc; }
void judgeproto_cbreg_logout_confirm( void (*cbfunc)( int ) )              { cb_logout_confirm = cbfunc; }
void judgeproto_cbreg_timer_set( void (*cbfunc)( unsigned int, unsigned int, unsigned int ) ) { cb_timer_set = cbfunc; }
void judgeproto_cbreg_contest_start( void (*cbfunc)( void ) ) { cb_contest_start = cbfunc; }
void judgeproto_cbreg_contest_stop( void (*cbfunc)( void ) )  { cb_contest_stop = cbfunc; }
void judgeproto_cbreg_run_request( void (*cbfunc)( unsigned int, unsigned int, wchar_t*, wchar_t** ) )      { cb_run_request = cbfunc; }
void judgeproto_cbreg_run_request_dlfin( void (*cbfunc)( unsigned int, unsigned int, wchar_t*, wchar_t* ) ) { cb_run_request_dlfin = cbfunc; }
void judgeproto_cbreg_problem_update( void (*cbfunc)( unsigned int, wchar_t**, wchar_t**, wchar_t** ) )     { cb_problem_update = cbfunc; }
void judgeproto_cbreg_problem_update_dlfin( void (*cbfunc)( unsigned int, wchar_t*, wchar_t*, wchar_t* ) )  { cb_problem_update_dlfin = cbfunc; }
void judgeproto_cbreg_take_result( void (*cbfunc)( unsigned int, int ) ) { cb_take_result = cbfunc; }
void judgeproto_cbreg_clar_request( void (*cbfunc)( unsigned int, int, wchar_t* ) ) { cb_clar_request = cbfunc; }

static int judgeproto_cbcheck( void )
{
	if( cb_login_confirm == NULL || cb_logout_confirm == NULL ||
		cb_timer_set == NULL || cb_contest_start == NULL || cb_contest_stop == NULL ||
		cb_run_request == NULL || cb_run_request_dlfin == NULL ||
		cb_problem_update == NULL || cb_problem_update_dlfin == NULL || cb_clar_request == NULL )
		return 0;
	else
		return 1;
}