#include "player.h"

#define MAX_GAMEPADS 4

Input checkGamePadInput(void);

Input checkPlayerInput(void){

    Input input = checkGamePadInput();
    if(input!=NONE){
        return input;
    }

    if(IsKeyDown(KEY_DOWN)|| IsKeyDown(KEY_S)){
        return DOWN;
    }else{
        if(IsKeyDown(KEY_UP)|| IsKeyDown(KEY_W)){
            return UP;
        }else{
            if(IsKeyDown(KEY_LEFT)|| IsKeyDown(KEY_A)){
                return LEFT;
            }else{
                if(IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_D)){
                    return RIGHT;
                }
            }
        }
    }

    if(IsKeyPressed(KEY_ENTER)){
        return INTRO;
    }

    return NONE;
}

Input checkGamePadInput(void){

    int gamepadId=-1;
    for(int i=0;i<MAX_GAMEPADS;i++){
        if(IsGamepadAvailable(i)){
            gamepadId=i;
            break;
        }
    }

    if(gamepadId<0){
        return NONE;
    }
    if(GetGamepadAxisMovement(gamepadId,GAMEPAD_AXIS_LEFT_Y)>0){
        return DOWN;
    }else{
        if(GetGamepadAxisMovement(gamepadId,GAMEPAD_AXIS_LEFT_Y)<0){
            return UP;
        }else{
            if(GetGamepadAxisMovement(gamepadId,GAMEPAD_AXIS_LEFT_X)>0){
                return RIGHT;
            }else{
                if(GetGamepadAxisMovement(gamepadId,GAMEPAD_AXIS_LEFT_X)<0){
                    return LEFT;
                }
            }
        }
    }

    return NONE;

}