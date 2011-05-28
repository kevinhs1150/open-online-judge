#ifndef _JUDGEMAIN_H_
#define _JUDGEMAIN_H_

#include <wx/wx.h>
#include "JudgeApp.h"
#include "gui.h"
#include "judgeproto.h"

#define STOP  0
#define START 1

#define SUCCESS 0
#define SUCCESS_WITH_WARNING 1
#define COMPLIE_ERROR -1
#define OUTPUT_ERROR -2
#define TYPE_ERROR -3
#define FILE_OPEN_ERROR -4
#define OUTPUT_OPEN_ERROR -5
#define TIME_OUT -6

class JudgeFrame: public JudgeGUI
{
    public:
        JudgeFrame(wxFrame *frame);
        ~JudgeFrame();
        void timer(unsigned int hours, unsigned int minutes, unsigned int seconds);
        void start();
        void stop();

    private:
        unsigned int timer_hours;
        unsigned int timer_minutes;
        unsigned int timer_seconds;
        unsigned int state;
};


#endif // _JUDGEMAIN_H_
