#include <protointernal.h>

#include <windows.h>

int main( void )
{
	printf("File send.\n");
	filesend( "127.0.0.1", L"send.file" );
	return 0;
}
