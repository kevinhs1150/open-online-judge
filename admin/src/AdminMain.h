#ifndef _ADMINMAIN_H_
#define _ADMINMAIN_H_

#include <wx/wx.h>
#include <vector>
#include "AdminApp.h"
#include "gui.h"

using namespace std;

struct Problem{
	unsigned int id;
	wxString name;
	unsigned int time_limit;
	wxString path_description;
	wxString path_input;
	wxString path_answer;
};

class AdminFrame: public AdminGUI
{
    public:
        AdminFrame(wxFrame *frame);
        ~AdminFrame();
		
		bool isLogin;
		unsigned int m_timeleft;
		
    private:
		bool isProblemInfoEnable;
		int m_selectedProblem;
		wxTimer m_timer;
		vector<Problem> temp_problem;
		vector<Problem> list_problem;
	
		//void OnClose( wxCloseEvent& event );
		void InitAccountList();
		void InitProblemList();
		void ProblemInfoEnable(bool enable);
		
		void OnButtonClickChangePassword( wxCommandEvent& event );
		void OnButtonClickLogout( wxCommandEvent& event );
		void OnListItemActivatedAdmin( wxListEvent& event );
		void OnListItemSelectedAdmin( wxListEvent& event );
		void OnListItemActivatedJudge( wxListEvent& event );
		void OnListItemSelectedJudge( wxListEvent& event );
		void OnListItemActivatedTeam( wxListEvent& event );
		void OnListItemSelectedTeam( wxListEvent& event );
		void OnButtonClickNewAccount( wxCommandEvent& event );
		void OnButtonClickDeleteAccount( wxCommandEvent& event );
		void OnButtonClickManualTimeSet( wxCommandEvent& event );
		void OnButtonClickStart( wxCommandEvent& event );
		void OnButtonClickStop( wxCommandEvent& event );
		void OnListItemDeselectedProblem( wxListEvent& event );
		void OnListItemSelectedProblem( wxListEvent& event );
		void OnButtonClickAddProblem( wxCommandEvent& event );
		void OnButtonClickDelProblem( wxCommandEvent& event );
		void OnButtonClickProblemApply( wxCommandEvent& event );
		
		void OnTimerEvent(wxTimerEvent &event);
		DECLARE_EVENT_TABLE()
};


#endif // _ADMINMAIN_H_
