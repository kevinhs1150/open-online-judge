#include "AdminApp.h"
#include "AdminMain.h"

IMPLEMENT_APP(AdminApp);

bool AdminApp::OnInit()
{
	LoginDialog* loginDialog = new LoginDialog(NULL);
	loginDialog->Show();
	//delete loginDialog;
    //AdminFrame* frame = new AdminFrame(0L);
    //frame->Show();

    return true;
}
