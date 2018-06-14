// using SDL and standard IO
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// include header file
#include <levels.hpp>
#include <textures.hpp>

// external variables
extern Texture tile_tex;
extern SDL_Rect tile_clips[];

Tile::Tile(int x, int y, int tile_type)
{
    // set position
    col_rect.x = x;
    col_rect.y = y;

    // set collision box size
    col_rect.w = TILE_WIDTH;
    col_rect.h = TILE_WIDTH;

    // set tile type
    type = tile_type;

    // set activity
    if (type >= 0 && type <= 14)
    {
        status = TILE_ACTIVE;
        frame = 0;
    }
    else if (type >= 15 && type <= 29)
    {
        status = TILE_INACTIVE;
        frame = TILE_FRAMES - 1;
    }
    // animation DEBUG
    animating = false;

    // start with this
    floor = wall = ceiling = false;

    // define floor properties (corners to come to smooth some stuff out, biznatches)
    switch (type)
    {
        case B_FLOOR1:
        case B_FLOOR2:
        case B_FLOOR3:
            floor = true;
            break;
        case B_FLOOREDGE_L:
        case B_FLOOREDGE_R:
            floor = true;
            wall = true;
            break;
        case B_WALL_L:
        case B_WALL_R:
            wall = true;
            break;
        case B_CEILING:
            ceiling = true;
            break;
        case B_CEILINGEDGE_L:
        case B_CEILINGEDGE_R:
            ceiling = true;
            wall = true;
            break;
        case W_FLOOR1:
        case W_FLOOR2:
        case W_FLOOR3:
            floor = true;
            break;
        case W_FLOOREDGE_L:
        case W_FLOOREDGE_R:
            floor = true;
            wall = true;
            break;
        case W_WALL_L:
        case W_WALL_R:
            wall = true;
            break;
        case W_CEILING:
            ceiling = true;
            break;
        case W_CEILINGEDGE_L:
        case W_CEILINGEDGE_R:
            ceiling = true;
            wall = true;
            break;
    }
    my_color = (type >= W_BACK);
}

// collision rectangle accessor
int Tile::get_type() {
    return type;
}

// collision rectangle accessor
SDL_Rect Tile::get_col_rect() {
    return col_rect;
}


// render tile
void Tile::render(int active_color, SDL_Rect* camera, Engine* game, Texture* tile_tex)
{
    status = (my_color == active_color) ? TILE_ACTIVE : TILE_INACTIVE;

    // activity clippers
    SDL_Rect active_clip = {0, 0, TILE_WIDTH_TEX, TILE_WIDTH_TEX};
    SDL_Rect inactive_clip = {TILE_WIDTH_TEX * (TILE_FRAMES - 1), 0, TILE_WIDTH_TEX, TILE_WIDTH_TEX};

    switch (status)
    {
        // animating cases
        case TILE_ACTIVE:
            tile_tex->render_tile(col_rect.x, col_rect.y, &tile_clips[type], &active_clip, camera, game);
            frame = 0;
            break;
        case TILE_INACTIVE:
            tile_tex->render_tile(col_rect.x, col_rect.y, &tile_clips[type], &inactive_clip, camera, game);
            frame = TILE_FRAMES - 1;
            break;
        case TILE_INACTIVATE:
        {
            // start animation (if necessary)
            if (!animating && frame <= 0)
            {
                animating = true;
            }

            // next frame!
            frame++;

            // sprite sheet clipper
            SDL_Rect inactivate_clip = {TILE_WIDTH_TEX * frame, 0, TILE_WIDTH_TEX, TILE_WIDTH_TEX};
            tile_tex->render_tile(col_rect.x, col_rect.y, &tile_clips[type], &inactivate_clip, camera, game);

            // change the status if animation is over!
            if (frame >= TILE_FRAMES - 1) {
                animating = false;
                status = TILE_INACTIVE;
            }
            break;
        }
        case TILE_ACTIVATE:
        {
            // start animation (if necessary)
            if (!animating && frame >= TILE_FRAMES - 1)
            {
                animating = true;
                frame = TILE_FRAMES;
            }

            // next frame!
            frame--;

            // sprite sheet clipper
            SDL_Rect activate_clip = {TILE_WIDTH_TEX * frame, 0, TILE_WIDTH_TEX, TILE_WIDTH_TEX};

            // render that
            tile_tex->render_tile(col_rect.x, col_rect.y, &tile_clips[type], &activate_clip, camera, game);

            // change the status if animation is over!
            if (frame <= 1)
            {
                animating = false;
                status = TILE_ACTIVE;
            }
            break;
        }
    }
}
