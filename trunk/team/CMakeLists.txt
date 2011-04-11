CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Client)

# modify your wxWidgets directory HERE!
SET(wxWidgets_ROOT_DIR C:/wxMSW-2.8.12)

FIND_PACKAGE(wxWidgets COMPONENTS core base REQUIRED)

INCLUDE(${wxWidgets_USE_FILE})
SET(srcs src/ClientApp.cpp src/ClientGUI.cpp src/ClientMain.cpp)
ADD_EXECUTABLE(Client WIN32 ${srcs})
TARGET_LINK_LIBRARIES(Client ${wxWidgets_LIBRARIES})
