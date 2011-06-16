#ifndef _JUDGEMENTCONFIRM_H_
#define _JUDGEMENTCONFIRM_H_

#include <wx/wx.h>
#include "JudgeApp.h"
#include "gui.h"

#define YES 0
#define COMPLIE_ERROR -1
#define WRONG_ANSWER -2
#define TIME_LIMIT_EXCEED -3
#define RUN_TIME_ERROR -4

class JudgementConfirmFrame: public JudgementConfirmGUI
{
    public:
        JudgementConfirmFrame(wxFrame *frame);
        ~JudgementConfirmFrame();
		
		void setJudgementVal(int result);

    private:
		void OnButtonClickYes( wxCommandEvent& event );
		void OnButtonClickNo( wxCommandEvent& event );
};


#endif // _JUDGEMENTCONFIRM_H_
