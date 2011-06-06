#include "JudgeMain.h"
extern "C"
{
    #include "judgeproto.h"
}

JudgeShowClarFrame::JudgeShowClarFrame(wxFrame *frame)
    : JudgeShowClarGUI(frame)
{
}

JudgeShowClarFrame::~JudgeShowClarFrame()
{
}

void JudgeShowClarFrame::setClarQA( wchar_t *clarmsg, wchar_t *result_string )
{
	wxSting showTextCtrl;
	
	showTextCtrl.Printf("%s",clarmsg);
	m_textCtrlQuestion->SetValue(showTextCtrl);
	showTextCtrl.Printf("%s",result_string);
	m_textCtrlAnswer->SetValue(showTextCtrl);
}

void JudgeShowClarFrame::OnButtonClickClose( wxCommandEvent& event )
{
	Destroy();
}