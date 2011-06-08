#ifndef _JUDGECOMPARE_H_
#define _JUDGECOMPARE_H_

#include <wx/wx.h>
#include "JudgeApp.h"
#include "gui.h"

class JudgeCompareFrame: public JudgeCompareGUI
{
    public:
        JudgeCompareFrame(wxFrame *frame);
        ~JudgeCompareFrame();
		
		void setProblemID(unsigned int problem_id);

    private:
		void OnButtonClickClose( wxCommandEvent& event );
};

#endif // _JUDGECOMPARE_H_
