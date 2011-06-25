#include "JudgeMain.h"
#include "JudgeSubmission.h"
#include "JudgeCompare.h"
#include "JudgementConfirm.h"

#include "judge_tool.h"

extern "C"
{
    #include "judgeproto.h"
}

JudgeCompareFrame *compareFrame;
JudgementConfirmFrame *confirmFrame;
extern JudgeSubmissionFrame *submissionFrame;

JudgeSubmissionFrame::JudgeSubmissionFrame(wxFrame *frame)
    : JudgeSubmissionGUI(frame)
{
	IP_set();
	setResultChoice();
	
	m_buttonShowInputData->Enable(false);
	m_buttonShowSource->Enable(false);
	m_buttonStop->Enable(false);
}

JudgeSubmissionFrame::~JudgeSubmissionFrame()
{
}

void JudgeSubmissionFrame::IP_set()
{
    FILE *fptr1;

    fptr1=fopen("ip.txt","r");
    fscanf (fptr1, "%s", IP);
    fclose(fptr1);
}

void JudgeSubmissionFrame::setRunProblemID(unsigned int run_id,unsigned int problem_id, wchar_t *coding_language, wchar_t *problem_name, unsigned int time_limit)
{
	wxString submissionNO;
	wxString problemNO;
	
	this->run_id = run_id;
	this->problem_id = problem_id;
	this->coding_language = (wchar_t *) malloc( (wcslen(coding_language) +1 ) * sizeof(wchar_t));
    wcscpy(this->coding_language,coding_language);
	this->problem_name = (wchar_t *) malloc( (wcslen(problem_name) +1 ) * sizeof(wchar_t));
    wcscpy(this->problem_name,problem_name);
	this->time_limit = time_limit;
	
	submissionNO.Printf(wxT("%u"), run_id);
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
	
	wcscpy(type, this->coding_language);
	
	if(!(wcscmp(type, L"c"))){
		wsprintf(file_name,L"%u.c",this->run_id);
	}
	else if(!(wcscmp(type, L"c++"))){
		wsprintf(file_name,L"%u.cpp",this->run_id);
	}
	else{
		errtyp = TYPE_ERROR;
	}
	
	m_staticTextRunStatus->SetLabel(wxT("Compile..."));
	errtyp = compile(file_name, type);
	if(errtyp == SUCCESS || errtyp == SUCCESS_WITH_WARNING){
		m_staticTextRunStatus->SetLabel(wxT("File execute..."));
		if(execute( getTimeLimit() ) == 0){
			if(judge(this->problem_id) != 0){
				errtyp = OUTPUT_ERROR;
				m_staticTextRunStatus->SetLabel(wxT("Wrong answer."));
			}
		}
		else{
			errtyp = TIME_OUT;
		}
	}
	
	if(errtyp == SUCCESS){
		m_staticTextRunStatus->SetLabel(wxT("Compile success."));
	}
	else if(errtyp == SUCCESS_WITH_WARNING){
		m_staticTextRunStatus->SetLabel(wxT("Compile success, but has warning."));
	}
	else if(errtyp == COMPILE_ERROR){
		m_staticTextRunStatus->SetLabel(wxT("Compile error."));
	}
	else if(errtyp == OUTPUT_ERROR){
		m_staticTextRunStatus->SetLabel(wxT("Output error."));
	}
	else if(errtyp == TYPE_ERROR){
		m_staticTextRunStatus->SetLabel(wxT("Submission file type error."));
	}
	else if(errtyp == FILE_OPEN_ERROR){
		m_staticTextRunStatus->SetLabel(wxT("Submission file open error."));
	}
	else if(errtyp == OUTPUT_OPEN_ERROR){
		m_staticTextRunStatus->SetLabel(wxT("Compile result file open error."));
	}
	else if(errtyp == TIME_OUT){
		m_staticTextRunStatus->SetLabel(wxT("Execute time out."));
	}
	else{
		m_staticTextRunStatus->SetLabel(wxT("Other unexpected error."));
	}
}

void JudgeSubmissionFrame::OnButtonClickStop( wxCommandEvent& event ) /**SKIP**/
{
}

void JudgeSubmissionFrame::OnButtonClickShowOutput( wxCommandEvent& event )
{
	compareFrame = new JudgeCompareFrame(0L);
	compareFrame->setProblemID(this->problem_id);
	compareFrame->Show();
}

void JudgeSubmissionFrame::OnButtonClickJudge( wxCommandEvent& event )
{
	int column = m_choiceJudgement->GetSelection();
	wchar_t result_string[20];
	
	if(column == 0){
		this->result = YES;
	}
	else if(column == 1){
		this->result = COMPILE_ERROR;
	}
	else if(column == 2){
		this->result = WRONG_ANSWER;
	}
	else if(column == 3){
		this->result = TIME_LIMIT_EXCEED;
	}
	else if(column == 4){
		this->result = RUN_TIME_ERROR;
	}
	
	confirmFrame = new JudgementConfirmFrame(0L);
	confirmFrame->setJudgementVal(this->result);
	if(confirmFrame->ShowModal() == 0){
		if(this->result == YES){
			swprintf(result_string,L"yes");
		}
		else if(this->result == COMPILE_ERROR){
			swprintf(result_string,L"compile error");
		}
		else if(this->result == WRONG_ANSWER){
			swprintf(result_string,L"wrong answer");
		}
		else if(this->result == TIME_LIMIT_EXCEED){
			swprintf(result_string,L"time limit exceed");
		}
		else if(this->result == RUN_TIME_ERROR){
			swprintf(result_string,L"runtime error");
		}
		else{
			swprintf(result_string,L"YOU SHALL NOT PASS!!!!"); //this should never occur??
		}
		
		if(judgeproto_judge_result(this->IP,this->run_id,result_string) != 0){
			wxMessageBox(wxT("Judgement Submission Error.\nPromble: Socket error."),wxT("Judgement Submission Error"),wxOK|wxICON_EXCLAMATION);
		}
		else{
			EndModal(0);
		}
    }
	confirmFrame->Destroy();
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
	choice.Printf(wxT("compile error"));
	m_choiceJudgement->Append(choice);
	choice.Printf(wxT("wrong answer"));
	m_choiceJudgement->Append(choice);
	choice.Printf(wxT("time-limit exceed"));
	m_choiceJudgement->Append(choice);
	choice.Printf(wxT("run-time error"));
	m_choiceJudgement->Append(choice);
}

void JudgeSubmissionFrame::showStatus()
{
	wxString status;
	FILE *fptr1;
	char filename[50];
	
	sprintf(filename,"problem/%u_input.txt",this->problem_id);
	fptr1 = fopen(filename,"r");
	if(fptr1 != NULL){
		m_staticTextInputStatusValue->SetLabel(wxT("OK"));
	}
	else{
		m_buttonRun->Enable(false);
		m_buttonShowOutput->Enable(false);
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
	
	fptr1 = fopen(filename,"r");
	if(fptr1 != NULL){
		m_staticTextSourceStatusValue->SetLabel(wxT("OK"));
	}
	else{
		m_staticTextSourceStatusValue->SetLabel(wxT("Not Exist"));
		m_buttonRun->Enable(false);
		m_buttonShowOutput->Enable(false);
	}
	
	m_staticTextRunStatus->SetLabel(wxT("Not start"));
}
