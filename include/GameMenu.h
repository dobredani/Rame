#ifndef GAME_MENU_H_INCLUDED
#define GAME_MENU_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
const int SCREEN_WIDTH = 750;
const int SCREEN_HEIGHT = 500;

class Menu
{
public:
    Menu();
    ~Menu();

    void MenuLoop();

private:
    bool quit;
    SDL_Window* window;
    SDL_Surface* ScreenSurface;
    SDL_Renderer* renderer;
    SDL_Event e;

    SDL_Texture* buton1_imagine;
    SDL_Rect buton1_rect;

    SDL_Texture* buton2_imagine;
    SDL_Rect buton2_rect;

    SDL_Texture* buton3_imagine;
    SDL_Rect buton3_rect;
};

#endif // GAME_MENU_H_INCLUDED
