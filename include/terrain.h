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
    WATER
}TerrainType;

typedef enum car_direction{
    CAR_LEFT=0,
    CAR_RIGHT
}CarDirection;

typedef enum train_direction{
    TRAIN_LEFT=0,
    TRAIN_RIGHT
}TrainDirection;

typedef enum log_direction{
    LOG_RIGHT=0,
    LOG_LEFT
}LogDirection;

typedef struct{
    TerrainType type;
    int index;
    Rectangle position;
    Texture2D texture;
    void* terrainData;
}Row;

typedef struct{
    Texture2D* texture;
    CarDirection direction;
    Rectangle position;
}Car;

typedef struct{
    Texture2D* texture;
    TrainDirection direction;
    Rectangle position;
}Train;

typedef struct{
    Texture2D* texture;
    Rectangle position;
    LogDirection direction;
}Log;


//TODO: Create Update/Draw Functions for each TerrainType
void initRow(Row* output,TerrainType type, int index, Rectangle position);

void drawRow(Row* row);

void deInitRow(Row* row);

#endif