#include "JudgeMain.h"

struct run_problem_id{
    unsigned int run_id;
    unsigned int problem_id;
    struct run_problem_id *next;
} run_request_id;

JudgeLoginFrame* loginframe;
run_request_id *pptr = NULL;

void login_confirm( int confirm_code, unsigned int account_id );
void logout_confirm( int confirm_code );
void run_request( unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code );
void run_request_dlfin( unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code );


JudgeFrame::JudgeFrame(wxFrame *frame)
    : JudgeGUI(frame)
{
    judgeproto_cbreg_login_confirm( login_confirm );
    judgeproto_cbreg_logout_confirm( logout_confirm );
    judgeproto_cbreg_run_request(run_request);
    judgeproto_cbreg_run_request_dlfin(run_request_dlfin);

    loginframe = new JudgeLoginFrame(0L)
    if(loginframe->ShowModal() == -1){
        Destroy();
    }
}


JudgeFrame::~JudgeFrame()
{
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

void run_request( unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t **path_code )
{
    char filename[50];

    if(!strcmp(coding_language,"c"))
    {
        strcpy(filename, run_id);
        strcat(filename, ".c");
        strcpy(path_code, filename);
    }
    else if(!strcmp(coding_language,"c++"))
    {
        strcpy(filename, run_id);
        strcat(filename, ".cpp");
        strcpy(path_code, filename);
    }

    run_request_id temp_id = new run_request_id;
    temp_id.run_id = run_id;
    temp_id.problem_id = problem_id;
    pptr->next = temp_id;
    *pptr = temp_id->next;
}

void run_request_dlfin( unsigned int run_id, unsigned int problem_id, wchar_t *coding_language, wchar_t *path_code )
{

}
