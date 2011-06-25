#ifndef _JUDGEMAIN_H_
#define _JUDGEMAIN_H_

#include <wx/wx.h>
#include "JudgeApp.h"
#include "gui.h"

#define STOP  0
#define START 1

class JudgeFrame: public JudgeGUI
{
    public:
		unsigned int m_timeleft;
		wxTimer m_timer;
		wxMutex m_mutexRunRequest;
		wxMutex m_mutexProblem;
		wxMutex m_mutexClarRequest;
		
        JudgeFrame(wxFrame *frame);
        ~JudgeFrame();
		void account_id_set(unsigned int account_id);
		void account_set(wxString account);
		void setPtoblemFilterChoice(unsigned int problem_id, wchar_t *problem_name);
		void deleteProblemFilterChoice(unsigned int problem_count);
		void setUnJudgeNum(unsigned int unJudgeNum);
		void setRunListColumn();
		void setClarListColumn();
        void start();
        void stop();
        void IP_set();
        char *IP_get();

    private:
		unsigned int account_id;
        unsigned int state;
        char IP[16];
		
		void OnButtonClickChangePassword( wxCommandEvent& event );
		void OnButtonClickLogout( wxCommandEvent& event );
		void OnChoiceFilter( wxCommandEvent& event );
		void OnCheckBoxAutoJudge( wxCommandEvent& event );
		void OnListItemActivatedRuns( wxListEvent& event );
		void OnListItemActivatedClar( wxListEvent& event );
		
		void OnTimerEvent(wxTimerEvent &event);
		void TimerCall(wxCommandEvent &event);
		void ShowSubmissionDialog(wxCommandEvent &event);
		void AutoJudge(wxCommandEvent &event);
		DECLARE_EVENT_TABLE()
};


#endif // _JUDGEMAIN_H_
