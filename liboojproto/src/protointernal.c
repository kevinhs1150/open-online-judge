#include "protointernal.h"

/* variables used globally over liboojproto */
void (*cb_login_confirm)( int confirm_code, unsigned int account_id ) = NULL;
void (*cb_logout_confirm)( int confirm_code ) = NULL;
void (*cb_password_change_confirm)( int confirm_code ) = NULL;
void (*cb_timer_set)( unsigned int hours, unsigned int minutes, unsigned int seconds ) = NULL;
void (*cb_contest_start)( void ) = NULL;
void (*cb_contest_stop)( void ) = NULL;

/* callback common to admin and judge */
void (*cb_clar_request)( unsigned int clar_id, unsigned int account_id, wchar_t *account, int private_byte, wchar_t *clarmsg ) = NULL;
void (*cb_problem_update)( unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer ) = NULL;
void (*cb_problem_update_dlfin)( unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer ) = NULL;
void (*cb_problem_remove)( unsigned int problem_id ) = NULL;

/* callback common to admin and team */
void (*cb_sb_update)( unsigned int updated_account_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time ) = NULL;
void (*cb_sb_remove)( unsigned int rm_account_id ) = NULL;

/* callback common to all clients */
void (*cb_clar_reply)( unsigned int clar_id, wchar_t *clarmsg, wchar_t *result_string ) = NULL;

/* external download management mutex from protointernal_listen.c */
extern pthread_mutex_t proto_dlmgr_mutex;

/* utility function implementation */
#if _WIN32
int win32_sock_init( void )
{
	WSADATA wsaData;

	if( WSAStartup( MAKEWORD(2,2), &wsaData ) != 0 )
	{
#if PROTO_DBG > 0
		printf("[win32_sock_init()] WSAStartup() call failed.\n");
#endif
		return -1;
	}

	return 0;
}

int win32_sock_cleanup( void )
{
	if( WSACleanup() != 0 )
	{
#if PROTO_DBG > 0
		printf("[win32_sock_cleanup()] WSACleanup() call failed.\n");
#endif
		return -1;
	}

	return 0;
}
#endif

int tcp_listen( const char *bind_address, unsigned short bind_port )
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

/*	int reuseaddr = 1;
	int reuseaddr_len = sizeof(reuseaddr);
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, reuseaddr_len); */

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

int tcp_connect( const char *conn_address, unsigned short conn_port )
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
	socklen_t len = sizeof( struct sockaddr_in );
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

/* external vsftp listen socket from protointernal_listen.c */
extern int proto_vsftp_listenfd;

int filesend( const char *destip, short desttype, const wchar_t *filepath )
{
	int sockfd;
	unsigned short listen_port;
	char recvbuf[BUFLEN];
	FILE *fptr;
	char sendbuf[BUFLEN];
	char s_buf[BUFLEN];
	int filesize;
	size_t sendbyte = 0, a_sendbyte = 0;

#if PROTO_DBG > 1
	wprintf(L"Path: %s\n", filepath );
#endif

	fptr = fopen_sp( filepath, L"rb" );

	/* collect file spec */
	fseek( fptr, 0, SEEK_END );
	filesize = ftell( fptr );
	fseek( fptr, 0, SEEK_SET );

	if( desttype == OPSR_ADMIN )
		listen_port = LISTEN_PORT_VSFTP_ADMIN;
	else if( desttype == OPSR_JUDGE )
		listen_port = LISTEN_PORT_VSFTP_JUDGE;
	else if( desttype == OPSR_TEAM )
		listen_port = LISTEN_PORT_VSFTP_TEAM;
	else if( desttype == OPSR_SERVER )
		listen_port = LISTEN_PORT_VSFTP_SERVER;
	else
	{
#if PROTO_DBG > 0
		printf("[filesend()] Destination type error.\n");
#endif
		return -1;
	}

	/* connect to receiver */
	if( ( sockfd = tcp_connect( destip, listen_port ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[filesend()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	/* sync: wait for receiver to standby */
	recv( sockfd, recvbuf, BUFLEN, 0 );

	/* send file spec */
	sprintf( sendbuf, "%d", filesize );
	send_sp( sockfd, sendbuf, BUFLEN );

#if PROTO_DBG > 1
	printf("Filesize = %d\n", filesize );
#endif

	/* enter file transfer loop */
	while( a_sendbyte != filesize )
	{
		/* sync: send next packet size */
		sendbyte = fread( sendbuf, 1, BUFLEN, fptr );
		sprintf( s_buf, "%d", sendbyte );
		send_sp( sockfd, s_buf, BUFLEN );

		/* first sync: are you ready? */
		recv( sockfd, recvbuf, BUFLEN, 0 );

		/* read 1KB(BUFLEN=1024bytes) block and send */
		sendbyte = send_sp( sockfd, sendbuf, sendbyte );
		a_sendbyte += sendbyte;

#if PROTO_DBG > 1
		printf("%d, %d      \r", a_sendbyte, sendbyte);
#endif

		/* second sync: are you ready? */
		recv( sockfd, recvbuf, BUFLEN, 0 );
	}
#if PROTO_DBG > 1
	printf("\n");
#endif

	shutdown_wr_sp( sockfd );
	fclose( fptr );

	return 0;
}

int filerecv( const wchar_t *filepath )
{
	int sockfd;
	char recvbuf[BUFLEN];
	size_t recvsize;
	FILE *fptr;
	char sendbuf[BUFLEN];
	int filesize;
	int recvbyte = 0, a_recvbyte = 0;

#if PROTO_DBG > 1
	wprintf(L"Path: %s\n", filepath );
#endif

	fptr = fopen_sp( filepath, L"wb" );

	if( ( sockfd = accept( proto_vsftp_listenfd, NULL, NULL ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[filerecv()] accpet() call failed.\n");
#endif
		return -1;
	}

	/* sync: standby ready, setup (wwwww */
	sprintf( sendbuf, "VSFTPREADY" );
	send_sp( sockfd, sendbuf, BUFLEN );

	/* receive file spec */
	recvsize = recv( sockfd, recvbuf, BUFLEN, 0 );
	filesize = atoi( recvbuf );

#if PROTO_DBG > 1
	printf("Filesize = %d\n", filesize );
#endif

	/* enter file transfer loop */
	while( a_recvbyte != filesize )
	{
		/* sync: standby ready */
		recv( sockfd, recvbuf, BUFLEN, 0 );
		sscanf( recvbuf, "%d", &recvbyte );

		/* first sync: i'm ready */
		send( sockfd, sendbuf, BUFLEN, 0 );

		/* recieve block and write */
		recvbyte = recv( sockfd, recvbuf, recvbyte, 0 );
		fwrite( recvbuf, 1, recvbyte, fptr );
		a_recvbyte += recvbyte;

#if PROTO_DBG >1
		printf("%d, %d        \r", a_recvbyte, recvbyte );
#endif

		/* second sync: i'm ready */
		send( sockfd, sendbuf, BUFLEN, 0 );
	}
#if PROTO_DBG > 1
	printf("\n");
#endif

	shutdown_wr_sp( sockfd );
	fclose( fptr );

	return 0;
}

FILE *fopen_sp( const wchar_t *filename, const wchar_t *mode )
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
	size_t r_recv;
	char buftmp[BUFLEN];
	int count;

	r_recv = recv( sockfd, buftmp, BUFLEN, 0 );

	if( buffer != NULL )
	{
		*buffer = (char *)realloc( *buffer, r_recv * sizeof( char ) );
		for( count = 0; count < r_recv; count++ )
			(*buffer)[count] = buftmp[count];
	}

	return r_recv;
}

/*
size_t recv_sp( int sockfd, char **buffer )
{
	size_t a_recv = 0; //received bytes cumulated
	size_t pa_recv = 0; //received bytes cumulated, previous state
	size_t r_recv; //received bytes each time
	char buftmp[BUFLEN];
	int count;

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
}*/

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
	*SRptr = (unsigned char)arr[0];
	*IDptr = (unsigned char)arr[1];
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

char *proto_str_comb( char *arr, const char *msg )
{
	strcpy( arr, msg );
	return arr + strlen( msg ) + 1;
}

#include <math.h>

char *int2str( int input )
{
	char *out;
	int input_cpy = abs( input );
	int input_digit;
	int size;

	/* to prevent floating point precision trouble */
	if( input_cpy == 0 )
		input_cpy = 1;

	/* take log10 to count the digits */
	input_digit = (int)ceil( log10( input_cpy ) );
	size = ( input_digit + 2 ) * sizeof( char );

	/* space for negative sign */
	if( input < 0 )
		size = size + sizeof( char );

	out = (char *)malloc( size );
	sprintf( out, "%d", input );
	return out;
}

char *uint2str( unsigned int input )
{
	char *out;
	int input_cpy = abs( input );
	int input_digit;
	int size;

	/* to prevent floating point precision trouble */
	if( input_cpy == 0 )
		input_cpy = 1;

	input_digit = (int)ceil( log10( input_cpy ) );
	size = ( input_digit + 2 ) * sizeof( char );

	out = (char *)malloc( size );
	sprintf( out, "%d", input );
	return out;
}

int between( int test_value, int low_value, int high_value )
{
	if( low_value <= test_value && test_value < high_value )
		return 1;
	else
		return 0;
}

char *proto_str_presend( const wchar_t *src )
{
	char *str;
	str = u16_to_u8( src );
	return str;
}

wchar_t *proto_str_postrecv( const char *src )
{
	wchar_t *str;
	str = u8_to_u16( src );
	return str;
}

char *u16_to_u8( const wchar_t *src )
{
	char *u8str = NULL;
	char *u8str_ptr;
	char *src_ptr;
	size_t insize = ( wcslen(src) + 1 ) * sizeof( wchar_t );
	size_t outsize = 0, total_outsize = 0;
	int offset;
	size_t iconv_rc;
	iconv_t iconv_cd;

	/* set pointer */
	u8str_ptr = (char *)u8str;
	src_ptr = (char *)src;

	iconv_cd = iconv_open("UTF-8", "UTF-16LE");

	/* Because we can't estimate output string size, we instead increment 50 units each time
	 * until iconv() report string converted. */
	while( 1 )
	{
		offset = u8str_ptr - u8str;

		outsize = 50 * sizeof( char );
		total_outsize = total_outsize + outsize;
		u8str = realloc( u8str, total_outsize );
		u8str_ptr = u8str + offset;

		iconv_rc = iconv( iconv_cd, (const char **)&src_ptr, &insize, &u8str_ptr, &outsize );

		if( iconv_rc == 0 || ( iconv_rc == -1 && errno != E2BIG ) )
			break;
	}

	iconv_close( iconv_cd );

#if PROTO_DBG > 0
	if( iconv_rc == -1 )
	{
		switch( errno )
		{
			case E2BIG:
				printf("[u16_to_u8()] There is not sufficient room at *outbuf.\n");
				break;
			case EILSEQ:
				printf("[u16_to_u8()] An invalid multibyte sequence has been encountered in the input.\n");
				break;
			case EINVAL:
				printf("[u16_to_u8()] An incomplete multibyte sequence has been encountered in the input.\n");
				break;
			default:
				printf("[u16_to_u8()] Strange error happened.\n");
				break;
		}
	}
#endif

	return u8str;
}

wchar_t *u8_to_u16( const char *src )
{
	wchar_t *u16str = NULL;
	char *u16str_ptr_head;
	char *u16str_ptr;
	char *src_ptr;
	size_t insize = ( strlen(src) + 1 ) * sizeof( char );
	size_t outsize = 0, total_outsize = 0;
	int offset;
	size_t iconv_rc;
	iconv_t iconv_cd;

	/* allocate UTF-16 string */
	u16str = malloc( outsize );

	/* set pointer */
	u16str_ptr = (char *)u16str;
	u16str_ptr_head = (char *)u16str;
	src_ptr = (char *)src;

	iconv_cd = iconv_open("UTF-16LE", "UTF-8");

	/* Because we can't estimate output string size, we instead increment 50 units each time
	 * until iconv() report string converted. */
	while( 1 )
	{
		offset = u16str_ptr - u16str_ptr_head;

		outsize = 50 * sizeof( wchar_t );
		total_outsize = total_outsize + outsize;
		u16str = realloc( u16str, total_outsize );
		u16str_ptr_head = (char *)u16str;
		u16str_ptr = u16str_ptr_head + offset;

		iconv_rc = iconv( iconv_cd, (const char **)&src_ptr, &insize, &u16str_ptr, &outsize );

		if( iconv_rc == 0 || ( iconv_rc == -1 && errno != E2BIG ) )
			break;
	}

	iconv_close( iconv_cd );

#if PROTO_DBG > 0
	if( iconv_rc == -1 )
	{
		switch( errno )
		{
			case E2BIG:
				printf("[u8_to_u16()] There is not sufficient room at *outbuf.\n");
				break;
			case EILSEQ:
				printf("[u8_to_u16()] An invalid multibyte sequence has been encountered in the input.\n");
				break;
			case EINVAL:
				printf("[u8_to_u16()] An incomplete multibyte sequence has been encountered in the input.\n");
				break;
			default:
				printf("[u8_to_u16()] Strange error happened.\n");
				break;
		}
	}
#endif

	return u16str;
}

int proto_commonreq( int RQSR, int RQID, char *msgptr )
{
	/* part 1. login/logout confirmation */
	if( between( RQID, 0, 10 ) && RQSR == OPSR_SERVER )
	{
		if( RQID == OPID_LOGIN_REPLY )
		{
			char *confirm_code_str = proto_str_split( msgptr, &msgptr );
			char *account_id_str = proto_str_split( msgptr, NULL );

			int confirm_code = atoi( confirm_code_str );
			unsigned int account_id = atoi( account_id_str );

			(*cb_login_confirm)( confirm_code, account_id );

			free( confirm_code_str );
			free( account_id_str );
		}
		else if( RQID == OPID_LOGOUT_REPLY )
		{
			char *confirm_code_str = proto_str_split( msgptr, NULL );

			int confirm_code = atoi( confirm_code_str );

			(*cb_logout_confirm)( confirm_code );

			free( confirm_code_str );
		}
		else if( RQID == OPID_PASSWD_REPLY )
		{
			char *confirm_code_str = proto_str_split( msgptr, NULL );

			int confirm_code = atoi( confirm_code_str );

			(*cb_password_change_confirm)( confirm_code );

			free( confirm_code_str );
		}

		return 1;
	}
	/* part 2. time control & start and stop */
	else if( between( RQID, 200, 210 ) && RQSR == OPSR_SERVER )
	{
		if( RQID == OPID_TIMER_SET )
		{
			char *hours_str = proto_str_split( msgptr, &msgptr );
			char *minutes_str = proto_str_split( msgptr, &msgptr );
			char *seconds_str = proto_str_split( msgptr, NULL );

			unsigned int hours = atoi( hours_str );
			unsigned int minutes = atoi( minutes_str );
			unsigned int seconds = atoi( seconds_str );

			(*cb_timer_set)( hours, minutes, seconds );

			free( hours_str );
			free( minutes_str );
			free( seconds_str );
		}
		else if( RQID == OPID_CONTEST_START )
		{
			(*cb_contest_start)();
		}
		else if( RQID == OPID_CONTEST_STOP )
		{
			(*cb_contest_stop)();
		}

		return 1;
	}

	return 0;
}

void proto_clar_request( char *msgptr )
{
	char *clar_id_str = proto_str_split( msgptr, &msgptr );
	char *account_id_str = proto_str_split( msgptr, &msgptr );
	char *account_mb = proto_str_split( msgptr, &msgptr );
	char *private_byte_str = proto_str_split( msgptr, &msgptr );
	char *clarmsg_mb = proto_str_split( msgptr, NULL );

	unsigned int clar_id = atoi( clar_id_str );
	unsigned int account_id = atoi( account_id_str );
	wchar_t *account = proto_str_postrecv( account_mb );
	int private_byte = atoi( private_byte_str );
	wchar_t *clarmsg = proto_str_postrecv( clarmsg_mb );

	(*cb_clar_request)( clar_id, account_id, account, private_byte, clarmsg );

	free( clar_id_str );
	free( account_id_str );
	free( account_mb );
	free( account );
	free( private_byte_str );
	free( clarmsg_mb );
	free( clarmsg );
}

void proto_clar_reply( char *msgptr )
{
	char *clar_id_str = proto_str_split( msgptr, &msgptr );
	char *clarmsg_mb = proto_str_split( msgptr, &msgptr );
	char *result_string_mb = proto_str_split( msgptr, NULL );

	unsigned int clar_id = atoi( clar_id_str );
	wchar_t *clarmsg = proto_str_postrecv( clarmsg_mb );
	wchar_t *result_string = proto_str_postrecv( result_string_mb );

	(*cb_clar_reply)( clar_id, clarmsg, result_string );

	free( clar_id_str );
	free( result_string_mb );
	free( result_string );
}

void proto_sb_update( char *msgptr )
{
	char *updated_account_id_str = proto_str_split( msgptr, &msgptr );
	char *new_account_mb = proto_str_split( msgptr, &msgptr );
	char *new_accept_count_str = proto_str_split( msgptr, &msgptr );
	char *new_time_str = proto_str_split( msgptr, NULL );

	unsigned int updated_account_id = atoi( updated_account_id_str );
	wchar_t *new_account = proto_str_postrecv( new_account_mb );
	unsigned int new_accept_count = atoi( new_accept_count_str );
	unsigned int new_time = atoi( new_time_str );

	(*cb_sb_update)( updated_account_id, new_account, new_accept_count, new_time );

	free( updated_account_id_str );
	free( new_account_mb );
	free( new_accept_count_str );
	free( new_time_str );
	free( new_account );
}

void proto_sb_remove( char *msgptr )
{
	char *rm_account_id_str = proto_str_split( msgptr, NULL );

	unsigned int rm_account_id = atoi( rm_account_id_str );

	(*cb_sb_remove)( rm_account_id );

	free( rm_account_id_str );
}

void proto_problem_update( int sockfd, char *msgptr )
{
	char *problem_id_str = proto_str_split( msgptr, &msgptr );
	char *problem_name_mb = proto_str_split( msgptr, &msgptr );
	char *time_limit_str = proto_str_split( msgptr, NULL );
	wchar_t *path_description = NULL, *path_input = NULL, *path_answer = NULL;

	unsigned int problem_id = atoi( problem_id_str );
	wchar_t *problem_name = proto_str_postrecv( problem_name_mb );
	unsigned int time_limit = atoi( time_limit_str );

	/* mutex lock protection -- prevent concurrent downloading causing race condition */
	pthread_mutex_lock( &proto_dlmgr_mutex );
	send_sp( sockfd, "FSREADY", BUFLEN );

	(*cb_problem_update)( problem_id, problem_name, time_limit, &path_description, &path_input, &path_answer );

	/* download file */
	filerecv( path_description );
	filerecv( path_input );
	filerecv( path_answer );

	(*cb_problem_update_dlfin)( problem_id, problem_name, time_limit, path_description, path_input, path_answer );

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

void proto_problem_remove( char *msgptr )
{
	char *problem_id_str = proto_str_split( msgptr ,NULL );

	unsigned int problem_id = atoi( problem_id_str );

	(*cb_problem_remove)( problem_id );

	free( problem_id_str );
}

/* common function implementation */
int proto_login( const char *destip, short src, const wchar_t *account, const char *password )
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

int proto_logout( const char *destip, short src, unsigned int account_id )
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

int proto_password_change( const char *destip, short src, unsigned int account_id, const char *old_password, const char *new_password )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *account_id_str = uint2str( account_id );

	msgptr = proto_srid_comb( sendbuf, src, OPID_PASSWD_CHANGE );
	msgptr = proto_str_comb( msgptr, account_id_str );
	msgptr = proto_str_comb( msgptr, old_password );
	msgptr = proto_str_comb( msgptr, new_password );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[proto_password_change()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send( sockfd, sendbuf, BUFLEN, 0 );

	shutdown_wr_sp( sockfd );
	free( account_id_str );
	return 0;
}

int proto_clar_result( const char *destip, short srctype, unsigned int clar_id, int private_byte, const wchar_t *result_string )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;
	char *clar_id_str = uint2str( clar_id );
	char *private_byte_str = int2str( private_byte );
	char *result_string_mb = proto_str_presend( result_string );

	msgptr = proto_srid_comb( sendbuf, srctype, OPID_CLAR_RESULT );
	msgptr = proto_str_comb( msgptr, clar_id_str );
	msgptr = proto_str_comb( msgptr, private_byte_str );
	msgptr = proto_str_comb( msgptr, result_string_mb );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[proto_clar_result()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	free( clar_id_str );
	free( private_byte_str );
	free( result_string_mb );
	return 0;
}

int proto_sb_sync( const char *destip, short srctype )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;

	msgptr = proto_srid_comb( sendbuf, srctype, OPID_SB_SYNC );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[proto_sb_sync()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	return 0;
}

int proto_timer_sync( const char *destip, short srctype )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;

	msgptr = proto_srid_comb( sendbuf, srctype, OPID_TIMER_SYNC );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[proto_timer_sync()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	return 0;
}

int proto_contest_state_sync( const char *destip, short srctype )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;

	msgptr = proto_srid_comb( sendbuf, srctype, OPID_CONTEST_STATE_SYNC );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[proto_contest_sync()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	return 0;
}

int proto_clar_sync( const char *destip, short srctype )
{
	int sockfd;
	char sendbuf[BUFLEN];
	char *msgptr = NULL;

	msgptr = proto_srid_comb( sendbuf, srctype, OPID_CLAR_SYNC );

	if( ( sockfd = tcp_connect( destip, LISTEN_PORT_SERVER ) ) < 0 )
	{
#if PROTO_DBG > 0
		printf("[proto_clar_sync()] tcp_connect() call failed.\n");
#endif
		return -1;
	}

	send_sp( sockfd, sendbuf, BUFLEN );

	shutdown_wr_sp( sockfd );
	return 0;
}