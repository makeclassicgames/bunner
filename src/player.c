#include "player.h"
#include "util/resources.h"

#define MAX_GAMEPADS 4
#define PLAYER_SPEED 5

Input checkGamePadInput(void);
Texture *GetCurrentPlayerTexture(Player *);
void initCamera(Player *);
void updateCamera(Player *);

Rectangle getCurrentSitHitBox(Player *player);
Rectangle getCurrentJumpHitBox(Player *player);

void initPlayer(Player *player, Vector2 position, short lives)
{
    player->direction = DOWN_DIR;
    player->state = SIT;
    player->currentFrame = 0;
    player->Frame=0;
    player->lives = lives;
    player->position = position;
    player->offset = 0;
    player->texture = GetCurrentPlayerTexture(player);
    initCamera(player);
}

void initCamera(Player *player)
{
    player->camera.offset = (Vector2){225, 0};
    player->camera.target = (Vector2){player->position.x, player->position.y + player->offset};
    player->camera.rotation = 0.0f;
    player->camera.zoom = 1.0f;
}
void updatePlayer(Player *player)
{
    player->Frame++;
    if (player->state != SPLASH && player->state != DROWING)
    {
        switch (player->playerInput)
        {
        case UP:
            player->direction = UP_DIR;
            player->state = JUMP;
            if (player->position.y > 0)
                player->position.y -= PLAYER_SPEED;
            if (player->position.y > 400)
                player->offset -= PLAYER_SPEED;
            break;
        case DOWN:
            player->direction = DOWN_DIR;
            player->state = JUMP;

            player->position.y += PLAYER_SPEED;
            if (player->position.y > 400)
                player->offset += PLAYER_SPEED;
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

        if (player->Frame % 10 == 0 && player->state)
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
    }else{
        if(player->state==DROWING && player->Frame%6==0 && player->currentFrame<7){
            player->currentFrame++;
        }

    }

    updateCamera(player);

    // Get current Texture
    player->texture = GetCurrentPlayerTexture(player);
}

void updateCamera(Player *player)
{
    player->camera.target.y = player->offset;
}

void drawPlayer(Player *player)
{

    DrawTexture(*player->texture, player->position.x, player->position.y, WHITE);
}

void drawLives(Player* player){
 for (int i = 0; i < player->lives; i++)
 {
    DrawTextureEx(*getSpriteTexture(PLAYER_SIT_TYPE,1),
    (Vector2){10+(30*i),10},0.0f,0.5f,WHITE);
 }
 
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
    case DROWING:
        return (getSpriteTexture(PLAYER_DROWING_TYPE,player->currentFrame));
    case SPLASH:
        return (getSpriteTexture(PLAYER_SPLAT_TYPE,player->direction));
    default:
        break;
    }
}

Rectangle getCurrentHitBox(Player *player)
{
    switch (player->direction)
    {
    case SIT:
        return getCurrentSitHitBox(player);
        break;
    case JUMP:
        return getCurrentJumpHitBox(player);
        break;
    default:
        return (Rectangle){player->position.x,
                           player->position.y,
                           player->texture->width,
                           player->texture->height};
        break;
    }
}

Rectangle getCurrentSitHitBox(Player *player)
{
    switch (player->direction)
    {
    case DOWN_DIR:
    case UP_DIR:
        return (Rectangle){player->position.x + 23, player->position.y + 11, 17, 27};
    case RIGHT_DIR:
    case LEFT_DIR:
        return (Rectangle){player->position.x + 17, player->position.y + 11, 23, 27};
    default:
        break;
    }
}
Rectangle getCurrentJumpHitBox(Player *player)
{
    switch (player->direction)
    {
    case DOWN_DIR:
    case UP_DIR:
        return (Rectangle){player->position.x + 23, player->position.y + 11, 13, 33};
    case RIGHT_DIR:
    case LEFT_DIR:
        return (Rectangle){player->position.x + 11, player->position.y + 11, 37, 18};
    default:
        break;
    }
}