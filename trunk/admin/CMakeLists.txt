CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Admin)
INCLUDE_DIRECTORIES("../gui")

SET(srcs src/AdminApp.cpp src/AdminMain.cpp src/LoginDialog.cpp ../gui/gui.cpp)
ADD_EXECUTABLE(Admin WIN32 ${srcs})
TARGET_LINK_LIBRARIES(Admin ${wxWidgets_LIBRARIES})
