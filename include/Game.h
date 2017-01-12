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
        bool GetGameOver() {return bGameOver;}
        void SetGameOver(bool bValue) {bGameOver = bValue;}

        Worm* SpawnNewWorm(unsigned char xWorm);
        GameObject* SpawnNewFood(unsigned char xGobject);
        GameObject* SpawnNewCritter(unsigned char xGobject);

        void SpawnWorms();
        void SpawnGameObjects();
        void RenderWorms();
        void MoveWorms();
        void PreCollision();
        void MoveCritters();

        double SteerWorm(Player* oPlayer);
        void RenderGameObjects();
    protected:

    private:
        struct GameObjects{
            GameObject *oGameObject;
            GameObjects *pNext;
        };

        Worm *arrWorms[6];
        GameObjects *lstFoodObjects = NULL;
        GameObjects *lstCritterObjects = NULL;

        unsigned char xPlayers;
        SDL_Renderer* oRenderer;
        long long xFramesCount = 0;
        GameMenu *oGameMenu;
        bool bGameOver = true;
        bool CheckPrecollision(Worm *oWorm1, Worm *oWorm2);
        unsigned char xFoodObjects = 0;
        unsigned char xCritterObjects = 0;

        double AngleTowardsWorm(GameObject *pCritter);
};

#endif // GAME_H
