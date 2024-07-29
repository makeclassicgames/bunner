#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

typedef enum player_input{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    INTRO,
    NONE
}Input;

typedef enum player_state{
    SIT,
    JUMP,
    DROWING,
    SPLASH,
}PlayerState;

typedef enum direction{
    UP_DIR,
    RIGHT_DIR,
    DOWN_DIR,
    LEFT_DIR
}PlayerDirection;

typedef struct{
    Texture* texture;
    short lives;
    Input playerInput;
    PlayerState state;
    PlayerDirection direction;
    Vector2 position;
    int offset;
    short currentFrame;
    Camera2D camera;
}Player;

void initPlayer(Player* ,Vector2 ,short);
void updatePlayer(Player* player);
void drawPlayer(Player*);

//Input

Input checkPlayerInput(void);

#endif