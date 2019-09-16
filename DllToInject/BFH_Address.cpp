#include "BFH_Address.h"


DWORD Get_BFHeroes_BaseAddress()
{
	return (DWORD)GetModuleHandleA("BFHeroes.exe");
}

DWORD Get_BFHeroes_w32ded_BaseAddress()
{
	return (DWORD)GetModuleHandleA("BFHeroes_w32ded.exe");
}

DWORD ADDRESS_BFH_DisableSSL_Pattern()
{
	static DWORD address = 0;
	LPCSTR Signature = "\x55\x8B\xEC\x56\x8B\x75\x08\x57\xFF\x75\x0C\x8B\xC6\xE8";
	LPCSTR Mask = "XXXXXXXXXXXXXX";

	if (address == 0)
		address = FindSignature(Get_BFHeroes_BaseAddress(), GetModuleSize("BFHeroes.exe"), Signature, Mask);

	return address;
}

DWORD ADDRESS_BFHW_DisableSSL_Pattern()
{
	static DWORD address = 0;
	LPCSTR Signature = "\x55\x8B\xEC\x56\x8B\x75\x08\x57\xFF\x75\x0C\x8B\xC6\xE8";
	LPCSTR Mask = "XXXXXXXXXXXXXX";

	if (address == 0)
		address = FindSignature(Get_BFHeroes_w32ded_BaseAddress(), GetModuleSize("BFHeroes_w32ded.exe"), Signature, Mask);

	return address;
}

DWORD GetModuleSize(char *szModule)
{
	MODULEINFO modinfo = { 0 };
	HMODULE hModule = GetModuleHandleA(szModule);
	if (hModule == 0) return 0;
	GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
	return modinfo.SizeOfImage;
}

// for comparing a region in memory, needed in finding a signature
bool MemoryCompare(const BYTE* bData, const BYTE* bMask, const char* szMask) {
	for (; *szMask; ++szMask, ++bData, ++bMask) {
		if (*szMask == 'X' && *bData != *bMask) {
			return false;
		}
	}
	return (*szMask == NULL);
}

// for finding a signature/pattern in memory of another process
DWORD FindSignature(DWORD start, DWORD size, const char* sig, const char* mask)
{
	BYTE* data = new BYTE[size];
	SIZE_T bytesRead;

	ReadProcessMemory(GetCurrentProcess(), (LPVOID)start, data, size, &bytesRead);

	for (DWORD i = 0; i < size; i++)
	{
		if (MemoryCompare((const BYTE*)(data + i), (const BYTE*)sig, mask)) {
			return start + i;
		}
	}
	delete[] data;
	return NULL;
}