#include "player.h"
#include "util/resources.h"

void initPlayer(Player* player,Vector2 position, short lives){
    player->direction=DOWN;
    player->state=ALIVE;
    player->currentFrame=0;
    player->lives=lives;
    player->position=position;
    player->texture=getSpriteTexture(PLAYER_JUMP_TYPE,0);
}

void drawPlayer(Player* player){
    DrawTexture(*player->texture,player->position.x,player->position.y,WHITE);
}