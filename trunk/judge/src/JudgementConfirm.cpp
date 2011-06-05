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
		judgementVal("Yes.",wxConvUTF8);
	}
	else if(result == COMPLIE_ERROR){
		judgementVal("Complie error.",wxConvUTF8);
	}
	else if(result == WRONG_ANSWER){
		judgementVal("Wrong answer.",wxConvUTF8);
	}
	else if(result == TIME_LIMIT_EXCEED){
		judgementVal("Time-limit exceed.",wxConvUTF8);
	}
	else{
		judgementVal("Other error.",wxConvUTF8);
	}
	
	m_staticTextJudgementVal->SetLabel(judgementVal);
}