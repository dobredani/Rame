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
    oWorm->SetHeadPos((PrecissionPoint){50 + xWorm*60,100});
    oWorm->SetSpeed(80);
    oWorm->AddBodyParts(6);

    Texture *oTexture = new Texture(oRenderer);
    oTexture->LoadImage("Images/Worm Sprites.png");

    oWorm->SetTexture(oTexture);
    return oWorm;
}

double Game::SteerWorm(Player* oPlayer)
{
    if (oPlayer == NULL) return 0;

    const unsigned char *arrKeybState = SDL_GetKeyboardState(NULL);
    if (arrKeybState[oPlayer->xLeftKeyCode]) return -0.7;
    if (arrKeybState[oPlayer->xRightKeyCode]) return 0.7;
    return 0;

    if (arrKeybState[SDL_SCANCODE_RIGHT] && arrKeybState[SDL_SCANCODE_UP]) {
    }

}

void Game::RenderWorms()
{
    for (unsigned char xi = 0; xi<xPlayers; xi++)
        {
            arrWorms[xi]->Move(SteerWorm(oGameMenu->GetPlayer(xi)),++xFramesCount);
            arrWorms[xi]->Render();
        }
}

