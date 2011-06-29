#include "ServerMain.h"

#include "db_tool.h"

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_LOCAL_EVENT_TYPE( wxEVT_CALL_TIMER, 7777 )
END_DECLARE_EVENT_TYPES()
DEFINE_EVENT_TYPE( wxEVT_CALL_TIMER )

#define EVT_CALL_TIMER( id, fn )\
    DECLARE_EVENT_TABLE_ENTRY( \
        wxEVT_CALL_TIMER, id, wxID_ANY, \
        (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent( wxCommandEventFunction, &fn ), \
        (wxObject*)NULL\
    ),

BEGIN_EVENT_TABLE(ServerFrame, wxFrame)
    EVT_TIMER(-1, ServerFrame::OnTimerEvent)
	EVT_CALL_TIMER(wxID_ANY, ServerFrame::TimerCall)
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
void callback_tp_sync( char *srcip );

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
void serverdb_contest( int (*serverproto)(const char *destip, short desttype), short desttype );
void serverdb_problem_change( unsigned int FUNC, unsigned int problem_id, wchar_t *problem_name );
void serverdb_clar_request( short desttype, unsigned int clar_id, unsigned int account_id, int private_byte, wchar_t *clarmsg );
void serverdb_sb_update( short desttype, unsigned int upd_acc_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time );

/* external prepared statement structures from db_tool.cpp */
extern sqlite3_stmt *ps_select_admin01_exist;
extern sqlite3_stmt *ps_insert_admin01;
extern sqlite3_stmt *ps_select_account;
extern sqlite3_stmt *ps_select_account_pass;
extern sqlite3_stmt *ps_update_user_online;
extern sqlite3_stmt *ps_select_logged_in;
extern sqlite3_stmt *ps_update_user_offline;
extern sqlite3_stmt *ps_select_password;
extern sqlite3_stmt *ps_update_change_password;
extern sqlite3_stmt *ps_select_acctype_ipaddr;
extern sqlite3_stmt *ps_select_max_run_id;
extern sqlite3_stmt *ps_insert_new_submission;
extern sqlite3_stmt *ps_select_ipaddr_online_sreq;
extern sqlite3_stmt *ps_select_path_desc;
extern sqlite3_stmt *ps_select_full_sb;
extern sqlite3_stmt *ps_select_run;
extern sqlite3_stmt *ps_select_run_chk_dup;
extern sqlite3_stmt *ps_update_judge_result;
extern sqlite3_stmt *ps_select_accept_count_rrn;
extern sqlite3_stmt *ps_update_accept_count;
extern sqlite3_stmt *ps_select_account_accept_count;
extern sqlite3_stmt *ps_select_full_trun;
extern sqlite3_stmt *ps_select_problem_id_name;
extern sqlite3_stmt *ps_select_unjudged;
extern sqlite3_stmt *ps_update_taken;
extern sqlite3_stmt *ps_select_ipaddr_exclusive;
extern sqlite3_stmt *ps_insert_new_account;
extern sqlite3_stmt *ps_select_max_account_id;
extern sqlite3_stmt *ps_insert_new_scoreboard;
extern sqlite3_stmt *ps_select_ipaddr_online_accadd;
extern sqlite3_stmt *ps_select_acctype_accdel;
extern sqlite3_stmt *ps_delete_user;
extern sqlite3_stmt *ps_select_ipaddr_accdel;
extern sqlite3_stmt *ps_select_acctype_accmod;
extern sqlite3_stmt *ps_update_account;
extern sqlite3_stmt *ps_update_account_password;
extern sqlite3_stmt *ps_select_ipaddr_accmod;
extern sqlite3_stmt *ps_select_accept_count_accmod;
extern sqlite3_stmt *ps_select_full_account;
extern sqlite3_stmt *ps_insert_new_problem;
extern sqlite3_stmt *ps_select_ipaddr_padd;
extern sqlite3_stmt *ps_delete_related_runs;
extern sqlite3_stmt *ps_delete_problem;
extern sqlite3_stmt *ps_select_ipaddr_pdel;
extern sqlite3_stmt *ps_update_problem;
extern sqlite3_stmt *ps_select_ipaddr_pmod;
extern sqlite3_stmt *ps_select_full_problem;
extern sqlite3_stmt *ps_insert_clar;
extern sqlite3_stmt *ps_select_max_clar_id;
extern sqlite3_stmt *ps_update_clar_result;
extern sqlite3_stmt *ps_select_clar_msg;
extern sqlite3_stmt *ps_select_ipaddr_acc_cr;
extern sqlite3_stmt *ps_select_ipaddr_cr;
extern sqlite3_stmt *ps_select_unrep_clar;
extern sqlite3_stmt *ps_select_ipaddr_sdbc;
extern sqlite3_stmt *ps_select_ipaddr_sdbpc;
extern sqlite3_stmt *ps_select_ipaddr_sdbcr;
extern sqlite3_stmt *ps_select_ipaddr_sdbsbu;


/* global variables */
bool is_contest_stop;	/* contest_state */
sqlite3 *db;	/* sqlite variable */
ServerFrame *mainFrame;
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

	FILE *fptr;  // file pointer to test initialization

	mainFrame = this;

	/* timer variable */
	m_timeleft = 0;
	is_timer_set = false;

	/* set contest state */
	is_contest_stop = true;

	/* test if server_db.db3 exists
	 * if not, then the application is not initialized on this machine -- initialize it */
	if( ( fptr = fopen("server_db.db3", "r") ) == NULL )
	{
		/* create subdirectory to store files */
		/* FIXME: this should be check on every start */
		system( "mkdir submits" );
		system( "mkdir problems" );

		/* create database file */
		if ( sqlite3_open_v2( "server_db.db3", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL ) )
		   return;

		/* create table SQL */
		sqlite3_exec( db, create_user, 0, 0, &errMsg );
		sqlite3_exec( db, create_problem, 0, 0, &errMsg );
		sqlite3_exec( db, create_submission, 0, 0, &errMsg );
		sqlite3_exec( db, create_clarification, 0, 0, &errMsg );
		sqlite3_exec( db, create_scoreboard, 0, 0, &errMsg );
	}
	else /* else, skip initialization */
	{
		if ( sqlite3_open_v2( "server_db.db3", &db, SQLITE_OPEN_READWRITE, NULL ) )
			return;
		fclose( fptr );
	}


	/* re-initialize server GUI status indicator (add color) */
	StaticTextStatus->SetLabel( wxT("Not Running") );
	StaticTextStatus->SetForegroundColour( *wxRED );
	StaticTextStatus->Refresh();

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
	serverproto_cbreg_tp_sync( callback_tp_sync );
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

	/* create SQLite prepared statements */
	createPrepareStatement(db);
}


ServerFrame::~ServerFrame()
{
	if( serverproto_active() )
		serverproto_stop_listen();

	/* release SQLite prepared statements */
	destroyPrepareStatement(db);
	/* close database */
	sqlite3_close(db);
}

void ServerFrame::OnButtonClickStart( wxCommandEvent& event )
{
	int sqlite3_rc;

	if( serverproto_active() )
	{
		wxMessageBox( wxT("Server already running.\nYou cannot start twice."), wxT("Information"), wxOK|wxICON_INFORMATION, this );
		return;
	}

	/* start listen socket */
	if( serverproto_listen("0.0.0.0") < 0 )
	{
#if SERVER_DBG > 0
		printf("[ServerFrame::OnButtonClickStart()] serverproto_listen() call failed.\n");
#endif
		wxMessageBox( wxT("Server start failed.\nStage: start listen socket."), wxT("Fatal Error"), wxOK|wxICON_ERROR, this );
		return;
	}

	/* set wxStaticText label */
	StaticTextStatus->SetLabel( wxT("NOW Running") );
	StaticTextStatus->SetForegroundColour( *wxBLUE );
	StaticTextStatus->Refresh();

	/* if admin01 not exist, add an admin01 account */
	sqlite3_rc = sqlite3_step( ps_select_admin01_exist );
	if( sqlite3_rc == SQLITE_DONE )
	{
		sqlite3_bind_int( ps_insert_admin01, 1, OPSR_ADMIN );
		sqlite3_rc = sqlite3_step( ps_insert_admin01 );
		sqlite3_reset( ps_insert_admin01 );
		sqlite3_clear_bindings( ps_insert_admin01 );
	}

	sqlite3_reset( ps_select_admin01_exist );
}

void ServerFrame::OnButtonClickStop( wxCommandEvent& event )
{
	if( serverproto_active() )
		serverproto_stop_listen();

	StaticTextStatus->SetLabel( wxT("Not Running") );
	StaticTextStatus->SetForegroundColour( *wxRED );
	StaticTextStatus->Refresh();
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

void ServerFrame::TimerCall(wxCommandEvent &event){
	if(event.GetInt() == 1 && !m_timer.IsRunning() ){
		//callback function said that contest is running.
		//add your code here
		m_timer.Start(1000);
	}
	else if(event.GetInt() == 0){
		//callback function said that contest is not running.
		//add your code here
		m_timer.Stop();
	}

	return;
}

/* Server callback function definition. */
void callback_login_request( char *srcip, short srctype, wchar_t *account, char *password )
{
	int sqlite3_rc;
	char *account_char;
	unsigned int account_id;

	/* determine the validity of account */
	account_char = u16_to_u8( account );
	sqlite3_bind_text( ps_select_account, 1, account_char, -1, SQLITE_STATIC );
	sqlite3_rc = sqlite3_step( ps_select_account );

	if( sqlite3_rc == SQLITE_ROW )
	{
		/* determine the validity of account/password */
		sqlite3_bind_text( ps_select_account_pass, 1, account_char, -1, SQLITE_STATIC );
		sqlite3_bind_text( ps_select_account_pass, 2, password, -1, SQLITE_STATIC );
		sqlite3_rc = sqlite3_step( ps_select_account_pass );

		if( sqlite3_rc == SQLITE_ROW )  /* LOGIN_VALID */
		{
			account_id = sqlite3_column_int( ps_select_account_pass, 0 );

			/* mark the account as logged in, set account ip */
			sqlite3_bind_text( ps_update_user_online, 1, srcip, -1, SQLITE_STATIC );
			sqlite3_bind_int( ps_update_user_online, 2, account_id );
			sqlite3_rc = sqlite3_step( ps_update_user_online );
			sqlite3_reset( ps_update_user_online );
			sqlite3_clear_bindings( ps_update_user_online );

			if( sqlite3_rc == SQLITE_DONE )
				serverproto_login_reply( srcip, srctype, LOGIN_VALID, account_id );
		}
		else if( sqlite3_rc == SQLITE_DONE )	/* LOGIN_PASS_WRONG */
			serverproto_login_reply( srcip, srctype, LOGIN_PASS_WRONG, -1);

		sqlite3_reset( ps_select_account_pass );
		sqlite3_clear_bindings( ps_select_account_pass );
	}
	else if( sqlite3_rc == SQLITE_DONE )  /* LOGIN_ACC_NOTEXIST */
		serverproto_login_reply( srcip, srctype, LOGIN_ACC_NOTEXIST, -1);

	sqlite3_reset( ps_select_account );
	sqlite3_clear_bindings( ps_select_account );

	free( account_char );
}

void callback_logout_request( char *srcip, short srctype, unsigned int account_id )
{
	int sqlite3_rc;

	sqlite3_bind_int( ps_select_logged_in, 1, account_id );
	sqlite3_rc = sqlite3_step( ps_select_logged_in );

	if( sqlite3_rc == SQLITE_ROW )  /* LOGOUT_OK */
	{
		/* mark the account as logged out */
		sqlite3_bind_int( ps_update_user_offline, 1, account_id );
		sqlite3_rc = sqlite3_step( ps_update_user_offline );
		sqlite3_reset( ps_update_user_offline );
		sqlite3_clear_bindings( ps_update_user_offline );

		if( sqlite3_rc == SQLITE_DONE )
			serverproto_logout_reply( srcip, srctype, LOGOUT_OK );
	}
	else if( sqlite3_rc == SQLITE_DONE )  /* LOGOUT_FAIL */
	{
		/* account not exist */
		serverproto_logout_reply( srcip, srctype, LOGOUT_FAIL );
	}

	sqlite3_reset( ps_select_logged_in );
	sqlite3_clear_bindings( ps_select_logged_in );
}

void callback_password_change( char *srcip, short srctype, unsigned int account_id, char *old_password, char *new_password )
{
	int sqlite3_rc;
	char *db_password;

	sqlite3_bind_int( ps_select_password, 1, account_id );
	sqlite3_rc = sqlite3_step( ps_select_password );

	if( sqlite3_rc == SQLITE_ROW )  /* PASSWD_SUCCESS */
	{
		db_password = dyn_strcpy( sqlite3_column_text( ps_select_password, 0 ) );

		if( strcmp( db_password, old_password ) == 0 )  /* PASSWD_SUCCESS */
		{
			/* store the changed password into database and give the client a reply */
			sqlite3_bind_text( ps_update_change_password, 1, new_password, -1, SQLITE_STATIC );
			sqlite3_bind_int( ps_update_change_password, 2, account_id );
			sqlite3_rc = sqlite3_step( ps_update_change_password );
			sqlite3_reset( ps_update_change_password );
			sqlite3_clear_bindings( ps_update_change_password );

			if( sqlite3_rc == SQLITE_DONE )
				serverproto_password_change_reply( srcip, srctype, PASSWD_SUCCESS );
		}
		else	/* PASSWD_MISMATCH */
		{
			serverproto_password_change_reply( srcip, srctype, PASSWD_MISMATCH );
		}

		free( db_password );
	}
	else if( sqlite3_rc == SQLITE_DONE )  /* PASSWD_FAIL */
	{
		/* account not exist */
		serverproto_password_change_reply( srcip, srctype, PASSWD_INVALID );
	}

	sqlite3_reset( ps_select_password );
	sqlite3_clear_bindings( ps_select_password );
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
	int sqlite3_rc;
	unsigned int account_type;
	char *dest_ipaddr;

	/* set timer */
	m_timeleft = hours * 3600 + minutes * 60 + seconds;
	is_timer_set = true;

	while( ( sqlite3_rc = sqlite3_step( ps_select_acctype_ipaddr ) ) == SQLITE_ROW )
	{
		account_type = sqlite3_column_int( ps_select_acctype_ipaddr, 0 );
		dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_acctype_ipaddr, 1 ) );

		serverproto_timer_set( dest_ipaddr, account_type, hours, minutes, seconds );

		free( dest_ipaddr );
	}

	sqlite3_reset( ps_select_acctype_ipaddr );
}

void callback_admin_contest_start( char *srcip )
{
	wxCommandEvent event(wxEVT_CALL_TIMER);
	event.SetInt(1);
	wxPostEvent(mainFrame, event);

	is_contest_stop = false;
	serverdb_contest( serverproto_contest_start, OPSR_ADMIN );
	serverdb_contest( serverproto_contest_start, OPSR_JUDGE );
	serverdb_contest( serverproto_contest_start, OPSR_TEAM );
}

void callback_admin_contest_stop( char *srcip )
{
	wxCommandEvent event(wxEVT_CALL_TIMER);
	event.SetInt(0);
	wxPostEvent(mainFrame, event);

	is_contest_stop = true;
	serverdb_contest( serverproto_contest_stop, OPSR_ADMIN );
	serverdb_contest( serverproto_contest_stop, OPSR_JUDGE );
	serverdb_contest( serverproto_contest_stop, OPSR_TEAM );
}

/* the function needs a subdirectory "submits/" */
/* TODO: Test here. */
void callback_submission_request( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code )
{
	int sqlite3_rc;
	wchar_t path_code_tmp[30];
	unsigned int next_run_id;

	/* if several submission request pour in, the run_id will be in chaos */
	mainFrame->m_mutexSubmissionRequest.Lock();

	/* retrieve next run_id */
	sqlite3_rc = sqlite3_step( ps_select_max_run_id );
	next_run_id = sqlite3_column_int( ps_select_max_run_id, 0 ) + 1;
	sqlite3_reset( ps_select_max_run_id );

	/* set path_code */
	wsprintf(path_code_tmp, L"submits/submit%d.%s", next_run_id, coding_language );
	*path_code = (wchar_t *)malloc( ( wcslen( path_code_tmp ) + 1 ) * sizeof( wchar_t ) );
	wcscpy( *path_code, path_code_tmp );
}

void callback_submission_request_dlfin( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code )
{
	int sqlite3_rc;
	char *path_code_char, *coding_language_char;
	unsigned int run_id;
	char *dest_ipaddr;

	/* record those information into db */
	coding_language_char = u16_to_u8( coding_language );
	path_code_char = u16_to_u8( path_code );
	sqlite3_bind_int( ps_insert_new_submission, 1, account_id );
	sqlite3_bind_int( ps_insert_new_submission, 2, problem_id );
	sqlite3_bind_text( ps_insert_new_submission, 3, coding_language_char, -1, SQLITE_STATIC );
	sqlite3_bind_text( ps_insert_new_submission, 4, path_code_char, -1, SQLITE_STATIC );
	sqlite3_rc = sqlite3_step( ps_insert_new_submission );
	sqlite3_reset( ps_insert_new_submission );
	sqlite3_clear_bindings( ps_insert_new_submission );

	/* get run_id from submission table */
	sqlite3_rc = sqlite3_step( ps_select_max_run_id );
	run_id = sqlite3_column_int( ps_select_max_run_id, 0 );
	sqlite3_reset( ps_select_max_run_id );

	/* redirect the submission to all judge */
	sqlite3_bind_int( ps_select_ipaddr_online_sreq, 1, OPSR_JUDGE );
	while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_online_sreq ) ) == SQLITE_ROW )
	{
		dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_online_sreq, 0 ) );
		serverproto_run_request( dest_ipaddr, run_id, problem_id, coding_language, path_code );
		free( dest_ipaddr );
	}

	sqlite3_reset( ps_select_ipaddr_online_sreq );
	sqlite3_clear_bindings( ps_select_ipaddr_online_sreq );

	/* reply submitter queue successed */
	serverproto_run_reply( srcip, run_id, problem_id, L"queued" );

	mainFrame->m_mutexSubmissionRequest.Unlock();

	free( coding_language_char );
	free( path_code_char );
}

void callback_pd_request( char *srcip, unsigned int account_id, unsigned int problem_id )
{
	int sqlite3_rc;
	char *path_description_char;
	wchar_t *path_description_wchar;

	/* upload the corresponding problem pack to user  */
	sqlite3_bind_int( ps_select_path_desc, 1, problem_id );
	sqlite3_rc = sqlite3_step( ps_select_path_desc );
	if( sqlite3_rc == SQLITE_ROW )
	{
		path_description_char = dyn_strcpy( sqlite3_column_text( ps_select_path_desc, 0 ) );
		path_description_wchar = u8_to_u16( path_description_char );

		serverproto_problem_upload( srcip, path_description_wchar );

		free( path_description_char );
		free( path_description_wchar );
	}

	sqlite3_reset( ps_select_path_desc );
	sqlite3_clear_bindings( ps_select_path_desc );
}

void callback_sb_sync( char *srcip, short srctype )
{
	int sqlite3_rc;
	unsigned int account_id, new_time, new_accept_count;
	wchar_t *new_account_wchar;
	char *new_account_char;

	while( ( sqlite3_rc = sqlite3_step( ps_select_full_sb ) ) == SQLITE_ROW )
	{
		account_id = sqlite3_column_int( ps_select_full_sb, 0 );
		new_account_char = dyn_strcpy( sqlite3_column_text( ps_select_full_sb, 1 ) );
		new_time = sqlite3_column_int( ps_select_full_sb, 2 );
		new_accept_count = sqlite3_column_int( ps_select_full_sb, 3 );

		new_account_wchar = u8_to_u16( new_account_char );

		serverproto_sb_update( srcip, srctype, account_id, new_account_wchar, new_accept_count, new_time );

		free( new_account_char );
		free( new_account_wchar );
	}

	sqlite3_reset( ps_select_full_sb );
}

void callback_run_result_notify( char *srcip, unsigned int run_id, wchar_t *result )
{
	int sqlite3_rc;
	char *result_char, *dstip;
	unsigned int problem_id, account_id, accept_count;
	wchar_t *account_wchar;
	char *account_char;

	/* get account_id, problem_id, and ipaddress */
	sqlite3_bind_int( ps_select_run, 1, run_id );
	sqlite3_rc = sqlite3_step( ps_select_run );
	if( sqlite3_rc == SQLITE_ROW )
	{
		account_id = sqlite3_column_int( ps_select_run, 0 );
		problem_id = sqlite3_column_int( ps_select_run, 1 );
		dstip = dyn_strcpy( sqlite3_column_text( ps_select_run, 2 ) );
	}

	sqlite3_reset( ps_select_run );
	sqlite3_clear_bindings( ps_select_run );

	/* If the team get the point of the same problem before, the score will not add by one. Modify the result. */
	sqlite3_bind_int( ps_select_run_chk_dup, 1, account_id );
	sqlite3_bind_int( ps_select_run_chk_dup, 2, problem_id );
	sqlite3_rc = sqlite3_step( ps_select_run_chk_dup );
	if( sqlite3_rc == SQLITE_ROW )
	{
		if( wcscmp(result, L"yes") == 0 )
			wcscpy(result, L"Duplicated");
	}

	sqlite3_reset( ps_select_run_chk_dup );
	sqlite3_clear_bindings( ps_select_run_chk_dup );

	/* record result information into db */
	result_char = u16_to_u8( result );
	sqlite3_bind_text( ps_update_judge_result, 1, result_char, -1, SQLITE_STATIC );
	sqlite3_bind_int( ps_update_judge_result, 2, run_id );
	sqlite3_rc = sqlite3_step( ps_update_judge_result );

	/* update accept_count in scoreboard if result = "yes" */
	if( strcmp(result_char, "yes") == 0 )
	{
		/* get accept_count */
		sqlite3_bind_int( ps_select_accept_count_rrn, 1, account_id );
		sqlite3_rc = sqlite3_step( ps_select_accept_count_rrn );
		if( sqlite3_rc == SQLITE_ROW )
			accept_count = sqlite3_column_int( ps_select_accept_count_rrn, 0 );

		sqlite3_reset( ps_select_accept_count_rrn );
		sqlite3_clear_bindings( ps_select_accept_count_rrn );

		/* update accept_count */
		sqlite3_bind_int( ps_update_accept_count, 1, accept_count + 1 );
		sqlite3_bind_int( ps_update_accept_count, 2, account_id );
		sqlite3_rc = sqlite3_step( ps_update_accept_count );
		sqlite3_reset( ps_update_accept_count );
		sqlite3_clear_bindings( ps_update_accept_count );

		/* update scoreboard globally */
		sqlite3_bind_int( ps_select_account_accept_count, 1, account_id );
		sqlite3_rc = sqlite3_step( ps_select_account_accept_count );
		if( sqlite3_rc == SQLITE_ROW )
		{
			account_char = dyn_strcpy( sqlite3_column_text( ps_select_account_accept_count, 0 ) );
			accept_count = sqlite3_column_int( ps_select_account_accept_count, 1 );

			account_wchar = u8_to_u16( account_char );

			serverdb_sb_update( OPSR_TEAM, account_id, account_wchar, accept_count, 0 );
			serverdb_sb_update( OPSR_ADMIN, account_id, account_wchar, accept_count, 0 );

			free( account_char );
			free( account_wchar );
		}

		sqlite3_reset( ps_select_account_accept_count );
		sqlite3_clear_bindings( ps_select_account_accept_count );
	}

	/* redirect the result to corresponding team */
	serverproto_run_reply( dstip, run_id, problem_id, result );

	sqlite3_reset( ps_update_judge_result );
	sqlite3_clear_bindings( ps_update_judge_result );

	free( dstip );
	free( result_char );
}

void callback_trun_sync( char *srcip, unsigned int account_id )
{
	int sqlite3_rc;
	unsigned int run_id, problem_id;
	wchar_t *judge_result_wchar;
	char *judge_result_char;

	/* update all runs related to requesting team */
	sqlite3_bind_int( ps_select_full_trun, 1, account_id );
	while( ( sqlite3_rc = sqlite3_step( ps_select_full_trun ) ) == SQLITE_ROW )
	{
		run_id = sqlite3_column_int( ps_select_full_trun, 0 );
		problem_id = sqlite3_column_int( ps_select_full_trun, 1 );
		judge_result_char = dyn_strcpy( sqlite3_column_text( ps_select_full_trun, 2 ) );

		judge_result_wchar = u8_to_u16( judge_result_char );

		serverproto_run_reply(srcip, run_id, problem_id, judge_result_wchar);

		free( judge_result_char );
		free( judge_result_wchar );
	}

	sqlite3_reset( ps_select_full_trun );
	sqlite3_clear_bindings( ps_select_full_trun );
}

void callback_tp_sync( char *srcip )
{
	int sqlite3_rc;
	unsigned int problem_id;
	wchar_t *problem_name_wchar;
	char *problem_name_char;

	/* sync problem list */
	while( ( sqlite3_rc = sqlite3_step( ps_select_problem_id_name ) ) == SQLITE_ROW )
	{
		problem_id = sqlite3_column_int( ps_select_problem_id_name, 0 );
		problem_name_char = dyn_strcpy( sqlite3_column_text( ps_select_problem_id_name, 1 ) );
		problem_name_wchar = u8_to_u16( problem_name_char );

		serverproto_problem_change_add( srcip, problem_id, problem_name_wchar );

		free( problem_name_char );
		free( problem_name_wchar );
	}

	sqlite3_reset( ps_select_problem_id_name );
}

void callback_run_sync( char *srcip )
{
	int sqlite3_rc;
	unsigned int run_id, problem_id;
	wchar_t *lang_wchar, *path_code_wchar;
	char *lang_char, *path_code_char;

	/* update all un-judged runs to the requesting judge */
	while( ( sqlite3_rc = sqlite3_step( ps_select_unjudged ) ) == SQLITE_ROW )
	{
		run_id = sqlite3_column_int( ps_select_unjudged, 0 );
		problem_id = sqlite3_column_int( ps_select_unjudged, 1 );
		lang_char = dyn_strcpy( sqlite3_column_text( ps_select_unjudged, 2 ) );
		path_code_char = dyn_strcpy( sqlite3_column_text( ps_select_unjudged, 3 ) );

		lang_wchar = u8_to_u16( lang_char );
		path_code_wchar = u8_to_u16( path_code_char );

		serverproto_run_request(srcip, run_id, problem_id, lang_wchar, path_code_wchar);

		free( lang_char );
		free( path_code_char );
		free( lang_wchar );
		free( path_code_wchar );
	}

	sqlite3_reset( ps_select_unjudged );
}

void callback_take_run( char *srcip, unsigned int run_id )
{
	int sqlite3_rc;
	char *dest_ipaddr;

	/* mark the judge as taken */
	sqlite3_bind_int( ps_update_taken, 1, run_id );
	sqlite3_rc = sqlite3_step( ps_update_taken );
	sqlite3_reset( ps_update_taken );
	sqlite3_clear_bindings( ps_update_taken );

	/* notify judges about take result */
	serverproto_take_result( srcip, run_id, TAKE_SUCCESS );
	sqlite3_bind_int( ps_select_ipaddr_exclusive, 1, OPSR_JUDGE );
	sqlite3_bind_text( ps_select_ipaddr_exclusive, 2, srcip, -1, SQLITE_STATIC );
	while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_exclusive ) ) == SQLITE_ROW )
	{
		dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_exclusive, 0 ) );
		serverproto_take_result( dest_ipaddr, run_id, TAKE_FAIL );
		free( dest_ipaddr );
	}

	sqlite3_reset( ps_select_ipaddr_exclusive );
	sqlite3_clear_bindings( ps_select_ipaddr_exclusive );
}

void callback_account_add( char *srcip, unsigned int type, wchar_t *account, char *password )
{
	int sqlite3_rc;
	unsigned int account_id;
	char *account_char;
	char *dest_ipaddr;

	/* record account and scoreboard information into db */
	account_char = u16_to_u8( account );
	sqlite3_bind_text( ps_insert_new_account, 1, account_char, -1, SQLITE_STATIC );
	sqlite3_bind_text( ps_insert_new_account, 2, password, -1, SQLITE_STATIC );
	sqlite3_bind_int( ps_insert_new_account, 3, type );
	sqlite3_rc = sqlite3_step( ps_insert_new_account );
	sqlite3_reset( ps_insert_new_account );
	sqlite3_clear_bindings( ps_insert_new_account );

	/* retrieve account_id */
	sqlite3_rc = sqlite3_step( ps_select_max_account_id );
	account_id = sqlite3_column_int( ps_select_max_account_id, 0 );
	sqlite3_reset( ps_select_max_account_id );

	if( type == OPSR_TEAM )
	{
		sqlite3_bind_int( ps_insert_new_scoreboard, 1, account_id );
		sqlite3_rc = sqlite3_step( ps_insert_new_scoreboard );
		sqlite3_reset( ps_insert_new_scoreboard );
		sqlite3_clear_bindings( ps_insert_new_scoreboard );
	}

	/* updates account listing to administrators */
	sqlite3_bind_int( ps_select_ipaddr_online_accadd, 1, OPSR_ADMIN );
	while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_online_accadd ) ) == SQLITE_ROW )
	{
		dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_online_accadd, 0 ) );
		serverproto_account_update( dest_ipaddr, account_id, type, account );
		free( dest_ipaddr );
	}

	sqlite3_reset( ps_select_ipaddr_online_accadd );
	sqlite3_clear_bindings( ps_select_ipaddr_online_accadd );

	/* notify team and admin client about scoreboard updates */
	if( type == OPSR_TEAM )
	{
		serverdb_sb_update( OPSR_TEAM, account_id, account, 0, 0 );
		serverdb_sb_update( OPSR_ADMIN, account_id, account, 0, 0 );
	}

	free( account_char );
}

void callback_account_del( char *srcip, unsigned int account_id )
{
	int sqlite3_rc;
	short type;
	char *dest_ipaddr;

	/* get client account type */
	sqlite3_bind_int( ps_select_acctype_accdel, 1, account_id );
	sqlite3_rc = sqlite3_step( ps_select_acctype_accdel );
	type = sqlite3_column_int( ps_select_acctype_accdel, 0 );
	sqlite3_reset( ps_select_acctype_accdel );
	sqlite3_clear_bindings( ps_select_acctype_accdel );

	/* remove the account from db and remove everything related to that account from the system
	 * FIXME: foreign key constraint. */
	sqlite3_bind_int( ps_delete_user, 1, account_id );
	sqlite3_rc = sqlite3_step( ps_delete_user );
	sqlite3_reset( ps_delete_user );
	sqlite3_clear_bindings( ps_delete_user );

	/* updates account listing to administrator */
	sqlite3_bind_int( ps_select_ipaddr_accdel, 1, OPSR_ADMIN );
	while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_accdel ) ) == SQLITE_ROW )
	{
		dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_accdel, 0 ) );
		serverproto_account_remove( dest_ipaddr, account_id );
		free( dest_ipaddr );
	}

	sqlite3_reset( ps_select_ipaddr_accdel );
	sqlite3_clear_bindings( ps_select_ipaddr_accdel );

	/* notify team and admin client about scoreboard updates */
	if( type == OPSR_TEAM )
	{
		sqlite3_bind_int( ps_select_ipaddr_accdel, 1, OPSR_TEAM );
		while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_accdel ) ) == SQLITE_ROW )
		{
			dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_accdel, 0 ) );
			serverproto_sb_remove( dest_ipaddr, OPSR_TEAM, account_id );
			free( dest_ipaddr );
		}

		sqlite3_reset( ps_select_ipaddr_accdel );
		sqlite3_clear_bindings( ps_select_ipaddr_accdel );

		sqlite3_bind_int( ps_select_ipaddr_accdel, 1, OPSR_ADMIN );
		while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_accdel ) ) == SQLITE_ROW )
		{
			dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_accdel, 0 ) );
			serverproto_sb_remove( dest_ipaddr, OPSR_ADMIN, account_id );
			free( dest_ipaddr );
		}

		sqlite3_reset( ps_select_ipaddr_accdel );
		sqlite3_clear_bindings( ps_select_ipaddr_accdel );
	}

	/* FIXME: If deleted user is online, kick it? */
}

void callback_account_mod( char *srcip, unsigned int account_id, wchar_t *new_account, char *new_password )
{
	int sqlite3_rc;
	char *new_account_char;
	unsigned int account_type, accept_count, time;
	short type;
	char *dest_ipaddr;

	/* get client account type */
	sqlite3_bind_int( ps_select_acctype_accmod, 1, account_id );
	sqlite3_rc = sqlite3_step( ps_select_acctype_accmod );
	type = sqlite3_column_int( ps_select_acctype_accmod, 0 );
	sqlite3_reset( ps_select_acctype_accmod );
	sqlite3_clear_bindings( ps_select_acctype_accmod );

	/* modify the record in db */
	new_account_char = u16_to_u8( new_account );
	/* FIXME: new_password from oojproto won't be NULL, it should be at least an empty string. */
	if(new_password == NULL)  /* update only account */
	{
		sqlite3_bind_text( ps_update_account, 1, new_account_char, -1, SQLITE_STATIC );
		sqlite3_bind_int( ps_update_account, 2, account_id );
		sqlite3_rc = sqlite3_step( ps_update_account );
		sqlite3_reset( ps_update_account );
		sqlite3_clear_bindings( ps_update_account );
	}
	else  /* update both account and password */
	{
		sqlite3_bind_text( ps_update_account_password, 1, new_account_char, -1, SQLITE_STATIC );
		sqlite3_bind_text( ps_update_account_password, 2, new_password, -1, SQLITE_STATIC );
		sqlite3_bind_int( ps_update_account_password, 3, account_id );
		sqlite3_rc = sqlite3_step( ps_update_account_password );
		sqlite3_reset( ps_update_account_password );
		sqlite3_clear_bindings( ps_update_account_password );
	}

	/* determine account type of the updated account */
	sqlite3_bind_int( ps_select_acctype_accmod, 1, account_id );
	sqlite3_rc = sqlite3_step( ps_select_acctype_accmod );
	account_type = sqlite3_column_int( ps_select_acctype_accmod, 0 );
	sqlite3_reset( ps_select_acctype_accmod );
	sqlite3_clear_bindings( ps_select_acctype_accmod );

	/* updates account to administrator */
	sqlite3_bind_int( ps_select_ipaddr_accmod, 1, OPSR_ADMIN );
	while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_accmod ) ) == SQLITE_ROW )
	{
		dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_accmod, 0 ) );
		serverproto_account_update( dest_ipaddr, account_id, account_type, new_account );
		free( dest_ipaddr );
	}

	sqlite3_reset( ps_select_ipaddr_accmod );
	sqlite3_clear_bindings( ps_select_ipaddr_accmod );

	/* notify team and admin client about scoreboard updates */
	if( type == OPSR_TEAM )
	{
		sqlite3_bind_int( ps_select_accept_count_accmod, 1, account_id );
		sqlite3_rc = sqlite3_step( ps_select_accept_count_accmod );
		if( sqlite3_rc == SQLITE_ROW )
		{
			accept_count = sqlite3_column_int( ps_select_accept_count_accmod, 0 );
			time = sqlite3_column_int( ps_select_accept_count_accmod, 1 );
			serverdb_sb_update( OPSR_TEAM, account_id, new_account, accept_count, time );
			serverdb_sb_update( OPSR_ADMIN, account_id, new_account, accept_count, time );
		}

		sqlite3_reset( ps_select_accept_count_accmod );
		sqlite3_clear_bindings( ps_select_accept_count_accmod );
	}

	free( new_account_char );
}

void callback_account_sync( char *srcip )
{
	int sqlite3_rc;
	unsigned int account_id, account_type;
	wchar_t *acc_wchar;
	char *acc_char;

	/* updates account listing to administrator */
	while( ( sqlite3_rc = sqlite3_step( ps_select_full_account ) ) == SQLITE_ROW )
	{
		account_id = sqlite3_column_int( ps_select_full_account, 0 );
		acc_char = dyn_strcpy( sqlite3_column_text( ps_select_full_account, 1 ) );
		account_type = sqlite3_column_int( ps_select_full_account, 2 );

		acc_wchar = u8_to_u16( acc_char );

		serverproto_account_update(srcip, account_id, account_type, acc_wchar);

		free( acc_char );
		free( acc_wchar );
	}

	sqlite3_reset( ps_select_full_account );
}

/* the function needs a subdirectory "problems/" */
void callback_problem_add( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer )
{
	char path_description_char[50], path_input_char[50], path_answer_char[50];

	/* edit path names */
	*path_description = (wchar_t *) malloc( 50 * sizeof(wchar_t) );
	sprintf(path_description_char, "problems/path_descr%u.pdf", problem_id);
	*path_description = u8_to_u16( path_description_char );

	*path_input = (wchar_t *) malloc( 50 * sizeof(wchar_t) );
	sprintf(path_input_char, "problems/p%u_in.txt", problem_id);
	*path_input = u8_to_u16( path_input_char );

	*path_answer = (wchar_t *) malloc( 50 * sizeof(wchar_t) );
	sprintf(path_answer_char, "problems/p%u_out.txt", problem_id);
	*path_answer = u8_to_u16( path_answer_char );
}

void callback_problem_add_dlfin( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer )
{
	int sqlite3_rc;
	char *problem_name_char, *path_description_char, *path_input_char, *path_answer_char;
	char *dest_ipaddr;

	problem_name_char = u16_to_u8( problem_name );
	path_description_char = u16_to_u8( path_description );
	path_input_char = u16_to_u8( path_input );
	path_answer_char = u16_to_u8( path_answer );

	/* record the new problem into db */
	sqlite3_bind_text( ps_insert_new_problem, 1, problem_name_char, -1, SQLITE_STATIC );
	sqlite3_bind_text( ps_insert_new_problem, 2, path_description_char, -1, SQLITE_STATIC );
	sqlite3_bind_text( ps_insert_new_problem, 3, path_input_char, -1, SQLITE_STATIC );
	sqlite3_bind_text( ps_insert_new_problem, 4, path_answer_char, -1, SQLITE_STATIC );
	sqlite3_bind_int( ps_insert_new_problem, 5, time_limit );
	sqlite3_rc = sqlite3_step( ps_insert_new_problem );
	sqlite3_reset( ps_insert_new_problem );
	sqlite3_clear_bindings( ps_insert_new_problem );

	/* reply function */
	sqlite3_bind_int( ps_select_ipaddr_padd, 1, OPSR_ADMIN );
	while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_padd ) ) == SQLITE_ROW )
	{
		dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_padd, 0 ) );
		serverproto_problem_update( dest_ipaddr, OPSR_ADMIN, problem_id, problem_name, time_limit, path_description, path_input, path_answer );
		free( dest_ipaddr );
	}

	sqlite3_reset( ps_select_ipaddr_padd );
	sqlite3_clear_bindings( ps_select_ipaddr_padd );

	sqlite3_bind_int( ps_select_ipaddr_padd, 1, OPSR_JUDGE );
	while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_padd ) ) == SQLITE_ROW )
	{
		dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_padd, 0 ) );
		serverproto_problem_update( dest_ipaddr, OPSR_JUDGE, problem_id, problem_name, time_limit, path_description, path_input, path_answer );
		free( dest_ipaddr );
	}

	sqlite3_reset( ps_select_ipaddr_padd );
	sqlite3_clear_bindings( ps_select_ipaddr_padd );

	serverdb_problem_change(PROBLEM_CHANGE_ADD, problem_id, problem_name);

	free( problem_name_char );
	free( path_description_char );
	free( path_input_char );
	free( path_answer_char );
}

void callback_problem_del( char *srcip, unsigned int problem_id )
{
	int sqlite3_rc;
	char *dest_ipaddr;

	/* delete related runs first (foreign key constraint)
	 * FIXME: Client-end may not be upaded.*/
	sqlite3_bind_int( ps_delete_related_runs, 1, problem_id );
	sqlite3_rc = sqlite3_step( ps_delete_related_runs );
	sqlite3_reset( ps_delete_related_runs );
	sqlite3_clear_bindings( ps_delete_related_runs );

	/* remove the problem from db and
	 * FIXME: delete correspond data on disk */
	sqlite3_bind_int( ps_delete_problem, 1, problem_id );
	sqlite3_rc = sqlite3_step( ps_delete_problem );
	sqlite3_reset( ps_delete_problem );
	sqlite3_clear_bindings( ps_delete_problem );

	/* reply function */
	sqlite3_bind_int( ps_select_ipaddr_pdel, 1, OPSR_ADMIN );
	while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_pdel ) ) == SQLITE_ROW )
	{
		dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_pdel, 0 ) );
		serverproto_problem_remove( dest_ipaddr, OPSR_ADMIN, problem_id );
		free( dest_ipaddr );
	}

	sqlite3_reset( ps_select_ipaddr_pdel );
	sqlite3_clear_bindings( ps_select_ipaddr_pdel );

	sqlite3_bind_int( ps_select_ipaddr_pdel, 1, OPSR_JUDGE );
	while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_pdel ) ) == SQLITE_ROW )
	{
		dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_pdel, 0 ) );
		serverproto_problem_remove( dest_ipaddr, OPSR_JUDGE, problem_id );
		free( dest_ipaddr );
	}

	sqlite3_reset( ps_select_ipaddr_pdel );
	sqlite3_clear_bindings( ps_select_ipaddr_pdel );

	serverdb_problem_change(PROBLEM_CHANGE_DEL, problem_id, NULL);
}

void callback_problem_mod( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer )
{
	/* do the same thing as callback_problem_add(), just copy and paste */
	char path_description_char[50], path_input_char[50], path_answer_char[50];

	/* edit path names */
	sprintf(path_description_char, "problems/path_descr%u.pdf", problem_id);
	*path_description = u8_to_u16( path_description_char );

	sprintf(path_input_char, "problems/p%u_in.txt", problem_id);
	*path_input = u8_to_u16( path_input_char );

	sprintf(path_answer_char, "problems/p%u_out.txt", problem_id);
	*path_answer = u8_to_u16( path_answer_char );
}

void callback_problem_mod_dlfin( char *srcip, unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer )
{
	/* do the same thing as callback_problem_add_dlfin(), except for serverdb_problem_change parameter */
	int sqlite3_rc;
	char *problem_name_char, *path_description_char, *path_input_char, *path_answer_char;
	char *dest_ipaddr;

	problem_name_char = u16_to_u8( problem_name );
	path_description_char = u16_to_u8( path_description );
	path_input_char = u16_to_u8( path_input );
	path_answer_char = u16_to_u8( path_answer );

	/* record the new information into db */
	sqlite3_bind_text( ps_update_problem, 1, problem_name_char, -1, SQLITE_STATIC );
	sqlite3_bind_text( ps_update_problem, 2, path_description_char, -1, SQLITE_STATIC );
	sqlite3_bind_text( ps_update_problem, 3, path_input_char, -1, SQLITE_STATIC );
	sqlite3_bind_text( ps_update_problem, 4, path_answer_char, -1, SQLITE_STATIC );
	sqlite3_bind_int( ps_update_problem, 5, time_limit );
	sqlite3_bind_int( ps_update_problem, 6, problem_id );
	sqlite3_rc = sqlite3_step( ps_update_problem );
	sqlite3_reset( ps_update_problem );
	sqlite3_clear_bindings( ps_update_problem );

	/* reply function */
	sqlite3_bind_int( ps_select_ipaddr_pmod, 1, OPSR_ADMIN );
	while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_pmod ) ) == SQLITE_ROW )
	{
		dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_pmod, 0 ) );
		serverproto_problem_update( dest_ipaddr, OPSR_ADMIN, problem_id, problem_name, time_limit, path_description, path_input, path_answer );
		free( dest_ipaddr );
	}

	sqlite3_reset( ps_select_ipaddr_pmod );
	sqlite3_clear_bindings( ps_select_ipaddr_pmod );

	sqlite3_bind_int( ps_select_ipaddr_pmod, 1, OPSR_JUDGE );
	while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_pmod ) ) == SQLITE_ROW )
	{
		dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_pmod, 0 ) );
		serverproto_problem_update( dest_ipaddr, OPSR_JUDGE, problem_id, problem_name, time_limit, path_description, path_input, path_answer );
		free( dest_ipaddr );
	}

	sqlite3_reset( ps_select_ipaddr_pmod );
	sqlite3_clear_bindings( ps_select_ipaddr_pmod );

	serverdb_problem_change(PROBLEM_CHANGE_MOD, problem_id, problem_name);

	free( problem_name_char );
	free( path_description_char );
	free( path_input_char );
	free( path_answer_char );
}

void callback_problem_sync( char *srcip, short srctype )
{
	int sqlite3_rc;
	wchar_t *problem_name_wchar, *path_description_wchar, *correct_input_filename_wchar, *correct_output_filename_wchar;
	char *problem_name_char, *path_description_char, *correct_input_filename_char, *correct_output_filename_char;
	unsigned int problem_id, time_limit;

	while( ( sqlite3_rc = sqlite3_step( ps_select_full_problem ) ) == SQLITE_ROW )
	{
		problem_id = sqlite3_column_int( ps_select_full_problem, 0 );
		problem_name_char = dyn_strcpy( sqlite3_column_text( ps_select_full_problem, 1 ) );
		path_description_char = dyn_strcpy( sqlite3_column_text( ps_select_full_problem, 2 ) );
		correct_input_filename_char = dyn_strcpy( sqlite3_column_text( ps_select_full_problem, 3 ) );
		correct_output_filename_char = dyn_strcpy( sqlite3_column_text( ps_select_full_problem, 4 ) );
		time_limit = sqlite3_column_int( ps_select_full_problem, 5 );

		problem_name_wchar = u8_to_u16( problem_name_char );
		path_description_wchar = u8_to_u16( path_description_char );
		correct_input_filename_wchar = u8_to_u16( correct_input_filename_char );
		correct_output_filename_wchar = u8_to_u16( correct_output_filename_char );

		serverproto_problem_update( srcip, srctype, problem_id, problem_name_wchar, time_limit, path_description_wchar, correct_input_filename_wchar, correct_output_filename_wchar );

		free( problem_name_wchar );
		free( path_description_wchar );
		free( correct_input_filename_wchar );
		free( correct_output_filename_wchar );
	}

	sqlite3_reset( ps_select_full_problem );
}

void callback_clar_request( char *srcip, unsigned int account_id, int private_byte, wchar_t *clarmsg )
{
	int sqlite3_rc;
	char *clarmsg_char;
	unsigned int clar_id;

	clarmsg_char = u16_to_u8( clarmsg );

	/* record clarification information into db */
	sqlite3_bind_int( ps_insert_clar, 1, account_id );
	sqlite3_bind_text( ps_insert_clar, 2, clarmsg_char, -1, SQLITE_STATIC );
	sqlite3_bind_int( ps_insert_clar, 3, private_byte );
	sqlite3_rc = sqlite3_step( ps_insert_clar );
	sqlite3_reset( ps_insert_clar );
	sqlite3_clear_bindings( ps_insert_clar );

	/* select clar id */
	sqlite3_rc = sqlite3_step( ps_select_max_clar_id );
	clar_id = sqlite3_column_int( ps_select_max_clar_id, 0 );
	sqlite3_reset( ps_select_max_clar_id );

	/* redirect the request to admins */
	serverdb_clar_request(OPSR_ADMIN, clar_id, account_id, private_byte, clarmsg);

	/* redirect the request to judges */
	serverdb_clar_request(OPSR_JUDGE, clar_id, account_id, private_byte, clarmsg);

	/* reply team client */
	serverproto_clar_reply( srcip, OPSR_TEAM, clar_id, clarmsg, L"Clarifying...." );

	free( clarmsg_char );
}

void callback_clar_result( char *srcip, unsigned int clar_id, int private_byte, wchar_t *result_string )
{
	int sqlite3_rc;
	char *result_string_char;
	unsigned int account_id;
	wchar_t *msg_wchar;
	char *msg_char;
	char *dest_ipaddr;

	result_string_char = u16_to_u8( result_string );

	/* update clarification information into db */
	sqlite3_bind_text( ps_update_clar_result, 1, result_string_char, -1, SQLITE_STATIC );
	sqlite3_bind_int( ps_update_clar_result, 2, clar_id );
	sqlite3_rc = sqlite3_step( ps_update_clar_result );
	sqlite3_reset( ps_update_clar_result );
	sqlite3_clear_bindings( ps_update_clar_result );

	/* reply to all or one team, according to how private byte is set */
	sqlite3_bind_int( ps_select_clar_msg, 1, clar_id );
	sqlite3_rc = sqlite3_step( ps_select_clar_msg );
	if( sqlite3_rc == SQLITE_ROW )
	{
		account_id = sqlite3_column_int( ps_select_clar_msg, 0 );
		msg_char = dyn_strcpy( sqlite3_column_text( ps_select_clar_msg, 1 ) );

		msg_wchar = u8_to_u16( msg_char );
		free( msg_char );
	}

	sqlite3_reset( ps_select_clar_msg );
	sqlite3_clear_bindings( ps_select_clar_msg );

	if(private_byte == 1)
	{
		sqlite3_bind_int( ps_select_ipaddr_acc_cr, 1, account_id );
		sqlite3_rc = sqlite3_step( ps_select_ipaddr_acc_cr );
		if( sqlite3_rc == SQLITE_ROW )
		{
			dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_acc_cr, 0 ) );
			serverproto_clar_reply( dest_ipaddr, OPSR_TEAM, clar_id, msg_wchar, result_string );
			free( dest_ipaddr );
		}

		sqlite3_reset( ps_select_ipaddr_acc_cr );
		sqlite3_clear_bindings( ps_select_ipaddr_acc_cr );
	}
	else if(private_byte == 0)
	{
		sqlite3_bind_int( ps_select_ipaddr_cr, 1, OPSR_TEAM );
		while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_cr ) ) == SQLITE_ROW )
		{
			dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_cr, 0 ) );
			serverproto_clar_reply( dest_ipaddr, OPSR_TEAM, clar_id, msg_wchar, result_string );
			free( dest_ipaddr );
		}

		sqlite3_reset( ps_select_ipaddr_cr );
		sqlite3_clear_bindings( ps_select_ipaddr_cr );
	}

	/* reply to judge and admin */
	sqlite3_bind_int( ps_select_ipaddr_cr, 1, OPSR_ADMIN );
	while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_cr ) ) == SQLITE_ROW )
	{
		dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_cr, 0 ) );
		serverproto_clar_reply( dest_ipaddr, OPSR_ADMIN, clar_id, msg_wchar, result_string );
		free( dest_ipaddr );
	}

	sqlite3_reset( ps_select_ipaddr_cr );
	sqlite3_clear_bindings( ps_select_ipaddr_cr );

	sqlite3_bind_int( ps_select_ipaddr_cr, 1, OPSR_JUDGE );
	while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_cr ) ) == SQLITE_ROW )
	{
		dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_cr, 0 ) );
		serverproto_clar_reply( dest_ipaddr, OPSR_JUDGE, clar_id, msg_wchar, result_string );
		free( dest_ipaddr );
	}

	sqlite3_reset( ps_select_ipaddr_cr );
	sqlite3_clear_bindings( ps_select_ipaddr_cr );

	free( msg_wchar );
	free( result_string_char );
}

void callback_clar_sync( char *srcip, short srctype )
{
	int sqlite3_rc;
	int private_byte;
	unsigned int clar_id, account_id;
	wchar_t *msg_wchar, *account_wchar;
	char *msg_char, *account_char;

	while( ( sqlite3_rc = sqlite3_step( ps_select_unrep_clar ) ) == SQLITE_ROW )
	{
		clar_id = sqlite3_column_int( ps_select_unrep_clar, 0 );
		account_id = sqlite3_column_int( ps_select_unrep_clar, 1 );
		msg_char = dyn_strcpy( sqlite3_column_text( ps_select_unrep_clar, 2 ) );
		private_byte = sqlite3_column_int( ps_select_unrep_clar, 3 );
		account_char = dyn_strcpy( sqlite3_column_text( ps_select_unrep_clar, 4 ) );

		msg_wchar = u8_to_u16( msg_char );
		account_wchar = u8_to_u16( account_char );

		serverproto_clar_request( srcip, srctype, clar_id, account_id, account_wchar, private_byte, msg_wchar);

		free( msg_char );
		free( account_char );
		free( msg_wchar );
		free( account_wchar );
	}

	sqlite3_reset( ps_select_unrep_clar );
}


/* database tool function below */
/* sets contest state for clients */
void serverdb_contest( int (*serverproto)(const char *destip, short desttype), short desttype )
{
	int sqlite3_rc;
	char *dest_ipaddr;

	sqlite3_bind_int( ps_select_ipaddr_sdbc, 1, desttype );
	while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_sdbc ) ) == SQLITE_ROW )
	{
		dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_sdbc, 0 ) );
		(*serverproto)( dest_ipaddr, desttype );
		free( dest_ipaddr );
	}

	sqlite3_reset( ps_select_ipaddr_sdbc );
	sqlite3_clear_bindings( ps_select_ipaddr_sdbc );
}

/* notify all team clients about changes on a problem */
void serverdb_problem_change( unsigned int FUNC, unsigned int problem_id, wchar_t *problem_name )
{
	int sqlite3_rc;
	char *dest_ipaddr;

	sqlite3_bind_int( ps_select_ipaddr_sdbpc, 1, OPSR_TEAM );
	while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_sdbpc ) ) == SQLITE_ROW )
	{
		dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_sdbpc, 0 ) );

		if(FUNC == PROBLEM_CHANGE_ADD)
			serverproto_problem_change_add( dest_ipaddr, problem_id, problem_name );
		else if(FUNC == PROBLEM_CHANGE_DEL)
			serverproto_problem_change_del( dest_ipaddr, problem_id );
		else if(FUNC == PROBLEM_CHANGE_MOD)
			serverproto_problem_change_mod( dest_ipaddr, problem_id, problem_name );

		free( dest_ipaddr );
	}

	sqlite3_reset( ps_select_ipaddr_sdbpc );
	sqlite3_clear_bindings( ps_select_ipaddr_sdbpc );
}

/* request clarification to admin and judge clients */
void serverdb_clar_request( short desttype, unsigned int clar_id, unsigned int account_id, int private_byte, wchar_t *clarmsg )
{
	int sqlite3_rc;
	wchar_t *account_wchar;
	char *account_char;
	char *dest_ipaddr;

	sqlite3_bind_int( ps_select_ipaddr_sdbcr, 1, desttype );
	while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_sdbcr ) ) == SQLITE_ROW )
	{
		dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_sdbcr, 0 ) );
		account_char = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_sdbcr, 1 ) );

		account_wchar = u8_to_u16( account_char );

		serverproto_clar_request( dest_ipaddr, desttype, clar_id, account_id, account_wchar, private_byte, clarmsg );

		free( dest_ipaddr );
		free( account_char );
		free( account_wchar );
	}

	sqlite3_reset( ps_select_ipaddr_sdbcr );
	sqlite3_clear_bindings( ps_select_ipaddr_sdbcr );
}

void serverdb_sb_update( short desttype, unsigned int upd_acc_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time )
{
	int sqlite3_rc;
	char *dest_ipaddr;

	sqlite3_bind_int( ps_select_ipaddr_sdbsbu, 1, desttype );
	while( ( sqlite3_rc = sqlite3_step( ps_select_ipaddr_sdbsbu ) ) == SQLITE_ROW )
	{
		dest_ipaddr = dyn_strcpy( sqlite3_column_text( ps_select_ipaddr_sdbsbu, 0 ) );
		serverproto_sb_update( dest_ipaddr, desttype, upd_acc_id, new_account, new_accept_count, new_time );
		free( dest_ipaddr );
	}

	sqlite3_reset( ps_select_ipaddr_sdbsbu );
	sqlite3_clear_bindings( ps_select_ipaddr_sdbsbu );
}
