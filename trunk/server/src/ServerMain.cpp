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



ServerFrame::ServerFrame(wxFrame *frame)
    : ServerGUI(frame)
{
	/* cb_submission_request() needs subdirectory to store submit files */
	system("mkdir submit_temp");
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
	char insertsql[100];
	char account_char[20];
	
	wcstombs(account_char, account, 20);
	sprintf(insertsql, "INSERT INTO user VALUES(NULL, '%s', '%s', '%d', '%s', 'yes');", account_char, password, &srctype, scrip);
	sqlite3_exec(db, insertsql, 0, 0, &errMsg);
}

void cb_logout_request( char *srcip, short srctype, unsigned int account_id )
{
	char insertsql[100];
	sprintf(insertsql, "UPDATE user SET logged_in = 'no' WHERE account_id = '%d';", &account_id);
	sqlite3_exec(db, insertsql, 0, 0, &errMsg);
}

//the function needs a subdirectory "submit_temp/"
void cb_submission_request( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code )
{
	char insertsql[100];
	char coding_language_char[10];
	char path_code_char[30];
	
	sprintf(path_code_char, "submit_temp/submit%d.txt", sqlite3_last_insert_rowid(db) + 1);
	wcstombs(coding_language_char, coding_language, 10);
	sprintf(insertsql, "INSERT INTO submission(NULL, '%d', '%d', '%s', %s, NULL);", &account_id, &problem_id, coding_language_char, path_code_char);
	sqlite3_exec(db, insertsql, 0, 0, &errMsg);
	mbstowcs( *path_code, path_code_char, 30 );
}

void cb_submission_request_dlfin( char *srcip, unsigned int account_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code )
{
}

void cb_clar_request( char *srcip, unsigned int account_id, int private_byte, wchar_t *clarmsg )
{
}

void cb_pd_request( char *srcip, unsigned int account_id, unsigned int problem_id )
{
}

void cb_run_result_notify( char *srcip, unsigned int run_id, wchar_t *result )
{
}

void cb_account_add( char *srcip, unsigned int type, wchar_t *account, char *password )
{
}

void cb_account_del( char *srcip, unsigned int account_id )
{
}

void cb_account_mod( char *srcip, unsigned int account_id, wchar_t *new_account, char *new_password )
{
}

void cb_account_update( char *srcip )
{
}

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
}

