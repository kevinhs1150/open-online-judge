#include "LoginDialog.h"
#include <wx/wx.h>

LoginDialog::LoginDialog(wxWindow *parent) : LoginGUI(parent){
	
}

LoginDialog::~LoginDialog(){

}

void LoginDialog::OnClose( wxCloseEvent& event ){
	EndModal(0);
}

void LoginDialog::OnButtonClickLogin( wxCommandEvent& event ){
	wchar_t *id = m_textCtrlID->GetValue().wchar_str();
	char *pw = m_textCtrlPassword->GetValue().char_str();
	//adminproto_login( char *destip, wchar_t *account, char *password )
}

void LoginDialog::OnButtonClickExit( wxCommandEvent& event ){
	EndModal(0);
}