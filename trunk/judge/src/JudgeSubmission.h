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
		
		void setRunProblemID(unsigned int run_id,unsigned int problem_id, wchar_t *coding_language);

    private:
		unsigned int run_id;
		unsigned int problem_id;
		wchar_t *coding_language
		int result;

		void OnButtonClickShowInput( wxCommandEvent& event );
		void OnButtonClickShowSource( wxCommandEvent& event );
		void OnButtonClickRun( wxCommandEvent& event );
		void OnButtonClickStop( wxCommandEvent& event );
		void OnButtonClickShowOutput( wxCommandEvent& event );
		void OnButtonClickJudge( wxCommandEvent& event );
		void OnButtonClickCancel( wxCommandEvent& event );
		void setResultChoice();
		void showStatus();
};

#endif // _JUDGESUBMISSION_H_
