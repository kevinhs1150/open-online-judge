#include "TeamApp.h"
#include "TeamMain.h"

IMPLEMENT_APP(TeamApp);

bool TeamApp::OnInit()
{
    TeamFrame* frame = new TeamFrame(0L);
    frame->Show();

    return true;
}
