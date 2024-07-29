#include "util/resources.h"
#include <stdio.h>

Texture2D gfxTextures[GFX_TYPES][MAX_TEXTURES];
Texture2D spriteTextures[SPRITE_TYPES][MAX_SPRITE_TEXTURES];

#define GRASS_STR "grass"
#define ROAD_STR "road"
#define DIRT_STR "dirt"
#define RAIL_STR "rail"
#define WATER_STR "water"
#define SLIDE_STR "side"

#define CAR_SRT "car";

#define RESOURCE_FORMAT "../resources/gfx/%s/%s%d.png"

#define SPRITE_RESOURCE_FORMAT "../resources/sprites/%s/%s%d%d.png"
#define SPRITE_PLAYER_FORMAT "../resources/sprites/player/%s%d.png"
void initTextures(void){
    char path[60];
    //Grass
    for(int i=0;i<16;i++){
    
    sprintf(path,RESOURCE_FORMAT,GRASS_STR,GRASS_STR,i);
    gfxTextures[GRASS_TYPE][i]=LoadTexture(path);
    }
    //Road
    for(int i=0;i<6;i++){
    sprintf(path,RESOURCE_FORMAT,ROAD_STR,ROAD_STR,i);
    gfxTextures[ROAD_TYPE][i]=LoadTexture(path);
    }
    //Dirt
    for(int i=0;i<16;i++){
          sprintf(path,RESOURCE_FORMAT,DIRT_STR,DIRT_STR,i);
    gfxTextures[DIRT_TYPE][i]=LoadTexture(path);
    }
    //Rail
    for(int i=0;i<4;i++){
        sprintf(path,RESOURCE_FORMAT,RAIL_STR,RAIL_STR,i);
        gfxTextures[RAIL_TYPE][i]=LoadTexture(path);
    }
    //Water
    for(int i=0;i<8;i++){
        sprintf(path,RESOURCE_FORMAT,WATER_STR,WATER_STR,i);
        gfxTextures[WATER_TYPE][i]=LoadTexture(path);
    }
    //Slide
    for(int i=0;i<3;i++){
          sprintf(path,RESOURCE_FORMAT,"pavement",SLIDE_STR,i);
        gfxTextures[PAVEMENT_TYPE][i]=LoadTexture(path);
    }
    //SPrite Textures
    
    //Car
    int count=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<2;j++){
            sprintf(path,SPRITE_RESOURCE_FORMAT,"car","car",i,j);
            spriteTextures[CARS_TYPE][count]=LoadTexture(path);
            count++;
        }
    }

    //player
    //junp
    for(int i=0;i<4;i++){
        sprintf(path,SPRITE_PLAYER_FORMAT,"jump",i);
        spriteTextures[PLAYER_JUMP_TYPE][i]=LoadTexture(path);
    }
    //sit
    for(int i=0;i<4;i++){
        sprintf(path,SPRITE_PLAYER_FORMAT,"sit",i);
        spriteTextures[PLAYER_SIT_TYPE][i]=LoadTexture(path);
    }
    //splat

    //splash

}

Texture getGfxTexture(int typeIndex, int index){
    return gfxTextures[typeIndex][index];
}

Texture* getSpriteTexture(int typeIndex,int index){
    return &spriteTextures[typeIndex][index];
}
