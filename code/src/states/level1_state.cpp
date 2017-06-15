
// using SDL and standard IO
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// include headers
#include <states/level1_state.hpp>
#include <states/level7_state.hpp>
#include <states/level8_state.hpp>
#include <states/level6_state.hpp>
#include <states/level2_state.hpp>
#include <states/mainmenu_state.hpp>
#include <states/pausemenu_state.hpp>
#include <char.hpp>
#include <levels.hpp>
#include <engine.hpp>
#include <objects.hpp>
#include <menu.hpp>

void Level1State::init(Engine* game)
{
    // load textures
    load_textures(game);

    // initialize objects
    init_objects(game);

    if (game->read_save() < 1)
    {
        game->save(1);
    }
}

void Level1State::handle_events(Engine* game)
{
    // event handler
    SDL_Event event;

    // handle those events, bruh
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                game->quit();
                break;
        }

        // quit if he pressed escape
        if (!b_char.handle_event(event, this, game))
        {
            Mix_PauseMusic();
            Mix_PlayChannel(-1, game->sound->menu_exit_snd, 0);
            game->push_state(new PauseMenuState);
        }

        w_char.handle_event(event, this, game);

    }

    shiftable = true;
}

void Level1State::update(Engine* game)
{
    // clear the window
    SDL_RenderClear(game->rend);

    // move the square
    if (b_char.status == CHAR_ACTIVE)
        b_char.move(this, game);
    if (w_char.status == CHAR_ACTIVE)
        w_char.move(this, game);

    for (int i = 0; i < crates.size(); i++)
    {
        crates[i]->update();
    }

    // track the player
    camera->track(&b_char.col_rect, &b_char.col_rect);

    // move that camera!
    camera->move(width, height, game);

    interactions(game);
}

void Level1State::draw(Engine* game)
{
    // draw stuff to the screen!
    for (int i = 0; i < (width * height); i++)
    {
        tileset[i]->render(b_char.status, &camera->display, game, &tile_tex);
    }

    for (int i = 0; i < crates.size(); i++)
    {
        crates[i]->render(b_char.status, &camera->display, game, this);
    }

    b_char.render(&camera->display, game);
    b_level_end.render(&camera->display, game);
    SDL_RenderPresent(game->rend);
}

void Level1State::cleanup()
{
    // iterate over all tiles and delete them all
    for (int i = 0; i < width * height; i++)
    {
        if (tileset[i] != NULL)
        {
            delete tileset[i];
            tileset[i] = NULL;
        }
    }

    for (int i = 0; i < crates.size(); i++)
    {
        if (crates[i] != NULL)
        {
            delete crates[i];
            crates.pop_back();
        }
    }

    // free all textures
    b_char_tex.free();
    w_char_tex.free();

}

void Level1State::pause()
{
    return;
}

void Level1State::resume()
{
    return;
}

void Level1State::load_textures(Engine* game)
{
    // LOAD ALL TEXTURES
    if (!b_char_tex.load_tile_sheet("resources/textures/black/b_char.png", game->rend))
    {
        printf("Failed to load black dot texture!\n");
        return;
    }
    if (!tile_tex.load_tile_sheet("resources/textures/tile_sheet.png", game->rend))
    {
        printf("Failed to load tile sheet texture!\n");
        return;
    }
    if (!b_end_tex.load_tile_sheet("resources/textures/black/level_end/black_end.png", game->rend))
    {
        printf("Failed to load black level end texter!\n");
        return;
    }

    // initialize level
    width = 26;
    height = 17;

    path = "resources/level-files/level_01.csv";

    if (!set_tiles(tileset, path, width, height))
    {
        printf("Failed to load level 1 map!\n");
        return;
    }
}

void Level1State::init_objects(Engine* game)
{
    // initialize black dot
    b_char.status = CHAR_ACTIVE;
    b_char.tex = b_char_tex;
    b_char.col_rect.x = 2 * TILE_WIDTH;
    b_char.col_rect.y = 4 * TILE_WIDTH;
    b_char.black = true;

    // initialize black level end
    b_level_end.tex = b_end_tex;
    b_level_end.col_rect.x = 1360;
    b_level_end.col_rect.y = 720;



    camera = new class Camera(game->screen_width, game->screen_height);

}

void Level1State::interactions(Engine* game)
{
    // if both are on level end object
    if(b_level_end.check(b_char.col_rect))
    {
        b_char.center(&b_level_end.col_rect);

        // change state to level 2
        change_state(game, new Level2State);
    }

}