#ifndef TERRAIN_H
#define TERRAIN_H
    #include <raylib.h>

    //Terrain Type Enumeration
    typedef enum terrain_type{
        //Grass
        GRASS,
        //Dirt
        DIRT,
        //Road
        ROAD,
        //Rail
        RAIL,
        //Water
        WATER
    }TerrainType;

    //Current entity (obstacles) direction enumeration
    typedef enum entity_direction{
        //Entity Direction left
        ENT_LEFT,
        //Entity direction right
        ENT_RIGHT
    }EntityDirection;

    //Entity Struct
    typedef struct{
        //Current entity Texture
        Texture2D texture;
        //current entity position
        Vector2 position;
        //Current entity direction
        EntityDirection direction;
    }Entity;

    //Row Struct
    typedef struct{
        //Row terrain type
        TerrainType type;
        //Row index
        int index;
        //Row Position
        Rectangle position;
        //Current entity array (based on entity_size)
        Entity* entity;
        //Entiti array size
        int entity_size;
        //Current row texture
        Texture2D* texture;
    }Row;

    //Init all the current Rows
    //Rows-> row array as a pointer.
    //n -> rows array size
    void initRows(Row*,int);

    //Update all the entities (obstacles)
    //Rows-> row array as a pointer
    //n -> rows array size
    void updateRows(Row*,int);

    //Draw all the rows
    //Rows-> row array as a pointer.
    //n -> row array size.
    void drawRows(Row*,int);

    //Generate all the road type entities (Cars)
    //Entities-> entities array as a pointer.
    //Entities_size-> entities array size.
    //position-> current row position.
    //index -> current row index.
    //TerrainType-> current row terrain type.
    void generateRoadEntities(Entity* ,int ,Vector2 ,int,TerrainType);
    //Generate all the Rail type entities (Train)
    //Entities-> entities array as a pointer.
    //Entities_size-> entities array size.
    //position-> current row position.
    //index -> current row index.
    //TerrainType-> current row terrain type.
    void generateRailEntities(Entity* ,int ,Vector2 ,int,TerrainType);
    //Generate all the Water type entities (Logs)
    //Entities-> entities array as a pointer.
    //Entities_size-> entities array size.
    //position-> current row position.
    //index -> current row index.
    //TerrainType-> current row terrain type.
    void generateLogEntities(Entity* ,int ,Vector2 ,int,TerrainType);
    //Update all the entities position
    //Entities-> entities array as a pointer.
    //entity_size-> entities array size.
    //TerrainType-> current row terrain type.
    void updateEntities(Entity*,int,TerrainType);
    //Get the current active row
    //rows-> rows array as a pointer.
    //n-> rows array size.
    //playerhitbox-> current player hitbox
    int getCurrentActiveRow(Row*,int,Rectangle);
    //Deinit all the rows (free memory and VRAM textures)
    //Rows-> rows array as a pointer.
    //n-> rows array size.
    void deInitRows(Row*, int);

    //Check the current entity (car) collision with the player
    //Entity -> car entity
    //playerHitbox-> current playerHitbox
    bool checkCarEntitiesCollision(Entity , Rectangle);
    //Check the current entity (train) collision with the player
    //Entity -> train entity
    //playerHitbox-> current playerHitbox
    bool checkTrainEntitiesCollision(Entity , Rectangle);
    //Check the current entity (log) collision with the player
    //Entity -> log entity
    //playerHitbox-> current playerHitbox
    bool checkLogEntitiesCollision(Entity , Rectangle);
#endif