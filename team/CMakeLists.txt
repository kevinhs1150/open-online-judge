CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Team)
INCLUDE_DIRECTORIES("../gui")

# modify your wxWidgets directory HERE!
SET(wxWidgets_ROOT_DIR C:/wxMSW-2.8.12)

FIND_PACKAGE(wxWidgets COMPONENTS core base REQUIRED)
INCLUDE(${wxWidgets_USE_FILE})

SET(srcs src/ClientApp.cpp src/ClientMain.cpp ../gui/gui.cpp)
ADD_EXECUTABLE(Team WIN32 ${srcs})
TARGET_LINK_LIBRARIES(Team ${wxWidgets_LIBRARIES})
