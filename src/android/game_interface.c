#include <stdbool.h>

#include "game_interface.h"
#include "../../../../Clibs_OpenTouch/game_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>

#include "SDL2/SDL.h"

#ifndef LOGI

#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO,"JNI", __VA_ARGS__))
#endif

extern int SDL_SendKeyboardKey(Uint8 state, SDL_Scancode scancode);

extern void androidWaitFrames(int frames);

int PortableKeyEvent(int state, int code, int unicode)
{
    //LOGI("PortableKeyEvent %d %d %d",state,code,unicode);

    if(state)
        SDL_SendKeyboardKey(SDL_PRESSED, (SDL_Scancode) code);
    else
        SDL_SendKeyboardKey(SDL_RELEASED, (SDL_Scancode) code);

    return 0;
}


void PortableAction(int state, int action)
{
    LOGI("PortableAction %d   %d", state, action);

    if(((action >= PORT_ACT_MENU_UP) && (action <= PORT_ACT_MENU_ABORT)) &&
       ((PortableGetScreenMode() == TS_MENU) || (PortableGetScreenMode() == TS_Y_N)))
    {
        SDL_Scancode scanCode = SDL_SCANCODE_UNKNOWN;

        switch(action)
        {
            case PORT_ACT_MENU_UP:
                scanCode = SDL_SCANCODE_UP;
                break;
            case PORT_ACT_MENU_DOWN:
                scanCode = SDL_SCANCODE_DOWN;
                break;
            case PORT_ACT_MENU_LEFT:
                scanCode = SDL_SCANCODE_LEFT;
                break;
            case PORT_ACT_MENU_RIGHT:
                scanCode = SDL_SCANCODE_RIGHT;
                break;
            case PORT_ACT_MENU_SELECT:
                scanCode = SDL_SCANCODE_RETURN;
                break;
            case PORT_ACT_MENU_BACK:
                scanCode = SDL_SCANCODE_ESCAPE;
                break;
            case PORT_ACT_MENU_CONFIRM:
                scanCode = SDL_SCANCODE_Y;
                break;
            case PORT_ACT_MENU_ABORT:
                scanCode = SDL_SCANCODE_N;
                break;
        }

        if(scanCode != SDL_SCANCODE_UNKNOWN)
            PortableKeyEvent(state, scanCode, 0);
    }
    else
    {

        switch(action)
        {
            case PORT_ACT_LEFT:

                break;
            case PORT_ACT_RIGHT:

                break;
            case PORT_ACT_FWD:

                break;
            case PORT_ACT_BACK:

                break;
            case PORT_ACT_MOVE_LEFT:

                break;
            case PORT_ACT_MOVE_RIGHT:

                break;
            case PORT_ACT_USE:

                break;
            case PORT_ACT_ATTACK:

                break;
            case PORT_ACT_MAP:

                break;
            case PORT_ACT_MAP_ZOOM_IN:

                break;
            case PORT_ACT_MAP_ZOOM_OUT:

                break;
            case PORT_ACT_NEXT_WEP:

                break;
            case PORT_ACT_PREV_WEP:

                break;
            case PORT_ACT_QUICKSAVE:

                break;
            case PORT_ACT_QUICKLOAD:

                break;
            case PORT_ACT_WEAP1:

                break;
            case PORT_ACT_WEAP2:

                break;
            case PORT_ACT_WEAP3:

                break;
            case PORT_ACT_WEAP4:

                break;
            case PORT_ACT_FLY_UP:

                break;
            case PORT_ACT_FLY_DOWN:

                break;
        }

    }
}

void PortableMouseButton(int state, int button, float dx, float dy)
{

}

void PortableCommand(const char *cmd)
{

}

bool PortableSetAlwaysRun(bool run)
{
    return false;
}

// =================== FORWARD and SIDE MOVMENT ==============

static float forwardmove, sidemove; //Joystick mode

void PortableMoveFwd(float fwd)
{
    if(fwd > 1)
        fwd = 1;
    else if(fwd < -1)
        fwd = -1;

    forwardmove = fwd;
}

void PortableMoveSide(float strafe)
{
    if(strafe > 1)
        strafe = 1;
    else if(strafe < -1)
        strafe = -1;

    sidemove = strafe;
}

void PortableMove(float fwd, float strafe)
{
    PortableMoveFwd(fwd);
    PortableMoveSide(strafe);
}

//======================================================================

//Look up and down
static int look_pitch_mode;
static float look_pitch_mouse, look_pitch_abs, look_pitch_joy;

void PortableLookPitch(int mode, float pitch)
{
    look_pitch_mode = mode;
    switch(mode)
    {
        case LOOK_MODE_MOUSE:
            look_pitch_mouse += pitch;
            break;
        case LOOK_MODE_ABSOLUTE:
            look_pitch_abs = pitch;
            break;
        case LOOK_MODE_JOYSTICK:
            look_pitch_joy = pitch;
            break;
    }
}

//left right
static int look_yaw_mode;
static float look_yaw_mouse, look_yaw_joy;

void PortableLookYaw(int mode, float yaw)
{
    look_yaw_mode = mode;
    switch(mode)
    {
        case LOOK_MODE_MOUSE:
            look_yaw_mouse += yaw;
            break;
        case LOOK_MODE_JOYSTICK:
            look_yaw_joy = yaw;
            break;
    }
}


void PortableInit(int argc, const char **argv)
{
    int main_mobile(int argc, char *argv[]);
    main_mobile(argc, (char **) argv);
}

touchscreemode_t PortableGetScreenMode()
{
    return TS_MENU;
}

void PortableBackButton()
{
    PortableKeyEvent(1, SDL_SCANCODE_ESCAPE, 0);
    androidWaitFrames(1);
    PortableKeyEvent(0, SDL_SCANCODE_ESCAPE, 0);
}

void PortableAutomapControl(float zoom, float x, float y)
{

}


void INL_ANDROID_GetMovement(int *side, int *forward, int *yaw, int *pitch)
{
    *side += sidemove * -0x160000;
    *forward += -forwardmove * 2000;

    // Mouse movement
    *yaw += look_yaw_mouse * 200000000;
    *pitch += look_pitch_mouse * -600;

    // Joystick movement
    *pitch += look_pitch_joy * 80;
    *yaw += look_yaw_joy * 2000000;

    look_yaw_mouse = 0;
    look_pitch_mouse = 0;
}




