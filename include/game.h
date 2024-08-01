#ifndef GAME_H
#define GAME_H
#include "terrain.h"
#include "player.h"

#define MAX_ROWS 100

typedef enum status{
    MENU,
    GAME,
    GAME_OVER
}Status;

struct{
    Player player;
    Status status;
    int activeRow;
    Row rows[MAX_ROWS];
}Game;

#endif