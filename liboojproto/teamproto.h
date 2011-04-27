/* team.h
 * OOJ communication implementation, team client. */
#ifndef TEAMPROTO_H_
#define TEAMPROTO_H_

#include "protointernal.h"

#include <stdio.h>

/* callback registration functions */

/* Callback for run result reply. (from server)
 * Pass the run id and result string to team client.
 * Team client should notify the user about the result. */
void teamproto_cbreg_run_reply( void (*cbfunc)( unsigned int run_id, wchar_t *result_string ) );

/* Callback for clarification reply. (from server)
 * Pass the clarification id and result string to team client.
 * Team client should notify the user about the result. */
void teamproto_cbreg_clar_reply( void (*cbfunc)( unsigned int clar_id, wchar_t *result_string ) );

/* Callback for scoreboard update. (from server)
 * Pass the "account id whose account is going to be updated", the new account name, the new accept count and the new time.
 * Team client should update its scoreboard immediately. */
void teamproto_cbreg_sb_update( void (*cbfunc)( unsigned int updated_account_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time ) );

/* Callback for problem upload request. (from server, due to a previous problem download request)
 * Team client should fill the string with the path where problem description will be stored. */
void teamproto_cbreg_pu_request( void (*cbfunc)( wchar_t **path_description ) );

/* listen thread
 * This function should be called in initial routine.  It listens for data from server. */
int teamproto_listen( char *localaddr );
int teamproto_stop_listen( void );

/* login
 * send account and password to server */
int teamproto_login( char *destip, wchar_t *account, char *password );

/* logout
 * send the id of the logging out account to server */
int teamproto_logout( char *destip, unsigned int account_id );

/* submit */
int teamproto_submission( char *destip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code );

/* clarification request */
int teamproto_clar( char *destip, unsigned int account_id, int private_byte, wchar_t *clarmsg );

/* problem download */
int teamproto_problem_download( char *destip, unsigned int account_id, unsigned int problem_id );

#endif
