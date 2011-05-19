#include "protointernal.h"

/* variables used globally over liboojproto */
void (*cb_login_confirm)( int confirm_code, unsigned int account_id ) = NULL;
void (*cb_logout_confirm)( int confirm_code ) = NULL;

/* utility function implementation */
#if _WIN32
int win32_sock_init( void )
{
	WSADATA wsaData;

	if( WSAStartup( MAKEWORD(2,2), &wsaData ) != 0 )
	{
		printf("[win32_sock_init()] WSAStartup() call failed.\n");
		return -1;
	}

	return 0;
}

int win32_sock_cleanup( void )
{
	if( WSACleanup() != 0 )
	{
		printf("[win32_sock_cleanup()] WSACleanup() call failed.\n");
		return -1;
	}

	return 0;
}
#endif

int tcp_listen( char *bind_address, unsigned short bind_port )
{
	int listenfd;
	struct sockaddr_in servaddr;

	if( ( listenfd = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[tcp_listen()] socket() call failed.\n");
#endif
		return -1;
	}

	bzero( &servaddr, sizeof( servaddr ) );
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr( bind_address );
	servaddr.sin_port        = htons( bind_port );

	if( bind( listenfd, (struct sockaddr *)&servaddr, sizeof( servaddr ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[tcp_listen()] bind() call failed.\n");
#endif
		return -1;
	}

	if( listen( listenfd, SOMAXCONN ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[tcp_listen()] listen() call failed.\n");
#endif
		return -1;
	}

	return listenfd;
}

int tcp_connect( char *conn_address, unsigned short conn_port )
{
	int sockfd;
	struct sockaddr_in servaddr;

	if( ( sockfd = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[tcp_connect()] socket() call failed.\n");
#endif
		return -1;
	}

	bzero( &servaddr, sizeof( servaddr ) );
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons( conn_port );
	servaddr.sin_addr.s_addr = inet_addr( conn_address );
/*#ifdef _WIN32
	servaddr.sin_addr.s_addr = inet_addr( conn_address );
#elif __linux
	inet_pton( AF_INET, conn_address, &servaddr.sin_addr );
#endif*/

	if( ( connect( sockfd, (struct sockaddr *)&servaddr, sizeof( servaddr ) ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[tcp_connect()] connect() call failed.\n");
#endif
		return -1;
	}

	return sockfd;
}

char *tcp_getaddr( int sockfd )
{
	struct sockaddr_in addr;
	unsigned int len;
	char *addr_str = malloc( 16 * sizeof( char ) );

	if( getpeername( sockfd, (struct sockaddr *)&addr, &len ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[tcp_getaddr()] getpeername() call failed.\n");
#endif
		return NULL;
	}

	strcpy( addr_str, inet_ntoa( addr.sin_addr ) );

	return addr_str;
}

int filesend( int sockfd, wchar_t *filepath )
{
	char *recvbuf;
	FILE *fptr;
	char sendbuf[BUFLEN];
	int filesize;

	fptr = fopen_sp( filepath, L"rb" );

	/* collect file spec */
	fseek( fptr, 0, SEEK_END );
	filesize = ftell( fptr );
	fseek( fptr, 0, SEEK_SET );

	/* sync: wait for receiver to standby */
	recv_sp( sockfd, NULL );

	/* send file spec */
	sprintf( sendbuf, "%d", filesize );
	send_sp( sockfd, sendbuf, BUFLEN );

	/* enter file transfer loop */
	while( !feof( fptr ) )
	{
		/* sync: wait for receiver to standby */
		recv_sp( sockfd, NULL );

		/* read 1KB(BUFLEN=1024bytes) block and send */
		fread( sendbuf, BUFLEN, 1, fptr );
		send_sp( sockfd, sendbuf, BUFLEN );
	}

	return 0;
}

int filerecv( int sockfd, wchar_t *filepath )
{
	char *recvbuf;
	size_t recvsize;
	FILE *fptr;
	char sendbuf[BUFLEN];
	int filesize;
	int a_recvbyte = 0, recvbyte;

	fptr = fopen_sp( filepath, L"wb" );

	/* sync: standby ready, setup (wwwww */
	sprintf( sendbuf, "VSFTPREADY" );
	send_sp( sockfd, sendbuf, BUFLEN );

	/* receive file spec */
	recvsize = recv_sp( sockfd, &recvbuf );
	filesize = atoi( recvbuf );

	/* enter file transfer loop */
	while( a_recvbyte != filesize )
	{
		/* sync: standby ready */
		send_sp( sockfd, sendbuf, BUFLEN );

		/* recieve block and write */
		recvbyte = recv_sp( sockfd, &recvbuf );
		fwrite( recvbuf, BUFLEN, 1, fptr );
		free( recvbuf );
		a_recvbyte = a_recvbyte + recvbyte;
	}

	return 0;
}

FILE *fopen_sp( wchar_t *filename, wchar_t *mode )
{
#ifdef _WIN32
	return _wfopen( filename, mode );
#elif __linux
	FILE *fptr;
	/* the presend function converts WCS to MBS */
	char *filename_mb = proto_str_presend( filename );
	char *mode_mb = proto_str_presend( mode );
	fptr = fopen( filename_mb, mode_mb );
	free( filename_mb );
	free( mode_mb );
	return fptr;
#endif
}

size_t send_sp( int sockfd, char *buffer, size_t length )
{
	return send( sockfd, buffer, length, 0 );
}

size_t recv_sp( int sockfd, char **buffer )
{
	size_t a_recv = 0; /* received bytes cumulated */
	size_t pa_recv = 0; /* received bytes cumulated, previous state */
	size_t r_recv; /* received bytes each time */
	char buftmp[BUFLEN];
	int count;

	/* receive until socket closed */
	while( ( r_recv = recv( sockfd, buftmp, BUFLEN, 0 ) ) > 0 )
	{
		pa_recv = a_recv;
		a_recv = a_recv + r_recv;

		if( buffer != NULL )
		{
			*buffer = (char *)realloc( *buffer, a_recv * sizeof( char ) );

			for( count = 0; count < r_recv; count++ )
				(*buffer)[pa_recv+count] = buftmp[count];
		}
	}

	if( r_recv < 0 )
		return r_recv;

	return a_recv;
}

int shutdown_wr_sp( int sockfd )
{
#ifdef _WIN32
	return shutdown( sockfd, SD_SEND );
#elif __linux
	return shutdown( sockfd, SHUT_WR );
#endif
}

char *proto_srid_split( char *arr, short *SRptr, short *IDptr )
{
	*SRptr = arr[0];
	*IDptr = arr[1];

	return arr + 2;
}

/* TODO: Check if this function is UTF-8 compliant. */
char *proto_str_split( char *arr, char **next_msg )
{
	char *msg = (char *)malloc( ( strlen(arr) + 1 ) * sizeof( char ) );
	strcpy( msg, arr );

	if( next_msg != NULL )
		*next_msg = arr + strlen(arr) + 1;

	return msg;
}

char *proto_srid_comb( char *arr, short SR, short ID )
{
	arr[0] = SR;
	arr[1] = ID;

	return arr + 2;
}

char *proto_str_comb( char *arr, char *msg )
{
	strcpy( arr, msg );
	return arr + strlen( msg ) + 2;
}

#include <math.h>

char *int2str( int input )
{
	char *out;
	/* take log10 to count the digits */
	int size = ceil( log10( input ) ) + 1;

	/* space for negative sign */
	if( input < 0 )
		size++;

	out = (char *)malloc( size );
	sprintf( out, "%d", input );
	return out;
}

char *uint2str( unsigned int input )
{
	char *out = (char *)malloc( ceil( log10( input ) ) + 1 );
	sprintf( out, "%d", input );
	return out;
}

char *proto_str_presend( const wchar_t *src )
{
	int mbsize;
	char *str;

	mbsize = wcstombs( NULL, src, 0 ) + 1;
	str = malloc( mbsize * sizeof( char ) );
	wcstombs( str, src, mbsize );

	return str;
}

wchar_t *proto_str_postrecv( const char *src )
{
	int wcsize;
	wchar_t *str;

	wcsize = mbstowcs( NULL, src, 0 ) + 1;
	str = malloc( wcsize * sizeof( wchar_t ) );
	mbstowcs( str, src, wcsize );

	return str;
}

/* common function implementation */
int proto_login( char *destip, short src, wchar_t *account, char *password )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *account_mb = proto_str_presend( account );

	msgptr = proto_srid_comb( sendbuf, src, OPID_LOGIN_REQUEST );
	msgptr = proto_str_comb( msgptr, account_mb );
	msgptr = proto_str_comb( msgptr, password );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[proto_login()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send( sockfd, sendbuf, BUFLEN, 0 );

	shutdown_wr_sp( sockfd );
	free( account_mb );

	return 0;
}

int proto_logout( char *destip, short src, unsigned int account_id )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *account_id_str = uint2str( account_id );

	msgptr = proto_srid_comb( sendbuf, src, OPID_LOGOUT_REQUEST );
	msgptr = proto_str_comb( msgptr, account_id_str );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[proto_logout()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send( sockfd, sendbuf, BUFLEN, 0 );

	shutdown_wr_sp( sockfd );
	free( account_id_str );
	return 0;
}

