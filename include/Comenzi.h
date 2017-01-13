#ifndef COMENZI_H
#define COMENZI_H
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "GameMenu.h"
#include "SubMenu.h"
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;

class Comenzi
{
public:
    Comenzi();
    virtual ~Comenzi();

    void ComenziLoop();

    int nrPlayers=0;
    int Difficulty=0;
    int TypeOfGame=0;

private:
    bool quit;
    SDL_Window* window;
    SDL_Surface* ScreenSurface;
    SDL_Renderer* renderer;
    SDL_Event e;

    SDL_Texture* jucator1_imagine;
    SDL_Rect jucator1_rect;

    SDL_Texture* jucator2_imagine;
    SDL_Rect jucator2_rect;

    SDL_Texture* jucator3_imagine;
    SDL_Rect jucator3_rect;

    SDL_Texture* jucator4_imagine;
    SDL_Rect jucator4_rect;

    SDL_Texture* jucator5_imagine;
    SDL_Rect jucator5_rect;

    SDL_Texture* jucator6_imagine;
    SDL_Rect jucator6_rect;

    SDL_Texture* a_imagine;
    SDL_Rect a_rect;

    SDL_Texture* z_imagine;
    SDL_Rect z_rect;

    SDL_Texture* p_imagine;
    SDL_Rect p_rect;

    SDL_Texture* l_imagine;
    SDL_Rect l_rect;

    SDL_Texture* left_imagine;
    SDL_Rect left__rect;

    SDL_Texture* right_imagine;
    SDL_Rect right_rect;

    SDL_Texture* c_imagine;
    SDL_Rect c_rect;

    SDL_Texture* v_imagine;
    SDL_Rect v_rect;

    SDL_Texture* n_imagine;
    SDL_Rect n_rect;

    SDL_Texture* m_imagine;
    SDL_Rect m_rect;

    SDL_Texture* r_imagine;
    SDL_Rect r_rect;

    SDL_Texture* t_imagine;
    SDL_Rect t_rect;

    SDL_Texture* inapoi_imagine;
    SDL_Rect inapoi_rect;

};

#endif // COMENZI_H
