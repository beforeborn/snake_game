// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"
#include "tchar.h"
#include "windows.h"
using namespace std;

#define UCHAR unsigned char
#define UINT  unsigned int
#define ULONG unsigned long
#define IN
#define OUT

ULONG FUNC_ReadBinaryFile(const char * pcFilePath, UCHAR **ppucBuf, UINT *puiBufLen);
void UTF8ToWideChar(IN UCHAR* utfChar,OUT UCHAR** wideChar);
void WideCharToANSI(IN UCHAR* wideChar, OUT UCHAR** destChar);
char* UTF8ToANSI(IN UCHAR* utf8);
int _tmain_Test(int argc, _TCHAR* argv[])
{
	char* pcFilePath = "d:\\utf-8.txt";
	UCHAR* pucBuf = NULL;
	UINT  puiBufLen ;
	ULONG ulResult = FUNC_ReadBinaryFile(pcFilePath, &pucBuf,& puiBufLen);
	if (0 != ulResult)
	{
		return 0;
	}
    //printf("content=%s", pucBuf);
	UCHAR* wideChar = NULL;
	UCHAR* destChar = NULL;
	printf("len=%d\n", strlen((LPSTR)pucBuf));
	UTF8ToWideChar(pucBuf,&wideChar);
	WideCharToANSI(wideChar, &destChar);
	printf("%s\n", destChar);
	printf("len=%d\n", strlen((LPSTR)destChar));
	printf("len=%d\n", strlen((LPSTR)"abc 你好!"));
	
	char* str=UTF8ToANSI(pucBuf);
	printf("str=%s", str);

	FILE *f = fopen((LPSTR)destChar+1, "r");
	if (NULL == f)
	{
		printf("打开f失败\n");
	}
	FILE *f2 = fopen((LPSTR)str, "r");
	if (NULL == f2)
	{
		printf("打开f2失败\n");
	}
	getchar();
	return 0;
}
void UTF8ToWideChar(IN UCHAR* utfChar, OUT UCHAR** wideChar)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, (LPSTR)utfChar, -1, NULL, 0);
	*wideChar = (UCHAR*)malloc(2 * len+1);
	MultiByteToWideChar(CP_UTF8,0,(LPSTR)utfChar,-1,(LPWSTR)*wideChar,len);
	setlocale(LC_ALL, "chs");
	wprintf(L"widechar=%ls\n", (const wchar_t*)(*wideChar));
	MessageBoxW(NULL, (const wchar_t*)*wideChar+1, NULL, MB_OK);
}
void WideCharToANSI(IN UCHAR* wideChar, OUT UCHAR** destChar)
{
	int len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wideChar, -1, NULL, 0, NULL, NULL);
	*destChar = (UCHAR*)malloc(len * 2+1);
	BOOLEAN b = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wideChar, -1, (LPSTR)*destChar, len, NULL, NULL);
	printf("b=%d\n", b);
}

char* UTF8ToANSI(IN UCHAR* utf8)
{
	int len;

	//UTF-8转UNICODE 
	len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)utf8, -1, NULL, 0);
	WCHAR * wszUtf8 = new WCHAR[len + 1];
	memset(wszUtf8, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)utf8, -1, wszUtf8, len);

	MessageBoxW(NULL, (const wchar_t*)wszUtf8, NULL, MB_OK);

	//UNICODE转ANSI，实际上经过两次转换 UTF-8 已经变成了 GBK 编码 
	len = WideCharToMultiByte(CP_ACP, 0, wszUtf8, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszUtf8, -1, szGBK, len, NULL, NULL);

	return szGBK;
}

ULONG FUNC_ReadBinaryFile(const char * pcFilePath, UCHAR **ppucBuf, UINT *puiBufLen)
{
	FILE *fp = NULL;
	UCHAR *pBuf = NULL;
	UINT uiBufLen = 0;
	int iResult = 0;

	fp = fopen(pcFilePath, "rb");
	if (NULL == fp)
	{
		printf("open file failed %s", pcFilePath);
		return 1;
	}
	iResult = fseek(fp, 0, SEEK_END);
	if (0 != iResult)
	{
		fclose(fp);
		printf("fseek end failed");
		return 2;
	}
	uiBufLen = ftell(fp);

	iResult = fseek(fp, 0, SEEK_SET);
	if (0 != iResult)
	{
		fclose(fp);
		printf("fseek set failed");
		return 3;
	}
	pBuf = (UCHAR*)malloc(uiBufLen+1);
	if (NULL == pBuf)
	{
		fclose(fp);
		printf("malloc failed");
		return 4;
	}
	iResult = fread(pBuf, 1, uiBufLen, fp);
	if (iResult != uiBufLen)
	{
		free(pBuf);
		fclose(fp);
		printf("fread failed");
		return 5;
	}
	memset(pBuf + uiBufLen, '\0', 1);
	*ppucBuf = pBuf;
	*puiBufLen = uiBufLen;
	fclose(fp);	
	return 0;
}

