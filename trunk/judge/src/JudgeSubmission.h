#ifndef _JUDGESUBMISSION_H_
#define _JUDGESUBMISSION_H_

#include <wx/wx.h>
#include "JudgeApp.h"
#include "gui.h"
#include "judgeproto.h"

#define SUCCESS 0
#define SUCCESS_WITH_WARNING 1
#define COMPLIE_ERROR -1
#define OUTPUT_ERROR -2
#define TYPE_ERROR -3
#define FILE_OPEN_ERROR -4
#define OUTPUT_OPEN_ERROR -5
#define TIME_OUT -6

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
