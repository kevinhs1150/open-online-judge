CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Team)
INCLUDE_DIRECTORIES("../gui")
INCLUDE_DIRECTORIES("../liboojproto/include")
INCLUDE_DIRECTORIES("../libpthread")

SET(srcs src/TeamApp.cpp src/TeamMain.cpp src/LoginDialog.cpp)
ADD_EXECUTABLE(Team WIN32 ${srcs})
TARGET_LINK_LIBRARIES(Team ${wxWidgets_LIBRARIES} gui oojproto ${CMAKE_BINARY_DIR}/lib/pthreadGC2.a iconv)
