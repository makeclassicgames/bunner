#ifndef GAME_H
#define GAME_H
#include "terrain.h"
#include "player.h"

//Maximum Generated Rows
#define MAX_ROWS 100

//Game Status Enumeration
typedef enum status{
    //Menu Status
    MENU,
    //Game Status
    GAME,
    //Game Over Status
    GAME_OVER
}Status;

//Game Struct
struct{
    //Player Information
    Player player;
    //Game Status
    Status status;
    //Current activeRow
    int activeRow;
    //Rows Array
    Row rows[MAX_ROWS];
}Game;

#endif