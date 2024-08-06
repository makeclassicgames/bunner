#ifndef TERRAIN_H
#define TERRAIN_H
    #include <raylib.h>

    typedef enum terrain_type{
        GRASS,
        DIRT,
        ROAD,
        RAIL,
        WATER
    }TerrainType;

    typedef enum entity_direction{
        ENT_LEFT,
        ENT_RIGHT
    }EntityDirection;

    typedef struct{
        Texture2D texture;
        Vector2 position;
        EntityDirection direction;
    }Entity;

    typedef struct{
        TerrainType type;
        int index;
        Rectangle position;
        Entity* entity;
        int entity_size;
        Texture2D* texture;
    }Row;


    void initRows(Row*,int);

    void updateRows(Row*,int);

    void drawRows(Row*,int);

    void generateRoadEntities(Entity* ,int ,Vector2 ,int,TerrainType);
    void generateRailEntities(Entity* ,int ,Vector2 ,int,TerrainType);
    void generateLogEntities(Entity* ,int ,Vector2 ,int,TerrainType);

    void deInitRow(Row* row);
#endif