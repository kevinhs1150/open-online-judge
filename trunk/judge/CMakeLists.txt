CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Judge)
INCLUDE_DIRECTORIES("../gui")
INCLUDE_DIRECTORIES("../liboojproto/include")
INCLUDE_DIRECTORIES("../libpthread")

SET(srcs src/JudgeApp.cpp src/JudgeMain.cpp src/JudgeChangePass.cpp src/JudgeCompare.cpp src/JudgeLogin.cpp src/JudgementConfirm.cpp src/JudgeShowClar.cpp src/JudgeSubmission.cpp)
ADD_EXECUTABLE(Judge WIN32 ${srcs})
TARGET_LINK_LIBRARIES(Judge ${wxWidgets_LIBRARIES} gui oojproto ${CMAKE_BINARY_DIR}/lib/pthreadGC2.a)
