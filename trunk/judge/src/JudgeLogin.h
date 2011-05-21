#ifndef _JUDGEMAIN_H_
#define _JUDGEMAIN_H_

#include <wx/wx.h>
#include "JudgeApp.h"
#include "gui.h"
#include "judgeproto.h"

class JudgeLoginFrame: public LoginGUI
{
    public:
        JudgeLoginFrame(wxFrame *frame);
        ~JudgeLoginFrame();

        void cleanPassword();

    private:
        void OnTextEnterPassword( wxCommandEvent& event );
		void OnButtonClickLogin( wxCommandEvent& event );
		void OnButtonClickExit( wxCommandEvent& event );

		void login();
};


#endif // _JUDGEMAIN_H_
