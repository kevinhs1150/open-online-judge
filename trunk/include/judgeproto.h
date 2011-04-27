/* judge.h
 * OOJ communication implementation, judge client. */
#ifndef JUDGEPROTO_H_
#define JUDGEPROTO_H_

#include "protointernal.h"

#include <stdio.h>

/* callback registration functions */

/* Callback for login confirmation. (from server)
 * Pass the confirmation code and account id to judge client.
 * Judge client should allow or deny user login according to confirmation code. */
void judgeproto_cbreg_login_confirm( void (*cbfun)( int confirm_code, unsigned int account_id ) );

/* Callback for logout confirmation. (from server)
 * Pass the confirmation code to judge client.
 * Judge client can ignore this message, since it is currently noot meaningful.*/
void judgeproto_cbreg_logout_confirm( void (*cbfunc)( int confirm_code ) );

/* Callback for run request. (from server)
 * Pass the run id, problem is and its coding language to judge client.
 * The path_code should be filled with the path to store source code.
 * Source code will then be downloaded to that location. */
void judgeproto_cbreg_run_request( void (*cbfunc)( unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code ) );

/* Callback for problem update. (from server)
 * Pass the problem id to judge client.
 * The rest three strings should be filled with path to store "problem description", "input data" and "correct answer" respectively. */
void judgeproto_cbreg_problem_update( void (*cbfunc)( unsigned int problem_id, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer ) );


/* listen thread
 * This function should be called in initial routine.  It listens for data from server. */
int judgeproto_listen( char *localaddr );
int judgeproto_stop_listen( void );

/* login */
int judgeproto_login( char *destip, wchar_t *account, char *password );

/* logout */
int judgeproto_logout( char *destip, unsigned int account_id );

/* run result */
int judgeproto_judge_result( char *destip, unsigned int run_id, wchar_t *result_string );

#endif
