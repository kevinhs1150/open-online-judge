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
#include <iconv.h>

#define BUFLEN 1024
#define LISTEN_PORT_SERVER 27015
#define LISTEN_PORT_ADMIN 27016
#define LISTEN_PORT_JUDGE 27017
#define LISTEN_PORT_TEAM 27018
#define LISTEN_PORT_VSFTP_SERVER 27020
#define LISTEN_PORT_VSFTP_ADMIN 27021
#define LISTEN_PORT_VSFTP_JUDGE	27022
#define LISTEN_PORT_VSFTP_TEAM	27023

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
int tcp_listen( const char *bind_address, unsigned short bind_port );
int tcp_connect( const char *conn_address, unsigned short conn_port );
/*int tcp_close( int sockfd );
  int tcp_disconnect( int sockfd );*/
/* use this function to get ip address of existing connection */
char *tcp_getaddr( int sockfd );

/* file transfer -- given connected socket
 * note that file name should be Unicode string */
int filesend( const char *destip, short desttype, const wchar_t *filepath );
int filerecv( const wchar_t *filepath );
//int filerecv( char *ipaddr, wchar_t *filepath );
//int filesend( int sockfd, wchar_t *filepath );
//int filerecv( int sockfd, wchar_t *filepath );
/* file open function with cross platform unicode support*/
FILE *fopen_sp( const wchar_t *filename, const wchar_t *mode );
/* send and recv function wrapper
 * remember to free memory after using the received buffer
 * if recv_sp retrieved a NULL pointer to buffer, size will be returned but the message will not be stored */
size_t send_sp( int sockfd, char *buffer, size_t length );
size_t recv_sp( int sockfd, char **buffer );
int shutdown_wr_sp( int sockfd );

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
char *proto_str_comb( char *arr, const char *msg );

/* conversion from integer value into string */
char *int2str( int input );
char *uint2str( unsigned int input );

/* other tool functions */
/* between test, closed low_value, opened high_value */
int between( int test_value, int low_value, int high_value );

/* wcs(wide character string) and mbs(multi-byte character string) conversion
 * presend: wcs -> mbs
 * postreceive: mbs -> wcs */
char *proto_str_presend( const wchar_t *src );
wchar_t *proto_str_postrecv( const char *src );

/* UTF-8 <--> UTF-16 conversion functions */
char *u16_to_u8( const wchar_t *src );
wchar_t *u8_to_u16( const char *src );

/* internal common listen functions
 * function defined in protointernal_listen.c */
int proto_listen( const char *localaddr, unsigned short listen_bind_port, unsigned short vsftp_bind_port, void *(*cbthread)( void *) );
int proto_activated( void );
int proto_stop_listen( void );

/* internal common listen request function -- handle requests common to all clients
 * serverproto should not use this function as its requests are different from other clients
 * return 1 if the request is handled inside, otherwise 0*/
int proto_commonreq( int RQSR, int RQID, char *msgptr );

/* internal common clarification request function -- common to admin and judge clients */
void proto_clar_request( char *msgptr );

/* internal common clarification reply function -- common to all clients */
void proto_clar_reply( char *msgptr );

/* internal common scoreboard update request function -- common to team and admin client */
void proto_sb_update( char *msgptr );
/* this one removes record from scoreboard */
void proto_sb_remove( char *msgptr );

/* internal common problem update function -- common to admin and judge client */
void proto_problem_update( int sockfd, char *msgptr );
/* this one is for problem removal */
void proto_problem_remove( char *msgptr );

/* internal common account management functions */
int proto_login( const char *destip, short src, const wchar_t *account, const char *password );
int proto_logout( const char *destip, short src, unsigned int account_id );
int proto_password_change( const char *destip, short src, unsigned int account_id, const char *old_password, const char *new_password );

/* internal clarification result function common to administrator client and judge client */
int proto_clar_result( const char *destip, short srctype, unsigned int clar_id, int private_byte, const wchar_t *result_string );

/* internal common scoreboard sync function -- common to admin and team client */
int proto_sb_sync( const char *destip, short srctype );

/* internal common timer sync function -- common to all clients */
int proto_timer_sync( const char *destip, short srctype );

/* internal contest state sync function -- common to all clients */
int proto_contest_state_sync( const char *destip, short srctype );

/* internal clarification sync function -- common to admin and judge client */
int proto_clar_sync( const char *destip, short srctype );

#endif
