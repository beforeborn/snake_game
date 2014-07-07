#include "stdio.h"
#include "windows.h"
#include "ipHlpapi.h"
#include "tchar.h"
#include "iostream"

#pragma comment(lib,"iphlpapi.lib")
void GetLocalMAC(char * buf);
BOOL IsLocalAdapter(char *pAdapterName);
void UTF8ToWideChar(IN UCHAR* utfChar, OUT _TCHAR** wideChar)
{
	int len = MultiByteToWideChar(CP_ACP, 0, (LPSTR)utfChar, -1, NULL, 0);
	*wideChar = (_TCHAR*)malloc(2 * len + 1);
	MultiByteToWideChar(CP_ACP, 0, (LPSTR)utfChar, -1, (LPWSTR)*wideChar, len);
	
	wprintf(L"widechar=%ls\n", (const wchar_t*)(*wideChar));
	//MessageBoxW(NULL, (const wchar_t*)*wideChar + 1, NULL, MB_OK);
}
int main(int n, char* arg[])
{
	setlocale(LC_ALL, "en");
	char* s1 = "helloÄãºÃa";
	
	wchar_t* s2 = NULL;
	UTF8ToWideChar((UCHAR*)s1,&s2);

	printf("s1.len=%d,s2.len=%d\n", strlen(s1), wcslen(s2));
	printf("s1=%s\n", s1);
	wprintf(L"s2=%ls\n", s2);

	getchar();
}

void GetLocalMAC(char *buf)
{
	IP_ADAPTER_INFO *IpAdaptersInfo = NULL;
	IP_ADAPTER_INFO *IpAdaptersInfoHead = NULL;
	IpAdaptersInfo = (IP_ADAPTER_INFO *)GlobalAlloc(GPTR, sizeof(IP_ADAPTER_INFO));
	if (IpAdaptersInfo == NULL)
	{
		return;
	}
	DWORD dwDataSize = sizeof(IP_ADAPTER_INFO);
	DWORD dwRetVal = GetAdaptersInfo(IpAdaptersInfo, &dwDataSize);
	if (ERROR_SUCCESS != dwRetVal)
	{
		GlobalFree(IpAdaptersInfo);
		IpAdaptersInfo = NULL;
		if (ERROR_BUFFER_OVERFLOW == dwRetVal)
		{
			IpAdaptersInfo = (IP_ADAPTER_INFO *)GlobalAlloc(GPTR, dwDataSize);
			if (IpAdaptersInfo == NULL)
			{
				return;
			}
			if (ERROR_SUCCESS != GetAdaptersInfo(IpAdaptersInfo, &dwDataSize))
			{
				GlobalFree(IpAdaptersInfo);
				return;
			}
		}
		else
		{
			return;
		}
	}
	//Save the head pointer of IP_ADAPTER_INFO structures list.
	IpAdaptersInfoHead = IpAdaptersInfo;
	do{
		if (IsLocalAdapter(IpAdaptersInfo->AdapterName))
		{
			sprintf(buf, "%02x-%02x-%02x-%02x-%02x-%02x",
				IpAdaptersInfo->Address[0],
				IpAdaptersInfo->Address[1],
				IpAdaptersInfo->Address[2],
				IpAdaptersInfo->Address[3],
				IpAdaptersInfo->Address[4],
				IpAdaptersInfo->Address[5]);
			//
			break;
		}
		IpAdaptersInfo = IpAdaptersInfo->Next;
	} while (IpAdaptersInfo);
	if (IpAdaptersInfoHead != NULL)
	{
		GlobalFree(IpAdaptersInfoHead);
	}
}

BOOL IsLocalAdapter(char *pAdapterName)
{
	BOOL ret_value = FALSE;
#if 0
#define NET_CARD_KEY _T("System\\CurrentControlSet\\Control\\Network\\{4D36E972-E325-11CE-BFC1-08002BE10318}")
	char szDataBuf[MAX_PATH + 1];
	DWORD dwDataLen = MAX_PATH;
	DWORD dwType = REG_SZ;
	HKEY hNetKey = NULL;
	HKEY hLocalNet = NULL;
	if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, NET_CARD_KEY, 0, KEY_READ, &hNetKey))
		return FALSE;
	wsprintf(szDataBuf, "%s\\Connection", pAdapterName);
	if (ERROR_SUCCESS != RegOpenKeyEx(hNetKey, szDataBuf, 0, KEY_READ, &hLocalNet))
	{
		RegCloseKey(hNetKey);
		return FALSE;
	}
	if (ERROR_SUCCESS != RegQueryValueEx(hLocalNet, "MediaSubType", 0, &dwType, (BYTE *)szDataBuf, &dwDataLen))
	{
		goto ret;
	}
	if (*((DWORD *)szDataBuf) != 0x01)
		goto ret;
	dwDataLen = MAX_PATH;
	if (ERROR_SUCCESS != RegQueryValueEx(hLocalNet, "PnpInstanceID", 0, &dwType, (BYTE *)szDataBuf, &dwDataLen))
	{
		goto ret;
	}
	if (strncmp(szDataBuf, "PCI", strlen("PCI")))
		goto ret;
	ret_value = TRUE;
ret:
	RegCloseKey(hLocalNet);
	RegCloseKey(hNetKey);
#endif
	return ret_value;
}