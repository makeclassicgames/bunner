#ifndef RESOURCES_H
#define RESOURCES_H

#include<raylib.h>
#include "terrain.h"

#define GFX_TYPES 6
#define MAX_TEXTURES 16

#define SPRITE_TYPES 7
#define MAX_SPRITE_TEXTURES 20

#define GRASS_TYPE 0
#define ROAD_TYPE 1
#define DIRT_TYPE 2
#define RAIL_TYPE 3
#define WATER_TYPE 4
#define PAVEMENT_TYPE 5

//Sprites Textures

//Cars
#define CARS_TYPE 0
#define TRAIN_TYPE 1
#define LOG_TYPE 2

//Player
#define PLAYER_JUMP_TYPE 3
#define PLAYER_SIT_TYPE 4
#define PLAYER_SPLAT_TYPE 5
#define PLAYER_DROWING_TYPE 6


void initTextures(void);
Texture getGfxTexture(int, int);
Texture* getSpriteTexture(int,int);

#endif