#include "MyFunction.h"

void PlaceJMP(BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen) {
	DWORD dwOldProtect, dwBkup, dwRelAddr;

	VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	dwRelAddr = (DWORD)(dwJumpTo - (DWORD)pAddress) - 5;

	*pAddress = 0xE9;

	*((DWORD *)(pAddress + 0x1)) = dwRelAddr;

	for (DWORD x = 0x5; x < dwLen; x++)
		*(pAddress + x) = 0x90;

	VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);

}

void PlaceNOPE(BYTE *pAddress, DWORD dwLen) {
	DWORD dwOldProtect, dwBkup;

	VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	for (DWORD x = 0; x < dwLen; x++)
		*(pAddress + x) = 0x90;

	VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);
}

void WriteMemory(BYTE *pAddress, BYTE *value, DWORD dwLen) {
	DWORD dwOldProtect, dwBkup;

	VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	for (DWORD x = 0; x < dwLen; x++)
		*(pAddress + x) = value[x];

	VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);
}