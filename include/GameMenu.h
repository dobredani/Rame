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

    int nrPlayers = 0;
    int Difficulty = 0;
    int TypeOfGame = 0;
    unsigned char GetPlayersCount()
    {
        return xPlayersCount;
    }
    void SetPlayersCount(unsigned char val)
    {
        xPlayersCount = val;
    }
    void SetRenderer(SDL_Renderer* oValue)
    {
        oRenderer = oValue;
    }
    unsigned char GetDifficulty()
    {
        return xDifficulty;
    }
    void SetDifficulty(unsigned char val)
    {
        xDifficulty = val;
    }
    string GetGameType()
    {
        return sGameType;
    }
    void SetGameType(string val)
    {
        sGameType = val;
    }

    bool ClickedNewGame()
    {
        if (bNewGame)
        {
            bNewGame=false;
            return true;
        }
        else return false;
    }
    bool ClickedOptions()
    {
        if (bOptions) return bOptions;   // bOptions flag will be set to false when the user returns to main menu from the options menu
    }
    bool ClickedCommands()
    {
        if (bCommands) return bCommands;
    }
    bool ClickedExit()
    {
        if (bExit)
        {
            bExit=false;
            return true;
        }
        else return false;
    }

    Player* GetPlayer(unsigned char xPlayer);
    void PollEvent(SDL_Event e);
    void ShowMainMenu();
    void ShowOptionsMenu();
    void ShowCommandsMenu();
    void OptionsPollEvent(SDL_Event e);
    void CommandsPollEvent(SDL_Event e);
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
    bool bCommands = false;
    bool bExit = false;

    SDL_Texture* buton1_imagine;
    SDL_Rect buton1_rect;

    SDL_Texture* buton2_imagine;
    SDL_Rect buton2_rect;

    SDL_Texture* buton3_imagine;
    SDL_Rect buton3_rect;

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
    SDL_Rect facultate_rect;

    SDL_Texture* arcade_imagine;
    SDL_Rect arcade_rect;

    SDL_Texture* deathmatch_imagine;
    SDL_Rect deathmatch_rect;

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
};

#endif // GAMEMENU_H
