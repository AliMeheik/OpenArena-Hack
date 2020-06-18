#ifndef CL_AIMBOT_H__
#define CL_AIMBOT_H__
#include "g_openArena.h"
#include "cl_esp.h"

struct Client {

    int         id = -1;
    int         team;
    char    *   name;
    vec3_t  *   eye_coordinates;
    void        toString();
    float       Get_distance( vec3_t other );
    refdef_t*   refdef;
};

struct Player {
    int         id = -1;
    int         team;
    char    *   name;
    vec3_t      world_location;
    vec3_t      eye_coordinates;
    void        toString();
    int         model;
    vec3_t*     lerpOrigin;
    float       Get_distance( vec3_t other );
    bool        isVisible( vec3_t from );
    void        DrawPlus( const Color color );
};

struct Active_game {

    Player        player_list[MAX_CLIENTS];
    Client        local_player;
    int           game_type;
    int           current_playerNum;
    bool          isLocal; 

};
            
struct Aimbot {
    static  void Start        ( void );
            bool Init         ( void );
            bool isVisible    ( trace_t *result, vec3_t from, vec3_t to, vec3_t mins, vec3_t maxs, const int mask );
            void AimPoint     ( vec3_t target_head, vec3_t local_head ); 
};

extern Aimbot aimbot;
extern Active_game active_game;
#endif
