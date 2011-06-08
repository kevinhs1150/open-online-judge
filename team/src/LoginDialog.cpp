#include "LoginDialog.h"
#include <wx/wx.h>
extern "C"
{
    #include "teamproto.h"
}

extern char server_ip[20];

LoginDialog::LoginDialog(wxWindow *parent) : LoginGUI(parent){

}

LoginDialog::~LoginDialog(){

}

void LoginDialog::OnClose( wxCloseEvent& event ){
	EndModal(0);
	return;
}

void LoginDialog::OnButtonClickLogin( wxCommandEvent& event ){
	wchar_t *id = new wchar_t [wcslen(m_textCtrlID->GetValue().c_str()) + 1];
	wcscpy( id, m_textCtrlID->GetValue().c_str() );
	m_loginName = m_textCtrlID->GetValue();
	char *pw = new char [strlen(m_textCtrlPassword->GetValue().mb_str()) + 1];
	strcpy( pw, m_textCtrlPassword->GetValue().mb_str() );

	if(teamproto_login(server_ip, id, pw) < 0)
		wxMessageBox(_("Server not responding"));

    delete id;
	delete pw;
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
