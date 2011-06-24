/* judge.h
 * OOJ communication implementation, judge client. */
#ifndef JUDGEPROTO_H_
#define JUDGEPROTO_H_

#include "protointernal.h"

#include <stdio.h>

/*----------------------------- callback functions -----------------------------*/

/* Callback for login confirmation. (from server)
 * Pass the confirmation code and account id to judge client.
 * Judge client should allow or deny user login according to confirmation code. */
void judgeproto_cbreg_login_confirm( void (*cbfun)( int confirm_code, unsigned int account_id ) );

/* Callback for logout confirmation. (from server)
 * Pass the confirmation code to judge client.
 * Judge client can ignore this message, since it is currently noot meaningful.*/
void judgeproto_cbreg_logout_confirm( void (*cbfunc)( int confirm_code ) );

/* Callback for password change confirmation. (from server)
 * Pass the confirmation code to client.
 * Client should pop out a notification about the change result. */
void judgeproto_cbreg_password_change_confirm( void (*cbfunc)( int confirm_code ) );

/* Callback for timer set. (from server)
 * Pass time components(hr, min, sec) to server program.
 * Client should update its timer at once.*/
void judgeproto_cbreg_timer_set( void (*cbfunc)( unsigned int hours, unsigned int minutes, unsigned int seconds ) );

/* Callback for contest start/stop. (from server)
 * Client should update its contest state at once.*/
void judgeproto_cbreg_contest_start( void (*cbfunc)( void ) );
void judgeproto_cbreg_contest_stop( void (*cbfunc)( void ) );

/* Callback for run request. (from server)
 * Pass the run id, problem id and its coding language to judge client.
 * The path_code should be filled with the path to store source code.
 * Source code will then be downloaded to that location. */
void judgeproto_cbreg_run_request( void (*cbfunc)( unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code ) );
void judgeproto_cbreg_run_request_dlfin( void (*cbfunc)( unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code ) );

/* Callback for problem update. (from server)
 * Pass the problem id to judge client.
 * The rest three strings should be filled with path to store "problem description", "input data" and "correct answer" respectively. */
void judgeproto_cbreg_problem_update( void (*cbfunc)( unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer ) );
void judgeproto_cbreg_problem_update_dlfin( void (*cbfunc)( unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer ) );
/* This one is for problem deletion. */
void judgeproto_cbreg_problem_remove( void (*cbfunc)( unsigned int problem_id ) );

/* Callback for take result. (from server)
 * Pass the run id and success indicator to judge client.
 * If judge client received TAKE_FAIL in success indicator, it must remove that run_id from its run list. */
void judgeproto_cbreg_take_result( void (*cbfunc)( unsigned int run_id, int success ) );

/* Callback for clarification request. (from server)
 * Pass "clarification id", "whether this is a private message" and "clarification message" to administrator client.
 * Client should notify the judge.  Judge should then reply the clarification. */
void judgeproto_cbreg_clar_request( void (*cbfunc)( unsigned int clar_id, unsigned int account_id, wchar_t *account, int private_byte, wchar_t *clarmsg ) );

/* Callback for clarification reply. (from server)
 * Pass the clarification id and result string to team client.
 * Team client should notify the user about the result. */
void judgeproto_cbreg_clar_reply( void (*cbfunc)( unsigned int clar_id, wchar_t *clarmsg, wchar_t *result_string ) );


/*----------------------------- tool functions -----------------------------*/

/* This function should be called in initial routine.  It listens for data from clients.
 * Note that all callbacks should be registered before invoking listen(). */
int judgeproto_listen( const char *localaddr );
int judgeproto_stop_listen( void );
/* This function checks whether the listen socket is currently active or not. */
int judgeproto_active( void );

/* login */
int judgeproto_login( const char *destip, const wchar_t *account, const char *password );

/* logout */
int judgeproto_logout( const char *destip, unsigned int account_id );

/* password change */
int judgeproto_password_change( const char *destip, unsigned int account_id, const char *old_password, const char *new_password );

/* run result */
int judgeproto_judge_result( const char *destip, unsigned int run_id, const wchar_t *result_string );

/* run update request */
int judgeproto_run_sync( const char *destip );

/* run take */
int judgeproto_take_run( const char *destip, unsigned int run_id );

/* clarification reply */
int judgeproto_clar_result( const char *destip, unsigned int clar_id, int private_byte, const wchar_t *result_string );

/* timer sync request */
int judgeproto_timer_sync( const char *destip );

/* contest state sync request */
int judgeproto_contest_state_sync( const char *destip );

/* clarification sync request */
int judgeproto_clar_sync( const char *destip );

/* problem sync request */
int judgeproto_problem_sync( const char *destip );

#endif
