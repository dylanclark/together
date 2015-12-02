
#ifndef quitmenu_state_hpp
#define quitmenu_state_hpp

// using SDL and standard IO
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

// include headers
#include "menu.hpp"
#include "engine.hpp"
#include "gamestate.hpp"
#include "textures.hpp"

class quitmenu_state : public gamestate
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
    
    quitmenu_state() { };
    
    menu* quit_menu = nullptr;
    
    texture quit_title;
    texture yes_button;
    texture no_button;
};

#endif /* mainmenu_state_hpp */
