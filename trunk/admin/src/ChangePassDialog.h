#ifndef _CHANGEPASSDIALOG_H_
#define _CHANGEPASSDIALOG_H_

#include "gui.h"

class ChangePassDialog: public ChangePassGUI{
	private:
		void OnClose( wxCloseEvent& event );
		void OnButtonClickOK( wxCommandEvent& event );
		void OnButtonClickCancel( wxCommandEvent& event );

	public:
		ChangePassDialog(wxWindow *parent);
		~ChangePassDialog();
		void ChangeSuccess();
};

#endif