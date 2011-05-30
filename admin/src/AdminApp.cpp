#include "AdminApp.h"
#include "AdminMain.h"

IMPLEMENT_APP(AdminApp);

bool AdminApp::OnInit()
{
	AdminFrame* adminMain = new AdminFrame(NULL);
	if(adminMain->isLogin)
		adminMain->Show();
	else
		adminMain->Destroy();
	
    return true;
}
