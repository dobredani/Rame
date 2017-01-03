#ifndef GAME_H
#define GAME_H
#include "Worm.h"
#include "SDL.h"

class Game
{


    public:
        Game(unsigned char xPlayers);
        virtual ~Game();
        void SetRenderer(SDL_Renderer* oValue) { oRenderer = oValue;}
        Worm* SpawnNewWorm(unsigned char xWorm);
        void SpawnWorms();
        void RenderWorms();
    protected:

    private:
        Worm *arrWorms[6];
        unsigned char xPlayers;
        SDL_Renderer* oRenderer;
        long long xFramesCount = 0;
};

#endif // GAME_H
