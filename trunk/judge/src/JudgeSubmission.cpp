#include "JudgeMain.h"
#include "JudgeCompare.h"
#include "JudgementConfirm.h"

extern "C"
{
    #include "judgeproto.h"
}

JudgeCompareFrame *CompareFrame;
JudgementConfirmFrame *ConfirmFrame;
JudgeSubmissionFrame *submissionFrame;

int compile(wchar_t file_name[], wchar_t type[]);
int complie_result();
int time();
int judge(unsigned int problem_id);

JudgeSubmissionFrame::JudgeSubmissionFrame(wxFrame *frame)
    : JudgeSubmissionGUI(frame)
{
	setResultChoice();
	showStatus();
}

JudgeSubmissionFrame::~JudgeSubmissionFrame()
{
}

void JudgeSubmissionFrame::IP_set()
{
    FILE *fptr1;

    fptr1=fopen("config.txt","r");
    fscanf (fptr1, "%s", IP);
    fclose(fptr1);
}

void JudgeSubmissionFrame::setRunProblemID(unsigned int run_id,unsigned int problem_id, wchar_t *coding_language, wchar_t *problem_name, unsigned int time_limit)
{
	wxString submissionNO;
	wxString problemNO;
	
	this->run_id = run_id;
	this->problem_id = problem_id;
	this->coding_language = coding_language;
	this->problem_name = problem_name;
	this->time_limit = time_limit;
	
	submissionNO.Printf(wxT("%u), run_id);
	problemNO.Printf(wxT("%u %s"), problem_id, problem_name);
	
	m_staticTextSubmissionValue->SetLabel(submissionNO);
	m_staticTextProblemNumberValue->SetLabel(problemNO);
}

unsigned int JudgeSubmissionFrame::getTimeLimit()
{
	return this->time_limit;
}

void JudgeSubmissionFrame::OnButtonClickShowInput( wxCommandEvent& event ) /**SKIP**/
{
}

void JudgeSubmissionFrame::OnButtonClickShowSource( wxCommandEvent& event )/**SKIP**/
{
}

void JudgeSubmissionFrame::OnButtonClickRun( wxCommandEvent& event )
{
	wchar_t file_name[50];
    wchar_t type[20];
	int errtyp;
	
	swprintf(file_name, L"%u", run_id);
	wcscpy(type, this->coding_language);
	m_staticTextResult->SetLabel(wxT("Compile..."));
	errtyp = compile(file_name, type);
	if(errtyp == SUCCESS || errtyp == SUCCESS_WITH_WARNING){
		m_staticTextResult->SetLabel(wxT("File execute..."));
		if(time() == 0){
			if(judge(this->problem_id) != 0){
				errtyp = OUTPUT_ERROR;
			}
		}
		else{
			errtyp = TIME_OUT;
		}
	}
	
	if(errtyp == SUCCESS){
		m_staticTextResult->SetLabel(wxT("Compile success."));
	}
	else if(errtyp == SUCCESS_WITH_WARNING){
		m_staticTextResult->SetLabel(wxT("Compile success, but has warning."));
	}
	else if(errtyp == COMPLIE_ERROR){
		m_staticTextResult->SetLabel(wxT("Compile error."));
	}
	else if(errtyp == OUTPUT_ERROR){
		m_staticTextResult->SetLabel(wxT("Output error."));
	}
	else if(errtyp == TYPE_ERROR){
		m_staticTextResult->SetLabel(wxT("Submission file type error."));
	}
	else if(errtyp == FILE_OPEN_ERROR){
		m_staticTextResult->SetLabel(wxT("Submission file open error."));
	}
	else if(errtyp == OUTPUT_OPEN_ERROR){
		m_staticTextResult->SetLabel(wxT("Complie result file open error."));
	}
	else if(errtyp == TIME_OUT){
		m_staticTextResult->SetLabel(wxT("Execute time out."));
	}
	else{
		m_staticTextResult->SetLabel(wxT("Other unexpected error."));
	}
}

void JudgeSubmissionFrame::OnButtonClickStop( wxCommandEvent& event ) /**SKIP**/
{
}

void JudgeSubmissionFrame::OnButtonClickShowOutput( wxCommandEvent& event )
{
	Compareframe = new JudgeCompareFrame(0L);
	Compareframe->setProblemID(this->problem_id);
}

void JudgeSubmissionFrame::OnButtonClickJudge( wxCommandEvent& event )
{
	int column = m_choiceJudgement->GetSelection();
	wchar_t result_string[20];
	
	if(column == 0){
		this->result = YES;
	}
	else if(column == 1){
		this->result = COMPLIE_ERROR;
	}
	else if(cloumn == 2){
		this->result = WRONG_ANSWER;
	}
	else if(column == 3){
		this->result = TIME_LIMIT_EXCEED;
	}
	
	Confirmframe = new JudgementConfirmFrame(0L);
	Confirmframe->setJudgementVal(this->result);
	if(Confirmframe->ShowModal() == 0){
		if(this->reult == YES){
			swprintf(result_string,L"yes");
		}
		else if(this->result == COMPLIE_ERROR){
			swprintf(result_string,L"complie error");
		}
		else if(this->result == WRONG_ANSWER){
			swprintf(result_string,L"wrong answer");
		}
		else{
			swprintf(result_string,L"time-limit exceed");
		}
		if(judgeproto_judge_result(this->IP,this->run_id,result_string) != 0){
			wxMessageBox("Judgement Submission Error.\nPromble: Socket error.","Judgement Submission Error",wxOK|wxICON_EXCLAMATION);
		}
		else{
			EndModal(0);
		}
    }
}

void JudgeSubmissionFrame::OnButtonClickCancel( wxCommandEvent& event )
{
	EndModal(-1);
}

void JudgeSubmissionFrame::setResultChoice()
{
	wxString choice;
	
	choice.Printf(wxT("yes"));
	m_choiceJudgement->Append(choice);
	choice.Printf(wxT("complie error"));
	m_choiceJudgement->Append(choice);
	choice.Printf(wxT("output wrong"));
	m_choiceJudgement->Append(choice);
	choice.Printf(wxT("time-limit exceed"));
	m_choiceJudgement->Append(choice);
}

void JudgeSubmissionFrame::showStatus()
{
	wxString status;
	File *fptr1;
	char filename[50];
	
	sprintf(filename,"problem/%u_input.txt",this->problem_id);
	fptr1 = fopen(fileanme,"r");
	if(fptr1 != NULL){
		m_staticTextInputStatusValue->SetLabel(wxT("OK"));
	}
	else{
		m_staticTextInputStatusValue->SetLabel(wxT("Not Exist"));
	}
	
	if( !wcscmp(this->coding_language, L"c") )
    {
        sprintf(filename, "%u.c", run_id);
    }
    else if(!wcscmp(this->coding_language,L"c++"))
    {
        sprintf(filename, "%u.cpp", run_id);
    }
	
	fptr1 = fopen(fileanme,"r");
	if(fptr1 != NULL){
		m_staticTextSourceStatusValue->SetLabel(wxT("OK"));
	}
	else{
		m_staticTextSourceStatusValue->SetLabel(wxT("Not Exist"));
	}
	
	m_staticTextResult->SetLabel(wxT("Not start"));
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
            return TYPE_ERROR;
        }
        fclose(fptr1);
    }
    else{
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

    for(i = 0; i < (submissionFrame->getTimeLimit()) ;i++){
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
            return -1;
        }
        fclose(fptr1);
    }
    else{
        return -1;
    }

    return 0;
}