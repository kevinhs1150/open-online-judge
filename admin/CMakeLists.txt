CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Admin)
INCLUDE_DIRECTORIES("../gui")
INCLUDE_DIRECTORIES("../liboojproto/include")
#LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib)

SET(srcs src/AdminApp.cpp src/AdminMain.cpp src/LoginDialog.cpp)
ADD_EXECUTABLE(Admin WIN32 ${srcs})
TARGET_LINK_LIBRARIES(Admin ${wxWidgets_LIBRARIES} gui oojproto ${CMAKE_BINARY_DIR}/lib/pthreadGC2.a)

CONFIGURE_FILE(../libpthread/pthreadGC2.dll ${CMAKE_BINARY_DIR}/bin/pthreadGC2.dll COPYONLY)
CONFIGURE_FILE(../libpthread/libpthreadGC2.a ${CMAKE_BINARY_DIR}/lib/pthreadGC2.a COPYONLY)
