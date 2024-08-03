#ifndef GAME_H
#define GAME_H

#include <raylib.h>

#include "terrain.h"
#include "player.h"


#define MAX_TERRAINS 200

typedef enum state{
    MENU,
    GAME,
    GAME_OVER
}Status;

struct{
    Player player;
    Status status;
    int activeRow;
    //TODO: Terrain Info
    Row rows[MAX_TERRAINS];
}Game;

void initGame(void);

void updateGame(void);
void drawGame(void);

void restartGame(void);

//Input functions

void checkInputs(void);


#endif