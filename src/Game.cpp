#include "Game.h"
#include "GameObject.h"
#include "math.h"
#include "stdio.h"

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

void Game::SpawnGameObjects()
{

    if (xFoodObjects<3) SpawnNewFood(++xFoodObjects);
    if (xCritterObjects<2) SpawnNewCritter(++xCritterObjects);

}

Worm* Game::SpawnNewWorm(unsigned char xWorm)
{
    Worm * oWorm = new Worm;
    oWorm->SetWormIndex(xWorm);
    oWorm->SetDirection(5.2);
    oWorm->SetHeadPos((PrecissionPoint){50 + xWorm*60,100});
    oWorm->SetSpeed(50);
    oWorm->InitialPosition(xPlayers,12);
    oWorm->AddBodyParts(12);

    Texture *oTexture = new Texture(oRenderer);
    oTexture->LoadImage("Images/Worm Sprites.png");

    oWorm->SetTexture(oTexture);
    return oWorm;
}

GameObject* Game::SpawnNewFood(unsigned char xGobject)
{
    GameObject * oGameObject = new GameObject;
    oGameObject->SetIndex(xGobject);
    oGameObject->SetPosition((PrecissionPoint){50 + xGobject*60,100});
    oGameObject->SetDoesDamage(false);
    oGameObject->SetDoesFeed(true);

    Texture *oTexture = new Texture(oRenderer);
    oTexture->LoadImage("Images/Object Sprites.png");

    oGameObject->SetTexture(oTexture);

    oGameObject->oSpriteRect.y = 0 + TEXTURE_BORDER;
    oGameObject->oSpriteRect.x = TEXTURE_BORDER + (int)(xGobject*1.2)%4 * 62;
    oGameObject->oSpriteRect.h = 63 - TEXTURE_BORDER * 2;
    oGameObject->oSpriteRect.w = 63 - TEXTURE_BORDER * 2;

    GameObjects *pFoodObject = lstFoodObjects;

    lstFoodObjects = new GameObjects;
    lstFoodObjects->oGameObject = oGameObject;
    lstFoodObjects->pNext=pFoodObject;

    return oGameObject;
}

GameObject* Game::SpawnNewCritter(unsigned char xGobject)
{
    GameObject * oGameObject = new GameObject;
    oGameObject->SetIndex(xGobject);
    oGameObject->SetPosition((PrecissionPoint){50 + xGobject*60,200});
    oGameObject->SetDoesDamage(true);
    oGameObject->SetDoesFeed(false);
    oGameObject->SetSpeed(25);

    Texture *oTexture = new Texture(oRenderer);
    oTexture->LoadImage("Images/Object Sprites.png");

    oGameObject->SetTexture(oTexture);

    oGameObject->oSpriteRect.y = 0 + TEXTURE_BORDER + 62;
    oGameObject->oSpriteRect.x = TEXTURE_BORDER + (int)(xGobject*1.2)%4 * 62;
    oGameObject->oSpriteRect.h = 63 - TEXTURE_BORDER * 2;
    oGameObject->oSpriteRect.w = 63 - TEXTURE_BORDER * 2;

    GameObjects *pCritterObject = lstCritterObjects;

    lstCritterObjects = new GameObjects;
    lstCritterObjects->oGameObject = oGameObject;
    lstCritterObjects->pNext=pCritterObject;

    return oGameObject;
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

void Game::RenderGameObjects()
{
    GameObjects *pFoodObject = lstFoodObjects;
    while (pFoodObject!=NULL)
    {
        pFoodObject->oGameObject->Render();
        pFoodObject = pFoodObject->pNext;
    }

    GameObjects *pCritterObject = lstCritterObjects;
    while (pCritterObject!=NULL)
    {
        pCritterObject->oGameObject->Render();
        pCritterObject = pCritterObject->pNext;
    }

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

void Game::MoveCritters()
{
    GameObjects *pCritter = lstCritterObjects;
    PrecissionPoint ptClosest;
    double xSpeed;
    double xAngle=0.0;

    while(pCritter!=NULL)
    {
        xSpeed = pCritter->oGameObject->GetSpeed();

        xAngle = AngleTowardsWorm(pCritter->oGameObject);
        pCritter->oGameObject->MoveOffset( 10.0*sin(xAngle)/xSpeed, 10.0*cos(xAngle)/xSpeed);

        pCritter = pCritter->pNext;
    }

}

double Game::AngleTowardsWorm(GameObject *pCritter)
{
    double xShortestDistance ;
    double xDistance;
    double xAngle=0.0;

    xShortestDistance= SCREEN_WIDTH*20;
    for (unsigned int xi = 0; xi<xPlayers; xi++)
        if (arrWorms[xi]!=NULL)
        {
            PrecissionPoint ptClosest2 = arrWorms[xi]->ClosestBodyPart(pCritter->ptPosition);
            xDistance = DistanceBetweenPoints(ptClosest2,pCritter->ptPosition);

            if (xDistance<xShortestDistance)
                {
                    xShortestDistance = xDistance;
                    pCritter->ptClosest.x = ptClosest2.x;
                    pCritter->ptClosest.y = ptClosest2.y;
                    xAngle = GetSegmentAngle(pCritter->ptPosition.x,pCritter->ptPosition.y,pCritter->ptClosest.x,pCritter->ptClosest.y);
                    pCritter->SetDirection(xAngle);
                }
        }
    return xAngle;
}
