#include "player.h"
#include "util/resources.h"

#define MAX_GAMEPADS 4
#define PLAYER_SPEED 5

Input checkGamePadInput(void);
Texture *GetCurrentPlayerTexture(Player *);
void initCamera(Player*);
void updateCamera(Player*);

void initPlayer(Player *player, Vector2 position, short lives)
{
    player->direction = DOWN_DIR;
    player->state = SIT;
    player->currentFrame = 0;
    player->lives = lives;
    player->position = position;
    player->offset=0;
    player->texture = GetCurrentPlayerTexture(player);
    initCamera(player);
}

void initCamera(Player* player){
    player->camera.offset=(Vector2){225,0};
    player->camera.target=(Vector2){player->position.x, player->position.y+player->offset};
    player->camera.rotation=0.0f;
    player->camera.zoom=1.0f;
}
void updatePlayer(Player *player)
{
    player->currentFrame++;
    switch (player->playerInput)
    {
    case UP:
        player->direction = UP_DIR;
        player->state = JUMP;
        if (player->position.y > 0)
            player->position.y -= PLAYER_SPEED;
        if(player->position.y>400)
            player->offset-=PLAYER_SPEED;
        break;
    case DOWN:
        player->direction = DOWN_DIR;
        player->state = JUMP;

        player->position.y += PLAYER_SPEED;
        if(player->position.y>400)
            player->offset+=PLAYER_SPEED;
        break;
    case LEFT:
        player->direction = LEFT_DIR;
        player->state = JUMP;
        if (player->position.x > 0)
            player->position.x -= PLAYER_SPEED;
        break;
    case RIGHT:
        player->direction = RIGHT_DIR;
        player->state = JUMP;
        if (player->position.x < 390)
            player->position.x += PLAYER_SPEED;
        break;
    case NONE:
        player->state = SIT;
        break;
    default:
        break;
    }


   if(player->currentFrame%10==0&&player->state)
    {
        if (player->state == JUMP)
        {
            player->state = SIT;
        }
        else
        {
            player->state = JUMP;
        }
    }

   updateCamera(player);

    // Get current Texture
    player->texture = GetCurrentPlayerTexture(player);
}

void updateCamera(Player* player){
    player->camera.target.y=player->offset;
}

void drawPlayer(Player *player)
{

    DrawTexture(*player->texture, player->position.x, player->position.y, WHITE);
}

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

    if(IsKeyPressed(KEY_ENTER))
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

    return input;
}

Texture *GetCurrentPlayerTexture(Player *player)
{
    switch (player->state)
    {
    case SIT:
        return (getSpriteTexture(PLAYER_SIT_TYPE, player->direction));
        break;
    case JUMP:
        return (getSpriteTexture(PLAYER_JUMP_TYPE, player->direction));
    default:
        break;
    }
}
