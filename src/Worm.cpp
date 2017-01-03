#include "Worm.h"
#include "Texture.h"
#include "math.h"
#include "stdlib.h"

Worm::Worm()
{

}

Worm::~Worm()
{
    //dtor
}

bool Worm::AddBodyParts(unsigned char xParts)
{
    for (unsigned char xi = 0; xi<xParts; xi++)
    {
        xWormBodyLength++;
        xCrawlIndex = xWormBodyLength+1;
        WormBody* pCurrentBody = lstWormBody;
        lstWormBody = new WormBody;
        lstWormBody->pNextWormBody = pCurrentBody;
        lstWormBody->ptRenderPosition = (PrecissionPoint){ptHeadPos.x,ptHeadPos.y + (xi+1)*25}; // <- To Do: function that calculates the position of the body part based on direction, screen constrains and distance to worm head

        lstWormBody->oSpriteRect.y = 2 + xWormIndex*62;
        lstWormBody->oSpriteRect.x = 64 + (int)(xWormBodyLength*1.2)%3 * 62; // Pick one of the 3 available body sprites considering the position in the worm body
        lstWormBody->oSpriteRect.h = 59;
        lstWormBody->oSpriteRect.w = 59;
    }
    return true;
}

void Worm::Render()
{
    WormBody* pBodyPart = lstWormBody;
    while (pBodyPart != NULL)
    {
        oTexture->Render(pBodyPart->ptRenderPosition.x, pBodyPart->ptRenderPosition.y, &pBodyPart->oSpriteRect, 0.9);
        pBodyPart = pBodyPart->pNextWormBody;
    }

    RenderWormHead();
}

void Worm::RenderWormHead()
{
    oTexture->SetAngle(xDirection/(2*M_PI)*360 +90);
    oTexture->Render(ptHeadPos.x, ptHeadPos.y, &oHeadSprite, 0.9);
}

void Worm::Move(double xSteer, long long xFrame)
{
    double xCrawl = xWormBodyLength+1;
    double xCoef1 = 0; //xFrame/xWormBodyLength; // Phase Best so far: xFrame/18
//    double xCoef2 = 1.0; // Frequency Best so far: 1.5
//    double xCoef3 = 6; // Amplitude Best so far: 6
    WormBody* pBodyPart = lstWormBody;
    while (pBodyPart != NULL)
    {
//        if (abs(xCrawlIndex-xCrawl) < min(6,xWormBodyLength/2))
//            xCoef1 =sin(M_PI * abs(xCrawlIndex-xCrawl) / min(6,xWormBodyLength/2))*xWormStretch;
//        else
//            xCoef1 = 0;
        if (pBodyPart->pNextWormBody != NULL)
            {
                pBodyPart->ptRenderPosition.x = pBodyPart->ptRenderPosition.x + (pBodyPart->pNextWormBody->ptRenderPosition.x - pBodyPart->ptRenderPosition.x)/(xSpeed - xCoef1);
                pBodyPart->ptRenderPosition.y = pBodyPart->ptRenderPosition.y + (pBodyPart->pNextWormBody->ptRenderPosition.y - pBodyPart->ptRenderPosition.y)/(xSpeed - xCoef1);
            }
        else
            {
                pBodyPart->ptRenderPosition.x = pBodyPart->ptRenderPosition.x + (ptHeadPos.x - pBodyPart->ptRenderPosition.x)/(xSpeed - xCoef1);
                pBodyPart->ptRenderPosition.y = pBodyPart->ptRenderPosition.y + (ptHeadPos.y - pBodyPart->ptRenderPosition.y)/(xSpeed - xCoef1);
            }

        xCrawl--;
        pBodyPart = pBodyPart->pNextWormBody;
    }

    ptHeadPos.x = ptHeadPos.x + (xWormStretch - xCoef1)*cos(xDirection)/xSpeed;
    ptHeadPos.y = ptHeadPos.y + (xWormStretch - xCoef1)*sin(xDirection)/xSpeed;
    xDirection += (xSteer+0.2)/xSpeed;

//    xCrawlIndex --;
//    if (xCrawlIndex == -1) xCrawlIndex = xWormBodyLength+1;

}
