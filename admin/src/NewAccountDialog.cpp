#include "NewAccountDialog.h"
#include <wx/wx.h>
extern "C"
{
#include "adminproto.h"
}

extern char server_ip[20];

NewAccountDialog::NewAccountDialog(wxWindow *parent) : NewAccountGUI(parent){
}

NewAccountDialog::~NewAccountDialog(){
}

void NewAccountDialog::OnClose( wxCloseEvent& event ){
	EndModal(0);
	return;
}

void NewAccountDialog::OnButtonClickOK( wxCommandEvent& event ){
	wchar_t *id = m_textCtrlID->GetValue().wchar_str();
	char *pw = m_textCtrlPassword->GetValue().char_str();
	
	return;
}

void NewAccountDialog::OnButtonClickCancel( wxCommandEvent& event ){
	EndModal(0);
	return;
}