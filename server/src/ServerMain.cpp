#include "ServerMain.h"

BEGIN_EVENT_TABLE(ServerFrame, wxFrame)
    EVT_TIMER(-1, ServerFrame::OnTimerEvent)
END_EVENT_TABLE()

/* server callback functions prototype. */
void callback_login_request( char *srcip, short srctype, wchar_t *account, char *password );
void callback_logout_request( char *srcip, short srctype, unsigned int account_id );
void callback_password_change( char *srcip, short srctype, unsigned int account_id, char *old_password, char *new_password );

void callback_timer_sync( char *srcip, short srctype );
void callback_contest_state_sync( char *srcip, short srctype );
void callback_admin_timer_set( char *srcip, unsigned int hours, unsigned int minutes, unsigned int seconds );
void callback_admin_contest_start( char *srcip );
void callback_admin_contest_stop( char *srcip );

void callback_submission_request( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code );
void callback_submission_request_dlfin( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code );

void callback_pd_request( char *srcip, unsigned int account_id, unsigned int problem_id );
void callback_sb_sync( char *srcip, short srctype );
void callback_run_sync( char *srcip );
void callback_run_result_notify( char *srcip, unsigned int run_id, wchar_t *result );
void callback_trun_sync( char *srcip, unsigned int account_id );

void callback_take_run( char *srcip, unsigned int run_id );
void callback_account_add( char *srcip, unsigned int type, wchar_t *account, char *password );
void callback_account_del( char *srcip, unsigned int account_id );
void callback_account_mod( char *srcip, unsigned int account_id, wchar_t *new_account, char *new_password );
void callback_account_sync( char *srcip );

void callback_problem_add( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer );
void callback_problem_add_dlfin( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer );
void callback_problem_del( char *srcip, unsigned int problem_id );
void callback_problem_mod( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer );
void callback_problem_mod_dlfin( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer );
void callback_problem_sync( char *srcip, short srctype );

void callback_clar_request( char *srcip, unsigned int account_id, int private_byte, wchar_t *clarmsg );
void callback_clar_result( char *srcip, unsigned int clar_id, int private_byte, wchar_t *result_string );
void callback_clar_sync( char *destip, short srctype );

/* database tool function */
void serverdb_contest( int (*serverproto)(char *destip, short desttype), short desttype );
void serverdb_problem_change( unsigned int FUNC, unsigned int problem_id, wchar_t *problem_name );
void serverdb_clar_request( short desttype, unsigned int clar_id, int private_byte, wchar_t *clarmsg );
void serverdb_sb_update( short desttype, unsigned int upd_acc_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time );


/* global variables */
bool is_contest_stop;	/* contest_state */
sqlite3 *db;	/* sqlite variable */
enum FUNC_NAME{PROBLEM_CHANGE_ADD, PROBLEM_CHANGE_DEL, PROBLEM_CHANGE_MOD};	/* Database tool function parameter */

/* timer */
bool is_timer_set;
wxTimer m_timer;
unsigned int m_timeleft;

ServerFrame::ServerFrame(wxFrame *frame)
    : ServerGUI(frame), m_timer(this)
{
	/* "CREATE TABLE" SQL */
	char create_user[] = "CREATE TABLE user("
		"account_id   INTEGER PRIMARY KEY,"
		"account      VARCHAR(25),"
		"password     VARCHAR(25),"
		"account_type INTEGER,"
		"ipaddress    VARCHAR(20),"
		"logged_in    VARCHAR(5));";

	char create_problem[] = "CREATE TABLE problem("
		"problem_id					INTEGER PRIMARY KEY,"
		"problem_name				VARCHAR(20),"
		"path_description			VARCHAR(50),"
		"correct_input_filename     VARCHAR(50),"
		"correct_output_filename    VARCHAR(50),"
		"time_limit					INTEGER);";
	char create_submission[] = "CREATE TABLE submission("
		"run_id      INTEGER PRIMARY KEY,"
		"account_id  INTEGER,"
		"problem_id  INTEGER,"
		"lang        VARCHAR(10),"
		"path_code	 VARCHAR(50),"
		"taken		 VARCHAR(5),"
		"judge_result VARCHAR(25),"
		"FOREIGN KEY(account_id) REFERENCES user(account_id),"
		"FOREIGN KEY(problem_id) REFERENCES problem(problem_id));";

	char create_clarification[] = "CREATE TABLE clarification("
		"clar_id       INTEGER PRIMARY KEY,"
		"account_id    INTEGER,"
		"msg           VARCHAR(100),"
		"result        VAECHAR(100),"
		"private_byte  INTEGER,"
		"FOREIGN KEY(account_id) REFERENCES user(account_id));";

	char create_scoreboard[] = "CREATE TABLE scoreboard("
		"score_id		INTEGER PRIMARY KEY,"
		"account_id		INTEGER,"
		"time			INTEGER,"
		"accept_count	INTEGER,"
		"FOREIGN KEY(score_id) REFERENCES user(score_id));";
	char *errMsg = NULL;
	
	/* timer variable */
	m_timeleft = 0;
	is_timer_set = false;
	
	/* create subdirectory to store files */
	system( "mkdir submits" );
	system( "mkdir problems" );

	/* set contest state */
	is_contest_stop = true;
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

	/* register callback functions */
	serverproto_cbreg_login_request( callback_login_request );
	serverproto_cbreg_logout_request( callback_logout_request );
	serverproto_cbreg_password_change( callback_password_change );
	serverproto_cbreg_timer_sync( callback_timer_sync );
	serverproto_cbreg_contest_state_sync( callback_contest_state_sync );
	serverproto_cbreg_admin_timer_set( callback_admin_timer_set );
	serverproto_cbreg_admin_contest_start( callback_admin_contest_start );
	serverproto_cbreg_admin_contest_stop( callback_admin_contest_stop );
	serverproto_cbreg_submission_request( callback_submission_request );
	serverproto_cbreg_submission_request_dlfin( callback_submission_request_dlfin );
	serverproto_cbreg_pd_request( callback_pd_request );
	serverproto_cbreg_sb_sync( callback_sb_sync );
	serverproto_cbreg_run_result_notify( callback_run_result_notify );
	serverproto_cbreg_run_sync( callback_run_sync );
	serverproto_cbreg_trun_sync( callback_trun_sync );
	serverproto_cbreg_take_run( callback_take_run );
	serverproto_cbreg_account_add( callback_account_add );
	serverproto_cbreg_account_del( callback_account_del );
	serverproto_cbreg_account_mod( callback_account_mod );
	serverproto_cbreg_account_sync( callback_account_sync );
	serverproto_cbreg_problem_add( callback_problem_add );
	serverproto_cbreg_problem_add_dlfin( callback_problem_add_dlfin );
	serverproto_cbreg_problem_del( callback_problem_del );
	serverproto_cbreg_problem_mod( callback_problem_mod );
	serverproto_cbreg_problem_mod_dlfin( callback_problem_mod_dlfin );
	serverproto_cbreg_problem_sync( callback_problem_sync );
	serverproto_cbreg_tsclar_request( callback_clar_request );
	serverproto_cbreg_clar_result( callback_clar_result );
	serverproto_cbreg_clar_sync( callback_clar_sync );
}


ServerFrame::~ServerFrame()
{
	if( serverproto_active() )
		serverproto_stop_listen();
	/* close database */
	sqlite3_close(db);
}

void ServerFrame::OnButtonClickStart( wxCommandEvent& event )
{
	char sqlquery[100], **table, *errMsg;
	int rows, cols, i;

	/* start listen socket */
	if( serverproto_listen("0.0.0.0") < 0 )
	{
#if SERVER_DBG > 0
		printf("[ServerFrame::OnButtonClickStart()] serverproto_listen() call failed.\n");
#endif
		wxMessageBox( wxT("Server start failed.\nStage: start listen socket."), wxT("Fatal Error"), wxOK|wxICON_ERROR, this );
	}

	/* set wxStaticText label */
	StaticTextStatus->SetLabel( wxT("NOW Running") );

	/* if admin01 not exist, add an admin01 account */
	sprintf(sqlquery, "SELECT * FROM user WHERE account = 'admin01';");
	sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
	if(rows == 0)
	{
		sprintf(sqlquery, "INSERT INTO user VALUES(NULL, 'admin01', 'admin01', '%d', NULL, 'no');", OPSR_ADMIN);
		sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
	}
	sqlite3_free_table(table);
}

void ServerFrame::OnButtonClickStop( wxCommandEvent& event )
{
	if( serverproto_active() )
	{
		serverproto_stop_listen();
	}
	
	StaticTextStatus->SetLabel( wxT("Not Running") );
}

void ServerFrame::OnTimerEvent(wxTimerEvent &event){
	if(is_timer_set == true)
	{
		m_timeleft--;
		if( m_timeleft <= 0 )
		{
			m_timer.Stop();
			is_contest_stop = true;
		}
	}
}

/* Server callback function definition. */
void callback_login_request( char *srcip, short srctype, wchar_t *account, char *password )
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

void callback_logout_request( char *srcip, short srctype, unsigned int account_id )
{
	char sqlquery[100], **table, *errMsg = NULL;
	int rows, cols;

	/* mark the account as logged out */
	sprintf(sqlquery, "SELECT logged_in FROM user WHERE account_id = '%u';", account_id);
	sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
	if(rows >= 1)	/* LOGOUT_OK */
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

void callback_password_change( char *srcip, short srctype, unsigned int account_id, char *old_password, char *new_password )
{
	char sqlquery[100], **table, *errMsg = NULL;
	int rows, cols;

	sprintf(sqlquery, "SELECT password FROM user WHERE account_id = '%u';", account_id);
	sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
	if(rows >= 1)	/* PASSWD_SUCCESS */
	{
		if(strcmp(table[1 * cols + 0], old_password) == 0)	/* PASSWD_SUCCESS */
		{
			/* store the changed password into database and give the client a reply */
			sprintf(sqlquery, "UPDATE user SET password = '%s' WHERE account_id = '%u';", new_password, account_id);
			sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
			serverproto_password_change_reply( srcip, srctype, PASSWD_SUCCESS );
		}
		else	/* PASSWD_MISMATCH */
		{
			serverproto_password_change_reply( srcip, srctype, PASSWD_MISMATCH );
		}
	}
	else	/* PASSWD_FAIL */
	{
		/* account not exist */
		serverproto_password_change_reply( srcip, srctype, PASSWD_INVALID );
	}
	sqlite3_free_table(table);
}

void callback_timer_sync( char *srcip, short srctype )
{
	serverproto_timer_set( srcip, srctype, m_timeleft / 60 / 60, (m_timeleft / 60) % 60, m_timeleft % 60 );
}

void callback_contest_state_sync( char *srcip, short srctype )
{
	if(is_contest_stop)
	{
		serverproto_contest_stop( srcip, srctype );
	}
	else
	{
		serverproto_contest_start( srcip, srctype );
	}
}

void callback_admin_timer_set( char *srcip, unsigned int hours, unsigned int minutes, unsigned int seconds )
{
	char sqlquery[100], **table, *errMsg;
	int rows, cols, i;
	unsigned int account_type;
	
	/* set timer */
	
	m_timeleft = hours * 360 + minutes * 60 + seconds;
	
	sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
	sprintf(sqlquery, "SELECT account_type, ipaddress FROM user WHERE logged_in = 'yes';");
	for(i=1;i<=rows;i++)
	{
		sscanf(table[i * cols + 0], "%u", &account_type);
		serverproto_timer_set( table[i * cols + 1], account_type, hours, minutes, seconds );
	}
	sqlite3_free_table(table);
}

void callback_admin_contest_start( char *srcip )
{
	m_timer.Start(1000);
	is_contest_stop = false;
	serverdb_contest( serverproto_contest_start, OPSR_JUDGE );
	serverdb_contest( serverproto_contest_start, OPSR_TEAM );
}

void callback_admin_contest_stop( char *srcip )
{
	m_timer.Stop();
	is_contest_stop = true;
	serverdb_contest( serverproto_contest_stop, OPSR_JUDGE );
	serverdb_contest( serverproto_contest_stop, OPSR_TEAM );
}

/* the function needs a subdirectory "submits/" */
void callback_submission_request( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code )
{
	char sqlquery[100], coding_language_char[10], path_code_char[30], **table, *errMsg = NULL;
	int rows, cols;

	/* set path_code */
	sprintf(sqlquery, "SELECT * FROM submission;");
	sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
	wcstombs(coding_language_char, coding_language, 10);
	sprintf(path_code_char, "submits/submit%d.%s", rows + 1, coding_language_char);
	mbstowcs(*path_code, path_code_char, 30);
	sqlite3_free_table(table);
}

void callback_submission_request_dlfin( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code )
{
	char sqlquery[100], path_code_char[30], coding_language_char[10];
	char **table, *errMsg = NULL;
	int rows, cols, i;
	unsigned int run_id;

	/* record those information into db */
	wcstombs(coding_language_char, coding_language, 10);
	wcstombs(path_code_char, path_code, 30);
	sprintf(sqlquery, "INSERT INTO submission VALUES(NULL, '%u', '%u', '%s', '%s', 'no', 'queued');", account_id, problem_id, coding_language_char, path_code_char);
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

	serverproto_run_reply( srcip, run_id, problem_id, L"queued" );
}

void callback_pd_request( char *srcip, unsigned int account_id, unsigned int problem_id )
{
	char sqlquery[100], path_description_char[50], **table, *errMsg = NULL;
	wchar_t path_description_wchar[50];
	int rows, cols;

	/* upload the corresponding problem pack to user  */
	sprintf(sqlquery, "SELECT path_description FROM problem WHERE problem_id = '%u';", problem_id);
	sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
	if(rows >= 1)
	{
		sscanf(path_description_char, "%s", table[1 * cols + 0]);
		mbstowcs(path_description_wchar, path_description_char, 50);
		serverproto_problem_upload( srcip, path_description_wchar );
	}
	sqlite3_free_table(table);
}

void callback_sb_sync( char *srcip, short srctype )
{
	char sqlquery[100], **table, *errMsg, **table2, account[25];
	int rows, cols, i, rows2, cols2, j;
	unsigned int account_id, new_time, new_accept_count, account_type;
	wchar_t new_account_wchar[25];
	
	sprintf(sqlquery, "SELECT account_id, time, accept_count FROM scoreboard;");
	sqlite3_get_table(db, sqlquery, &table, &rows, &cols, &errMsg);
	for(i=1;i<=rows;i++)
	{
		sscanf(table[i * cols + 0], "%u", &account_id);
		sscanf(table[i * cols + 1], "%u", &new_time);
		sscanf(table[i * cols + 2], "%u", &new_accept_count);
		sprintf(sqlquery, "SELECT account, account_type FROM user WHERE account_id = '%u';", account_id);
		sqlite3_get_table(db, sqlquery, &table2, &rows2, &cols2, &errMsg);
		if(rows2 >= 1)
		{
			mbstowcs(new_account_wchar, table[1 * cols2 + 0], 25);
			sscanf(table2[1 * cols2 + 0], "%u", &account_type);
			serverproto_sb_update( srcip, account_type, account_id, new_account_wchar, new_accept_count, new_time );
		}
		sqlite3_free_table(table2);

	}
	sqlite3_free_table(table);
}

void callback_run_result_notify( char *srcip, unsigned int run_id, wchar_t *result )
{
	char sqlquery[100], result_char[25], destip[20], **table, *errMsg = NULL;
	int rows, cols;
	unsigned int problem_id, account_id, accept_count;

	/* record result information into db */
	wcstombs(result_char, result, 25);
 	sprintf(sqlquery, "UPDATE submission SET judge_result = '%s' WHERE run_id = '%u';", result_char, run_id);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
	
	/* get account_id and problem_id */
	sprintf(sqlquery, "SELECT account_id, problem_id FROM submission WHERE run_id = '%u';", run_id);
	sqlite3_get_table(db, sqlquery, &table, &rows, &cols, &errMsg);
	if(rows >= 1)
	{
		sscanf(table[1 * cols + 0], "%u", &account_id);
		sscanf(table[1 * cols + 1], "%u", &problem_id);
	}
	sqlite3_free_table(table);
	
	/* update accept_count in scoreboard if result = "YES" */
	if(strcmp( result_char, "YES" ) == 0)	
	{
		/* get accept_count */
		sprintf(sqlquery, "SELECT accept_count FROM scoreboard WHERE account_id = '%u';", account_id);
		sqlite3_get_table(db, sqlquery, &table, &rows, &cols, &errMsg);
		if(rows >=1)
		{
			sscanf(table[1 * cols + 0], "%u", &accept_count);
		}
		sqlite3_free_table(table);
		
		/* update accept_count */
		sprintf(sqlquery, "UPDATE scoreboard SET accept_count = '%u' WHERE = account_id = '%u';", accept_count + 1, account_id);
		sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
	}
	
	/* redirect the result to corresponding team */
	sprintf(sqlquery, "SELECT ipaddress FROM user WHERE account_id = '%u';", account_id);
	sqlite3_get_table(db, sqlquery, &table, &rows, &cols, &errMsg);
	if(rows >= 1)
	{
		sscanf(table[1 * cols + 0], "%s", destip);
	}
	sqlite3_free_table(table);
	serverproto_run_reply( destip, run_id, problem_id, result );
}

void callback_trun_sync( char *srcip, unsigned int account_id )
{
	char sqlquery[100], **table, *errMsg = NULL;
	int rows, cols, i;
	unsigned int run_id, problem_id;
	wchar_t lang_wchar[10], path_code_wchar[50];

	/* update all runs */
	sprintf(sqlquery, "SELECT run_id, problem_id, lang, path_code FROM submission WHERE account_id = '%u';");
	sqlite3_get_table(db, sqlquery, &table, &rows, &cols, &errMsg);
	for(i=1;i<=rows;i++)
	{
		sscanf(table[i * cols + 0], "%u", &run_id);
		sscanf(table[i * cols + 1], "%u", &problem_id);
		mbstowcs(lang_wchar, table[i * cols + 2], 10);
		mbstowcs(path_code_wchar, table[i * cols + 3], 50);
		serverproto_run_request(srcip, run_id, problem_id, lang_wchar, path_code_wchar);
	}
	sqlite3_free_table(table);
}

void callback_run_sync( char *srcip)
{
	char sqlquery[100], **table, *errMsg = NULL;
	int rows, cols, i;
	unsigned int run_id, problem_id;
	wchar_t lang_wchar[10], path_code_wchar[50];

	/* update all runs belong to that team to the reqesting client */
	sprintf(sqlquery, "SELECT run_id, problem_id, lang, path_code FROM submission;");
	sqlite3_get_table(db, sqlquery, &table, &rows, &cols, &errMsg);
	for(i=1;i<=rows;i++)
	{
		sscanf(table[i * cols + 0], "%u", &run_id);
		sscanf(table[i * cols + 1], "%u", &problem_id);
		mbstowcs(lang_wchar, table[i * cols + 2], 10);
		mbstowcs(path_code_wchar, table[i * cols + 3], 50);
		serverproto_run_request(srcip, run_id, problem_id, lang_wchar, path_code_wchar);
	}
	sqlite3_free_table(table);
}

void callback_take_run( char *srcip, unsigned int run_id )
{
	char sqlquery[100], **table, *errMsg;
	int rows, cols, i;

	/* mark the judge as taken */
	sprintf(sqlquery, "UPDATE submission SET taken = 'yes' WHERE run_id = '%u';", run_id);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);

	/* notify judges about take result */
	serverproto_take_result( srcip, run_id, TAKE_SUCCESS );
	sprintf(sqlquery, "SELECT ipaddress FROM user WHERE account_type = '%d' and ipaddress <> '%s';", OPSR_JUDGE, srcip);
	sqlite3_get_table(db, sqlquery, &table, &rows, &cols, &errMsg);
	for(i=1;i<=rows;i++)
	{
		serverproto_take_result( table[i * cols + 1], run_id, TAKE_FAIL );
	}
	sqlite3_free_table(table);
}

void callback_account_add( char *srcip, unsigned int type, wchar_t *account, char *password )
{
	char sqlquery[100], account_char[25], *errMsg = NULL;
	unsigned int account_id;

	/* record account and scoreboard information into db */
	wcstombs(account_char, account, 25);
	sprintf(sqlquery, "INSERT INTO user VALUES(NULL, '%s', '%s', '%u', NULL, 'no');", account_char, password, type);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
	account_id = sqlite3_last_insert_rowid(db);
	sprintf(sqlquery, "INSERT INTO scoreboard VALUES(NULL, '%u', '0', '0');", account_id);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);

	
	/* updates account listing to administrator */
	serverproto_account_update( srcip, account_id, type, account );
	
	/* notify team and admin client about scoreboard updates */
	serverdb_sb_update( OPSR_TEAM, account_id, account, 0, 0 );
	serverdb_sb_update( OPSR_ADMIN, account_id, account, 0, 0 );
}

void callback_account_del( char *srcip, unsigned int account_id )
{
	char sqlquery[100], **table, *errMsg = NULL;

	/* remove the account from db and remove everything related to that account from the system */
	sprintf(sqlquery, "DELETE FROM user WHERE account_id = '%u';", account_id);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);

	/* updates account listing to administrator */
	serverproto_account_remove( srcip, account_id );

	/* notify team and admin client about scoreboard updates */
	//serverdb_sb_update( OPSR_TEAM, account_id, account, 0, 0 );
	//serverdb_sb_update( OPSR_ADMIN, account_id, account, 0, 0 );
}

void callback_account_mod( char *srcip, unsigned int account_id, wchar_t *new_account, char *new_password )
{
	char sqlquery[100], **table, *errMsg = NULL;
	char new_account_char[25];
	int rows, cols;
	unsigned int account_type, accept_count, time;

	/* modify the record in db */
	wcstombs(new_account_char, new_account, 25);
	if(new_password == NULL)	/* update only account */
	{
		sprintf(sqlquery, "UPDATE user SET account = '%s' WHERE account_id = '%u';", new_account_char, new_password, account_id);
	}
	else	/* update both account and password */
	{
		sprintf(sqlquery, "UPDATE user SET account = '%s', password = '%s' WHERE account_id = '%u';", new_account_char, new_password, account_id);
	}
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
	
	/* updates account to administrator */
	sprintf(sqlquery, "SELECT account_type FROM user WHERE account_id = '%u';", account_id);
	sqlite3_get_table(db, sqlquery, &table, &rows, &cols, &errMsg);
	if(rows >= 1)
	{
		sscanf(table[1 * cols + 0], "%u", &account_type);
		serverproto_account_update( srcip, account_id, account_type, new_account );
	}
	sqlite3_free_table(table);
	
	/* notify team and admin client about scoreboard updates */
	sprintf(sqlquery, "SELECT accept_count, time FROM scoreboard WHERE account_id = '%u';", account_id);
	if(rows >= 1)
	{
		sscanf(table[1 * cols + 0], "%u", &accept_count);
		sscanf(table[1 * cols + 1], "%u", &time);
		serverdb_sb_update( OPSR_TEAM, account_id, new_account, accept_count, time );
		serverdb_sb_update( OPSR_ADMIN, account_id, new_account, accept_count, time );
	}
}

void callback_account_sync( char *srcip )
{
	/* updates account listing to administrator */
	char sqlquery[100], acc_char[25], **table, *errMsg;
	int rows, cols, i;
	unsigned int account_id, account_type;
	wchar_t acc_wchar[25];

	sprintf(sqlquery, "SELECT account_id, account, account_type FROM user;");
	sqlite3_get_table(db, sqlquery, &table, &rows, &cols, &errMsg);
	for(i=1;i<=rows;i++)
	{
		sscanf(table[i * cols + 0], "%u", &account_id);
		sscanf(table[i * cols + 1], "%s", acc_char);
		sscanf(table[i * cols + 2], "%u", &account_type);
		mbstowcs(acc_wchar, acc_char, 25);
		serverproto_account_update(srcip, account_id, account_type, acc_wchar);
	}
	sqlite3_free_table(table);
}

/* the function needs a subdirectory "problems/" */
void callback_problem_add( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer )
{
	char sqlquery[100];
	char path_description_char[50], path_input_char[50], path_answer_char[50];
	
	/* edit path names */
	*path_description = (wchar_t *) malloc( 50 * sizeof(wchar_t) );
	sprintf(path_description_char, "problems/path_descr%u.pdf", problem_id);
	mbstowcs(*path_description, path_description_char, 50);
	wprintf(L"path = %ls\n", *path_description);
	
	*path_input = (wchar_t *) malloc( 50 * sizeof(wchar_t) );
	sprintf(path_input_char, "problems/p%u_in.txt", problem_id);
	mbstowcs(*path_input, path_input_char, 50);
	wprintf(L"input = %ls\n", *path_input);
	
	*path_answer = (wchar_t *) malloc( 50 * sizeof(wchar_t) );
	sprintf(path_answer_char, "problems/p%u_out.txt", problem_id);
	mbstowcs(*path_answer, path_answer_char, 50);
	wprintf(L"ans = %ls\n", *path_answer);
}

void callback_problem_add_dlfin( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer )
{
	char sqlquery[100], *errMsg = NULL;
	char problem_name_char[20], path_description_char[50], path_input_char[50], path_answer_char[50];
	
	printf("download finish start\n");
	
	/* record the new problem into db */
	wcstombs(problem_name_char, problem_name, 20);
	wcstombs(path_description_char, path_description, 50);
	wcstombs(path_input_char, path_input, 50);
	wcstombs(path_answer_char, path_answer, 50);
	sprintf(sqlquery, "INSERT INTO problem VALUES(NULL, '%s', '%s', '%s', '%s', '%u');", problem_name_char, path_description_char, path_input_char, path_answer_char, time_limit);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);

	/* reply function */
	serverproto_problem_update( srcip, OPSR_ADMIN, problem_id, problem_name, time_limit, path_description, path_input, path_answer );
	serverdb_problem_change(PROBLEM_CHANGE_ADD, problem_id, problem_name);
}

void callback_problem_del( char *srcip, unsigned int problem_id )
{
	char sqlquery[100], *errMsg;
	/* remove the problem from db and delete correspond data on disk */
	sprintf(sqlquery, "DELETE FROM problem WHERE problem_id = '%u';", problem_id);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);

	/* reply function */
	serverproto_problem_remove( srcip, OPSR_ADMIN, problem_id );
	serverdb_problem_change(PROBLEM_CHANGE_DEL, problem_id, NULL);
}

void callback_problem_mod( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer )
{
	/* do the same thing as callback_problem_add(), just copy and paste */
	char sqlquery[100];
	char path_description_char[50], path_input_char[50], path_answer_char[50];

	/* edit path names */
	sprintf(path_description_char, "problems/path_descr%u.pdf", problem_id);
	mbstowcs(*path_description, path_description_char, 50);

	sprintf(path_input_char, "problems/p%u_in.txt", problem_id);
	mbstowcs(*path_input, path_input_char, 50);

	sprintf(path_answer_char, "problems/p%u_out.txt", problem_id);
	mbstowcs(*path_answer, path_answer_char, 50);
}

void callback_problem_mod_dlfin( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer )
{
	/* do the same thing as callback_problem_add_dlfin(), except for serverdb_problem_change parameter */
	char sqlquery[100], *errMsg = NULL;
	char problem_name_char[20], path_description_char[50], path_input_char[50], path_answer_char[50];

	/* record the new problem into db */
	wcstombs(problem_name_char, problem_name, 20);
	wcstombs(path_description_char, path_description, 50);
	wcstombs(path_input_char, path_input, 50);
	wcstombs(path_answer_char, path_answer, 50);
	sprintf(sqlquery, "INSERT INTO problem VALUES(NULL, '%s', '%s', '%s', '%s', '%u');", problem_name_char, path_description_char, path_input_char, path_answer_char, time_limit);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);

	/* reply function */
	serverproto_problem_update( srcip, OPSR_ADMIN, problem_id, problem_name, time_limit, path_description, path_input, path_answer );
	serverdb_problem_change(PROBLEM_CHANGE_MOD, problem_id, problem_name);
}

void callback_problem_sync( char *srcip, short srctype )
{
	char sqlquery[100], **table, *errMsg;
	int rows, cols, i;
	char problem_name_char[20], path_description_char[50], correct_input_filename_char[50], correct_output_filename_char[50];
	wchar_t problem_name_wchar[20], path_description_wchar[50], correct_input_filename_wchar[50], correct_output_filename_wchar[50];
	unsigned int problem_id, time_limit;

	sprintf(sqlquery, "SELECT * FROM problem");
	sqlite3_get_table(db, sqlquery, &table, &rows, &cols, &errMsg);

	for(i=1;i<=rows;i++)
	{
		sscanf(table[i * cols + 0], "%u", &problem_id);
		sscanf(table[i * cols + 1], "%s", problem_name_char);
		sscanf(table[i * cols + 2], "%s", path_description_char);
		sscanf(table[i * cols + 3], "%s", correct_input_filename_char);
		sscanf(table[i * cols + 4], "%s", correct_output_filename_char);
		sscanf(table[i * cols + 5], "%u", &time_limit);

		mbstowcs(problem_name_wchar, problem_name_char, 20);
		mbstowcs(path_description_wchar, path_description_char, 50);
		mbstowcs(correct_input_filename_wchar, correct_input_filename_char, 50);
		mbstowcs(correct_output_filename_wchar, correct_output_filename_char, 50);

		serverproto_problem_update( srcip, srctype, problem_id, problem_name_wchar, time_limit, path_description_wchar, correct_input_filename_wchar, correct_output_filename_wchar );
	}
	sqlite3_free_table(table);
}

void callback_clar_request( char *srcip, unsigned int account_id, int private_byte, wchar_t *clarmsg )
{
	char sqlquery[100], *errMsg = NULL, **table, clarmsg_char[100];
	unsigned int clar_id;
	int rows, cols;

	/* record clarification information into db */
	wcstombs(clarmsg_char, clarmsg, 100);
	sprintf(sqlquery, "INSERT INTO clarification VALUES(NULL, '%u', '%s', NULL, '%d');", account_id, clarmsg_char, private_byte);
	sqlite3_exec(db, sqlquery, 0, 0, &errMsg);
	clar_id = sqlite3_last_insert_rowid(db);


	/* redirect the request to admins */
	serverdb_clar_request(OPSR_ADMIN, clar_id, private_byte, clarmsg);

	/* redirect the request to judges */
	serverdb_clar_request(OPSR_JUDGE, clar_id, private_byte, clarmsg);
	
	/* reply team client */
	serverproto_clar_reply( srcip, OPSR_TEAM, clar_id, clarmsg, L"Clarifying...." );
}

void callback_clar_result( char *srcip, unsigned int clar_id, int private_byte, wchar_t *result_string )
{
	char sqlquery[100], **table, *errMsg = NULL, result_string_char[100];
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
	if(rows >= 1)
	{
		sscanf(table[1 * cols + 0], "%u", &account_id);
		mbstowcs(msg_wchar, table[1 * cols + 1], 100);
	}
	sqlite3_free_table(table);

	if(private_byte == 1)
	{
		sprintf(sqlquery, "SELECT ipaddress FROM user WHERE account_id = '%u';", account_id);
		sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
		if(rows >= 1)
		{
			serverproto_clar_reply( table[1 * cols + 0], OPSR_TEAM, clar_id, msg_wchar, result_string );
		}
		sqlite3_free_table(table);
	}
	else if(private_byte == 0)
	{
		sprintf(sqlquery, "SELECT ipaddress FROM user WHERE account_type = '%d';", OPSR_TEAM);
		sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
		for(i=1;i<=rows;i++)
			serverproto_clar_reply( table[i * cols + 0], OPSR_TEAM, clar_id, msg_wchar, result_string );
		sqlite3_free_table(table);
	}
}

void callback_clar_sync( char *srcip, short srctype )
{
	char sqlquery[100], **table, *errMsg = NULL;
	int rows, cols, i, private_byte;
	unsigned int clar_id;
	wchar_t msg_wchar[100];

	sprintf(sqlquery, "SELECT clar_id, msg, private_byte FROM clarification WHERE result IS NULL;");
	sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
	for(i=1;i<=rows;i++)
	{
		sscanf(table[i * cols + 0], "%u", &clar_id);
		mbstowcs(msg_wchar, table[i * cols + 1], 100);
		sscanf(table[i * cols + 2], "%d", &private_byte);
		serverproto_clar_request( srcip, srctype, clar_id, private_byte, msg_wchar);
	}
	sqlite3_free_table(table);
}


/* database tool function below */
/* sets contest state for clients */
void serverdb_contest( int (*serverproto)(char *destip, short desttype), short desttype )
{
	char sqlquery[100], **table, *errMsg = NULL, destip[20];
	int rows, cols, i;

	sprintf(sqlquery, "SELECT ipaddress FROM user WHERE account_type = '%h';", desttype);
	sqlite3_get_table(db, sqlquery, &table, &rows, &cols, &errMsg);
	for(i=1;i<=rows;i++)
	{
		(*serverproto)( table[i * cols + 0], desttype );
	}
	sqlite3_free_table(table);
}

/* notify all team clients about changes on a problem */
void serverdb_problem_change( unsigned int FUNC, unsigned int problem_id, wchar_t *problem_name )
{
	char sqlquery[100], **table, *errMsg;
	int rows, cols, i;

	sprintf(sqlquery, "SELECT ipaddress FROM user WHERE account_type = '%d';", OPSR_TEAM);
	sqlite3_get_table(db, sqlquery, &table, &rows, &cols, &errMsg);
	for(i=1;i<=rows;i++)
	{
		/* table[i * cols + 0] is ipaddress, (char *) */
		if(FUNC == PROBLEM_CHANGE_ADD)
			serverproto_problem_change_add( table[i * cols + 0], problem_id, problem_name );
		else if(FUNC == PROBLEM_CHANGE_DEL)
			serverproto_problem_change_del( table[i * cols + 0], problem_id );
		else if(FUNC == PROBLEM_CHANGE_MOD)
			serverproto_problem_change_mod( table[i * cols + 0], problem_id, problem_name );
	}
	sqlite3_free_table(table);
}

/* request clarification to admin and judge clients */
void serverdb_clar_request( short desttype, unsigned int clar_id, int private_byte, wchar_t *clarmsg )
{
	char sqlquery[100], **table, *errMsg = NULL, destip[20];
	int rows, cols, i;

	sprintf(sqlquery, "SELECT ipaddress FROM user WHERE account_type = '%h';", desttype);
	sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
	for(i=1;i<=rows;i++)
	{
		sscanf(table[i * cols + 0], "%s",  destip);
		serverproto_clar_request(destip, desttype, clar_id, private_byte, clarmsg);
	}
	sqlite3_free_table(table);
}

void serverdb_sb_update( short desttype, unsigned int upd_acc_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time )
{
	char sqlquery[100], **table, *errMsg;
	int rows, cols, i;

	sprintf(sqlquery, "SELECT ipaddress FROM user WHERE account_type = '%h';", desttype);
	sqlite3_get_table(db , sqlquery, &table , &rows, &cols, &errMsg);
	for(i=1;i<=rows;i++)
	{
		serverproto_sb_update( table[i * cols + 1], desttype, upd_acc_id, new_account, new_accept_count, new_time );
	}

	sqlite3_free_table(table);
}