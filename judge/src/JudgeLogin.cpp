#include "JudgeMain.h"

JudgeLoginFrame::JudgeLoginFrame(wxFrame *frame)
    : LoginGUI(frame)
{
}

JudgeLoginFrame::~JudgeLoginFrame()
{
}

void JudgeLoginFrame::OnClose( wxCloseEvent& event )
{
	Destroy();
}

void JudgeLoginFrame::OnTextEnterPassword( wxCommandEvent& event )
{
    login();
}
void JudgeLoginFrame::OnButtonClickLogin( wxCommandEvent& event )
{
    login();
}
void JudgeLoginFrame::OnButtonClickExit( wxCommandEvent& event )
{
    EndModal(-1);
}

void JudgeLoginFrame::login()
{
    wchar_t ID[20];
    char password[50];
    FILE *fptr1;
    char IP[20];

    if(m_textCtrlID->isEmpty || m_textCtrlPassword->isEmpty){
        wxMessageBox("Login Error.\nPromble: ID or password isn't entered.","Login Error",wxOK|wxICON_EXCLAMATION);
        m_textCtrlPassword->Clear();
    }
    else{
        wxString getID = m_textCtrlID->GetValue();
        wxString getPassword = m_textCtrlPassword->GetValue();

        wcscpy(ID, getID.wc_str());
        strcpy(password, getPassword.mb_str());

        fptr1=fopen("config.txt","r");
        fscanf (fptr1, "%s", IP);

        judgeproto_login(IP, ID, password );
    }
}

void JudgeLoginFrame::cleanPassword()
{
    m_textCtrlPassword->Clear();
}
