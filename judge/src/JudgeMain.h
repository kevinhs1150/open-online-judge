#ifndef _JUDGEMAIN_H_
#define _JUDGEMAIN_H_

#include <wx/wx.h>
#include "JudgeApp.h"
#include "gui.h"

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
		void account_id_set(unsigned int account_id);
        void timer(unsigned int hours, unsigned int minutes, unsigned int seconds);
		void set_problem_choice();
        void start();
        void stop();
        void IP_set();
        char *IP_get();

    private:
		void OnButtonClickLogout( wxCommandEvent& event );
		unsigned int account_id;
        unsigned int timer_hours;
        unsigned int timer_minutes;
        unsigned int timer_seconds;
        unsigned int state;
        char *IP;
};


#endif // _JUDGEMAIN_H_
