#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

typedef enum player_input
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    INTRO,
    NONE
} Input;

typedef enum player_status
{
    SIT,
    JUMP,
    DROWING,
    SPLAH
} PlayerState;

typedef enum player_dir
{
    UP_DIR,
    RIGHT_DIR,
    DOWN_DIR,
    LEFT_DIR
} PlayerDirection;

typedef struct
{
    Texture2D *texture;
    short lives;
    Input playerInput;
    PlayerState state;
    PlayerDirection direction;
    Vector2 position;
    int offset;
    short currentFrame;
    Camera2D camera;
} Player;

#endif