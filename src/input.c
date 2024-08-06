#include "player.h"

#define MAX_GAMEPADS 4

Input checkGamePadInput(void);

Input checkPlayerInput(void)
{
    Input input;
    input = checkGamePadInput();
    if (input != NONE)
    {
        return input;
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
    {
        input = DOWN;
    }
    else
    {
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        {
            input = UP;
        }
        else
        {
            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
            {
                input = LEFT;
            }
            else
            {
                if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
                {
                    input = RIGHT;
                }
                else
                {
                    input = NONE;
                }
            }
        }
    }

    if (IsKeyPressed(KEY_ENTER))
        return INTRO;
    return input;
}

Input checkGamePadInput(void)
{
    Input input;
    int gamepadId = -1; // No GamePad
    for (int i = 0; i < MAX_GAMEPADS; i++)
    {
        if (IsGamepadAvailable(i))
        {
            gamepadId = i;
            break;
        }
    }

    if (gamepadId < 0)
    {
        return NONE;
    }

    if (GetGamepadAxisMovement(gamepadId, GAMEPAD_AXIS_LEFT_Y) > 0)
    {
        input = DOWN;
    }
    else
    {
        if (GetGamepadAxisMovement(gamepadId, GAMEPAD_AXIS_LEFT_Y < 0))
        {
            input = UP;
        }
        else
        {
            if (GetGamepadAxisMovement(gamepadId, GAMEPAD_AXIS_LEFT_X > 0))
            {
                input = RIGHT;
            }
            else
            {
                if (GetGamepadAxisMovement(gamepadId, GAMEPAD_AXIS_LEFT_X) < 0)
                {
                    input = LEFT;
                }
                else
                {
                    input = NONE;
                }
            }
        }
    }
    if(IsGamepadButtonPressed(gamepadId,GAMEPAD_BUTTON_UNKNOWN)){
        return INTRO;
    }

    return input;
}