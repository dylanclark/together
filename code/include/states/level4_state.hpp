
#ifndef Level4State_hpp
#define Level4State_hpp

// using SDL and standard IO
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// include headers
#include <engine.hpp>
#include <char.hpp>
#include <levels.hpp>

class Level4State : public Gamestate, public Levelstate
{
public:
    // init and shutdown
    void init(Engine* game);
    void cleanup();

    // pause and resume
    void pause();
    void resume();

    // handling control of screen
    void handle_events(Engine* game);
    void update(Engine* game);
    void draw(Engine* game);

    Level4State() { };

    // load textures
    void load_textures(Engine* game);

    // init objects
    void init_objects(Engine* game);

    // object interactions
    void interactions(Engine* game);
};

#endif /* Level4State_hpp */
