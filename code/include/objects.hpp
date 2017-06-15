
#ifndef object_hpp
#define object_hpp

// using SDL and standard IO
#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// include header files
#include <textures.hpp>
#include <char.hpp>
#include <engine.hpp>

typedef enum _buttonstatus {
    BUTT_INACTIVE = 0,
    BUTT_ACTIVATE = 1,
    BUTT_ACTIVE = 2,
    BUTT_INACTIVATE = 3
} buttonstatus;

#define BUTT_ANIMATION_LENGTH 4

typedef enum _directions {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
} directions;

typedef enum _cratetype {
    FOUR_BY_TWO = 0,
    FOUR_BY_ONE = 1,
    TWO_BY_TWO = 2,
    THREE_BY_TWO = 3
} cratetype;

// max number of tiles that this crate will need to render
#define MAX_BORDER 12

typedef enum _springstatus {
    BOARD_INACTIVE = 0,
    BOARD_ACTIVATE = 1,
    BOARD_ACTIVE = 2,
    BOARD_INACTIVATE = 3
} springstatus;

#define BOARD_ANIMATION_LENGTH 7
#define SPRING_X_VEL 0
#define SPRING_Y_VEL 10

// direction
typedef enum _flipdir {
    FLIP_LEFT = 0,
    FLIP_RIGHT = 1
} flipdir;

const int LOCATION = 0;
const int VELOCITY = 1;

class Button
{
public:
    Button();

    void render(SDL_Rect* camera, Engine* game);

    double angle;
    SDL_Point* center;
    SDL_RendererFlip flip;
    SDL_Rect col_rect;

    Texture tex;

    bool check(SDL_Rect dot_rect);

    bool activated;
    bool single;
    bool used;
    int direction;
    int status;
    int frame;
};

class Crate
{
public:
    float x_vel;
    SDL_Rect get_col_rect() { return col_rect; };
    bool check_col(SDL_Rect crate, Levelstate* level, Vector* repos);
    void update();
    void render(int b_status, SDL_Rect* camera, Engine* game, Levelstate* level);

    Texture tex;
    int crate_type;
    bool black;
    bool pushed;

    Crate(int x, int y, int type);

    Tile* tileset[MAX_BORDER];
    void create_tiles(int b_status, Levelstate* level);
    bool generating;

    int tile_type_top(int type);
    int tile_type_bottom(int type);
    int tile_type_left(int type);
    int tile_type_right(int type);

    SDL_Rect col_rect;
};

class Springboard
{
public:
    Springboard();

    void render(SDL_Rect* camera, Engine* game);
    SDL_Rect col_rect;
    Texture tex;

    bool check(SDL_Rect dot_rect);

    bool activated;
    bool show;
    int direction;
    int status;
    int frame;

    // type. can be LOCATION for defualt jumping or VELOCITY for jumping the
    // abount of the dot doing the springing
    int type;
    double angle;
    SDL_Point* center;
    SDL_RendererFlip flip_type;

    float x_spring;
    float y_spring;

    // cross-layer spring logic
    void cross_spring(Dot* springer, Dot* springee, int type);

};

#endif /* object_hpp */