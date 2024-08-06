#ifndef RESOURCE_H
#define RESOURCE_H

#include <raylib.h>

#define GRASS_TYPE 0
#define ROAD_TYPE 1
#define RAIL_TYPE 2
#define DIRT_TYPE 3
#define WATER_TYPE 4

#define CAR_TYPE 0
#define TRAIN_TYPE 1
#define LOG_TYPE 2
#define PLAYER_JUMP_TYPE 3
#define PLAYER_SIT_TYPE 4
#define PLAYER_SPLAT_TYPE 5
#define PLAYER_DROWING_TYPE 6

void initTextures(void);
Texture2D *getGfxTexture(int, int);
Texture2D *getSpriteTexture(int, int);
#endif