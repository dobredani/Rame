#ifndef SUBMENU_H
#define SUBMENU_H
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "GameMenu.h"
#include "Comenzi.h"
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;

class SubMenu
{
public:
    SubMenu();
    ~SubMenu();

    void SubMenuLoop();

    int nrPlayers=0;
    int Difficulty=0;
    int TypeOfGame=0;
private:
    bool quit;
    SDL_Window* window2;
    SDL_Surface* ScreenSurface;
    SDL_Renderer* renderer;
    SDL_Event e;

    SDL_Texture* jucatori_imagine;
    SDL_Rect jucatori_rect;

    SDL_Texture* dificultate_imagine;
    SDL_Rect dificultate_rect;

    SDL_Texture* tipjoc_imagine;
    SDL_Rect tipjoc_rect;

    SDL_Texture* comenzi_imagine;
    SDL_Rect comenzi_rect;

    SDL_Texture* inapoi_imagine;
    SDL_Rect inapoi_rect;

    SDL_Texture* minus_imagine;
    SDL_Rect minus_rect;

    SDL_Texture* numbers_imagine;
    SDL_Rect numbers_rect;

    SDL_Texture* plus_imagine;
    SDL_Rect plus_rect;

    SDL_Texture* gradinita_imagine;
    SDL_Rect gradinita_rect;

    SDL_Texture* liceu_imagine;
    SDL_Rect liceu_rect;

    SDL_Texture* facultate_imagine;
    SDL_Rect facultate__rect;

    SDL_Texture* arcade_imagine;
    SDL_Rect arcade_rect;

    SDL_Texture* deathmatch_imagine;
    SDL_Rect deathmatch_rect;
};

#endif // SUBMENU_H
