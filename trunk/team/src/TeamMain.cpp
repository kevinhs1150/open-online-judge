#include "TeamMain.h"
#include "LoginDialog.h"
extern "C"
{
    #include "teamproto.h"
}
#include <string.h>

void cb_login_confirm( int confirm_code, unsigned int account_id );
void cb_logout_confirm( int confirm_code );
void cb_password_change_confirm( confirm_code );
void cb_timer_set( unsigned int hours, unsigned int minutes, unsigned int seconds );
void cb_contest_start( void );
void cb_contest_stop( void );
void cb_run_reply( unsigned int run_id, wchar_t *result_string );
void cb_clar_reply( unsigned int clar_id, wchar_t *result_string );
void cb_sb_update( unsigned int updated_account_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time );
void cb_pu_request( wchar_t **path_description );
void cb_pu_request_dlfin( wchar_t *path_description );
void cb_problem_add( unsigned int problem_id, wchar_t *problem_name ) );
void cb_problem_del( unsigned int problem_id ) );
void cb_problem_mod( unsigned int problem_id, wchar_t *problem_name ) );

//global variables
char server_ip[20];
unsigned int login_id;
unsigned int max_problem_id = 0;
TeamFrame* TeamFrameGlobal;
LoginDialog* logindialog;
ChangePassDialog* changepassdialog;
SubmitConfirmDialog* submitconfirmdialog;
ClarDialog* clardialog;
ClarConfirmDialog* clarconfirmdialog;



///////////////////////////////////////////////////////////////////////////////
/// TeamFrame
///////////////////////////////////////////////////////////////////////////////
TeamFrame::TeamFrame(wxFrame *frame)
    : TeamGUI(frame)
{
    TeamFrameGlobal = this;
    int ip1, ip2, ip3, ip4;
	FILE *ipFile;
	wxListItem itemCol;

    teamproto_cbreg_login_confirm( cb_login_confirm );
    teamproto_cbreg_logout_confirm( cb_logout_confirm );
    teamproto_cbreg_password_change_confirm( cb_password_change_confirm );
    teamproto_cbreg_timer_set( cb_timer_set );
    teamproto_cbreg_contest_start( cb_contest_start );
    teamproto_cbreg_contest_stop( cb_contest_stop );
    teamproto_cbreg_run_reply( cb_run_reply );
    teamproto_cbreg_clar_reply( cb_clar_reply );
    teamproto_cbreg_sb_update( cb_sb_update );
    teamproto_cbreg_pu_request( cb_pu_request );
    teamproto_cbreg_pu_request_dlfin( cb_pu_request_dlfin );
    teamproto_cbreg_problem_add(cb_problem_add);
    teamproto_cbreg_problem_del(cb_problem_del);
    teamproto_cbreg_problem_mod(cb_problem_mod);

    //Load IP setting
	ipFile = fopen("ip.txt", "r");
	if(ipFile == NULL){
		wxMessageBox(_("ip.txt not found!"));
		Destroy();
	}
	else if(fscanf(ipFile, "%d.%d.%d.%d", &ip1, &ip2, &ip3, &ip4) != 4){
		wxMessageBox(_("Invalid IP Address!"));
		Destroy();
	}
	else if(teamproto_listen("0.0.0.0") < 0){
		wxMessageBox(_("Listen Error!"));
		Destroy();
	}
	else{
		sprintf(server_ip, "%d.%d.%d.%d", ip1, ip2, ip3, ip4);
		//pop out LoginDialog
		logindialog = new LoginDialog();
		if(logindialog->ShowModal() == 0){
			logindialog->Destroy();
			Destroy();
		}
    }

    itemCol.SetText(_("ID"));
	m_listCtrlRuns->InsertColumn(0, itemCol);
	m_listCtrlClars->InsertColumn(0, itemCol);
	m_listCtrlScore->InsertColumn(0, itemCol);

	itemCol.SetText(_("Result"));
    m_listCtrlRuns->InsertColumn(1, itemCol);
	m_listCtrlClars->InsertColumn(1, itemCol);

	itemCol.SetText(_("Team"));
	m_listCtrlScore->InsertColumn(1, itemCol);
	itemCol.SetText(_("Accept"));
	m_listCtrlScore->InsertColumn(2, itemCol);
	itemCol.SetText(_("Time"));
	m_listCtrlScore->InsertColumn(3, itemCol);
}

TeamFrame::~TeamFrame()
{

}

void TeamFrame::OnButtonClickChangePassword( wxCommandEvent& event )
{
    changepassdialog = new ChangePassDialog;
    changepassdialog->ShowModal();
    changepassdialog->Destroy();
}

void TeamFrame::OnButtonClickLogout( wxCommandEvent& event )
{
    teamproto_logout(server_ip, login_id);
}

void TeamFrame::OnButtonClickDownload( wxCommandEvent& event )
{
    teamproto_problem_download(server_ip, login_id, m_choiceProblem->GetCurrentSelection());
}

void TeamFrame::OnButtonClickTest( wxCommandEvent& event )
{

}

void TeamFrame::OnButtonClickSubmit( wxCommandEvent& event )
{
    submitconfirmdialog = new SubmitConfirmDialog();
    submitconfirmdialog->ShowModal();
    submitconfirmdialog->Destroy();
}

void TeamFrame::OnButtonClickAsk( wxCommandEvent& event )
{
    clardialog = new ClarDialog();
    clardialog->ShowModal();
    clardialog->Destroy();
}



///////////////////////////////////////////////////////////////////////////////
/// ChangePassDialog
///////////////////////////////////////////////////////////////////////////////
ChangePassDialog::ChangePassDialog(wxFrame *frame)
{

}

ChangePassDialog::~ChangePassDialog()
{

}

void ChangePassDialog::OnButtonClickOK( wxCommandEvent& event )
{
    cahr* op = new char [strlen(m_textCtrlOldPass->GetValue().mb_str()) + 1];
    strcpy( op, m_textCtrlOldPass->GetValue().mb_str());
    cahr* np = new char [strlen(m_textCtrlNewPass->GetValue().mb_str()) + 1];
    strcpy( np, m_textCtrlNewPass->GetValue().mb_str();
    cahr* cp = new char [strlen(m_textCtrlConfirmPass->GetValue().mb_str()) + 1];
    strcpy( cp, m_textCtrlConfirmPass->GetValue().mb_str();
    if( strcmp(np, cp) == 0 )
        teamproto_password_change(server_ip, login_id, op, np);
    else
        wxMessageBox(_("Confirm Password Error!"));

    delete op;
    delete np;
    delete cp;
    return;
}

void ChangePassDialog::OnButtonClickCancel( wxCommandEvent& event )
{
    EndModal(0);
    return;
}

void ChangePassDialog::ChangeSuccess(){
	EndModal(1);
	return;
}


///////////////////////////////////////////////////////////////////////////////
/// SubmitConfirmDialog
///////////////////////////////////////////////////////////////////////////////
SubmitConfirmDialog::SubmitConfirmDialog(wxFrame *frame)
{
    m_staticTextProblemVal->SetLabel(TeamFrameGlobal->m_choiceProblem->GetStringSelection());
    m_staticTextLangVal->SetLabel(TeamFrameGlobal->m_choiceLang->GetStringSelection());
    m_textCtrlFilePathVal->SetValue(TeamFrameGlobal->m_filePicker->GetPath());
}

SubmitConfirmDialog::~SubmitConfirmDialog()
{

}

void SubmitConfirmDialog::OnButtonClickYes( wxCommandEvent& event )
{
    wchar_t *lang = new wchar_t [wcslen(m_staticTextLangVal->GetLabel().c_str()) + 1];
	wcscpy( lang, m_staticTextLangVal->GetLabel().c_str() );
	wchar_t *path = new wchar_t [wcslen(m_staticTextFilePath->GetLabel().c_str()) + 1];
	wcscpy( path, m_staticTextFilePath->GetLabel().c_str() );

    teamproto_submission(server_ip, login_id, TeamFrameGlobal->m_choiceProblem->GetCurrentSelection(), lang, path);

    delete lang;
    delete path;
    EndModal(1);
	return;
}

void SubmitConfirmDialog::OnButtonClickNo( wxCommandEvent& event )
{
    EndModal(0);
    return;
}



///////////////////////////////////////////////////////////////////////////////
/// ClarDialog
///////////////////////////////////////////////////////////////////////////////
ClarDialog::ClarDialog(wxFrame *frame)
{

}

ClarDialog::~ClarDialog()
{

}

void ClarDialog::OnButtonClickYes( wxCommandEvent& event )
{
    clarconfirmdialog = new ClarConfirmDialog;
    clarconfirmdialog->ShowModal();
    clarconfirmdialog->Destroy();
}

void ClarDialog::OnButtonClickNo( wxCommandEvent& event )
{
    EndModal(0);
    return;
}



///////////////////////////////////////////////////////////////////////////////
/// ClarConfirmDialog
///////////////////////////////////////////////////////////////////////////////
ClarConfirmDialog::ClarConfirmDialog(wxFrame *frame)
{
    m_textCtrlFileQuestion->SetValue(clardialog->m_textCtrlFileQuestion->GetValue());
}

ClarConfirmDialog::~ClarConfirmDialog()
{

}

void ClarConfirmDialog::OnButtonClickYes( wxCommandEvent& event )
{
    wchar_t *temp = new wchar_t [wcslen(m_textCtrlFileQuestion->GetValue().c_str()) + 1];
	wcscpy( temp, m_textCtrlFileQuestion->GetValue().c_str() );
    teamproto_clar(server_ip, login_id, 0, temp);

    delete temp;
    EndModal(1);
    return;
}

void ClarConfirmDialog::OnButtonClickNo( wxCommandEvent& event )
{
    EndModal(0);
    return;
}



///////////////////////////////////////////////////////////////////////////////
/// Callback Functions
///////////////////////////////////////////////////////////////////////////////
void cb_login_confirm( int confirm_code, unsigned int account_id )
{
    if(confirm_code == LOGIN_VALID){
		login_id = account_id;
		logindialog->LoginSuccess();

        teamproto_sb_sync(server_ip);
        teamproto_run_sync(server_ip);
        teamproto_timer_sync(server_ip);
        teamproto_contest_state_sync(server_ip);
	}
	else if(confirm_code == LOGIN_ACC_NOTEXIST){
		wxMessageBox(_("Account not exist!"));
	}
	else if(confirm_code == LOGIN_PASS_WRONG){
		wxMessageBox(_("Wrong password!"));
	}
	return;
}

void cb_logout_confirm( int confirm_code )
{
    if(confirm_code == LOGOUT_OK){
		wxMessageBox(_("Logout success!"));
		login_id = NULL;
		if(logindialog->ShowModal() == 0){
			logindialog->Destroy();
			Destroy();
		}
	}
	else if(confirm_code == LOGOUT_FAIL){
		wxMessageBox(_("Logout fail!"));
	}
	return;
}

void cb_password_change_confirm( confirm_code )
{
    if(confirm_code == PASSWD_SUCCESS){
        wxMessageBox(_("Password change success!"));
        changepassdialog->ChangeSuccess();
    }
    else if(confirm_code == PASSWD_MISMATCH){
        wxMessageBox(_("Password change mismatch!"));
    }
    else if(confirm_code == PASSWD_INVALID){
        wxMessageBox(_("Password invalid!"));
    }
}

void cb_timer_set( unsigned int hours, unsigned int minutes, unsigned int seconds )
{

}

void cb_contest_start( void )
{

}

void cb_contest_stop( void )
{

}

void cb_run_reply( unsigned int run_id, wchar_t *result_string )
{

}

void cb_clar_reply( unsigned int clar_id, wchar_t *result_string )
{

}

void cb_sb_update( unsigned int updated_account_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time )
{

}

void cb_pu_request( wchar_t **path_description )
{
    wxString temp;
    do
    {
        temp = wxFileSelector(_("Download File"), _(""), _("problem"), _("pdf"));
    }while( filename.empty() );
    wchar_t *path = malloc( ( wcslen(temp.c_str()) + 1 ) * sizeof( wchar_t ) );
	wcscpy( path, temp.c_str());
	path_description = &path;
}

void cb_pu_request_dlfin( wchar_t *path_description )
{
    wxMessageBox(_("Download Completed!"));
}

void cb_problem_add( unsigned int problem_id, wchar_t *problem_name ) )
{
    for(;max_problem_id <= problem_id; max_problem_id++)
        TeamFrameGlobal->m_choiceProblem.Append(_(""));
    TeamFrameGlobal->m_choiceProblem.SetString(problem_id, wxString(problem_name, wxConvLibc));
}

void cb_problem_del( unsigned int problem_id ) )
{
    TeamFrameGlobal->m_choiceProblem.SetString(problem_id, _(""));
}

void cb_problem_mod( unsigned int problem_id, wchar_t *problem_name ) )
{
    TeamFrameGlobal->m_choiceProblem.SetString(problem_id, wxString(problem_name, wxConvLibc);
}
