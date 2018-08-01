
#ifndef char_hpp
#define char_hpp

// using SDL and standard IO
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// include header files
#include <textures.hpp>
#include <engine.hpp>
#include <tiles.hpp>

static const float GRAVITY = .25;

class Vector
{
public:
    // init
    Vector();

    // coords
    int x;
    int y;
};

class Zonestate;
class Level;

bool check_collision(SDL_Rect a, SDL_Rect b, Vector* overlap);
bool check_grounded(SDL_Rect a, SDL_Rect b, bool a_color);

typedef enum _CharDir {
    DIR_RIGHT = 0,
    DIR_LEFT
} CharDir;

typedef enum _CharStatus {
    CHAR_IDLE = 0,
    CHAR_RUN,
    CHAR_JUMP,
    CHAR_INACTIVE,
    CHAR_EXITED,
} CharStatus;

typedef enum _ExitDir {
    EXIT_LEFT = 0,
    EXIT_RIGHT,
    EXIT_UP,
    EXIT_DOWN
} ExitDir;

class Dot
{
public:
    Dot(int x, int y, bool color, SDL_Color* palette = NULL);

    bool m_color;

    bool handle_event(SDL_Event &e, Zonestate* zone);
    void update(Zonestate* zone);
    void render(SDL_Rect* camera, Level* lvl);

    void move(int x, int y);

    SDL_Rect get_rect() { return col_rect; }
    int get_dir() { return dir; }
    float get_yvel() { return m_yvel; }
    int get_exit_dir() { return (exited || entering) ? (int) exit_dir : -1; }

    void spring_me(float yvel);

    void exit(ExitDir dir);
    void enter();
    void good_exit();
    bool in_level(Level* lvl);

    bool center(SDL_Rect* end_rect);

    bool snapped;
    // ready for exit
    bool ready;

private:
    // m_status = idle, jump, run, inactive, etc.
    CharStatus m_status;
    // which way is the dot facing?
    CharDir dir;
    // what animation frame is the dot on?
    int jump_start;

    // is the dot jumping?
    int short_hop;
    float m_xvel, m_yvel;
    float true_y;
    bool up, down, left, right;
    bool platform_drop;
    bool exiting, exited, entering;
    ExitDir exit_dir;
    Controller* controller;
    Texture m_tex;
    SDL_Rect col_rect;

    bool crate_col(Zonestate* zone);
};

#endif /* char_hpp */
