#include "cl_esp.h"

EspController esp_controller;

void EspController::dr_SetOrthoState() {

    GLint viewPort[4];
    glGetIntegerv(GL_VIEWPORT, viewPort);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, viewPort[2] , viewPort[3] , 0, -1.0, 1.0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
}

void EspController::dr_RestoreState() {
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}


void EspController::dr_DrawPlus( float x, float y, float width, float height,  Color color ) {
        

    dr_SetOrthoState();
    switch( color ) {
        case RED    : glColor3ub( 255,  0,   0 );  break; 
        case GREEN  : glColor3ub(  0,  255,  0 );  break;
        case YELLOW : glColor3ub( 255, 255,  0 );  break;
    }
    //glColor3ub( 0, 255, 0 );
    glBegin(GL_LINES);
    glVertex2f(x - width, y);
    glVertex2f(x + width, y);
    glVertex2f(x, y - width);
    glVertex2f(x , y + width);
    glEnd();  
    dr_RestoreState();
}
