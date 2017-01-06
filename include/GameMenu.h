#ifndef GAME_MENU_H_INCLUDED
#define GAME_MENU_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
//#include "PublicStructures.h"
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

    /*public:
        GameMenu();
        ~GameMenu();

        unsigned char GetPlayersCount() { return xPlayersCount; }
        void SetPlayersCount(unsigned char val) { xPlayersCount = val; }
        unsigned char GetDifficulty() { return xDifficulty; }
        void SetDifficulty(unsigned char val) { xDifficulty = val; }
        string GetGameType() { return sGameType; }
        void SetGameType(string val) { sGameType = val; }

        Player* GetPlayer(unsigned char xPlayer);
    protected:

    private:
        string sSettingsFileName;
        unsigned char xPlayersCount;
        unsigned char xDifficulty;
        string sGameType;
        Player *oPlayer[5];*/
};

#endif // GAME_MENU_H_INCLUDED
