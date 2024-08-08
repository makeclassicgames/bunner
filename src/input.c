#include "player.h"

//Maximum GamePads
#define MAX_GAMEPADS 4

//Functions prototypes
//Check current GamepadInput
Input checkGamePadInput(void);

Input checkPlayerInput(void){

    //Get current GamepadInput
    Input input = checkGamePadInput();
    //if the gamepad Returns an input, return the result.
    if(input!=NONE){
        return input;
    }

    //Check down Direction (down key or S)
    if(IsKeyDown(KEY_DOWN)|| IsKeyDown(KEY_S)){
        return DOWN;
    }else{
        //Check Up direction (Up key or W)
        if(IsKeyDown(KEY_UP)|| IsKeyDown(KEY_W)){
            return UP;
        }else{
            //Check Left Direction (Left or A)
            if(IsKeyDown(KEY_LEFT)|| IsKeyDown(KEY_A)){
                return LEFT;
            }else{
                //Check Rigth direction (Right or D)
                if(IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_D)){
                    return RIGHT;
                }
            }
        }
    }

    //If Enter key is pressed once...
    if(IsKeyPressed(KEY_ENTER)){
        return INTRO;
    }
    //Return none otherwise
    return NONE;
}

Input checkGamePadInput(void){

    //Current Gamepad Id
    int gamepadId=-1;
    //Check the current gamepadId
    for(int i=0;i<MAX_GAMEPADS;i++){
        if(IsGamepadAvailable(i)){
            gamepadId=i;
            break;
        }
    }
    //If thereis no gamepad, return none
    if(gamepadId<0){
        return NONE;
    }
    //Check gamepad axis for down Direction.
    if(GetGamepadAxisMovement(gamepadId,GAMEPAD_AXIS_LEFT_Y)>0){
        return DOWN;
    }else{
        //Check gamepad axis for up Direction.
        if(GetGamepadAxisMovement(gamepadId,GAMEPAD_AXIS_LEFT_Y)<0){
            return UP;
        }else{
            //Check gamepad axis for Right Direction.
            if(GetGamepadAxisMovement(gamepadId,GAMEPAD_AXIS_LEFT_X)>0){
                return RIGHT;
            }else{
                //Check gamepad axis for Left Direction.
                if(GetGamepadAxisMovement(gamepadId,GAMEPAD_AXIS_LEFT_X)<0){
                    return LEFT;
                }
            }
        }
    }
    //Return None otherwise
    return NONE;

}