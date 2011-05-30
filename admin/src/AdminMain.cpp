#include "AdminMain.h"

AdminFrame::AdminFrame(wxFrame *frame)
    : AdminGUI(frame)
{
	LoginDialog* loginDialog = new LoginDialog(NULL);
	if(loginDialog->ShowModal() == 0)
		isLogin = false;
	else
		isLogin = true;
	loginDialog->Destroy();
}

AdminFrame::~AdminFrame()
{
}
