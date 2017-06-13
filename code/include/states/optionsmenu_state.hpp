
#ifndef optionsmenu_state_hpp
#define optionsmenu_state_hpp

// using SDL and standard IO
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// include headers
#include <menus/menu.hpp>
#include <engine/engine.hpp>
#include <engine/gamestate.hpp>
#include <textures/textures.hpp>

class optionsmenu_state : public gamestate
{
public:
    // init and shutdown
    void init(engine* game);
    void cleanup();

    // pause and resume
    void pause();
    void resume();

    // handling control of screen
    void handle_events(engine* game);
    void update(engine* game);
    void draw(engine* game);

    optionsmenu_state() { };

    menu* options_menu = NULL;

    texture volume_slider;
    texture sfx_slider;
    texture controls_button;
    texture back_button;
};

#endif /* optionsmenu_state_hpp */
