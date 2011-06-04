#include "JudgeMain.h"
extern "C"
{
    #include "judgeproto.h"
}

JudgeSubmissionFrame::JudgeSubmissionFrame(wxFrame *frame)
    : JudgeSubmissionGUI(frame)
{
}

JudgeSubmissionFrame::~JudgeSubmissionFrame()
{
}