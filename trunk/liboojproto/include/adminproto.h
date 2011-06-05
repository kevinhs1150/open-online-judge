/* admin.h
 * OOJ communication implementation, adminstration client. */
#ifndef ADMINPROTO_H_
#define ADMINPROTO_H_

#include "protointernal.h"

#include <stdio.h>

/*----------------------------- callback functions -----------------------------*/

/* Callback for login confirmation. (from server)
 * Pass the confirmation code and account id to administrator client.
 * Administrator client should allow or deny user login according to confirmation code. */
void adminproto_cbreg_login_confirm( void (*cbfunc)( int confirm_code, unsigned int account_id ) );

/* Callback for logout confirmation. (from server)
 * Pass the confirmation code to administrator client.
 * Administrator client can ignore this message, since it is currently not meaningful. */
void adminproto_cbreg_logout_confirm( void (*cbfunc)( int confirm_code ) );

/* Callback for password change confirmation. (from server)
 * Pass the confirmation code to client.
 * Client should pop out a notification about the change result. */
void adminproto_cbreg_password_change_confirm( void (*cbfunc)( int confirm_code ) );

/* Callback for timer set. (from server)
 * Pass time components(hr, min, sec) to server program.
 * Client should update its timer at once. */
void adminproto_cbreg_timer_set( void (*cbfunc)( unsigned int hours, unsigned int minutes, unsigned int seconds ) );

/* Callback for contest start/stop. (from server)
 * Client should update its contest state at once. */
void adminproto_cbreg_contest_start( void (*cbfunc)( void ) );
void adminproto_cbreg_contest_stop( void (*cbfunc)( void ) );

/* Callback for clarification request. (from server)
 * Pass "clarification id", "whether this is a private message" and "clarification message" to administrator client.
 * Client should notify the administrator.  Administrator should then reply the clarification. */
void adminproto_cbreg_clar_request( void (*cbfunc)( unsigned int clar_id, unsigned int account_id, wchar_t *account, int private_byte, wchar_t *clarmsg ) );

/* Callback for clarification reply. (from server)
 * Pass the clarification id and result string to team client.
 * Team client should notify the user about the result. */
void adminproto_cbreg_clar_reply( void (*cbfunc)( unsigned int clar_id, wchar_t *clarmsg, wchar_t *result_string ) );

/* Callback for account information update. (from server)
 * Pass "account id", "account type" and "account name(possibly updated one)" to administrator client.
 * Administrator client should update its own list of accounts. */
void adminproto_cbreg_account_update( void (*cbfunc)( unsigned int account_id, unsigned int type, wchar_t *account ) );
/* This one is for account deletion. */
void adminproto_cbreg_account_remove( void (*cbfunc)( unsigned int account_id ) );

/* Callback for problem information update. (from server)
 * Pass "problem id" to administrator client.
 * The three string should be filled respectively with path where "problem description", "input data" and "correct answer" will be stored.
 * Administrator client should store the files and update its own list of problems. */
void adminproto_cbreg_problem_update( void (*cbfunc)( unsigned int problem_id, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer ) );
void adminproto_cbreg_problem_update_dlfin( void (*cbfunc)( unsigned int problem_id, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer ) );
/* This one is for problem deletion. */
void adminproto_cbreg_problem_remove( void (*cbfunc)( unsigned int problem_id ) );

/* Callback for scoreboard update. (from server)
 * Pass the "account id whose record is going to be updated", the new account name, the new accept count and the new time.
 * Administrator client should notify the user about the result. */
void adminproto_cbreg_sb_update( void (*cbfunc)( unsigned int updated_account_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time ) );


/*----------------------------- tool functions -----------------------------*/

/* This function should be called in initial routine.  It listens for data from clients.
 * Note that all callbacks should be registered before invoking listen(). */
int adminproto_listen( char *localaddr );
int adminproto_stop_listen( void );
/* This function checks whether listen socket is currently active or not. */
int adminproto_active( void );

/* login
 * send account and password to server */
int adminproto_login( char *destip, wchar_t *account, char *password );

/* logout
 * send the id of the logging out account to server */
int adminproto_logout( char *destip, unsigned int account_id );

/* password change */
int adminproto_password_change( char *destip, unsigned int account_id, char *new_password );

/* account management */
int adminproto_account_add( char *destip, unsigned int type, wchar_t *account, char *password );
int adminproto_account_del( char *destip, unsigned int account_id );
int adminproto_account_mod( char *destip, unsigned int account_id, wchar_t *new_account, char *new_password );
int adminproto_account_sync( char *destip );

/* problem management */
int adminproto_problem_add( char *destip, unsigned int problem_id, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer );
int adminproto_problem_del( char *destip, unsigned int problem_id );
int adminproto_problem_mod( char *destip, unsigned int problem_id, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer );
int adminproto_problem_sync( char *destip );

/* clarification reply */
int adminproto_clar_result( char *destip, unsigned int clar_id, int private_byte, wchar_t *result_string );

/* timer set function */
int adminproto_timer_set( char *destip, unsigned int hours, unsigned int minutes, unsigned int seconds );

/* contest start/stop function */
int adminproto_contest_start( char *destip );
int adminproto_contest_stop( char *destip );

/* scoreboard sync function */
int adminproto_sb_sync( char *destip );

/* timer sync request */
int adminproto_timer_sync( char *destip );

/* contest state sync request */
int adminproto_contest_state_sync( char *destip );

/* clarification sync request */
int adminproto_clar_sync( char *destip );

#endif
