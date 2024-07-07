#include <stdio.h>
#include "terrain.h"

void initRoadRow(Row* output,int index,Rectangle position);
void initGrassRow(Row* output, int index, Rectangle position);
void initRail(Row* output,int index, Rectangle position);
void initDirt(Row* output, int index, Rectangle position);
void initWater(Row* output,int index, Rectangle position);

void initRow(Row* output,TerrainType type, int index, Rectangle position){
    switch (type)
    {
    case ROAD:
        return initRoadRow(output,index,position);
    case GRASS:
        return initGrassRow(output,index,position);
    case RAIL:
        return initRail(output,index,position);
    case DIRT:
        return initDirt(output,index,position);
    case WATER:
        return initWater(output,index,position);
    default:
        break;
    }
    return 0;
}

void initRoadRow(Row* output,int index,Rectangle position){
    char id[130];
    sprintf(id,"../resources/gfx/road/%s%d.png","road",index);
    Texture2D text= LoadTexture(id);

    output->index=index;
    output->position=position;
    output->texture=text;
    output->type=ROAD;
}

void initGrassRow(Row* output,int index,Rectangle position){
    char id[130];
    sprintf(id,"../resources/gfx/grass/%s%d.png","grass",index);
    Texture2D text= LoadTexture(id);

    output->index=index;
    output->position=position;
    output->texture=text;
    output->type=GRASS;
}

void initRail(Row* output,int index, Rectangle position){
    char id[130];
    sprintf(id,"../resources/gfx/rail/%s%d.png","rail",index);
    Texture2D text= LoadTexture(id);

    output->index=index;
    output->position=position;
    output->texture=text;
    output->type=RAIL;
}

void initDirt(Row* output,int index, Rectangle position){
    char id[130];
    sprintf(id,"../resources/gfx/dirt/%s%d.png","dirt",index);
    Texture2D text= LoadTexture(id);

    output->index=index;
    output->position=position;
    output->texture=text;
    output->type=DIRT;
}

void initWater(Row* output, int index, Rectangle position){
    char id[130];
    sprintf(id,"../resources/gfx/water/%s%d.png","water",index);
    Texture2D text= LoadTexture(id);

    output->index=index;
    output->position=position;
    output->texture=text;
    output->type=WATER;
}

void deInitRow(Row* row){
    UnloadTexture(row->texture);
}

void drawRow(Row* row){
    DrawTexture(row->texture,row->position.x,row->position.y,WHITE);
}