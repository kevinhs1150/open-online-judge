#include "JudgeMain.h"
#include "JudgeCompare.h"
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

void JudgeCompareFrame::OnButtonClickClose( wxCommandEvent& event )
{
	Destroy();
}

void JudgeCompareFrame::setProblemID(unsigned int problem_id)
{
	char officialOutputFile[50];
	FILE *fptr1,*fptr2;
    char buf;
	wxString officialOutput = wxEmptyString;
	wxString userOutput = wxEmptyString;

    sprintf(officialOutputFile, "problem/%u_answer.txt", problem_id);

    fptr1 = fopen(officialOutputFile,"r");
    fptr2 = fopen("ans.txt","r");
    if(fptr1 != NULL){
        if(fptr2 != NULL)
        {
			while(1){
				fread(&buf, sizeof(char), 1, fptr2);
				if(feof(fptr2))
					break;
				userOutput << (wxChar)buf;
			}
            fclose(fptr2);
        }
        else{
			userOutput.Printf(wxT("File opening failure."));
        }
		
        while(1){
				fread(&buf, sizeof(char), 1, fptr1);
				if(feof(fptr1))
					break;
				officialOutput << (wxChar)buf;
			}
        fclose(fptr1);
    }
    else{
		officialOutput.Printf(wxT("File opening failure."));
    }
	
	m_textCtrlOfficialOutput->SetValue(officialOutput);
	m_textCtrlUserOutput->SetValue(userOutput);
}