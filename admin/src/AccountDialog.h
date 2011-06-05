#ifndef _ACCOUNTDIALOG_H_
#define _ACCOUNTDIALOG_H_

#include "gui.h"

class AccountDialog: public AccountGUI{
	private:
		bool newAccount;
		void OnClose( wxCloseEvent& event );
		void OnButtonClickOK( wxCommandEvent& event );
		void OnButtonClickCancel( wxCommandEvent& event );

	public:
		AccountDialog(wxWindow *parent, wxString name = wxEmptyString, unsigned int type = 0, unsigned int account_id = 0);
		~AccountDialog();
};

#endif