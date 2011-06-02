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
	int ip1, ip2, ip3, ip4;
	FILE *ipFile;
	ipFile = fopen("ip.txt", "r");
	
	if(ipFile == NULL){
		wxMessageBox(_("ip.txt not found!"));
		EndModal(0);
	}
	
	if(fscanf(ipFile, "%d.%d.%d.%d", &ip1, &ip2, &ip3, &ip4) != 4){
		wxMessageBox(_("Invalid IP Address!"));
		EndModal(0);
	}
	
	sprintf(ip, "%d.%d.%d.%d", ip1, ip2, ip3, ip4);
	wchar_t *id = m_textCtrlID->GetValue().wchar_str();
	char *pw = m_textCtrlPassword->GetValue().char_str();
	adminproto_login(ip, id, pw);
	
}

void LoginDialog::OnButtonClickExit( wxCommandEvent& event ){
	EndModal(0);
}