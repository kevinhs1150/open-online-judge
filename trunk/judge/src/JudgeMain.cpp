#include "JudgeMain.h"
#include "JudgeLogin.h"
#include "JudgeChangePass.h"
#include "JudgeShowClar.h"
#include "JudgeSubmission.h"
#include <wx/process.h>
#include <wx/filefn.h>

extern "C"
{
    #include "judgeproto.h"
}

typedef struct run_problem_id{
    unsigned int run_id;
    unsigned int problem_id;
    wchar_t *coding_language;
    struct run_problem_id *next;
} run_request_id;

typedef struct clar{
    unsigned int clar_id;
	unsigned int account_id;
	wchar_t *account; 
    int private_byte;
    wchar_t *clarmsg;
	wchar_t *result_string;
    struct clar *next;
}clar_request_id;

typedef struct problem_list{
	unsigned int problem_id;
	wchar_t *problem_name;
	unsigned int time_limit;
	struct problem_list *next;
} problem_all;

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_LOCAL_EVENT_TYPE( wxEVT_CALL_TIMER, 7777 )
	DECLARE_LOCAL_EVENT_TYPE( wxEVT_SHOW_SUBMISSION_DIALOG, 8888 )
END_DECLARE_EVENT_TYPES()
DEFINE_EVENT_TYPE( wxEVT_CALL_TIMER )
DEFINE_EVENT_TYPE( wxEVT_SHOW_SUBMISSION_DIALOG )

#define EVT_CALL_TIMER( id, fn )\
    DECLARE_EVENT_TABLE_ENTRY( \
        wxEVT_CALL_TIMER, id, wxID_ANY, \
        (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent( wxCommandEventFunction, &fn ), \
        (wxObject*)NULL\
    ),

#define EVT_SHOW_SUBMISSION_DIALOG( id, fn )\
    DECLARE_EVENT_TABLE_ENTRY( \
        wxEVT_SHOW_SUBMISSION_DIALOG, id, wxID_ANY, \
        (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent( wxCommandEventFunction, &fn ), \
        (wxObject*)NULL\
    ),
	
BEGIN_EVENT_TABLE(JudgeFrame, wxFrame)
    EVT_TIMER(-1, JudgeFrame::OnTimerEvent)
	EVT_CALL_TIMER(wxID_ANY, JudgeFrame::TimerCall)
	EVT_SHOW_SUBMISSION_DIALOG(wxID_ANY, JudgeFrame::ShowSubmissionDialog)
END_EVENT_TABLE()

JudgeLoginFrame *loginframe;
JudgeChangePassFrame *changePassFrame;
JudgeShowClarFrame *showClarFrame;
JudgeSubmissionFrame *submissionFrame;
JudgeFrame *mainFrame = NULL;
run_request_id *pptr = NULL;
clar_request_id *clar_hptr = NULL;
problem_all *problem_hptr = NULL;

void login_confirm( int confirm_code, unsigned int account_id );
void logout_confirm( int confirm_code );
void password_change_confirm( int confirm_code );
void timer_set(unsigned int hours, unsigned int minutes, unsigned int seconds);
void run_request( unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code );
void run_request_dlfin( unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code );
void contest_start( void );
void contest_stop( void );
void problem_update( unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer );
void problem_update_dlfin(unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer);
void problem_remove( unsigned int problem_id );
void take_result( unsigned int run_id, int success );
void clar_request( unsigned int clar_id, unsigned int account_id, wchar_t *account, int private_byte, wchar_t *clarmsg );
void clar_reply( unsigned int clar_id, wchar_t *clarmsg, wchar_t *result_string );
unsigned int unJudgeNumCount(void);
void id_insert(unsigned int run_id, unsigned int problem_id, wchar_t *coding_language);
void problem_insert(unsigned int problem_id,wchar_t *problem_name, unsigned int time_limit);
void problem_filter_search(unsigned int problem_id);
problem_all *problem_search(unsigned int problem_id);
void problem_search_delete(unsigned int problem_id);
void run_search_delete(unsigned int problem_id);
run_request_id *search(unsigned int run_id);
void id_delete(unsigned int run_id);
void autoJudge_take(void);
void autoJudge(unsigned int run_id,unsigned int problem_id, wchar_t *coding_language, unsigned int time_limit);
int compile_auto(wchar_t [], wchar_t []);
int complie_result_auto(void);
int judge_auto(unsigned int problem_id);
int time_auto(unsigned int time_limit);
void clar_insert(unsigned int clar_id, unsigned int account_id, wchar_t *account, int private_byte, wchar_t *clarmsg);
clar_request_id *clar_search(unsigned int clar_id);
unsigned int clarNumCount(void);
void clar_delete(unsigned int clar_id);

///////////////////////////////////////////////////
//class public function
///////////////////////////////////////////////////
JudgeFrame::JudgeFrame(wxFrame *frame)
    : JudgeGUI(frame), m_timer(this)
{
    judgeproto_cbreg_login_confirm( login_confirm );
    judgeproto_cbreg_logout_confirm( logout_confirm );
	judgeproto_cbreg_password_change_confirm( password_change_confirm );
    judgeproto_cbreg_timer_set(timer_set);
    judgeproto_cbreg_run_request(run_request);
    judgeproto_cbreg_contest_start(contest_start);
    judgeproto_cbreg_contest_stop(contest_stop);
    judgeproto_cbreg_run_request_dlfin(run_request_dlfin);
    judgeproto_cbreg_problem_update(problem_update);
    judgeproto_cbreg_problem_update_dlfin(problem_update_dlfin);
	judgeproto_cbreg_problem_remove(problem_remove);
    judgeproto_cbreg_take_result(take_result);
    judgeproto_cbreg_clar_request(clar_request);
	judgeproto_cbreg_clar_reply(clar_reply);
    judgeproto_listen("0.0.0.0");
	setRunListColumn();
	setClarListColumn();

    loginframe = new JudgeLoginFrame(0L);
    if(loginframe->ShowModal() == -1){
		loginframe->Destroy();
        Destroy();
		return;
    }
	
    system("mkdir problem");
    IP_set();
    mainFrame = this;
	mainFrame->setUnJudgeNum(0);
	
	judgeproto_run_sync( IP );
	judgeproto_timer_sync( IP );
	judgeproto_clar_sync( IP );
	judgeproto_problem_sync( IP );
}

JudgeFrame::~JudgeFrame()
{
}

void JudgeFrame::account_id_set(unsigned int account_id)
{
	wxString id;
	
	this->account_id = account_id;
	
	id.Printf(_("%u"),this->account_id);
}

void JudgeFrame::account_set(wxString account)
{
	m_staticTextName->SetLabel(account);
}

void JudgeFrame::setPtoblemFilterChoice(unsigned int problem_id, wchar_t *problem_name)
{
	wxString choice;
	
	choice.Printf(wxT("%u %s"), problem_id, problem_name);
	m_choiceFilter->Append(choice);
}

void JudgeFrame::deleteProblemFilterChoice(unsigned int problem_count)
{
	m_choiceFilter->Delete(problem_count);
}

void JudgeFrame::setUnJudgeNum(unsigned int unJudgeNum)
{
	wxString unJudgeNumStr;
	
	unJudgeNumStr.Printf(_("%u"),unJudgeNum);
	m_staticTextNewUnjudgeCount->SetLabel(unJudgeNumStr);
}

void JudgeFrame::setRunListColumn()
{
	wxListItem columnListItem;
	
	columnListItem.SetText(wxT("run_id"));
	m_listCtrlRuns->InsertColumn(0,columnListItem);
	columnListItem.SetText(wxT("problem_id"));
	m_listCtrlRuns->InsertColumn(1,columnListItem);
	columnListItem.SetText(wxT("coding language"));
	m_listCtrlRuns->InsertColumn(2,columnListItem);
}

void JudgeFrame::setClarListColumn()
{
	wxListItem columnListItem;	
	
	columnListItem.SetText(wxT("clar_id"));
	m_listCtrlClars->InsertColumn(0,columnListItem);
	columnListItem.SetText(wxT("clarmsg"));
	m_listCtrlClars->InsertColumn(1,columnListItem);
}

void JudgeFrame::start()
{
    state = START;
	if(m_timer.IsRunning() == false){
		wxCommandEvent event(wxEVT_CALL_TIMER);
		event.SetInt(1);
		wxPostEvent(mainFrame, event);
	}
}

void JudgeFrame::stop()
{
    state = STOP;
	if(m_timer.IsRunning() == true){
		wxCommandEvent event(wxEVT_CALL_TIMER);
		event.SetInt(0);
		wxPostEvent(mainFrame, event);
	}
}

void JudgeFrame::IP_set()
{
    FILE *fptr1;

    fptr1=fopen("ip.txt","r");
    fscanf (fptr1, "%s", IP);
    fclose(fptr1);
}

char *JudgeFrame::IP_get()
{
    return IP;
}

////////////////////////////////////////////////////////////////////
//class private function
////////////////////////////////////////////////////////////////////
void JudgeFrame::OnButtonClickChangePassword( wxCommandEvent& event )
{
	changePassFrame = new JudgeChangePassFrame(0L);
	changePassFrame->Show();
	changePassFrame->set_account_id(this->account_id);
	//=====================================================================================
	/*problem_update_dlfin( 1, L"one", 3, L"problem/1.pdf", L"problem/1_input.txt", L"problem/1_ans.txt" );
	problem_update_dlfin( 2, L"two", 3, L"problem/2.pdf", L"problem/2_input.txt", L"problem/2_ans.txt" );
	
	run_request_dlfin( 0, 1, L"c", L"0.c" );
	run_request_dlfin( 1, 1, L"c", L"1.c" );
	run_request_dlfin( 2, 1, L"c", L"2.c" );
	run_request_dlfin( 3, 1, L"c", L"3.c" );
	run_request_dlfin( 4, 1, L"c", L"4.c" );
	
	take_result(0,TAKE_SUCCESS);*/
	//autoJudge(0,1, L"c", 3);
	//======================================================================================
}

void JudgeFrame::OnButtonClickLogout( wxCommandEvent& event )
{
	judgeproto_logout(IP,account_id);
}

void JudgeFrame::OnChoiceFilter( wxCommandEvent& event )
{
	wxListItem item;
	unsigned int problem_id;
	wxString text;
	int post;
	
	text = event.GetString();
	post = text.Find(wxT(" "));
	text.Remove(post);
	problem_id = wxAtoi(text);
	
	problem_filter_search(problem_id);
}

void JudgeFrame::OnCheckBoxAutoJudge( wxCommandEvent& event )
{
	if((m_checkBoxAutoJudge->IsChecked()) == true && unJudgeNumCount() > 0){
	//	autoJudge_take();
	}
	//==========================================================
	/*autoJudge(1,1, L"c", 3);
	mainFrame->m_mutexRunRequest.Lock();
	id_delete(1);
	unsigned int unJudgeNum = unJudgeNumCount();
	mainFrame->setUnJudgeNum(unJudgeNum);
	mainFrame->m_mutexRunRequest.Unlock();*/
	//==========================================================
}

void JudgeFrame::OnListItemActivatedRuns( wxListEvent& event )
{
	wxListItem item;
	unsigned int run_id;
	
	item.SetId(event.GetIndex());
	item.SetColumn(0);
	item.SetMask(wxLIST_MASK_TEXT);
	m_listCtrlRuns->GetItem(item);

	run_id = wxAtoi(item.GetText());
	
	printf("Call judgeproto_take_run\n");
	judgeproto_take_run(this->IP_get(),run_id);
	printf("return from judgeproto_take_run\n");
}

void JudgeFrame::OnListItemActivatedClar( wxListEvent& event )
{
	wxListItem item0;
	wxListItem item1;
	clar_request_id *cptr;
	
	item0.SetId(event.GetIndex());
	item0.SetColumn(0);
	item0.SetMask(wxLIST_MASK_TEXT);
	m_listCtrlClars->GetItem(item0);
	
	item1.SetId(event.GetIndex());
	item1.SetMask(wxLIST_MASK_TEXT);
	m_listCtrlClars->GetItem(item1);
	
	cptr = clar_search(wxAtoi(item0.GetText()));
	showClarFrame = new JudgeShowClarFrame(0L);
	showClarFrame->Show();
	showClarFrame->setClarQA(cptr->clarmsg ,cptr->result_string);
	
}

void JudgeFrame::OnTimerEvent(wxTimerEvent &event){
	m_timeleft--;
	m_staticTextTime->SetLabel(wxString::Format(_("%d:%02d:%02d"), m_timeleft / 60 / 60, (m_timeleft / 60) % 60, m_timeleft % 60));
	if(m_timeleft <= 0){
		//contest end
		m_timer.Stop();
	}
	
	return;
}

void JudgeFrame::TimerCall(wxCommandEvent &event){
	if(event.GetInt() == 1){
		m_timer.Start(1000);
	}
	else if(event.GetInt() == 0){
		m_timer.Stop();
	}
	
	return;
}

void JudgeFrame::ShowSubmissionDialog(wxCommandEvent &event){
	unsigned int run_id = event.GetInt();
    run_request_id *rptr = search(run_id);
	problem_all *proptr = problem_search(rptr->problem_id);
	unsigned int unJudgeNum;

	submissionFrame = new JudgeSubmissionFrame(0L);
	submissionFrame->setRunProblemID(rptr->run_id,rptr->problem_id, rptr->coding_language, proptr->problem_name, proptr->time_limit);
	submissionFrame->showStatus();
	if(submissionFrame->ShowModal() == 0){
		mainFrame->m_mutexRunRequest.Lock();
		id_delete(rptr->run_id);
		unJudgeNum = unJudgeNumCount();
		mainFrame->setUnJudgeNum(unJudgeNum);
		mainFrame->m_mutexRunRequest.Unlock();
	}
	submissionFrame->Destroy();
	
	return;
}

/////////////////////////////////////////////////////////////
//call back function use
/////////////////////////////////////////////////////////////
void login_confirm( int confirm_code, unsigned int account_id )
{
    if( confirm_code == LOGIN_VALID ){
        loginframe->EndModal(0);
		mainFrame->account_set(loginframe->getAccount());
		loginframe->Destroy();
		mainFrame->account_id_set(account_id);
	}
    else{
        wxMessageBox( wxT("Login Error.\nPromble: account NOTEXIST or password WRONG."), wxT("Login Error"),wxOK|wxICON_EXCLAMATION);
        loginframe->cleanPassword();
    }
}

void logout_confirm( int confirm_code )
{
    if(confirm_code == LOGOUT_OK){
        mainFrame->Destroy();
    }
}

void timer_set(unsigned int hours, unsigned int minutes, unsigned int seconds)
{
	mainFrame->m_staticTextTime->SetLabel(wxString::Format(_("%d:%02d:%02d"), hours, minutes, seconds));
	mainFrame->m_timeleft = hours * 60 * 60 + minutes * 60 + seconds;
}

void contest_start( void )
{
    mainFrame->start();
}

void contest_stop( void )
{
    mainFrame->stop();
}

void run_request( unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code )
{/***HERE***/
    wchar_t filename[50];

    if( !wcscmp(coding_language, L"c") )
    {
        wsprintf(filename, L"%u.c", run_id);
    }
    else if(!wcscmp(coding_language,L"c++"))
    {
        wsprintf(filename, L"%u.cpp", run_id);
    }
    else{
        return;
    }

    /**TODO: new memory for *path_code**/
    *path_code = (wchar_t *) malloc( (wcslen(filename) +1 ) * sizeof(wchar_t));
    wsprintf(*path_code, L"%s", filename );
}

void run_request_dlfin( unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code )
{
	unsigned int unJudgeNum;
	
	mainFrame->m_mutexRunRequest.Lock();
    id_insert(run_id,problem_id,coding_language);
	unJudgeNum = unJudgeNumCount();
	mainFrame->setUnJudgeNum(unJudgeNum);
	mainFrame->m_mutexRunRequest.Unlock();
	
	if(unJudgeNum == 1 && (mainFrame->m_checkBoxAutoJudge->IsChecked()) == true){
		autoJudge_take();
	}
}

void problem_update( unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer)
{/***HERE***/
    wchar_t path[50];

    wsprintf(path, L"problem/%u.pdf", problem_id);
    *path_description = (wchar_t *) malloc( ( wcslen(path)+1 ) * sizeof(wchar_t));
	wcscpy(*path_description,path);
	
	wsprintf(path, L"problem/%u_input.txt", problem_id);
    *path_input = (wchar_t *)malloc( ( wcslen(path)+1 ) * sizeof(wchar_t));
	wcscpy(*path_input,path);
	
	wsprintf(path, L"problem/%u_answer.txt", problem_id);
    *path_answer = (wchar_t *)malloc( ( wcslen(path)+1 ) * sizeof(wchar_t));
	wcscpy(*path_answer,path);
}

void problem_update_dlfin( unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer )
{
    /**TODO:problem view**/
	mainFrame->m_mutexProblem.Lock();
	problem_insert(problem_id, problem_name, time_limit);
	mainFrame->setPtoblemFilterChoice(problem_id, problem_name);
	mainFrame->m_mutexProblem.Unlock();
}

void problem_remove( unsigned int problem_id )
{
	wchar_t file[20];
	
	swprintf(file,L"problem/%u.pdf",problem_id);
	DeleteFile(file);
	swprintf(file,L"problem/%u_input.txt",problem_id);
	DeleteFile(file);
	swprintf(file,L"problem/%u_answer.txt",problem_id);
	DeleteFile(file);
	
	mainFrame->m_mutexProblem.Lock();
	run_search_delete(problem_id);
	problem_search_delete(problem_id);
	mainFrame->m_mutexProblem.Unlock();
}

void take_result( unsigned int run_id, int success )
{
	printf("cb take_result\n");
	printf("run_id = %u\n", run_id);
    run_request_id *rptr = search(run_id);
	printf("after search\n");
	problem_all *proptr = problem_search(rptr->problem_id);
	printf("after problem_search\n");
	unsigned int unJudgeNum;
	
	printf("take\n");
	
	if(success == TAKE_SUCCESS){
		if(mainFrame->m_checkBoxAutoJudge->IsChecked()){
			autoJudge(rptr->run_id,rptr->problem_id, rptr->coding_language, proptr->time_limit);
		}
		else{
			printf("before event\n");
			wxCommandEvent event(wxEVT_SHOW_SUBMISSION_DIALOG);
			event.SetInt(run_id);
			wxPostEvent(mainFrame, event);
			printf("after event\n");
			/*
			submissionFrame = new JudgeSubmissionFrame(0L);
			submissionFrame->setRunProblemID(rptr->run_id,rptr->problem_id, rptr->coding_language, proptr->problem_name, proptr->time_limit);
			submissionFrame->showStatus();
			if(submissionFrame->ShowModal() == 0){
				mainFrame->m_mutexRunRequest.Lock();
				id_delete(rptr->run_id);
				unJudgeNum = unJudgeNumCount();
				mainFrame->setUnJudgeNum(unJudgeNum);
				mainFrame->m_mutexRunRequest.Unlock();
			}
			submissionFrame->Destroy();
			*/
		}
	}
	else{
		if(mainFrame->m_checkBoxAutoJudge->IsChecked()){
			autoJudge_take();
		}
		else{
			wxMessageBox( wxT("Take run Error.\nPromble: This problem has been judged."), wxT("Take run Error"),wxOK|wxICON_EXCLAMATION);
			mainFrame->m_mutexRunRequest.Lock();
			id_delete(run_id);
			unJudgeNum = unJudgeNumCount();
			mainFrame->setUnJudgeNum(unJudgeNum);
			mainFrame->m_mutexRunRequest.Unlock();
		}
	}
}

void clar_request( unsigned int clar_id, unsigned int account_id, wchar_t *account, int private_byte, wchar_t *clarmsg )
{
	mainFrame->m_mutexClarRequest.Lock();
    clar_insert(clar_id,account_id,account,private_byte,clarmsg);
	mainFrame->m_mutexClarRequest.Unlock();
}

void clar_reply( unsigned int clar_id, wchar_t *clarmsg, wchar_t *result_string )
{
	clar_request_id *result_insertPtr = clar_search(clar_id);
	result_insertPtr->result_string = (wchar_t *) malloc( (wcslen(result_string) +1 ) * sizeof(wchar_t));
    wcscpy(result_insertPtr->result_string, result_string);
}

///////////////////////////////////////////////////////////
//run_request_id & problem_all linked list modify
///////////////////////////////////////////////////////////
unsigned int unJudgeNumCount(void)
{
	unsigned int unJudgeNum = 0;
	
	run_request_id *cptr = pptr;

    if(cptr == NULL){
        return unJudgeNum;
    }
	unJudgeNum++;

    while( cptr->next != NULL ){
		unJudgeNum++;
        cptr = cptr->next;
    }
	
	return unJudgeNum;
}

void id_insert(unsigned int run_id, unsigned int problem_id, wchar_t *coding_language)
{
    run_request_id *currentPtr = pptr;
	unsigned int row;
	wxString insertString;
	long tmp;

    run_request_id *temp_id = new run_request_id;
    temp_id->run_id = run_id;
    temp_id->problem_id = problem_id;
	temp_id->coding_language = (wchar_t *) malloc( (wcslen(coding_language) +1 ) * sizeof(wchar_t));
    wcscpy(temp_id->coding_language, coding_language);
	temp_id->next = NULL;

	if( pptr == NULL )
	{
		pptr = temp_id;
	}
	else
	{
		while( currentPtr->next != NULL )
			currentPtr = currentPtr->next;

		currentPtr->next = temp_id;
	}
	
	row = unJudgeNumCount() + 1 ;
	insertString.Printf(wxT("%d"),run_id);
	tmp = mainFrame->m_listCtrlRuns->InsertItem(row,insertString);
	insertString.Printf(wxT("%d"),problem_id);
	mainFrame->m_listCtrlRuns->SetItem(tmp, 1, insertString);
	insertString.Printf(wxT("%s"),coding_language);
	mainFrame->m_listCtrlRuns->SetItem(tmp, 2, insertString);
}

void problem_insert(unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit)
{
    problem_all *currentPtr = problem_hptr;

    problem_all *temp_id = new problem_all;
    temp_id->problem_id = problem_id;
	temp_id->problem_name = (wchar_t *) malloc( (wcslen(problem_name) +1 ) * sizeof(wchar_t));
    wcscpy(temp_id->problem_name, problem_name);
	temp_id->time_limit = time_limit;
	temp_id->next = NULL;

	if( problem_hptr == NULL )
	{
		problem_hptr = temp_id;
	}
	else
	{
		while( currentPtr->next != NULL )
			currentPtr = currentPtr->next;

		currentPtr->next = temp_id;
	}
}

void problem_filter_search(unsigned int problem_id)
{
	unsigned int row = 0;
	run_request_id *pfptr = pptr;
	wxString insertString;
	long tmp;
	
	mainFrame->m_listCtrlRuns->DeleteAllItems();
	while(1){
		if(pfptr == NULL){
			break;
		}
		if(pfptr->problem_id == problem_id){
			row = unJudgeNumCount() + 1 ;
			insertString.Printf(wxT("%d"),pfptr->run_id);
			tmp = mainFrame->m_listCtrlRuns->InsertItem(row,insertString);
			insertString.Printf(wxT("%d"),pfptr->problem_id);
			mainFrame->m_listCtrlRuns->SetItem(tmp, 1, insertString);
			insertString.Printf(wxT("%s"),pfptr->coding_language);
			mainFrame->m_listCtrlRuns->SetItem(tmp, 2, insertString);
		}
		if(pfptr->next == NULL){
			break;
			}
		pfptr = pfptr->next; 
	}
}

problem_all *problem_search(unsigned int problem_id)
{
	problem_all *problem_all_hptr = problem_hptr;
	
	while(1){
		if(problem_all_hptr->problem_id == problem_id){
			return problem_all_hptr;
		}
		problem_all_hptr = problem_all_hptr->next; 
	}
}

void problem_search_delete(unsigned int problem_id)
{
	unsigned int problem_count = 0;

	problem_all *cptr = problem_hptr;
    problem_all *dptr = problem_hptr;
    problem_all *nptr = problem_hptr;

	if(dptr != NULL){
		if(dptr->problem_id == problem_id){
			problem_hptr = problem_hptr->next;
			delete(dptr);
			mainFrame->deleteProblemFilterChoice(problem_count);
			return;
		}

		while( dptr->next != NULL ){
			problem_count++;
			cptr = dptr;
			dptr = dptr->next;
			if(dptr->problem_id == problem_id){
				nptr = dptr->next;
				delete(dptr);
				cptr->next = nptr;
				mainFrame->deleteProblemFilterChoice(problem_count);
				break;
			}
		}
	}
}
void run_search_delete(unsigned int problem_id)
{
	run_request_id *cptr = pptr;
    run_request_id *dptr = pptr;
    run_request_id *nptr = pptr;

	if(dptr != NULL){
		if(dptr->problem_id == problem_id){
			pptr = pptr->next;
			delete(dptr);
		}

		while( dptr->next != NULL ){
			cptr = dptr;
			dptr = dptr->next;
			if(dptr->problem_id == problem_id){
				nptr = dptr->next;
				delete(dptr);
				cptr->next = nptr;
				dptr = cptr;
			}
		}
	}
}

run_request_id *search(unsigned int run_id)
{
    run_request_id *tptr = pptr;

    if(tptr->run_id == run_id){
        return tptr;
    }

    while( tptr->next != NULL ){
        if(tptr->run_id == run_id){
            return tptr;
            break;
        }
        tptr = tptr->next;
    }
}

void id_delete(unsigned int run_id)
{
	long itemCount = 0;
	
    run_request_id *cptr = pptr;
    run_request_id *dptr = pptr;
    run_request_id *nptr = pptr;

    if(dptr->run_id == run_id){
        pptr = pptr->next;
        delete(dptr);
		mainFrame->m_listCtrlRuns->DeleteItem(itemCount);
        return;
    }

    while( dptr->next != NULL ){
		itemCount++;
        cptr = dptr;
        dptr = dptr->next;
        if(dptr->run_id == run_id){
            nptr = dptr->next;
            delete(dptr);
            cptr->next = nptr;
			mainFrame->m_listCtrlRuns->DeleteItem(itemCount);
            break;
        }
    }
}

////////////////////////////////////////////////////////////
//clar_request_id linked list modify
////////////////////////////////////////////////////////////
void clar_insert(unsigned int clar_id, unsigned int account_id, wchar_t *account, int private_byte, wchar_t *clarmsg)
{
    clar_request_id *currentPtr = clar_hptr;
	unsigned int row;
	wxString insertString;
	long tmp;

    clar_request_id *temp = new clar_request_id;
    temp->clar_id = clar_id;
	temp->account_id = account_id;
	temp->account = (wchar_t *) malloc( (wcslen(account) +1 ) * sizeof(wchar_t));
    wcscpy((temp->account), account);
    temp->private_byte = private_byte;
	temp->clarmsg = (wchar_t *) malloc( (wcslen(clarmsg) +1 ) * sizeof(wchar_t));
    wcscpy((temp->clarmsg), clarmsg);
	temp->result_string = NULL;
	temp->next = NULL;
	
	if( clar_hptr == NULL )
	{
		clar_hptr = temp;
	}
	else
	{
		while( currentPtr->next != NULL )
			currentPtr = currentPtr->next;

		currentPtr->next = temp;
	}
	
	row = clarNumCount() + 1 ;
	insertString.Printf(wxT("%d"),clar_id);
	tmp = mainFrame->m_listCtrlClars->InsertItem(row,insertString);
	insertString.Printf(wxT("%s"),clarmsg);
	mainFrame->m_listCtrlClars->SetItem(tmp, 1, insertString);
}

clar_request_id *clar_search(unsigned int clar_id)
{	
    clar_request_id *tptr = clar_hptr;
	while(1){
		if(tptr->clar_id == clar_id){
			return tptr;
		}
		tptr = tptr->next;
	}
}

unsigned int clarNumCount(void)
{
	unsigned int clarNum = 0;
	
	clar_request_id *cptr = clar_hptr;

    if(cptr == NULL){
        return clarNum;
    }
	clarNum++;

    while( cptr->next != NULL ){
		clarNum++;
        cptr = cptr->next;
    }
	
	return clarNum;
}

void clar_delete(unsigned int clar_id)
{
    clar_request_id *uptr = clar_hptr;
    clar_request_id *dptr = clar_hptr;
    clar_request_id *nptr = clar_hptr;

    if(dptr->clar_id == clar_id){
        clar_hptr = clar_hptr->next;
        delete(dptr);
        return;
    }

    while( dptr->next != NULL ){
        uptr = dptr;
        dptr = dptr->next;
        if(dptr->clar_id == clar_id){
            nptr = dptr->next;
            delete(dptr);
            uptr->next = nptr;
            break;
        }
    }
}

/////////////////////////////////////////////////////
//do judge
/////////////////////////////////////////////////////
void autoJudge_take(void)
{
	judgeproto_take_run(mainFrame->IP_get(),pptr->run_id);
}

void autoJudge(unsigned int run_id,unsigned int problem_id, wchar_t *coding_language, unsigned int time_limit)
{
	wchar_t file_name[50];
    int errtyp;
    wchar_t type[20];
	wchar_t result_string[20];
	unsigned int unJudgeNum;

    wcscpy(type, coding_language);
	if(!(wcscmp(type, L"c"))){
		wsprintf(file_name,L"%u.c",run_id);
	}
	else if(!(wcscmp(type, L"c++"))){
		wsprintf(file_name,L"%u.cpp",run_id);
	}
	else{
		errtyp = TYPE_ERROR;
	}
    errtyp = compile_auto(file_name, type);
    if(errtyp == SUCCESS || errtyp == SUCCESS_WITH_WARNING){
		if(time_auto(time_limit) == 0){
            if(judge_auto(problem_id) != 0){
                errtyp = OUTPUT_ERROR;
			}
        }
		else{
			errtyp = TIME_OUT;
		}
    }
	
	if(errtyp == SUCCESS || errtyp == SUCCESS_WITH_WARNING){
		swprintf(result_string,L"yes");
	}
	else if(errtyp == COMPLIE_ERROR || errtyp == TYPE_ERROR || errtyp == FILE_OPEN_ERROR){
		swprintf(result_string,L"complie error");
	}
	else if(errtyp == OUTPUT_ERROR || errtyp == OUTPUT_OPEN_ERROR){
		swprintf(result_string,L"wrong answer");
	}
	else if(errtyp == TIME_OUT){
		swprintf(result_string,L"time-limit exceed");
	}
	else{
		swprintf(result_string,L"complie error");
	}
	
	if(judgeproto_judge_result(mainFrame->IP_get(),run_id,result_string) != 0){
		wxMessageBox(wxT("Judgement Submission Error.\nPromble: Socket error."),wxT("Judgement Submission Error"),wxOK|wxICON_EXCLAMATION);
	}
	else{
		unJudgeNum = unJudgeNumCount();
		if(unJudgeNum == 1 && (mainFrame->m_checkBoxAutoJudge->IsChecked()) == true){
			autoJudge_take();
		}
	}
}

int compile_auto(wchar_t file_name[], wchar_t type[])
{
    FILE *fptr1;
    wchar_t call[100];
    char call_mb[100];
    size_t call_mbsize;

    fptr1=fopen("out.exe","r");
    if(fptr1 != NULL){
        fclose(fptr1);
        wxRemoveFile(wxT("out.exe"));
    }
	
	fptr1=fopen("ans.txt","r");
    if(fptr1 != NULL){
        fclose(fptr1);
        wxRemoveFile(wxT("ans.txt"));
    }

    fptr1=fopen_sp(file_name,L"r");
    if(fptr1!=NULL)
    {
        if(!(wcscmp(type, L"c"))){
            wcscpy(call, L"gcc -o out.exe ");
            wcscat(call, file_name);
            wcscat(call, L" > output.txt 2>&1");

            call_mbsize = wcstombs( NULL, call, 0 ) + 1;
            wcstombs( call_mb, call, call_mbsize );

            system(call_mb);
            return(complie_result_auto());

        }
        else if(!(wcscmp(type, L"c++"))){
            wcscpy(call, L"g++ -o out.exe ");
            wcscat(call, file_name);
            wcscat(call, L" > output.txt 2>&1");

            call_mbsize = wcstombs( NULL, call, 0 ) + 1;
            wcstombs( call_mb, call, call_mbsize );

            system(call_mb);
            return(complie_result_auto());
        }
        else{
            return TYPE_ERROR;
        }
        fclose(fptr1);
    }
    else{
        return FILE_OPEN_ERROR;
    }
}

int complie_result_auto(){
    FILE *fptr1,*fptr2;
    char ch;
    int result = SUCCESS;

    fptr1 = fopen("out.exe","r");
    fptr2 = fopen("output.txt","r");
    if(fptr1 != NULL){
        if(fptr2 != NULL)
        {
            while((ch = getc(fptr2))!= EOF){
                result = SUCCESS_WITH_WARNING;
            }
            fclose(fptr2);
        }
        else{
            result = OUTPUT_OPEN_ERROR;
        }
        fclose(fptr1);
    }
    else{
        result = COMPLIE_ERROR;
        if(fptr2 != NULL)
        {
            while((ch = getc(fptr2))!= EOF){
            }
            fclose(fptr2);
        }
        else{
            result = OUTPUT_OPEN_ERROR;
        }
    }

    return(result);
}

int time_auto(unsigned int time_limit){
    int i;
	long pid;
	wxProcess *wxP = NULL;

   pid = wxExecute(wxT("executive.exe"),wxEXEC_NOHIDE,wxP);

    for(i = 0;i < time_limit;i++){
        Sleep(1000);
        if(wxProcess::Exists(pid) == true){
            break;
        }
    }

    if(wxProcess::Exists(pid) == false){
        system("taskkill /F /IM out.exe");
        return -1;
    }
	
    return 0;
}

int judge_auto(unsigned int problem_id){
    FILE *fptr1,*fptr2;
    char a;
    char o;
	char problem_ans[50];

    sprintf(problem_ans, "problem/%u_answer.txt", problem_id);

    fptr1 = fopen(problem_ans,"r");
    fptr2 = fopen("ans.txt","r");
    if(fptr1 != NULL){
        if(fptr2 != NULL)
        {
            while(1){
                o = getc(fptr2);
                a = getc(fptr1);
                if(o != EOF && a != EOF){
                    if(o != a){
                        return -1;
                    }
                }
                else if(o != EOF || a != EOF){
                    return -1;
                }
                else{
                    break;
                }
            }
            fclose(fptr2);
        }
        else{
            return -1;
        }
        fclose(fptr1);
    }
    else{
        return -1;
    }
	
    return 0;
}
