#ifndef _SERVERMAIN_H_
#define _SERVERMAIN_H_

#include <wx/wx.h>
#include "ServerApp.h"
#include "gui.h"

class ServerFrame: public ServerGUI
{
    public:
        ServerFrame(wxFrame *frame);
        ~ServerFrame();
    private:
};


#endif // _SERVERMAIN_H_
