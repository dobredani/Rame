#ifndef GAME_H
#define GAME_H
#include "Worm.h"
#include "SDL.h"
#include "GameMenu.h"

class Game
{


    public:
        Game(unsigned char xPlayers);
        virtual ~Game();
        void SetRenderer(SDL_Renderer* oValue) { oRenderer = oValue;}
        void SetGameMenu(GameMenu* oValue) { oGameMenu = oValue;}
        Worm* SpawnNewWorm(unsigned char xWorm);
        void SpawnWorms();
        void RenderWorms();
        void MoveWorms();
        double SteerWorm(Player* oPlayer);
        void PreCollision();

    protected:

    private:
        Worm *arrWorms[6];
        unsigned char xPlayers;
        SDL_Renderer* oRenderer;
        long long xFramesCount = 0;
        GameMenu *oGameMenu;
        bool CheckPrecollision(Worm *oWorm1, Worm *oWorm2);
};

#endif // GAME_H
