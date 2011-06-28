#include "db_tool.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

/*--------------------- prepared statement structures ---------------------*/
/* initial admin01/admin01 account */
sqlite3_stmt *ps_select_admin01_exist;
sqlite3_stmt *ps_insert_admin01;

/* login_request() */
sqlite3_stmt *ps_select_account;
sqlite3_stmt *ps_select_account_pass;
sqlite3_stmt *ps_update_user_online;

/* logout_request() */
sqlite3_stmt *ps_select_logged_in;
sqlite3_stmt *ps_update_user_offline;

/* password_change() */
sqlite3_stmt *ps_select_password;
sqlite3_stmt *ps_update_change_password;

/* admin_timer_set() */
sqlite3_stmt *ps_select_acctype_ipaddr;

/* submission_request{_dlfin}() */
sqlite3_stmt *ps_select_max_run_id;
sqlite3_stmt *ps_insert_new_submission;
sqlite3_stmt *ps_select_ipaddr_online_sreq;

/* pd_request() */
sqlite3_stmt *ps_select_path_desc;

/* sb_sync() */
sqlite3_stmt *ps_select_full_sb;

/* run_result_notify() */
sqlite3_stmt *ps_select_run;
sqlite3_stmt *ps_select_run_chk_dup;
sqlite3_stmt *ps_update_judge_result;
sqlite3_stmt *ps_select_accept_count_rrn;
sqlite3_stmt *ps_update_accept_count;
sqlite3_stmt *ps_select_account_accept_count;

/* trun_sync() */
sqlite3_stmt *ps_select_full_trun;

/* tp_sync() */
sqlite3_stmt *ps_select_problem_id_name;

/* run_sync() */
sqlite3_stmt *ps_select_unjudged;

/* take_run() */
sqlite3_stmt *ps_update_taken;
sqlite3_stmt *ps_select_ipaddr_exclusive;

/* account_add() */
sqlite3_stmt *ps_insert_new_account;
sqlite3_stmt *ps_select_max_account_id;
sqlite3_stmt *ps_insert_new_scoreboard;
sqlite3_stmt *ps_select_ipaddr_online_accadd;

/* account_del() */
sqlite3_stmt *ps_select_acctype_accdel;
sqlite3_stmt *ps_delete_user;
sqlite3_stmt *ps_select_ipaddr_accdel;

/* account_mod() */
sqlite3_stmt *ps_select_acctype_accmod;
sqlite3_stmt *ps_update_account;
sqlite3_stmt *ps_update_account_password;
sqlite3_stmt *ps_select_ipaddr_accmod;
sqlite3_stmt *ps_select_accept_count_accmod;

/* account_sync() */
sqlite3_stmt *ps_select_full_account;

/* problem_add_dlfin() */
sqlite3_stmt *ps_insert_new_problem;
sqlite3_stmt *ps_select_ipaddr_padd;

/* problem_del() */
sqlite3_stmt *ps_delete_related_runs;
sqlite3_stmt *ps_delete_problem;
sqlite3_stmt *ps_select_ipaddr_pdel;

/* problem_mod() */
sqlite3_stmt *ps_update_problem;
sqlite3_stmt *ps_select_ipaddr_pmod;

/* problem_sync() */
sqlite3_stmt *ps_select_full_problem;

/* clar_request() */
sqlite3_stmt *ps_insert_clar;
sqlite3_stmt *ps_select_max_clar_id;

/* clar_result() */
sqlite3_stmt *ps_update_clar_result;
sqlite3_stmt *ps_select_clar_msg;
sqlite3_stmt *ps_select_ipaddr_acc_cr;
sqlite3_stmt *ps_select_ipaddr_cr;

/* clar_sync() */
sqlite3_stmt *ps_select_unrep_clar;

/* serverdb_contest() */
sqlite3_stmt *ps_select_ipaddr_sdbc;

/* serverdb_problem_change() */
sqlite3_stmt *ps_select_ipaddr_sdbpc;

/* serverdb_clar_request() */
sqlite3_stmt *ps_select_ipaddr_sdbcr;

/* serverdb_sb_update() */
sqlite3_stmt *ps_select_ipaddr_sdbsbu;


void createPrepareStatement( sqlite3 *db )
{
	/* initial admin01/admin01 account */
	sqlite3_prepare_v2( db, "SELECT * FROM user WHERE account = 'admin01';", -1, &ps_select_admin01_exist, NULL );
	sqlite3_prepare_v2( db, "INSERT INTO user VALUES(NULL, 'admin01', 'admin01', ?, NULL, 'no');", -1, &ps_insert_admin01, NULL );
	
	/* login_request() */
	sqlite3_prepare_v2( db, "SELECT account_id FROM user WHERE account = ?;", -1, &ps_select_account, NULL );
	sqlite3_prepare_v2( db, "SELECT account_id FROM user WHERE account = ? AND password = ?;", -1, &ps_select_account_pass, NULL );
	sqlite3_prepare_v2( db, "UPDATE user SET ipaddress = ?, logged_in = 'yes' WHERE account_id = ?;", -1, &ps_update_user_online, NULL );

	/* logout_request() */
	sqlite3_prepare_v2( db, "SELECT logged_in FROM user WHERE account_id = ?;", -1, &ps_select_logged_in, NULL );
	sqlite3_prepare_v2( db, "UPDATE user SET logged_in = 'no' WHERE account_id = ?;", -1, &ps_update_user_offline, NULL );

	/* password_change() */
	sqlite3_prepare_v2( db, "SELECT password FROM user WHERE account_id = ?;", -1, &ps_select_password, NULL );
	sqlite3_prepare_v2( db, "UPDATE user SET password = ? WHERE account_id = ?;", -1, &ps_update_change_password, NULL );

	/* admin_timer_set() */
	sqlite3_prepare_v2( db, "SELECT account_type, ipaddress FROM user WHERE logged_in = 'yes';", -1, &ps_select_acctype_ipaddr, NULL );

	/* submission_request{_dlfin}() */
	sqlite3_prepare_v2( db, "SELECT MAX(run_id) FROM submission;", -1, &ps_select_max_run_id, NULL );
	sqlite3_prepare_v2( db, "INSERT INTO submission VALUES(NULL, ?, ?, ?, ?, 'no', 'queued');", -1, &ps_insert_new_submission, NULL );
	sqlite3_prepare_v2( db, "SELECT ipaddress FROM user WHERE account_type = ? AND logged_in = 'yes';", -1, &ps_select_ipaddr_online_sreq, NULL );

	/* pd_request() */
	sqlite3_prepare_v2( db, "SELECT path_description FROM problem WHERE problem_id = ?;", -1, &ps_select_path_desc, NULL );

	/* sb_sync() */
	sqlite3_prepare_v2( db, "SELECT account_id, account, time, accept_count FROM user NATURAL JOIN scoreboard;", -1, &ps_select_full_sb, NULL );

	/* run_result_notify() */
	sqlite3_prepare_v2( db, "SELECT account_id, problem_id, ipaddress FROM submission NATURAL JOIN user WHERE run_id = ?;", -1, &ps_select_run, NULL );
	sqlite3_prepare_v2( db, "SELECT * FROM submission WHERE account_id = ? AND problem_id = ? AND judge_result = 'yes';", -1, &ps_select_run_chk_dup, NULL );
	sqlite3_prepare_v2( db, "UPDATE submission SET judge_result = ? WHERE run_id = ?;", -1, &ps_update_judge_result, NULL );
	sqlite3_prepare_v2( db, "SELECT accept_count FROM scoreboard WHERE account_id = ?;", -1, &ps_select_accept_count_rrn, NULL );
	sqlite3_prepare_v2( db, "UPDATE scoreboard SET accept_count = ? WHERE account_id = ?;", -1, &ps_update_accept_count, NULL );
	sqlite3_prepare_v2( db, "SELECT account, accept_count FROM user NATURAL JOIN scoreboard WHERE account_id = ?;", -1, &ps_select_account_accept_count, NULL );

	/* trun_sync() */
	sqlite3_prepare_v2( db, "SELECT run_id, problem_id, judge_result FROM submission WHERE account_id = ?;", -1, &ps_select_full_trun, NULL );

	/* tp_sync() */
	sqlite3_prepare_v2( db, "SELECT problem_id, problem_name FROM problem;", -1, &ps_select_problem_id_name, NULL );

	/* run_sync() */
	sqlite3_prepare_v2( db, "SELECT run_id, problem_id, lang, path_code FROM submission WHERE judge_result = 'queued';", -1, &ps_select_unjudged, NULL );

	/* take_run() */
	sqlite3_prepare_v2( db, "UPDATE submission SET taken = 'yes' WHERE run_id = ?;", -1, &ps_update_taken, NULL );
	sqlite3_prepare_v2( db, "SELECT ipaddress FROM user WHERE account_type = ? and ipaddress <> ?;", -1, &ps_select_ipaddr_exclusive, NULL );

	/* account_add() */
	sqlite3_prepare_v2( db, "INSERT INTO user VALUES(NULL, ?, ?, ?, NULL, 'no');", -1, &ps_insert_new_account, NULL );
	sqlite3_prepare_v2( db, "SELECT MAX( account_id ) FROM user;", -1, &ps_select_max_account_id, NULL );
	sqlite3_prepare_v2( db, "INSERT INTO scoreboard VALUES(NULL, ?, 0, 0);", -1, &ps_insert_new_scoreboard, NULL );
	sqlite3_prepare_v2( db, "SELECT ipaddress FROM user WHERE account_type = ? AND logged_in = 'yes';", -1, &ps_select_ipaddr_online_accadd, NULL );

	/* account_del() */
	sqlite3_prepare_v2( db, "SELECT account_type FROM user WHERE account_id = ?;", -1, &ps_select_acctype_accdel, NULL );
	sqlite3_prepare_v2( db, "DELETE FROM user WHERE account_id = ?;", -1, &ps_delete_user, NULL );
	sqlite3_prepare_v2( db, "SELECT ipaddress FROM user WHERE account_type = ? AND logged_in = 'yes';", -1, &ps_select_ipaddr_accdel, NULL );

	/* account_mod() */
	sqlite3_prepare_v2( db, "SELECT account_type FROM user WHERE account_id = ?;", -1, &ps_select_acctype_accmod, NULL );
	sqlite3_prepare_v2( db, "UPDATE user SET account = ? WHERE account_id = ?;", -1, &ps_update_account, NULL );
	sqlite3_prepare_v2( db, "UPDATE user SET account = ?, password = ? WHERE account_id = ?;", -1, &ps_update_account_password, NULL );
	sqlite3_prepare_v2( db, "SELECT ipaddress FROM user WHERE account_type = ? AND logged_in = 'yes';", -1, &ps_select_ipaddr_accmod, NULL );
	sqlite3_prepare_v2( db, "SELECT accept_count, time FROM scoreboard WHERE account_id = ?;", -1, &ps_select_accept_count_accmod, NULL );

	/* account_sync() */
	sqlite3_prepare_v2( db, "SELECT account_id, account, account_type FROM user;", -1, &ps_select_full_account, NULL );

	/* problem_add_dlfin() */
	sqlite3_prepare_v2( db, "INSERT INTO problem VALUES(NULL, ?, ?, ?, ?, ?);", -1, &ps_insert_new_problem, NULL );
	sqlite3_prepare_v2( db, "SELECT ipaddress FROM user WHERE account_type = ? AND logged_in = 'yes';", -1, &ps_select_ipaddr_padd, NULL );

	/* problem_del() */
	sqlite3_prepare_v2( db, "DELETE FROM submission WHERE problem_id = ?;", -1, &ps_delete_related_runs, NULL );
	sqlite3_prepare_v2( db, "DELETE FROM problem WHERE problem_id = %u;", -1, &ps_delete_problem, NULL );
	sqlite3_prepare_v2( db, "SELECT ipaddress FROM user WHERE account_type = ? AND logged_in = 'yes';", -1, &ps_select_ipaddr_pdel, NULL );

	/* problem_mod() */
	sqlite3_prepare_v2( db, "UPDATE problem SET problem_name = ?, path_description = ?, correct_input_filename = ?, correct_output_filename = ?, time_limit = ? WHERE problem_id = ?;", -1, &ps_update_problem, NULL );
	sqlite3_prepare_v2( db, "SELECT ipaddress FROM user WHERE account_type = ? AND logged_in = 'yes';", -1, &ps_select_ipaddr_pmod, NULL );

	/* problem_sync() */
	sqlite3_prepare_v2( db, "SELECT * FROM problem;", -1, &ps_select_full_problem, NULL );

	/* clar_request() */
	sqlite3_prepare_v2( db, "INSERT INTO clarification VALUES(NULL, ?, ?, NULL, ?);", -1, &ps_insert_clar, NULL );
	sqlite3_prepare_v2( db, "SELECT MAX( clar_id ) FROM clarification;", -1, &ps_select_max_clar_id, NULL );

	/* clar_result() */
	sqlite3_prepare_v2( db, "UPDATE clarification SET result = ? WHERE clar_id = ?;", -1, &ps_update_clar_result, NULL );
	sqlite3_prepare_v2( db, "SELECT account_id, msg FROM clarification WHERE clar_id = ?;", -1, &ps_select_clar_msg, NULL );
	sqlite3_prepare_v2( db, "SELECT ipaddress FROM user WHERE account_id = ?;", -1, &ps_select_ipaddr_acc_cr, NULL );
	sqlite3_prepare_v2( db, "SELECT ipaddress FROM user WHERE account_type = ?;", -1, &ps_select_ipaddr_cr, NULL );

	/* clar_sync() */
	sqlite3_prepare_v2( db, "SELECT clar_id, account_id, msg, private_byte, account FROM user NATURAL JOIN clarification WHERE result IS NULL;", -1, &ps_select_unrep_clar, NULL );

	/* serverdb_contest() */
	sqlite3_prepare_v2( db, "SELECT ipaddress FROM user WHERE account_type = ? AND logged_in = 'yes';", -1, &ps_select_ipaddr_sdbc, NULL );

	/* serverdb_problem_change() */
	sqlite3_prepare_v2( db, "SELECT ipaddress FROM user WHERE account_type = ? AND logged_in = 'yes';", -1, &ps_select_ipaddr_sdbpc, NULL );

	/* serverdb_clar_request() */
	sqlite3_prepare_v2( db, "SELECT ipaddress, account FROM user WHERE account_type = ? AND logged_in = 'yes';", -1, &ps_select_ipaddr_sdbcr, NULL );

	/* serverdb_sb_update() */
	sqlite3_prepare_v2( db, "SELECT ipaddress FROM user WHERE account_type = ? AND logged_in = 'yes';", -1, &ps_select_ipaddr_sdbsbu, NULL );
}


void destroyPrepareStatement( sqlite3 *db )
{
	/* initial admin01/admin01 account */
	sqlite3_finalize( ps_select_admin01_exist );
	sqlite3_finalize( ps_insert_admin01 );

	/* login_request() */
	sqlite3_finalize( ps_select_account );
	sqlite3_finalize( ps_select_account_pass );
	sqlite3_finalize( ps_update_user_online );

	/* logout_request() */
	sqlite3_finalize( ps_select_logged_in );
	sqlite3_finalize( ps_update_user_offline );

	/* password_change() */
	sqlite3_finalize( ps_select_password );
	sqlite3_finalize( ps_update_change_password );

	/* admin_timer_set() */
	sqlite3_finalize( ps_select_acctype_ipaddr );

	/* submission_request{_dlfin}() */
	sqlite3_finalize( ps_select_max_run_id );
	sqlite3_finalize( ps_insert_new_submission );
	sqlite3_finalize( ps_select_ipaddr_online_sreq );

	/* pd_request() */
	sqlite3_finalize( ps_select_path_desc );

	/* sb_sync() */
	sqlite3_finalize( ps_select_full_sb );

	/* run_result_notify() */
	sqlite3_finalize( ps_select_run );
	sqlite3_finalize( ps_select_run_chk_dup );
	sqlite3_finalize( ps_update_judge_result );
	sqlite3_finalize( ps_select_accept_count_rrn );
	sqlite3_finalize( ps_update_accept_count );
	sqlite3_finalize( ps_select_account_accept_count );

	/* trun_sync() */
	sqlite3_finalize( ps_select_full_trun );

	/* tp_sync() */
	sqlite3_finalize( ps_select_problem_id_name );

	/* run_sync() */
	sqlite3_finalize( ps_select_unjudged );

	/* take_run() */
	sqlite3_finalize( ps_update_taken );
	sqlite3_finalize( ps_select_ipaddr_exclusive );

	/* account_add() */
	sqlite3_finalize( ps_insert_new_account );
	sqlite3_finalize( ps_select_max_account_id );
	sqlite3_finalize( ps_insert_new_scoreboard );
	sqlite3_finalize( ps_select_ipaddr_online_accadd );

	/* account_del() */
	sqlite3_finalize( ps_select_acctype_accdel );
	sqlite3_finalize( ps_delete_user );
	sqlite3_finalize( ps_select_ipaddr_accdel );

	/* account_mod() */
	sqlite3_finalize( ps_select_acctype_accmod );
	sqlite3_finalize( ps_update_account );
	sqlite3_finalize( ps_update_account_password );
	sqlite3_finalize( ps_select_acctype_accmod );
	sqlite3_finalize( ps_select_ipaddr_accmod );
	sqlite3_finalize( ps_select_accept_count_accmod );

	/* account_sync() */
	sqlite3_finalize( ps_select_full_account );

	/* problem_add_dlfin() */
	sqlite3_finalize( ps_insert_new_problem );
	sqlite3_finalize( ps_select_ipaddr_padd );

	/* problem_del() */
	sqlite3_finalize( ps_delete_related_runs );
	sqlite3_finalize( ps_delete_problem );
	sqlite3_finalize( ps_select_ipaddr_pdel );

	/* problem_mod() */
	sqlite3_finalize( ps_update_problem );
	sqlite3_finalize( ps_select_ipaddr_pmod );

	/* problem_sync() */
	sqlite3_finalize( ps_select_full_problem );

	/* clar_request() */
	sqlite3_finalize( ps_insert_clar );
	sqlite3_finalize( ps_select_max_clar_id );

	/* clar_result() */
	sqlite3_finalize( ps_update_clar_result );
	sqlite3_finalize( ps_select_clar_msg );
	sqlite3_finalize( ps_select_ipaddr_acc_cr );
	sqlite3_finalize( ps_select_ipaddr_cr );

	/* clar_sync() */
	sqlite3_finalize( ps_select_unrep_clar );

	/* serverdb_contest() */
	sqlite3_finalize( ps_select_ipaddr_sdbc );

	/* serverdb_problem_change() */
	sqlite3_finalize( ps_select_ipaddr_sdbpc );

	/* serverdb_clar_request() */
	sqlite3_finalize( ps_select_ipaddr_sdbcr );

	/* serverdb_sb_update() */
	sqlite3_finalize( ps_select_ipaddr_sdbsbu );
}


void strdis_cb( void *mem )
{
	free( mem );
}

char *dyn_strcpy( const unsigned char *src )
{
	char *retptr = NULL;
	
	if( src == NULL )
		return retptr;

	retptr = (char *)malloc( ( strlen( (const char*)src ) + 1 ) * sizeof( char ) );
	strcpy( retptr, (const char*)src );
	return retptr;
}
