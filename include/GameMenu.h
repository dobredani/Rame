#ifndef GAMEMENU_H
#define GAMEMENU_H
#include <string>
#include "PublicStructures.h"
#include "Texture.h"
#include "SDLWindow.h"

using namespace std;

class GameMenu
{
    public:
        GameMenu();
        ~GameMenu();

        unsigned char GetPlayersCount() { return xPlayersCount; }
        void SetPlayersCount(unsigned char val) { xPlayersCount = val; }
        void SetRenderer(SDL_Renderer* oValue) { oRenderer = oValue;}
        unsigned char GetDifficulty() { return xDifficulty; }
        void SetDifficulty(unsigned char val) { xDifficulty = val; }
        string GetGameType() { return sGameType; }
        void SetGameType(string val) { sGameType = val; }

        bool ClickedNewGame() { if (bNewGame) {bNewGame=false; return true;} else return false;}
        bool ClickedOptions() { if (bOptions) return bOptions;} // bOptions flag will be set to false when the user returns to main menu from the options menu
        bool ClickedExit() { if (bExit) {bExit=false; return true;} else return false;}

        Player* GetPlayer(unsigned char xPlayer);
        void PollEvent(SDL_Event e);
        void ShowMainMenu();
        void ShowOptionsMenu();
    protected:

    private:
        string sSettingsFileName;
        unsigned char xPlayersCount;
        unsigned char xDifficulty;
        string sGameType;
        Player *oPlayer[6];
        SDL_Renderer* oRenderer;

        bool bNewGame = false;
        bool bOptions = false;
        bool bExit = false;

        Texture* buton1_imagine;
        SDL_Rect buton1_rect;

        Texture* buton2_imagine;
        SDL_Rect buton2_rect;

        Texture* buton3_imagine;
        SDL_Rect buton3_rect;
};

#endif // GAMEMENU_H
