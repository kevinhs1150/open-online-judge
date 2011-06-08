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
	wchar_t *id = m_textCtrlID->GetValue().wchar_str();
	char *pw = m_textCtrlPassword->GetValue().char_str();

	if(teamproto_login(server_ip, id, pw) < 0)
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
