CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Admin)
INCLUDE_DIRECTORIES("../gui")
INCLUDE_DIRECTORIES("../liboojproto/include")
INCLUDE_DIRECTORIES("../libpthread")
INCLUDE_DIRECTORIES("../libiconv")

SET(srcs src/AdminApp.cpp src/AdminMain.cpp src/LoginDialog.cpp src/AccountDialog.cpp src/ChangePassDialog.cpp)
ADD_EXECUTABLE(Admin WIN32 ${srcs})
TARGET_LINK_LIBRARIES(Admin ${wxWidgets_LIBRARIES} gui oojproto ${CMAKE_BINARY_DIR}/lib/pthreadGC2.a ${CMAKE_BINARY_DIR}/lib/libiconv.a)

