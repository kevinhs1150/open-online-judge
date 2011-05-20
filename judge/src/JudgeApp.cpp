#include "JudgeApp.h"
#include "JudgeMain.h"

IMPLEMENT_APP(JudgeApp);

bool JudgeApp::OnInit()
{
    JudgeFrame* frame = new JudgeFrame(0L);
    frame->Show();

    return true;
}
