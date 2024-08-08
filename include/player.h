#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

//Player Input Enumeration
typedef enum player_input
{
    //Up
    UP,
    //Down
    DOWN,
    //left
    LEFT,
    //right
    RIGHT,
    //Enter
    INTRO,
    //No Button Pressed
    NONE
} Input;

//Player Status Enumeration
typedef enum player_status
{
    //Sit (no movement)
    SIT,
    //Jump (Movement)
    JUMP,
    //Drowing (on water)
    DROWING,
    //Splash (collided with car or train)
    SPLAH
} PlayerState;

//Player Direction enumeration
typedef enum player_dir
{
    UP_DIR,
    RIGHT_DIR,
    DOWN_DIR,
    LEFT_DIR
} PlayerDirection;

//Player Struct
typedef struct
{
    //Current Player's Texture
    Texture2D *texture;
    //Player's remain Lives
    short lives;
    //Current Input
    Input playerInput;
    //Player's State
    PlayerState state;
    //Player's Direction
    PlayerDirection direction;
    //Current Position
    Vector2 position;
    //CUrrent offset (for camera scrolling)
    int offset;
    //Current frame counter
    int frame;
    //Current animation frame (For Drowing animation)
    short currentFrame;
    //Player's camera
    Camera2D camera;
} Player;

//Init the current player
//Player-> current player pointer.
//Vector2 (position)-> initial player position.
//lives-> initial player lives.
void initPlayer(Player*,Vector2,short);

//Update the player's logic.
//Player-> current player pointer
void updatePlayer(Player*);
//Draw Current player
//Player-> current player pointer.
void drawPlayer(Player*);

//Check the current player input from gamepad or keyboard
//Return current player input (based on PlayerInput enumeration)
Input checkPlayerInput(void);

//Get the current player hitbox
//Player -> current player pointer.
Rectangle getCurrentPlayerHitBox(Player*);

#endif