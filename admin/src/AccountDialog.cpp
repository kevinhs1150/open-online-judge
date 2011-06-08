#include "AccountDialog.h"
#include <wx/wx.h>
extern "C"
{
#include "adminproto.h"
}

extern char server_ip[20];

AccountDialog::AccountDialog(wxWindow *parent, wxString name, unsigned int type, unsigned int account_id) : AccountGUI(parent){
	if(name == wxEmptyString){
		newAccount = true;
	}
	else{
		newAccount = false;
		if(type == SRC_ADMIN)
			m_radioBtnAdmin->SetValue(true);
		else if(type == SRC_JUDGE)
			m_radioBtnJudge->SetValue(true);
		else
			m_radioBtnTeam->SetValue(true);
		
		m_textCtrlID->SetValue(name);
	}
}

AccountDialog::~AccountDialog(){
}

void AccountDialog::OnClose( wxCloseEvent& event ){
	EndModal(0);
	return;
}

void AccountDialog::OnButtonClickOK( wxCommandEvent& event ){
	int type;
	if(m_radioBtnAdmin->GetValue())
		type = SRC_ADMIN;
	else if(m_radioBtnJudge->GetValue())
		type = SRC_JUDGE;
	else if(m_radioBtnTeam->GetValue())
		type = SRC_TEAM;
	else{
		wxMessageBox(_("Please select a type for this account."));
		return;
	}
		
	if(m_textCtrlID->IsEmpty()){
		wxMessageBox(_("ID cannot be empty!"));
		return;
	}
	if(m_textCtrlPassword->IsEmpty()){
		wxMessageBox(_("Password cannot be empty!"));
		return;
	}
	wchar_t *id = new wchar_t [wcslen(m_textCtrlID->GetValue().c_str()) + 1];
	wcscpy( id, m_textCtrlID->GetValue().c_str() );
	char *pw = new char [strlen(m_textCtrlPassword->GetValue().mb_str()) + 1];
	strcpy( pw, m_textCtrlPassword->GetValue().mb_str() );
	
	if(adminproto_account_add(server_ip, type, id, pw) < 0){
		wxMessageBox(_("Error!"));
		return;
	}
	EndModal(1);
	return;
}

void AccountDialog::OnButtonClickCancel( wxCommandEvent& event ){
	EndModal(0);
	return;
}