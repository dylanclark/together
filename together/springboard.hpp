
#ifndef springboard_hpp
#define springboard_hpp

// using SDL and standard IO
#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

// include header files
#include "characters.hpp"
#include "initialization.hpp"
#include "textures.hpp"
#include "collisions.hpp"
#include "tiles.hpp"
#include "camera.hpp"
#include "button.hpp"


// button status constants
const int BOARD_INACTIVE = 0;
const int BOARD_ACTIVATE = 1;
const int BOARD_ACTIVE = 2;
const int BOARD_INACTIVATE = 3;

// animation length
const int BOARD_ANIMATION_LENGTH = 8;

<<<<<<< HEAD
=======
// direction
const int FLIP_LEFT = 0;
const int FLIP_RIGHT = 1;

const int LOCATION = 0;
const int VELOCITY = 1;

>>>>>>> 250bb44... cross layer, bug fixes, levels 1 and 2,

class springboard
{
public:
    // initialize traits
    springboard();
    
    // render the item on the screen
    void render(SDL_Rect* camera, engine* game);
    
    // collision rectangle
    SDL_Rect col_rect;
    
    // texture
    texture tex;
    
    // check for collision with dot
    bool check(SDL_Rect dot_rect);
    
    // activated or not
    bool activated;
    
    // direction
    int direction;
    
    // animation status
    int status;
    
    // frame of animation
    int frame;
    
    // type. can be LOCATION for defualt jumping or VELOCITY for jumping the
    // abount of the dot doing the springing
    int type;
    
    // angle to flip
    double angle = 0.0;
    
    // flip axis point
    SDL_Point* center = NULL;
    
    // flip type
<<<<<<< HEAD
    SDL_RendererFlip flip = SDL_FLIP_NONE;

=======
    SDL_RendererFlip flip_type;
    
    // spring velocity
    float x_spring;
    
    float y_spring;
    
    // default velocity and acceleration constants
    const float SPRING_X_VEL = 0;
    const float SPRING_Y_VEL = 10;
    
    // cross-layer spring logic
    void cross_spring(dot* springer, dot* springee, int type);
>>>>>>> 250bb44... cross layer, bug fixes, levels 1 and 2,
    
};

#endif /* springboard_hpp */
