#ifndef RESOURCE_H
#define RESOURCE_H

#include <raylib.h>

//Gfx Types
//Grass Type
#define GRASS_TYPE 0
//Road Type
#define ROAD_TYPE 1
//Rail Type
#define RAIL_TYPE 2
//DIrt Type
#define DIRT_TYPE 3
//Water Type
#define WATER_TYPE 4
//Title Type (Title Screen and Game Over Screen)
#define TITLE_TYPE 5
//SPrites Types
//Car Type
#define CAR_TYPE 0
//Train Type
#define TRAIN_TYPE 1
//Log Type
#define LOG_TYPE 2
//Player Sprites
//Jump
#define PLAYER_JUMP_TYPE 3
//Sit
#define PLAYER_SIT_TYPE 4
//Splat
#define PLAYER_SPLAT_TYPE 5
//Drown.
#define PLAYER_DROWING_TYPE 6

//Init all the textures to VRAM
void initTextures(void);
//Get the current GFX Texture
//TypeIndex-> TypeIndex (ROAD,RAIL,WATER,...)
//Index-> Texture Index (on current Type)
Texture2D *getGfxTexture(int, int);
//Get the current Sprite Texture
//TypeIdex-> TypeIndex (CAR,TRAIN,LOG,...)
//Index-> Texture Index (on current Type)
Texture2D *getSpriteTexture(int, int);
#endif