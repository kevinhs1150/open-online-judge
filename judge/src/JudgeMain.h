#ifndef _JUDGEMAIN_H_
#define _JUDGEMAIN_H_

#include <wx/wx.h>
#include "JudgeApp.h"
#include "gui.h"
#include "judgeproto.h"

class JudgeFrame: public JudgeGUI
{
    public:
        JudgeFrame(wxFrame *frame);
        ~JudgeFrame();
    private:
};


#endif // _JUDGEMAIN_H_
