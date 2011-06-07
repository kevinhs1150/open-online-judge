#include <stdio.h>
#include <stdlib.h>
#include <protointernal.h>
#include <locale.h>

int main( void )
{
	setlocale(LC_ALL, "");

	wchar_t str[] = L"String test.中文測試";
	char *cstr;
	wchar_t *bstr;
	
	cstr = proto_str_presend( str );
	printf("cstr = %s\n", cstr );
	
	bstr = proto_str_postrecv( cstr );
	wprintf(L"bstr = %s\n", bstr);
	wprintf(L"cstrw= %s\n", (wchar_t*)cstr);
	
	getchar();

	return 0;
}