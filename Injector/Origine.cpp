#include "InjectionMethod.h"

int main(int argc, char *argv[])
{
	bool done = false;
	SetConsoleTitle(TEXT("Jefalo BFH noSSL Launcher"));
	char szProc[MAX_PATH], szDll[MAX_PATH];
	char* szDllPath1 = (char*)malloc(MAX_PATH);
	char* szExePath1 = (char*)malloc(MAX_PATH);
	std::cout << "Press 1 to start the game and 2 to start the server...";
	char res = getchar();
	char* szProc1 = "BFHeroes.exe";
	char* szDll1 = "Hook.dll";
	char* szEXE1 = "BFHeroes.exe";
	szDllPath1 = GetCurrentDir();
	strcat_s(szDllPath1, MAX_PATH, "\\");
	strcat_s(szDllPath1, MAX_PATH, szDll1);

	szExePath1 = GetCurrentDir();
	strcat_s(szExePath1, MAX_PATH, "\\");
	strcat_s(szExePath1, MAX_PATH, szEXE1);


	STARTUPINFO info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;

	if (res == '1')
	{
		if (CreateProcess(L"BFHeroes.exe", L" +sessionId 123456 +ignoreAsserts 1 +magma 0 +magmaProtocol \"http\" +magmaHost \"127.0.0.1\" +developer 1 +multi 1", NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo)) {
			CloseHandle(processInfo.hProcess);
			CloseHandle(processInfo.hThread);
		}

		if (InjectDll(processInfo.dwProcessId, szDllPath1))
		{
			done = true;
			std::cout << " > Injection succeeded!" << std::endl;
		}
	}
	else
	{
		if (CreateProcess(L"BFHeroes_w32ded.exe", L" +magma 0 +magmaProtocol \"http\" +magmaHost \"127.0.0.1\" +multi 1 +debugNetwork 1 +ignoreAsserts 1 +ranked 0 +matchmaking 1 +region \"EU\" +type 1 +checkEntitlement 0 +eaEncryptedLogin \"test-server\" +soldierName \"test-server\" +guid \"test-server\" +eaAccountName \"test-server\" +secret \"JVVBRLGE\" +developer 1", NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo)) {
			CloseHandle(processInfo.hProcess);
			CloseHandle(processInfo.hThread);
		}

		if (InjectDll(processInfo.dwProcessId, szDllPath1))
		{
			done = true;
			std::cout << " > Injection succeeded!" << std::endl;
		}
	}

	if(!done)
		std::cout << " > Injection failed!" << std::endl;
	system("pause");
	return 0;
}