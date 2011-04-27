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

int filesend( wchar_t *filepath, char *conn_address, unsigned short conn_port )
{
	int sockfd;
	FILE *fptr;

#ifdef _WIN32
	if( win32_sock_init() < 0 )
	{
	#if PROTO_DBG > 0
		printf("[filesend()] win32_sock_init() call failed.\n");
	#endif
		return -1;
	}
#endif

	if( ( sockfd = tcp_connect( conn_address, conn_port ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[filesend()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	if( ( fptr = fopen_sp( filepath, L"rb" ) ) == NULL )
	{
#if PROTO_DBG > 0
		printf("[filesend()] fopen_sp() call failed.\n");
#endif
		close( sockfd );
		return -1;
	}



	return 0;
}

int filerecv( wchar_t *filepath, char *bind_address, unsigned short bind_port )
{
	int listenfd, sockfd;
	FILE *fptr;

#ifdef _WIN32
	if( win32_sock_init() < 0 )
	{
	#if PROTO_DBG > 0
		printf("[filerecv()] win32_sock_init() call failed.\n");
	#endif
		return -1;
	}
#endif

	if( ( listenfd = tcp_listen( bind_address, bind_port ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[filerecv()] tcp_listen() call failed.\n");
#endif
		return -1;
	}

	if( ( fptr = fopen_sp( filepath, L"wb" ) ) == NULL )
	{
#if PROTO_DBG < 0
		printf("[filerecv()] fopen_sp call failed.\n");
#endif
		close( listenfd );
		return -1;
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

	close( sockfd );
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

	close( sockfd );
	free( account_id_str );
	return 0;
}

