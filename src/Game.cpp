#include "Game.h"

Game::Game(unsigned char xPlayersCount)
{
    xPlayers = xPlayersCount;
}

Game::~Game()
{
    //dtor
}

void Game::SpawnWorms()
{
    for(unsigned char xi = 0;xi<6;xi++)
        if (xi<xPlayers)
            arrWorms[xi] = SpawnNewWorm(xi);
        else
            arrWorms[xi] = NULL;
}

Worm* Game::SpawnNewWorm(unsigned char xWorm)
{
    Worm * oWorm = new Worm;
    oWorm->SetWormIndex(xWorm);
    oWorm->SetDirection(5.2);
    oWorm->SetHeadPos((PrecissionPoint){250 + xWorm*60,100});
    oWorm->SetSpeed(110);
    oWorm->AddBodyParts(8);

    Texture *oTexture = new Texture(oRenderer);
    oTexture->LoadImage("Images/Worm Sprites.png");

    oWorm->SetTexture(oTexture);
    return oWorm;
}

void Game::RenderWorms()
{
    for (unsigned char xi = 0; xi<xPlayers; xi++)
        {
            arrWorms[xi]->Move(xFramesCount++);
            arrWorms[xi]->Render();
        }
}
