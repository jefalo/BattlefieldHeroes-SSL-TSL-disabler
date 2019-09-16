#include "InjectionMethod.h"

char* GetCurrentDir()
{
	char* szRet = (char*)malloc(MAX_PATH);

	_getcwd(szRet, MAX_PATH);

	return szRet;
}

LPCTSTR SzToLPCTSTR(char* szString)
{
	LPTSTR lpszRet;
	size_t size = strlen(szString) + 1;

	lpszRet = (LPTSTR)malloc(MAX_PATH);
	mbstowcs_s(NULL, lpszRet, size, szString, _TRUNCATE);

	return lpszRet;
}

void WaitForProcessToAppear(LPCTSTR lpcszProc, DWORD dwDelay,int count)
{
	HANDLE hSnap;
	PROCESSENTRY32 peProc;
	DWORD procId = 0;
	int bAppared = 0;

	while (bAppared != count)
	{
		if ((hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) != INVALID_HANDLE_VALUE)
		{
			peProc.dwSize = sizeof(PROCESSENTRY32);
			if (Process32First(hSnap, &peProc))
				while (Process32Next(hSnap, &peProc) && bAppared != count)
				{
					if (!lstrcmp(lpcszProc, peProc.szExeFile) && peProc.th32ProcessID != procId)
					{
						procId = peProc.th32ProcessID;
						bAppared++;
						std::cout << " > Process Id " << procId << "..." << std::endl;
					}
				}
		}
		CloseHandle(hSnap);
		Sleep(dwDelay);
	}
}

DWORD GetProcessIDByName(LPCTSTR lpcszProc,int num)
{
	HANDLE hSnap;
	PROCESSENTRY32 peProc;
	DWORD dwRet = -1;
	int procCounter = num;

	if ((hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) != INVALID_HANDLE_VALUE)
	{
		peProc.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hSnap, &peProc))
			while (Process32Next(hSnap, &peProc) && procCounter>0)
				if (!lstrcmp(lpcszProc, peProc.szExeFile))
				{
					procCounter--;
					if(procCounter == 0)
						dwRet = peProc.th32ProcessID;
				}
	}
	CloseHandle(hSnap);

	return dwRet;
}

BOOL InjectDll(DWORD dwPid, char* szDLLPath)
{
	DWORD dwMemSize;
	HANDLE hProc;
	LPVOID lpRemoteMem, lpLoadLibrary;
	BOOL bRet = FALSE;

	if ((hProc = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_CREATE_THREAD, FALSE, dwPid)) != NULL)
	{
		dwMemSize = strlen(szDLLPath) + 1;
		if ((lpRemoteMem = VirtualAllocEx(hProc, NULL, dwMemSize, MEM_COMMIT, PAGE_READWRITE)) != NULL)
			if (WriteProcessMemory(hProc, lpRemoteMem, (LPCVOID)szDLLPath, dwMemSize, NULL))
			{
				lpLoadLibrary = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
				if (CreateRemoteThread(hProc, NULL, 0, (LPTHREAD_START_ROUTINE)lpLoadLibrary, lpRemoteMem, 0, NULL) != NULL)
					bRet = TRUE;
			}
	}
	CloseHandle(hProc);

	return bRet;
}

std::string ToLower(std::string _string)
{
	std::string _string_ = "";
	std::locale loc;
	for (std::string::size_type i = 0; i<_string.length(); ++i)
		_string_ += std::tolower(_string[i], loc);
	return _string_;
}