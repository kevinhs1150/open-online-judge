#include "TeamMain.h"
#include "LoginDialog.h"
extern "C"
{
    #include "teamproto.h"
}
#include <string.h>
#include <stdlib.h>

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_LOCAL_EVENT_TYPE( wxEVT_CALL_TIMER, 7777 )
END_DECLARE_EVENT_TYPES()
DEFINE_EVENT_TYPE( wxEVT_CALL_TIMER )

#define EVT_CALL_TIMER( id, fn )\
    DECLARE_EVENT_TABLE_ENTRY( \
        wxEVT_CALL_TIMER, id, wxID_ANY, \
        (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent( wxCommandEventFunction, &fn ), \
        (wxObject*)NULL\
    ),

BEGIN_EVENT_TABLE(TeamFrame, wxFrame)
    EVT_TIMER(-1, TeamFrame::OnTimerEvent)
	EVT_CALL_TIMER(wxID_ANY, TeamFrame::TimerCall)
END_EVENT_TABLE()

void cb_login_confirm( int confirm_code, unsigned int account_id );
void cb_logout_confirm( int confirm_code );
void cb_password_change_confirm( int confirm_code );
void cb_timer_set( unsigned int hours, unsigned int minutes, unsigned int seconds );
void cb_contest_start( void );
void cb_contest_stop( void );
void cb_run_reply( unsigned int run_id, unsigned int problem_id, wchar_t *result_string );
void cb_clar_reply( unsigned int clar_id, wchar_t *clarmsg, wchar_t *result_string );
void cb_sb_update( unsigned int updated_account_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time );
void cb_sb_remove( unsigned int rm_account_id );
void cb_pu_request( wchar_t **path_description );
void cb_pu_request_dlfin( wchar_t *path_description );
void cb_problem_add( unsigned int problem_id, wchar_t *problem_name );
void cb_problem_del( unsigned int problem_id );
void cb_problem_mod( unsigned int problem_id, wchar_t *problem_name );

//global variables
char server_ip[20];
unsigned int login_id;
unsigned int max_problem_id = 0;
TeamFrame* TeamFrameGlobal;
LoginDialog* logindialog;
ChangePassDialog* changepassdialog;
SubmitConfirmDialog* submitconfirmdialog;
ClarDialog* clardialog;
ClarConfirmDialog* clarconfirmdialog;
ShowClarDialog* showclardialog;
wxMutex mutexRun;
wxMutex mutexClar;
wxMutex mutexScoreboard;
wxMutex mutexProblem;



///////////////////////////////////////////////////////////////////////////////
/// TeamFrame
///////////////////////////////////////////////////////////////////////////////
TeamFrame::TeamFrame(wxFrame *frame)
    : TeamGUI(frame), m_timer(this)
{
    TeamFrameGlobal = this;
    int ip1, ip2, ip3, ip4;
	FILE *ipFile;
	wxListItem itemCol;

    teamproto_cbreg_login_confirm( cb_login_confirm );
    teamproto_cbreg_logout_confirm( cb_logout_confirm );
    teamproto_cbreg_password_change_confirm( cb_password_change_confirm );
    teamproto_cbreg_timer_set( cb_timer_set );
    teamproto_cbreg_contest_start( cb_contest_start );
    teamproto_cbreg_contest_stop( cb_contest_stop );
    teamproto_cbreg_run_reply( cb_run_reply );
    teamproto_cbreg_clar_reply( cb_clar_reply );
    teamproto_cbreg_sb_update( cb_sb_update );
    teamproto_cbreg_sb_remove( cb_sb_remove );
    teamproto_cbreg_pu_request( cb_pu_request );
    teamproto_cbreg_pu_request_dlfin( cb_pu_request_dlfin );
    teamproto_cbreg_problem_add(cb_problem_add);
    teamproto_cbreg_problem_del(cb_problem_del);
    teamproto_cbreg_problem_mod(cb_problem_mod);

    //Load IP setting
	ipFile = fopen("ip.txt", "r");
	if(ipFile == NULL){
		wxMessageBox(_("ip.txt not found!"));
		Destroy();
	}
	else if(fscanf(ipFile, "%d.%d.%d.%d", &ip1, &ip2, &ip3, &ip4) != 4){
		wxMessageBox(_("Invalid IP Address!"));
		Destroy();
	}
	else if(teamproto_listen("0.0.0.0") < 0){
		wxMessageBox(_("Listen Error!"));
		Destroy();
	}
	else{
		sprintf(server_ip, "%d.%d.%d.%d", ip1, ip2, ip3, ip4);
		//pop out LoginDialog
		logindialog = new LoginDialog(this);
		if(logindialog->ShowModal() == 0){
			logindialog->Destroy();
			Destroy();
		}
		m_staticTextTeamName->SetLabel(logindialog->m_textCtrlID->GetValue());
		logindialog->Destroy();
    }

    m_choiceLang->Append(wxString() << _("c"));
    m_choiceLang->Append(wxString() << _("cpp"));
    //m_choiceLang->Append(wxString() << _("cs"));
    //m_choiceLang->Append(wxString() << _("java"));
    //m_choiceLang->Append(wxString() << _("vb"));

    itemCol.SetText(_("ID"));
	m_listCtrlRuns->InsertColumn(0, itemCol);
	m_listCtrlClars->InsertColumn(0, itemCol);
	m_listCtrlScore->InsertColumn(0, itemCol);

	itemCol.SetText(_("Problem"));
    m_listCtrlRuns->InsertColumn(1, itemCol);

    itemCol.SetText(_("Clarmsg"));
	m_listCtrlClars->InsertColumn(1, itemCol);

	itemCol.SetText(_("Result"));
    m_listCtrlRuns->InsertColumn(2, itemCol);
	m_listCtrlClars->InsertColumn(2, itemCol);

	itemCol.SetText(_("Team"));
	m_listCtrlScore->InsertColumn(1, itemCol);
	itemCol.SetText(_("Accept"));
	m_listCtrlScore->InsertColumn(2, itemCol);
	itemCol.SetText(_("Time"));
	m_listCtrlScore->InsertColumn(3, itemCol);

	m_buttonTest->Hide();
}

TeamFrame::~TeamFrame()
{

}

void TeamFrame::OnButtonClickChangePassword( wxCommandEvent& event )
{
    changepassdialog = new ChangePassDialog(this);
    changepassdialog->ShowModal();
    changepassdialog->Destroy();
    return;
}

void TeamFrame::OnButtonClickLogout( wxCommandEvent& event )
{
    teamproto_logout(server_ip, login_id);
    return;
}

void TeamFrame::OnButtonClickDownload( wxCommandEvent& event )
{

    if(m_timer.IsRunning()){
        if(m_choiceProblem->GetStringSelection().IsEmpty()){
            wxMessageBox(_("Plz select problem!"));
        }
        else{
            teamproto_problem_download(server_ip, login_id, m_choiceProblem->GetCurrentSelection());
        }
    }
    else{
        wxMessageBox(_("Contest has not started!"));
    }
    return;
}

void TeamFrame::OnButtonClickTest( wxCommandEvent& event )
{
    wchar_t temp[10];

    swprintf(temp, L"test");

    cb_problem_add( 5, temp );
    cb_problem_add( 3, temp );
    cb_problem_add( 15, temp );
    cb_problem_add( 0, temp );

    cb_run_reply( 1, 3, temp );
    cb_run_reply( 3, 5, temp );
    cb_clar_reply( 1, temp, temp );
    cb_clar_reply( 2, temp, temp );

    cb_sb_update( 2, temp, 1, 1 );
    cb_sb_update( 1, temp, 2, 2 );
    cb_sb_update( 3, temp, 3, 3 );


    swprintf(temp, L"test2");
    cb_problem_add( 3, temp );
    cb_problem_del( 5 );
    cb_problem_del( 1 );
    cb_problem_mod( 15, temp );

    cb_run_reply( 2, 3, temp );
    cb_run_reply( 3, 5, temp );
    cb_clar_reply( 1, temp, temp );

    cb_sb_update( 1, temp, 4, 4 );
    cb_sb_remove( 3 );
}

void TeamFrame::OnButtonClickSubmit( wxCommandEvent& event )
{

    if(m_timer.IsRunning()){
        if(m_choiceProblem->GetStringSelection().IsEmpty() || m_choiceLang->GetStringSelection().IsEmpty()|| m_filePicker->GetPath().IsEmpty()){
            if(m_choiceProblem->GetStringSelection().IsEmpty()){
                wxMessageBox(_("Plz select problem!"));
            }
            if(m_choiceLang->GetStringSelection().IsEmpty()){
                wxMessageBox(_("Plz select code lang!"));
            }
            if(m_filePicker->GetPath().IsEmpty()){
                wxMessageBox(_("Plz select path!"));
            }
        }
        else{
            submitconfirmdialog = new SubmitConfirmDialog(this);
            submitconfirmdialog->ShowModal();
            submitconfirmdialog->Destroy();
        }
    }
    else{
        wxMessageBox(_("Contest has not started!"));
    }
    return;
}

void TeamFrame::OnButtonClickAsk( wxCommandEvent& event )
{
    if(m_timer.IsRunning()){
        clardialog = new ClarDialog(this);
        clardialog->ShowModal();
        clardialog->Destroy();
    }
    else{
        wxMessageBox(_("Contest has not started!"));
    }
    return;
}
void TeamFrame::OnTimerEvent(wxTimerEvent &event){
	m_timeleft--;
	m_staticTextTime->SetLabel(wxString::Format(_("%d:%02d:%02d"), m_timeleft / 60 / 60, (m_timeleft / 60) % 60, m_timeleft % 60));
	if(m_timeleft <= 0){
		//contest end
		if(m_timer.IsRunning())
            m_timer.Stop();
	}

	return;
}

void TeamFrame::TimerCall(wxCommandEvent &event){
	if(event.GetInt() == 1){
	    if(m_timer.IsRunning() == false)
            m_timer.Start(1000);
	}
	else if(event.GetInt() == 0){
	    if(m_timer.IsRunning())
            m_timer.Stop();
	}

	return;
}

void TeamFrame::OnListItemActivatedClar( wxListEvent& event ){
    wxListItem Clar;
    wxListItem Result;

	Clar.SetId(event.GetIndex());
	Clar.SetColumn(1);
	Clar.SetMask(wxLIST_MASK_TEXT);
	m_listCtrlClars->GetItem(Clar);

	Result.SetId(event.GetIndex());
	Result.SetColumn(2);
	Result.SetMask(wxLIST_MASK_TEXT);
	m_listCtrlClars->GetItem(Result);

    showclardialog = new ShowClarDialog(this);
    showclardialog->m_textCtrlQuestion->SetValue(Clar.GetText());
    showclardialog->m_textCtrlAnswer->SetValue(Result.GetText());
    showclardialog->Show();

    return;
}

///////////////////////////////////////////////////////////////////////////////
/// ChangePassDialog
///////////////////////////////////////////////////////////////////////////////
ChangePassDialog::ChangePassDialog(wxFrame *frame) : ChangePassGUI( frame )
{

}

ChangePassDialog::~ChangePassDialog()
{

}

void ChangePassDialog::OnButtonClickOK( wxCommandEvent& event )
{
    char* op = new char [strlen(m_textCtrlOldPass->GetValue().mb_str()) + 1];
    strcpy( op, m_textCtrlOldPass->GetValue().mb_str());
    char* np = new char [strlen(m_textCtrlNewPass->GetValue().mb_str()) + 1];
    strcpy( np, m_textCtrlNewPass->GetValue().mb_str());
    char* cp = new char [strlen(m_textCtrlConfirmPass->GetValue().mb_str()) + 1];
    strcpy( cp, m_textCtrlConfirmPass->GetValue().mb_str());
    if( strcmp(np, cp) == 0 )
        teamproto_password_change(server_ip, login_id, op, np);
    else
        wxMessageBox(_("Confirm Password Error!"));

    delete op;
    delete np;
    delete cp;
    return;
}

void ChangePassDialog::OnButtonClickCancel( wxCommandEvent& event )
{
    EndModal(0);
    return;
}

void ChangePassDialog::ChangeSuccess(){
	EndModal(1);
	return;
}


///////////////////////////////////////////////////////////////////////////////
/// SubmitConfirmDialog
///////////////////////////////////////////////////////////////////////////////
SubmitConfirmDialog::SubmitConfirmDialog(wxFrame *frame) : SubmitConfirmGUI( frame )
{
    m_staticTextProblemVal->SetLabel(TeamFrameGlobal->m_choiceProblem->GetStringSelection());
    m_staticTextLangVal->SetLabel(TeamFrameGlobal->m_choiceLang->GetStringSelection());
    m_textCtrlFilePathVal->SetValue(TeamFrameGlobal->m_filePicker->GetPath());
}

SubmitConfirmDialog::~SubmitConfirmDialog()
{

}

void SubmitConfirmDialog::OnButtonClickYes( wxCommandEvent& event )
{
    wchar_t *lang = new wchar_t [wcslen(m_staticTextLangVal->GetLabel().c_str()) + 1];
	wcscpy( lang, m_staticTextLangVal->GetLabel().c_str() );
	wchar_t *path = new wchar_t [wcslen(m_textCtrlFilePathVal->GetValue().c_str()) + 1];
	wcscpy( path, m_textCtrlFilePathVal->GetValue().c_str() );

    teamproto_submission(server_ip, login_id, TeamFrameGlobal->m_choiceProblem->GetCurrentSelection(), lang, path);

    delete lang;
    delete path;
    EndModal(1);
	return;
}

void SubmitConfirmDialog::OnButtonClickNo( wxCommandEvent& event )
{
    EndModal(0);
    return;
}



///////////////////////////////////////////////////////////////////////////////
/// ClarDialog
///////////////////////////////////////////////////////////////////////////////
ClarDialog::ClarDialog(wxFrame *frame) : ClarDialogGUI( frame )
{

}

ClarDialog::~ClarDialog()
{

}

void ClarDialog::OnButtonClickYes( wxCommandEvent& event )
{
    clarconfirmdialog = new ClarConfirmDialog(NULL);
    if(clarconfirmdialog->ShowModal() == 1){
        clarconfirmdialog->Destroy();
		Destroy();
    }
    clarconfirmdialog->Destroy();
    return;
}

void ClarDialog::OnButtonClickNo( wxCommandEvent& event )
{
    EndModal(0);
    return;
}



///////////////////////////////////////////////////////////////////////////////
/// ClarConfirmDialog
///////////////////////////////////////////////////////////////////////////////
ClarConfirmDialog::ClarConfirmDialog(wxFrame *frame) : ClarConfirmGUI( frame )
{
    m_textCtrlFileQuestion->SetValue(clardialog->m_textCtrlFileQuestion->GetValue());
}

ClarConfirmDialog::~ClarConfirmDialog()
{

}

void ClarConfirmDialog::OnButtonClickYes( wxCommandEvent& event )
{
    //printf("ClarConfirmDialog::OnButtonClickYes 1\n");
    wchar_t *temp = new wchar_t [wcslen(m_textCtrlFileQuestion->GetValue().c_str()) + 1];
	//printf("ClarConfirmDialog::OnButtonClickYes 2\n");
	wcscpy( temp, m_textCtrlFileQuestion->GetValue().c_str() );
	//printf("ClarConfirmDialog::OnButtonClickYes 3\n");
	//wprintf(L"temp = %s\n", temp);
	//printf("ClarConfirmDialog::OnButtonClickYes 4\n");
    teamproto_clar(server_ip, login_id, 0, temp);
    //printf("ClarConfirmDialog::OnButtonClickYes 5\n");

    delete temp;
    EndModal(1);
    return;
}

void ClarConfirmDialog::OnButtonClickNo( wxCommandEvent& event )
{
    EndModal(0);
    return;
}



///////////////////////////////////////////////////////////////////////////////
/// ShowClarDialog
///////////////////////////////////////////////////////////////////////////////
ShowClarDialog::ShowClarDialog(wxFrame *frame)
    : ShowClarGUI(frame)
{

}

ShowClarDialog::~ShowClarDialog()
{

}

void ShowClarDialog::OnButtonClickClose( wxCommandEvent& event )
{
	Destroy();
}



///////////////////////////////////////////////////////////////////////////////
/// Callback Functions
///////////////////////////////////////////////////////////////////////////////
void cb_login_confirm( int confirm_code, unsigned int account_id )
{
    if(confirm_code == LOGIN_VALID){
		login_id = account_id;
		logindialog->LoginSuccess();

        teamproto_sb_sync(server_ip);
        teamproto_run_sync(server_ip, login_id);
        teamproto_timer_sync(server_ip);
        teamproto_contest_state_sync(server_ip);
        teamproto_problem_sync( server_ip );
	}
	else if(confirm_code == LOGIN_ACC_NOTEXIST){
		wxMessageBox(_("Account not exist!"));
	}
	else if(confirm_code == LOGIN_PASS_WRONG){
		wxMessageBox(_("Wrong password!"));
	}
	return;
}

void cb_logout_confirm( int confirm_code )
{
    if(confirm_code == LOGOUT_OK){
		wxMessageBox(_("Logout success!"));
		TeamFrameGlobal->Destroy();
	}
	else if(confirm_code == LOGOUT_FAIL){
		wxMessageBox(_("Logout fail!"));
	}
	return;
}

void cb_password_change_confirm( int confirm_code )
{
    if(confirm_code == PASSWD_SUCCESS){
        wxMessageBox(_("Password change success!"));
        changepassdialog->ChangeSuccess();
    }
    else if(confirm_code == PASSWD_MISMATCH){
        wxMessageBox(_("Password change mismatch!"));
    }
    else if(confirm_code == PASSWD_INVALID){
        wxMessageBox(_("Password invalid!"));
    }
    return;
}

void cb_timer_set( unsigned int hours, unsigned int minutes, unsigned int seconds )
{
    TeamFrameGlobal->m_staticTextTime->SetLabel(wxString::Format(_("%d:%02d:%02d"), hours, minutes, seconds));
	TeamFrameGlobal->m_timeleft = hours * 60 * 60 + minutes * 60 + seconds;

	return;
}

void cb_contest_start( void )
{
    //TeamFrameGlobal->m_timer.Start(1000);
	wxCommandEvent event(wxEVT_CALL_TIMER);
	event.SetInt(1);
	wxPostEvent(TeamFrameGlobal, event);
    return;
}

void cb_contest_stop( void )
{
    //TeamFrameGlobal->m_timer.Stop();
	wxCommandEvent event(wxEVT_CALL_TIMER);
	event.SetInt(0);
	wxPostEvent(TeamFrameGlobal, event);
    return;
}

void cb_run_reply( unsigned int run_id, unsigned int problem_id, wchar_t *result_string )
{
    mutexRun.Lock();
    long temp = TeamFrameGlobal->m_listCtrlRuns->FindItem(-1, wxString() << run_id);
    if(temp == wxNOT_FOUND){
        temp = TeamFrameGlobal->m_listCtrlRuns->InsertItem(0, wxString() << run_id);
    }
    TeamFrameGlobal->m_listCtrlRuns->SetItem(temp, 1, TeamFrameGlobal->m_choiceProblem->GetString(problem_id));
    TeamFrameGlobal->m_listCtrlRuns->SetItem(temp, 2, wxString() << result_string);
    mutexRun.Unlock();
    return;
}

void cb_clar_reply( unsigned int clar_id, wchar_t *clarmsg, wchar_t *result_string )
{
    mutexClar.Lock();
    long temp = TeamFrameGlobal->m_listCtrlClars->FindItem(-1, wxString() << clar_id);
    if(temp == wxNOT_FOUND){
        temp = TeamFrameGlobal->m_listCtrlClars->InsertItem(0, wxString() << clar_id);
    }
    TeamFrameGlobal->m_listCtrlClars->SetItem(temp, 1, wxString() << clarmsg);
    TeamFrameGlobal->m_listCtrlClars->SetItem(temp, 2, wxString() << result_string);
    mutexClar.Unlock();
    return;
}

void cb_sb_update( unsigned int updated_account_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time )
{
    mutexScoreboard.Lock();
    long temp = TeamFrameGlobal->m_listCtrlScore->FindItem(-1, wxString() << updated_account_id);
    if(temp == wxNOT_FOUND){
        temp = TeamFrameGlobal->m_listCtrlScore->InsertItem(0, wxString() << updated_account_id);
    }
    TeamFrameGlobal->m_listCtrlScore->SetItem(temp, 1, wxString() << new_account);
    TeamFrameGlobal->m_listCtrlScore->SetItem(temp, 2, wxString() << new_accept_count);
    TeamFrameGlobal->m_listCtrlScore->SetItem(temp, 3, wxString() << new_time);
    mutexScoreboard.Unlock();
    return;
}

void cb_sb_remove( unsigned int rm_account_id )
{
    mutexScoreboard.Lock();
    long temp = TeamFrameGlobal->m_listCtrlScore->FindItem(-1, wxString() << rm_account_id);
    if(temp != wxNOT_FOUND){
        TeamFrameGlobal->m_listCtrlScore->DeleteItem(temp);
    }
    mutexScoreboard.Unlock();
    return;
}

void cb_pu_request( wchar_t **path_description )
{
    wxString temp;
    do
    {
        temp = wxFileSelector(_("Download Problem File"), _(""), TeamFrameGlobal->m_choiceProblem->GetStringSelection(), _(".pdf"), _(".pdf"), wxFD_SAVE);
    }while( temp.empty() );
    //wprintf(L"Msg Box will print temp(set by wxFileSelector)\n");
    //wxMessageBox(temp);
    wchar_t *path = (wchar_t*)malloc( ( wcslen(temp.c_str()) + 1 ) * sizeof( wchar_t ) );
	wcscpy( path, temp.c_str());
	//wprintf(L"path = %s\n", path);
	*path_description = path;
	return;
}

void cb_pu_request_dlfin( wchar_t *path_description )
{
    wxMessageBox(_("Download Completed!"));
    return;
}

void cb_problem_add( unsigned int problem_id, wchar_t *problem_name )
{
    mutexProblem.Lock();
    for(;max_problem_id <= problem_id; max_problem_id++)
        TeamFrameGlobal->m_choiceProblem->Append(wxString() << _(""));
    mutexProblem.Unlock();
    TeamFrameGlobal->m_choiceProblem->SetString(problem_id, wxString() << problem_name);
    return;
}

void cb_problem_del( unsigned int problem_id )
{
    TeamFrameGlobal->m_choiceProblem->SetString(problem_id, wxString() << _(""));
    return;
}

void cb_problem_mod( unsigned int problem_id, wchar_t *problem_name )
{
    TeamFrameGlobal->m_choiceProblem->SetString(problem_id, wxString() << problem_name);
    return;
}
