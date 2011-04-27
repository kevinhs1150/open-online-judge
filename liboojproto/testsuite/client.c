#include "../protointernal.h"

int main( void )
{
	int sockfd;
	char sendbuf[1024] = "Test message.";
	
#ifdef _WIN32
	WSADATA wsaData;
	
	if( WSAStartup( MAKEWORD(2,2), &wsaData ) != 0 )
	{
		printf("[APP] WSAStartup() failed.\n");
		return -1;
	}
#endif

	if( ( sockfd = tcp_connect("127.0.0.1", 27015) ) < 0 )
	{
		printf("[APP] tcp_connect() failed.\n");
		return -1;
	}

	printf("[APP] Connection established.  Sending message....\n");
	printf("[APP] Message: %s\n", sendbuf);
	send( sockfd, sendbuf, 1024, 0 );
	printf("[APP] Message sent.\n");

	closesocket( sockfd );
	WSACleanup();
	printf("[APP] Connection closed.\nPress enter to terminate the program.... ");
	getchar();
	return 0;
}
