/* team.h
 * OOJ communication implementation, team client. */
#ifndef TEAMPROTO_H_
#define TEAMPROTO_H_

#include "protointernal.h"

#include <stdio.h>

/*----------------------------- callback functions -----------------------------*/

/* Callback for login confirmation. (from server)
 * Pass the confirmation code and account id to team client.
 * Team client should allow or deny user login according to confirmation code. */
void teamproto_cbreg_login_confirm( void (*cbfun)( int confirm_code, unsigned int account_id ) );

/* Callback for logout confirmation. (from server)
 * Pass the confirmation code to team client.
 * Team client can ignore this message, since it is currently not meaningful.*/
void teamproto_cbreg_logout_confirm( void (*cbfunc)( int confirm_code ) );

/* Callback for password change confirmation. (from server)
 * Pass the confirmation code to client.
 * Client should pop out a notification about the change result. */
void teamproto_cbreg_password_change_confirm( void (*cbfunc)( int confirm_code ) );

/* Callback for timer set. (from server)
 * Pass time components(hr, min, sec) to server program.
 * Client should update its timer at once. */
void teamproto_cbreg_timer_set( void (*cbfunc)( unsigned int hours, unsigned int minutes, unsigned int seconds ) );

/* Callback for contest start/stop. (from server)
 * Client should update its contest state at once. */
void teamproto_cbreg_contest_start( void (*cbfunc)( void ) );
void teamproto_cbreg_contest_stop( void (*cbfunc)( void ) );

/* Callback for run result reply. (from server)
 * Pass the run id and result string to team client.
 * Team client should notify the user about the result. */
void teamproto_cbreg_run_reply( void (*cbfunc)( unsigned int run_id, unsigned int problem_id, wchar_t *result_string ) );

/* Callback for clarification reply. (from server)
 * Pass the clarification id, clarification message and result string to team client.
 * Team client should notify the user about the result. */
void teamproto_cbreg_clar_reply( void (*cbfunc)( unsigned int clar_id, wchar_t *clarmsg, wchar_t *result_string ) );

/* Callback for scoreboard update. (from server)
 * Pass the "account id whose account is going to be updated", the new account name, the new accept count and the new time.
 * Team client should update its scoreboard immediately. */
void teamproto_cbreg_sb_update( void (*cbfunc)( unsigned int updated_account_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time ) );

/* Callback for problem upload request. (from server, due to a previous problem download request)
 * Team client should fill the string with the path where problem description will be stored. */
void teamproto_cbreg_pu_request( void (*cbfunc)( wchar_t **path_description ) );
void teamproto_cbreg_pu_request_dlfin( void (*cbfunc)( wchar_t *path_description ) );

/* Callback for problem change notification. (from server, due to administrator changed some problem)
 * Team client should update its problem listing and, possibly pop up a window to nofity the user about the change. */
void teamproto_cbreg_problem_add( void (*cbfunc)( unsigned int problem_id ) );
void teamproto_cbreg_problem_del( void (*cbfunc)( unsigned int problem_id ) );
void teamproto_cbreg_problem_mod( void (*cbfunc)( unsigned int problem_id ) );


/*----------------------------- tool functions -----------------------------*/

/* This function should be called in initial routine.  It listens for data from clients.
 * Note that all callbacks should be registered before invoking listen(). */
int teamproto_listen( char *localaddr );
int teamproto_stop_listen( void );
/* This function checks whether listen socket is currently active or not. */
int teamproto_active( void );

/* login
 * send account and password to server */
int teamproto_login( char *destip, wchar_t *account, char *password );

/* logout
 * send the id of the logging out account to server */
int teamproto_logout( char *destip, unsigned int account_id );

/* password change */
int teamproto_password_change( char *destip, unsigned int account_id, char *old_password, char *new_password );

/* submit */
int teamproto_submission( char *destip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code );

/* clarification request */
int teamproto_clar( char *destip, unsigned int account_id, int private_byte, wchar_t *clarmsg );

/* problem download */
int teamproto_problem_download( char *destip, unsigned int account_id, unsigned int problem_id );

/* scoreboard sync request */
int teamproto_sb_sync( char *destip );

/* runs sync request */
int teamproto_run_sync( char *destip, unsigned int account_id );

/* timer sync request */
int teamproto_timer_sync( char *destip );

/* contest state sync request */
int teamproto_contest_state_sync( char *destip );

#endif
