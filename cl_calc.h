#ifndef CALC_FUNCTIONS_H__
#define CALC_FUNCTIONS_H__
#include "g_openArena.h"
bool calc_WorldToScreen(vec3_t src, vec3_t dst, float fovx, float fovy, float windowWidth, float windowHeight, vec3_t left, vec3_t up, vec3_t forward,vec3_t &screen);
//bool calc_AimToScreen( const vec3_t src, const vec3_t dest, vec3_t out ); 
float calc_Get_distance( const vec3_t src, const vec3_t dest ); 
void calc_VecToAngles( const vec3_t value1, vec3_t angles );
#endif
