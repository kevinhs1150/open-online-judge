#ifndef _NEWACCOUNTDIALOG_H_
#define _NEWACCOUNTDIALOG_H_

#include "gui.h"

class NewAccountDialog: public NewAccountGUI{
	private:
		void OnClose( wxCloseEvent& event );
		void OnButtonClickOK( wxCommandEvent& event );
		void OnButtonClickCancel( wxCommandEvent& event );

	public:
		NewAccountDialog(wxWindow *parent);
		~NewAccountDialog();
};

#endif