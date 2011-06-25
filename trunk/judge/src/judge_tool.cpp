#include "judge_tool.h"

#include <wx/process.h>
#include <wx/filefn.h>

extern "C"
{
    #include "judgeproto.h"
}

int compile(wchar_t file_name[], wchar_t type[])
{
    FILE *fptr1;
    wchar_t call[100];
    char call_mb[100];
    size_t call_mbsize;

	/* check if out.exe exist */
    fptr1=fopen("out.exe","r");
    if(fptr1 != NULL){
        fclose(fptr1);
        wxRemoveFile(wxT("out.exe"));
    }
	
	/* check if ans.txt exist */
	fptr1=fopen("ans.txt","r");
    if(fptr1 != NULL){
        fclose(fptr1);
        wxRemoveFile(wxT("ans.txt"));
    }
	
	/* test source file existence */
    fptr1=fopen_sp(file_name,L"r");
    if(fptr1!=NULL)
    {
		if(!(wcscmp(type, L"c"))){
			wcscpy(call, L"gcc -o out.exe ");
			wcscat(call, file_name);
			wcscat(call, L" > output.txt 2>&1");

			call_mbsize = wcstombs( NULL, call, 0 ) + 1;
			wcstombs( call_mb, call, call_mbsize );
			
			system(call_mb);
			return(complie_result());
		}
		else if(!(wcscmp(type, L"c++"))){
			wcscpy(call, L"g++ -o out.exe ");
			wcscat(call, file_name);
			wcscat(call, L" > output.txt 2>&1");

			call_mbsize = wcstombs( NULL, call, 0 ) + 1;
			wcstombs( call_mb, call, call_mbsize );
			
			system(call_mb);
			return(complie_result());
		}
		else{
			return TYPE_ERROR;
		}
        fclose(fptr1);
    }
    else{
        return FILE_OPEN_ERROR;
    }
}

int complie_result(){
    FILE *fptr1,*fptr2;
    char ch;
    int result = SUCCESS;

    fptr1 = fopen("out.exe","r");
    fptr2 = fopen("output.txt","r");
    if(fptr1 != NULL){
        if(fptr2 != NULL)
        {
            while((ch = getc(fptr2))!= EOF){
                result = SUCCESS_WITH_WARNING;
            }
            fclose(fptr2);
        }
        else{
            result = OUTPUT_OPEN_ERROR;
        }
        fclose(fptr1);
    }
    else{
        result = COMPLIE_ERROR;
    }

    return(result);
}

int time(unsigned int time_limit){
    int i;
	long pid;
	wxProcess *wxP = NULL;

    pid = wxExecute(wxT("executive.exe"),wxEXEC_NOHIDE,wxP);

    for(i = 0;i < time_limit;i++){
        Sleep(1);
        if(wxProcess::Exists(pid) == true){
            break;
        }
    }

    if(wxProcess::Exists(pid) == false){
        system("taskkill /F /IM out.exe");
        return -1;
    }

    return 0;
}

int judge(unsigned int problem_id){
    FILE *fptr1,*fptr2;
    char a;
    char o;
	char problem_ans[50];

    sprintf(problem_ans, "problem/%u_answer.txt", problem_id);

    fptr1 = fopen(problem_ans,"r");
	/*TODO: fix me*/
	Sleep(1000);
    fptr2 = fopen("ans.txt","r");
    if(fptr1 != NULL){
        if(fptr2 != NULL)
        {
            while(1){
                o = getc(fptr2);
                a = getc(fptr1);
                if(o != EOF && a != EOF){
                    if(o != a){
                        return -1;
                    }
                }
                else if((o != EOF && a == EOF) || (o == EOF && a != EOF)){
                    return -1;
                }
                else{
                    break;
                }
            }
            fclose(fptr2);
        }
        else{
            return -1;
        }
        fclose(fptr1);
    }
    else{
        return -1;
    }

    return 0;
}