#include "MyFunction.h"
#include <vector>
#include <algorithm>
#include "BFH_Address.h"

DWORD JMPback_DisableSSL_BFH = ADDRESS_BFH_DisableSSL_Pattern() + 7;
DWORD JMPback_DisableSSL_BFHW = ADDRESS_BFHW_DisableSSL_Pattern() + 7;
DWORD temp0 = 0;


__declspec(naked) void tHook_DisableSSL_BFH2()
{
	__asm
	{
		push ebp
		mov ebp, esp
		push esi
		mov esi, dword ptr ss : [ebp + 0x8]
		JMP[JMPback_DisableSSL_BFH]
	}
}

__declspec(naked) void tHook_DisableSSL_BFH()
{
	__asm
	{
		PUSH EBP
		MOV EBP, ESP
		PUSH DWORD PTR SS : [EBP + 0x18]
		PUSH DWORD PTR SS : [EBP + 0x14]
		PUSH DWORD PTR SS : [EBP + 0x10]
		push 0
		PUSH DWORD PTR SS : [EBP + 0x8]
		call [tHook_DisableSSL_BFH2]
		pop ebp
		pop ebp
		pop ebp
		pop ebp
		pop ebp
		pop ebp
		ret
	}
}

__declspec(naked) void tHook_DisableSSL_BFHW2()
{
	__asm
	{
		push ebp
		mov ebp, esp
		push esi
		mov esi, dword ptr ss : [ebp + 0x8]
		JMP[JMPback_DisableSSL_BFHW]
	}
}

__declspec(naked) void tHook_DisableSSL_BFHW()
{
	__asm
	{
		PUSH EBP
		MOV EBP, ESP
		PUSH DWORD PTR SS : [EBP + 0x18]
		PUSH DWORD PTR SS : [EBP + 0x14]
		PUSH DWORD PTR SS : [EBP + 0x10]
		push 0
		PUSH DWORD PTR SS : [EBP + 0x8]
		call[tHook_DisableSSL_BFHW2]
		pop ebp
		pop ebp
		pop ebp
		pop ebp
		pop ebp
		pop ebp
		ret
	}
}

DWORD WINAPI InjectHooks(LPVOID lpParam)
{
	if (ADDRESS_BFHW_DisableSSL_Pattern() != 0x0)
	{
		PlaceJMP((BYTE*)ADDRESS_BFHW_DisableSSL_Pattern(), (DWORD)tHook_DisableSSL_BFHW, 7);
	}

	if (ADDRESS_BFH_DisableSSL_Pattern() != 0x0)
	{
		PlaceJMP((BYTE*)ADDRESS_BFH_DisableSSL_Pattern(), (DWORD)tHook_DisableSSL_BFH, 7);
	}

	while (true)
	{
	}
	return 0;
}