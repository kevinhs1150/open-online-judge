#ifndef _TEAMMAIN_H_
#define _TEAMMAIN_H_

#include <wx/wx.h>
#include "TeamApp.h"
#include "gui.h"
#include "LoginDialog.h"
extern "C"
{
    #include "teamproto.h"
}


class TeamFrame: public TeamGUI
{
    public:
        TeamFrame(wxFrame *frame);
        ~TeamFrame();
        void OnButtonClickLogout( wxCommandEvent& event );
		void OnButtonClickDownload( wxCommandEvent& event );
		void OnButtonClickBrowse( wxCommandEvent& event );
		void OnButtonClickTest( wxCommandEvent& event );
		void OnButtonClickSubmit( wxCommandEvent& event );
		void OnButtonClickAsk( wxCommandEvent& event );

    private:

};


#endif // _TEAMMAIN_H_
