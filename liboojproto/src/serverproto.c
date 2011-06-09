﻿/* serverproto.c
 * Source code file for server protocol implementation. */

#include "serverproto.h"

/* callback registration check function, return 1(true) if all functions has been registered */
static int serverproto_cbcheck( void );

/* callback functions */
void (*cb_login_request)( char *srcip, short srctype, wchar_t *account, char *password ) = NULL;
void (*cb_logout_request)( char *srcip, short srctype, unsigned int account_id )         = NULL;
void (*cb_password_change)( char *srcip, short srctype, unsigned int account_id, char *old_password, char *new_password )       = NULL;
void (*cb_timer_sync)( char *srcip, short srctype ) = NULL;
void (*cb_contest_state_sync)( char *srcip, short srctype ) = NULL;
void (*cb_admin_timer_set)( char *srcip, unsigned int hours, unsigned int minutes, unsigned int seconds ) = NULL;
void (*cb_admin_contest_start)( char *srcip ) = NULL;
void (*cb_admin_contest_stop)( char *srcip )  = NULL;
void (*cb_submission_request)( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code )      = NULL;
void (*cb_submission_request_dlfin)( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code ) = NULL;
void (*cb_tsclar_request)( char *srcip, unsigned int account_id, int private_byte, wchar_t *clarmsg ) = NULL;
void (*cb_clar_sync)( char *srcip, short srctype ) = NULL;
void (*cb_pd_request)( char *srcip, unsigned int account_id, unsigned int problem_id )              = NULL;
void (*cb_sb_sync)( char *srcip, short srctype )             = NULL;
void (*cb_trun_sync)( char *srcip, unsigned int account_id )   = NULL;
void (*cb_run_result_notify)( char *srcip, unsigned int run_id, wchar_t *result )                   = NULL;
void (*cb_run_sync)( char *srcip )  = NULL;
void (*cb_take_run)( char *srcip, unsigned int run_id )        = NULL;
void (*cb_account_add)( char *srcip, unsigned int type, wchar_t *account, char *password )          = NULL;
void (*cb_account_del)( char *srcip, unsigned int account_id ) = NULL;
void (*cb_account_mod)( char *srcip, unsigned int account_id, wchar_t *new_account, char *new_password ) = NULL;
void (*cb_account_sync)( char *srcip )      = NULL;
void (*cb_problem_add)( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer )    = NULL;
void (*cb_problem_add_dlfin)( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer ) = NULL;
void (*cb_problem_del)( char *srcip, unsigned int problem_id )                                                                             = NULL;
void (*cb_problem_mod)( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer )    = NULL;
void (*cb_problem_mod_dlfin)( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer ) = NULL;
void (*cb_problem_sync)( char *srcip, short srctype )      = NULL;
void (*cb_clar_result)( char *srcip, unsigned int clar_id, int private_byte, wchar_t *result_string ) = NULL;

/* callback registration functions */
void serverproto_cbreg_login_request( void (*cbfunc)( char*, short, wchar_t*, char* ) )  { cb_login_request = cbfunc; }
void serverproto_cbreg_logout_request( void (*cbfunc)( char*, short, unsigned int ) )    { cb_logout_request = cbfunc; }
void serverproto_cbreg_password_change( void (*cbfunc)( char*, short, unsigned int, char*, char* ) )   { cb_password_change = cbfunc; }
void serverproto_cbreg_timer_sync( void (*cbfunc)( char*, short ) ) { cb_timer_sync = cbfunc; }
void serverproto_cbreg_contest_state_sync( void (*cbfunc)( char*, short ) ) { cb_contest_state_sync = cbfunc; }
void serverproto_cbreg_admin_timer_set( void (*cbfunc)( char*, unsigned int, unsigned int, unsigned int ) ) { cb_admin_timer_set = cbfunc; }
void serverproto_cbreg_admin_contest_start( void (*cbfunc)( char* ) ) { cb_admin_contest_start = cbfunc; }
void serverproto_cbreg_admin_contest_stop( void (*cbfunc)( char* ) )  { cb_admin_contest_stop = cbfunc; }
void serverproto_cbreg_submission_request( void (*cbfunc)( char*, unsigned int, unsigned int, wchar_t*, wchar_t** ) )      { cb_submission_request = cbfunc; }
void serverproto_cbreg_submission_request_dlfin( void (*cbfunc)( char*, unsigned int, unsigned int, wchar_t*, wchar_t* ) ) { cb_submission_request_dlfin = cbfunc; }
void serverproto_cbreg_tsclar_request( void (*cbfunc)( char*, unsigned int, int, wchar_t* ) )  { cb_tsclar_request = cbfunc; }
void serverproto_cbreg_clar_sync( void (*cbfunc)( char*, short ) ) { cb_clar_sync = cbfunc; }
void serverproto_cbreg_pd_request( void (*cbfunc)( char*, unsigned int, unsigned int ) )     { cb_pd_request = cbfunc; }
void serverproto_cbreg_sb_sync( void (*cbfunc)( char*, short ) ) { cb_sb_sync = cbfunc; }
void serverproto_cbreg_trun_sync( void (*cbfunc)( char*, unsigned int ) ) { cb_trun_sync = cbfunc; }
void serverproto_cbreg_run_result_notify( void (*cbfunc)( char*, unsigned int, wchar_t* ) )  { cb_run_result_notify = cbfunc; }
void serverproto_cbreg_run_sync( void (*cbfunc)( char* ) )  { cb_run_sync = cbfunc; }
void serverproto_cbreg_take_run( void (*cbfunc)( char*, unsigned int ) ) { cb_take_run = cbfunc; }
void serverproto_cbreg_account_add( void (*cbfunc)( char*, unsigned int, wchar_t*, char* ) ) { cb_account_add = cbfunc; }
void serverproto_cbreg_account_del( void (*cbfunc)( char*, unsigned int ) )                  { cb_account_del = cbfunc; }
void serverproto_cbreg_account_mod( void (*cbfunc)( char*, unsigned int, wchar_t*, char* ) ) { cb_account_mod = cbfunc; }
void serverproto_cbreg_account_sync( void (*cbfunc)( char* ) )                             { cb_account_sync = cbfunc; }
void serverproto_cbreg_problem_add( void (*cbfunc)( char*, unsigned int, wchar_t*, unsigned int, wchar_t**, wchar_t**, wchar_t** ) )    { cb_problem_add = cbfunc; }
void serverproto_cbreg_problem_add_dlfin( void (*cbfunc)( char*, unsigned int, wchar_t*, unsigned int, wchar_t*, wchar_t*, wchar_t* ) ) { cb_problem_add_dlfin = cbfunc; }
void serverproto_cbreg_problem_del( void (*cbfunc)( char*, unsigned int ) )                  { cb_problem_del = cbfunc; }
void serverproto_cbreg_problem_mod( void (*cbfunc)( char*, unsigned int, wchar_t*, unsigned int, wchar_t**, wchar_t**, wchar_t** ) )    { cb_problem_mod = cbfunc; }
void serverproto_cbreg_problem_mod_dlfin( void (*cbfunc)( char*, unsigned int, wchar_t*, unsigned int, wchar_t*, wchar_t*, wchar_t* ) ) { cb_problem_mod_dlfin = cbfunc; }
void serverproto_cbreg_problem_sync( void (*cbfunc)( char*, short ) )                      { cb_problem_sync = cbfunc; }
void serverproto_cbreg_clar_result( void (*cbfunc)( char*, unsigned int, int, wchar_t* ) )   { cb_clar_result = cbfunc; }

/* thread function */
void *serverproto_reqhand_thread( void *args );

/* external sync variable (from proto_commonfunction.c) */
extern pthread_mutex_t proto_sockfd_pass_mutex;
extern pthread_cond_t proto_sockfd_pass_cv;

/* external download management mutex from protointernal_listen.c */
extern pthread_mutex_t proto_dlmgr_mutex;

/* callback registration check function */
static int serverproto_cbcheck( void )
{
	if( cb_login_request == NULL || cb_logout_request == NULL || cb_password_change == NULL || cb_timer_sync == NULL ||
		cb_contest_state_sync == NULL || cb_admin_timer_set == NULL || cb_admin_contest_start == NULL ||
		cb_admin_contest_stop == NULL || cb_submission_request == NULL || cb_submission_request_dlfin == NULL ||
		cb_tsclar_request == NULL || cb_clar_sync == NULL || cb_pd_request == NULL || cb_sb_sync == NULL ||
		cb_trun_sync == NULL || cb_run_result_notify == NULL || cb_run_sync == NULL || cb_take_run == NULL ||
		cb_account_add == NULL || cb_account_del == NULL || cb_account_mod == NULL || cb_account_sync == NULL ||
		cb_problem_add == NULL || cb_problem_add_dlfin == NULL || cb_problem_del == NULL || cb_problem_mod == NULL ||
		cb_problem_mod_dlfin == NULL || cb_problem_sync == NULL || cb_clar_result == NULL )
		return 0;
	else
		return 1;
}

int serverproto_listen( char *localaddr )
{
	/* dont start listening if callback functions are not fully registered. */
	if( !serverproto_cbcheck() )
	{
#if PROTO_DBG > 0
		printf("[serverproto_listen()] All callbacks should be registered before start.\n");
#endif
		return -1;
	}

	if( proto_listen( localaddr, LISTEN_PORT_SERVER, LISTEN_PORT_VSFTP_SERVER, serverproto_reqhand_thread ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_listen()] proto_listen() call failed.\n");
#endif
		return -1;
	}
}

int serverproto_stop_listen( void )
{
	if( proto_stop_listen() < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_stop_listen()] proto_stop_listen() call failed.\n");
#endif
		return -1;
	}

	return 0;
}

int serverproto_active( void )
{
	return proto_active();
}

void *serverproto_reqhand_thread( void *args )
{
	int sockfd;
	char *recvbuf = NULL;
	char *src_ipaddr;
	short RQSR, RQID;  /* ReQuest SouRce & ReQuest ID */
	char *msgptr = NULL;

	/* get sockfd from listen thread
	 * avoid race condition using condition variable */
	pthread_mutex_lock( &proto_sockfd_pass_mutex );
	sockfd = *((int *)args);
	pthread_cond_signal( &proto_sockfd_pass_cv );
	pthread_mutex_unlock( &proto_sockfd_pass_mutex );

	src_ipaddr = tcp_getaddr( sockfd );

	/* receive and interpret message */
	recv_sp( sockfd, &recvbuf );
	msgptr = proto_srid_split( recvbuf, &RQSR, &RQID );

	/* request handling */
	/* part 1. account status management */
	if( between( RQID, 0, 10 ) )
	{
		if( RQID == OPID_LOGIN_REQUEST )
		{
			char *account_mb = proto_str_split( msgptr, &msgptr );
			char *password = proto_str_split( msgptr, NULL );
			
			wchar_t *account = proto_str_postrecv( account_mb );

			(*cb_login_request)( src_ipaddr, RQSR, account, password );

			free( account_mb );
			free( password );
			free( account );
		}
		else if( RQID == OPID_LOGOUT_REQUEST )
		{
			char *account_id_str = proto_str_split( msgptr, NULL );
			unsigned int account_id = atoi( account_id_str );

			(*cb_logout_request)( src_ipaddr, RQSR, account_id );

			free( account_id_str );
		}
		else if( RQID = OPID_PASSWD_CHANGE )
		{
			char *account_id_str = proto_str_split( msgptr, &msgptr );
			char *old_password = proto_str_split( msgptr, &msgptr );
			char *new_password = proto_str_split( msgptr, NULL );

			unsigned int account_id = atoi( account_id_str );

			(*cb_password_change)( src_ipaddr, RQSR, account_id, old_password, new_password );

			free( account_id_str );
			free( old_password );
			free( new_password );
		}
	}
	/* part 2. time control & start and stop */
	else if( between( RQID, 200, 210 ) && RQSR == OPSR_ADMIN )
	{
		if( RQID == OPID_TIMER_SET )
		{
			char *hours_str = proto_str_split( msgptr, &msgptr );
			char *minutes_str = proto_str_split( msgptr, &msgptr );
			char *seconds_str = proto_str_split( msgptr, NULL );

			unsigned int hours = atoi( hours_str );
			unsigned int minutes = atoi( minutes_str );
			unsigned int seconds = atoi( seconds_str );

			(*cb_admin_timer_set)( src_ipaddr, hours, minutes, seconds );

			free( hours_str );
			free( minutes_str );
			free( seconds_str );
		}
		else if( RQID == OPID_CONTEST_START )
		{
			(*cb_admin_contest_start)( src_ipaddr );
		}
		else if( RQID == OPID_CONTEST_STOP )
		{
			(*cb_admin_contest_stop)( src_ipaddr );
		}
	}
	/* part 3. multi-source requests */
	else if( RQID == OPID_CLAR_RESULT && ( RQSR == OPSR_ADMIN || RQSR == OPSR_JUDGE ) )
	{
		char *clar_id_str = proto_str_split( msgptr, &msgptr );
		char *private_byte_str = proto_str_split( msgptr, &msgptr );
		char *result_string_mb = proto_str_split( msgptr, NULL );

		unsigned int clar_id = atoi( clar_id_str );
		int private_byte = atoi( private_byte_str );
		wchar_t *result_string = proto_str_postrecv( result_string_mb );

		(*cb_clar_result)( src_ipaddr, clar_id, private_byte, result_string );

		free( clar_id_str );
		free( private_byte_str );
		free( result_string_mb );
		free( result_string );
	}
	else if( RQID == OPID_CLAR_SYNC && ( RQSR == OPSR_ADMIN || RQSR == OPSR_JUDGE ) )
	{
		(*cb_clar_sync)( src_ipaddr, RQSR );
	}
	else if( RQID == OPID_SB_SYNC && ( RQSR == OPSR_ADMIN || RQSR == OPSR_TEAM ) )
	{
		(*cb_sb_sync)( src_ipaddr, RQSR );
	}
	else if( RQID == OPID_TIMER_SYNC )
	{
		(*cb_timer_sync)( src_ipaddr, RQSR );
	}
	else if( RQID == OPID_CONTEST_STATE_SYNC )
	{
		(*cb_contest_state_sync)( src_ipaddr, RQSR );
	}
	/* part 4. other single-source requests */
	else if( RQSR == OPSR_ADMIN )
	{
		if( RQID == OPID_ACC_MANAGE )
		{
			char *acc_opid_str = proto_str_split( msgptr, &msgptr );
			unsigned int acc_opid = atoi( acc_opid_str );

			if( acc_opid == ACC_OPID_ADD )
			{
				char *type_str = proto_str_split( msgptr, &msgptr );
				char *account_mb = proto_str_split( msgptr, &msgptr );
				char *password = proto_str_split( msgptr, NULL );

				unsigned int type = atoi( type_str );
				wchar_t *account = proto_str_postrecv( account_mb );

				(*cb_account_add)( src_ipaddr, type, account, password );

				free( type_str );
				free( account_mb );
				free( password );
				free( account );
			}
			else if( acc_opid == ACC_OPID_DEL )
			{
				char *account_id_str = proto_str_split( msgptr, NULL );

				unsigned int account_id = atoi( account_id_str );

				(*cb_account_del)( src_ipaddr, account_id );

				free( account_id_str );
			}
			else if( acc_opid == ACC_OPID_MOD )
			{
				char *account_id_str = proto_str_split( msgptr, &msgptr );
				char *new_account_mb = proto_str_split( msgptr, &msgptr );
				char *new_password = proto_str_split( msgptr, NULL );

				unsigned int account_id = atoi( account_id_str );
				wchar_t *new_account = proto_str_postrecv( new_account_mb );

				(*cb_account_mod)( src_ipaddr, account_id, new_account, new_password );

				free( account_id_str );
				free( new_account_mb );
				free( new_password );
				free( new_account );
			}
			else if( acc_opid == ACC_OPID_SYNC )
			{
				(*cb_account_sync)( src_ipaddr );
			}

			free( acc_opid_str );
		}
		else if( RQID == OPID_P_MANAGE )
		{
			char *p_opid_str = proto_str_split( msgptr, &msgptr );
			unsigned int p_opid = atoi( p_opid_str );

			if( p_opid == P_OPID_ADD )
			{
				char *problem_id_str = proto_str_split( msgptr, &msgptr );
				char *problem_name_mb = proto_str_split( msgptr, &msgptr );
				char *time_limit_str = proto_str_split( msgptr ,NULL );

				unsigned int problem_id = atoi( problem_id_str );
				wchar_t *problem_name = proto_str_postrecv( problem_name_mb );
				unsigned int time_limit = atoi( time_limit_str );
				wchar_t *path_description = NULL, *path_input = NULL, *path_answer = NULL;
				
				/* mutex lock protection -- prevent concurrent downloading causing race condition */
				pthread_mutex_lock( &proto_dlmgr_mutex );
				send_sp( sockfd, "FSREADY", BUFLEN );

				(*cb_problem_add)( src_ipaddr, problem_id, problem_name, time_limit, &path_description, &path_input, &path_answer );

				/* download files */
				filerecv( path_description );
				printf("first file received.\n");
				filerecv( path_input );
				printf("second file received.\n");
				filerecv( path_answer );

				(*cb_problem_add_dlfin)( src_ipaddr, problem_id, problem_name, time_limit, path_description, path_input, path_answer );

				/* mutex unlock */
				pthread_mutex_unlock( &proto_dlmgr_mutex );
				
				free( problem_id_str );
				free( problem_name_mb );
				free( problem_name );
				free( time_limit_str );
				free( path_description );
				free( path_input );
				free( path_answer );
			}
			else if( p_opid == P_OPID_DEL )
			{
				char *problem_id_str = proto_str_split( msgptr, NULL );

				unsigned int problem_id = atoi( problem_id_str );

				(*cb_problem_del)( src_ipaddr, problem_id );

				free( problem_id_str );
			}
			else if( p_opid == P_OPID_MOD )
			{
				char *problem_id_str = proto_str_split( msgptr, &msgptr );
				char *problem_name_mb = proto_str_split( msgptr, &msgptr );
				char *time_limit_str = proto_str_split( msgptr, NULL );

				unsigned int problem_id = atoi( problem_id_str );
				wchar_t *problem_name = proto_str_postrecv( problem_name_mb );
				unsigned int time_limit = atoi( time_limit_str );
				wchar_t *path_description = NULL, *path_input = NULL, *path_answer = NULL;
				
				/* mutex lock protection -- prevent concurrent downloading causing race condition */
				pthread_mutex_lock( &proto_dlmgr_mutex );
				send_sp( sockfd, "FSREADY", BUFLEN );

				(*cb_problem_mod)( src_ipaddr, problem_id, problem_name, time_limit, &path_description, &path_input, &path_answer );

				/* download files */
				filerecv( path_description );
				filerecv( path_input );
				filerecv( path_answer );

				(*cb_problem_mod_dlfin)( src_ipaddr, problem_id, problem_name, time_limit, path_description, path_input, path_answer );
				
				/* mutex unlock */
				pthread_mutex_unlock( &proto_dlmgr_mutex );

				free( problem_id_str );
				free( problem_name_mb );
				free( problem_name );
				free( time_limit_str );
				free( path_description );
				free( path_input );
				free( path_answer );
			}
			else if( p_opid == P_OPID_SYNC )
			{
				(*cb_problem_sync)( src_ipaddr, RQSR );
			}

			free( p_opid_str );
		}
		else
		{
#if PROTO_DBG > 0
		printf("[serverproto_reqhand_thread()] Invalid SRID bytes.\n");
#endif
		}
	}
	else if( RQSR == OPSR_JUDGE )
	{
		if( RQID == OPID_RUN_RESULT )
		{
			char *run_id_str = proto_str_split( msgptr, &msgptr );
			char *result_mb = proto_str_split( msgptr, NULL );

			unsigned int run_id = atoi( run_id_str );
			wchar_t *result = proto_str_postrecv( result_mb );

			(*cb_run_result_notify)( src_ipaddr, run_id, result );

			free( run_id_str );
			free( result_mb );
			free( result );
		}
		else if( RQID == OPID_RUN_SYNC )
		{
			(*cb_run_sync)( src_ipaddr );
		}
		else if( RQID == OPID_TAKE_RUN )
		{
			char *run_id_str = proto_str_split( msgptr, NULL );

			unsigned int run_id = atoi( run_id_str );

			(*cb_take_run)( src_ipaddr, run_id );

			free( run_id_str );
		}
		else if( RQID == OPID_JPROBLEM_SYNC )
		{
			(*cb_problem_sync)( src_ipaddr, RQSR );
		}
		else
		{
#if PROTO_DBG > 0
		printf("[serverproto_reqhand_thread()] Invalid SRID bytes.\n");
#endif
		}
	}
	else if( RQSR == OPSR_TEAM )
	{
		if( RQID == OPID_SUBMISSION )
		{
			char *account_id_str = proto_str_split( msgptr, &msgptr );
			char *problem_id_str = proto_str_split( msgptr, &msgptr );
			char *coding_language_mb = proto_str_split( msgptr, NULL );

			unsigned int account_id = atoi( account_id_str );
			unsigned int problem_id = atoi( problem_id_str );
			wchar_t *coding_language = proto_str_postrecv( coding_language_mb );
			wchar_t *path_code = NULL;

			/* mutex lock protection -- prevent concurrent downloading causing race condition */
			pthread_mutex_lock( &proto_dlmgr_mutex );
			send_sp( sockfd, "FSREADY", BUFLEN );
			
			(*cb_submission_request)( src_ipaddr, account_id, problem_id, coding_language, &path_code );

			/* download file */
			filerecv( path_code );

			(*cb_submission_request_dlfin)( src_ipaddr, account_id, problem_id, coding_language, path_code );
			
			/* mutex unlock */
			pthread_mutex_unlock( &proto_dlmgr_mutex );

			free( account_id_str );
			free( problem_id_str );
			free( coding_language_mb );
			free( coding_language );
			free( path_code );
		}
		else if( RQID == OPID_CLAR )
		{
			char *account_id_str = proto_str_split( msgptr, &msgptr );
			char *private_byte_str = proto_str_split( msgptr, &msgptr );
			char *clarmsg_mb = proto_str_split( msgptr, NULL );

			unsigned int account_id = atoi( account_id_str );
			int private_byte = atoi( private_byte_str );
			wchar_t *clarmsg = proto_str_postrecv( clarmsg_mb );

			(*cb_tsclar_request)( src_ipaddr, account_id, private_byte, clarmsg );

			free( account_id_str );
			free( private_byte_str );
			free( clarmsg_mb );
			free( clarmsg );
		}
		else if( RQID == OPID_PD_REQUEST )
		{
			char *account_id_str = proto_str_split( msgptr, &msgptr );
			char *problem_id_str = proto_str_split( msgptr, NULL );

			unsigned int account_id = atoi( account_id_str );
			unsigned int problem_id = atoi( problem_id_str );

			(*cb_pd_request)( src_ipaddr, account_id, problem_id );

			free( account_id_str );
			free( problem_id_str );
		}
		else if( RQID == OPID_TRUN_SYNC )
		{
			char *account_id_str = proto_str_split( msgptr, &msgptr );

			unsigned int account_id = atoi( account_id_str );

			(*cb_trun_sync)( src_ipaddr, account_id );

			free( account_id_str );
		}
		else
		{
#if PROTO_DBG > 0
		printf("[serverproto_reqhand_thread()] Invalid SRID bytes.\n");
#endif
		}
	}
	else
	{
#if PROTO_DBG > 0
		printf("[serverproto_reqhand_thread()] Invalid SRID bytes.\n");
#endif
	}

	free( src_ipaddr );
	free( recvbuf );
	shutdown_wr_sp( sockfd );
	pthread_exit( NULL );
}

int serverproto_login_reply( char *destip, short srctype, int confirmation, unsigned int account_id )
{
	int sockfd;
	unsigned short listen_port;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *confirmation_str = int2str( confirmation );
	char *account_id_str = uint2str( account_id );

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_LOGIN_REPLY );
	msgptr = proto_str_comb( msgptr, confirmation_str );
	msgptr = proto_str_comb( msgptr, account_id_str );
	
	if( srctype == OPSR_TEAM )
		listen_port = LISTEN_PORT_TEAM;
	else if( srctype == OPSR_ADMIN )
		listen_port = LISTEN_PORT_ADMIN;
	else if( srctype == OPSR_JUDGE )
		listen_port = LISTEN_PORT_JUDGE;
	else
	{
#if PROTO_DBG > 0
		printf("[serverproto_login_reply()] Wrong source specified.  Reply failed.\n");
#endif
		return -1;
	}

	if( ( sockfd = tcp_connect( destip, listen_port ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_login_reply()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( confirmation_str );
	free( account_id_str );
	return 0;
}

int serverproto_logout_reply( char *destip, short srctype, int confirmation )
{
	int sockfd;
	unsigned short listen_port;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *confirmation_str = int2str( confirmation );

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_LOGOUT_REPLY );
	msgptr = proto_str_comb( msgptr, confirmation_str );

	if( srctype == OPSR_TEAM )
		listen_port = LISTEN_PORT_TEAM;
	else if( srctype == OPSR_ADMIN )
		listen_port = LISTEN_PORT_ADMIN;
	else if( srctype == OPSR_JUDGE )
		listen_port = LISTEN_PORT_JUDGE;
	else
	{
#if PROTO_DBG > 0
		printf("[serverproto_logout_reply()] Wrong source specified.  Reply failed.\n");
#endif
		return -1;
	}

	if( ( sockfd = tcp_connect( destip, listen_port ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_logout_reply()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( confirmation_str );
	return 0;
}

int serverproto_password_change_reply( char *destip, short desttype, int confirmation )
{
	int sockfd;
	unsigned short listen_port;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *confirmation_str = int2str( confirmation );

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_PASSWD_REPLY );
	msgptr = proto_str_comb( msgptr, confirmation_str );

	if( desttype == OPSR_TEAM )
		listen_port = LISTEN_PORT_TEAM;
	else if( desttype == OPSR_ADMIN )
		listen_port = LISTEN_PORT_ADMIN;
	else if( desttype == OPSR_JUDGE )
		listen_port = LISTEN_PORT_JUDGE;
	else
	{
#if PROTO_DBG > 0
		printf("[serverproto_password_change_reply()] Wrong source specified.  Reply failed.\n");
#endif
		return -1;
	}

	if( ( sockfd = tcp_connect( destip, listen_port ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_password_change_reply()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( confirmation_str );
	return 0;
}

int serverproto_timer_set( char *destip, short desttype, unsigned int hours, unsigned int minutes, unsigned int seconds )
{
	int sockfd;
	unsigned short listen_port;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *hours_str = uint2str( hours );
	char *minutes_str = uint2str( minutes );
	char *seconds_str = uint2str( seconds );

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_TIMER_SET );
	msgptr = proto_str_comb( msgptr, hours_str );
	msgptr = proto_str_comb( msgptr, minutes_str );
	msgptr = proto_str_comb( msgptr, seconds_str );

	if( desttype == OPSR_TEAM )
		listen_port = LISTEN_PORT_TEAM;
	else if( desttype == OPSR_ADMIN )
		listen_port = LISTEN_PORT_ADMIN;
	else if( desttype == OPSR_JUDGE )
		listen_port = LISTEN_PORT_JUDGE;
	else
	{
#if PROTO_DBG > 0
		printf("[serverproto_timer_set()] Wrong destination specified.  Set failed.\n");
#endif
		return -1;
	}

	if( ( sockfd = tcp_connect( destip, listen_port ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_timer_set()] tcp_connect() call failed.\n");
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

int serverproto_contest_start( char *destip, short desttype )
{
	int sockfd;
	unsigned short listen_port;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_CONTEST_START );

	if( desttype == OPSR_TEAM )
		listen_port = LISTEN_PORT_TEAM;
	else if( desttype == OPSR_ADMIN )
		listen_port = LISTEN_PORT_ADMIN;
	else if( desttype == OPSR_JUDGE )
		listen_port = LISTEN_PORT_JUDGE;
	else
	{
#if PROTO_DBG > 0
		printf("[serverproto_contest_start()] Wrong destination specified.  Set failed.\n");
#endif
		return -1;
	}

	if( ( sockfd = tcp_connect( destip, listen_port ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_contest_start()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	return 0;
}

int serverproto_contest_stop( char *destip, short desttype )
{
	int sockfd;
	unsigned short listen_port;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_CONTEST_STOP );

	if( desttype == OPSR_TEAM )
		listen_port = LISTEN_PORT_TEAM;
	else if( desttype == OPSR_ADMIN )
		listen_port = LISTEN_PORT_ADMIN;
	else if( desttype == OPSR_JUDGE )
		listen_port = LISTEN_PORT_JUDGE;
	else
	{
#if PROTO_DBG > 0
		printf("[serverproto_contest_stop()] Wrong destination specified.  Set failed.\n");
#endif
		return -1;
	}

	if( ( sockfd = tcp_connect( destip, listen_port ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_contest_stop()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	return 0;
}

int serverproto_run_reply( char *destip, unsigned int run_id, unsigned int problem_id, wchar_t *result )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *run_id_str = uint2str( run_id );
	char *problem_id_str = uint2str( problem_id );
	char *result_mb = proto_str_presend( result );

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_RUN_REPLY );
	msgptr = proto_str_comb( msgptr, run_id_str );
	msgptr = proto_str_comb( msgptr, problem_id_str );
	msgptr = proto_str_comb( msgptr, result_mb );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_TEAM ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_login_reply()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( run_id_str );
	free( problem_id_str );
	free( result_mb );
	return 0;
}

int serverproto_clar_reply( char *destip, short desttype, unsigned int clar_id, wchar_t *clarmsg, wchar_t *result )
{
	int sockfd;
	unsigned short listen_port;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *clar_id_str = uint2str( clar_id );
	char *clarmsg_mb = proto_str_presend( clarmsg );
	char *result_mb = proto_str_presend( result );

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_CLAR_REPLY );
	msgptr = proto_str_comb( msgptr, clar_id_str );
	msgptr = proto_str_comb( msgptr, clarmsg_mb );
	msgptr = proto_str_comb( msgptr, result_mb );

	if( desttype == OPSR_TEAM )
		listen_port = LISTEN_PORT_TEAM;
	else if( desttype == OPSR_ADMIN )
		listen_port = LISTEN_PORT_ADMIN;
	else if( desttype == OPSR_JUDGE )
		listen_port = LISTEN_PORT_JUDGE;
	else
	{
#if PROTO_DBG > 0
		printf("[serverproto_clar_reply()] Wrong source specified.\n");
#endif
		return -1;
	}

	if( ( sockfd = tcp_connect( destip, listen_port ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_clar_reply()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( clar_id_str );
	free( clarmsg_mb );
	free( result_mb );
	return 0;
}

int serverproto_problem_change_add( char *destip, unsigned int problem_id, wchar_t *problem_name )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *pch_opid_str = uint2str( PCH_OPID_ADD );
	char *problem_id_str = uint2str( problem_id );
	char *problem_name_mb = proto_str_presend( problem_name );

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_P_CHANGE );
	msgptr = proto_str_comb( msgptr, pch_opid_str );
	msgptr = proto_str_comb( msgptr, problem_id_str );
	msgptr = proto_str_comb( msgptr, problem_name_mb );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_TEAM ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_problem_change_add()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( pch_opid_str );
	free( problem_id_str );
	free( problem_name_mb );
	return 0;
}

int serverproto_problem_change_del( char *destip, unsigned int problem_id )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *pch_opid_str = uint2str( PCH_OPID_DEL );
	char *problem_id_str = uint2str( problem_id );

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_P_CHANGE );
	msgptr = proto_str_comb( msgptr, pch_opid_str );
	msgptr = proto_str_comb( msgptr, problem_id_str );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_TEAM ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_problem_change_del()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( pch_opid_str );
	free( problem_id_str );
	return 0;
}

int serverproto_problem_change_mod( char *destip, unsigned int problem_id, wchar_t *problem_name )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *pch_opid_str = uint2str( PCH_OPID_MOD );
	char *problem_id_str = uint2str( problem_id );
	char *problem_name_mb = proto_str_presend( problem_name );

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_P_CHANGE );
	msgptr = proto_str_comb( msgptr, pch_opid_str );
	msgptr = proto_str_comb( msgptr, problem_id_str );
	msgptr = proto_str_comb( msgptr, problem_name_mb );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_TEAM ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_problem_change_mod()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( pch_opid_str );
	free( problem_id_str );
	free( problem_name_mb );
	return 0;
}

int serverproto_sb_update( char *destip, short desttype, unsigned int upd_acc_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time )
{
	int sockfd;
	unsigned short listen_port;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *upd_acc_id_str = uint2str( upd_acc_id );
	char *new_account_mb = proto_str_presend( new_account );
	char *new_accept_count_str = uint2str( new_accept_count );
	char *new_time_str = uint2str( new_time );

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_SB_UPDATE );
	msgptr = proto_str_comb( msgptr, upd_acc_id_str );
	msgptr = proto_str_comb( msgptr, new_account_mb );
	msgptr = proto_str_comb( msgptr, new_accept_count_str );
	msgptr = proto_str_comb( msgptr, new_time_str );

	if( desttype == OPSR_TEAM )
		listen_port = LISTEN_PORT_TEAM;
	else if( desttype == OPSR_ADMIN )
		listen_port = LISTEN_PORT_ADMIN;
	else
	{
#if PROTO_DBG > 0
		printf("[serverproto_sb_update()] Wrong destination specified.\n");
#endif
		return -1;
	}

	if( ( sockfd = tcp_connect( destip, listen_port ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_sb_update()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( upd_acc_id_str );
	free( new_account_mb );
	free( new_accept_count_str );
	free( new_time_str );
	return 0;
}

int serverproto_sb_remove( char *destip, short desttype, unsigned int rm_account_id )
{
	int sockfd;
	unsigned short listen_port;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *rm_account_id_str = uint2str( rm_account_id );
	
	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_SB_REMOVE );
	msgptr = proto_str_comb( msgptr, rm_account_id_str );
	
	if( desttype == OPSR_TEAM )
		listen_port = LISTEN_PORT_TEAM;
	else if( desttype == OPSR_ADMIN )
		listen_port = LISTEN_PORT_ADMIN;
	else
	{
#if PROTO_DBG > 0
		printf("[serverproto_sb_remove()] Wrong destination specified.\n");
#endif
		return -1;
	}

	if( ( sockfd = tcp_connect( destip, listen_port ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_sb_remove()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );
	
	shutdown_wr_sp( sockfd );
	free( rm_account_id_str );
	return 0;
}

int serverproto_problem_upload( char *destip, wchar_t *path_description )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char syncbuf[BUFLEN];
	char *msgptr = NULL;

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_PUPLOAD );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_TEAM ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_login_reply()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );
	
	/* sync message from receiver: i'm ready */
	recv( sockfd, syncbuf, BUFLEN, 0 );

	/* upload files */
	filesend( destip, OPSR_TEAM, path_description );

	shutdown_wr_sp( sockfd );
	return 0;
}

int serverproto_run_request( char *destip, unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char syncbuf[BUFLEN];
	char *msgptr = NULL;
	char *run_id_str = uint2str( run_id );
	char *problem_id_str = uint2str( problem_id );
	char *coding_language_mb = proto_str_presend( coding_language );

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_RUN_REQUEST );
	msgptr = proto_str_comb( msgptr, run_id_str );
	msgptr = proto_str_comb( msgptr, problem_id_str );
	msgptr = proto_str_comb( msgptr, coding_language_mb );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_JUDGE ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_login_reply()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );
	
	/* sync message from receiver: i'm ready */
	recv( sockfd, syncbuf, BUFLEN, 0 );

	/* upload files */
	filesend( destip, OPSR_JUDGE, path_code );

	shutdown_wr_sp( sockfd );
	free( run_id_str );
	free( problem_id_str );
	free( coding_language_mb );
	return 0;
}

int serverproto_take_result( char *destip, unsigned int run_id, int success )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *run_id_str = uint2str( run_id );
	char *success_str = int2str( success );

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_TAKE_RESULT );
	msgptr = proto_str_comb( msgptr, run_id_str );
	msgptr = proto_str_comb( msgptr, success_str );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_JUDGE ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_take_result()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( run_id_str );
	free( success_str );
	return 0;
}

int serverproto_account_update( char *destip, unsigned int account_id, unsigned int type, wchar_t *account )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *account_id_str = uint2str( account_id );
	char *type_str = uint2str( type );
	char *account_mb = proto_str_presend( account );

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_ACCUPDATE );
	msgptr = proto_str_comb( msgptr, account_id_str );
	msgptr = proto_str_comb( msgptr, type_str );
	msgptr = proto_str_comb( msgptr, account_mb );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_ADMIN ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_account_update()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( account_id_str );
	free( type_str );
	free( account_mb );
	return 0;
}

int serverproto_account_remove( char *destip, unsigned int account_id )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *account_id_str = uint2str( account_id );

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_ACCREMOVE );
	msgptr = proto_str_comb( msgptr, account_id_str );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_ADMIN ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_account_remove()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( account_id_str );
	return 0;
}

int serverproto_problem_update( char *destip, short desttype, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer )
{
	int sockfd;
	unsigned short listen_port;
	char sendbuf[BUFLEN];
	char syncbuf[BUFLEN];
	char *msgptr = NULL;
	char *problem_id_str = uint2str( problem_id );
	char *problem_name_mb = proto_str_presend( problem_name );
	char *time_limit_str = uint2str( time_limit );

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_PUPDATE );
	msgptr = proto_str_comb( msgptr, problem_id_str );
	msgptr = proto_str_comb( msgptr, problem_name_mb );
	msgptr = proto_str_comb( msgptr, time_limit_str );

	if( desttype == OPSR_ADMIN )
		listen_port = LISTEN_PORT_ADMIN;
	else if( desttype == OPSR_JUDGE )
		listen_port = LISTEN_PORT_JUDGE;
	else
	{
#if PROTO_DBG > 0
		printf("[serverproto_problem_update()] Wrong destination specified.\n");
#endif
		return -1;
	}

	if( ( sockfd = tcp_connect( destip, listen_port ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_problem_update()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );
	
	/* sync message from receiver: i'm ready */
	recv( sockfd, syncbuf, BUFLEN, 0 );

	/* upload files */
	if( desttype == OPSR_ADMIN )
	{
		filesend( destip, OPSR_ADMIN, path_description );
		filesend( destip, OPSR_ADMIN, path_input );
		filesend( destip, OPSR_ADMIN, path_answer );
	}
	else if( desttype == OPSR_JUDGE )
	{
		filesend( destip, OPSR_JUDGE, path_description );
		filesend( destip, OPSR_JUDGE, path_input );
		filesend( destip, OPSR_JUDGE, path_answer );
	}

	shutdown_wr_sp( sockfd );
	free( problem_id_str );
	free( problem_name_mb );
	free( time_limit_str );
	return 0;
}

int serverproto_problem_remove( char *destip, short desttype, unsigned int problem_id )
{
	int sockfd;
	unsigned short listen_port;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *problem_id_str = uint2str( problem_id );

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_PREMOVE );
	msgptr = proto_str_comb( msgptr, problem_id_str );

	if( desttype == OPSR_ADMIN )
		listen_port = LISTEN_PORT_ADMIN;
	else if( desttype == OPSR_JUDGE )
		listen_port = LISTEN_PORT_JUDGE;
	else
	{
#if PROTO_DBG > 0
		printf("[serverproto_problem_remove()] Wrong destination specified.\n");
#endif
		return -1;
	}

	if( ( sockfd = tcp_connect( destip, listen_port ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_problem_remove()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( problem_id_str );
	return 0;
}

int serverproto_clar_request( char *destip, short desttype, unsigned int clar_id, int private_byte, wchar_t *clarmsg )
{
	int sockfd;
	unsigned short listen_port;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *clar_id_str = uint2str( clar_id );
	char *private_byte_str = int2str( private_byte );
	char *clarmsg_mb = proto_str_presend( clarmsg );

	msgptr = proto_srid_comb( sendbuf, OPSR_SERVER, OPID_CLAR_REQUEST );
	msgptr = proto_str_comb( msgptr, clar_id_str );
	msgptr = proto_str_comb( msgptr, private_byte_str );
	msgptr = proto_str_comb( msgptr, clarmsg_mb );

	if( desttype == OPSR_ADMIN )
		listen_port = LISTEN_PORT_ADMIN;
	else if( desttype == OPSR_JUDGE )
		listen_port = LISTEN_PORT_JUDGE;
	else
	{
#if PROTO_DBG > 0
		printf("[serverproto_clar_request()] Wrong destination specified.\n");
#endif
		return -1;
	}

	if( ( sockfd = tcp_connect( destip, listen_port ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[serverproto_clar_request()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( clar_id_str );
	free( private_byte_str );
	free( clarmsg_mb );
	return 0;
}
