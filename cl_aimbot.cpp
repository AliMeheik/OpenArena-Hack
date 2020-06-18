#include "cl_aimbot.h"
#include "cl_reverse.h"
#include "cl_util.h"
#include "cl_calc.h"
#include "cl_hook.h"
#include <iostream>
#include "cl_esp.h"

DWORD       jmp_BackFromSysCall;
Aimbot      aimbot;
Active_game active_game;

//-- Player

bool Player::isVisible( vec3_t from ) {
    trace_t trace;
    cl_BoxTrace( &trace, from , this->eye_coordinates, vec3_origin, vec3_origin, 0, MASK_PLAYERSOLID, qfalse );   
    return trace.fraction == 1.0;
}

void Player::DrawPlus( const Color color ) {
    vec3_t screenCoords;
    refdef_t refdef = *( active_game.local_player.refdef);
    if( calc_WorldToScreen( *( active_game.local_player.eye_coordinates ),  this->eye_coordinates,refdef.fov_x, refdef.fov_y, refdef.width, refdef.height, refdef.viewaxis[0], refdef.viewaxis[1], refdef.viewaxis[2], screenCoords )){
        esp_controller.dr_DrawPlus( screenCoords[0], screenCoords[1], 3,3, color ); 
    }
}

void Player::toString() {
    printf( "Name: %s id: %d team: %d\n", name, id, team );
}

float Player::Get_distance( vec3_t other ) {
    return calc_Get_distance( other, this->eye_coordinates );
}


//-- SysCall handling func

void __stdcall LoadEyeCoords( uintptr_t* offset ) {

    switch( *offset ) {
        case CG_R_ADDREFENTITYTOSCENE: 
            refEntity_t *refentity = reinterpret_cast<refEntity_t*>( cl_vmArgPtr( offset[1] ) ); 
            if( refentity->reType == RT_MODEL )  {
                refentity->renderfx |= 8; //wallhack
                char* modelName = cl_getModuleByHandle( refentity->hModel )->name;
                if( strstr( modelName, "head" ) ) {   //check if there is a head word in the modelName
                    Player *player;
                    int *currentPlayers = &( active_game.current_playerNum );
                    for( int i = 0 ; i < *currentPlayers ; i++ ) {
                        player = &( active_game.player_list[i] );
                        if( VectorCompare( refentity->lightingOrigin, *( player->lerpOrigin ) ) ) {  
                            VectorCopy( refentity->origin,  player->eye_coordinates );
                        }
                    }
                }
            }
            break;
    }   
}

//--Aimbot

void Aimbot::AimPoint(vec3_t target_head, vec3_t local_head ) {
    vec3_t refdefViewAngles;           
    calc_VecToAngles( rev_Structs.cg->refdef.viewaxis[0], refdefViewAngles );  

    vec3_t org, ang;
    VectorSubtract(target_head, local_head, org);
    calc_VecToAngles(org, ang);

    ang[PITCH] -= refdefViewAngles[PITCH];
    ang[YAW] -= refdefViewAngles[YAW];

    *( rev_Structs.viewAngleY ) +=  ang[PITCH];
    *( rev_Structs.viewAngleX ) +=  ang[YAW];
}

void LoadAimbot_data() {

    //read basic data 
    active_game.current_playerNum = 0;
    active_game.game_type = rev_Structs.cgs->gametype;

    //load local_player data
    Client *localPlayer                 = &( active_game.local_player );
    localPlayer->refdef                 = &(rev_Structs.cg->refdef);
    localPlayer->id                     = rev_Structs.cg->clientNum;
    clientInfo_t* local_clientInfo      = &( rev_Structs.cgs->clientinfo[ localPlayer->id ] ) ;
    localPlayer->name                   = local_clientInfo->name; 
    localPlayer->team                   = local_clientInfo->team; 
    localPlayer->eye_coordinates        = &(( localPlayer->refdef)->vieworg);

    //load target list
    centity_t *entity;
    clientInfo_t* client_info;
    Player* player_ptr;
    for( int i = 0 ; i < MAX_CLIENTS ; i++ ) {
        entity = & ( rev_Structs.entity_list[i] ); 
        if( entity->currentState.eType == ET_PLAYER && entity->currentValid) { 
            if( !(entity->currentState.eFlags & EF_DEAD) && entity->currentState.number != localPlayer->id ) {
                client_info = &( rev_Structs.cgs->clientinfo[ i ] );
                if( client_info->infoValid ) {
                    player_ptr = &( active_game.player_list[active_game.current_playerNum++]);      
                    player_ptr->name             = client_info->name;
                    player_ptr->team             = client_info->team;
                    player_ptr->lerpOrigin       = &( entity->lerpOrigin );
                }
            }
        }
    }
}


void Aimbot::Start() {

    if( !strcmp( (**rev_Structs.cgame_ptr).name, "cgame" ) ) {                       
        LoadAimbot_data();    //Load data

        Client *localPlayer      = &( active_game.local_player );
        int *currentPlayers      = &( active_game.current_playerNum );

        Player *target           = nullptr; 
        Player *lock_target      = nullptr; 

        for( int i = 0 ; i < *currentPlayers ; i++ ) {                                
            target = &( active_game.player_list[i]); 

            if( target->team == localPlayer->team && active_game.game_type != GT_FFA ) {
                continue;
            }

            if( target->isVisible( *( localPlayer->eye_coordinates ) ) ) { 
                target->DrawPlus( RED );
                lock_target = target;     
            } else {
                target->DrawPlus( GREEN );
                continue; 
            }

            for( ++i ; i < *currentPlayers; i++ ) {         //continue
                target++;    
                if( target->team == localPlayer->team && active_game.game_type != GT_FFA ) {
                    continue;
                }  

                if( target->isVisible( *( localPlayer->eye_coordinates ) ) ) {
                    float distanceA = calc_Get_distance( *( localPlayer->eye_coordinates), lock_target->eye_coordinates );
                    float distanceB = calc_Get_distance( *( localPlayer->eye_coordinates), target->eye_coordinates );
                    if( distanceB < distanceA ) {
                        target->DrawPlus( RED );
                        lock_target = target;
                    }
                } else {
                    target->DrawPlus( GREEN );
                }
            }
        }

        //target should be found
        if( lock_target ) {
            if(GetAsyncKeyState(0x2)) {
                aimbot.AimPoint( lock_target->eye_coordinates, *( localPlayer->eye_coordinates ) ); 
            }
        }
    }
}

//-- Hooked jmp functions, aimbot loops

void __declspec( naked )h_sysCall() {
    __asm {
        push    ebp
            mov     ebp, esp
            push    edi
            push    esi
            pushfd
            pushad
            mov eax, [ebp + 8] 
            push eax
            call LoadEyeCoords
            popad
            popfd 
            jmp[ jmp_BackFromSysCall ] 
    }
}

void __declspec(naked) h_swapBuffer() {
    __asm {
        pushfd                  
            pushad
            call   Aimbot::Start    
            popad
            popfd
            mov     edi, edi        
            push    ebp
            mov     ebp, esp 
            jmp     hooks[SWAP_BUFFER_HOOK].returnAddress  
    }
}


bool InitAimbotHooks( void ) {

    DWORD addr_swapbuffer = rev_GameFunction.addr_swapbuffer;
    cl_HookFunction( addr_swapbuffer, reinterpret_cast<DWORD>( h_swapBuffer ), 5, SWAP_BUFFER_HOOK );      //swapBuffers
    cl_HookFunction( reinterpret_cast<DWORD>( cl_gameSysCall ), reinterpret_cast<DWORD> ( h_sysCall ),5, CL_GAMESYSCALL ); 
    return true;
}


bool Aimbot::Init( void ) {

    cl_BoxTrace         = reinterpret_cast<CL_BoxTrace>( rev_GameFunction.addr_boxTrace );
    cl_gameSysCall      = reinterpret_cast<CL_GameSysCall>( rev_GameFunction.addr_gameSysCall );
    jmp_BackFromSysCall = reinterpret_cast<DWORD>( cl_gameSysCall ) + 5;

    InitAimbotHooks();

    return true;
}

