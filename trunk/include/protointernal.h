/* protointernal.h
 * Functions for internal use. */

#ifndef PROTOINTERNAL_H_
#define PROTOINTERNAL_H_

#include "proto_commondefine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <pthread.h>

#define BUFLEN 1024
#define LISTEN_PORT_SERVER 27015
#define LISTEN_PORT_ADMIN 27016
#define LISTEN_PORT_JUDGE 27017
#define LISTEN_PORT_TEAM 27018
#define VSFTP_PORT 27020

#ifdef _WIN32
/* Win32 has no bzero implementation, but has an ZeroMemory which is identical to bzero in usage (implementation not sure). */
#define bzero ZeroMemory
/* This two functions must be called before socket in Windows or it will not work.
 * The init and cleanup should be in pair.  One init must be cleaned up exactly once. */
int win32_sock_init( void );
int win32_sock_cleanup( void );
#endif

/* network connection management
 * use ANSI string to retain simplicity (it isn't necessary to pass pure-number and dots using Unicode) */
int tcp_listen( char *bind_address, unsigned short bind_port );
int tcp_connect( char *conn_address, unsigned short conn_port );
/*int tcp_close( int sockfd );
  int tcp_disconnect( int sockfd );*/
/* use this function to get ip address of existing connection */
char *tcp_getaddr( int sockfd );

/* file transfer
 * note that file name should be Unicode string */
int filesend( wchar_t *filepath, char *conn_address, unsigned short conn_port );
int filerecv( wchar_t *filepath, char *bind_address, unsigned short bind_port );
/* file open function with cross platform unicode support*/
FILE *fopen_sp( wchar_t *filename, wchar_t *mode );

/* split SR,ID byte from packet
 * function returns a pointer which points to the start of message byte */
char *proto_srid_split( char *arr, short *SRptr, short *IDptr );
/* split a message fragment from packet
 * function returns THE MESSAGE
 * the pointer to next message will be stored in next_msg.  if next_msg if NULL, pointer to next message will be discarded */
char *proto_str_split( char *arr, char **next_msg );
/* initialize a buffer with SR,ID byte
 * function returns a pointer which points to the start of message byte */
char *proto_srid_comb( char *arr, short SR, short ID );
/* append a message fragment, with the start position of the message specified
 * function returns pointer to where next message should be appended
 * note that string functions will currently not check array bound, so it will be your task to make sure not to exceed the limitation for now */
char *proto_str_comb( char *arr, char *msg );

/* conversion from integer value into string */
char *int2str( int input );
char *uint2str( unsigned int input );

/* wcs(wide character string) and mbs(multi-byte character string) conversion
 * presend: wcs -> mbs
 * postreceive: mbs -> wcs */
char *proto_str_presend( const wchar_t *src );
wchar_t *proto_str_postrecv( const char *src );

/* internal common listen functions
 * function defined in protointernal_listen.c */
int proto_listen( char *localaddr, unsigned short bind_port, void *(*cbthread)( void *) );
int proto_stop_listen( void );

/* internal common login & logout functions */
int proto_login( char *destip, short src, wchar_t *account, char *password );
int proto_logout( char *destip, short src, unsigned int account_id );

#endif
