#ifndef _JUDGEMAIN_H_
#define _JUDGEMAIN_H_

#include <wx/wx.h>
#include "JudgeApp.h"
#include "gui.h"

#define STOP  0
#define START 1

#define SUCCESS 0
#define SUCCESS_WITH_WARNING 1
#define COMPLIE_ERROR -1
#define OUTPUT_ERROR -2
#define TYPE_ERROR -3
#define FILE_OPEN_ERROR -4
#define OUTPUT_OPEN_ERROR -5
#define TIME_OUT -6

class JudgeFrame: public JudgeGUI
{
    public:
		unsigned int m_timeleft;
		wxTimer m_timer;
		
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
		void OnCheckBoxAutoJudge( wxCommandEvent& event );
		void OnListItemActivatedRuns( wxListEvent& event );
		void OnListItemActivatedClar( wxListEvent& event );
		
		void OnTimerEvent(wxTimerEvent &event);
		DECLARE_EVENT_TABLE()
};


#endif // _JUDGEMAIN_H_
