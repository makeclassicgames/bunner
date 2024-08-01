#include "util/resource.h"
#include <stdio.h>

#define GFX_TYPES 7
#define MAX_TEXTURES 16
#define SPRT_TYPES 8

#define GFX_PATH_SRT "../resources/gfx/%s/%s%d.png"

Texture2D gfxTextures[GFX_TYPES][MAX_TEXTURES];
Texture2D sprtTextures[SPRT_TYPES][MAX_TEXTURES];

void initTextures(void)
{   
    //Grass
    for(int i=0;i<16;i++){
        char path[60];
        sprintf(path,GFX_PATH_SRT,"grass","grass",i);
        gfxTextures[GRASS_TYPE][i]=LoadTexture(path);
    }
    //Road
    for(int i=0;i<6;i++){
        char path[60];
        sprintf(path,GFX_PATH_SRT,"road","road",i);
        gfxTextures[ROAD_TYPE][i]=LoadTexture(path);
    }
    //Rail
    for(int i=0;i<4;i++){
        char path[60];
        sprintf(path,GFX_PATH_SRT,"rail","rail",i);
        gfxTextures[RAIL_TYPE][i]=LoadTexture(path);
    }
    //Dirt
    for(int i=0;i<16;i++){
        char path[60];
        sprintf(path,GFX_PATH_SRT,"dirt","dirt",i);
        gfxTextures[DIRT_TYPE][i]=LoadTexture(path);
    }
    //Water
    for(int i=0;i<8;i++){
        char path[60];
        sprintf(path,GFX_PATH_SRT,"water","water",i);
        gfxTextures[WATER_TYPE][i]=LoadTexture(path);
    }
}
Texture2D *getGfxTexture(int type, int index)
{
    return &gfxTextures[type][index];
}
Texture2D *getSpriteTexture(int type, int index)
{
    return &sprtTextures[type][index];
}