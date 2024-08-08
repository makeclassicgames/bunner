#include "terrain.h"
#include "util/resource.h"

#define CAR_SPEED 3
#define TRAIN_SPEED 7
#define LOG_1_SPEED 1
#define LOG_2_SPEED 2

void updateRoadEntities(Entity*,int);
void updateRailEntities(Entity*,int);
void updateWaterEntities(Entity*,int);

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

void updateEntities(Entity* entities,int entity_size,TerrainType type){
    switch (type)
    {
    case ROAD:
        updateRoadEntities(entities,entity_size);
        break;
    case RAIL:
        updateRailEntities(entities,entity_size);
        break;
    case WATER:
        updateWaterEntities(entities,entity_size);
        break;
    default:
        break;
    }
}

void updateRoadEntities(Entity* entities,int n){
    for(int i=0;i<n;i++){
        switch (entities[i].direction)
        {
        case ENT_LEFT:
            entities[i].position.x-=CAR_SPEED;
            if(entities[i].position.x<-60)
                entities[i].position.x=511;
            break;
        case ENT_RIGHT:
            entities[i].position.x+=CAR_SPEED;
            if(entities[i].position.x>511)
                entities[i].position.x=-60;
            break;
        default:
            break;
        }
    }
}
void updateRailEntities(Entity* entities,int n){
    for(int i=0;i<n;i++){
        switch (entities[i].direction)
        {
        case ENT_LEFT:
            entities[i].position.x-=TRAIN_SPEED;
            if(entities[i].position.x<-1000)
                entities[i].position.x=511;
            break;
        case ENT_RIGHT:
            entities[i].position.x+=TRAIN_SPEED;
            if(entities[i].position.x>1310)
                entities[i].position.x=-800;
            break;
        default:
            break;
        }
    }
}
void updateWaterEntities(Entity* entities,int n){
    for(int i=0;i<n;i++){
        switch (entities[i].direction)
        {
        case ENT_LEFT:
            entities[i].position.x-=LOG_1_SPEED;
            if(entities[i].position.x<-90){
                entities[i].position.x=534;
            }
            break;
        case ENT_RIGHT:
            entities[i].position.x+=LOG_2_SPEED;
            if(entities[i].position.x>534){
                entities[i].position.x=-84;
            }
            break;
        default:
            break;
        }
    }
}

 bool checkCarEntitiesCollision(Entity entity, Rectangle playerHitBox){
        Rectangle carRect =(Rectangle){
            entity.position.x+11,
            entity.position.y+11,
            70,
            29
        };
        return CheckCollisionRecs(carRect,playerHitBox);
   }
    bool checkTrainEntitiesCollision(Entity entity, Rectangle playerHitBox){
         Rectangle trainRect =(Rectangle){
            entity.position.x+7,
            entity.position.y+11,
            827,
            34
        };
        return CheckCollisionRecs(trainRect,playerHitBox);
    }
    bool checkLogEntitiesCollision(Entity entity, Rectangle playerHitBox){
        Rectangle logRect;

        switch (entity.direction)
        {

        case ENT_LEFT:
            logRect.x=entity.position.x+14;
            logRect.y=entity.position.y+14;
            logRect.width=57;
            logRect.height=31;
            break;
        case ENT_RIGHT:
            logRect.x=entity.position.x+14;
            logRect.y=entity.position.y+12;
            logRect.width=109;
            logRect.height=31;
        default:
            break;
        }

        return CheckCollisionRecs(logRect,playerHitBox);
    }