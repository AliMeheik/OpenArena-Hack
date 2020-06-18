/*===================================================
 *          hooking
 * ==================================================*/
#ifndef _CL_HOOK_H__
#define _CL_HOOK_H__
#include <Windows.h>
#include "g_openArena.h"

//Original function pointers
using CL_BoxTrace           =   void         ( __cdecl* )( trace_t *result, const vec3_t start, const vec3_t end, vec3_t mins, vec3_t maxs, clipHandle_t model, int brushmask, int capsule ); 
using CL_MemsetFunc         =   void*        ( __cdecl* )( void*,int,size_t );
using CL_GameSysCall        =   uintptr_t    ( __cdecl* )( uintptr_t* arg   ); 
using CL_VMArgPtr           =   uintptr_t    ( __cdecl* )( uintptr_t offset );
using CL_GetModelByHandle   =   model_t     *( __cdecl* )( int mHandle      );

extern CL_MemsetFunc        cl_memset;
extern CL_BoxTrace          cl_BoxTrace;
extern CL_GameSysCall       cl_gameSysCall;
extern CL_VMArgPtr          cl_vmArgPtr;
extern CL_GetModelByHandle  cl_getModuleByHandle;

constexpr BYTE MAX_HOOKS                    = 10;
constexpr BYTE JMP_INSTRUCTION_SIZE         = 5;
constexpr BYTE MAX_SAVED_BYTES              = 10;

//register hook flags, also direct index in registredHooks array

enum Hook_id {
    SWAP_BUFFER_HOOK,
    MEMSET_HOOK,
    CL_GAMESYSCALL,
    CM_TRACE,
    CG_SYSCALL
};

struct Hook_info {
    DWORD   targetAddress;
    DWORD   returnAddress;
    DWORD   overWritenBytes;
    BYTE    originalBytes[MAX_SAVED_BYTES];
};


bool cl_HookFunction(  const DWORD targetFunctionAddress, const DWORD injectFunctionAddress, const INT bytesToWrite, const Hook_id id );   
bool cl_RemoveHook  (  const Hook_id id );


extern Hook_info hooks[MAX_HOOKS];

#endif
