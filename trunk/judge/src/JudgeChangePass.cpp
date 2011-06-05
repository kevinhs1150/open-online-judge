#include "JudgeMain.h"
extern "C"
{
    #include "judgeproto.h"
}

JudgeChangePassFrame::JudgeChangePassFrame(wxFrame *frame)
    : JudgeChangePassGUI(frame)
{
	judgeproto_cbreg_password_change_confirm( password_change_confirm );
}

JudgeChangePassFrame::~JudgeChangePassFrame()
{
}

void JudgeChangePassFrame::OnButtonClickOK( wxCommandEvent& event )
{
	char oldPass[50];
	char newPass[50];
	char confirmPass[50];
	
	if(m_textCtrlOldPass->isEmpty || m_textCtrlNewPass->isEmpty || m_textCtrlConfirmPass->isEmpty){
        wxMessageBox("Change Password Error.\nPromble: Old password, new password or confirm password isn't entered.","Change Password Error",wxOK|wxICON_EXCLAMATION);
        m_textCtrlOldPass->Clear();
		m_textCtrlNewPass->Clear();
		m_textCtrlConfirmPass->Clear();
    }
    else{
        wxString getOldPassword = m_textCtrlOldPass->GetValue();
        wxString getNewPassword = m_textCtrlNewPass->GetValue();
        wxString getConfirmPass = m_textCtrlConfirmPass->GetValue();

        strcpy(oldPass, getOldPassword.mb_str());
        strcpy(newPass, getNewPassword.mb_str());
        strcpy(confirmPass, getConfirmPass.mb_str());
		
		if(strcmp(newPass,confirmPass)){
			wxMessageBox("Change Password Error.\nPromble: New password and confirm password are not the same.","Change Password Error",wxOK|wxICON_EXCLAMATION);
			m_textCtrlOldPass->Clear();
			m_textCtrlNewPass->Clear();
			m_textCtrlConfirmPass->Clear();
			return;
		}
		if(1){/**ÂÂ±K½X¿ù»~ from server**/
			wxMessageBox("Change Password Error.\nPromble: Old password is WRONG.","Change Password Error",wxOK|wxICON_EXCLAMATION);
			m_textCtrlOldPass->Clear();
			m_textCtrlNewPass->Clear();
			m_textCtrlConfirmPass->Clear();
			return;
		}
		/**ÅÜ§ó±K½X to server**/
		Destroy();
    }
}

void JudgeChangePassFrame::OnButtonClickCancel( wxCommandEvent& event )
{
	Destroy();
}

void password_change_confirm( int confirm_code )
{
	
}