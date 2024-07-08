#include <stdio.h>
#include "util/resources.h"
#include "util/tuple.h"
#include "terrain.h"

#define DEFAULT_ROW 40

void initRow(Row *output, TerrainType type, int index, Rectangle position);
void initRoadRow(Row *output, int index, Rectangle position);
void initGrassRow(Row *output, int index, Rectangle position);
void initRail(Row *output, int index, Rectangle position);
void initDirt(Row *output, int index, Rectangle position);
void initWater(Row *output, int index, Rectangle position);
void initPavement(Row *output, int index, Rectangle position);

Tuple getNextTerrain(TerrainType type, int index);

Tuple getNextGrassTerrain(int index);
Tuple getNextDirtTerrain(int index);
Tuple getNextWaterTerrain(int index);
Tuple getNextRoadTerrain(int index);
Tuple getNextRailTerrain(int index);
Tuple getNextPavementTerrain(int index);

void initRows(Row *rows, int n)
{
    // First Row Grass 0
    Rectangle position = {0, 0, GetScreenWidth(), DEFAULT_ROW};

    initRow(&rows[0], GRASS, 0, position);
    int index = 0;
    for (int i = 1; i < n; i++)
    {
        Tuple tuple = getNextTerrain(rows[i - 1].type, index);
        index = tuple.index;
        Rectangle curr_position = (Rectangle){
            position.x,
            tuple.height * i,
            position.width,
            position.height};
        initRow(&rows[i], tuple.type, tuple.index, curr_position);
    }
}

void initRow(Row *output, TerrainType type, int index, Rectangle position)
{
    switch (type)
    {
    case ROAD:
        return initRoadRow(output, index, position);
    case GRASS:
        return initGrassRow(output, index, position);
    case RAIL:
        return initRail(output, index, position);
    case DIRT:
        return initDirt(output, index, position);
    case WATER:
        return initWater(output, index, position);
    case PAVEMENT:
        return initPavement(output, index, position);
    default:
        break;
    }
    return 0;
}

void initRoadRow(Row *output, int index, Rectangle position)
{

    Texture2D text = getGfxTexture(ROAD_TYPE, index);
    output->index = index;
    output->position = position;
    output->texture = text;
    output->type = ROAD;
}

void initGrassRow(Row *output, int index, Rectangle position)
{

    Texture2D text = getGfxTexture(GRASS_TYPE, index);

    output->index = index;
    output->position = position;
    output->texture = text;
    output->type = GRASS;
}

void initRail(Row *output, int index, Rectangle position)
{

    Texture2D text = getGfxTexture(RAIL_TYPE, index);

    output->index = index;
    output->position = position;
    output->texture = text;
    output->type = RAIL;
}

void initDirt(Row *output, int index, Rectangle position)
{

    Texture2D text = getGfxTexture(DIRT_TYPE, index);

    output->index = index;
    output->position = position;
    output->texture = text;
    output->type = DIRT;
}

void initWater(Row *output, int index, Rectangle position)
{

    Texture2D text = getGfxTexture(WATER_TYPE, index);

    output->index = index;
    output->position = position;
    output->texture = text;
    output->type = WATER;
}

void initPavement(Row *output, int index, Rectangle position)
{

    Texture2D text = getGfxTexture(PAVEMENT_TYPE, index);

    output->index = index;
    output->position = position;
    output->texture = text;
    output->type = PAVEMENT;
}

Tuple getNextTerrain(TerrainType type, int index)
{
    switch (type)
    {
    case GRASS:
        return getNextGrassTerrain(index);
    case DIRT:
        return getNextDirtTerrain(index);
    case WATER:
        return getNextWaterTerrain(index);
    case ROAD:
        return getNextRoadTerrain(index);
    case RAIL:
        return getNextRailTerrain(index);
    case PAVEMENT:
        return getNextPavementTerrain(index);
    default:
        Tuple tuple;
        tuple.type = -1;
        tuple.index = -1;
        return tuple;
        break;
    }
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

Tuple getNextDirtTerrain(int index)
{
    Tuple tuple;
    tuple.index = index;
    tuple.type = DIRT;
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
                        tuple.index = 0;
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
    if(index==3){
        tuple.index=2;
    }else{
        if(index<3 && index>0){
            tuple.index--;
        }else{
            tuple.type=ROAD;
            tuple.index=1;
        }
    }
    tuple.height = DEFAULT_ROW;
    return tuple;
}

Tuple getNextPavementTerrain(int index)
{
    Tuple tuple;
    tuple.index = index;
    tuple.type = PAVEMENT;
    if (index < 2)
    {
        tuple.index++;
    }
    else
    {
        tuple.type = ROAD;
        tuple.index = 0;
    }
    tuple.height = DEFAULT_ROW;
    return tuple;
}

Tuple getNextRoadTerrain(int index)
{
    Tuple tuple;
    tuple.index = index;
    tuple.type = ROAD;
    if (index == 0)
    {
        tuple.index = 1;
    }
    else
    {
        if (index < 5)
        {
            int prob = GetRandomValue(1, 10);
            if (prob < 7)
            {
                tuple.index++;
            }
            else
            {
                if (prob < 8)
                {
                    tuple.type = GRASS;
                    tuple.index = GetRandomValue(0, 6);
                }
                else
                {
                    if (prob < 9)
                    {
                        tuple.type = RAIL;
                        tuple.index = 3;
                    }
                    else
                    {
                        tuple.type = PAVEMENT;
                        tuple.index = 0;
                    }
                }
            }
        }
        else
        {
            int prob2 = GetRandomValue(1, 10);
            if (prob2 < 6)
            {
                tuple.type = GRASS;
                tuple.index = GetRandomValue(0, 6);
            }
            else
            {
                if (prob2 < 9)
                {
                    tuple.type = RAIL;
                    tuple.index = 0;
                }
                else
                {
                    tuple.type = PAVEMENT;
                    tuple.index = 0;
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
    int prob = GetRandomValue(0, 1);
    if (index == 7 || (index >= 1 && prob))
    {
        tuple.type = DIRT;
        tuple.index = GetRandomValue(4, 6);
    }
    else
    {
        tuple.index++;
    }
    tuple.height = DEFAULT_ROW;
    return tuple;
}

void deInitRow(Row *row)
{
    UnloadTexture(row->texture);
}

void drawRow(Row *row)
{
    DrawTexture(row->texture, row->position.x, row->position.y, WHITE);
}