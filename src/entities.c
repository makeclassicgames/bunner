#include "terrain.h"
#include "util/resource.h"

//Entities Speeds
//car Speed (3px /frame)
#define CAR_SPEED 3
//Train Speed (7px/frame)
#define TRAIN_SPEED 7
//Log Speed (1px/frame)
#define LOG_1_SPEED 1
//Log 2 Speed (2px/frame)
#define LOG_2_SPEED 2

//Functions prototypes
//Update Road Entities (cars) positions
//Entities-> entity array as a pointer
//entity_size ->entity array size.
void updateRoadEntities(Entity*,int);
//Update Road Entities (train) positions
//Entities-> entity array as a pointer
//entity_size ->entity array size.
void updateRailEntities(Entity*,int);
//Update Road Entities (logs) positions
//Entities-> entity array as a pointer
//entity_size ->entity array size.
void updateWaterEntities(Entity*,int);

void generateRoadEntities(Entity *output, int entity_size, Vector2 position, int index, TerrainType type)
{

    //if the index is between 1 and 5
    if (index > 1 && index < 5 && type == ROAD)
    {
        //If the index is odd generate the car with left direction.
        if (index % 2 == 0)
        {

            for (int i = 0; i < entity_size; i++)
            {
                //get current car index randomly
                int car_index = GetRandomValue(0, 2);
                output[i].direction = ENT_LEFT;
                output[i].position = (Vector2){position.x + (i * 150.0f), position.y};
                output[i].texture = *getSpriteTexture(CAR_TYPE, 2 * car_index);
            }
        }
        //if the index is even, the car direction is right.
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
    //The train is on index 3
    if (index == 3 && type == RAIL)
    {
        //Geenerate train and direction randomly
        int trainDir = GetRandomValue(0, 1);
        int trainType = GetRandomValue(0, 2);
        output->position = (Vector2){position.x + 150.0f, position.y};
        output->texture = *getSpriteTexture(TRAIN_TYPE, trainDir + trainType);
        output->direction = trainDir;
    }
}

void generateLogEntities(Entity *output, int entity_size, Vector2 position, int index, TerrainType type)
{
    //if the index is between 0 and 7
    if (index >= 0 && index < 7 && type == WATER)
    {
        //generate the logs with direction left or right (index odd or even)
        for (int i = 0; i < entity_size; i++)
        {
            output[i].direction = index % 2 == 0;
            output[i].position = (Vector2){position.x + (i * 150.0f), position.y};
            output[i].texture = *getSpriteTexture(LOG_TYPE, output[i].direction);
        }
    }
}

void updateEntities(Entity* entities,int entity_size,TerrainType type){
    //swith terrain type
    switch (type)
    {
    //Road type
    case ROAD:
        //update all the road entities (cars)
        updateRoadEntities(entities,entity_size);
        break;
    //Rail Type
    case RAIL:
        //update all the road entities (Train)
        updateRailEntities(entities,entity_size);
        break;
    case WATER:
        //Update all the water entities (logs)
        updateWaterEntities(entities,entity_size);
        break;
    default:
        break;
    }
}

void updateRoadEntities(Entity* entities,int n){
    //depends on direction the car update their position using CAR_SPEED
    //if the car is outside the screen, the car appears in the opposite direction
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
    //depends on direction the train update their position using TRAIN_SPEED
    //if the car is outside the screen, the train appears in the opposite direction
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
    //depends on direction the log update their position using LOG_SPEED or LOG2_SPEED (Depends on direction)
    //if the car is outside the screen, the car appears in the opposite direction
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
        //Current car rectangle (hitBox)
        Rectangle carRect =(Rectangle){
            entity.position.x+11,
            entity.position.y+11,
            70,
            29
        };
        //Check Collision
        return CheckCollisionRecs(carRect,playerHitBox);
   }
    bool checkTrainEntitiesCollision(Entity entity, Rectangle playerHitBox){
        //Current train rectangle (hitBox)

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
        //Depends on Log direction calculate the logRect
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
        //Check Collision
        return CheckCollisionRecs(logRect,playerHitBox);
    }