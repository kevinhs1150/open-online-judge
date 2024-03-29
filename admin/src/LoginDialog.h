#ifndef _LOGINDIALOG_H_
#define _LOGINDIALOG_H_

#include "gui.h"

class LoginDialog: public LoginGUI{
	private:
		void OnClose( wxCloseEvent& event );
		void OnButtonClickLogin( wxCommandEvent& event );
		void OnButtonClickExit( wxCommandEvent& event );

	public:
		LoginDialog(wxWindow *parent);
		~LoginDialog();
		
		void LoginSuccess();
};

#endif