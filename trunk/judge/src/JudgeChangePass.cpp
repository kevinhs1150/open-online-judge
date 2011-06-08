#include "JudgeMain.h"
#include "JudgeChangePass.h"
extern "C"
{
    #include "judgeproto.h"
}

extern JudgeChangePassFrame *changePassFrame;

void password_change_confirm( int confirm_code );

JudgeChangePassFrame::JudgeChangePassFrame(wxFrame *frame)
    : ChangePassGUI(frame)
{
	judgeproto_cbreg_password_change_confirm( password_change_confirm );
}

JudgeChangePassFrame::~JudgeChangePassFrame()
{
}

void JudgeChangePassFrame::set_account_id(unsigned int account_id)
{
	this->account_id = account_id;
}

void JudgeChangePassFrame::IP_set()
{
    FILE *fptr1;

    fptr1=fopen("config.txt","r");
    fscanf (fptr1, "%s", IP);
    fclose(fptr1);
}

void JudgeChangePassFrame::textCtrlClear()
{
	m_textCtrlOldPass->Clear();
	m_textCtrlNewPass->Clear();
	m_textCtrlConfirmPass->Clear();
}

void JudgeChangePassFrame::OnButtonClickOK( wxCommandEvent& event )
{
	char oldPass[50];
	char newPass[50];
	char confirmPass[50];
	
	if((m_textCtrlOldPass->GetValue()) == wxEmptyString || (m_textCtrlNewPass->GetValue()) == wxEmptyString || (m_textCtrlConfirmPass->GetValue()) == wxEmptyString){
        wxMessageBox(wxT("Change Password Error.\nPromble: Old password, new password or confirm password isn't entered."),wxT("Change Password Error"),wxOK|wxICON_EXCLAMATION);
		textCtrlClear();
    }
    else{
        wxString getOldPassword = m_textCtrlOldPass->GetValue();
        wxString getNewPassword = m_textCtrlNewPass->GetValue();
        wxString getConfirmPass = m_textCtrlConfirmPass->GetValue();

        strcpy(oldPass, getOldPassword.mb_str());
        strcpy(newPass, getNewPassword.mb_str());
        strcpy(confirmPass, getConfirmPass.mb_str());
		
		if(strcmp(newPass,confirmPass)){
			wxMessageBox(wxT("Change Password Error.\nPromble: New password and confirm password are not the same."),wxT("Change Password Error"),wxOK|wxICON_EXCLAMATION);
			textCtrlClear();
			return;
		}
		
		if((judgeproto_password_change( this->IP, this->account_id, oldPass, newPass )) != 0){
			wxMessageBox(wxT("Change Password Error.\nPromble: Socket error."),wxT("Change Password Error"),wxOK|wxICON_EXCLAMATION);
			textCtrlClear();
		}
    }
}

void JudgeChangePassFrame::OnButtonClickCancel( wxCommandEvent& event )
{
	Destroy();
}

void password_change_confirm( int confirm_code )
{
	if(confirm_code == PASSWD_SUCCESS){
		changePassFrame->Destroy();
	}
	else if(confirm_code == PASSWD_MISMATCH){
		wxMessageBox(wxT("Change Password Error.\nPromble: Old password is WRONG."),wxT("Change Password Error"),wxOK|wxICON_EXCLAMATION);
		changePassFrame->textCtrlClear();	
	}
	else if(confirm_code == PASSWD_INVALID){
		wxMessageBox(wxT("Change Password Error.\nPromble: Password is invalid."),wxT("Change Password Error"),wxOK|wxICON_EXCLAMATION);
		changePassFrame->textCtrlClear();	
	}
}