#include "AdminMain.h"
#include "AccountDialog.h"
#include "ChangePassDialog.h"
extern "C"
{
#include "adminproto.h"
}

BEGIN_EVENT_TABLE(AdminFrame, wxFrame)
    EVT_TIMER(-1, AdminFrame::OnTimerEvent)
END_EVENT_TABLE()

AdminFrame* AdminFrameGlobal;

char server_ip[20];
wxString m_loginName;
unsigned int login_id;
LoginDialog *loginDialog = NULL;
ChangePassDialog *changePassDialog = NULL;

/* callback functions */
void cb_account_update( unsigned int account_id, unsigned int type, wchar_t *account ){
	wxString name(account);
	wxString id = wxString() << account_id;
	long tmp;
	unsigned int old_type;
	int index;
	int i;
	bool found = false;
	
	//find in the lists
	for(i = 0 ; i < AdminFrameGlobal->m_listCtrlAdmin->GetItemCount() ; i++)
		if(AdminFrameGlobal->m_listCtrlAdmin->GetItemData(i) == account_id)
			break;
	if(i < AdminFrameGlobal->m_listCtrlAdmin->GetItemCount()){
		index = i;
		old_type = SRC_ADMIN;
		found = true;
	}
	
	if(!found){
		for(i = 0 ; i < AdminFrameGlobal->m_listCtrlJudge->GetItemCount() ; i++)
			if(AdminFrameGlobal->m_listCtrlJudge->GetItemData(i) == account_id)
				break;
		if(i < AdminFrameGlobal->m_listCtrlJudge->GetItemCount()){
			index = i;
			old_type = SRC_JUDGE;
			found = true;
		}
	}
	
	if(!found){
		for(i = 0 ; i < AdminFrameGlobal->m_listCtrlTeam->GetItemCount() ; i++)
			if(AdminFrameGlobal->m_listCtrlTeam->GetItemData(i) == account_id)
				break;
		if(i < AdminFrameGlobal->m_listCtrlTeam->GetItemCount()){
			index = i;
			old_type = SRC_TEAM;
			found = true;
		}
	}
	
	if(type == SRC_ADMIN){ // new type is admin
		if(found && type == old_type){ // type no change
			AdminFrameGlobal->m_listCtrlAdmin->SetItem(index, 1, name);
			return;
		}
		if(found){ // type change
			if(old_type == SRC_JUDGE)
				AdminFrameGlobal->m_listCtrlJudge->DeleteItem(index);
			else if(old_type == SRC_TEAM)
				AdminFrameGlobal->m_listCtrlTeam->DeleteItem(index);
		}
		tmp = AdminFrameGlobal->m_listCtrlAdmin->InsertItem(AdminFrameGlobal->m_listCtrlAdmin->GetItemCount(), id);
		AdminFrameGlobal->m_listCtrlAdmin->SetItem(tmp, 1, name);
		AdminFrameGlobal->m_listCtrlAdmin->SetItemData(tmp, account_id);
	}
	else if(type == SRC_JUDGE){
		if(found && type == old_type){ // type no change
			AdminFrameGlobal->m_listCtrlJudge->SetItem(index, 1, name);
			return;
		}
		if(found){ // type change
			if(old_type == SRC_ADMIN)
				AdminFrameGlobal->m_listCtrlAdmin->DeleteItem(index);
			else if(old_type == SRC_TEAM)
				AdminFrameGlobal->m_listCtrlTeam->DeleteItem(index);
		}
		tmp = AdminFrameGlobal->m_listCtrlJudge->InsertItem(AdminFrameGlobal->m_listCtrlJudge->GetItemCount(), id);
		AdminFrameGlobal->m_listCtrlJudge->SetItem(tmp, 1, name);
		AdminFrameGlobal->m_listCtrlJudge->SetItemData(tmp, account_id);
	}
	else if(type == SRC_TEAM){
		if(found && type == old_type){ // type no change
			AdminFrameGlobal->m_listCtrlTeam->SetItem(index, 1, name);
			return;
		}
		if(found){ // type change
			if(old_type == SRC_JUDGE)
				AdminFrameGlobal->m_listCtrlJudge->DeleteItem(index);
			else if(old_type == SRC_ADMIN)
				AdminFrameGlobal->m_listCtrlAdmin->DeleteItem(index);
		}
		tmp = AdminFrameGlobal->m_listCtrlTeam->InsertItem(AdminFrameGlobal->m_listCtrlTeam->GetItemCount(), id);
		AdminFrameGlobal->m_listCtrlTeam->SetItem(tmp, 1, name);
		AdminFrameGlobal->m_listCtrlTeam->SetItemData(tmp, account_id);
	}
	else{
		// no definition, it must a mistake!
	}
	return;
}

void cb_account_remove( unsigned int account_id ){
	int i;
	wxListItem item;
	item.SetColumn(0);
	item.SetMask(wxLIST_MASK_TEXT);
	
	for(i = 0 ; i < AdminFrameGlobal->m_listCtrlAdmin->GetItemCount() ; i++){
		item.SetId(i);
		AdminFrameGlobal->m_listCtrlAdmin->GetItem(item);
		if(atoi(item.GetText().char_str()) == account_id){
			AdminFrameGlobal->m_listCtrlAdmin->DeleteItem(i);
			return;
		}
	}

	for(i = 0 ; i < AdminFrameGlobal->m_listCtrlJudge->GetItemCount() ; i++){
		item.SetId(i);
		AdminFrameGlobal->m_listCtrlJudge->GetItem(item);
		if(atoi(item.GetText().char_str()) == account_id){
			AdminFrameGlobal->m_listCtrlJudge->DeleteItem(i);
			return;
		}
	}
	
	for(i = 0 ; i < AdminFrameGlobal->m_listCtrlTeam->GetItemCount() ; i++){
		item.SetId(i);
		AdminFrameGlobal->m_listCtrlTeam->GetItem(item);
		if(atoi(item.GetText().char_str()) == account_id){
			AdminFrameGlobal->m_listCtrlTeam->DeleteItem(i);
			return;
		}
	}
	
	return;
}

void cb_problem_update( unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer ){

	FILE *file_d, *file_i, *file_o;
	char path[20];
	int i = 0;
	
	while(1){
		FILE *temp;
		sprintf(path, "temp\\%d_d.tmp", i);
		temp = fopen(path, "r");
		if(temp == NULL)
			return;
		fclose(temp);
		i++;
	}
	
	file_d = fopen("temp\\%d_d.tmp", "w");
	file_i = fopen("temp\\%d_i.tmp", "w");
	file_o = fopen("temp\\%d_o.tmp", "w");
	fclose(file_o);
	fclose(file_i);
	fclose(file_d);
	
	
	Problem p;
	//p.problem_id = problem_id;
	//p.name = wxString(problem_name);
	//p.time_limit = time_limit;
	p.path_description = _("temp\\%d_d.tmp");
	p.path_input = _("temp\\%d_i.tmp");
	p.path_answer = _("temp\\%d_o.tmp");
	//AdminFrameGlobal->temp_problem.push_back(p);
	
	wchar_t *p_d = new wchar_t [wcslen(p.path_description.c_str()) + 1];
	wcscpy(p_d, p.path_description.c_str());
	wchar_t *p_i = new wchar_t [wcslen(p.path_input.c_str()) + 1];
	wcscpy(p_i, p.path_input.c_str());
	wchar_t *p_a = new wchar_t [wcslen(p.path_answer.c_str()) + 1];
	wcscpy(p_a, p.path_answer.c_str());
	
	*path_description = p_d;
	*path_input = p_i;
	*path_answer = p_a;
	
	return;

}

void cb_problem_update_dlfin( unsigned int problem_id, wchar_t *problem_name, unsigned int time_limit, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer ){
	
	int i = 0;
	for(i = 0 ; i < AdminFrameGlobal->list_problem.size() ; i++)
		if(AdminFrameGlobal->list_problem[i].problem_id == problem_id)
			break;
	if(i < AdminFrameGlobal->list_problem.size())
		AdminFrameGlobal->list_problem.erase(AdminFrameGlobal->list_problem.begin() + i);
	
	Problem p;
	p.problem_id = problem_id;
	p.name = wxString(problem_name);
	p.time_limit = time_limit;
	p.path_description = wxString(path_description);
	p.path_input = wxString(path_input);
	p.path_answer = wxString(path_answer);
	
	char path[100];
	FILE *inFile;
	FILE *outFile;
	
	sprintf(path, "data\\%s_d.dat", problem_id);
	inFile = fopen_sp(path_description, L"rb");
	outFile = fopen(path, "wb");
	while( !feof( inFile ) ){
		char buf;
		fread( &buf, sizeof( char ), 1, inFile );
		fwrite( &buf, sizeof( char ), 1, outFile );
	}
	
	sprintf(path, "data\\%s_i.dat", problem_id);
	inFile = fopen_sp(path_input, L"rb");
	outFile = fopen(path, "wb");
	while( !feof( inFile ) ){
		char buf;
		fread( &buf, sizeof( char ), 1, inFile );
		fwrite( &buf, sizeof( char ), 1, outFile );
	}
	
	sprintf(path, "data\\%s_o.dat", problem_id);
	inFile = fopen_sp(path_answer, L"rb");
	outFile = fopen(path, "wb");
	while( !feof( inFile ) ){
		char buf;
		fread( &buf, sizeof( char ), 1, inFile );
		fwrite( &buf, sizeof( char ), 1, outFile );
	}
	
	//AdminFrameGlobal->temp_problem.push_back(p);
	
	/*
	unsigned int index;
	int tmp, i;
	bool found = false;
	wxString name(problem_name);
	
	//find in the lists
	for(i = 0 ; i < AdminFrameGlobal->m_listCtrlProblems->GetItemCount() ; i++)
		if(AdminFrameGlobal->m_listCtrlProblems->GetItemData(i) == problem_id)
			break;
	if(i < AdminFrameGlobal->m_listCtrlProblems->GetItemCount()){
		index = i;
		found = true;
	}
	
	tmp = AdminFrameGlobal->m_listCtrlProblems->InsertItem(AdminFrameGlobal->m_listCtrlProblems->GetItemCount(), id);
	AdminFrameGlobal->m_listCtrlProblems->SetItem(tmp, 1, name);
	AdminFrameGlobal->m_listCtrlProblems->SetItemData(tmp, problem_id);
	
	return;
	*/
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

void cb_timer_set( unsigned int hours, unsigned int minutes, unsigned int seconds ){
	AdminFrameGlobal->m_staticTextTime->SetLabel(wxString::Format(_("%d:%02d:%02d"), hours, minutes, seconds));
	AdminFrameGlobal->m_timeleft = hours * 60 * 60 + minutes * 60 + seconds;
	
	return;
}

void cb_contest_start( void ){

}

void cb_contest_stop( void ){

}

void cb_clar_request( unsigned int clar_id, unsigned int account_id, wchar_t *account, int private_byte, wchar_t *clarmsg ){

}

void cb_clar_reply( unsigned int clar_id, wchar_t *clarmsg, wchar_t *result_string ){

}

void cb_sb_update( unsigned int updated_account_id, wchar_t *new_account, unsigned int new_accept_count, unsigned int new_time ){

}

void cb_problem_remove( unsigned int problem_id ){
	int i;
	for(i = 0 ; i < AdminFrameGlobal->m_listCtrlProblems->GetItemCount() ; i++){
		if(AdminFrameGlobal->m_listCtrlProblems->GetItemData(i) == problem_id){
			AdminFrameGlobal->m_listCtrlProblems->DeleteItem(i);
		}
	}
	
	return;
}

AdminFrame::AdminFrame(wxFrame *frame)
    : AdminGUI(frame), m_timer(this)
{
	char localaddr[20];
	int ip1, ip2, ip3, ip4;
	FILE *ipFile;
	
	isProblemInfoEnable = false;
	AdminFrameGlobal = this;
	InitAccountList();
	InitProblemList();
	m_timeleft = 0;
	
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
}

AdminFrame::~AdminFrame()
{
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

void AdminFrame::ProblemInfoEnable(bool enable){
	if(isProblemInfoEnable == enable)
		return;
	
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

void AdminFrame::OnButtonClickChangePassword( wxCommandEvent& event ){
	changePassDialog = new ChangePassDialog(this);
	changePassDialog->ShowModal();
	
	return;
}

void AdminFrame::OnButtonClickLogout( wxCommandEvent& event ){
	long tmp;
	tmp = m_listCtrlAdmin->InsertItem(0, _("Test A"));
	m_listCtrlAdmin->SetItem(tmp, 1, _("Test B"));
	
	tmp = m_listCtrlAdmin->InsertItem(1, _("Test C"));
	m_listCtrlAdmin->SetItem(tmp, 1, _("Test D"));
	
	tmp = m_listCtrlJudge->InsertItem(0, _("Test E"));
	m_listCtrlJudge->SetItem(tmp, 1, _("Test F"));
	
	tmp = m_listCtrlJudge->InsertItem(1, _("Test G"));
	m_listCtrlJudge->SetItem(tmp, 1, _("Test H"));
	
	tmp = m_listCtrlJudge->InsertItem(2, _("Test I"));
	m_listCtrlJudge->SetItem(tmp, 1, _("Test J"));
	
	tmp = m_listCtrlTeam->InsertItem(0, _("Test K"));
	m_listCtrlTeam->SetItem(tmp, 1, _("Test L"));
	
	tmp = m_listCtrlTeam->InsertItem(1, _("Test M"));
	m_listCtrlTeam->SetItem(tmp, 1, _("Test N"));
	
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
	if(adminproto_contest_start(server_ip) < 0)
		wxMessageBox(_("Cannot start contest!"));
	
	return;
}

void AdminFrame::OnButtonClickStop( wxCommandEvent& event ){
	if(adminproto_contest_start(server_ip) < 0)
		wxMessageBox(_("Cannot stop contest!"));
	
	return;
}

void AdminFrame::OnListItemDeselectedProblem( wxListEvent& event ){
	ProblemInfoEnable(false);
	m_selectedProblem = -1;
}

void AdminFrame::OnListItemSelectedProblem( wxListEvent& event ){
	ProblemInfoEnable(true);
	m_selectedProblem = event.GetIndex();
}

void AdminFrame::OnButtonClickAddProblem( wxCommandEvent& event ){
	int i;
	for(i = 0 ; i < m_listCtrlProblems->GetItemCount() ; i++)
		m_listCtrlProblems->SetItemState(i, !wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
	m_selectedProblem = -1;
	m_textCtrlProblemName->Clear();
	m_filePickerProblemFile->SetPath(wxEmptyString);
	m_spinCtrlTimeLimitVal->SetValue(3000);
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

void AdminFrame::OnButtonClickProblemApply( wxCommandEvent& event ){
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
		
		wchar_t *name = m_textCtrlProblemName->GetLabel().wchar_str();
		wchar_t *p_path = m_filePickerProblemFile->GetPath().wchar_str();
		unsigned int time_limit = m_spinCtrlTimeLimitVal->GetValue();
		wchar_t *i_path = m_filePickerProblemInputData->GetPath().wchar_str();
		wchar_t *o_path = m_filePickerProblemOutputData->GetPath().wchar_str();
		
		adminproto_problem_add(server_ip, id, name, time_limit, p_path, i_path, o_path);
	}
	else{
		//edit
	}
	
	return;
}

void AdminFrame::OnTimerEvent(wxTimerEvent &event){
	m_timeleft--;
	m_staticTextTime->SetLabel(wxString::Format(_("%d:%02d:%02d"), m_timeleft / 60 / 60, (m_timeleft / 60) % 60, m_timeleft % 60));
	if(m_timeleft <= 0){
		//contest end
		m_timer.Stop();
	}
	
	return;
}