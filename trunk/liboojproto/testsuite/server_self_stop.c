#include "../protointernal.h"

#include <windows.h>

int go = 1;
pthread_t tid;
void *stop_thread( void *arg );

int main( void )
{
	int listenfd, sockfd;
	char recvbuf[1024];

#ifdef _WIN32
	if( win32_sock_init() != 0 )
	{
		printf("[APP] win32_sock_init() failed.\n");
		return -1;
	}
#endif

	if( ( listenfd = tcp_listen("127.0.0.1", 27015) ) < 0 )
	{
		printf("[APP] tcp_listen() failed.\n");
		return -1;
	}

	printf("[APP] Listen socket is ready....\n");
	pthread_create( &tid, NULL, stop_thread, NULL );

	while( 1 )
	{
		if( ( sockfd = accept( listenfd, NULL, NULL ) ) < 0 )
		{
			printf("[APP] accept() failed.\n");
			return -1;
		}

		/* check point */
		if( !go )   break;

		recv( sockfd, recvbuf, 1024, 0 );
		printf("[APP] Message received: %s\n", recvbuf );
		close( sockfd );
	}

	close( sockfd );
	close( listenfd );
	printf("[APP] Program terminated, press enter to exit....");
	getchar();

#ifdef _WIN32
	if( win32_sock_cleanup() != 0 )
	{
		printf("[APP] win32_sock_cleanup() failed.\n");
		return -1;
	}
#endif

	return 0;
}

/* create another thread to wait for termination signal */
void *stop_thread( void *arg )
{
	int sockfd;

	printf("[APP] stop_thread ready, press enter to stop listening.\n");
	getchar();

	go = 0;

	/* connect to socket for accept() to break */
	if( ( sockfd = tcp_connect("127.0.0.1", 27015) ) < 0 )
	{
		printf("[APP] tcp_connect() failed.  Unable to stop program.\n");
		pthread_exit( NULL );
	}

	printf("[APP] Connected to local socket.  Disconnect.\n");
	close( sockfd );

	pthread_exit( NULL );
}