#pragma once

#include <Windows.h>
#include <string>
//#include <iostream>
#include <psapi.h>

void PlaceJMP(BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen);
void PlaceNOPE(BYTE *pAddress, DWORD dwLen);
void WriteMemory(BYTE *pAddress, BYTE *value, DWORD dwLen);