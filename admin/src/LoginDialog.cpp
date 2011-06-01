#include "LoginDialog.h"
#include <wx/wx.h>
extern "C"
{
#include "adminproto.h"
}

LoginDialog::LoginDialog(wxWindow *parent) : LoginGUI(parent){
	
}

LoginDialog::~LoginDialog(){

}

void LoginDialog::OnClose( wxCloseEvent& event ){
	EndModal(0);
}

void LoginDialog::OnButtonClickLogin( wxCommandEvent& event ){
	char ip[20];
	sprintf(ip, "127.0.0.1");
	wchar_t *id = m_textCtrlID->GetValue().wchar_str();
	char *pw = m_textCtrlPassword->GetValue().char_str();
	adminproto_login(ip, id, pw);
}

void LoginDialog::OnButtonClickExit( wxCommandEvent& event ){
	EndModal(0);
}