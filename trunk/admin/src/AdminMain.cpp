#include <dir.h>
#include "AdminMain.h"
#include "AccountDialog.h"
#include "ChangePassDialog.h"
extern "C"
{
#include "adminproto.h"
}

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

BEGIN_EVENT_TABLE(AdminFrame, wxFrame)
    EVT_TIMER(-1, AdminFrame::OnTimerEvent)
	EVT_CALL_TIMER(wxID_ANY, AdminFrame::TimerCall)
END_EVENT_TABLE()

AdminFrame* AdminFrameGlobal;
char server_ip[20];
wxString m_loginName;
unsigned int login_id;
bool contestRunning;
LoginDialog *loginDialog = NULL;
ChangePassDialog *changePassDialog = NULL;

void cb_account_update( unsigned int account_id, unsigned int type, wchar_t *account );
void cb_account_remove( unsigned int account_id );
void cb_problem_update( unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer );
void cb_problem_update_dlfin( unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer );
void cb_login_confirm( int confirm_code, unsigned int account_id );
void cb_logout_confirm( int confirm_code );
void cb_password_change_confirm( int confirm_code );
void cb_contest_start( void );
void cb_contest_stop( void );
void cb_timer_set( unsigned int hours, unsigned int minutes, unsigned int seconds );
void cb_clar_request( unsigned int clar_id, unsigned int account_id, wchar_t *account, int private_byte, wchar_t *clarmsg );
void cb_clar_reply( unsigned int clar_id, wchar_t *clarmsg, wchar_t *result_string );
void cb_sb_update( unsigned int updated_account_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time );
void cb_sb_remove( unsigned int rm_account_id );
void cb_problem_remove( unsigned int problem_id );

int wxCALLBACK ListCompareFunction(long item1, long item2, long sortData){
    if (item1 < item2)
		if(sortData)
			return 1;
		else
			return -1;
    if (item1 > item2)
		if(sortData)
			return -1;
		else
			return 1;

    return 0;
}

/* callback functions */
void cb_account_update( unsigned int account_id, unsigned int type, wchar_t *account ){
	wxString name(account);
	wxString id = wxString() << account_id;
	long tmp;
	int i;
	
	AdminFrameGlobal->m_mutexAccount.Lock();
	
	//find in the lists
	for(i = 0 ; i < AdminFrameGlobal->m_listCtrlAdmin->GetItemCount() ; i++){
		if(AdminFrameGlobal->m_listCtrlAdmin->GetItemData(i) == account_id){
			AdminFrameGlobal->m_listCtrlAdmin->DeleteItem(i);
			break;
		}
	}
	for(i = 0 ; i < AdminFrameGlobal->m_listCtrlJudge->GetItemCount() ; i++){
		if(AdminFrameGlobal->m_listCtrlJudge->GetItemData(i) == account_id){
			AdminFrameGlobal->m_listCtrlJudge->DeleteItem(i);
			break;
		}
	}
	for(i = 0 ; i < AdminFrameGlobal->m_listCtrlTeam->GetItemCount() ; i++){
		if(AdminFrameGlobal->m_listCtrlTeam->GetItemData(i) == account_id){
			AdminFrameGlobal->m_listCtrlTeam->DeleteItem(i);
			break;
		}
	}
	
	if(type == SRC_ADMIN){ // new type is admin
		tmp = AdminFrameGlobal->m_listCtrlAdmin->InsertItem(AdminFrameGlobal->m_listCtrlAdmin->GetItemCount(), id);
		AdminFrameGlobal->m_listCtrlAdmin->SetItem(tmp, 1, name);
		AdminFrameGlobal->m_listCtrlAdmin->SetItemData(tmp, account_id);
		
		AdminFrameGlobal->m_listCtrlAdmin->SortItems(ListCompareFunction, 0);
	}
	else if(type == SRC_JUDGE){
		tmp = AdminFrameGlobal->m_listCtrlJudge->InsertItem(AdminFrameGlobal->m_listCtrlJudge->GetItemCount(), id);
		AdminFrameGlobal->m_listCtrlJudge->SetItem(tmp, 1, name);
		AdminFrameGlobal->m_listCtrlJudge->SetItemData(tmp, account_id);
		
		AdminFrameGlobal->m_listCtrlJudge->SortItems(ListCompareFunction, 0);
	}
	else if(type == SRC_TEAM){
		tmp = AdminFrameGlobal->m_listCtrlTeam->InsertItem(AdminFrameGlobal->m_listCtrlTeam->GetItemCount(), id);
		AdminFrameGlobal->m_listCtrlTeam->SetItem(tmp, 1, name);
		AdminFrameGlobal->m_listCtrlTeam->SetItemData(tmp, account_id);
		
		AdminFrameGlobal->m_listCtrlTeam->SortItems(ListCompareFunction, 0);
	}
	else{
		// no definition, it must a mistake!
	}
	
	AdminFrameGlobal->m_mutexAccount.Unlock();
	
	return;
}

void cb_account_remove( unsigned int account_id ){
	int i;
	wxListItem item;
	item.SetColumn(0);
	item.SetMask(wxLIST_MASK_TEXT);
	
	AdminFrameGlobal->m_mutexAccount.Lock();
	
	for(i = 0 ; i < AdminFrameGlobal->m_listCtrlAdmin->GetItemCount() ; i++){
		item.SetId(i);
		AdminFrameGlobal->m_listCtrlAdmin->GetItem(item);
		if(atoi(item.GetText().char_str()) == account_id){
			AdminFrameGlobal->m_listCtrlAdmin->DeleteItem(i);
			AdminFrameGlobal->m_mutexAccount.Unlock();
			return;
		}
	}
	for(i = 0 ; i < AdminFrameGlobal->m_listCtrlJudge->GetItemCount() ; i++){
		item.SetId(i);
		AdminFrameGlobal->m_listCtrlJudge->GetItem(item);
		if(atoi(item.GetText().char_str()) == account_id){
			AdminFrameGlobal->m_listCtrlJudge->DeleteItem(i);
			AdminFrameGlobal->m_mutexAccount.Unlock();
			return;
		}
	}
	for(i = 0 ; i < AdminFrameGlobal->m_listCtrlTeam->GetItemCount() ; i++){
		item.SetId(i);
		AdminFrameGlobal->m_listCtrlTeam->GetItem(item);
		if(atoi(item.GetText().char_str()) == account_id){
			AdminFrameGlobal->m_listCtrlTeam->DeleteItem(i);
			AdminFrameGlobal->m_mutexAccount.Unlock();
			return;
		}
	}
	
	AdminFrameGlobal->m_mutexAccount.Unlock();
	
	return;
}

void cb_problem_update( unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer ){

	printf("DL\n");

	FILE *file_d, *file_i, *file_o;
	int i = 0;
	
	AdminFrameGlobal->m_mutexProblem.Lock();
	while(1){
		FILE *temp;
		char path[50];
		sprintf(path, "temp\\%d_d.tmp", i);
		printf("chcek :%s\n", path);
		temp = fopen(path, "r");
		if(temp == NULL)
			break;
		fclose(temp);
		i++;
	}
	char temp[50];
	sprintf(temp, "temp\\%d_d.tmp", i);
	file_d = fopen(temp, "w");
	sprintf(temp, "temp\\%d_i.tmp", i);
	file_i = fopen(temp, "w");
	sprintf(temp, "temp\\%d_o.tmp", i);
	file_o = fopen(temp, "w");
	fclose(file_o);
	fclose(file_i);
	fclose(file_d);
	AdminFrameGlobal->m_mutexProblem.Unlock();

	wxString path;
	path = wxString::Format(_("temp\\%d_d.tmp"), i);
	wchar_t *path_d = (wchar_t*)malloc( (wcslen(path.c_str()) + 1) * sizeof(wchar_t) );
	wcscpy(path_d, path.c_str());
	
	path = wxString::Format(_("temp\\%d_i.tmp"), i);
	wchar_t *path_i = (wchar_t*)malloc( (wcslen(path.c_str()) + 1) * sizeof(wchar_t) );
	wcscpy(path_i, path.c_str());
	
	path = wxString::Format(_("temp\\%d_o.tmp"), i);
	wchar_t *path_o = (wchar_t*)malloc( (wcslen(path.c_str()) + 1) * sizeof(wchar_t) );
	wcscpy(path_o, path.c_str());

	*path_description = path_d;
	*path_input = path_i;
	*path_answer = path_o;
	
	return;
}

void cb_problem_update_dlfin( unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer ){
	printf("DLFIN\n");
	
	AdminFrameGlobal->m_mutexProblem.Lock();
	int i;
	for(i = 0 ; i < AdminFrameGlobal->list_problem.size() ; i++)
		if(AdminFrameGlobal->list_problem[i].problem_id == problem_id)
			break;
	if(i < AdminFrameGlobal->list_problem.size())
		AdminFrameGlobal->list_problem.erase(AdminFrameGlobal->list_problem.begin() + i);
	AdminFrameGlobal->m_mutexProblem.Unlock();
	
	Problem p;
	p.problem_id = problem_id;
	p.name = wxString(problem_name);
	p.time_limit = time_limit;
	p.path_description = wxString::Format(_("data\\%d_d.pdf"), problem_id);
	p.path_input = wxString::Format(_("data\\%d_i.txt"), problem_id);
	p.path_answer = wxString::Format(_("data\\%d_o.txt"), problem_id);
	
	char path[100];
	FILE *inFile;
	FILE *outFile;
	
	wchar_t mode[10] = L"rb";
	sprintf(path, "data\\%d_d.pdf", problem_id);
	inFile = fopen_sp(path_description, mode);
	outFile = fopen(path, "wb");
	while(1){
		char buf;
		fread( &buf, sizeof( char ), 1, inFile );
		if(feof(inFile))
			break;
		fwrite( &buf, sizeof( char ), 1, outFile );
	}
	fclose(outFile);
	fclose(inFile);
	
	sprintf(path, "data\\%d_i.txt", problem_id);
	inFile = fopen_sp(path_input, mode);
	outFile = fopen(path, "wb");
	while(1){
		char buf;
		fread( &buf, sizeof( char ), 1, inFile );
		if(feof(inFile))
			break;
		fwrite( &buf, sizeof( char ), 1, outFile );
	}
	fclose(outFile);
	fclose(inFile);
	
	sprintf(path, "data\\%d_o.txt", problem_id);
	inFile = fopen_sp(path_answer, mode);
	outFile = fopen(path, "wb");
	while(1){
		char buf;
		fread( &buf, sizeof( char ), 1, inFile );
		if(feof(inFile))
			break;
		fwrite( &buf, sizeof( char ), 1, outFile );
	}
	fclose(outFile);
	fclose(inFile);
	
	AdminFrameGlobal->list_problem.push_back(p);
	
	AdminFrameGlobal->m_mutexProblem.Lock();
	long tmp;
	tmp = AdminFrameGlobal->m_listCtrlProblems->InsertItem(0, wxString() << p.problem_id);
	AdminFrameGlobal->m_listCtrlProblems->SetItem(tmp, 1, wxString() << p.name);
	AdminFrameGlobal->m_listCtrlProblems->SetItemData(tmp, p.problem_id);
	AdminFrameGlobal->m_listCtrlProblems->SortItems(ListCompareFunction, 0);
	AdminFrameGlobal->m_mutexProblem.Unlock();
	
	return;
}

/* callback functions extern-ed from protointernal.c */
void cb_login_confirm( int confirm_code, unsigned int account_id ){
	if(confirm_code == LOGIN_VALID){
		login_id = account_id;
		loginDialog->LoginSuccess();
	}
	else if(confirm_code == LOGIN_ACC_NOTEXIST){
		wxMessageBox(_("Account not exist!"));
	}
	else if(confirm_code == LOGIN_PASS_WRONG){
		wxMessageBox(_("Wrong password!"));
	}
	return;
}

void cb_logout_confirm( int confirm_code ){
	AdminFrameGlobal->Destroy();
	
	return;
}

void cb_password_change_confirm( int confirm_code ){
	if(confirm_code == PASSWD_SUCCESS){
		if(changePassDialog != NULL){
			changePassDialog->ChangeSuccess();
			changePassDialog->Destroy();
			changePassDialog = NULL;
		}
	}
	else if(confirm_code == PASSWD_MISMATCH){
		wxMessageBox(_("Wrong password!"));
	}
	else{
		wxMessageBox(_("You cannot change your password..."));
	}

	return;
}

void cb_contest_start( void ){
	printf("cb_password_change_confirm called\n");
	contestRunning = true;
	if(AdminFrameGlobal->m_timeleft > 0){
		wxCommandEvent event(wxEVT_CALL_TIMER);
		event.SetInt(1);
		wxPostEvent(AdminFrameGlobal, event);
	}
	return;
}

void cb_contest_stop( void ){
	contestRunning = false;
	wxCommandEvent event(wxEVT_CALL_TIMER);
	event.SetInt(0);
	wxPostEvent(AdminFrameGlobal, event);
	return;
}

void cb_timer_set( unsigned int hours, unsigned int minutes, unsigned int seconds ){
	AdminFrameGlobal->m_staticTextTime->SetLabel(wxString::Format(_("%d:%02d:%02d"), hours, minutes, seconds));
	AdminFrameGlobal->m_timeleft = hours * 60 * 60 + minutes * 60 + seconds;
	if(contestRunning == true){
		printf("call cb_contest_start\n");
		cb_contest_start();
	}
	return;
}

void cb_clar_request( unsigned int clar_id, unsigned int account_id, wchar_t *account, int private_byte, wchar_t *clarmsg ){
	printf("cb_clar_request\n");
	wprintf(L"%s\n", clarmsg);
	
	AdminFrameGlobal->m_mutexClar.Lock();
	int i;
	for(i = 0 ; i < AdminFrameGlobal->list_clar.size() ; i++)
		if(AdminFrameGlobal->list_clar[i].clar_id == clar_id)
			break;
	if(i < AdminFrameGlobal->list_clar.size()){ // in list
		AdminFrameGlobal->list_clar[i].account_id = account_id;
		AdminFrameGlobal->list_clar[i].clar_msg = wxString(clarmsg);
		AdminFrameGlobal->list_clar[i].private_byte = private_byte;
	}
	else{ // not in list
		Clar c;
		c.clar_id = clar_id;
		c.account_id = account_id;
		c.name = wxString(account);
		c.private_byte = private_byte;
		c.clar_msg = wxString(clarmsg);
		c.result_msg = wxEmptyString;
		AdminFrameGlobal->list_clar.push_back(c);
		
		long tmp;
		tmp = AdminFrameGlobal->m_listCtrlClars->InsertItem(0, wxString() << clar_id);
		wxString msg = wxString(clarmsg);
		printf("msg = %s\n", msg.c_str());
		msg = msg.Mid(0, 10);
		msg << _("...");
		AdminFrameGlobal->m_listCtrlClars->SetItem(tmp, 1, msg);
		AdminFrameGlobal->m_listCtrlClars->SetItemData(tmp, clar_id);
		AdminFrameGlobal->m_listCtrlClars->SortItems(ListCompareFunction, 0);
	}
	
	AdminFrameGlobal->m_mutexClar.Unlock();
	
	return;
}

void cb_clar_reply( unsigned int clar_id, wchar_t *clarmsg, wchar_t *result_string ){
	printf("cb_clar_reply\n");

	AdminFrameGlobal->m_mutexClar.Lock();
	int i;
	for(i = 0 ; i < AdminFrameGlobal->list_clar.size() ; i++)
		if(AdminFrameGlobal->list_clar[i].clar_id == clar_id)
			break;
	if(i < AdminFrameGlobal->list_clar.size()){ // in list
		AdminFrameGlobal->list_clar[i].result_msg = wxString(result_string);
	}
	else{
		Clar c;
		c.clar_id = clar_id;
		c.result_msg = wxString(result_string);
		AdminFrameGlobal->list_clar.push_back(c);
	}
	AdminFrameGlobal->m_mutexClar.Unlock();
	
	return;
}

void cb_sb_update( unsigned int updated_account_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time ){
	AdminFrameGlobal->m_mutexScoreboard.Lock();
	
	for(int i = 0 ; i < AdminFrameGlobal->m_listCtrlSB->GetItemCount() ; i++){
		if(AdminFrameGlobal->m_listCtrlSB->GetItemData(i) == updated_account_id){
			AdminFrameGlobal->m_listCtrlSB->DeleteItem(i);
			break;
		}
	}
	long tmp;
	tmp = AdminFrameGlobal->m_listCtrlSB->InsertItem(0, wxString() << updated_account_id);
	AdminFrameGlobal->m_listCtrlSB->SetItem(tmp, 1, wxString(new_account));
	AdminFrameGlobal->m_listCtrlSB->SetItem(tmp, 2, wxString() << new_accept_count);
	AdminFrameGlobal->m_listCtrlSB->SetItem(tmp, 3, wxString() << new_time);
	AdminFrameGlobal->m_listCtrlSB->SetItemData(tmp, updated_account_id);
	
	wxListItem item;
	
	for(int i = 0 ; i < AdminFrameGlobal->m_listCtrlSB->GetItemCount() ; i++){
		unsigned int temp;
		item.SetId(i);
		item.SetColumn(2);
		item.SetMask(wxLIST_MASK_TEXT);
		AdminFrameGlobal->m_listCtrlSB->GetItem(item);
		temp = wxAtoi(item.GetText());
		AdminFrameGlobal->m_listCtrlSB->SetItem(i, 2, wxString() << AdminFrameGlobal->m_listCtrlSB->GetItemData(i));
		AdminFrameGlobal->m_listCtrlSB->SetItemData(i, temp);
	}
	AdminFrameGlobal->m_listCtrlSB->SortItems(ListCompareFunction, 1);
	int rank = 1, p_rank = 1;
	int accnum = AdminFrameGlobal->m_listCtrlSB->GetItemData(0);
	for(int i = 0 ; i < AdminFrameGlobal->m_listCtrlSB->GetItemCount() ; i++){
		if(accnum != AdminFrameGlobal->m_listCtrlSB->GetItemData(i)){
			rank = p_rank;
			accnum = AdminFrameGlobal->m_listCtrlSB->GetItemData(i);
		}
		AdminFrameGlobal->m_listCtrlSB->SetItem(i, 0, wxString() << rank);
		p_rank++;
		unsigned int temp;
		item.SetId(i);
		item.SetColumn(2);
		item.SetMask(wxLIST_MASK_TEXT);
		AdminFrameGlobal->m_listCtrlSB->GetItem(item);
		temp = wxAtoi(item.GetText());
		AdminFrameGlobal->m_listCtrlSB->SetItem(i, 2, wxString() << AdminFrameGlobal->m_listCtrlSB->GetItemData(i));
		AdminFrameGlobal->m_listCtrlSB->SetItemData(i, temp);
	}
	
	
	AdminFrameGlobal->m_mutexScoreboard.Unlock();
	
	return;
}

void cb_sb_remove( unsigned int rm_account_id ){
	AdminFrameGlobal->m_mutexScoreboard.Lock();
	for(int i = 0 ; i < AdminFrameGlobal->m_listCtrlSB->GetItemCount() ; i++)
		if(AdminFrameGlobal->m_listCtrlSB->GetItemData(i) == rm_account_id)
			AdminFrameGlobal->m_listCtrlSB->DeleteItem(i);
	AdminFrameGlobal->m_mutexScoreboard.Unlock();
	
	return;
}

void cb_problem_remove( unsigned int problem_id ){
	AdminFrameGlobal->m_mutexProblem.Lock();
	for(int i = 0 ; i < AdminFrameGlobal->m_listCtrlProblems->GetItemCount() ; i++){
		if(AdminFrameGlobal->m_listCtrlProblems->GetItemData(i) == problem_id){
			AdminFrameGlobal->m_listCtrlProblems->DeleteItem(i);
			break;
		}
	}
	AdminFrameGlobal->m_mutexProblem.Unlock();
	
	return;
}

AdminFrame::AdminFrame(wxFrame *frame)
    : AdminGUI(frame), m_timer(this){
	char localaddr[20];
	int ip1, ip2, ip3, ip4;
	FILE *ipFile;
	
	AdminFrameGlobal = this;
	ClarEnable(false);
	
	if(!wxDirExists(_("temp")))
		wxMkdir(_("temp"));
	if(!wxDirExists(_("data")))
		wxMkdir(_("data"));
	
	InitAccountList();
	InitProblemList();
	InitClarList();
	InitSBList();
	m_timeleft = 0;
	contestRunning = false;

	isProblemInfoEnable = true;
	ProblemInfoClear();
	ProblemInfoEnable(false);
	ClarClear();
	ClarEnable(false);
	
	loginDialog = new LoginDialog(this);
	
	adminproto_cbreg_login_confirm( cb_login_confirm );
	adminproto_cbreg_logout_confirm( cb_logout_confirm );
	adminproto_cbreg_password_change_confirm( cb_password_change_confirm );
	adminproto_cbreg_timer_set( cb_timer_set );
	adminproto_cbreg_contest_start( cb_contest_start );
	adminproto_cbreg_contest_stop( cb_contest_stop );
	adminproto_cbreg_clar_request( cb_clar_request );
	adminproto_cbreg_clar_reply( cb_clar_reply );
	adminproto_cbreg_account_update( cb_account_update );
	adminproto_cbreg_account_remove( cb_account_remove );
	adminproto_cbreg_problem_update( cb_problem_update );
	adminproto_cbreg_problem_update_dlfin( cb_problem_update_dlfin );
	adminproto_cbreg_problem_remove( cb_problem_remove );
	adminproto_cbreg_sb_update( cb_sb_update );
	adminproto_cbreg_sb_remove( cb_sb_remove );
	
	sprintf(localaddr, "0.0.0.0");
	ipFile = fopen("ip.txt", "r");
	if(ipFile == NULL){
		wxMessageBox(_("ip.txt not found!"));
		isLogin = false;
	}
	else if(fscanf(ipFile, "%d.%d.%d.%d", &ip1, &ip2, &ip3, &ip4) != 4){
		wxMessageBox(_("Invalid IP Address!"));
		isLogin = false;
	}
	else if(adminproto_listen(localaddr) < 0){
		wxMessageBox(_("Listen Error!"));
		isLogin = false;
	}
	else{
		sprintf(server_ip, "%d.%d.%d.%d", ip1, ip2, ip3, ip4);
		if(loginDialog->ShowModal() == 0)
			isLogin = false;
		else
			isLogin = true;
	}
	loginDialog->Destroy();
	
	if(isLogin){
		m_staticTextName->SetLabel(m_loginName);
		adminproto_account_sync(server_ip);
		adminproto_problem_sync(server_ip);
		adminproto_sb_sync(server_ip);
		adminproto_timer_sync(server_ip);
		adminproto_contest_state_sync(server_ip);
		adminproto_clar_sync(server_ip);
	}
	
}

AdminFrame::~AdminFrame(){
	wxString filename;
	if(wxDirExists(_("temp"))){
		filename = wxFindFirstFile(_("temp/*"));
		while(filename != wxEmptyString){
			wxRemoveFile(filename);
			filename = wxFindNextFile();
		}
		wxRmdir(_("temp"));
	}
	if(wxDirExists(_("data"))){
		filename = wxFindFirstFile(_("data/*"));
		while(filename != wxEmptyString){
			wxRemoveFile(filename);
			filename = wxFindNextFile();
		}
		wxRmdir(_("data"));
	}
}

void AdminFrame::InitAccountList(){
	wxListItem itemCol;
	
	m_listCtrlAdmin->DeleteAllItems();
	while(m_listCtrlAdmin->GetColumnCount())
		m_listCtrlAdmin->DeleteColumn(0);
	
	m_listCtrlJudge->DeleteAllItems();
	while(m_listCtrlJudge->GetColumnCount())
		m_listCtrlJudge->DeleteColumn(0);
	
	m_listCtrlTeam->DeleteAllItems();
	while(m_listCtrlTeam->GetColumnCount())
		m_listCtrlTeam->DeleteColumn(0);
	
	itemCol.SetText(_("ID"));
	m_listCtrlAdmin->InsertColumn(0, itemCol);
	m_listCtrlJudge->InsertColumn(0, itemCol);
	m_listCtrlTeam->InsertColumn(0, itemCol);
	
	itemCol.SetText(_("Name"));
	m_listCtrlAdmin->InsertColumn(1, itemCol);
	m_listCtrlJudge->InsertColumn(1, itemCol);
	m_listCtrlTeam->InsertColumn(1, itemCol);
	
	return;
}

void AdminFrame::InitProblemList(){
	wxListItem itemCol;
	
	m_listCtrlProblems->DeleteAllItems();
	while(m_listCtrlProblems->GetColumnCount())
		m_listCtrlProblems->DeleteColumn(0);
	
	itemCol.SetText(_("ID"));
	m_listCtrlProblems->InsertColumn(0, itemCol);
	
	itemCol.SetText(_("Name"));
	m_listCtrlProblems->InsertColumn(1, itemCol);
	
	m_selectedProblem = -1;
	
	return;
}

void AdminFrame::InitClarList(){
	wxListItem itemCol;
	
	m_listCtrlClars->DeleteAllItems();
	while(m_listCtrlClars->GetColumnCount())
		m_listCtrlClars->DeleteColumn(0);
	
	itemCol.SetText(_("ID"));
	m_listCtrlClars->InsertColumn(0, itemCol);
	
	itemCol.SetText(_("Message"));
	m_listCtrlClars->InsertColumn(1, itemCol);
	
	m_selectedClar = -1;
	
	return;
}

void AdminFrame::InitSBList(){
	wxListItem itemCol;
	
	m_listCtrlSB->DeleteAllItems();
	while(m_listCtrlSB->GetColumnCount())
		m_listCtrlSB->DeleteColumn(0);
	
	itemCol.SetText(_("Rank"));
	m_listCtrlSB->InsertColumn(0, itemCol);
	itemCol.SetText(_("ID-Name"));
	m_listCtrlSB->InsertColumn(1, itemCol);
	itemCol.SetText(_("Accept"));
	m_listCtrlSB->InsertColumn(2, itemCol);
	itemCol.SetText(_("Penalty"));
	m_listCtrlSB->InsertColumn(3, itemCol);
	
	return;
}

void AdminFrame::ProblemInfoEnable(bool enable){
	if(isProblemInfoEnable == enable)
		return;
	m_staticTextProblemID->Enable(enable);
	m_textCtrlProblemID->Enable(enable);
	m_staticTextProblemName->Enable(enable);
	m_textCtrlProblemName->Enable(enable);
	m_checkBoxProblemFile->Enable(enable);
	m_filePickerProblemFile->Enable(enable);
	m_staticTextTimeLimit->Enable(enable);
	m_spinCtrlTimeLimitVal->Enable(enable);
	m_staticTextTimeLimitUnit->Enable(enable);
	m_staticTextProblemInputData->Enable(enable);
	m_filePickerProblemInputData->Enable(enable);
	m_staticTextProblemOutputData->Enable(enable);
	m_filePickerProblemOutputData->Enable(enable);
	m_buttonProblemApply->Enable(enable);
	isProblemInfoEnable = enable;
	
	return;
}

void AdminFrame::ProblemInfoClear(){
	m_textCtrlProblemID->Clear();
	m_textCtrlProblemName->Clear();
	m_filePickerProblemFile->SetPath(wxEmptyString);
	m_spinCtrlTimeLimitVal->SetValue(3000);
	m_filePickerProblemInputData->SetPath(wxEmptyString);
	m_filePickerProblemOutputData->SetPath(wxEmptyString);
	
	return;
}

void AdminFrame::ClarEnable(bool enable){
	m_textCtrlQuestion->Enable(enable);
	m_textCtrlAnswer->Enable(enable);
	m_buttonClarReply->Enable(enable);
	
	return;
}

void AdminFrame::ClarClear(){
	m_textCtrlQuestion->Clear();
	m_textCtrlAnswer->Clear();
	m_staticTextClarIDVal->SetLabel(wxEmptyString);

	return;
}

void AdminFrame::OnButtonClickChangePassword( wxCommandEvent& event ){
	changePassDialog = new ChangePassDialog(this);
	changePassDialog->ShowModal();
	
	return;
}

void AdminFrame::OnButtonClickLogout( wxCommandEvent& event ){
	if(adminproto_logout(server_ip, login_id) < 0)
		wxMessageBox(_("Server not responding"));
	
	return;
}

void AdminFrame::OnListItemActivatedAdmin( wxListEvent& event ){
	wxListItem item;
	item.SetId(event.GetIndex());
	item.SetColumn(1);
	item.SetMask(wxLIST_MASK_TEXT);
	m_listCtrlAdmin->GetItem(item);
	AccountDialog *accountDialog = new AccountDialog(this, item.GetText(), SRC_ADMIN, event.GetIndex());
	accountDialog->ShowModal();
	accountDialog->Destroy();
	
	return;
}

void AdminFrame::OnListItemSelectedAdmin( wxListEvent& event ){
	int i;
	for(i = 0 ; i < m_listCtrlJudge->GetItemCount() ; i++)
		m_listCtrlJudge->SetItemState(i, !wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
	for(i = 0 ; i < m_listCtrlTeam->GetItemCount() ; i++)
		m_listCtrlTeam->SetItemState(i, !wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
	
	return;
}

void AdminFrame::OnListItemActivatedJudge( wxListEvent& event ){
	wxListItem item;
	item.SetId(event.GetIndex());
	item.SetColumn(1);
	item.SetMask(wxLIST_MASK_TEXT);
	m_listCtrlJudge->GetItem(item);
	AccountDialog *accountDialog = new AccountDialog(this, item.GetText(), SRC_JUDGE, event.GetIndex());
	accountDialog->ShowModal();
	accountDialog->Destroy();
	
	return;
}

void AdminFrame::OnListItemSelectedJudge( wxListEvent& event ){
	int i;
	for(i = 0 ; i < m_listCtrlAdmin->GetItemCount() ; i++)
		m_listCtrlAdmin->SetItemState(i, !wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
	for(i = 0 ; i < m_listCtrlTeam->GetItemCount() ; i++)
		m_listCtrlTeam->SetItemState(i, !wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
	
	return;
}

void AdminFrame::OnListItemActivatedTeam( wxListEvent& event ){
	wxListItem item;
	item.SetId(event.GetIndex());
	item.SetColumn(1);
	item.SetMask(wxLIST_MASK_TEXT);
	m_listCtrlTeam->GetItem(item);
	AccountDialog *accountDialog = new AccountDialog(this, item.GetText(), SRC_TEAM, event.GetIndex());
	accountDialog->ShowModal();
	accountDialog->Destroy();
	
	return;
}

void AdminFrame::OnListItemSelectedTeam( wxListEvent& event ){
	int i;
	for(i = 0 ; i < m_listCtrlAdmin->GetItemCount() ; i++)
		m_listCtrlAdmin->SetItemState(i, !wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
	for(i = 0 ; i < m_listCtrlJudge->GetItemCount() ; i++)
		m_listCtrlJudge->SetItemState(i, !wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
	
	return;
}

void AdminFrame::OnButtonClickNewAccount( wxCommandEvent& event ){
	AccountDialog *accountDialog = new AccountDialog(this);
	accountDialog->ShowModal();
	accountDialog->Destroy();
	return;
}

void AdminFrame::OnButtonClickDeleteAccount( wxCommandEvent& event ){
	int i;
	i = -1;
	while(1){
		i = m_listCtrlAdmin->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if(i == -1)
			break;
		unsigned int account_id = m_listCtrlAdmin->GetItemData(i);
		adminproto_account_del(server_ip, account_id);
		m_listCtrlAdmin->DeleteItem(i);
	}

	i = -1;
	while(1){
		i = m_listCtrlJudge->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if(i == -1)
			break;
		unsigned int account_id = m_listCtrlJudge->GetItemData(i);
		adminproto_account_del(server_ip, account_id);
		m_listCtrlJudge->DeleteItem(i);
	}
	
	i = -1;
	while(1){
		i = m_listCtrlTeam->GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if(i == -1)
			break;
		unsigned int account_id = m_listCtrlTeam->GetItemData(i);
		adminproto_account_del(server_ip, account_id);
		m_listCtrlTeam->DeleteItem(i);
	}
	
	return;
}

void AdminFrame::OnButtonClickManualTimeSet( wxCommandEvent& event ){
	unsigned int hr = 0, min = 0, sec = 0;
	hr = m_spinCtrlTimeManualTotalHr->GetValue();
	min = m_spinCtrlTimeManualTotalMin->GetValue();
	adminproto_timer_set(server_ip, hr, min, sec);
	
	return;
}

void AdminFrame::OnButtonClickStart( wxCommandEvent& event ){
	printf("call adminproto_contest_start\n");
	if(adminproto_contest_start(server_ip) < 0)
		wxMessageBox(_("Cannot start contest!"));
	
	return;
}

void AdminFrame::OnButtonClickStop( wxCommandEvent& event ){
printf("call adminproto_contest_stop\n");
	if(adminproto_contest_stop(server_ip) < 0)
		wxMessageBox(_("Cannot stop contest!"));
	
	return;
}

void AdminFrame::OnListItemDeselectedProblem( wxListEvent& event ){
	ProblemInfoClear();
	ProblemInfoEnable(false);
	m_selectedProblem = -1;
}

void AdminFrame::OnListItemSelectedProblem( wxListEvent& event ){
	ProblemInfoEnable(true);
	
	m_textCtrlProblemID->SetValue(wxString() << list_problem[event.GetIndex()].problem_id);
	m_textCtrlProblemName->SetLabel(wxString() << list_problem[event.GetIndex()].name);
	m_filePickerProblemFile->SetPath(wxString() << list_problem[event.GetIndex()].path_description);
	m_spinCtrlTimeLimitVal->SetValue(list_problem[event.GetIndex()].time_limit);
	m_filePickerProblemInputData->SetPath(wxString() << list_problem[event.GetIndex()].path_input);
	m_filePickerProblemOutputData->SetPath(wxString() << list_problem[event.GetIndex()].path_answer);
	
	m_selectedProblem = event.GetIndex();
}

void AdminFrame::OnButtonClickAddProblem( wxCommandEvent& event ){
	int i;
	for(i = 0 ; i < m_listCtrlProblems->GetItemCount() ; i++)
		m_listCtrlProblems->SetItemState(i, !wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
	m_selectedProblem = -1;
	ProblemInfoClear();
	ProblemInfoEnable(true);
	
	return;
}

void AdminFrame::OnButtonClickDelProblem( wxCommandEvent& event ){
	if(m_selectedProblem == -1){
		wxMessageBox(_("No problem is selected"));
	}
	else{
		wxListItem item;
		item.SetId(m_selectedProblem);
		item.SetColumn(0);
		item.SetMask(wxLIST_MASK_TEXT);
		m_listCtrlProblems->GetItem(item);
		unsigned int id = wxAtoi(item.GetText());
		adminproto_problem_del(server_ip, id);
	}
	
	return;
}

void AdminFrame::OnCheckBoxProblemFile( wxCommandEvent& event ){
	m_checkBoxProblemFile->SetValue(true);
	
	return;
}

void AdminFrame::OnButtonClickProblemApply( wxCommandEvent& event ){
	printf("Apply click\n");
	if(m_selectedProblem == -1){
		//new
		if(m_textCtrlProblemID->IsEmpty()){
			wxMessageBox(_("Problem ID cannot be empty!"));
			return;
		}
		// check if problem id exist
		int i;
		wxListItem item;
		item.SetColumn(0);
		item.SetMask(wxLIST_MASK_TEXT);
		unsigned int id = wxAtoi(m_textCtrlProblemID->GetLabel());
		for(i = 0 ; i < m_listCtrlProblems->GetItemCount() ; i++){
			item.SetId(i);
			m_listCtrlProblems->GetItem(item);
			if(wxAtoi(item.GetText()) == id){
				wxMessageBox(_("Problem ID is existed!"));
				return;
			}
		}
		
		if(m_textCtrlProblemName->IsEmpty()){
			wxMessageBox(_("Problem name cannot be empty!"));
			return;
		}
		
		if(m_filePickerProblemFile->GetPath() == wxEmptyString){
			wxMessageBox(_("Problem's path cannot be empty!"));
			return;
		}
		
		// check input and output data path is not empty
		if(m_filePickerProblemInputData->GetPath() == wxEmptyString){
			wxMessageBox(_("Input data's path cannot be empty!"));
			return;
		}
		if(m_filePickerProblemOutputData->GetPath() == wxEmptyString){
			wxMessageBox(_("Output data's path cannot be empty!"));
			return;
		}
		
		//wchar_t *name = m_textCtrlProblemName->GetLabel().wchar_str();
		wchar_t *name = new wchar_t [wcslen(m_textCtrlProblemName->GetLabel().c_str()) + 1];
		wcscpy( name, m_textCtrlProblemName->GetLabel().c_str() );
		
		//wchar_t *p_path = m_filePickerProblemFile->GetPath().wchar_str();
		wchar_t *p_path = new wchar_t [wcslen(m_filePickerProblemFile->GetPath().c_str()) + 1];
		wcscpy( p_path, m_filePickerProblemFile->GetPath().c_str() );
		
		unsigned int time_limit = m_spinCtrlTimeLimitVal->GetValue();
		//wchar_t *i_path = m_filePickerProblemInputData->GetPath().wchar_str();
		wchar_t *i_path = new wchar_t [wcslen(m_filePickerProblemInputData->GetPath().c_str()) + 1];
		wcscpy( i_path, m_filePickerProblemInputData->GetPath().c_str() );
		
		//wchar_t *o_path = m_filePickerProblemOutputData->GetPath().wchar_str();
		wchar_t *o_path = new wchar_t [wcslen(m_filePickerProblemOutputData->GetPath().c_str()) + 1];
		wcscpy( o_path, m_filePickerProblemOutputData->GetPath().c_str() );
		
		wprintf(L"%s\n", name);
		wprintf(L"%s\n", p_path);
		wprintf(L"%s\n", i_path);
		wprintf(L"%s\n", o_path);
		
		adminproto_problem_add(server_ip, id, name, time_limit, p_path, i_path, o_path);
	}
	else{
		//edit
		m_selectedProblem = -1;
	}
	ProblemInfoClear();
	ProblemInfoEnable(false);
	
	
	return;
}

void AdminFrame::OnListItemDeselectedClar( wxListEvent& event ){
	m_selectedClar = -1;
	ClarClear();
	ClarEnable(false);
	
	return;
}

void AdminFrame::OnListItemSelectedClar( wxListEvent& event ){
	ClarEnable(true);
	m_selectedClar = m_listCtrlClars->GetItemData(event.GetIndex());
	m_staticTextClarIDVal->SetLabel(wxString() << list_clar[event.GetIndex()].clar_id);
	m_textCtrlQuestion->SetLabel(list_clar[event.GetIndex()].clar_msg);
	m_textCtrlAnswer->SetLabel(list_clar[event.GetIndex()].result_msg);
	
	return;
}

void AdminFrame::OnButtonClickClarReply( wxCommandEvent& event ){
	if(m_selectedClar < 0)
		return;

	wchar_t *result = new wchar_t [wcslen(m_textCtrlAnswer->GetLabel().c_str()) + 1];
	wcscpy( result, m_textCtrlAnswer->GetLabel().c_str() );
	
	adminproto_clar_result(server_ip, m_selectedClar, 0, result);

	for(int i = 0 ; i < m_listCtrlClars->GetItemCount() ; i++)
		m_listCtrlClars->SetItemState(i, !wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
	m_selectedClar = -1;
	ClarEnable(false);
	ClarClear();
	
	return;
}

void AdminFrame::OnTimerEvent(wxTimerEvent &event){
	m_timeleft--;
	m_staticTextTime->SetLabel(wxString::Format(_("%d:%02d:%02d"), m_timeleft / 60 / 60, (m_timeleft / 60) % 60, m_timeleft % 60));
	if(m_timeleft <= 0){
		//contest end
		m_timer.Stop();
		contestRunning = false;
	}
	
	return;
}

void AdminFrame::TimerCall(wxCommandEvent &event){
	if(event.GetInt() == 1 && m_timer.IsRunning() == 0)
		m_timer.Start(1000);
	else if(event.GetInt() == 0 && m_timer.IsRunning() == 1)
		m_timer.Stop();
	
	return;
}