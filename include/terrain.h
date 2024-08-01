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

    typedef struct{
        TerrainType type;
        int index;
        Rectangle position;
        Texture2D* texture;
    }Row;


    void initRows(Row*,int);

    void updateRows(Row*,int);

    void drawRows(Row*,int);

    void deInitRow(Row* row);
#endif