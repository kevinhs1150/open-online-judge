#include "judge_tool.h"

#include <wx/process.h>
#include <wx/filefn.h>

extern "C"
{
    #include "judgeproto.h"
}

int wxOoj_ProcessExists(long pid);
#define wxOOJ_NOTEXIST		0
#define wxOOJ_EXISTS		1
#define wxOOJ_ACCESS_DENIED	2
#define wxOOJ_UNEXPECTED	3

int compile(wchar_t file_name[], wchar_t type[])
{
    FILE *fptr1;
	FILE *crPtr;  /* compile result file pointer */
	wxString cCompile;

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
    unsigned int i;
	long pid;
	FILE *rrPtr;  /* run result file pointer */

	wxProcess *pExecute = new wxProcess;
	pExecute->Redirect();
    pid = wxExecute(wxT("out.exe"), wxEXEC_ASYNC, pExecute);

    for(i = 0;i < time_limit;i++){
        Sleep(1);
        if(wxOoj_ProcessExists(pid) == wxOOJ_NOTEXIST){
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

    if(wxOoj_ProcessExists(pid) == wxOOJ_EXISTS){
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
				/* get next character */
                o = getc(fptr2);
                a = getc(fptr1);
				
				/* compare character */
                if(o != EOF && a != EOF){
                    if(o != a){
						/* character compare different, return */
						fclose( fptr1 );
						fclose( fptr2 );
                        return -1;
                    }
                }
                else if((o != EOF && a == EOF) || (o == EOF && a != EOF)){
					/* EOF encountered, return */
					fclose( fptr1 );
					fclose( fptr2 );
                    return -1;
                }
                else{
                    break;
                }
            }
            fclose(fptr2);
        }
        else{
			fclose( fptr1 );
            return -1;
        }
        fclose(fptr1);
    }
    else{
        return -1;
    }

    return 0;
}

/* This wxOoj_ProcessExists() function is taken from wxWidgets trunk.
 * wxWidgets/trunk/src/msw/utils.cpp, revision 65493, line 705
 * At the time of this revision, there's a bug in wxKill() in both stable and development build of wxWidgets,
 * which causes wxProcess::Exists() to always return 1.
 * So we took the wxKill() function from trunk and modify it by ourself to adapt our application. */
#ifdef _WIN32
int wxOoj_ProcessExists(long pid)
{
	int krc = wxOOJ_EXISTS;	// this one becomes return code

    // get the process handle to operate on
    DWORD dwAccess = PROCESS_QUERY_INFORMATION | SYNCHRONIZE;

    HANDLE hProcess = OpenProcess(dwAccess, FALSE, (DWORD)pid);
    if ( hProcess == NULL )
	{
		// recognize wxKILL_ACCESS_DENIED as special because this doesn't
		// mean that the process doesn't exist and this is important for
		// wxProcess::Exists()
		krc = GetLastError() == ERROR_ACCESS_DENIED
							? wxOOJ_ACCESS_DENIED
							: wxOOJ_NOTEXIST;
        return krc;
	}

	switch ( WaitForSingleObject(hProcess, 0) )
	{
		case WAIT_OBJECT_0:
			// Process terminated: normally this indicates that we
			// successfully killed it but when testing for the process
			// existence, this means failure.
			krc = wxOOJ_NOTEXIST;
			break;

		default:
		case WAIT_FAILED:
			krc = wxOOJ_UNEXPECTED;

		case WAIT_TIMEOUT:
			// Process didn't terminate: normally this is a failure but not
			// when we're just testing for its existence.
			break;
	}

	CloseHandle( hProcess );

    return krc;
}
/* For Linux build, return to normal wxProcess::Exists(). */
#else
int wxOoj_ProcessExists(long pid)
{
	return wxProcess::Exists(pid);
}
#endif