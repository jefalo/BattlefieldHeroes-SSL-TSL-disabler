#include "MyFunction.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD nReason, VOID* pvReserved)
{
	HANDLE hookThread;
	DWORD dwThreadId1 = 0;
	switch (nReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		hookThread = CreateThread(NULL, 0, InjectHooks, NULL, 0, &dwThreadId1);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}