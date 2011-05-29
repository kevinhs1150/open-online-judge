#include "JudgeMain.h"

struct run_problem_id{
    unsigned int run_id;
    unsigned int problem_id;
    wchar_t *coding_language;
    struct run_problem_id *next;
} run_request_id;

JudgeLoginFrame* loginframe;
JudgeFrame *mainFrame = NULL;
run_request_id *pptr = NULL;

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
run_request_id *search(unsigned int run_id);
int compile(char [], char []);
int complie_result(void);
int judge(unsigned int problem_id);
int time(void);

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

    loginframe = new JudgeLoginFrame(0L)
    if(loginframe->ShowModal() == -1){
        Destroy();
    }

    mainFrame = this;
}


JudgeFrame::~JudgeFrame()
{
}

JudgeFrame::timer(unsigned int hours, unsigned int minutes, unsigned int seconds)
{
    timer_hours = hours;
    timer_minutes = minutes;
    timer_seconds = seconds;
}

JudgeFrame::start()
{
    state = START;
}

JudgeFrame::stop()
{
    state = STOP;
}

void OnButtonClickLogout( wxCommandEvent& event )
{
    judgeproto_cbreg_logout_confirm( logout_confirm );
}

void login_confirm( int confirm_code, unsigned int account_id )
{
    if( confirm_code == LOGIN_VALID )
        loginframe->EndModal(0);
    else{
        wxMessageBox("Login Error.\nPromble: account NOTEXIST or password WRONG.","Login Error",wxOK|wxICON_EXCLAMATION);
        loginframe->cleanPassword();
    }
}

void logout_confirm( int confirm_code )
{
    if(confirm_code == LOGOUT_OK){
        Destroy();
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

    if(!strcmp(coding_language,"c"))
    {
        sprintf(filename, "%u.c", run_id);
    }
    else if(!strcmp(coding_language,"c++"))
    {
        sprintf(filename, "%u.cpp", run_id);
    }
    else{
        return;
    }

    /**TODO: new memory for *path_code**/
    *path_code = new wchar_t [ strlen(filename)+1 ];
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
    *path_description = new wchar_t [ strlen(path)+1 ];
    *path_input = new wchar_t [ strlen(path)+1 ];
    *path_answer = new wchar_t [ strlen(path)+1 ];

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
    char file_name[50];
    int errtyp;

    if(/**auto judge**/){
        if(success == TAKE_SUCCESS){
            /**TODO:show message**/
            run_request_id *proptr = search(run_id);
            sprintf(file_name, "%s", run_id);
            strcpy(type, proptr->coding_language);
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
        }
    }
    else{
        if(success == TAKE_SUCCESS){
            run_request_id *proptr = search(run_id);
            sprintf(file_name, "%s", run_id);
            strcpy(type, proptr->coding_language);
            errtyp = compile(file_name, type);
            }
    }

}

void clar_request( unsigned int clar_id, int private_byte, wchar_t *clarmsg )
{

}

void id_insert(unsigned int run_id, unsigned int problem_id, wchar_t *coding_language)
{
    run_request_id *currentPtr = pptr;

    run_request_id *temp_id = new run_request_id;
    temp_id.run_id = run_id;
    temp_id.problem_id = problem_id;
    temp_id.coding_language = coding_language;
	temp_id.next = NULL;

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
}

run_request_id *search(unsigned int run_id)
{
    run_request_id *tptr = pptr;

    if(tptr->run_id == run_id){
        return tptr->coding_language;
    }

    while( tptr->next != NULL ){
        if(tptr->run_id == run_id){
            return tptr;
            break;
        }
        tptr = tptr->next;
    }
}
int compile(char file_name[], char type[])
{
    FILE *fptr1;
    char call[100];

    fptr1=fopen("out.exe","r");
    if(fptr1 != NULL){
        fclose(fptr1);
        DeleteFile("out.exe");
    }

    fptr1=fopen(file_name,"r");
    if(fptr1!=NULL)
    {
        if(!(strcmp(type, "c"))){
            strcpy(call, "gcc -o out.exe ");
            strcat(call, file_name);
            strcat(call, " > output.txt 2>&1");
            system(call);
            return(complie_result());

        }
        else if(!(strcmp(type, "c++"))){
            strcpy(call, "g++ -o out.exe ");
            strcat(call, file_name);
            strcat(call, " > output.txt 2>&1");
            system(call);
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
                printf("%c",ch);
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
                printf("%c",ch);
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

    CreateProcess( NULL, "executive.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
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
