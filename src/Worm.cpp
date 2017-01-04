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
        oTexture->Render(pBodyPart->ptRenderPosition.x, pBodyPart->ptRenderPosition.y,pBodyPart->xDirection, &pBodyPart->oSpriteRect, 0.9);
        pBodyPart = pBodyPart->pNextWormBody;
    }

    RenderWormHead();
}

void Worm::RenderWormHead()
{
    double xAngle = xDirection/(2*M_PI)*360 +90;
    oTexture->Render(ptHeadPos.x, ptHeadPos.y, xAngle, &oHeadSprite, 0.9);
}

void Worm::Move(double xSteer, long long xFrame)
{
    WormBody* pBodyPart = lstWormBody;
    while (pBodyPart != NULL)
    {
        if (pBodyPart->pNextWormBody != NULL)
            {
                pBodyPart->xDirection = GetSegmentAngle(pBodyPart->pNextWormBody->ptRenderPosition.x, pBodyPart->pNextWormBody->ptRenderPosition.y, pBodyPart->ptRenderPosition.x, pBodyPart->ptRenderPosition.y);
                pBodyPart->xDirection = (2*M_PI - pBodyPart->xDirection)/(2*M_PI)*360 ;

                pBodyPart->ptRenderPosition.x = pBodyPart->ptRenderPosition.x + (pBodyPart->pNextWormBody->ptRenderPosition.x - pBodyPart->ptRenderPosition.x)/xSpeed;
                pBodyPart->ptRenderPosition.y = pBodyPart->ptRenderPosition.y + (pBodyPart->pNextWormBody->ptRenderPosition.y - pBodyPart->ptRenderPosition.y)/xSpeed;
            }
        else
            {
                pBodyPart->xDirection = GetSegmentAngle(ptHeadPos.x, ptHeadPos.y, pBodyPart->ptRenderPosition.x, pBodyPart->ptRenderPosition.y);
                pBodyPart->xDirection = (2*M_PI - pBodyPart->xDirection)/(2*M_PI)*360 ;

                pBodyPart->ptRenderPosition.x = pBodyPart->ptRenderPosition.x + (ptHeadPos.x - pBodyPart->ptRenderPosition.x)/xSpeed;
                pBodyPart->ptRenderPosition.y = pBodyPart->ptRenderPosition.y + (ptHeadPos.y - pBodyPart->ptRenderPosition.y)/xSpeed;
            }

        pBodyPart = pBodyPart->pNextWormBody;
    }

    ptHeadPos.x = ptHeadPos.x + (xWormStretch)*cos(xDirection)/xSpeed;
    ptHeadPos.y = ptHeadPos.y + (xWormStretch)*sin(xDirection)/xSpeed;
    xDirection += (xSteer+0.2)/xSpeed;

}

double GetSegmentAngle(double x1, double y1, double x2, double y2)
{
    double x = x2-x1;
    double y = y2-y1;

    if (x == 0 && y == 0)
        return 0;
    else
    {
        double xAngle = atan2(x,y);
        if (xAngle>=0)
            return xAngle;
        else
            return 2*M_PI + xAngle;
    }
}
