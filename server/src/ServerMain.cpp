#include "ServerMain.h"

/*
BEGIN_EVENT_TABLE(ServerFrame, wxFrame)
    EVT_CLOSE(ServerFrame::OnClose)
END_EVENT_TABLE()
*/

ServerFrame::ServerFrame(wxFrame *frame)
    : ServerGUI(frame)
{
}


ServerFrame::~ServerFrame()
{
}

/*
void ServerFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}
*/
