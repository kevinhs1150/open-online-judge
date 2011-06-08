/* adminproto.c
 * Source code file for administration client protocol implementation. */

#include "adminproto.h"

/* callback registration check function, return 1(true) if all functions has been registered */
static int adminproto_cbcheck( void );

/* callback functions */
void (*cb_account_update)( unsigned int account_id, unsigned int type, wchar_t *account )    = NULL;
void (*cb_account_remove)( unsigned int account_id ) = NULL;

/* callback functions extern-ed from protointernal.c */
extern void (*cb_login_confirm)( int confirm_code, unsigned int account_id );
extern void (*cb_logout_confirm)( int confirm_code );
extern void (*cb_password_change_confirm)( int confirm_code );
extern void (*cb_timer_set)( unsigned int hours, unsigned int minutes, unsigned int seconds );
extern void (*cb_contest_start)( void );
extern void (*cb_contest_stop)( void );
extern void (*cb_clar_request)( unsigned int clar_id, unsigned int account_id, wchar_t *account, int private_byte, wchar_t *clarmsg );
extern void (*cb_clar_reply)( unsigned int clar_id, wchar_t *clarmsg, wchar_t *result_string );
extern void (*cb_sb_update)( unsigned int updated_account_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time );
extern void (*cb_sb_remove)( unsigned int rm_account_id );
extern void (*cb_problem_update)( unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer );
extern void (*cb_problem_update_dlfin)( unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer );
extern void (*cb_problem_remove)( unsigned int problem_id );

/* callback registration functions */
void adminproto_cbreg_login_confirm( void (*cbfunc)( int, unsigned int ) )                    { cb_login_confirm = cbfunc; }
void adminproto_cbreg_logout_confirm( void (*cbfunc)( int ) )                                 { cb_logout_confirm = cbfunc; }
void adminproto_cbreg_password_change_confirm( void (*cbfunc)( int ) ) { cb_password_change_confirm = cbfunc; }
void adminproto_cbreg_timer_set( void (*cbfunc)( unsigned int, unsigned int, unsigned int ) ) { cb_timer_set = cbfunc; }
void adminproto_cbreg_contest_start( void (*cbfunc)( void ) ) { cb_contest_start = cbfunc; }
void adminproto_cbreg_contest_stop( void (*cbfunc)( void ) )  { cb_contest_stop = cbfunc; }
void adminproto_cbreg_clar_request( void (*cbfunc)( unsigned int, unsigned int, wchar_t*, int, wchar_t* ) ) { cb_clar_request = cbfunc; }
void adminproto_cbreg_clar_reply( void (*cbfunc)( unsigned int, wchar_t*, wchar_t* ) )  {cb_clar_reply = cbfunc;}
void adminproto_cbreg_account_update( void (*cbfunc)( unsigned int, unsigned int, wchar_t* ) )  { cb_account_update = cbfunc; }
void adminproto_cbreg_account_remove( void (*cbfunc)( unsigned int ) ) { cb_account_remove = cbfunc; }
void adminproto_cbreg_problem_update( void (*cbfunc)( unsigned int, wchar_t*, unsigned int, wchar_t**, wchar_t**, wchar_t** ) ) { cb_problem_update = cbfunc; }
void adminproto_cbreg_problem_update_dlfin( void (*cbfunc)( unsigned int, wchar_t*, unsigned int, wchar_t*, wchar_t*, wchar_t* ) ) { cb_problem_update_dlfin = cbfunc; }
void adminproto_cbreg_problem_remove( void (*cbfunc)( unsigned int ) ) { cb_problem_remove = cbfunc; }
void adminproto_cbreg_sb_update( void (*cbfunc)( unsigned int, wchar_t*, unsigned int, unsigned int ) )  { cb_sb_update = cbfunc; }
void adminproto_cbreg_sb_remove( void (*cbfunc)( unsigned int ) ) { cb_sb_remove = cbfunc; }

/* thread function */
void *adminproto_reqhand_thread( void *args );

/* external sync variable (from proto_commonfunction.c) */
extern pthread_mutex_t proto_sockfd_pass_mutex;
extern pthread_cond_t proto_sockfd_pass_cv;

/* callback registration check function */
static int adminproto_cbcheck( void )
{
	if( cb_login_confirm == NULL || cb_logout_confirm == NULL || cb_password_change_confirm == NULL ||
		cb_timer_set == NULL || cb_contest_start == NULL || cb_contest_stop == NULL || cb_clar_request == NULL ||
		cb_clar_reply == NULL || cb_account_update == NULL || cb_account_remove == NULL || cb_problem_update == NULL ||
		cb_problem_update_dlfin == NULL || cb_problem_remove == NULL || cb_sb_update == NULL || cb_sb_remove == NULL )
		return 0;
	else
		return 1;
}

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
		if( RQID == OPID_CLAR_REQUEST )
		{
			proto_clar_request( msgptr );
		}
		else if( RQID == OPID_CLAR_REPLY )
		{
			proto_clar_reply( msgptr );
		}
		else if( RQID == OPID_ACCUPDATE )
		{
			char *account_id_str = proto_str_split( msgptr, &msgptr );
			char *type_str = proto_str_split( msgptr, &msgptr );
			char *account_mb = proto_str_split( msgptr, NULL );

			unsigned int account_id = atoi( account_id_str );
			unsigned int type = atoi( type_str );
			wchar_t *account = proto_str_postrecv( account_mb );

			(*cb_account_update)( account_id, type, account );

			free( account_id_str );
			free( type_str );
			free( account_mb );
			free( account );
		}
		else if( RQID == OPID_ACCREMOVE )
		{
			char *account_id_str = proto_str_split( msgptr, NULL );

			unsigned int account_id = atoi( account_id_str );

			(*cb_account_remove)( account_id );

			free( account_id_str );
		}
		else if( RQID == OPID_PUPDATE )
		{
			proto_problem_update( sockfd, src_ipaddr, msgptr );
		}
		else if( RQID == OPID_PREMOVE )
		{
			proto_problem_remove( msgptr );
		}
		else if( RQID == OPID_SB_UPDATE )
		{
			proto_sb_update( msgptr );
		}
		else if( RQID == OPID_SB_REMOVE )
		{
			proto_sb_remove( msgptr );
		}
		else
		{
#if PROTO_DBG > 0
		printf("[adminproto_reqhand_thread()] Inavlid SRID bytes.\n");
#endif
		}
	}

	free( src_ipaddr );
	free( recvbuf );
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

int adminproto_password_change( char *destip, unsigned int account_id, char *old_password, char *new_password )
{
	return proto_password_change( destip, OPSR_ADMIN, account_id, old_password, new_password );
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

int adminproto_account_sync( char *destip )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *acc_opid_str = uint2str( ACC_OPID_SYNC );

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

int adminproto_problem_add( char *destip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *p_opid_str = uint2str( P_OPID_ADD );
	char *problem_id_str = uint2str( problem_id );
	char *problem_name_mb = proto_str_presend( problem_name );
	char *time_limit_str = uint2str( time_limit );

	msgptr = proto_srid_comb( sendbuf, OPSR_ADMIN, OPID_P_MANAGE );
	msgptr = proto_str_comb( msgptr, p_opid_str );
	msgptr = proto_str_comb( msgptr, problem_id_str );
	msgptr = proto_str_comb( msgptr, problem_name_mb );
	msgptr = proto_str_comb( msgptr, time_limit_str );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[adminproto_problem_add()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	/* upload files */
	filesend( destip, path_description );
	filesend( destip, path_input );
	filesend( destip, path_answer );

	shutdown_wr_sp( sockfd );
	free( p_opid_str );
	free( problem_id_str );
	free( problem_name_mb );
	free( time_limit_str );
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

int adminproto_problem_mod( char *destip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *p_opid_str = uint2str( P_OPID_MOD );
	char *problem_id_str = uint2str( problem_id );
	char *problem_name_mb = proto_str_presend( problem_name );
	char *time_limit_str = uint2str( time_limit );

	msgptr = proto_srid_comb( sendbuf, OPSR_ADMIN, OPID_P_MANAGE );
	msgptr = proto_str_comb( msgptr, p_opid_str );
	msgptr = proto_str_comb( msgptr, problem_id_str );
	msgptr = proto_str_comb( msgptr, problem_name_mb );
	msgptr = proto_str_comb( msgptr, time_limit_str );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[adminproto_problem_mod()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	/* upload files */
	filesend( destip, path_description );
	filesend( destip, path_input );
	filesend( destip, path_answer );

	shutdown_wr_sp( sockfd );
	free( p_opid_str );
	free( problem_id_str );
	free( problem_name_mb );
	free( time_limit_str );
	return 0;
}

int adminproto_problem_sync( char *destip )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *p_opid_str = uint2str( P_OPID_SYNC );

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
	return proto_clar_result( destip, OPSR_ADMIN, clar_id, private_byte, result_string );
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

int adminproto_sb_sync( char *destip )
{
	return proto_sb_sync( destip, OPSR_ADMIN );
}

int adminproto_timer_sync( char *destip )
{
	return proto_timer_sync( destip, OPSR_ADMIN );
}

int adminproto_contest_state_sync( char *destip )
{
	return proto_contest_state_sync( destip, OPSR_ADMIN );
}

int adminproto_clar_sync( char *destip )
{
	return proto_clar_sync( destip, OPSR_ADMIN );
}

/* not implemented yet */
int adminproto_broadcast()
{
}
