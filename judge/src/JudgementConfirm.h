#ifndef _JUDGEMENTCONFIRM_H_
#define _JUDGEMENTCONFIRM_H_

#include <wx/wx.h>
#include "JudgeApp.h"
#include "gui.h"
#include "judgeproto.h"

class JudgementConfirmFrame: public JudgementConfirmGUI
{
    public:
        JudgementConfirmFrame(wxFrame *frame);
        ~JudgementConfirmFrame();

    private:
		void OnButtonClickYes( wxCommandEvent& event );
		void OnButtonClickNo( wxCommandEvent& event );
};


#endif // _JUDGEMENTCONFIRM_H_
