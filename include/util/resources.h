#ifndef RESOURCES_H
#define RESOURCES_H

#include<raylib.h>
#include "terrain.h"

#define GFX_TYPES 6
#define MAX_TEXTURES 16

#define GRASS_TYPE 0
#define ROAD_TYPE 1
#define DIRT_TYPE 2
#define RAIL_TYPE 3
#define WATER_TYPE 4
#define PAVEMENT_TYPE 5


void initTextures(void);
Texture getGfxTexture(int, int);

#endif