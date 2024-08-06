#include "terrain.h"
#include "util/tuple.h"
#include "util/resource.h"

#include <stdlib.h>

#define DEFAULT_ROW 40

void initRow(Row *, TerrainType, int, Rectangle);

void initGrassRow(Row *, int, Rectangle);
void initRoadRow(Row *, int, Rectangle);
void initRailRow(Row *, int, Rectangle);
void initDirtRow(Row *, int, Rectangle);
void initWaterRow(Row *, int, Rectangle);

Tuple getNextTerrain(TerrainType, int);

Tuple getNextRoadTerrain(int index);
Tuple getNextGrassTerrain(int index);
Tuple getNextRailTerrain(int index);
Tuple getNextDirtTerrain(int index);
Tuple getNextWaterTerrain(int index);

void drawRow(Row *);

void initRows(Row *rows, int n)
{

    Rectangle position = {0, 1, GetScreenWidth(), DEFAULT_ROW};
    initRow(&rows[0], GRASS, 0, position);
    int index = 0;
    Rectangle cur_position = position;
    for (int i = 1; i < n; i++)
    {
        Tuple tuple = getNextTerrain(rows[i - 1].type, index);
        index = tuple.index;
        cur_position.y += tuple.height;
        initRow(&rows[i], tuple.type, tuple.index, cur_position);
    }
}

void initRow(Row *output, TerrainType type, int index, Rectangle position)
{
    switch (type)
    {
    case GRASS:
        initGrassRow(output, index, position);
        break;
    case ROAD:
        initRoadRow(output, index, position);
        break;
    case RAIL:
        initRailRow(output, index, position);
        break;
    case DIRT:
        initDirtRow(output, index, position);
        break;
    case WATER:
        initWaterRow(output, index, position);
        break;
    default:
        break;
    }
}

void initGrassRow(Row *output, int index, Rectangle position)
{
    output->index = index;
    output->position = position;
    output->type = GRASS;
    output->entity_size=0;
    output->texture = getGfxTexture(GRASS_TYPE, index);
}
void initRoadRow(Row *output, int index, Rectangle position)
{
    output->index = index;
    output->position = position;
    output->type = ROAD;
    output->entity_size=0;
    output->texture = getGfxTexture(ROAD_TYPE, index);
    Entity* entities = (Entity*)malloc(3*sizeof(Entity));
    generateRoadEntities(entities,3,(Vector2){output->position.x,output->position.y},output->index,ROAD);
    output->entity=entities;
    output->entity_size=3;
}
void initRailRow(Row *output, int index, Rectangle position)
{
    output->index = index;
    output->position = position;
    output->type = RAIL;
    output->entity_size=0;
    Entity* entity = (Entity*)malloc(sizeof(Entity));
    generateRailEntities(entity,1,(Vector2){output->position.x,output->position.y},output->index,RAIL);
    output->entity=entity;
    output->entity_size=1;
    output->texture = getGfxTexture(RAIL_TYPE, index);
}
void initDirtRow(Row *output, int index, Rectangle position)
{
    output->index = index;
    output->position = position;
    output->type = DIRT;
    output->entity_size=0;
    output->texture = getGfxTexture(DIRT_TYPE, index);
}
void initWaterRow(Row *output, int index, Rectangle position)
{
    output->index = index;
    output->position = position;
    output->type = WATER;
    output->entity_size=0;
    Entity* entities = (Entity*)malloc(3*sizeof(Entity));
    generateLogEntities(entities,3,(Vector2){output->position.x,output->position.y},output->index,WATER);
    output->texture = getGfxTexture(WATER_TYPE, index);
}

Tuple getNextTerrain(TerrainType type, int index)
{
    switch (type)
    {
    case GRASS:
        return getNextGrassTerrain(index);
        break;
    case ROAD:
        return getNextRoadTerrain(index);
    case RAIL:
        return getNextRailTerrain(index);
    case DIRT:
        return getNextDirtTerrain(index);
    case WATER:
        return getNextWaterTerrain(index);
    default:
        Tuple tuple;
        tuple.index=-1;
        tuple.type=-1;
        tuple.height=0;
        return tuple;
        break;
    }
}

Tuple getNextRoadTerrain(int index)
{
   Tuple tuple;
    tuple.index = index;
    tuple.type = ROAD;
    tuple.height = DEFAULT_ROW;
    if (index == 0)
    {
        tuple.index = 1;
    }
    else
    {
        if (index < 5)
        {
            tuple.index++;
        }
        else
        {
            int prob = GetRandomValue(0, 1);
            if (prob)
            {
                tuple.index = 3;
                tuple.type = RAIL;
                tuple.height = 20;
            }
            else
            {
                tuple.index = 15;
                tuple.type = DIRT;
                tuple.height = 20;
            }
        }
    }

    return tuple;
}

Tuple getNextGrassTerrain(int index)
{
    Tuple tuple;
    tuple.index = index;
    tuple.type = GRASS;
    if (index == 0)
    {
        tuple.type = ROAD;
        tuple.index = 1;
    }
    else
    {
        if (index <= 5)
        {
            tuple.index += 8;
        }
        else
        {
            if (index == 6)
            {
                tuple.index = 7;
            }
            else
            {
                if (index == 7)
                {
                    tuple.index = 15;
                }
                else
                {
                    if (index >= 8 && index <= 14)
                    {
                        tuple.index++;
                    }
                    else
                    {
                        int prob = GetRandomValue(0, 1);
                        if (prob)
                        {
                            tuple.type = WATER;
                            tuple.index = 0;
                        }
                        else
                        {
                            tuple.type = ROAD;
                            tuple.index = 1;
                        }
                    }
                }
            }
        }
    }

    tuple.height = DEFAULT_ROW;
    return tuple;
}
Tuple getNextRailTerrain(int index)
{
    Tuple tuple;
    tuple.index = index;
    tuple.type = RAIL;
    if (index == 3)
    {
        tuple.index = 2;
    }
    else
    {
        if (index < 3 && index > 0)
        {
            tuple.index--;
        }
        else
        {
            tuple.type = ROAD;
            tuple.index = 1;
        }
    }
    tuple.height = DEFAULT_ROW;
    return tuple;
}

Tuple getNextDirtTerrain(int index)
{
    Tuple tuple;
    tuple.index = index;
    tuple.type = DIRT;

    if (index == 15)
    {
        tuple.index = 10;
    }
    else
    {
        if (index >= 7 && index < 14)
        {
            tuple.index++;
        }
        else
        {
            if (index == 14)
            {
                int nextind = GetRandomValue(0, 6);
                tuple.index = nextind;
                tuple.type = DIRT;
            }
            else
            {
                if (index < 6)
                {
                    tuple.type = WATER;
                    tuple.index = 1;
                }
            }
        }
    }

    tuple.height = DEFAULT_ROW;
    return tuple;
}
Tuple getNextWaterTerrain(int index)
{
     Tuple tuple;
    tuple.index = index;
    tuple.type = WATER;
    tuple.height = DEFAULT_ROW;
    if (index < 7)
    {
        tuple.index++;
    }
    else
    {
        int prob = GetRandomValue(0, 1);
        if (prob)
        {
            tuple.type = GRASS;
            tuple.index = 15;
            tuple.height = 20;
        }
        else
        {
            tuple.type = DIRT;
            tuple.index = 15;
            tuple.height = 20;
        }
    }

    return tuple;
}

// Draw
void drawRows(Row *rows, int n)
{
    for (int i = 0; i < n; i++)
    {
        drawRow(&rows[i]);
    }
}

void drawRow(Row *row)
{

    DrawTexture(*row->texture, row->position.x, row->position.y, WHITE);
    for(int i=0;i<row->entity_size;i++){
        DrawTexture(row->entity[i].texture,row->entity[i].position.x,row->entity[i].position.y,WHITE);
    }    
}
