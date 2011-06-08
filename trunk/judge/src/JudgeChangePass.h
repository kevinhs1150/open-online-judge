#ifndef _JUDGECHANGEPASS_H_
#define _JUDGECHANGEPASS_H_

#include <wx/wx.h>
#include "JudgeApp.h"
#include "gui.h"

class JudgeChangePassFrame: public ChangePassGUI
{
    public:
        JudgeChangePassFrame(wxFrame *frame);
        ~JudgeChangePassFrame();
		
		void set_account_id(unsigned int account_id);
		void IP_set();
		void textCtrlClear();

    private:
		unsigned int account_id;
		char IP[20];
		
		void OnButtonClickOK( wxCommandEvent& event );
		void OnButtonClickCancel( wxCommandEvent& event );
};

#endif // _JUDGECHANGEPASS_H_