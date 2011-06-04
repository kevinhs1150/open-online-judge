#include "AdminMain.h"
extern "C"
{
#include "adminproto.h"
}

AdminFrame* AdminFrameGlobal;

char server_ip[20];
unsigned int login_id;
LoginDialog* loginDialog;

/* callback functions */
void cb_account_update( unsigned int account_id, unsigned int type, wchar_t *account ){
	wxString name(account);
	if(type == SRC_ADMIN){
		AdminFrameGlobal->m_listCtrlAdmin->InsertItem(account_id, name);
	}
	else if(type == SRC_JUDGE){
		AdminFrameGlobal->m_listCtrlJudge->InsertItem(account_id, name);
	}
	else if(type == SRC_TEAM){
		AdminFrameGlobal->m_listCtrlTeam->InsertItem(account_id, name);
	}
	else{
		// no definition, it must a mistake!
	}
}

void cb_problem_update( unsigned int problem_id, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer )
{
}

void cb_problem_update_dlfin( unsigned int problem_id, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer )
{
}


/* callback functions extern-ed from protointernal.c */
void cb_login_confirm( int confirm_code, unsigned int account_id ){
	if(confirm_code == LOGIN_VALID){
		login_id = account_id;
		loginDialog->LoginSuccess();
	}
	else if(confirm_code == LOGIN_ACC_NOTEXIST){
		wxMessageBox(_("Account not exist!"));
	}
	else if(confirm_code == LOGIN_PASS_WRONG){
		wxMessageBox(_("Wrong password!"));
	}
	return;
}

void cb_logout_confirm( int confirm_code ){

}

void cb_timer_set( unsigned int hours, unsigned int minutes, unsigned int seconds ){

}

void cb_contest_start( void ){

}

void cb_contest_stop( void ){

}

void cb_clar_request( unsigned int clar_id, unsigned int account_id, wchar_t *account, int private_byte, wchar_t *clarmsg ){

}

void cb_clar_reply( unsigned int clar_id, wchar_t *clarmsg, wchar_t *result_string ){

}

void cb_sb_update( unsigned int updated_account_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time ){

}

AdminFrame::AdminFrame(wxFrame *frame)
    : AdminGUI(frame)
{
	char localaddr[20];
	int ip1, ip2, ip3, ip4;
	FILE *ipFile;
	
	AdminFrameGlobal = this;
	
	loginDialog = new LoginDialog(NULL);
	
	adminproto_cbreg_login_confirm( cb_login_confirm );
	adminproto_cbreg_logout_confirm( cb_logout_confirm );
	adminproto_cbreg_timer_set( cb_timer_set );
	adminproto_cbreg_contest_start( cb_contest_start );
	adminproto_cbreg_contest_stop( cb_contest_stop );
	adminproto_cbreg_clar_request( cb_clar_request );
	adminproto_cbreg_clar_reply( cb_clar_reply );
	adminproto_cbreg_account_update( cb_account_update );
	adminproto_cbreg_problem_update( cb_problem_update );
	adminproto_cbreg_problem_update_dlfin( cb_problem_update_dlfin );
	adminproto_cbreg_sb_update( cb_sb_update );
	
	sprintf(localaddr, "0.0.0.0");
	ipFile = fopen("ip.txt", "r");
	if(ipFile == NULL){
		wxMessageBox(_("ip.txt not found!"));
		isLogin = false;
	}
	else if(fscanf(ipFile, "%d.%d.%d.%d", &ip1, &ip2, &ip3, &ip4) != 4){
		wxMessageBox(_("Invalid IP Address!"));
		isLogin = false;
	}
	else if(adminproto_listen(localaddr) < 0){
		wxMessageBox(_("Listen Error!"));
		isLogin = false;
	}
	else{
		sprintf(server_ip, "%d.%d.%d.%d", ip1, ip2, ip3, ip4);
		if(loginDialog->ShowModal() == 0)
			isLogin = false;
		else
			isLogin = true;
	}
	loginDialog->Destroy();
}

AdminFrame::~AdminFrame()
{
}

/*
void AdminFrame::OnClose( wxCloseEvent& event ){
	//Destroy();
}
*/

void AdminFrame::OnButtonClickChangePassword( wxCommandEvent& event ){

}

void AdminFrame::OnButtonClickLogout( wxCommandEvent& event ){

}

void AdminFrame::OnButtonClickNewAccount( wxCommandEvent& event ){

}

void AdminFrame::OnButtonClickDeleteAccount( wxCommandEvent& event ){

}

void AdminFrame::OnButtonClickAddProblem( wxCommandEvent& event ){
	m_textCtrlProblemName->Clear();
}

void AdminFrame::OnButtonClickDelProblem( wxCommandEvent& event ){
	event.Skip();
}
