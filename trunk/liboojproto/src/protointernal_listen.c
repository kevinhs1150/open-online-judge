/* protointernal_listen.c
 * The common listen utility functions used on all ends.
 * function prototype defined in protointernal.h */

#include "protointernal.h"

/* execution data */
int proto_listenfd;
int proto_vsftp_listenfd;
int proto_stop = 1;

/* listen thread */
pthread_t proto_listen_tid;
void *proto_listen_thread( void *args );

/* request handling callback, function pointer
 * TODO: Implement an array to store all thread information. */
pthread_t proto_reqhand_tid;
void *(*proto_reqhand_thread)( void *args );

/* sync variables between listen thread and request handle thread
 * condition variable is used here */
pthread_mutex_t proto_sockfd_pass_mutex;
pthread_cond_t proto_sockfd_pass_cv;

/* mutex variables for download management
 * this should be used to prevent concurrent download, which may cause race condition */
pthread_mutex_t proto_dlmgr_mutex;

/* listen socket bind information */
char proto_bind_address[16];
unsigned short proto_bind_port;

int proto_listen( char *localaddr, unsigned short listen_bind_port, unsigned short vsftp_bind_port, void *(*cbthread)( void *) )
{
	/* initialize mutex and condition variable */
	pthread_mutex_init( &proto_sockfd_pass_mutex, NULL );
	pthread_cond_init( &proto_sockfd_pass_cv, NULL );
	pthread_mutex_init( &proto_dlmgr_mutex, NULL );

	/* startup socket */
#ifdef _WIN32
	if( win32_sock_init() < 0 )
	{
	#if PROTO_DBG > 0
		printf("[proto_listen()] win32_sock_init() call failed.\n");
	#endif
		return -1;
	}
#endif

	if( ( proto_listenfd = tcp_listen( localaddr, listen_bind_port ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[proto_listen()] tcp_listen() for listen socket failed.\n");
#endif
		return -1;
	}
	
	if( ( proto_vsftp_listenfd = tcp_listen( localaddr, vsftp_bind_port ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[proto_listen()] tcp_listen() for VSFTP failed.\n");
#endif
		return -1;
	}

	/* store connection ifnormation for later use (see proto_stop_listen() function) */
	strcpy( proto_bind_address, localaddr );
	proto_bind_port = listen_bind_port;

	/* prepare threading */
	proto_stop = 0;
	proto_reqhand_thread = cbthread;

	if( pthread_create( &proto_listen_tid, NULL, proto_listen_thread, NULL ) != 0 )
	{
#if PROTO_DBG > 0
		printf("[proto_listen()] pthread_create() call failed.\n");
#endif
		return -1;
	}

	return 0;
}

int proto_active( void )
{
	return !proto_stop;
}

int proto_stop_listen( void )
{
	int sockfd;
	char connaddr[16];

	/* raise listening socket close flag */
	proto_stop = 1;
	
	/* connect to localhost if binded to all interfaces */
	if( strcmp( proto_bind_address, "0.0.0.0" ) == 0 )
		strcpy( connaddr, "127.0.0.1" );
	else
		strcpy( connaddr, proto_bind_address );

	/* local connection to unblock accept() */
	if( ( sockfd = tcp_connect( connaddr, proto_bind_port ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[proto_stop_listen()] tcp_connect() call failed.  Unblocking failed.\n");
#endif
		return -1;
	}

	close( sockfd );
	close( proto_vsftp_listenfd );

	/* wait for thread termination before clean up */
	pthread_join( proto_listen_tid, NULL );
	pthread_mutex_destroy( &proto_sockfd_pass_mutex );
	pthread_cond_destroy( &proto_sockfd_pass_cv );
	pthread_mutex_destroy( &proto_dlmgr_mutex );

#ifdef _WIN32
	if( win32_sock_cleanup() < 0 )
	{
	#if PROTO_DBG > 0
		printf("[proto_stop_listen()] win32_sock_cleanup() call failed.\n");
	#endif
		return -1;
	}

	return 0;
#endif
}

void *proto_listen_thread( void *args )
{
	int sockfd;

	while( !proto_stop )
	{
		if( ( sockfd = accept( proto_listenfd, NULL, NULL ) ) < 0 )
		{
#if PROTO_DBG > 0
			printf("[proto_listen_thread()] accpet() call failed.\n");
#endif
			pthread_exit( NULL );
		}

		/* check point */
		if( proto_stop )
			break;

		/* create request handling thread and sync sockfd
		 * mutex is locked in advance to prevent the thread lock the mutex earlier, which may cause an early signal */
		pthread_mutex_lock( &proto_sockfd_pass_mutex );
		pthread_create( &proto_reqhand_tid, NULL, *proto_reqhand_thread, (void *)&sockfd );
		pthread_cond_wait( &proto_sockfd_pass_cv, &proto_sockfd_pass_mutex );
		pthread_mutex_unlock( &proto_sockfd_pass_mutex );
	}

	close( sockfd );
	close( proto_listenfd );

	pthread_exit( NULL );
}

