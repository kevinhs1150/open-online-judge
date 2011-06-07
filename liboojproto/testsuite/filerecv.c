#include <protointernal.h>

#include <windows.h>

int main( void )
{
	printf("File receive.\n");
	
	filerecv( "127.0.0.1", L"recv.file" );

	printf("[APP] Connection closed.\nPress enter to terminate the program.... ");
	getchar();
	return 0;
}
