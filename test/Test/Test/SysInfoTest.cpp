#if 0
#include "stdio.h"
#include "windows.h"
//#include "ipTypes.h"
//#include "windef.h"
#include "ipHlpapi.h"
#include "tchar.h"

#pragma comment(lib,"iphlpapi.lib")
void GetLocalMAC(char * buf);
BOOL IsLocalAdapter(char *pAdapterName);

#define NET_CARD_KEY _T("System\\CurrentControlSet\\Control\\Network\\{4D36E972-E325-11CE-BFC1-08002BE10318}")
#define TAR _T("{54E176A1-C087-4B3E-A969-3F4BE379F6C7}\\Connection")
//#define key _T("System\\CurrentControlSet\\Control\\Network\\{4D36E972-E325-11CE-BFC1-08002BE10318}\\{54E176A1-C087-4B3E-A969-3F4BE379F6C7}\\Connection\\PnpInstanceID")
#define rootKey _T("System\\CurrentControlSet\\Control\\Network")
int main_sys(int argc, char* argv[])
{
	char mac[1024];
	GetLocalMAC(mac);

	getchar();
	return 1;
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
			sprintf(buf, "%02x-%02x-%02x-%02x-%02x-%02x'\0'",
				IpAdaptersInfo->Address[0],
				IpAdaptersInfo->Address[1],
				IpAdaptersInfo->Address[2],
				IpAdaptersInfo->Address[3],
				IpAdaptersInfo->Address[4],
				IpAdaptersInfo->Address[5]);
			printf("buf=%s", buf);
			//break;
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

	CHAR szDataBuf[20480 + 1];
	DWORD dwDataLen = 20480;
	DWORD dwType = REG_SZ;
	HKEY hNetKey = NULL;
	HKEY hLocalNet = NULL;
	if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, rootKey, 0, KEY_READ, &hNetKey))
		return FALSE;
	sprintf(szDataBuf, (LPCSTR)"%s\\Connection", (LPCSTR)pAdapterName);
	/*if (ERROR_SUCCESS != RegOpenKeyEx(hNetKey, TAR, 0, KEY_READ, &hLocalNet))
	{
		RegCloseKey(hNetKey);
		return FALSE;
	}
		if (ERROR_SUCCESS != RegQueryValueEx(hLocalNet, (LPCWSTR) "MediaSubType", 0, &dwType, (BYTE *)szDataBuf, &dwDataLen))
		{
		goto ret;
		}
		if (*((DWORD *)szDataBuf) != 0x01)
		goto ret;
		*/
	dwDataLen = 20480;

	int result = 0;
	BYTE *desBuf=NULL;
	IErrorInfo * errorInfo;
	result = RegQueryValueEx(hNetKey, _T("Config"), 0, &dwType, desBuf, &dwDataLen);
	printf("result=%d", result);
	if (ERROR_SUCCESS != result)
	{
		goto ret;
	}
	printf("desBuf1=%s\n", desBuf);

	if (strncmp((LPSTR)szDataBuf, "PCI", strlen("PCI")))
		goto ret;
	ret_value = TRUE;
ret:
	RegCloseKey(hLocalNet);
	RegCloseKey(hNetKey);
	return ret_value;
}
#endif