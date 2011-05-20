Suggest using CMake to target "build" directory for building files.

1.安裝cmake
2.在build資料夾下指令:" cmake -G "MinGW Makefiles" .. "，即可產生MinGW用的Makefile
3.若要重新產生Makefile，清空build資料夾後重新使用cmake