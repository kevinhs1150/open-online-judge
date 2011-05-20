CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Server)
INCLUDE_DIRECTORIES("../gui")

SET(srcs src/ServerApp.cpp src/ServerMain.cpp ../gui/gui.cpp)
ADD_EXECUTABLE(Server WIN32 ${srcs})
TARGET_LINK_LIBRARIES(Server ${wxWidgets_LIBRARIES})
