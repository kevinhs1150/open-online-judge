CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Judge)
INCLUDE_DIRECTORIES("../gui")
INCLUDE_DIRECTORIES("../liboojproto/include")

SET(srcs src/JudgeApp.cpp src/JudgeMain.cpp)
ADD_EXECUTABLE(Judge WIN32 ${srcs})
TARGET_LINK_LIBRARIES(Judge ${wxWidgets_LIBRARIES} gui oojproto ${CMAKE_BINARY_DIR}/lib/pthreadGC2.a)
