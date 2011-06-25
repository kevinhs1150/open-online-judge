#include "judge_tool.h"

#include <wx/process.h>
#include <wx/filefn.h>

extern "C"
{
    #include "judgeproto.h"
}

bool wxcExists(int pid);

int compile(wchar_t file_name[], wchar_t type[])
{
    FILE *fptr1;
	FILE *crPtr;  /* compile result file pointer */
    wchar_t call[100];
	wxString cCompile;
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
		fclose( fptr1 );

		/* piece up compilation command string */
		if( wcscmp(type, L"c") == 0 ){
			cCompile << wxT("gcc -Wall -o out.exe ") << file_name;
		}
		else if( wcscmp(type, L"c++") == 0 ){
			cCompile << wxT("gcc -Wall -o out.exe ") << file_name;
		}
		else{
			return TYPE_ERROR;
		}

		/* start compilation */
		crPtr = fopen( "output.txt", "w" );

		wxProcess *pCompile = new wxProcess;
		pCompile->Redirect();
		/* specify sync flag which blocks wxExecute() until command execution is finished */
		wxExecute( cCompile, wxEXEC_SYNC, pCompile );

		wxInputStream *pStdout = pCompile->GetInputStream();
		wxInputStream *pStderr = pCompile->GetErrorStream();

		/* read output and error respectively from redirection stream */
		while( pCompile->IsErrorAvailable() )
		{
			char c = pStderr->GetC();
			
			if( c == 13 )  /* possibly a newline being interpreted as 13-10, check in depth */
			{
				char c2 = pStderr->GetC();
				
				if( c2 == 10 )
					putc('\n', crPtr );
				else
				{
					putc( c, crPtr );
					putc( c2, crPtr );
				}
			}
			else
				putc( c, crPtr );
		}
		while( pCompile->IsInputAvailable() )
		{
			char c = pStdout->GetC();
			
			if( c == 13 )  /* possibly a newline being interpreted as 13-10, check in depth */
			{
				char c2 = pStdout->GetC();
				
				if( c2 == 10 )
					putc('\n', crPtr );
				else
				{
					putc( c, crPtr );
					putc( c2, crPtr );
				}
			}
			else
				putc( c, crPtr );
		}

		/* end compilation */

        fclose( crPtr );

		return compile_result();
    }
    else{
        return FILE_OPEN_ERROR;
    }
}

int compile_result(){
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
        result = COMPILE_ERROR;
    }

    return(result);
}

int execute(unsigned int time_limit){
    int i;
	long pid;
	FILE *rrPtr;  /* run result file pointer */

	wxProcess *pExecute = new wxProcess;
	pExecute->Redirect();
    pid = wxExecute(wxT("out.exe"), wxEXEC_ASYNC, pExecute);

    for(i = 0;i < time_limit;i++){
        Sleep(1);
        if(wxProcess::Exists(pid) == false){
            break;
        }
    }

	rrPtr = fopen( "ans.txt", "w" );

	/* stderr will be ignored here */
	wxInputStream *pStdout = pExecute->GetInputStream();

	while( pExecute->IsInputAvailable() )
	{
		char c = pStdout->GetC();
		
		if( c == 13 )  /* possibly a newline being interpreted as 13-10, check in depth */
		{
			char c2 = pStdout->GetC();
			
			if( c2 == 10 )
				putc('\n', rrPtr );
			else
			{
				putc( c, rrPtr );
				putc( c2, rrPtr );
			}
		}
		else
			putc( c, rrPtr );
	}

	fclose( rrPtr );

    if(wxProcess::Exists(pid) == true){
		/* signal process kill */
		wxProcess::Kill( pid, wxSIGKILL );
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
