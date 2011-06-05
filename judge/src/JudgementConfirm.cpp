#include "JudgeMain.h"
extern "C"
{
    #include "judgeproto.h"
}

JudgementConfirmFrame::JudgementConfirmFrame(wxFrame *frame)
    : JudgementConfirmGUI(frame)
{
}

JudgementConfirmFrame::~JudgementConfirmFrame()
{
}

void JudgementConfirmFrame::OnButtonClickYes( wxCommandEvent& event );
{
	EndModal(0);
}

void JudgementConfirmFrame::OnButtonClickNo( wxCommandEvent& event );
{
	EndModal(-1);
}

void JudgementConfirmFrame::setJudgementVal(int result)
{
	wxString judgementVal;
	
	if(result == YES){
		judgementVal.Printf(wxT("Yes."));
	}
	else if(result == COMPLIE_ERROR){
		judgementVal.Printf(wxT("Complie error."));
	}
	else if(result == WRONG_ANSWER){
		judgementVal.Printf(wxT("Wrong answer."));
	}
	else if(result == TIME_LIMIT_EXCEED){
		judgementVal.Printf(wxT("Time-limit exceed."));
	}
	else{
		judgementVal.Printf(wxT("Other error."));
	}
	
	m_staticTextJudgementVal->SetLabel(judgementVal);
}