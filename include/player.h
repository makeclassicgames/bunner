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
    Texture2D* texture;
    short lives;
    PlayerState state;
    PlayerDirection direction;
    Vector2 position;
}Player;

Player* initPlayer(Vector2 position,short lives);
void updatePlayer(Player* player);
void drawPlayer(Player* player);

#endif