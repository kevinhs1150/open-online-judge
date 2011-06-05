#include "JudgeMain.h"
#include "JudgeLogin.h"

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
    int private_byte;
    wchar_t *clarmsg;
    struct clar *next;
}clar_request_id;

typedef struct problem_list{
	unsigned int problem_id;
	struct problem_list *next;
} problem_all;

JudgeLoginFrame *loginframe;
JudgeFrame *mainFrame = NULL;
run_request_id *pptr = NULL;
clar_request_id *clar_hptr = NULL;
problem_all *problem_hptr = NULL;

void login_confirm( int confirm_code, unsigned int account_id );
void logout_confirm( int confirm_code );
void timer_set(unsigned int hours, unsigned int minutes, unsigned int seconds);
void run_request( unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code );
void run_request_dlfin( unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code );
void contest_start( void );
void contest_stop( void );
void problem_update( unsigned int problem_id, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer );
void problem_update_dlfin(unsigned int problem_id, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer );
void take_result( unsigned int run_id, int success );
void clar_request( unsigned int clar_id, int private_byte, wchar_t *clarmsg );
void id_insert(unsigned int run_id, unsigned int problem_id, wchar_t *coding_language);
void problem_insert(unsigned int problem_id);
int problem_search(unsigned int problem_id)
run_request_id *search(unsigned int run_id);
void id_delete(unsigned int run_id);
int compile(wchar_t [], wchar_t []);
int complie_result(void);
int judge(unsigned int problem_id);
int time(void);
void clar_insert(unsigned int clar_id, int private_byte, wchar_t *clarmsg);
clar_request_id *clar_search(unsigned int clar_id);
void clar_delete(unsigned int clar_id);

JudgeFrame::JudgeFrame(wxFrame *frame)
    : JudgeGUI(frame)
{
    judgeproto_cbreg_login_confirm( login_confirm );
    judgeproto_cbreg_logout_confirm( logout_confirm );
    judgeproto_cbreg_timer_set(timer_set);
    judgeproto_cbreg_run_request(run_request);
    judgeproto_cbreg_contest_start(contest_start);
    judgeproto_cbreg_contest_stop(contest_stop);
    judgeproto_cbreg_run_request_dlfin(run_request_dlfin);
    judgeproto_cbreg_problem_update(problem_update);
    judgeproto_cbreg_problem_update_dlfin(problem_update_dlfin);
    judgeproto_cbreg_take_result(take_result);
    judgeproto_cbreg_clar_request(clar_request);
    judgeproto_listen("0.0.0.0");

    loginframe = new JudgeLoginFrame(0L);
    if(loginframe->ShowModal() == -1){
        Destroy();
    }
    IP_set();

    mainFrame = this;
}

JudgeFrame::~JudgeFrame()
{
}

void JudgeFrame::OnButtonClickLogout( wxCommandEvent& event )
{
	judgeproto_logout(IP,account_id);
}

void JudgeFrame::account_id_set(unsigned int account_id)
{
	wxString id;
	
	this->account_id = account_id;
	
	id << (this->account_id);
	m_staticTextName->SetLabel(id);
}

void JudgeFrame::timer(unsigned int hours, unsigned int minutes, unsigned int seconds)
{
	wxString time;
	
    timer_hours = hours;
    timer_minutes = minutes;
    timer_seconds = seconds;
	
	time << hours << wxT(":") << minutes << wxT(":") << seconds;
	m_staticTextTime->SetLabel( time );
}

void JudgeFrame::set_problem_choice()
{
	
}

void JudgeFrame::start()
{
    state = START;
}

void JudgeFrame::stop()
{
    state = STOP;
}

void JudgeFrame::IP_set()
{
    FILE *fptr1;

    fptr1=fopen("config.txt","r");
    fscanf (fptr1, "%s", IP);
    fclose(fptr1);
}

char *JudgeFrame::IP_get()
{
    return IP;
}

void OnButtonClickLogout( wxCommandEvent& event )
{
    judgeproto_cbreg_logout_confirm( logout_confirm );
}

void login_confirm( int confirm_code, unsigned int account_id )
{
    if( confirm_code == LOGIN_VALID )
		loginframe->account_id_set(account_id);
        loginframe->EndModal(0);
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
	mainFrame->timer( hours, minutes, seconds );
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
{
    char filename[50];

    if( !wcscmp(coding_language, L"c") )
    {
        sprintf(filename, "%u.c", run_id);
    }
    else if(!wcscmp(coding_language,L"c++"))
    {
        sprintf(filename, "%u.cpp", run_id);
    }
    else{
        return;
    }

    /**TODO: new memory for *path_code**/
    *path_code = (wchar_t *) molloc( (strlen(filename)) +1) * sizeof(wchar_t);
    wsprintf(*path_code, L"%s", filename );
}

void run_request_dlfin( unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code )
{
    /**TODO: UI**/
    id_insert(run_id,problem_id,coding_language);
}

void problem_update( unsigned int problem_id, wchar_t **path_description, wchar_t **path_input, wchar_t **path_answer )
{
    /**TODO:improve mkdir**/
    system("mkdir problem");

    char path[50];

    sprintf(path, "problem/%u", problem_id);

    /**TODO: new memory for *path_code**/
    *path_description = (wchar_t *) molloc( (strlen(path))+1 ) * sizeof(wchar_t);
    *path_input = (wchar_t *)molloc( strlen(path)+1 ) * sizeof(wchar_t);
    *path_answer = (wchar_t *)molloc( strlen(path)+1 ) * sizeof(wchar_t);

    wsprintf(*path_description, L"%s.pdf", path );
    wsprintf(*path_input, L"%s_input.txt", path );
    wsprintf(*path_answer, L"%s_answer.txt", path );
}

void problem_update_dlfin(unsigned int problem_id, wchar_t *path_description, wchar_t *path_input, wchar_t *path_answer )
{
    /**TODO:problem view**/
}

void take_result( unsigned int run_id, int success )
{
    wchar_t file_name[50];
    int errtyp;
    wchar_t type[20];

    if(1/**auto judge**/){
        if(success == TAKE_SUCCESS){
            /**TODO:show message**/
            run_request_id *proptr = search(run_id);
            id_delete(run_id);
            swprintf(file_name, L"%u", run_id);
            wcscpy(type, proptr->coding_language);
            errtyp = compile(file_name, type);
            if(errtyp == SUCCESS || errtyp == SUCCESS_WITH_WARNING){
                if(time() == 0){
                    if(judge(proptr->problem_id) != 0){
                        errtyp = OUTPUT_ERROR;
                    }
                }
                else{
                    errtyp = TIME_OUT;
                }
            }
            if(errtyp == SUCCESS){
                //printf("compile success\n");
            }
            else if(errtyp == SUCCESS_WITH_WARNING){
                //printf("compile success, but has warning\n");
            }
            else if(errtyp == COMPLIE_ERROR){
                //printf("compile error\n");
            }
            else if(errtyp == OUTPUT_ERROR){
                //printf("output error\n");
            }
            else if(errtyp == TYPE_ERROR){
                //printf("type error\n");
            }
            else if(errtyp == FILE_OPEN_ERROR){
                //printf("file open error\n");
            }
            else if(errtyp == OUTPUT_OPEN_ERROR){
                //printf("output.txt open error\n");
            }
            else if(errtyp == TIME_OUT){
                //printf("time out error\n");
            }
            else{
                //printf("other unexpected error\n");
            }
        }
        else{
            id_delete(run_id);
            judgeproto_take_run(mainFrame->IP_get(),pptr->run_id);
        }
    }
    else{
        if(success == TAKE_SUCCESS){
            run_request_id *proptr = search(run_id);
            id_delete(run_id);
            swprintf(file_name, L"%s", run_id);
            wcscpy(type, proptr->coding_language);
            errtyp = compile(file_name, type);
            }
    }

}

void clar_request( unsigned int clar_id, int private_byte, wchar_t *clarmsg )
{
    clar_insert(clar_id,private_byte,clarmsg);
}

void id_insert(unsigned int run_id, unsigned int problem_id, wchar_t *coding_language)
{
    run_request_id *currentPtr = pptr;

    run_request_id *temp_id = new run_request_id;
    temp_id->run_id = run_id;
    temp_id->problem_id = problem_id;
    temp_id->coding_language = coding_language;
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
	
	if(problem_search(problem_id) == 0){
		problem_insert(problem_id);
		mainFrame->set_problem_choice();
	}
}

void problem_insert(unsigned int problem_id)
{
    problem_all *currentPtr = problem_hptr;

    problem_all *temp_id = new problem_all;
    temp_id->problem_id = problem_id;
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

int problem_search(unsigned int problem_id)
{
	problem_all *problem_all_hptr = problem_hptr;
	
	if(problem_all_hptr->problem_id == problem_id){
		return 1;
	}
	
	while(problem_all_hptr->next != NULL){
		if(problem_all_hptr->problem_id == problem_id){
			return 1;
		}
		problem_all_hptr = problem_all_hptr->next; 
	}
	return 0;
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
    run_request_id *cptr = pptr;
    run_request_id *dptr = pptr;
    run_request_id *nptr = pptr;

    if(dptr->run_id == run_id){
        pptr = pptr->next;
        delete(dptr);
        return;
    }

    while( dptr->next != NULL ){
        cptr = dptr;
        dptr = dptr->next;
        if(dptr->run_id == run_id){
            nptr = dptr->next;
            delete(dptr);
            cptr->next = nptr;
            break;
        }
    }
}

int compile(wchar_t file_name[], wchar_t type[])
{
    FILE *fptr1;
    wchar_t call[100];
    char call_mb[100];
    size_t call_mbsize;

    fptr1=fopen("out.exe","r");
    if(fptr1 != NULL){
        fclose(fptr1);
        DeleteFile(L"out.exe");
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
            return(complie_result());

        }
        else if(!(wcscmp(type, L"c++"))){
            wcscpy(call, L"g++ -o out.exe ");
            wcscat(call, file_name);
            wcscat(call, L" > output.txt 2>&1");

            call_mbsize = wcstombs( NULL, call, 0 ) + 1;
            wcstombs( call_mb, call, call_mbsize );

            system(call_mb);
            return(complie_result());
        }
        else{
            //printf("Error: type error!!!\n");
            return TYPE_ERROR;
        }
        fclose(fptr1);
    }
    else{
        //printf("Error: file opening failure!!\n");
        return FILE_OPEN_ERROR;
    }
}

int complie_result(){
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
                //printf("%c",ch);
            }
            fclose(fptr2);
        }
        else{
            //printf("Error: output.txt opening failure!!\n");
            result = OUTPUT_OPEN_ERROR;
        }
        fclose(fptr1);
    }
    else{
        result = COMPLIE_ERROR;
        if(fptr2 != NULL)
        {
            while((ch = getc(fptr2))!= EOF){
                //printf("%c",ch);
            }
            fclose(fptr2);
        }
        else{
            //printf("Error: output.txt opening failure!!\n");
            result = OUTPUT_OPEN_ERROR;
        }
    }

    return(result);
}

int time(){
    int i;

    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    HANDLE hProg;

    memset(&si,0,sizeof(si));
    si.cb= sizeof(si);

    CreateProcess( NULL, L"executive.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    hProg = pi.hProcess;

    for(i = 0;i < 5;i++){
        Sleep(1000);
        if(WaitForSingleObject(hProg,0) != WAIT_TIMEOUT){
            break;
        }
    }

    if(WaitForSingleObject(hProg,0) == WAIT_TIMEOUT){
        system("taskkill /F /IM out.exe");
        return -1;
    }

    return 0;
}

int judge(unsigned int problem_id){
    FILE *fptr1,*fptr2;
    char a;
    char o;
	char problem_ans[50];

    sprintf(problem_ans, "problem/%s_answer.txt", problem_id);

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
            //printf("Error: ans.txt opening failure\n");
            return -1;
        }
        fclose(fptr1);
    }
    else{
        //printf("Error: problem/%s_answer.txt opening failure\n");
        return -1;
    }

    return 0;
}

void clar_insert(unsigned int clar_id, int private_byte, wchar_t *clarmsg)
{
    clar_request_id *currentPtr = clar_hptr;

    clar_request_id *temp = new clar_request_id;
    temp->clar_id = clar_id;
    temp->private_byte = private_byte;
    temp->clarmsg = clarmsg;
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
}

clar_request_id *clar_search(unsigned int clar_id)
{
    clar_request_id *tptr = clar_hptr;

    if(tptr->clar_id == clar_id){
        return tptr;
    }

    while( tptr->next != NULL ){
        if(tptr->clar_id == clar_id){
            return tptr;
            break;
        }
        tptr = tptr->next;
    }
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
