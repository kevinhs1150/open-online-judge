#ifndef _TEAMMAIN_H_
#define _TEAMMAIN_H_

#include <wx/wx.h>
#include "TeamApp.h"
#include "gui.h"
extern "C"
{
    #include "teamproto.h"
}


class TeamFrame: public TeamGUI
{
    public:
        TeamFrame(wxFrame *frame);
        ~TeamFrame();

    private:

};


#endif // _TEAMMAIN_H_
