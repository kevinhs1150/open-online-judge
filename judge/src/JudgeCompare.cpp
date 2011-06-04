#include "JudgeMain.h"
extern "C"
{
    #include "judgeproto.h"
}

JudgeCompareFrame::JudgeCompareFrame(wxFrame *frame)
    : JudgeCompareGUI(frame)
{
}

JudgeCompareFrame::~JudgeCompareFrame()
{
}

void JudgeCompareFrame::OnButtonClickClose( wxCommandEvent& event );
{
	Destroy();
}

void JudgeCompareFrame::setRunProblemID(unsigned int run_id, unsigned int problem_id)
{
	this->run_id = run_id;
	this->problem_id = problem_id;
	
	/**Εγ₯ά**/
}