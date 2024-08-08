#include "util/resource.h"
#include <stdio.h>

//Current Max GFX_TYPEs
#define GFX_TYPES 7
//Current max textures per type
#define MAX_TEXTURES 16
//current sprite types
#define SPRT_TYPES 8

//GFX Path pattern
#define GFX_PATH_SRT "../resources/gfx/%s/%s%d.png"

//Sprite resource path pattern
#define SPRITE_RESOURCE_FORMAT "../resources/sprites/%s/%s%d%d.png"
//Sprite player resource path pattern
#define SPRITE_PLAYER_FORMAT "../resources/sprites/player/%s%d.png"
//Gfx Textures array
Texture2D gfxTextures[GFX_TYPES][MAX_TEXTURES];
//Sprites textures array
Texture2D sprtTextures[SPRT_TYPES][MAX_TEXTURES];

void initTextures(void)
{
    // Grass
    for (int i = 0; i < 16; i++)
    {
        char path[60];
        sprintf(path, GFX_PATH_SRT, "grass", "grass", i);
        gfxTextures[GRASS_TYPE][i] = LoadTexture(path);
    }
    // Road
    for (int i = 0; i < 6; i++)
    {
        char path[60];
        sprintf(path, GFX_PATH_SRT, "road", "road", i);
        gfxTextures[ROAD_TYPE][i] = LoadTexture(path);
    }
    // Rail
    for (int i = 0; i < 4; i++)
    {
        char path[60];
        sprintf(path, GFX_PATH_SRT, "rail", "rail", i);
        gfxTextures[RAIL_TYPE][i] = LoadTexture(path);
    }
    // Dirt
    for (int i = 0; i < 16; i++)
    {
        char path[60];
        sprintf(path, GFX_PATH_SRT, "dirt", "dirt", i);
        gfxTextures[DIRT_TYPE][i] = LoadTexture(path);
    }
    // Water
    for (int i = 0; i < 8; i++)
    {
        char path[60];
        sprintf(path, GFX_PATH_SRT, "water", "water", i);
        gfxTextures[WATER_TYPE][i] = LoadTexture(path);
    }
    //Title and gameover textures
    gfxTextures[TITLE_TYPE][0]=LoadTexture("../resources/gfx/title.png");
    gfxTextures[TITLE_TYPE][1]=LoadTexture("../resources/gfx/gameover.png");
    char path[60];
    //Car
    int count=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<2;j++){
            sprintf(path,SPRITE_RESOURCE_FORMAT,"car","car",i,j);
            sprtTextures[CAR_TYPE][count]=LoadTexture(path);
            count++;
        }
    }
    //train
    count =0;
    for(int i=0;i<3;i++){
        for(int j=0;j<2;j++){
            sprintf(path,SPRITE_RESOURCE_FORMAT,"train","train",i,j);
            sprtTextures[TRAIN_TYPE][count]=LoadTexture(path);
            count++;
        }
    }

    //Logs
    count=0;
    for(int i=0;i<2;i++){
         sprintf(path,SPRITE_RESOURCE_FORMAT,"log","log",0,i);
            sprtTextures[LOG_TYPE][count]=LoadTexture(path);
            count++;
    }
    // Sprites
    // player
    // Jump

    for (int i = 0; i < 4; i++)
    {
        char path[60];
        sprintf(path, SPRITE_PLAYER_FORMAT, "jump", i);
        sprtTextures[PLAYER_JUMP_TYPE][i] = LoadTexture(path);
    }
    // Sit
    for (int i = 0; i < 4; i++)
    {
        char path[60];
        sprintf(path, SPRITE_PLAYER_FORMAT, "sit", i);
        sprtTextures[PLAYER_SIT_TYPE][i] = LoadTexture(path);
    }

    // SPLAT
    for (int i = 0; i < 4; i++)
    {
        char path[60];
        sprintf(path, SPRITE_PLAYER_FORMAT, "splat", i);
        sprtTextures[PLAYER_SPLAT_TYPE][i] = LoadTexture(path);
    }
    // DROWING
    for (int i = 0; i < 8; i++)
    {
        char path[60];
        sprintf(path, SPRITE_PLAYER_FORMAT, "splash", i);
        sprtTextures[PLAYER_DROWING_TYPE][i] = LoadTexture(path);
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