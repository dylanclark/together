
#ifndef textures_hpp
#define textures_hpp

// using SDL and standard IO
#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class texture
{
public:
    // initialization
    texture();
    
    // deallocation
    ~texture();
    
    // free the texture
    void free();
    
    // load the texture at the specified path
    bool load_object(int w, int h, std::string path, SDL_Renderer* rend);
    
    // load a tile
    bool load_tile_sheet(std::string path, SDL_Renderer* rend);
    
    // set blending
    void set_blend_mode(SDL_BlendMode blending);
    
    // set alpha
    void set_alpha (Uint8 alpha);
    
    // render the texture at the given point
    void render(int x, int y, SDL_Rect* clip, SDL_Rect* camera, SDL_Renderer* rend);
    
    // render a tile at the given point
    void render_tile(int x, int y, SDL_Rect* type_clip, SDL_Rect* active_clip, SDL_Rect* camera, SDL_Renderer* rend);
    
<<<<<<< HEAD
<<<<<<< HEAD
    // render something at an angle
    void angle_render(int x, int y, SDL_Rect* clip, SDL_Rect* camera, SDL_Renderer* rend, double angle, SDL_Point* center, SDL_RendererFlip flip);
=======
=======
    // render something at an angle
    void angle_render(int x, int y, SDL_Rect* clip, SDL_Rect* camera, SDL_Renderer* rend, double angle, SDL_Point* center, SDL_RendererFlip flip);
    
>>>>>>> 71027e4... Volume / sfx slider adjustment.
    // render a menu button
    void render_button(SDL_Rect* button, SDL_Rect* clip, SDL_Renderer* rend);
    
    // return width and height
    int get_width() {return width;}
    int get_height() {return height;}
>>>>>>> a671362... Implemented main menu, pause menu, and options menu!
    
private:
    
    // the texture itself
    SDL_Texture* tex = NULL;
    
    // dimensions
    int width, height;
};

#endif /* textures_hpp */
