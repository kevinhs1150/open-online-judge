#include "../include/ClientMain.h"

BEGIN_EVENT_TABLE(ClientFrame, wxFrame)
    EVT_CLOSE(ClientFrame::OnClose)
END_EVENT_TABLE()

ClientFrame::ClientFrame(wxFrame *frame)
    : ClientGUI(frame)
{
}


ClientFrame::~ClientFrame()
{
}

void ClientFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}
