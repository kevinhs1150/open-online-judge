#include "../protointernal.h"

#include <windows.h>

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

	if( ( sockfd = accept( listenfd, NULL, NULL ) ) < 0 )
	{
		printf("[APP] accept() failed.\n");
		return -1;
	}
	
	close( listenfd );
	
	while( recv( sockfd, recvbuf, 1024, 0 ) != 0 )
	{
		printf("Message received: %s\n", recvbuf );
		Sleep( 1000 );
	}
	
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
