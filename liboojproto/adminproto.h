/* admin.h
 * OOJ communication implementation, adminstration client. */
#ifndef ADMINPROTO_H_
#define ADMINPROTO_H_

#include "protointernal.h"

#include <stdio.h>

/* callback registration functions */

/* Callback for login confirmation. (from server)
 * Pass the confirmation code and account id to administrator client.
 * Administrator client should allow or deny user login according to confirmation code. */
void adminproto_cbreg_login_confirm( void (*login_confirm)( int confirm_code, unsigned int account_id ) );

/* Callback for logout confirmation. (from server)
 * Pass the confirmation code to administrator client.
 * Administrator client can ignore this message, since it is currently not meaningful. */
void adminproto_cbreg_logout_confirm( void (*logout_confirm)( int confirm_cod ) );

/* Callback for clarification request. (from server)
 * Pass "clarification id", "whether this is a private message" and "clarification message" to administrator client.
 * Administrator client should notify the administrator.  Administrator should then reply the clarification. */
void adminproto_cbreg_clar_request( void (*clar_request)( unsigned int clar_id, int private, wchar_t *clarmsg ) );

/* Callback for account information update. (from server)
 * Pass "account id", "account type" and "account name(possibly updated one)" to administrator client.
 * Administrator client should update its own list of accounts. */
void adminproto_cbreg_account_info( void (*account_info)( unsigned int account_id, unsigned int type, wchar_t *account ) );

/* Callback for problem information update. (from server)
 * Pass "problem id" to administrator client.
 * The three string should be filled respectively with path where "problem description", "input data" and "correct answer" will be stored.
 * Administrator client should store the files and update its own list of problems. */
void adminproto_cbreg_problem_info( void (*problem_info)( unsigned int problem_id, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer ) );

/* listen thread
 * This function should be called in initial routine.  It listens for data from server. */
int adminproto_listen( char *localaddr );
int adminproto_stop_listen( void );

/* login
 * send account and password to server */
int adminproto_login( char *destip, wchar_t *account, char *password );

/* logout
 * send the id of the logging out account to server */
int adminproto_logout( char *destip, unsigned int account_id );

/* account management */
int adminproto_account_add( char *destip, unsigned int type, wchar_t *account, char *password );
int adminproto_account_del( char *destip, unsigned int account_id );
int adminproto_account_mod( char *destip, unsigned int account_id, wchar_t *new_account, char *new_password );
int adminproto_account_update( char *destip );

/* problem management */
int adminproto_problem_add( char *destip, unsigned int problem_id, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer );
int adminproto_problem_del( char *destip, unsigned int problem_id );
int adminproto_problem_mod( char *destip, unsigned int problem_id, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer );
int adminproto_problem_update( char *destip );

/* clarification reply */
int adminproto_clar_result( char *destip, unsigned int clar_id, int private_byte, wchar_t *result_string );

/* global broadcast */
//int adminproto_broadcast();


/* property setting -- not implemented yet */

#endif
