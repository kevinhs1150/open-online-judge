#include "ServerApp.h"
#include "ServerMain.h"

IMPLEMENT_APP(ServerApp);

bool ServerApp::OnInit()
{
    ServerFrame* frame = new ServerFrame(0L);
    frame->Show();

    return true;
}
