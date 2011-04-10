#include "../include/ClientApp.h"
#include "../include/ClientMain.h"

IMPLEMENT_APP(ClientApp);

bool ClientApp::OnInit()
{
    ClientFrame* frame = new ClientFrame(0L);
    frame->Show();

    return true;
}
