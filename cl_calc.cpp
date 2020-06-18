#include "cl_calc.h"


float calc_Get_distance( const vec3_t src, const vec3_t dest ) {
    return sqrt(
            pow( src[0] - dest[0], 2 ) +
            pow( src[1] - dest[1], 2 ) +
            pow( src[2] - dest[2], 2 )
            );
}

// w2s for esp
bool calc_WorldToScreen( vec3_t src, vec3_t dst, float fovx, float fovy, float windowWidth, float windowHeight, vec3_t left, vec3_t up, vec3_t forward, vec3_t &screen ){

		float xc, yc;
		float px, py;
		float z;

		px = tan(fovx * M_PI / 360.0);
		py = tan(fovy * M_PI / 360.0);
        vec3_t result;
        VectorSubtract( dst, src, result ); 

		xc = windowWidth / 2.0;
		yc = windowHeight / 2.0;

		z = DotProduct( result, left ); 

		if (z <= 0.1) { return false; }

		screen[0] = xc - DotProduct(result, up ) *xc / (z*px);
		screen[1] = yc - DotProduct(result, forward) *yc / (z*py);
		return true;
}


// Getting aimpoint

void calc_VecToAngles( const vec3_t value1, vec3_t angles ) {
	float	forward;
	float	yaw, pitch;
	
	if ( value1[1] == 0 && value1[0] == 0 ) {
		yaw = 0;
		if ( value1[2] > 0 ) {
			pitch = 90;
		}
		else {
			pitch = 270;
		}
	}
	else {
		if ( value1[0] ) {
			yaw = ( atan2 ( value1[1], value1[0] ) * 180 / M_PI );
		}
		else if ( value1[1] > 0 ) {
			yaw = 90;
		}
		else {
			yaw = 270;
		}
		if ( yaw < 0 ) {
			yaw += 360;
		}

		forward = sqrt ( value1[0]*value1[0] + value1[1]*value1[1] );
		pitch = ( atan2(value1[2], forward) * 180 / M_PI );
		if ( pitch < 0 ) {
			pitch += 360;
		}
	}

	angles[PITCH] = -pitch;
	angles[YAW] = yaw;
	angles[ROLL] = 0;
}


