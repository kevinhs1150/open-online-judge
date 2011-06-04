CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(oojproto)

INCLUDE_DIRECTORIES("include")
INCLUDE_DIRECTORIES("../libpthread")

SET(srcs src/adminproto.c src/judgeproto.c src/protointernal.c src/protointernal_listen.c src/serverproto.c src/teamproto.c)
ADD_LIBRARY(oojproto STATIC ${srcs})