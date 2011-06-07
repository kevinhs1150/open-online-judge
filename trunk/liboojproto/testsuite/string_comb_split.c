#include <stdio.h>
#include <stdlib.h>
#include <protointernal.h>

int main( void )
{
	char msgbuf[1024];
	char *msgptr;
	char msg1[] = "Test Message1.";
	char msg2[] = "Test Message2.\n   Also part of message 2.";
	char msg3[] = "Test Message3. wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww";
	
	short sr, id;
	char *splitmsg1, *splitmsg2, *splitmsg3;
	
	printf("Combining.\n");
	msgptr = proto_srid_comb( msgbuf, 10, 20 );
	msgptr = proto_str_comb( msgptr, msg1 );
	msgptr = proto_str_comb( msgptr, msg2 );
	msgptr = proto_str_comb( msgptr, msg3 );
	
	printf("msgbuf:%d %d ... \n", msgbuf[0], msgbuf[1] );
	
	msgptr = proto_srid_split( msgbuf, &sr, &id );
	printf("Splitting: sr %d, id %d.\n", sr, id );
	splitmsg1 = proto_str_split( msgptr, &msgptr );
	splitmsg2 = proto_str_split( msgptr, &msgptr );
	splitmsg3 = proto_str_split( msgptr, NULL );
	
	printf("Outputting.\n%s\n%s\n%s\n", splitmsg1, splitmsg2, splitmsg3 );
	
	free( splitmsg1 );
	free( splitmsg2 );
	free( splitmsg3 );
	
	getchar();
	return 0;
}