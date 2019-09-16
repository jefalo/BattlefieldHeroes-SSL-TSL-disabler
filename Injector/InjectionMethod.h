#pragma once
#define _WIN32_WINNT 0x0400

#include <iostream>
#include <string>
#include <direct.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <vector>
#include <sstream>
#include <TlHelp32.h>
#include <locale>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <iphlpapi.h>
#include <stdio.h>
#include <streambuf>
#include <stdio.h>
#include <Assert.h>

#pragma comment(lib, "ws2_32")
#pragma comment(lib, "iphlpapi.lib")

/**
Get The Current Directory Path We Are In
*/
char* GetCurrentDir();

/**
Convert char* into LPCTSTR
*/
LPCTSTR SzToLPCTSTR(char* szString);

/**
Check And Wait Untill The Process We Are Looking For Will Appear
*/
void WaitForProcessToAppear(LPCTSTR lpcszProc, DWORD dwDelay,int count);

/**
Return The Process ID by His (LPCTSTR) Process Name
*/
DWORD GetProcessIDByName(LPCTSTR lpcszProc,int num);

/**
Inject The dll That Is Found At szDLLPath(Dll Path) To The Process Identified by dwPid(Process ID Given)
*/
BOOL InjectDll(DWORD dwPid, char* szDLLPath);

/**
Convert An Input String To A Output String With All Lower Case Letters
*/
std::string ToLower(std::string _string);