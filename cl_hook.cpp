#include "cl_hook.h"
#include "cl_util.h"
#include <iostream>

#define JMP_OPCODE 0xE9
//function pointers
CL_MemsetFunc       cl_memset;
CL_BoxTrace         cl_BoxTrace;  
CL_VMArgPtr         cl_vmArgPtr;
CL_GameSysCall      cl_gameSysCall;
CL_GetModelByHandle cl_getModuleByHandle;

Hook_info hooks[MAX_HOOKS];

bool cl_HookFunction(  const DWORD targetAddress, const DWORD functAddress, const INT bytesToWrite, const Hook_id id ){

    if( bytesToWrite > MAX_SAVED_BYTES ) {
        printf( "Error: byte size excides MAX_SAVED_BYTES\n" );
        return false;
    }

    DWORD delta = functAddress - targetAddress - JMP_INSTRUCTION_SIZE; 

    //saving info
    Hook_info hook_data;  
    hook_data.targetAddress     = targetAddress;
    hook_data.overWritenBytes   = bytesToWrite;
    hook_data.returnAddress     = targetAddress + bytesToWrite;

    mem_MakeWritable( targetAddress , bytesToWrite );    

    //saving bytes
    memcpy( hook_data.originalBytes, reinterpret_cast<LPCVOID>( targetAddress ), bytesToWrite ); 

    //register hook info
    hooks[id] = hook_data; 

    //clear the bytes 
    memset( reinterpret_cast<LPVOID>( targetAddress ), 0x90, bytesToWrite ); 

    //write the actual jmp instruction
    *reinterpret_cast<BYTE*>( targetAddress ) = JMP_OPCODE; 
    *reinterpret_cast<INT*>( targetAddress + 0x01 ) = delta;  

    mem_RestoreProtection( targetAddress, bytesToWrite );

    return true;
}

bool cl_RemoveHook  ( const Hook_id id ) {

    Hook_info hook_data;  
    hook_data = hooks[id];


    mem_MakeWritable( hook_data.targetAddress , hook_data.overWritenBytes );    

    //restore orignal bytes 
    memcpy( reinterpret_cast<LPVOID>( hook_data.targetAddress ), hook_data.originalBytes, hook_data.overWritenBytes ); 

    //restore 
    mem_RestoreProtection( hook_data.targetAddress, hook_data.overWritenBytes );

    return true;
}






