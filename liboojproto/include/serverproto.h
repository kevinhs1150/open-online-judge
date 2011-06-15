/* serverproto.h
 * OOJ communication implementation, server. */
#ifndef SERVERPROTO_H_
#define SERVERPROTO_H_

#include "protointernal.h"

#include <stdio.h>

/*----------------------------- callback functions -----------------------------*/

/* Callback for login request. (from all clients)
 * Pass "client type of requester(admin, team, etc.)", "login account", and "login password" to server program.
 * Server should determine the validity of account/password, reply, and mark the account as logged in.
 *   reply function: serverproto_login_reply()
 *   confirmation code defined in proto_commondefine.h */
void serverproto_cbreg_login_request( void (*cbfunc)( char *srcip, short srctype, wchar_t *account, char *password ) );

/* Callback for logout request. (from all clients)
 * Pass "account id" to server program.
 * Server should give the client a reply and mark the account as logged out.
 *   reply function: serverproto_logout_reply()
 *   confirmation code defined in proto_commondefine.h */
void serverproto_cbreg_logout_request( void (*cbfunc)( char *srcip, short srctype, unsigned int account_id ) );

/* Callback for password change request. (from all clients)
 * Pass "account id" and "new password" to server program.
 * Server should store the changed password into database and give the client a reply.
 *   reply function: serverproto_password_change_reply()
 *   confirmation code defined in proto_commondefine.h */
void serverproto_cbreg_password_change( void (*cbfunc)( char *srcip, short srctype, unsigned int account_id, char *old_password, char *new_password ) );

/* Callback for timer sync. (from all clients)
 * Server should sync the timer with the requesting client.
 *   reply function: serverproto_timer_set() */
void serverproto_cbreg_timer_sync( void (*cbfunc)( char *srcip, short srctype ) );

/* Callback for contest state sync. (from all clients)
 * Server should sync the contest state with the requesting client.
 *   reply function: serverproto_contest_start() and serverproto_contest_stop() */
void serverproto_cbreg_contest_state_sync( void (*cbfunc)( char *srcip, short srctype ) );

/* Callback for timer set. (from admin)
 * Pass time components(hr, min, sec) to server program.
 * Server should forward this setting to all clients.
 *   forward function: serverproto_timer_set() */
void serverproto_cbreg_admin_timer_set( void (*cbfunc)( char *srcip, unsigned int hours, unsigned int minutes, unsigned int seconds ) );

/* Callback for contest start/stop. (from admin)
 * Server should forward this notification to all clients.
 *   forward function: serverproto_contest_start() and serverproto_contest_stop() */
void serverproto_cbreg_admin_contest_start( void (*cbfunc)( char *srcip ) );
void serverproto_cbreg_admin_contest_stop( void (*cbfunc)( char *srcip ) );

/* Callback for submission request. (from team)
 * Pass the "requester's team account", "submit problem id", and "coding language" to server program.
 * Server should record those information into db and redirect the submission to judge.  Also note that all submission should be assigned a "run id".
 * The path_code string should be filled with the path where code will be stored.
 *   forward function: serverproto_run_request() */
void serverproto_cbreg_submission_request( void (*cbfunc)( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code ) );
void serverproto_cbreg_submission_request_dlfin( void (*cbfunc)( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code ) );

/* Callback for clarification request. (from team)
 * Pass the "requester's team account", "whether this is a private message", and "clarification message" to server program.
 * Server should record those information into db and redirect the request to admin and judge.  Also note that all clarifications should be assigned a "clar id".
 *   forward function: serverproto_clar_request()
 * Server should also reply the team with "queued" result string.
 *   reply function: serverproto_run_reply() */
void serverproto_cbreg_tsclar_request( void (*cbfunc)( char *srcip, unsigned int account_id, int private_byte, wchar_t *clarmsg ) );

/* Callback for problem download request. (from team)
 * Pass the "requester's team account", "requested problem id" to server program.
 * Server should upload the corresponding problem pack to user using problem_upload() function.
 *   reply function: serverproto_problem_upload() */
void serverproto_cbreg_pd_request( void (*cbfunc)( char *srcip, unsigned int account_id, unsigned int problem_id ) );

/* Callback for scoreboard sync request. (from team and admin)
 * Server should update all entries immediately to the requesting client.
 *   reply function: serverproto_sb_update() */
void serverproto_cbreg_sb_sync( void (*cbfunc)( char *srcip, short srctype ) );

/* Callback for run sync request. (from team)
 * Server should update all runs belong to that team to the reqesting client.
 *   reply function: serverproto_run_reply() */
void serverproto_cbreg_trun_sync( void (*cbfunc)( char *srcip, unsigned int account_id ) );

/* Callback for run result notification. (from judge)
 * Pass the "run id" and "result string" to server program.
 * Server should record those information into db and redirect the result to corresponding team.
 *   forward function: serverproto_run_reply() */
void serverproto_cbreg_run_result_notify( void (*cbfunc)( char *srcip, unsigned int run_id, wchar_t *result ) );

/* Callback for run sync request. (from judge)
 * Server should immediately re-send all run requests to the requesting judge client.
 *   reply function: serverproto_run_request() */
void serverproto_cbreg_run_sync( void (*cbfunc)( char *srcip ) );

/* Callback for judge to take run. (from judge)
 * Server should mark the judge as taken and notify all judges about this take (including the requesting client).
 *   reply function: serverproto_take_result() */
void serverproto_cbreg_take_run( void (*cbfunc)( char *srcip, unsigned int run_id ) );

/* Callback for account add request. (from admin)
 * Pass the "account type", "account name", and "password" to server program.  Note that password is passed using ANSI string.
 * Server should record those information into db and update functionalities to contain the new account (scoreboard for example).
 *   reply function: serverproto_account_update()
 *   forward function: serverproto_account_update() and serverproto_sb_update() */
void serverproto_cbreg_account_add( void (*cbfunc)( char *srcip, unsigned int type, wchar_t *account, char *password ) );

/* Callback for account delete request. (from admin)
 * Pass the "account name" to server program.
 * Server should remove the account from db and remove everything related to that account from the system.
 *    reply function: serverproto_account_update()
 *    forward function: serverproto_account_update() and serverproto_sb_update() */
void serverproto_cbreg_account_del( void (*cbfunc)( char *srcip, unsigned int account_id ) );

/* Callback for account modify request. (from admin)
 * Pass the "account id", "new account name", and "new password" to server program.
 * Server should modify the record in db and update everything related to that account (if account name is changed).
 *   reply function: serverproto_account_update()
 *   forward function: serverproto_account_update() and serverproto_sb_update() */
void serverproto_cbreg_account_mod( void (*cbfunc)( char *srcip, unsigned int account_id, wchar_t *new_account, char *new_password ) );

/* Callback for account sync request. (from admin)
 * Server should reply immediately all account information to requested administrator.
 *   reply function: serverproto_account_update() */
void serverproto_cbreg_account_sync( void (*cbfunc)( char *srcip ) );

/* Callback for problem add request. (from admin)
 * Pass "problem id" to server program.
 * The three string should be filled respectively with path where "problem description", "input data" and "correct answer" will be stored.
 * Server should record the new data into db.
 *   reply function: serverproto_problem_update()
 *   forward function: serverproto_problem_update() and serverproto_problem_change_add() */
void serverproto_cbreg_problem_add( void (*cbfunc)( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer ) );
void serverproto_cbreg_problem_add_dlfin( void (*cbfunc)( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer ) );

/* Callback for problem delete request. (from admin)
 * Pass "problem id" to server program.
 * Server should remove the problem from db and delete correspond data on disk.
 *   reply function: serverproto_problem_update()
 *   forward function: serverproto_problem_update() and serverproto_problem_change_del() */
void serverproto_cbreg_problem_del( void (*cbfunc)( char *srcip, unsigned int problem_id ) );

/* Callback for problem update request. (from admin)
 * Pass "problem id" to server program.
 * Server should modify the record in db and store new files.
 * The three strings is the same as problem_add().
 *   reply function: serverproto_problem_update()
 *   forward function: serverproto_problem_update() and serverproto_problem_change_mod() */
void serverproto_cbreg_problem_mod( void (*cbfunc)( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer ) );
void serverproto_cbreg_problem_mod_dlfin( void(*cbfunc)( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer ) );

/* Callback for problem sync request. (from admin or judge)
 * Server should reply immediately all problem information to requested client.
 *   reply function: serverproto_problem_update() */
void serverproto_cbreg_problem_sync( void (*cbfunc)( char *srcip, short srctype ) );

/* Callback for clarification result. (from admin or judge)
 * Pass "clarification id", "private message indicator" and "result string" to server program.
 * Server should update information in db and reply to all or one team, according to how private byte is set.
 *   reply function: serverproto_clar_reply()
 *   forward function: serverproto_clar_reply() */
void serverproto_cbreg_clar_result( void (*cbfunc)( char *srcip, unsigned int clar_id, int private_byte, wchar_t *result_string ) );

/* Callback form clarification sync. (from admin or judge)
 * Server should update clarification data with the requesting client.
 *   reply function: serverproto_clar_request() */
void serverproto_cbreg_clar_sync( void (*cbfunc)( char *srcip, short srctype ) );


/*----------------------------- tool functions -----------------------------*/

/* This function should be called in initial routine.  It listens for data from clients.
 * Note that all callbacks should be registered before invoking listen(). */
int serverproto_listen( char *localaddr );
int serverproto_stop_listen( void );
/* This function checks whether listen socket is currently active or not. */
int serverproto_active( void );

/* login/logout reply
 * used to reply client login requests */
int serverproto_login_reply( char *destip, short srctype, int confirmation, unsigned int account_id );
int serverproto_logout_reply( char *destip, short srctype, int confirmation );

/* password change reply
 * used to reply client password changing requests */
int serverproto_password_change_reply( char *destip, short desttype, int confirmation );

/* timer set function (to clients)
 * sets timer for clients */
int serverproto_timer_set( char *destip, short desttype, unsigned int hours, unsigned int minutes, unsigned int seconds );

/* contest start/stop functions (to clients)
 * sets contest state for clients */
int serverproto_contest_start( char *destip, short desttype );
int serverproto_contest_stop( char *destip, short desttype );

/* run result reply (to team)
 * reply run result to team clients */
int serverproto_run_reply( char *destip, unsigned int run_id, unsigned int problem_id, wchar_t *result );

/* clarification reply (to all clients)
 * reply clarification result to all clients */
int serverproto_clar_reply( char *destip, short desttype, unsigned int clar_id, wchar_t *clarmsg, wchar_t *result );

/* problem modification notify (to team)
 * notify team client about changes on problem listing */
int serverproto_problem_change_add( char *destip, unsigned int problem_id, wchar_t *problem_name );
int serverproto_problem_change_del( char *destip, unsigned int problem_id );
int serverproto_problem_change_mod( char *destip, unsigned int problem_id, wchar_t *problem_name );

/* scoreboard update (to team and admin)
 * notify team and admin client about scoreboard updates */
int serverproto_sb_update( char *destip, short desttype, unsigned int upd_acc_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time );
/* this one notifies about the removal of record on scoreboard (possibly triggered by a removal of account) */
int serverproto_sb_remove( char *destip, short desttype, unsigned int rm_account_id );

/* problem upload (to team)
 * upload problem description to team client (due to a previous problem download request) */
int serverproto_problem_upload( char *destip, wchar_t *path_description );

/* run request (to judge)
 * run request to judge client */
int serverproto_run_request( char *destip, unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code );

/* take result (to judge)
 * notify judges about take result */
int serverproto_take_result( char *destip, unsigned int run_id, int success );

/* account information update (to admin)
 * updates account listing to administrator */
int serverproto_account_update( char *destip, unsigned int account_id, unsigned int type, wchar_t *account );
/* this one notifies about account removal */
int serverproto_account_remove( char *destip, unsigned int account_id );

/* problem information update (to admin and judge)
 * updates problem listing to admin and judge clients */
int serverproto_problem_update( char *destip, short desttype, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer );
/* this one notifies about problem removal */
int serverproto_problem_remove( char *destip, short desttype, unsigned int problem_id );

/* clarification request (to admin and judge)
 * request clarification to admin and judge clients */
int serverproto_clar_request( char *destip, short desttype, unsigned int clar_id, unsigned int account_id, int private_byte, wchar_t *clarmsg );

/* contest site situation -- not implemented yet */

#endif
