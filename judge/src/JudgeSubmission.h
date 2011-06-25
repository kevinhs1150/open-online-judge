#ifndef _JUDGESUBMISSION_H_
#define _JUDGESUBMISSION_H_

#include <wx/wx.h>
#include "JudgeApp.h"
#include "gui.h"

#define YES 0
#define COMPLIE_ERROR -1
#define WRONG_ANSWER -2
#define TIME_LIMIT_EXCEED -3
#define RUN_TIME_ERROR -4

class JudgeSubmissionFrame: public JudgeSubmissionGUI
{
    public:
        JudgeSubmissionFrame(wxFrame *frame);
        ~JudgeSubmissionFrame();
		
		void IP_set();
		void showStatus();
		void setRunProblemID(unsigned int run_id,unsigned int problem_id, wchar_t *coding_language, wchar_t *problem_name, unsigned int time_limit);
		unsigned int getTimeLimit();

    private:
		unsigned int run_id;
		unsigned int problem_id;
		wchar_t *coding_language;
		wchar_t *problem_name;
		unsigned int time_limit;
		int result;
		char IP[20];

		void OnButtonClickShowInput( wxCommandEvent& event );
		void OnButtonClickShowSource( wxCommandEvent& event );
		void OnButtonClickRun( wxCommandEvent& event );
		void OnButtonClickStop( wxCommandEvent& event );
		void OnButtonClickShowOutput( wxCommandEvent& event );
		void OnButtonClickJudge( wxCommandEvent& event );
		void OnButtonClickCancel( wxCommandEvent& event );
		void setResultChoice();
};

#endif // _JUDGESUBMISSION_H_
