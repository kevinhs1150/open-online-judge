#include "JudgeMain.h"
#include "JudgeShowClar.h"
extern "C"
{
    #include "judgeproto.h"
}

JudgeShowClarFrame::JudgeShowClarFrame(wxFrame *frame)
    : ShowClarGUI(frame)
{
}

JudgeShowClarFrame::~JudgeShowClarFrame()
{
}

void JudgeShowClarFrame::setClarQA( wchar_t *clarmsg, wchar_t *result_string )
{
	wxString showTextCtrl;
	
	showTextCtrl.Printf(wxT("%s"),clarmsg);
	m_textCtrlQuestion->SetValue(showTextCtrl);
	showTextCtrl.Printf(wxT("%s"),result_string);
	m_textCtrlAnswer->SetValue(showTextCtrl);
}

void JudgeShowClarFrame::OnButtonClickClose( wxCommandEvent& event )
{
	Destroy();
}