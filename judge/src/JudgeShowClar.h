#ifndef _JUDGESHOWCLAR_H_
#define _JUDGESHOWCLAR_H_

#include <wx/wx.h>
#include "JudgeApp.h"
#include "gui.h"
#include "judgeproto.h"

class JudgeShowClarFrame: public JudgeShowClarGUI
{
    public:
        JudgeShowClarFrame(wxFrame *frame);
        ~JudgeShowClarFrame();
		
		void setClarQA();

    private:
};

#endif // _JUDGESHOWCLAR_H_
