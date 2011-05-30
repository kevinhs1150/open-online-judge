#ifndef _ADMINMAIN_H_
#define _ADMINMAIN_H_

#include <wx/wx.h>
#include "AdminApp.h"
#include "gui.h"

class AdminFrame: public AdminGUI
{
    public:
        AdminFrame(wxFrame *frame);
        ~AdminFrame();
		
		bool isLogin;
	
    private:

};


#endif // _ADMINMAIN_H_
