#ifndef RESOURCE_H
#define RESOURCE_H

#include <raylib.h>

#define GRASS_TYPE 0
#define ROAD_TYPE 1
#define RAIL_TYPE 2
#define DIRT_TYPE 3
#define WATER_TYPE 4

void initTextures(void);
Texture2D *getGfxTexture(int, int);
Texture2D *getSpriteTexture(int, int);
#endif