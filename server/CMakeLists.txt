CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Server)
INCLUDE_DIRECTORIES("../gui")
INCLUDE_DIRECTORIES("../liboojproto/include")

SET(srcs src/ServerApp.cpp src/ServerMain.cpp src/sqlite3.c)
ADD_EXECUTABLE(Server WIN32 ${srcs})
TARGET_LINK_LIBRARIES(Server ${wxWidgets_LIBRARIES} guioojproto ${CMAKE_BINARY_DIR}/lib/pthreadGC2.a)
