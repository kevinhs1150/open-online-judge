#ifndef _JUDGECOMPARE_H_
#define _JUDGECOMPARE_H_

#include <wx/wx.h>
#include "JudgeApp.h"
#include "gui.h"
#include "judgeproto.h"

class JudgeCompareFrame: public JudgeCompareGUI
{
    public:
        JudgeCompareFrame(wxFrame *frame);
        ~JudgeCompareFrame();
		
		void setRunProblemID(unsigned int run_id, unsigned int problem_id);

    private:
		unsigned int run_id;
		unsigned int problem_id;
		void OnButtonClickClose( wxCommandEvent& event );
};

#endif // _JUDGECOMPARE_H_
