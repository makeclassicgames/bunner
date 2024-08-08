#include "terrain.h"
#include "util/tuple.h"
#include "util/resource.h"

#include <stdlib.h>

//DEfault row height in pixels
#define DEFAULT_ROW 40

//Functions prototypes
//Init current Row and entities (obstacles)
//Row-> current row pointer
//TerrainType-> current row terrain type.
//index-> current row index.
//position-> current row position
void initRow(Row *, TerrainType, int, Rectangle);

//Init current Grass Row and entities (obstacles)
//Row-> current row pointer
//index-> current row index.
//position-> current row position
void initGrassRow(Row *, int, Rectangle);
//Init current Road Row and entities (obstacles)
//Row-> current row pointer
//index-> current row index.
//position-> current row position
void initRoadRow(Row *, int, Rectangle);
//Init current Rail Row and entities (obstacles)
//Row-> current row pointer
//index-> current row index.
//position-> current row position
void initRailRow(Row *, int, Rectangle);
//Init current Dirt Row and entities (obstacles)
//Row-> current row pointer
//index-> current row index.
//position-> current row position
void initDirtRow(Row *, int, Rectangle);
//Init current Water Row and entities (obstacles)
//Row-> current row pointer
//index-> current row index.
//position-> current row position
void initWaterRow(Row *, int, Rectangle);

//Get next terrain depend on type and current index
//Terraintype-> current terrainTYpe
//Index -> current Index
Tuple getNextTerrain(TerrainType, int);
//Get next Road terrain depend on type and current index
//Index -> current Index
Tuple getNextRoadTerrain(int index);
//Get next Grass terrain depend on type and current index
//Index -> current Index
Tuple getNextGrassTerrain(int index);
//Get next Rail terrain depend on type and current index
//Index -> current Index
Tuple getNextRailTerrain(int index);
//Get next Dirt terrain depend on type and current index
//Index -> current Index
Tuple getNextDirtTerrain(int index);
//Get next Water terrain depend on type and current index
//Index -> current Index
Tuple getNextWaterTerrain(int index);

//De init current row
//row-> current Row
void deInitRow(Row*);

//Draw Current Row
//row-> current Row
void drawRow(Row *);

void initRows(Row *rows, int n)
{
    //Get initial position as Grass0
    Rectangle position = {0, 1, GetScreenWidth(), DEFAULT_ROW};
    initRow(&rows[0], GRASS, 0, position);
    int index = 0;
    Rectangle cur_position = position;
    //For each row generate next terrain depending on earlier terrain and current index
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
    //Depend on terrain type init the current row type
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
    output->entity_size = 0;
    output->texture = getGfxTexture(GRASS_TYPE, index);
}
void initRoadRow(Row *output, int index, Rectangle position)
{
    output->index = index;
    output->position = position;
    output->type = ROAD;
    output->entity_size = 0;
    output->texture = getGfxTexture(ROAD_TYPE, index);
    Entity *entities = (Entity *)malloc(3 * sizeof(Entity));
    generateRoadEntities(entities, 3, (Vector2){output->position.x, output->position.y}, output->index, ROAD);
    output->entity = entities;
    output->entity_size = 3;
}
void initRailRow(Row *output, int index, Rectangle position)
{
    output->index = index;
    output->position = position;
    output->type = RAIL;
    output->entity_size = 0;
    Entity *entity = (Entity *)malloc(sizeof(Entity));
    generateRailEntities(entity, 1, (Vector2){output->position.x, output->position.y}, output->index, RAIL);
    output->entity = entity;
    output->entity_size = 1;
    output->texture = getGfxTexture(RAIL_TYPE, index);
}
void initDirtRow(Row *output, int index, Rectangle position)
{
    output->index = index;
    output->position = position;
    output->type = DIRT;
    output->entity_size = 0;
    output->texture = getGfxTexture(DIRT_TYPE, index);
}
void initWaterRow(Row *output, int index, Rectangle position)
{
    output->index = index;
    output->position = position;
    output->type = WATER;
    output->entity_size = 0;
    output->texture = getGfxTexture(WATER_TYPE, index);
    Entity *entities = (Entity *)malloc(3 * sizeof(Entity));
    generateLogEntities(entities, 3, (Vector2){output->position.x, output->position.y}, output->index, output->type);
    output->entity = entities;
    output->entity_size = 3;
}

void updateRows(Row* rows,int n){
    //Update all the entities for each row
    for(int i=0;i<n;i++){
        updateEntities(rows[i].entity,rows[i].entity_size,rows[i].type);
    }
}
Tuple getNextTerrain(TerrainType type, int index)
{
    //Depends on terrain type, calculate next index and type
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
        tuple.index = -1;
        tuple.type = -1;
        tuple.height = 0;
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
    //if index 0 next index 1
    if (index == 0)
    {
        tuple.index = 1;
    }
    else
    {
        //if index under 5 return next index
        if (index < 5)
        {
            tuple.index++;
        }
        else
        {
            //50% prob rail or dirt
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
    //if index=0 return road 1
    if (index == 0)
    {
        tuple.type = ROAD;
        tuple.index = 1;
    }
    else
    {
        //if index under 5 add 8 to index
        if (index <= 5)
        {
            tuple.index += 8;
        }
        else
        {
            //if index = 6 return 7
            if (index == 6)
            {
                tuple.index = 7;
            }
            else
            {
                //if index = 7 return 15
                if (index == 7)
                {
                    tuple.index = 15;
                }
                else
                {
                    //if index betweeen 8 and 14 return next index
                    if (index >= 8 && index <= 14)
                    {
                        tuple.index++;
                    }
                    else
                    {
                        //50% prob water or Road
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
    //if index = 3 return 2
    if (index == 3)
    {
        tuple.index = 2;
    }
    else
    {
        //if index between 3 and 0 return previous index
        if (index < 3 && index > 0)
        {
            tuple.index--;
        }
        else
        {
            //else return road 1
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

    //if index =15 return 10
    if (index == 15)
    {
        tuple.index = 10;
    }
    else
    {
        //if index between 7 and 14 return next index
        if (index >= 7 && index < 14)
        {
            tuple.index++;
        }
        else
        {
            //if index = 14  return dirt index between 0 and 6
            if (index == 14)
            {
                int nextind = GetRandomValue(0, 6);
                tuple.index = nextind;
                tuple.type = DIRT;
            }
            else
            {
                //if index <6 next is water (1)
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
    //if index under 7, return next index
    if (index < 7)
    {
        tuple.index++;
    }
    else
    {
        //50% prob grass or Dirt
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
int getCurrentActiveRow(Row* rows,int n,Rectangle playerHitBox){
    //Check each row if collides with the player hitBox.
    for(int i=0;i<n;i++){
        if(CheckCollisionRecs(rows[i].position,playerHitBox)){
            return i;
        }
    }
    return -1;
}


void deInitRows(Row* rows, int n){
    //DeInit each Row
    for(int i=0;i<n;i++){
        deInitRow(&rows[i]);
    }
}

void deInitRow(Row* row){

    //Deinit each entity texture from VRAM
    for(int i=0;i<row->entity_size;i++){
        UnloadTexture(row->entity[i].texture);
    }
    //Free entity memory
    free(row->entity);
    //Unload row texture from VRAM
    UnloadTexture(*row->texture);
}

// Draw
void drawRows(Row *rows, int n)
{
    //Draw Each Row
    for (int i = 0; i < n; i++)
    {
        drawRow(&rows[i]);
    }
}

void drawRow(Row *row)
{
    //Draw Row Texture
    DrawTexture(*row->texture, row->position.x, row->position.y, WHITE);
}
