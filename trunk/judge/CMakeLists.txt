CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Judge)
INCLUDE_DIRECTORIES("../gui")

# modify your wxWidgets directory HERE!
SET(wxWidgets_ROOT_DIR C:/wxMSW-2.8.12)

FIND_PACKAGE(wxWidgets COMPONENTS core base REQUIRED)
INCLUDE(${wxWidgets_USE_FILE})

SET(srcs src/JudgeApp.cpp src/JudgeMain.cpp ../gui/gui.cpp)
ADD_EXECUTABLE(Judge WIN32 ${srcs})
TARGET_LINK_LIBRARIES(Judge ${wxWidgets_LIBRARIES})
