#ifndef GAME_H
#define GAME_H

#include <raylib.h>

#include "player.h"
#include "terrain.h"

#define MAX_TERRAINS 100

typedef enum state{
    MENU,
    GAME,
    GAME_OVER
}Status;

struct{
    Player player;
    Status status;
    int currentScroll;
    //TODO: Terrain Info
    Row rows[MAX_TERRAINS];
}Game;

void initGame(void);

void updateGame(void);
void drawGame(void);
#endif