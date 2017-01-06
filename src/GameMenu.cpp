#include "GameMenu.h"
#include "fstream"

GameMenu::GameMenu()
{
    sSettingsFileName = "Settings.ini";
    xPlayersCount = 2;
    xDifficulty = GAME_DIFFICULTY_MEDIUM;
    sGameType = "Arcade";

    oPlayer[0] = new Player;
    oPlayer[0]->sName = "Player1";
    oPlayer[0]->xLeftKeyCode=SDL_SCANCODE_A;
    oPlayer[0]->xRightKeyCode=SDL_SCANCODE_Z;
    oPlayer[0]->bIsAIplayer=false;

    oPlayer[1] = new Player;
    oPlayer[1]->sName = "Player2";
    oPlayer[1]->xLeftKeyCode=SDL_SCANCODE_L;
    oPlayer[1]->xRightKeyCode=SDL_SCANCODE_P;
    oPlayer[1]->bIsAIplayer=false;

    oPlayer[2] = NULL;
    oPlayer[3] = NULL;
    oPlayer[4] = NULL;
    oPlayer[5] = NULL;

}

GameMenu::~GameMenu()
{
    //dtor
}

Player* GameMenu::GetPlayer(unsigned char xPlayer)
{
    return oPlayer[xPlayer];
}
