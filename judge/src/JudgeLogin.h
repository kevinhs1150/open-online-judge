#ifndef _JUDGELOGIN_H_
#define _JUDGELOGIN_H_

#include <wx/wx.h>
#include "JudgeApp.h"
#include "gui.h"

class JudgeLoginFrame: public LoginGUI
{
    public:
        JudgeLoginFrame(wxFrame *frame);
        ~JudgeLoginFrame();

        void cleanPassword();
		wxString getAccount();

    private:
		void OnClose( wxCloseEvent& event );
        void OnTextEnterPassword( wxCommandEvent& event );
		void OnButtonClickLogin( wxCommandEvent& event );
		void OnButtonClickExit( wxCommandEvent& event );

		void login();
		wxString account;
};


#endif // _JUDGELOGIN_H_
