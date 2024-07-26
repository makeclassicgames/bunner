#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

typedef enum player_state{
    ALIVE,
    DROWING,
    SPLASH,
}PlayerState;

typedef enum direction{
    UP,
    RIGHT,
    DOWN,
    LEFT
}PlayerDirection;

typedef struct{
    Texture* texture;
    short lives;
    PlayerState state;
    PlayerDirection direction;
    Vector2 position;
    short currentFrame;
}Player;

void initPlayer(Player* ,Vector2 ,short);
void updatePlayer(Player* player);
void drawPlayer(Player*);

#endif