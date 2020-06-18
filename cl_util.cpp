#include "cl_util.h"
#include <iostream> 

bool mem_MakeWritable( const DWORD targetAddress, const int size ) {
    DWORD orgProtection;
    return VirtualProtect( reinterpret_cast<LPVOID>( targetAddress ), size, PAGE_EXECUTE_READWRITE, &orgProtection );      
}

bool mem_RestoreProtection( const DWORD targetAddress, const int size ) {
    DWORD orgProtection;
   return VirtualProtect( reinterpret_cast<LPVOID>( targetAddress ), size, PAGE_READONLY, &orgProtection ); 
}

DWORD GetModuleAddress( const WCHAR* moduleName ) {
    
    DWORD address;
    if( moduleName != NULL ) {
        address = ( DWORD )GetModuleHandle( moduleName );
        printf( "found module %S address: %x\n", moduleName, address );
    } else {
        address = ( DWORD )GetModuleHandle( NULL );
        printf( "found game base address: %x\n", address );
    }

    return address;
}

DWORD GetfunctionAddress( const char* functionName, HMODULE moduleHandle ) {
    
    DWORD address;
    address = ( DWORD )GetProcAddress( moduleHandle, functionName );
    printf( "found function %s address: %x\n", functionName, address );
    return address;
}
