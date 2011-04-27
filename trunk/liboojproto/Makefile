COMMON_FILES=proto_commondefine.h protointernal.h
WIN32OBJ=win32protointernal_listen.o win32protointernal.o win32serverproto.o win32adminproto.o win32judgeproto.o win32teamproto.o
LINUXOBJ=linuxprotointernal_listen.o linuxprotointernal.o linuxserverproto.o linuxadminproto.o linuxjudgeproto.o linuxteamproto.o

liboojprotowin32.a:	${WIN32OBJ}
	ar -cvq liboojprotowin32.a ${WIN32OBJ}
	ranlib liboojprotowin32.a

win32protointernal_listen.o:	protointernal_listen.c ${COMMON_FILES}
	gcc -o win32protointernal_listen.o -c protointernal_listen.c

win32protointernal.o:			protointernal.c ${COMMON_FILES}
	gcc -o win32protointernal.o -c protointernal.c

win32serverproto.o:				serverproto.c serverproto.h ${COMMON_FILES}
	gcc -o win32serverproto.o -c serverproto.c

win32adminproto.o:				adminproto.c adminproto.h ${COMMON_FILES}
	gcc -o win32adminproto.o -c adminproto.c

win32judgeproto.o:				judgeproto.c judgeproto.h ${COMMON_FILES}
	gcc -o win32judgeproto.o -c judgeproto.c

win32teamproto.o:				teamproto.c teamproto.h ${COMMON_FILES}
	gcc -o win32teamproto.o -c teamproto.c

win32clean:
	del ${WIN32OBJ}
	del liboojprotowin32.a




liboojprotolinux.a:	${LINUXOBJ}
	ar -cvq liboojprotolinux.a ${LINUXOBJ}
	ranlib liboojprotolinux.a

linuxprotointernal_listen.o:	protointernal_listen.c ${COMMON_FILES}
	gcc -o linuxprotointernal_listen.o -c protointernal_listen.c

linuxprotointernal.o:			protointernal.c ${COMMON_FILES}
	gcc -o linuxprotointernal.o -c protointernal.c

linuxserverproto.o:				serverproto.c serverproto.h ${COMMON_FILES}
	gcc -o linuxserverproto.o -c serverproto.c

linuxadminproto.o:				adminproto.c adminproto.h ${COMMON_FILES}
	gcc -o linuxadminproto.o -c adminproto.c

linuxjudgeproto.o:				judgeproto.c judgeproto.h ${COMMON_FILES}
	gcc -o linuxjudgeproto.o -c judgeproto.c

linuxteamproto.o:				teamproto.c teamproto.h ${COMMON_FILES}
	gcc -o linuxteamproto.o -c teamproto.c

linuxclean:
	rm ${LINUXOBJ}
	rm liboojprotolinux.a




win32ts:	testsuite/server.c testsuite/client.c
	cd testsuite && gcc -o server.exe server.c -L../ -loojprotowin32 -lws2_32
	cd testsuite && gcc -o client.exe client.c -L../ -loojprotowin32 -lws2_32
	cd testsuite && gcc -o server_self_stop.exe server_self_stop.c -L../ -loojprotowin32 -lws2_32 -lpthread

win32tsclean:
	cd testsuite && del server.exe client.exe server_self_stop.exe

linuxts:	testsuite/server.c testsuite/client.c
	cd testsuite && gcc -o server server.c -L../ -loojprotolinux
	cd testsuite && gcc -o client client.c -L../ -loojprotolinux
	cd testsuite && gcc -o server_self_stop server_self_stop.c -L../ -loojprotolinux -lpthread

linuxtsclean:
	cd testsuite && rm server client server_self_stop
