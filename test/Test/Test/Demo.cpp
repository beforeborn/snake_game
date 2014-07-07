#include <windows.h>
#include <malloc.h>
#include <stdio.h>

#define TOTALBYTES    8192
#define BYTEINCREMENT 4096

void main_demo()
{
	DWORD BufferSize = TOTALBYTES;
	PPERF_DATA_BLOCK PerfData = NULL;

	printf("Allocating memory...\n");
	while (RegQueryValueEx(HKEY_PERFORMANCE_DATA,
		TEXT("Global"),
		NULL,
		NULL,
		(LPBYTE)PerfData,
		&BufferSize) == ERROR_MORE_DATA)
	{
		// Get a buffer that is big enough.

		BufferSize += BYTEINCREMENT;
		PerfData = (PPERF_DATA_BLOCK)realloc(PerfData, BufferSize);
	}
	printf("\nFinal buffer size is %d.\n", BufferSize);
}
