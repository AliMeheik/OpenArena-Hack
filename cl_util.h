#ifndef CL_UTIL_H__
#define CL_UTIL_H__

#include <Windows.h>


bool mem_MakeWritable       ( const DWORD targetAddress, const int size );
bool mem_RestoreProtection  ( const DWORD targetAddress, const int size );
DWORD GetModuleAddress( const WCHAR* moduleName );
DWORD GetfunctionAddress( const char* functionName, HMODULE moduleHandle );

#endif



