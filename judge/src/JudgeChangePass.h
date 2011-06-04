#ifndef _JUDGECHANGEPASS_H_
#define _JUDGECHANGEPASS_H_

#include <wx/wx.h>
#include "JudgeApp.h"
#include "gui.h"
#include "judgeproto.h"

class JudgeChangePassFrame: public ChangePassGUI
{
    public:
        JudgeChangePassFrame(wxFrame *frame);
        ~JudgeChangePassFrame();

    private:
		void OnButtonClickOK( wxCommandEvent& event );
		void OnButtonClickCancel( wxCommandEvent& event );
};

#endif // _JUDGECHANGEPASS_H_