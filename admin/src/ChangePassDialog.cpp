#include "ChangePassDialog.h"
#include <wx/wx.h>
extern "C"
{
#include "adminproto.h"
}

extern char server_ip[20];
extern unsigned int login_id;

ChangePassDialog::ChangePassDialog(wxWindow *parent) : ChangePassGUI(parent){
}

ChangePassDialog::~ChangePassDialog(){
}

void ChangePassDialog::OnClose( wxCloseEvent& event ){
	EndModal(0);
	return;
}

void ChangePassDialog::OnButtonClickOK( wxCommandEvent& event ){
	if(m_textCtrlNewPass->GetValue() != m_textCtrlConfirmPass->GetValue()){
		wxMessageBox(_("Passwords not match!"));
		return;
	}
	char *old_pw = new char [strlen(m_textCtrlOldPass->GetValue().mb_str()) + 1];
	strcpy( old_pw, m_textCtrlOldPass->GetValue().mb_str() );
	char *new_pw = new char [strlen(m_textCtrlNewPass->GetValue().mb_str()) + 1];
	strcpy( new_pw, m_textCtrlNewPass->GetValue().mb_str() );
	
	adminproto_password_change( server_ip, login_id, old_pw, new_pw );
	
	return;
}

void ChangePassDialog::OnButtonClickCancel( wxCommandEvent& event ){
	EndModal(0);
	return;
}

void ChangePassDialog::ChangeSuccess(){
	EndModal(1);
	return;
}