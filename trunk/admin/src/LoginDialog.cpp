#include "LoginDialog.h"
#include <wx/wx.h>
extern "C"
{
#include "adminproto.h"
}

extern char server_ip[20];
extern wxString m_loginName;

LoginDialog::LoginDialog(wxWindow *parent) : LoginGUI(parent){
}

LoginDialog::~LoginDialog(){
}

void LoginDialog::OnClose( wxCloseEvent& event ){
	EndModal(0);
	return;
}

void LoginDialog::OnButtonClickLogin( wxCommandEvent& event ){
	wchar_t *id = m_textCtrlID->GetValue().wchar_str();
	m_loginName = m_textCtrlID->GetValue();
	char *pw = m_textCtrlPassword->GetValue().char_str();
	
	if(adminproto_login(server_ip, id, pw) < 0)
		wxMessageBox(_("Server not responding"));
	
	return;
}

void LoginDialog::OnButtonClickExit( wxCommandEvent& event ){
	EndModal(0);
	return;
}

void LoginDialog::LoginSuccess(){
	EndModal(1);
	return;
}