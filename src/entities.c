#include "terrain.h"
#include "util/resource.h"

void generateRoadEntities(Entity *output, int entity_size, Vector2 position, int index, TerrainType type)
{

    if (index > 1 && index < 5 && type == ROAD)
    {
        if (index % 2 == 0)
        {

            for (int i = 0; i < entity_size; i++)
            {
                int car_index = GetRandomValue(0, 2);
                output[i].direction = ENT_LEFT;
                output[i].position = (Vector2){position.x + (i * 150.0f), position.y};
                output[i].texture = *getSpriteTexture(CAR_TYPE, 2 * car_index);
            }
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                int car_index = GetRandomValue(0, 2);
                output[i].direction = ENT_RIGHT;
                output[i].position = (Vector2){position.x + (i * 150.0f), position.y};
                output[i].texture = *getSpriteTexture(CAR_TYPE, (2 * car_index) + 1);
            }
        }
    }
}
void generateRailEntities(Entity *output, int entity_size, Vector2 position, int index, TerrainType type)
{
    if (index == 3 && type == RAIL)
    {
        int trainDir = GetRandomValue(0, 1);
        int trainType = GetRandomValue(0, 2);
        output->position = (Vector2){position.x + 150.0f, position.y};
        output->texture = *getSpriteTexture(TRAIN_TYPE, trainDir + trainType);
        output->direction = trainDir;
    }
}
void generateLogEntities(Entity *output, int entity_size, Vector2 position, int index, TerrainType type)
{
    if (index >= 0 && index < 7 && type == WATER)
    {
        for (int i = 0; i < entity_size; i++)
        {
            output[i].direction = index % 2 == 0;
            output[i].position = (Vector2){position.x + (i * 150.0f), position.y};
            output[i].texture = *getSpriteTexture(LOG_TYPE, output[i].direction);
        }
    }
}