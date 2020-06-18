#ifndef CL_DATA_H__
#define CL_DATA_H__
#include "cl_util.h"
#include <Windows.h>
#include "g_openArena.h"

extern DWORD addr_gamebase;

struct Game_function {

    
    //swapbuffer
    DWORD addr_opengl                 =   GetModuleAddress    ( L"opengl32.dll"    );
    DWORD addr_swapbuffer             =   GetfunctionAddress  ( "wglSwapBuffers", reinterpret_cast<HMODULE>( addr_opengl ) );

    DWORD addr_gameSysCall            =   addr_gamebase + 0x2778;
    DWORD addr_vmArgPtr               =   addr_gamebase + 0x8CFDC;
    DWORD addr_boxTrace               =   addr_gamebase + 0x37F18;
    DWORD addr_memset                 =   addr_gamebase + 0x1D8CE0;
    DWORD addr_getModuleByHandle      =   addr_gamebase + 0x128668;
};

extern Game_function    rev_GameFunction;

struct Reverse_data {
                 cg_t            *cg             = nullptr;    // this should be referenced staticly from cgame base, need to find this offset
                 cgs_t           *cgs            = nullptr;    // this is clientgame static, should contain static info 
                 centity_t       *entity_list    = nullptr; 
                 clientInfo_t    *client_info    = nullptr;
                 float*          viewAngleX      = reinterpret_cast<float*>( addr_gamebase + 0x8821FC ); 
                 float*          viewAngleY      = reinterpret_cast<float*>( addr_gamebase + 0x8821F8 ); 
           const vm_s**          cgame_ptr       = reinterpret_cast<const vm_s**>( addr_gamebase + 0x76CC74 ) ;                 
    static const size_t          size_cg         = sizeof( cg_t );
    static const size_t          size_cgs        = sizeof( cgs_t );
    static const size_t          size_entityList = sizeof( centity_t ) * 1024 ;
};
extern Reverse_data     rev_Structs;

#endif

