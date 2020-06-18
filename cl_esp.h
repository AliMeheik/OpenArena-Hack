#ifndef CL_ESP_H__
#define CL_ESP_H__

#include <Windows.h>
#include <gl/GL.h>
#include <iostream>
#pragma comment(lib, "opengl32.lib")

enum Color {
    RED,
    YELLOW,
    GREEN
};

struct EspController {
       
    void dr_SetOrthoState();
    void dr_RestoreState();
    void dr_DrawPlus( float x, float y, float width, float height, Color color );
    void dr_DrawBox();

};


extern EspController esp_controller;

#endif
