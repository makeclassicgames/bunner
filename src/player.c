#include "player.h"
#include "util/resource.h"

#define PLAYER_SPEED 5

void initCamera(Player*);
void updateCamera(Player*);

Texture2D* getCurrentPlayerTexture(Player*);

Rectangle getCurrentPlayerSitHitBox(Player*);
Rectangle getCurrentPlayerJumpHitBox(Player*);

void initPlayer(Player* player,Vector2 position,short lives){
    player->direction=DOWN_DIR;
    player->state=SIT;
    player->frame=0;
    player->currentFrame=0;
    player->lives=lives;
    player->position=position;
    player->offset=0;
    initCamera(player);
    player->texture=getCurrentPlayerTexture(player);
}

void initCamera(Player* player){
    player->camera.offset=(Vector2){225,0};
    player->camera.target=(Vector2){player->position.x,player->position.y+player->offset};
    player->camera.rotation=0.0f;
    player->camera.zoom=1.0f;
}

void updateCamera(Player* player){
    player->camera.target.y=player->offset;
}

Texture2D* getCurrentPlayerTexture(Player* player){
    switch (player->state)
    {
    case SIT:
        return getSpriteTexture(PLAYER_SIT_TYPE,player->direction);
        break;
    case JUMP:
        return getSpriteTexture(PLAYER_JUMP_TYPE,player->direction);
        break;
    case SPLAH:
        return getSpriteTexture(PLAYER_SPLAT_TYPE,player->direction);
        break;
    case DROWING:
        return getSpriteTexture(PLAYER_DROWING_TYPE,player->currentFrame);
        break;
    default:
        break;
    }
}

void updatePlayer(Player* player){
    player->frame++;
    if(player->state!=SPLAH && player->state!=DROWING){
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

        if(player->frame%10==0 && player->state){
            if(player->state==JUMP){
                player->state=SIT;
            }else{
                player->state=JUMP;
            }
        }
    }else{
        if(player->state==DROWING && player->frame%6==0 && player->currentFrame<7){
            player->currentFrame++;
        }
    }
    updateCamera(player);
    player->texture=getCurrentPlayerTexture(player);
}
void drawPlayer(Player* player){
    for(int i=0;i<player->lives;i++){
        DrawTextureEx(*getSpriteTexture(PLAYER_SIT_TYPE,1), (Vector2){10+(i*30),10},
        0.0f,0.5f,WHITE);
    }
    
    DrawTexture(*player->texture,player->position.x,player->position.y,WHITE);
}

Rectangle getCurrentPlayerHitBox(Player* player){
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