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

    if (xFoodObjects<5) SpawnNewFood(++xFoodObjects);
    if (xCritterObjects<2) SpawnNewCritter(++xCritterObjects);

}

Worm* Game::SpawnNewWorm(unsigned char xWorm)
{
    Worm * oWorm = new Worm;
    oWorm->SetWormIndex(xWorm);
//    oWorm->SetDirection(5.2);
//    oWorm->SetHeadPos((PrecissionPoint){50 + xWorm*60,100});
    oWorm->SetSpeed(250);
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
    oGameObject->SetPosition((PrecissionPoint){50 + ((int)(xFramesCount*0.3 + xGobject))%5*130,30 + ((int)(xFramesCount*0.7 + xGobject))%4*105});
    oGameObject->SetDoesDamage(false);
    oGameObject->SetDoesFeed(true);
    oGameObject->SetDirection(xFramesCount + xGobject);

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
    if (arrKeybState[oPlayer->xLeftKeyCode])
        return -0.7;
    if (arrKeybState[oPlayer->xRightKeyCode])
        return 0.7;
    return 0;
}

void Game::MoveWorms()
{
    for (unsigned char xi = 0; xi<xPlayers; xi++)
        {
            arrWorms[xi]->Move(SteerWorm(oGameMenu->GetPlayer(xi)),++xFramesCount);
            arrWorms[xi]->DebugIsInf(arrWorms[xi]->ptHeadPos.x);
            arrWorms[xi]->DebugIsNaN();
        }

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

void Game::FeedWorms()
{
    for (unsigned char xi = 0; xi<xPlayers; xi++)
    {
        if (arrWorms[xi] != NULL && arrWorms[xi]->GetInPreCollision())
        {
            arrWorms[xi]->EatCollidingWorm();
        }

        if (arrWorms[xi] != NULL)
        {
            GameObjects *pGameObject = lstFoodObjects;

            while (pGameObject != NULL)
            {
                if (DistanceBetweenPoints(arrWorms[xi]->ptMouth,(PrecissionPoint) {pGameObject->oGameObject->ptPosition.x +32, pGameObject->oGameObject->ptPosition.y +32 })< 32)
                {
                    arrWorms[xi]->AddBodyParts(2);
                    RemoveFood(pGameObject);
                }

                pGameObject = pGameObject->pNext;
            }
        }
    }
}

void Game::AttackWorms()
{
    for (unsigned char xi = 0; xi<xPlayers; xi++)
    {
        if (arrWorms[xi] != NULL)
        {
            GameObjects *pGameObject = lstCritterObjects;

            while (pGameObject != NULL)
            {
                if (DistanceBetweenPoints(arrWorms[xi]->ptMouth,(PrecissionPoint) {pGameObject->oGameObject->ptPosition.x +32, pGameObject->oGameObject->ptPosition.y +32 })< 32)
                {
                    arrWorms[xi]->ShrinkWorm(1);
                }

                pGameObject = pGameObject->pNext;
            }
        }
    }
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
                arrWorms[xi]->AddCollidingWorm(arrWorms[yi]);
                arrWorms[yi]->AddCollidingWorm(arrWorms[xi]);
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
        xAngle = AngleTowardsWorm(pCritter->oGameObject);
        pCritter->oGameObject->MoveOffset(xAngle);

        pCritter = pCritter->pNext;
    }

}

void Game::ApplyForces()
{
    GameObjects *pCritter = lstCritterObjects;
    PrecissionPoint ptClosest;
    double xSpeed;
    double xAngle=0.0;

    while(pCritter!=NULL)
    {
        xSpeed = pCritter->oGameObject->GetSpeed();

        CrittersSpreadOut(pCritter->oGameObject);
        pCritter->oGameObject->ApplyPullForces();

        pCritter = pCritter->pNext;
    }

}

// Critters move away from each other
//http://www.wolframalpha.com/input/?i=plot+0.01%5Ex
PullForce Game::CrittersSpreadOut(GameObject *pCritter)
{
    double xDistance;
    GameObjects *pOtherCritter = lstCritterObjects;

    while(pOtherCritter!=NULL)
    {
        if (pOtherCritter->oGameObject->GetIndex() != pCritter->GetIndex())
        {
            xDistance = DistanceBetweenPoints(pCritter->ptPosition, pOtherCritter->oGameObject->ptPosition);
            if (xDistance < pOtherCritter->oGameObject->GetPushForce().xRadius)
            {
                PullForce oPF;
                double xPercentage;

                xPercentage = xDistance/pOtherCritter->oGameObject->GetPushForce().xRadius;

                oPF.xDirection = GetSegmentAngle(pOtherCritter->oGameObject->ptPosition.x, pOtherCritter->oGameObject->ptPosition.y, pCritter->ptPosition.x, pCritter->ptPosition.y);
                oPF.xMagnitude = pOtherCritter->oGameObject->GetPushForce().xStrength * pow(pOtherCritter->oGameObject->GetPushForce().xCurve,xPercentage*4 - 2);

                pCritter->CombinePullForces(oPF);
            }
        }
        pOtherCritter = pOtherCritter->pNext;
    }
}

double Game::AngleTowardsWorm(GameObject *pCritter)
{
    double xShortestDistance;
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
//                    pCritter->SetDirection(xAngle);
                }
        }
    return xAngle;
}

void Game::RemoveFood(GameObjects *pGameObject)
{
    if (lstFoodObjects == pGameObject)
    {
        lstFoodObjects = pGameObject->pNext;
        delete pGameObject;
    }
    else
    {
        GameObjects *pPrevObject = lstFoodObjects;

        while (pPrevObject->pNext != pGameObject)
            pPrevObject = pPrevObject->pNext;

        pPrevObject->pNext = pGameObject->pNext;
        delete pGameObject->oGameObject;
        delete pGameObject;
    }
    xFoodObjects--;
}
