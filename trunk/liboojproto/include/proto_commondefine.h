#ifndef PROTO_COMMONDEFINE_H_
#define PROTO_COMMONDEFINE_H_

#define PROTO_DBG 1

/* include socket library */
#ifdef _WIN32 /* winsock2 */
//	#include <windows.h>
	#include <winsock2.h>
//	#include <ws2tcpip.h>
#elif __linux /* linux socket */
	#include <sys/socket.h>
	#include <arpa/inet.h>
#else
	#error "Currently only Windows and Linux are supported."
#endif

/* SRC Type Definition */
#define SRC_ADMIN 1
#define SRC_JUDGE 2
#define SRC_TEAM  3

/* SR Byte Definition */
#define OPSR_SERVER	0
#define OPSR_ADMIN	1
#define OPSR_JUDGE	2
#define OPSR_TEAM	3

/* ID Byte Definition */
/* account status management */
#define OPID_LOGIN_REQUEST	0	/* login request from client */
#define OPID_LOGIN_REPLY	0	/* login reply from server */
#define OPID_LOGOUT_REQUEST	1	/* logout request from client */
#define OPID_LOGOUT_REPLY	1	/* logout reply from server */
#define OPID_PASSWD_CHANGE	2   /* password change from client */
#define OPID_PASSWD_REPLY	2   /* password change reply from server */

/* time control & start and stop */
#define OPID_TIMER_SET			200 /* set client timer */
#define OPID_CONTEST_START		201 /* start contest */
#define OPID_CONTEST_STOP		202 /* stop contest */
#define OPID_TIMER_SYNC			203 /* sync timer */
#define OPID_CONTEST_STATE_SYNC	204 /* sync contest state */

/* team -> server */
#define OPID_SUBMISSION		10	/* submission */
#define OPID_CLAR			11	/* clarification */
#define OPID_PD_REQUEST		12	/* problem download request */
#define OPID_TRUN_SYNC		13	/* run sync for team */
#define OPID_SB_SYNC		100	/* request sync scoreboard */
/* server -> team */
#define OPID_RUN_REPLY		10	/* run result reply */
#define OPID_CLAR_REPLY		11	/* clarification reply */
#define OPID_SB_UPDATE		12	/* scoreboard update */
#define OPID_PUPLOAD		13	/* problem upload */
#define OPID_P_CHANGE		14	/* problem change */
	#define PCH_OPID_ADD		0	/* problem added */
	#define PCH_OPID_DEL		1	/* problem deleted */
	#define PCH_OPID_MOD		2	/* problem modified */

/* judge -> server */
#define OPID_RUN_RESULT		10	/* run result */
#define OPID_RUN_SYNC		11	/* run sync request */
#define OPID_TAKE_RUN		12	/* take run */
#define OPID_JPROBLEM_SYNC	13	/* sync problems for judge */
#define OPID_CLAR_RESULT	101	/* clarification result */
#define OPID_CLAR_SYNC		102	/* clarification update */
/* server -> judge */
#define OPID_CLAR_REPLY		11	/* clarification reply */
#define OPID_RUN_REQUEST	15	/* run request */
#define OPID_CLAR_REQUEST	16	/* clarification request */
#define OPID_PUPDATE		17	/* problem update */
#define OPID_PREMOVE		18	/* problem removal */
#define OPID_TAKE_RESULT	19	/* take result */

/* admin -> server */
#define OPID_ACC_MANAGE		10	/* account management */
	#define ACC_OPID_ADD		0	/* add account */
	#define ACC_OPID_DEL		1	/* delete account */
	#define ACC_OPID_MOD		2	/* modify account */
	#define ACC_OPID_SYNC		3	/* sync account info */
#define OPID_P_MANAGE		11	/* problem management */
	#define P_OPID_ADD			0	/* add problem */
	#define P_OPID_DEL			1	/* delete problem */
	#define P_OPID_MOD			2	/* modify problem */
	#define P_OPID_SYNC			3	/* sync problem info */
#define OPID_SB_SYNC		100	/* request sync scoreboard */
#define OPID_CLAR_RESULT	101	/* clarification result */
#define OPID_CLAR_SYNC		102	/* clarification sync */
/* server -> admin */
#define OPID_CLAR_REPLY		11	/* clarification reply */
#define OPID_SB_UPDATE		12	/* scoreboard update */
#define OPID_CLAR_REQUEST	16	/* clarification request */
#define OPID_PUPDATE		17	/* problem update */
#define OPID_PREMOVE		18	/* problem removal */
#define OPID_ACCUPDATE		20	/* account update */
#define OPID_ACCREMOVE		21	/* account removal */


/* login/logout confirmation code */
#define LOGIN_VALID			1
#define LOGIN_ACC_NOTEXIST	2
#define LOGIN_PASS_WRONG	3
#define LOGOUT_OK			1
#define LOGOUT_FAIL			2

/* password change confirmation code */
#define PASSWD_SUCCESS		1
#define PASSWD_MISMATCH		2
#define PASSWD_INVALID		3

/* take success code */
#define TAKE_FAIL		0
#define TAKE_SUCCESS	1

#endif
