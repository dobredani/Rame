#include "GameMenu.h"
#include "fstream"

GameMenu::GameMenu()
{
    sSettingsFileName = "Settings.ini";
    xPlayersCount = 2;
    xDifficulty = GAME_DIFFICULTY_MEDIUM;
    sGameType = "Arcade";

    oPlayer[0]->sName = "Player1";
    oPlayer[0]->xLeftKeyCode=SDLK_a;
    oPlayer[0]->xRightKeyCode=SDLK_z;
    oPlayer[0]->bIsAIplayer=false;

    oPlayer[1]->sName = "Player2";
    oPlayer[1]->xLeftKeyCode=SDLK_l;
    oPlayer[1]->xRightKeyCode=SDLK_p;
    oPlayer[1]->bIsAIplayer=false;


}

GameMenu::~GameMenu()
{
    //dtor
}
