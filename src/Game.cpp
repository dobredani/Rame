#include "Game.h"

Game::Game(unsigned char xPlayersCount)
{
    xPlayers = xPlayersCount;
}

Game::~Game()
{
    //dtor
    xPlayers = 0;
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
    oWorm->InitialPosition(xPlayers,12);
    oWorm->AddBodyParts(12);

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

void Game::MoveWorms()
{
    for (unsigned char xi = 0; xi<xPlayers; xi++)
        arrWorms[xi]->Move(SteerWorm(oGameMenu->GetPlayer(xi)),++xFramesCount);
}

void Game::RenderWorms()
{
    for (unsigned char xi = 0; xi<xPlayers; xi++)
        arrWorms[xi]->Render();
}

bool Game::CheckPrecollision(Worm *oWorm1, Worm *oWorm2)
{
    if (oWorm1->GetPreCollisionBox().x > oWorm2->GetPreCollisionBox().x + oWorm2->GetPreCollisionBox().w) return false;
    if (oWorm1->GetPreCollisionBox().y > oWorm2->GetPreCollisionBox().y + oWorm2->GetPreCollisionBox().h) return false;
    if (oWorm1->GetPreCollisionBox().x + oWorm1->GetPreCollisionBox().w < oWorm2->GetPreCollisionBox().x) return false;
    if (oWorm1->GetPreCollisionBox().y + oWorm1->GetPreCollisionBox().h < oWorm2->GetPreCollisionBox().y) return false;
    return true;
}

void Game::PreCollision()
{
    for (unsigned char xi = 0; xi<xPlayers; xi++)
        arrWorms[xi]->SetInPreCollision(false);

    for (unsigned char xi = 0; xi<xPlayers; xi++)
    {
        if (! arrWorms[xi]->GetInPreCollision()) arrWorms[xi]->SetPreCollisionBoxColor((SDL_Color){0x00,0xFF,0x00,0xFF});

        for (unsigned char yi = xi+1; yi<xPlayers; yi++)
            if (CheckPrecollision(arrWorms[xi], arrWorms[yi]))
            {
                arrWorms[xi]->SetPreCollisionBoxColor((SDL_Color){0xFF,0x00,0x00,0xFF});
                arrWorms[yi]->SetPreCollisionBoxColor((SDL_Color){0xFF,0x00,0x00,0xFF});
                arrWorms[xi]->SetInPreCollision(true);
                arrWorms[yi]->SetInPreCollision(true);
            }
    }
}
