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

//global variables
char server_ip[20];
unsigned int login_id;
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

}

void TeamFrame::OnButtonClickTest( wxCommandEvent& event )
{

}

void TeamFrame::OnButtonClickSubmit( wxCommandEvent& event )
{

}

void TeamFrame::OnButtonClickAsk( wxCommandEvent& event )
{
    clardialog = new ClarDialog;
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
    cahr* op = m_textCtrlOldPass->GetValue().char_str();
    cahr* np = m_textCtrlNewPass->GetValue().char_str();
    cahr* cp = m_textCtrlConfirmPass->GetValue().char_str();
    if( strcmp(np, cp) == 0 )
        teamproto_password_change(server_ip, login_id, op, np);
    else
        wxMessageBox(_("Confirm Password Error!"));
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

}

SubmitConfirmDialog::~SubmitConfirmDialog()
{

}

void SubmitConfirmDialog::OnButtonClickYes( wxCommandEvent& event )
{

}

void SubmitConfirmDialog::OnButtonClickNo( wxCommandEvent& event )
{

}



///////////////////////////////////////////////////////////////////////////////
/// ClarDialogDialog
///////////////////////////////////////////////////////////////////////////////
ClarDialogDialog::ClarDialogDialog(wxFrame *frame)
{

}

ClarDialogDialog::~ClarDialogDialog()
{

}

void ClarDialogDialog::OnButtonClickYes( wxCommandEvent& event )
{

}

void ClarDialogDialog::OnButtonClickNo( wxCommandEvent& event )
{

}



///////////////////////////////////////////////////////////////////////////////
/// ClarConfirmDialog
///////////////////////////////////////////////////////////////////////////////
ClarConfirmDialog::ClarConfirmDialog(wxFrame *frame)
{

}

ClarConfirmDialog::~ClarConfirmDialog()
{

}

void ClarConfirmDialog::OnButtonClickYes( wxCommandEvent& event )
{

}

void ClarConfirmDialog::OnButtonClickNo( wxCommandEvent& event )
{

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

}

void cb_pu_request_dlfin( wchar_t *path_description )
{

}
