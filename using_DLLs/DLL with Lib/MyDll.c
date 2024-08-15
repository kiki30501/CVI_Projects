#include <cvidef.h>
#include <ansi_c.h>
DLLEXPORT int  PrintLen = 10;
void DllPrint(void)
{
int k;
for (k=0;k<PrintLen;k++)
		printf("Hello World\n");	
}
