#include <stdio.h>
#include <stdlib.h>
#include "terrain.h"
#include "util/resources.h"
#include "util/tuple.h"

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

void updateRow(Row *row);

void drawRow(Row *);

void initRows(Row *rows, int n)
{
    // First Row Grass 0
    Rectangle position = {0, 0, GetScreenWidth(), DEFAULT_ROW};

    initRow(&rows[0], GRASS, 0, position);
    int index = 0;
    Rectangle curr_position = position;
    for (int i = 1; i < n; i++)
    {

        Tuple tuple = getNextTerrain(rows[i - 1].type, index);
        index = tuple.index;
        curr_position.y += tuple.height;
        initRow(&rows[i], tuple.type, tuple.index, curr_position);
    }
}

void initRow(Row *output, TerrainType type, int index, Rectangle position)
{
    switch (type)
    {
    case ROAD:
        initRoadRow(output, index, position);
        break;
    case GRASS:
        initGrassRow(output, index, position);
        break;
    case RAIL:
        initRail(output, index, position);
        break;
    case DIRT:
        initDirt(output, index, position);
        break;
    case WATER:
        initWater(output, index, position);
        break;
    case PAVEMENT:
        initPavement(output, index, position);
        break;
    default:
        break;
    }
}

void initRoadRow(Row *output, int index, Rectangle position)
{

    Texture2D text = getGfxTexture(ROAD_TYPE, index);
    output->index = index;
    output->position = position;
    output->texture = text;
    output->type = ROAD;
    output->entity_size = 0;
    Entity *entities = (Entity *)malloc(3 * sizeof(Entity));
    generateRoadEntities(entities, 3, (Vector2){output->position.x, output->position.y}, output->index, output->type);
    output->entities = entities;
    output->entity_size = 3;
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
    output->entity_size = 0;
    Entity *entity = (Entity *)malloc(sizeof(Entity));
    generateTrainEntities(entity, 1, (Vector2){output->position.x, output->position.y}, output->index, output->type);
    output->entities = entity;
    output->entity_size = 1;
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
    output->entity_size = 0;
    Entity *entities = (Entity *)malloc(3 * sizeof(Entity));
    generateLogEntities(entities, 3, (Vector2){output->position.x, output->position.y}, output->index, output->type);
    output->entities = entities;
    output->entity_size = 3;
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

void deInitRow(Row *row)
{
    for (int i = 0; i < row->entity_size; i++)
    {
        UnloadTexture(row->entities[i].texture);
    }
    free(row->entities);
    UnloadTexture(row->texture);
}

// Update
void updateRows(Row *rows, int n)
{

    for (int i = 0; i < n; i++)
    {
        updateRow(&rows[i]);
    }
}

void updateRow(Row* row){
    updateEntities(row->entities,row->entity_size,row->type);
}

void drawRows(Row *rows, int n)
{
    for (int i = 0; i < n; i++)
    {
        drawRow(&rows[i]);
    }
    // Draw Entities
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < rows[i].entity_size; j++)
        {
            DrawTexture(rows[i].entities[j].texture, rows[i].entities[j].position.x, rows[i].entities[j].position.y, WHITE);
        }
    }
}

void drawRow(Row *row)
{
    DrawTexture(row->texture, row->position.x, row->position.y, WHITE);
}
