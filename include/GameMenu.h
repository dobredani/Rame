#ifndef GAMEMENU_H
#define GAMEMENU_H
#include <string>
#include "PublicStructures.h"

using namespace std;

class GameMenu
{
    public:
        GameMenu();
        ~GameMenu();

        unsigned char GetPlayersCount() { return xPlayersCount; }
        void SetPlayersCount(unsigned char val) { xPlayersCount = val; }
        unsigned char GetDifficulty() { return xDifficulty; }
        void SetDifficulty(unsigned char val) { xDifficulty = val; }
        string GetGameType() { return sGameType; }
        void SetGameType(string val) { sGameType = val; }

    protected:

    private:
        string sSettingsFileName;
        unsigned char xPlayersCount;
        unsigned char xDifficulty;
        string sGameType;
        Player *oPlayer[5];
};

#endif // GAMEMENU_H
