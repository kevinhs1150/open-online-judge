/* serverproto.h
 * OOJ communication implementation, server. */
#ifndef SERVERPROTO_H_
#define SERVERPROTO_H_

#include "protointernal.h"

#include <stdio.h>

/* callback registration functions */
/* NOTE:
 * All strings passed as argument to callback function will be released afterward.  Be sure to wcscpy() (wide-string-strcpy()) it if needed.
 * Password will be ANSI string, not Unicode. */

/* Callback for login request. (from everyone)
 * Pass "login account", "login password" and "client type of requester(admin, team, etc.)" to server program.
 * Server should determine the validity of account/password, reply, and mark the account as login. */
void serverproto_cbreg_login_request( void (*cbfunc)( char *srcip, short srctype, wchar_t *account, char *password ) );

/* Callback for logout request. (from everyone)
 * Pass "account id" to server program.
 * Server should give the client a reply and mark the account as logged out. */
void serverproto_cbreg_logout_request( void (*cbfunc)( char *srcip, short srctype, unsigned int account_id ) );

/* Callback for submission request. (from team)
 * Pass the "requester's team account", "submit problem id", and "coding language" to server program.
 * Server should record those information into db and redirect the submission to judge.  Also note that all submission should be assigned a "run id".
 * The path_code string should be filled with the path where code will be stored. */
void serverproto_cbreg_submission_request( void (*cbfunc)( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code ) );
void serverproto_cbreg_submission_request_dlfin( void (*cbfunc)( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code ) );

/* Callback for clarification request. (from team)
 * Pass the "requester's team account", "whether this is a private message", and "clarification message" to server program.
 * Server should record those information into db and redirect the request to admin. */
void serverproto_cbreg_clar_request( void (*cbfunc)( char *srcip, unsigned int account_id, int private_byte, wchar_t *clarmsg ) );

/* Callback for problem download request. (from team)
 * Pass the "requester's team account", "requested problem id" to server program.
 * Server should upload the corresponding problem pack to user using problem_upload() function. */
void serverproto_cbreg_pd_request( void (*cbfunc)( char *srcip, unsigned int account_id, unsigned int problem_id ) );

/* Callback for run result notification. (from judge)
 * Pass the "run id" and "result string" to server program.
 * Server should record those information into db and redirect the result to corresponding team. */
void serverproto_cbreg_run_result_notify( void (*cbfunc)( char *srcip, unsigned int run_id, wchar_t *result ) );

/* Callback for account add request. (from admin)
 * Pass the "account type", "account name", and "password" to server program.  Note that password is passed using ANSI string.
 * Server should record those information into db. */
void serverproto_cbreg_account_add( void (*cbfunc)( char *srcip, unsigned int type, wchar_t *account, char *password ) );

/* Callback for account delete request. (from admin)
 * Pass the "account name" to server program.
 * Server should remove the account from db. */
void serverproto_cbreg_account_del( void (*cbfunc)( char *srcip, unsigned int account_id ) );

/* Callback for account modify request. (from admin)
 * Pass the "account id", "new account name", and "new password" to server program.
 * Server should modify the record in db. */
void serverproto_cbreg_account_mod( void (*cbfunc)( char *srcip, unsigned int account_id, wchar_t *new_account, char *new_password ) );

/* Callback for account update request. (from admin)
 * Server should reply immediately all account information to requested administrator. */
void serverproto_cbreg_account_update( void (*cbfunc)( char *srcip ) );

/* Callback for problem add request. (from admin)
 * Pass "problem id" to server program.
 * The three string should be filled respectively with path where "problem description", "input data" and "correct answer" will be stored.
 * Server should record the new data into db. */
void serverproto_cbreg_problem_add( void (*cbfunc)( char *srcip, unsigned int problem_id, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer ) );
void serverproto_cbreg_problem_add_dlfin( void (*cbfunc)( char *srcip, unsigned int problem_id, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer ) );

/* Callback for problem delete request. (from admin)
 * Pass "problem id" to server program.
 * Server should remove the problem from db and delete correspond data on disk. */
void serverproto_cbreg_problem_del( void (*cbfunc)( char *srcip, unsigned int problem_id ) );

/* Callback for problem update request. (from admin)
 * Pass "problem id" to server program.
 * Server should modify the record in db and store new files.
 * The three strings is the same as problem_add(). */
void serverproto_cbreg_problem_mod( void (*cbfunc)( char *srcip, unsigned int problem_id, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer ) );
void serverproto_cbreg_problem_mod_dlfin( void(*cbfunc)( char *srcip, unsigned int problem_id, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer ) );

/* Callback for problem update request. (from admin)
 * Server should reply immediately all problem information to requested administrator. */
void serverproto_cbreg_problem_update( void (*cbfunc)( char *srcip ) );

/* Callback for clarification result. (from admin)
 * Pass "clarification id", "private message indicator" and "result string" to server program.
 * Server should update information in db and reply to all or one team, according to how private byte is set. */
void serverproto_cbreg_clar_result( void (*cbfunc)( char *srcip, unsigned int clar_id, int private_byte, wchar_t *result_string ) );


/* listen thread
 * This function should be called in initial routine.  It listens for data from clients. */
int serverproto_listen( char *localaddr );
int serverproto_stop_listen( void );
/* This function checks whether listen socket is currently active or not. */
int serverproto_active( void );

/* login reply */
int serverproto_login_reply( char *destip, short srctype, int confirmation, unsigned int account_id );

/* logout reply */
int serverproto_logout_reply( char *destip, short srctype, int confirmation );

/* run result reply (to team)
 * Initial state (waiting for run) should also be notofied with this function. */
int serverproto_run_reply( char *destip, unsigned int run_id, wchar_t *result );

/* clarification reply (to team) */
int serverproto_clar_reply( char *destip, unsigned int clar_id, wchar_t *result );

/* scoreboard update */
int serverproto_sb_update( char *destip, unsigned int upd_acc_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time );

/* problem upload */
int serverproto_problem_upload( char *destip, wchar_t *path_description );

/* run request (to judge) */
int serverproto_run_request( char *destip, unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code );

/* account information update (to admin) */
int serverproto_account_info( char *destip, unsigned int account_id, unsigned int type, wchar_t *account );

/* problem update (to judge & admin) */
int serverproto_problem_info( char *destip, unsigned int problem_id, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer );

/* contest site situation -- not implemented yet */

/* clarification request (to admin) */
int serverproto_clar_request( char *destip, unsigned int clar_id, int private_byte, wchar_t *clarmsg );

#endif
