#ifndef _LOGINDIALOG_H_
#define _LOGINDIALOG_H_

#include "gui.h"

class LoginDialog: public LoginGUI{
	public:
		LoginDialog(wxWindow *parent);
		~LoginDialog();
};

#endif