#ifndef TERRAIN_H
#define TERRAIN_H

#include <raylib.h>


#define MAX_CARS 5
#define MAX_EAGLES 2
#define MAX_LOGS 4

typedef enum terrain_type{
    GRASS,
    DIRT,
    ROAD,
    RAIL,
    WATER,
    PAVEMENT
}TerrainType;

typedef enum entity_direction{
    ENTITY_LEFT=0,
    ENTITY_RIGHT
}EntityDirection;

typedef struct {
    Texture2D texture;
    Vector2 position;
    EntityDirection direction;
}Entity;

typedef struct{
    TerrainType type;
    int index;
    Rectangle position;
    Texture2D texture;
    Entity* entities;
    int entity_size;
}Row;





void initRows(Row* rows, int n);

void updateRows(Row* row,int n);

void drawRows(Row* row,int n);

void deInitRow(Row* row);

//Generate Entities

void generateRoadEntities(Entity* output, int entity_size,Vector2 position,int index,TerrainType type);
void generateTrainEntities(Entity* output, int entity_size,Vector2 position,int index,TerrainType type);
void generateLogEntities(Entity* output, int entity_size,Vector2 position,int index,TerrainType type);

//Update Entities

//CheckCollisionsEntities

#endif