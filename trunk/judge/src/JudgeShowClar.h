#ifndef _JUDGESHOWCLAR_H_
#define _JUDGESHOWCLAR_H_

#include <wx/wx.h>
#include "JudgeApp.h"
#include "gui.h"
#include "judgeproto.h"

class JudgeShowClarFrame: public ShowClarGUI
{
    public:
        JudgeShowClarFrame(wxFrame *frame);
        ~JudgeShowClarFrame();
		
		void setClarQA( wchar_t *clarmsg, wchar_t *result_string);

    private:
		void OnButtonClickClose( wxCommandEvent& event );
};

#endif // _JUDGESHOWCLAR_H_
