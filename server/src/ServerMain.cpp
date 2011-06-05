#include "ServerMain.h"

#include "liboojproto.h"

/* Server callback functions prototype. */
void cb_login_request( char *srcip, short srctype, wchar_t *account, char *password );
void cb_logout_request( char *srcip, short srctype, unsigned int account_id );
void cb_password_change( char *srcip, unsigned int account_id, char *password );
void cb_timer_sync( char *srcip, short srctype );
void cb_contest_state_sync( char *srcip, short srctype );
void cb_admin_timer_set( char *srcip, unsigned int hours, unsigned int minutes, unsigned int seconds );
void cb_admin_contest_start( char *srcip );
void cb_admin_contest_stop( char *srcip );
void cb_submission_request( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code );
void cb_submission_request_dlfin( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code );
void cb_clar_request( char *srcip, unsigned int account_id, int private_byte, wchar_t *clarmsg );
void cb_pd_request( char *srcip, unsigned int account_id, unsigned int problem_id );
void cb_sb_sync( char *srcip );
void cb_run_sync( char *srcip, unsigned int account_id );
void cb_run_result_notify( char *srcip, unsigned int run_id, wchar_t *result );
void cb_take_run( char *srcip, unsigned int run_id );
void cb_account_add( char *srcip, unsigned int type, wchar_t *account, char *password );
void cb_account_del( char *srcip, unsigned int account_id );
void cb_account_mod( char *srcip, unsigned int account_id, wchar_t *new_account, char *new_password );
void cb_account_sync( char *srcip );
void cb_problem_add( char *srcip, unsigned int problem_id, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer );
void cb_problem_add_dlfin( char *srcip, unsigned int problem_id, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer );
void cb_problem_del( char *srcip, unsigned int problem_id );
void cb_problem_mod( char *srcip, unsigned int problem_id, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer );
void cb_problem_mod_dlfin( char *srcip, unsigned int problem_id, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer );
void cb_problem_sync( char *srcip, short srctype )
void cb_clar_result( char *srcip, unsigned int clar_id, int private_byte, wchar_t *result_string );
void cb_clar_sync( char *srcip, short srctype );


ServerFrame::ServerFrame(wxFrame *frame)
    : ServerGUI(frame)
{
	/* cb_submission_request() needs subdirectory to store submit files */
	system( "mkdir submits" );
	
	/* create database file */
	if ( sqlite3_open_v2( "server_db.db3", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL ) ) {
       return;
    }
	/* create table SQL */
	sqlite3_exec( db, create_user, 0, 0, &errMsg );
	sqlite3_exec( db, create_problem, 0, 0, &errMsg );
	sqlite3_exec( db, create_submission, 0, 0, &errMsg );
	sqlite3_exec( db, create_clarification, 0, 0, &errMsg );
	sqlite3_exec( db, create_scoreboard, 0, 0, &errMsg );
	sqlite3_exec( db, create_judge_type, 0, 0, &errMsg );
	
	/* register callback functions */
	serverproto_cbreg_login_request( cb_login_request );
	serverproto_cbreg_logout_request( cb_logout_request );
	serverproto_cbreg_password_change( cb_password_change );
	serverproto_cbreg_timer_sync( cb_timer_sync );
	serverproto_cbreg_contest_state_sync( cb_contest_state_sync );
	serverproto_cbreg_admin_timer_set( cb_admin_timer_set );
	serverproto_cbreg_admin_contest_start( cb_admin_contest_start );
	serverproto_cbreg_admin_contest_stop( cb_admin_contest_stop );
	serverproto_cbreg_submission_request( cb_submission_request );
	serverproto_cbreg_submission_request_dlfin( cb_submission_request_dlfin );
	serverproto_cbreg_clar_request( cb_clar_request );
	serverproto_cbreg_pd_request( cb_pd_request );
	serverproto_cbreg_sb_sync( cb_sb_sync );
	serverproto_cbreg_run_result_notify( cb_run_result_notify );
	serverproto_cbreg_trun_sync( cb_run_sync );
	serverproto_cbreg_take_run( cb_take_run );
	serverproto_cbreg_account_add( cb_account_add );
	serverproto_cbreg_account_del( cb_account_del );
	serverproto_cbreg_account_mod( cb_account_mod );
	serverproto_cbreg_account_sync( cb_account_sync );
	serverproto_cbreg_problem_add( cb_problem_add );
	serverproto_cbreg_problem_add_dlfin( cb_problem_add_dlfin );
	serverproto_cbreg_problem_del( cb_problem_del );
	serverproto_cbreg_problem_mod( cb_problem_mod );
	serverproto_cbreg_problem_mod_dlfin( cb_problem_mod_dlfin );
	serverproto_cbreg_problem_sync( cb_problem_sync );
	serverproto_cbreg_clar_result( cb_clar_result );
	serverproto_cbreg_clar_sync( cb_clar_sync );
}


ServerFrame::~ServerFrame()
{
	if( serverproto_active() )
		serverproto_stop_listen();
	/* close database */
	sqlite3_close( db );
}

void ServerFrame::OnButtonClickStart( wxCommandEvent& event )
{
	/* start listen socket */
	if( serverproto_listen("0.0.0.0") < 0 )
	{
#if SERVER_DBG > 0
		printf("[ServerFrame::OnButtonClickStart()] serverproto_listen() call failed.\n");
#endif
		wxMessageBox( wxT("Server start failed.\nStage: start listen socket."), wxT("Fatal Error"), wxOK|wxICON_ERROR, this );
	}
}

void ServerFrame::OnButtonClickStop( wxCommandEvent& event )
{
	if( serverproto_active() )
		serverproto_stop_listen();
}



/* Server callback function definition. */
void cb_login_request( char *srcip, short srctype, wchar_t *account, char *password )
{
	char sqlquery[100], account_char[28], **table, *errMsg = NULL;
	int rows, cols;
	unsigned int account_id;
	
	/* determine the validity of account */
	wcstombs(account_char, account, 25);
	sprintf(sqlquery, "SELECT account_id FROM user WHERE account = '%s';", account_char);
	sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
	
	if(rows == 0)	/* LOGIN_ACC_NOTEXIST */
	{
		serverproto_login_reply( srcip, srctype, LOGIN_ACC_NOTEXIST, -1);
		sqlite3_free_table(table);
	}
	else
	{
		sqlite3_free_table(table);
		
		/* determine the validity of account/password */
		sprintf(sqlquery, "SELECT account_id FROM user WHERE account = '%s' AND password = '%s';", account_char, password);
		sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
		if(rows >= 1)	/* LOGIN_VALID */
		{
			sscanf(table[1 * cols + 0], "%u", &account_id);
			
			/*  mark the account as logged in, set account ip */
			sprintf(sqlquery, "UPDATE user SET ipaddress = '%s', logged_in = 'yes' WHERE account_id = '%u';", srcip, account_id);
			sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
			serverproto_login_reply( srcip, srctype, LOGIN_VALID, account_id);
		}
		else	/* LOGIN_PASS_WRONGs */
		{
			serverproto_login_reply( srcip, srctype, LOGIN_PASS_WRONG, -1);
		}
		sqlite3_free_table(table);
	}
}

void cb_logout_request( char *srcip, short srctype, unsigned int account_id )
{
	char sqlquery[100], **table, *errMsg = NULL;
	int rows, cols;
	
	/* mark the account as logged out */
	sprintf(sqlquery, "SELECT logged_in FROM user WHERE account_id = '%u';", account_id);
	sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
	if(row >= 1)	/* LOGOUT_OK */
	{
		sprintf(sqlquery, "UPDATE user SET logged_in = 'no' WHERE account_id = '%u';", account_id);
		sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
		serverproto_logout_reply( srcip, srctype, LOGOUT_OK );
	}
	else	/* LOGOUT_FAIL */
	{
		/* account not exist */
		serverproto_logout_reply( srcip, srctype, LOGOUT_FAIL );
	}
	sqlite3_free_table(table);
}

void cb_password_change( char *srcip, unsigned int account_id, char *password )
{
	char sqlquery[100], **table, *errMsg = NULL;
	int rows, cols;
	short account_type;
	
	sprintf(sqlquery, "SELECT account_type FROM user WHERE account_id = '%u';", account_id);
	sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
	if(row >= 1)	/* PASSWD_SUCCESS */
	{
		/* store the changed password into database and give the client a reply */
		sscanf(table[1 * cols + 0], "%h", &account_type);
		sprintf(sqlquery, "UPDATE user SET password = '%s' WHERE account_id = '%u';", password, account_id);
		sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
		serverproto_password_change_reply( srcip, account_type, PASSWD_SUCCESS );

	}
	else	/* PASSWD_FAIL */
	{
		/* account not exist */
		serverproto_password_change_reply( srcip, -1, PASSWD_FAIL );
	}
	sqlite3_free_table(table);
}

void cb_timer_sync( char *srcip, short srctype )
{
	
}

void cb_contest_state_sync( char *srcip, short srctype )
{

}

void cb_admin_timer_set( char *srcip, unsigned int hours, unsigned int minutes, unsigned int seconds )
{

}

void cb_admin_contest_start( char *srcip )
{

}

void cb_admin_contest_stop( char *srcip )
{

}

//the function needs a subdirectory "submits/"
void cb_submission_request( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code )
{
	char sqlquery[100], coding_language_char[10], path_code_char[30], **table, *errMsg;
	int rows, cols;
	
	/* set path_code */
	sprintf(sqlquery, "SELECT * FROM submission;");
	sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
	wcstombs(coding_language_char, coding_language, 10);
	sprintf(path_code_char, "submits/submit%d.%s", rows + 1, coding_language_char);
	mbstowcs(*path_code, path_code_char, 30);
	sqlite3_free_table(table);
}

void cb_submission_request_dlfin( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code )
{
	char sqlquery[100], path_code_char[30], coding_language_char[10];
	char **table, *errMsg;
	int rows, cols, i;
	unsigned int run_id;
	
	/* record those information into db */
	wcstombs(coding_language_char, coding_language, 10);
	wcstombs(path_code_char, path_code, 30);
	sprintf(sqlquery, "INSERT INTO submission VALUES(NULL, '%u', '%u', '%s', '%s', NULL);", account_id, problem_id, coding_language_char, path_code_char);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
	
	/* get run_id from submission table */
	run_id = sqlite3_last_insert_rowid(db);  
	
	/* redirect the submission to all judge */
	sprintf(sqlquery, "SELECT ipaddress FROM user WHERE account_type = '%d';", OPSR_JUDGE);
	sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
	for(i=1;i<=rows;i++)
	{
		serverproto_run_request(table[i * cols + 0], run_id, problem_id, coding_language, path_code);
	}
	sqlite3_free_table(table);
}

void cb_clar_request( char *srcip, unsigned int account_id, int private_byte, wchar_t *clarmsg )
{
	char sqlquery[100], clarmsg_char[100];
	char *errMsg, **table;
	unsigned int clar_id;

	/* record clarification information into db */
	wcstombs(clarmsg_char, clarmsg, 100);
	sprintf(sqlquery, "INSERT INTO clarification VALUES(NULL, '%u', '%s', NULL, '%d');", account_id, clarmsg_char, private_byte);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
	clar_id = sqlite3_last_insert_rowid(db);
	
	/* redirect the request to admin */
	sprintf(sqlquery, "SELECT account_type, ipaddress FROM user WHERE account_type = '%d';", OPSR_ADMIN);
	sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
	for(i=1;i<=rows;i++)
	{
		serverproto_clar_request(table[i * cols + 0], OPSR_ADMIN, clar_id, private_byte, clarmsg );
	}
	sqlite3_free_table(table);
	
	/* redirect the request to judge */
	sprintf(sqlquery, "SELECT account_type, ipaddress FROM user WHERE account_type = '%d';", OPSR_JUDGE);
	sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
	for(i=1;i<=rows;i++)
	{
		serverproto_clar_request(table[i * cols + 0], OPSR_JUDGE, clar_id, private_byte, clarmsg );
	}
	sqlite3_free_table(table);
}

//the code has checked above. I'll check below later!
void cb_pd_request( char *srcip, unsigned int account_id, unsigned int problem_id )
{
	char sqlquery[100];
	char **table;
	char path_description_char[50];
	char path_description_w[50];
	
	/* send probem to team by calling problem_upload  */
	sprintf(sqlquery, "SELECT path_description FROM problem WHERE problem_id = '%u';", problem_id);
	sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
	sscanf(path_description_char, "%s", table[1 * cols + 0]);
	sqlite3_free_table(table);
	mbstowcs(path_description_w, path_description_char, 50);
	
	serverproto_problem_upload( srcip, path_description_w );
}

void cb_sb_sync( char *srcip )
{

}

void cb_run_result_notify( char *srcip, unsigned int run_id, wchar_t *result )
{
	char sqlquery[100];
	char result_char[25];
	char **table;
	char dstip[20];
	int rows, cols;
	unsigned int problem_id, account_id;
	
	/* add result to db */
	wcstombs(result_char, result, 25);
	sprintf(sqlquery, "UPDATE submission SET judge_result = '%s' WHERE run_id = '%u';", result_char, run_id);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
	/* call function, transfer the result to original submit team */
	sprintf(sqlquery, "SELECT account_id, problem_id FROM submission WHERE run_id = '%u';", run_id);
	sqlite3_get_table(db, sqlquery, &table, &rows, &cols, &errMsg);
	if(rows >= 1)
	{
		sscanf(table[1 * cols + 0], "%u", &account_id);
		sscanf(table[1 * cols + 1], "%u", &problem_id);
	}
	sqlite3_free_table(table);
	sprintf(sqlquery, "SELECT ipaddress FROM user WHERE account_id = '%u';", account_id);
	sqlite3_get_table(db, sqlquery, &table, &rows, &cols, &errMsg);
	if(rows >= 1)
	{
		sscanf(table[1 * cols + 0], "%s", dstip);
	}
	sqlite3_free_table(table);
	
	serverproto_run_reply( dstip, run_id, problem_id, result );
}

void cb_run_sync( char *srcip, unsigned int account_id )
{

}

void cb_take_run( char *srcip, unsigned int run_id )
{

}

void cb_account_add( char *srcip, unsigned int type, wchar_t *account, char *password )
{
	char sqlquery[100];
	char account_char[25];
	wcstombs(account_char, account, 25);
	sprintf(sqlquery, "INSERT INTO user VALUES(NULL, '%s', '%s', '%u', NULL, 'no');", account_char, password, type);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
}

void cb_account_del( char *srcip, unsigned int account_id )
{
	char sqlquery[100];
	sprintf(sqlquery, "DELETE FROM user WHERE account_id = '%u';", account_id);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
}

void cb_account_mod( char *srcip, unsigned int account_id, wchar_t *new_account, char *new_password )
{
	char sqlquery[100];
	char new_account_char[25];
	wcstombs(new_account_char, new_account, 25);
	if(password == NULL)	/* UPdate Only account */
	{
		sprintf(sqlquery, "UPDATE user SET account = '%s' WHERE account_id = '%u';", new_account_char, new_password, account_id);
	}
	else	/* update both account and password */
	{
		sprintf(sqlquery, "UPDATE user SET account = '%s', password = '%s' WHERE account_id = '%u';", new_account_char, new_password, account_id);
	}
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
}

void cb_account_sync( char *srcip )
{
	char sqlquery[100], account_char[25];
	char **table;
	unsigned int account_id;
	wchar_t account_w[25];
	
	/* update account information to the user with srcip */
	sprintf(sqlquery, "SELECT account_id, account, account_type FROM user WHERE ipaddress = '%s';", srcip);
	sqlite3_get_table(db, sqlquery, &table, &rows, &cols, &errMsg);
	if(rows >= 1)
	{
		sscanf(table[1 * rows + 0], "%u", &account_id);
		sscanf(table[1 * rows + 1], "%s", account_char);
		sscanf(table[1 * rows + 2], "%u", account_type);
		mbstowcs(account_w, account_char, 25);
		serverproto_account_update( srcip, account_id, account_type, account_w );
	}
	sqlite3_free_table(table);
	
}

//admin below
void cb_problem_add( char *srcip, unsigned int problem_id, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer )
{
	char sqlquery[100];
	char path_description_char[50], path_input_char[50], path_answer_char[50];
	
	/* edit path names */
	sprintf(path_description_char, "path_descr%u.pdf", problem_id);
	mbstowcs(*path_description, path_description_char, 50);
	
	sprintf(path_input_char, "p%u_in.txt", problem_id);
	mbstowcs(*path_input, path_input_char, 50);
	
	sprintf(path_answer_char, "p%u_out.txt", problem_id);
	mbstowcs(*path_answer, path_answer_char, 50);
}

void cb_problem_add_dlfin( char *srcip, unsigned int problem_id, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer )
{
	char sqlquery[100];
	char path_description_char[50], path_input_char[50], path_answer_char[50];
	
	/* convert (wchar_t *) to (char *) */
	wcstombs(path_description_char, path_description, 50);
	wcstombs(path_input_char, path_input, 50);
	wcstombs(path_answer_char, path_answer, 50);
	
	/* insert problem to db */
	sprintf(sqlquery, "INSERT INTO problem VALUES(NULL, '%s', '%s', '%s', '%u');", path_description_char, path_input_char, path_answer_char, time_limit);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
}

void cb_problem_del( char *srcip, unsigned int problem_id )
{
	char sqlquery[100];
	sprintf(sqlquery, "DELETE FROM problem WHERE problem_id = '%u';", problem_id);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
}

void cb_problem_mod( char *srcip, unsigned int problem_id, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer )
{
	/* do the same thing as cb_problem_add() */
	char sqlquery[100];
	char path_description_char[50], path_input_char[50], path_answer_char[50];
	
	/* edit path names */
	sprintf(path_description_char, "path_descr%u.pdf", problem_id);
	mbstowcs(*path_description, path_description_char, 50);
	
	sprintf(path_input_char, "p%u_in.txt", problem_id);
	mbstowcs(*path_input, path_input_char, 50);
	
	sprintf(path_answer_char, "p%u_out.txt", problem_id);
	mbstowcs(*path_answer, path_answer_char, 50);
}

void cb_problem_mod_dlfin( char *srcip, unsigned int problem_id, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer )
{
	/* do the same thing as cb_problem_add_dlfin() */
	char sqlquery[100];
	char path_description_char[50], path_input_char[50], path_answer_char[50];
	
	/* convert (wchar_t *) to (char *) */
	wcstombs(path_description_char, path_description, 50);
	wcstombs(path_input_char, path_input, 50);
	wcstombs(path_answer_char, path_answer, 50);
	
	/* insert problem to db */
	sprintf(sqlquery, "INSERT INTO problem VALUES(NULL, '%s', '%s', '%s', '%u');", path_description_char, path_input_char, path_answer_char, time_limit);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
}

void cb_problem_sync( char *srcip, short srctype )
{
	char sqlquery[100];
	char **table;
	int rows, cols;
	unsigned int account_id;
	/* update problem information to client with srcip */
	sprintf(sqlquery, "SELECT problem_id FROM problem WHERE ipaddress = '%s';", srcip);
    sqlite3_get_table(db , querysql, &table , &rows, &cols, &errMsg);
	if(row >= 1)
	{
		sscanf(table[1 * rows + 0], "%u", &account_id);
	}
	sqlite3_free_table(table);
	//serverproto_problem_update( char *destip, unsigned int problem_id, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer );
}

void cb_clar_result( char *srcip, unsigned int clar_id, int private_byte, wchar_t *result_string )
{
	char sqlquery[100], char result_string_char[100], **table, *errMsg;
	int rows, cols, i;
	unsigned int account_id;
	wchar_t msg_wchar[100];
	
	/* update clarification information into db */
	wcstombs(result_string_char, result_string, 100);
	sprintf(sqlquery, "UPDATE clarification SET result = '%s' WHERE clar_id = '%u';", result_string_char, clar_id);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
	
	/* reply to all or one team, according to how private byte is set */
	sprintf(sqlquery, "SELECT account_id, msg FROM clarification WHERE clar_id = '%u';", clar_id);
	sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
	sccanf(table[1 * cols + 0], "%u", &account_id);
	mbstowcs(msg_wchar, table[1 * cols + 1], 100);
	sqlite3_free_table(table);
	
	if(private_byte == 0)
	{
		sprintf(sqlquery, "SELECT ipaddress FROM user WHERE account_id = '%u';", account_id);
		sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
		serverproto_clar_reply( table[1 * cols + 0], OPSR_TEAM, clar_id, msg_wchar, result_string );
		sqlite3_free_table(table);
	}
	else if(private_byte == 1)
	{
		sprintf(sqlquery, "SELECT ipaddress FROM user WHERE account_type = '%d';", OPSR_TEAM);
		sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
		for(i=1;i<=rows;i++)
			serverproto_clar_reply( table[i * cols + 0], OPSR_TEAM, clar_id, msg_wchar, result_string );
		sqlite3_free_table(table);
	}
}

void cb_clar_sync( char *srcip, short srctype )
{

}