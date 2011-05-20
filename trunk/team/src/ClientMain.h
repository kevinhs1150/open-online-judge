#ifndef CLIENTMAIN_H_
#define CLIENTMAIN_H_

#include <wx/wx.h>
#include "ClientApp.h"
#include "gui.h"

class ClientFrame: public TeamGUI
{
    public:
        ClientFrame(wxFrame *frame);
        ~ClientFrame();
    private:
        void OnClose(wxCloseEvent& event);
        DECLARE_EVENT_TABLE()
};


#endif // CLIENTMAIN_H_
