#include "ServerMain.h"

#include "liboojproto.h"

/* Server callback functions prototype. */
void cb_login_request( char *srcip, short srctype, wchar_t *account, char *password );
void cb_logout_request( char *srcip, short srctype, unsigned int account_id );
void cb_submission_request( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code );
void cb_submission_request_dlfin( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code );
void cb_clar_request( char *srcip, unsigned int account_id, int private_byte, wchar_t *clarmsg );
void cb_pd_request( char *srcip, unsigned int account_id, unsigned int problem_id );
void cb_run_result_notify( char *srcip, unsigned int run_id, wchar_t *result );
void cb_account_add( char *srcip, unsigned int type, wchar_t *account, char *password );
void cb_account_del( char *srcip, unsigned int account_id );
void cb_account_mod( char *srcip, unsigned int account_id, wchar_t *new_account, char *new_password );
void cb_account_update( char *srcip );
void cb_problem_add( char *srcip, unsigned int problem_id, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer );
void cb_problem_add_dlfin( char *srcip, unsigned int problem_id, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer );
void cb_problem_del( char *srcip, unsigned int problem_id );
void cb_problem_mod( char *srcip, unsigned int problem_id, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer );
void cb_problem_mod_dlfin( char *srcip, unsigned int problem_id, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer );
void cb_problem_update( char *srcip );
void cb_clar_result( char *srcip, unsigned int clar_id, int private_byte, wchar_t *result_string );


//unsigned int, short, check sprintf!!!
ServerFrame::ServerFrame(wxFrame *frame)
    : ServerGUI(frame)
{
	/* cb_submission_request() needs subdirectory to store submit files */
	system("mkdir submit_temp");
	/* create database file */
	if (sqlite3_open_v2("server_db.db3", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL)) {
       return;
    }
	/* create table SQL */
	sqlite3_exec(db, create_user, 0, 0, &errMsg);
	sqlite3_exec(db, create_problem, 0, 0, &errMsg);
	sqlite3_exec(db, create_submission, 0, 0, &errMsg);
	sqlite3_exec(db, create_clarification, 0, 0, &errMsg);
	sqlite3_exec(db, create_scoreboard, 0, 0, &errMsg);
	sqlite3_exec(db, create_judge_type, 0, 0, &errMsg);
	/* register callback functions */
	serverproto_cbreg_login_request( cb_login_request );
	serverproto_cbreg_logout_request( cb_logout_request );
	serverproto_cbreg_submission_request( cb_submission_request );
	serverproto_cbreg_submission_request_dlfin( cb_submission_request_dlfin );
	serverproto_cbreg_clar_request( cb_clar_request );
	serverproto_cbreg_pd_request( cb_pd_request );
	serverproto_cbreg_run_result_notify( cb_run_result_notify );
	serverproto_cbreg_account_add( cb_account_add );
	serverproto_cbreg_account_del( cb_account_del );
	serverproto_cbreg_account_mod( cb_account_mod );
	serverproto_cbreg_account_update( cb_account_update );
	serverproto_cbreg_problem_add( cb_problem_add );
	serverproto_cbreg_problem_add_dlfin( cb_problem_add_dlfin );
	serverproto_cbreg_problem_del( cb_problem_del );
	serverproto_cbreg_problem_mod( cb_problem_mod );
	serverproto_cbreg_problem_mod_dlfin( cb_problem_mod_dlfin );
	serverproto_cbreg_problem_update( cb_problem_update );
	serverproto_cbreg_clar_result( cb_clar_result );
}


ServerFrame::~ServerFrame()
{
	if( serverproto_active() )
		serverproto_stop_listen();
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
	char sqlquery[100];
	char account_char[20];
	char **result;
	int rows, cols;
	unsigned int account_id;
	bool is_find_acc = false, is_find_pass = false;
	
	wcstombs(account_char, account, 20);
	
	/* check account */
	sprintf(sqlquery, "SELECT account_id FROM user WHERE account = '%s';", account_char);
	sqlite3_get_table(db , sqlquery, &result , &rows, &cols, &errMsg);
	if(rows >= 1)
	{
		is_find_acc = true;
	}
	sqlite3_free_table(result);
	
	/* check both account and password */
	sprintf(sqlquery, "SELECT account_id FROM user WHERE account = '%s' and password = '%s';", account_char, password);
	sqlite3_get_table(db , sqlquery, &result , &rows, &cols, &errMsg);
	if(rows >= 1)
	{
		is_find_pass = true;
		sscanf(result[1 * rows + 0], "%u", &account_id);
		
		/* Update logged_in entity */
		sprintf(sqlquery, "UPDATE user SET account_type = '%d', ipaddress = '%s', logged_in = 'yes' WHERE account_id = '%u';", srctype, srcip, account_id);
		sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
	}
	sqlite3_free_table(result);
	
	/* login reply */
	if(!is_find_acc)
		serverproto_login_reply( srcip, srctype, LOGIN_ACC_NOTEXIST, -1);
	else if(!is_find_pass)
		serverproto_login_reply( srcip, srctype, LOGIN_PASS_WRONG, -1);
	else	
		serverproto_login_reply( srcip, srctype, LOGIN_VALID, account_id);
}

void cb_logout_request( char *srcip, short srctype, unsigned int account_id )
{
	char sqlquery[100];
	char **result;
	int rows, cols;
	bool is_find = false;
	
	/* update logged_in entity */
	sprintf(sqlquery, "SELECT account_id FROM user WHERE account_id = '%u';", account_id);
	sqlite3_get_table(db , sqlquery, &result , &rows, &cols, &errMsg);
	if(row >= 1)
	{
		sprintf(sqlquery, "UPDATE user SET logged_in = 'no' WHERE account_id = '%u';", account_id);
		sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
	}
	sqlite3_free_table(result);
	
	/* logout reply */
	if(is_find)
		serverproto_logout_reply( srcip, srctype, LOGOUT_OK );
	else
		serverproto_logout_reply( srcip, srctype, LOGOUT_FAIL );
}

//the function needs a subdirectory "submit_temp/"
void cb_submission_request( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code )
{
	char sqlquery[100] = "SELECT * FROM problem;";
	char coding_language_char[10];
	char path_code_char[30];
	int rows, cols;
	
	/* set path_code */
	sqlite3_get_table(db , sqlquery, &result , &rows, &cols, &errMsg);
	wcstombs(coding_language_char, coding_language, 10);
	sprintf(path_code_char, "submit_temp/submit%d.%s", rows + 1, coding_language_char);
	mbstowcs( *path_code, path_code_char, 30 );
	sqlite3_free_table(result);
}

void cb_submission_request_dlfin( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code )
{
	char sqlquery[100];
	char path_code_char[30];
	char coding_language_char[10];
	char **result;
	int rows, cols;
	unsigned int run_id;
	
	/* insert problem information into submission table */
	wcstombs(coding_language_char, coding_language, 10);
	wcstombs(path_code_char, path_code, 30);
	sprintf(sqlquery, "INSERT INTO submission VALUES(NULL, '%u', '%u', '%s', '%s', NULL);", account_id, problem_id, coding_language_char, path_code_char);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
	run_id = sqlite3_last_insert_rowid(db);  /* get run_id from submission table */
	
	/* send run_request to each judge */
	sprintf(sqlquery, "SELECT ipaddress FROM user WHERE account_type = '%d';", SRC_JUDGE);
	sqlite3_get_table(db , sqlquery, &result , &rows, &cols, &errMsg);
	
	for(i=1;i<=rows;i++)
	{
		serverproto_run_request(result[i * cols + 0], run_id, problem_id, coding_language, path_code);
	}
	sqlite3_free_table(result);
}

void cb_clar_request( char *srcip, unsigned int account_id, int private_byte, wchar_t *clarmsg )
{
	char sqlquery[100];
	char clarmsg_char[100];
	char **result;
	unsigned int clar_id;
	
	
	/* insert clarification info */
	wcstombs(clarmsg_char, clarmsg, 100);
	sprintf(sqlquery, "INSERT INTO clarification VALUES(NULL, '%u', '%s', NULL, '%d');", account_id, clarmsg_char, private_byte);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
	clar_id = sqlite3_last_insert_rowid(db);
	
	/* send clar_request to each judge and admin */
	sprintf(sqlquery, "SELECT ipaddress FROM user WHERE account_type = '%d' or account_type = '%d';", SRC_JUDGE, SRC_ADMIN);
	sqlite3_get_table(db , sqlquery, &result , &rows, &cols, &errMsg);
	
	for(i=1;i<=rows;i++)
	{
		serverproto_clar_request(result[i * cols + 0], clar_id, private_byte, clarmsg );
	}
	sqlite3_free_table(result);
}

void cb_pd_request( char *srcip, unsigned int account_id, unsigned int problem_id )
{
	//call problem upload
	//send problem to team
}

void cb_run_result_notify( char *srcip, unsigned int run_id, wchar_t *result )
{
	//add result to db
	//call function, transfer the result to original submit team
}

void cb_account_add( char *srcip, unsigned int type, wchar_t *account, char *password )
{
	//char sqlquery[100];
	//char account_char[20];
	//wcstombs(account_char, account, 20);
	//sprintf(sqlquery, "INSERT INTO user VALUES(NULL, '%s', '%s', '%d', '%s', 'no');", account_char, password, type, srcip);
	//sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
}

void cb_account_del( char *srcip, unsigned int account_id )
{
	//char sqlquery[100];
	//sprintf(sqlquery, "DELETE FROM user WHERE account_id = '%d';", account_id);
	//sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
}

void cb_account_mod( char *srcip, unsigned int account_id, wchar_t *new_account, char *new_password )
{
	//char sqlquery[100];
	//char new_account_char[20];
	//wcstombs(new_account_char, new_account, 20);
	//sprintf(sqlquery, "UPDATE user SET account = '%s', password = '%s' WHERE account_id = '%d';", new_account_char, new_password, account_id);
	//sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
}

void cb_account_update( char *srcip )
{
	//serverproto_account_info
}

//admin below
void cb_problem_add( char *srcip, unsigned int problem_id, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer )
{
}

void cb_problem_add_dlfin( char *srcip, unsigned int problem_id, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer )
{
}

void cb_problem_del( char *srcip, unsigned int problem_id )
{
}

void cb_problem_mod( char *srcip, unsigned int problem_id, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer )
{
}

void cb_problem_mod_dlfin( char *srcip, unsigned int problem_id, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer )
{
}

void cb_problem_update( char *srcip )
{
}

void cb_clar_result( char *srcip, unsigned int clar_id, int private_byte, wchar_t *result_string )
{
	char sqlquery[100];
	char result_string_char[100];
	char **table;
	int rows, cols, i;
	unsigned int account_id;
	wchar_t msg_wchar[100];
	
	/* update clarification table */
	wcstombs(result_string_char, result_string, 100);
	sprintf(sqlquery, "UPDATE clarification SET result = '%s' WHERE clar_id = '%u';", result_string_char, clar_id);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
	
	/* send clar_reply to team */
	sprintf(sqlquery, "SELECT account_id, msg FROM clarification WHERE clar_id = '%u';", clar_id);
	sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
	sccanf(result[1 * cols + 1], "%u", &account_id);
	mbstowcs(msg_wchar, result[1 * cols + 1], 100);
	sqlite3_free_table(table);
	
	if(private_byte == 1)
	{
		sprintf(sqlquery, "SELECT ipaddress FROM user WHERE account_id = '%u';", account_id);
		sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
		serverproto_clar_reply( table[1 * cols + 0], clar_id, msg_wchar, result_string );
		sqlite3_free_table(table);
	}
	else
	{
		sprintf(sqlquery, "SELECT ipaddress FROM user WHERE account_type = '%d';", SRC_TEAM);
		sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
		for(i=1;i<=rows;i++)
			serverproto_clar_reply( table[i * cols + 0], clar_id, msg_wchar, result_string );
		sqlite3_free_table(table);
	}
}