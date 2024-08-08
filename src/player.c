#include "player.h"
#include "util/resource.h"

//Player Speed (pixels/frame)
#define PLAYER_SPEED 5

//Function Prototypes
//Init the player's camera
//Player-> current player pointer
void initCamera(Player*);

//Update the player's camera
//Player-> current player pointer.
void updateCamera(Player*);

//Get the current playerTexture.
//Player-> current player pointer.
Texture2D* getCurrentPlayerTexture(Player*);

//Get the current player hitbox on Sit status
//Player-> current player pointer.
Rectangle getCurrentPlayerSitHitBox(Player*);
//Get the current player hitbox on Jump Status
//Player-> current player pointer
Rectangle getCurrentPlayerJumpHitBox(Player*);

void initPlayer(Player* player,Vector2 position,short lives){
    //Init player struct
    player->direction=DOWN_DIR;
    player->state=SIT;
    player->frame=0;
    player->currentFrame=0;
    player->lives=lives;
    player->position=position;
    player->offset=0;
    //init the player camera
    initCamera(player);
    //get the current player texture
    player->texture=getCurrentPlayerTexture(player);
}

void initCamera(Player* player){
    //init the camera attributes
    player->camera.offset=(Vector2){225,0};
    player->camera.target=(Vector2){player->position.x,player->position.y+player->offset};
    player->camera.rotation=0.0f;
    player->camera.zoom=1.0f;
}

void updateCamera(Player* player){
    //Update camera target y coords.
    player->camera.target.y=player->offset;
}

Texture2D* getCurrentPlayerTexture(Player* player){
    //depends on player state
    switch (player->state)
    {
        //Sit Status
    case SIT:
        return getSpriteTexture(PLAYER_SIT_TYPE,player->direction);
        break;
    //Jump Status
    case JUMP:
        return getSpriteTexture(PLAYER_JUMP_TYPE,player->direction);
        break;
    //SPlash Status
    case SPLAH:
        return getSpriteTexture(PLAYER_SPLAT_TYPE,player->direction);
        break;
    //Drowing Status
    case DROWING:
        return getSpriteTexture(PLAYER_DROWING_TYPE,player->currentFrame);
        break;
    default:
        break;
    }
}

void updatePlayer(Player* player){
    //Update current Frame
    player->frame++;
    //If the player is alive
    if(player->state!=SPLAH && player->state!=DROWING){
        //Depends on player input, update current player status
        switch (player->playerInput)
        {
        case UP:
            player->direction=UP_DIR;
            player->state=JUMP;
            if(player->position.y>0){
                player->position.y-=PLAYER_SPEED;
            }
            if(player->position.y>GetScreenHeight()/2){
                player->offset-=PLAYER_SPEED;
            }
            break;
        case DOWN:
            player->direction=DOWN_DIR;
            player->state=JUMP;
            
            player->position.y+=PLAYER_SPEED;
        
            if(player->position.y>GetScreenHeight()/2){
                player->offset+=PLAYER_SPEED;
            }
            break;
        case LEFT:
            player->direction=LEFT_DIR;
            player->state=JUMP;
            if(player->position.x>0){
                player->position.x-=PLAYER_SPEED;
            }
            break;
         case RIGHT:
            player->direction=RIGHT_DIR;
            player->state=JUMP;
            if(player->position.x<390){
                player->position.x+=PLAYER_SPEED;
            }
            break;
        default:
            break;
        }
        //Update player frame animation
        if(player->frame%10==0 && player->state){
            if(player->state==JUMP){
                player->state=SIT;
            }else{
                player->state=JUMP;
            }
        }
    }else{
        //Update player drowing animation
        if(player->state==DROWING && player->frame%6==0 && player->currentFrame<7){
            player->currentFrame++;
        }
    }
    //Update the current player camera
    updateCamera(player);
    //Update player texture
    player->texture=getCurrentPlayerTexture(player);
}

void drawPlayer(Player* player){
    //Draw current lives (using scale)
    for(int i=0;i<player->lives;i++){
        DrawTextureEx(*getSpriteTexture(PLAYER_SIT_TYPE,1), (Vector2){10+(i*30),10},
        0.0f,0.5f,WHITE);
    }
    //Draw current player texture
    DrawTexture(*player->texture,player->position.x,player->position.y,WHITE);
}

Rectangle getCurrentPlayerHitBox(Player* player){
    //Depends on status, calculate current Player hitbox
    switch (player->state)
    {
    case SIT:
        return getCurrentPlayerSitHitBox(player);
        break;
    case JUMP:
        return getCurrentPlayerJumpHitBox(player);
        break;
    default:
        (Rectangle){
            player->position.x,
            player->position.y,
            player->texture->width,
            player->texture->height
        };
        break;
    }
}

Rectangle getCurrentPlayerSitHitBox(Player* player){
    //Depends on direction, calculate player hitbox for sit status
    switch (player->direction)
    {
    case DOWN_DIR:
    case UP_DIR:
        return (Rectangle){
            player->position.x+25,
            player->position.y+11,
            17,27
        };
        break;
    case LEFT_DIR:
    case RIGHT_DIR:
        return (Rectangle){
            player->position.x+17,
            player->position.y+11,
            23,27
        };
    default:
        break;
    }
}
Rectangle getCurrentPlayerJumpHitBox(Player* player){
    //Depends on direction, calculate player hitbox for Jump status
    switch (player->direction)
    {
    case DOWN_DIR:
    case UP_DIR:
        return (Rectangle){
            player->position.x+23,
            player->position.y+11,
            13,33
        };
        break;
    case LEFT_DIR:
    case RIGHT_DIR:
        return (Rectangle){
            player->position.x+11,
            player->position.y+11,
            37,18
        };
    default:
        break;
    }
}