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
    oWorm->SetDirection(0.5);
    oWorm->SetHeadPos((SDL_Point){50,100});
    oWorm->SetSpeed(1);
    oWorm->AddBodyParts(8);

    Texture *oTexture = new Texture(oRenderer);
    oTexture->LoadImage("Images/Worm Sprites.png");

    oWorm->SetTexture(oTexture);
    return oWorm;
}

void Game::RenderWorms()
{
    for (unsigned char xi = 0; xi<xPlayers; xi++)
        arrWorms[xi]->Render();
}
