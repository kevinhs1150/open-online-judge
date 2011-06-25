#ifndef JUDGE_TOOL_H_
#define JUDGE_TOOL_H_

#define SUCCESS 0
#define SUCCESS_WITH_WARNING 1
#define COMPILE_ERROR -1
#define OUTPUT_ERROR -2
#define TYPE_ERROR -3
#define FILE_OPEN_ERROR -4
#define OUTPUT_OPEN_ERROR -5
#define TIME_OUT -6

int compile(wchar_t file_name[], wchar_t type[]);
int compile_result();
int execute(unsigned int time_limit);
int judge(unsigned int problem_id);

#endif