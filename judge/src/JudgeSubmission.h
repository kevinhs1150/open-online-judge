#ifndef _JUDGESUBMISSION_H_
#define _JUDGESUBMISSION_H_

#include <wx/wx.h>
#include "JudgeApp.h"
#include "gui.h"
#include "judgeproto.h"

class JudgeSubmissionFrame: public JudgeSubmissionGUI
{
    public:
        JudgeSubmissionFrame(wxFrame *frame);
        ~JudgeSubmissionFrame();

    private:
		void OnButtonClickShowInput( wxCommandEvent& event );
		void OnButtonClickShowSource( wxCommandEvent& event );
		void OnButtonClickRun( wxCommandEvent& event );
		void OnButtonClickStop( wxCommandEvent& event );
		void OnButtonClickShowOutput( wxCommandEvent& event );
		void OnButtonClickJudge( wxCommandEvent& event );
		void OnButtonClickCancel( wxCommandEvent& event );
};

#endif // _JUDGESUBMISSION_H_
