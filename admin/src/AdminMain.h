#ifndef _ADMINMAIN_H_
#define _ADMINMAIN_H_

#include <wx/wx.h>
#include "AdminApp.h"
#include "gui.h"

class AdminFrame: public AdminGUI
{
    public:
        AdminFrame(wxFrame *frame);
        ~AdminFrame();
		
		bool isLogin;
	
    private:
		bool isProblemInfoEnable;
	
		//void OnClose( wxCloseEvent& event );
		void InitAccountList();
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
		void OnButtonClickStart( wxCommandEvent& event );
		void OnButtonClickStop( wxCommandEvent& event );
		void OnListItemDeselectedProblem( wxListEvent& event );
		void OnListItemSelectedProblem( wxListEvent& event );
		void OnButtonClickAddProblem( wxCommandEvent& event );
		void OnButtonClickDelProblem( wxCommandEvent& event );

};


#endif // _ADMINMAIN_H_
