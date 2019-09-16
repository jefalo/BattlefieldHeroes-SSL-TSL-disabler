#include "Injection.h"

/*BFHeroes pattern search*/
DWORD Get_BFHeroes_BaseAddress();
DWORD ADDRESS_BFH_DisableSSL_Pattern();
DWORD ADDRESS_BFH_LoadLevels_Pattern();

/*BFHeroes_w32ded pattern search*/
DWORD Get_BFHeroes_w32ded_BaseAddress();
DWORD ADDRESS_BFHW_DisableSSL_Pattern();
DWORD ADDRESS_BFHW_LoadLevels_Pattern();


DWORD GetModuleSize(char *szModule);

bool MemoryCompare(const BYTE* bData, const BYTE* bMask, const char* szMask);

DWORD FindSignature(DWORD start, DWORD size, const char* sig, const char* mask);

DWORD Get_BFHeroes_BaseAddress();

DWORD Get_BFHeroes_w32ded_BaseAddress();

