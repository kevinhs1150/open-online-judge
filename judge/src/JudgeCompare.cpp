#include "JudgeMain.h"
extern "C"
{
    #include "judgeproto.h"
}

JudgeCompareFrame::JudgeCompareFrame(wxFrame *frame)
    : JudgeCompareGUI(frame)
{
}

JudgeCompareFrame::~JudgeCompareFrame()
{
}

void JudgeCompareFrame::OnButtonClickClose( wxCommandEvent& event );
{
	Destroy();
}

void JudgeCompareFrame::setProblemID(unsigned int problem_id)
{
	char officialOutputFile[50];
	FILE *fptr1,*fptr2;
    wxChar ch;
	wxString officialOutput;
	wxString userOutput;

    sprintf(officialOutputFile, "problem/%s_answer.txt", problem_id);

    fptr1 = fopen(officialOutputFile,"r");
    fptr2 = fopen("ans.txt","r");
    if(fptr1 != NULL){
        if(fptr2 != NULL)
        {
			ch = get(fptr2);
			userOutput = ch;
            while(ch = getc(fptr2)!=EOF){
				userOutput << ch;
            }
            fclose(fptr2);
        }
        else{
			userOutput("File opening failure.",wxConvUTF8);
        }
		
		ch = get(fptr1);
		officialOutput = ch;
        while(ch = getc(fptr1) != EOF){
			officialOutput << ch;
		}
        fclose(fptr1);
    }
    else{
		officialOutput("File opening failure.",wxConvUTF8);
    }
	
	m_textCtrlOfficialOutput->SetValue(officialOutput);
	m_textCtrlUserOutput->SetValue(userOutput);
}