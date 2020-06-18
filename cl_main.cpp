/*
   ===============================================
   Coding using quake3 engine style and logic
   ==============================================
   */

#include <iostream>
#include <Windows.h>
#include "cl_hook.h"
#include "cl_util.h"
#include "g_openArena.h"
#include "cl_reverse.h"
#include "cl_aimbot.h"

void LoadConsole ( void ) {
    AllocConsole();
    FILE *f;
    freopen_s( &f, "CONOUT$", "w", stdout );
}

void* __cdecl h_memset( void* dest, int what, size_t count ) {
    
    switch( count ) {
        case rev_Structs.size_cg                :   rev_Structs.cg             = (   cg_t*    ) dest;  break;
        case rev_Structs.size_cgs               :   rev_Structs.cgs            = (   cgs_t*   ) dest;  break;
        case rev_Structs.size_entityList        :   rev_Structs.entity_list    = ( centity_t* ) dest;  break;
    }

    cl_RemoveHook( MEMSET_HOOK );

    //get correct return data
    void* return_val = cl_memset( dest, what, count);

    cl_HookFunction ( reinterpret_cast<DWORD>( cl_memset ), reinterpret_cast<DWORD>( h_memset ), 6, MEMSET_HOOK ); 

    return return_val;
}

void InitMainHooks() {

    cl_memset               = reinterpret_cast<CL_MemsetFunc>( rev_GameFunction.addr_memset ); 
    

    //hook memset for cg, cgs, centity
    cl_HookFunction ( reinterpret_cast<DWORD>( cl_memset ), reinterpret_cast<DWORD>( h_memset ), 6, MEMSET_HOOK ); 
    
}

DWORD WINAPI Init( LPVOID param ) {

    cl_vmArgPtr             =   reinterpret_cast<CL_VMArgPtr>        ( rev_GameFunction.addr_vmArgPtr          );
    cl_getModuleByHandle    =   reinterpret_cast<CL_GetModelByHandle>( rev_GameFunction.addr_getModuleByHandle );
    LoadConsole();
    InitMainHooks();
    aimbot.Init();
    return 0;
}


bool __stdcall DllMain( HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved ) {    

    //inject
    switch( dwReason  ) {
        case DLL_PROCESS_ATTACH: 
            CreateThread( NULL, NULL, Init, NULL, NULL, NULL );
            DisableThreadLibraryCalls( hModule );
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
