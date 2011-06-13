#ifndef _ADMINMAIN_H_
#define _ADMINMAIN_H_

#include <wx/wx.h>
#include <vector>
#include "AdminApp.h"
#include "gui.h"

using namespace std;

struct Problem{
	unsigned int problem_id;
	wxString name;
	unsigned int time_limit;
	wxString path_description;
	wxString path_input;
	wxString path_answer;
};

struct Clar{
	unsigned int clar_id;
	unsigned int account_id;
	wxString name;
	int private_byte;
	wxString clar_msg;
	wxString result_msg;
};

int wxCALLBACK ListCompareFunction(long item1, long item2, long WXUNUSED(sortData));

class AdminFrame: public AdminGUI
{
    public:
        AdminFrame(wxFrame *frame);
        ~AdminFrame();
		
		bool isLogin;
		unsigned int m_timeleft;
		vector<Problem> list_problem;
		vector<Clar> list_clar;
		wxMutex m_mutexAccount;
		wxMutex m_mutexProblem;
		wxMutex m_mutexClar;
		wxMutex m_mutexScoreboard;
		
		wxTimer m_timer;
		
    private:
		bool isProblemInfoEnable;
		int m_selectedProblem;
		int m_selectedClar;
	
		//void OnClose( wxCloseEvent& event );
		void InitAccountList();
		void InitProblemList();
		void InitClarList();
		void InitSBList();
		void ProblemInfoEnable(bool enable);
		void ClarEnable(bool enable);
		
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
		void OnListItemDeselectedClar( wxListEvent& event );
		void OnListItemSelectedClar( wxListEvent& event );
		
		void OnTimerEvent(wxTimerEvent &event);
		void TimerCall(wxCommandEvent &event);
		DECLARE_EVENT_TABLE()
		
};


#endif // _ADMINMAIN_H_
