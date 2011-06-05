#include "JudgeMain.h"
extern "C"
{
    #include "judgeproto.h"
}

JudgeSubmissionFrame::JudgeSubmissionFrame(wxFrame *frame)
    : JudgeSubmissionGUI(frame)
{
	setResultChoice();
	showStatus();
}

JudgeSubmissionFrame::~JudgeSubmissionFrame()
{
}

void JudgeSubmissionFrame::setRunProblemID(unsigned int run_id,unsigned int problem_id, wchar_t *coding_language)
{
	wxString submissionNO;
	wxString problemNO;
	
	this->run_id = run_id;
	this->problem_id = problem_id;
	this->coding_language = coding_language;
	
	submissionNO.Printf(wxT("%u"), run_id);
	problemNO.Printf(wxT("%u"), problem_id);
	
	m_staticTextSubmissionValue->SetLabel(submissionNO);
	m_staticTextProblemNumberValue->SetLabel(problemNO);
}

void JudgeSubmissionFrame::OnButtonClickShowInput( wxCommandEvent& event )
{
}

void JudgeSubmissionFrame::OnButtonClickShowSource( wxCommandEvent& event )
{
}

void JudgeSubmissionFrame::OnButtonClickRun( wxCommandEvent& event )
{
}

void JudgeSubmissionFrame::OnButtonClickStop( wxCommandEvent& event )
{
}

void JudgeSubmissionFrame::OnButtonClickShowOutput( wxCommandEvent& event )
{
	Compareframe = new JudgeCompareFrame(0L);
	Compareframe->setProblemID(this->problem_id);
}

void JudgeSubmissionFrame::OnButtonClickJudge( wxCommandEvent& event )
{
	Confirmframe = new JudgementConfirmFrame(0L);
	Confirmframe->setJudgementVal(this->result);
	if(Confirmframe->ShowModal() == 0){
        Destroy();
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
	choice.Printf(wxT("other error"));
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
}