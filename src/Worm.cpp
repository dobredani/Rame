#include "Worm.h"
#include "Texture.h"
#include "math.h"
#include "stdlib.h"
#include "SDLWindow.h"

Worm::Worm()
{
    oPreCollisionBoxColor.r = 0x00;
    oPreCollisionBoxColor.g = 0xFF;
    oPreCollisionBoxColor.b = 0x00;
    oPreCollisionBoxColor.a = 0xFF;
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
        WormBody* pCurrentBody = lstWormBody;
        lstWormBody = new WormBody;
        lstWormBody->pNextWormBody = pCurrentBody;
        lstWormBody->ptRenderPosition = (PrecissionPoint)
        {
            ptHeadPos.x, ptHeadPos.y + (xi+1)*25
        }; // <- To Do: function that calculates the position of the body part based on direction, screen constrains and distance to worm head

        lstWormBody->oSpriteRect.y = 0 + TEXTURE_BORDER + xWormIndex*62;
        lstWormBody->oSpriteRect.x = 62 + TEXTURE_BORDER + (int)(xWormBodyLength*1.2)%3 * 62; // Pick one of the 3 available body sprites considering the position in the worm body
        lstWormBody->oSpriteRect.h = 63 - TEXTURE_BORDER * 2;
        lstWormBody->oSpriteRect.w = 63 - TEXTURE_BORDER * 2;
    }
    return true;
}

void Worm::Render()
{
    WormBody* pBodyPart = lstWormBody;
    while (pBodyPart != NULL)
    {
        oTexture->Render(pBodyPart->ptRenderPosition.x, pBodyPart->ptRenderPosition.y,pBodyPart->xDirection, &pBodyPart->oSpriteRect, xZoomFactor);
        pBodyPart = pBodyPart->pNextWormBody;
    }

    RenderWormHead();

    if (DEBUG_SHOW) oTexture->DrawOutlineRect(PrecissionToSDLRect(oPreCollisionBox), oPreCollisionBoxColor);
    if (DEBUG_SHOW) oTexture->DrawLine(PrecissionToSDLPoint(ptLeftBounceCircle), PrecissionToSDLPoint(ptRightBounceCircle), oPreCollisionBoxColor);
    if (DEBUG_SHOW) oTexture->DrawCircle(PrecissionToSDLPoint(ptLeftBounceCircle), xBounceRadius, oPreCollisionBoxColor);
    if (DEBUG_SHOW) oTexture->DrawCircle(PrecissionToSDLPoint(ptRightBounceCircle), xBounceRadius, oPreCollisionBoxColor);


}

void Worm::RenderWormHead()
{
    double xAngle = xDirection/(2*M_PI)*360 +90;
    oTexture->Render(ptHeadPos.x, ptHeadPos.y, xAngle, &oHeadSprite, xZoomFactor);
}

void Worm::Move(double xSteer, long long xFrame)
{
    ResetPreCollisionBox();

    WormBody* pBodyPart = lstWormBody;
    while (pBodyPart != NULL)
    {
        if (pBodyPart->pNextWormBody != NULL)
        {
            CalculateDirectionPosition(pBodyPart);
            CalculatePrecollisionBox(pBodyPart->ptRenderPosition);
        }
        else
        {
            CalculateDirectionPosition(pBodyPart, ptHeadPos);
            CalculatePrecollisionBox(pBodyPart->ptRenderPosition);
        }

        pBodyPart = pBodyPart->pNextWormBody;
    }

    ptHeadPos.x = ptHeadPos.x + (xWormStretch)*cos(xDirection)/xSpeed;
    ptHeadPos.y = ptHeadPos.y + (xWormStretch)*sin(xDirection)/xSpeed;

    double xBounceAngle = BounceScreen();
    if (xBounceAngle<0)
        xDirection += (min(xSteer/2,0.0)+xBounceAngle)/xSpeed;
    else if (xBounceAngle>0)
        xDirection += (max(xSteer/2,0.0)+xBounceAngle)/xSpeed;
    else
        xDirection += (xSteer+0.0)/xSpeed;

    CalculatePrecollisionBox(ptHeadPos);
}

void Worm::CalculateDirectionPosition(WormBody *pBodyPart)
{
    pBodyPart->xDirection = GetSegmentAngle(pBodyPart->pNextWormBody->ptRenderPosition.x, pBodyPart->pNextWormBody->ptRenderPosition.y, pBodyPart->ptRenderPosition.x, pBodyPart->ptRenderPosition.y);
    pBodyPart->xDirection = (2*M_PI - pBodyPart->xDirection)/(2*M_PI)*360 ;

    pBodyPart->ptRenderPosition.x = pBodyPart->ptRenderPosition.x + (pBodyPart->pNextWormBody->ptRenderPosition.x - pBodyPart->ptRenderPosition.x)/xSpeed;
    pBodyPart->ptRenderPosition.y = pBodyPart->ptRenderPosition.y + (pBodyPart->pNextWormBody->ptRenderPosition.y - pBodyPart->ptRenderPosition.y)/xSpeed;
}

void Worm::CalculateDirectionPosition(WormBody *pBodyPart, PrecissionPoint ptHeadPos)
{
    pBodyPart->xDirection = GetSegmentAngle(ptHeadPos.x, ptHeadPos.y, pBodyPart->ptRenderPosition.x, pBodyPart->ptRenderPosition.y);
    pBodyPart->xDirection = (2*M_PI - pBodyPart->xDirection)/(2*M_PI)*360 ;

    pBodyPart->ptRenderPosition.x = pBodyPart->ptRenderPosition.x + (ptHeadPos.x - pBodyPart->ptRenderPosition.x)/xSpeed;
    pBodyPart->ptRenderPosition.y = pBodyPart->ptRenderPosition.y + (ptHeadPos.y - pBodyPart->ptRenderPosition.y)/xSpeed;
}

void Worm::CalculatePrecollisionBox(PrecissionPoint ptPoint)
{
    if (oPreCollisionBox.w == 0 && oPreCollisionBox.h == 0)
    {
        oPreCollisionBox.x = ptPoint.x;
        oPreCollisionBox.y = ptPoint.y;
        oPreCollisionBox.w = 2*(xBodyPartRadius - TEXTURE_BORDER)*xZoomFactor;
        oPreCollisionBox.h = 2*(xBodyPartRadius - TEXTURE_BORDER)*xZoomFactor;
    }
    else
    {
        if (ptPoint.x < oPreCollisionBox.x)
        {
            oPreCollisionBox.w += oPreCollisionBox.x - (ptPoint.x );
            oPreCollisionBox.x = ptPoint.x ;
        }
        if (ptPoint.y < oPreCollisionBox.y)
        {
            oPreCollisionBox.h += oPreCollisionBox.y - (ptPoint.y );
            oPreCollisionBox.y = ptPoint.y ;
        }
        if (ptPoint.x + 2*(xBodyPartRadius - TEXTURE_BORDER)*xZoomFactor > oPreCollisionBox.x + oPreCollisionBox.w)
        {
            oPreCollisionBox.w = ptPoint.x - oPreCollisionBox.x + 2*(xBodyPartRadius - TEXTURE_BORDER)*xZoomFactor;
        }
        if (ptPoint.y + 2*(xBodyPartRadius - TEXTURE_BORDER)*xZoomFactor > oPreCollisionBox.y + oPreCollisionBox.h)
        {
            oPreCollisionBox.h = ptPoint.y - oPreCollisionBox.y + 2*(xBodyPartRadius - TEXTURE_BORDER)*xZoomFactor;
        }
    }
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

bool intersectie(double x,double y,double raza)
{
    if((SCREEN_HEIGHT-y)<=raza||(SCREEN_WIDTH-x)<=raza||x<=raza||y<=raza)
        return true;
    else
        return false;

}
double minim(double x,double y)
{
    double a;
    a=x;
    if((SCREEN_HEIGHT-y)<a)
        a=SCREEN_HEIGHT-y;
    if((SCREEN_WIDTH-x)<a)
        a=SCREEN_WIDTH-x;
    if(y<a)
        a=y;
    return a;

}
double Worm::BounceScreen()
{

    double latura;
    double unghi;
    double unghiFinal;
    double au,bu;
    au=(((double)xWormStretch)/(2*(double)xBounceRadius));
//    bu=2*(atan(au));
    unghiFinal = 2*asin(au);
//    unghiFinal=(bu*M_PI)/180;
    unghi=xDirection; //(xDirection*180)/M_PI;
    latura=xBounceRadius-xBodyPartRadius*xZoomFactor;


    ptLeftBounceCircle.x = ptHeadPos.x + xBodyPartRadius*xZoomFactor +cos(xDirection + 3*M_PI/2) * latura;
    ptLeftBounceCircle.y = ptHeadPos.y + xBodyPartRadius*xZoomFactor +sin(xDirection + 3*M_PI/2) * latura;
    ptRightBounceCircle.x = ptHeadPos.x + xBodyPartRadius*xZoomFactor +cos(xDirection + M_PI/2) * latura;
    ptRightBounceCircle.y = ptHeadPos.y + xBodyPartRadius*xZoomFactor +sin(xDirection + M_PI/2) * latura;


//    if(unghi>=0&&unghi<=M_PI/2)
//    {
//        ptLeftBounceCircle.x=abs((cos(unghi+M_PI))*latura)+ptHeadPos.x;
//        ptLeftBounceCircle.y=abs((sin(unghi))*latura)+ptHeadPos.y;
//        ptRightBounceCircle.x=abs((cos(unghi))*latura)+ptHeadPos.x;
//        ptRightBounceCircle.y=abs((sin(unghi+M_PI))*latura)+ptHeadPos.y;
//    }
//    if((unghi>M_PI/2&&unghi<M_PI))
//    {
//        ptLeftBounceCircle.x=abs((cos(unghi))*latura)+ptHeadPos.x;
//        ptLeftBounceCircle.y=abs((sin(unghi+M_PI))*latura)+ptHeadPos.y;
//        ptRightBounceCircle.x=abs((cos(unghi+M_PI))*latura)+ptHeadPos.x;
//        ptRightBounceCircle.y=abs((sin(unghi))*latura)+ptHeadPos.y;
//    }
//    if(unghi>=M_PI&&unghi<=3*M_PI/2)
//    {
//        ptLeftBounceCircle.x=abs((cos(unghi))*latura)+ptHeadPos.x;
//        ptLeftBounceCircle.y=abs((sin(unghi-M_PI))*latura)+ptHeadPos.y;
//        ptRightBounceCircle.x=abs((cos(unghi-M_PI))*latura)+ptHeadPos.x;
//        ptRightBounceCircle.y=abs((sin(unghi))*latura)+ptHeadPos.y;
//
//    }
//    if(unghi>3*M_PI/2&&unghi<2*M_PI)
//    {
//        ptLeftBounceCircle.x=abs((cos(unghi))*latura)+ptHeadPos.x;
//        ptLeftBounceCircle.y=abs((sin(unghi-M_PI))*latura)+ptHeadPos.y;
//        ptRightBounceCircle.x=abs((cos(unghi))*latura)+ptHeadPos.x;
//        ptRightBounceCircle.y=abs((sin(unghi-M_PI))*latura)+ptHeadPos.y;
//
//    }

    if(intersectie(ptLeftBounceCircle.x,ptLeftBounceCircle.y,xBounceRadius)==1&&
            intersectie(ptRightBounceCircle.x,ptRightBounceCircle.y,xBounceRadius)==1)
    {
        if(minim(ptRightBounceCircle.x,ptRightBounceCircle.y)>=
                minim(ptLeftBounceCircle.x,ptLeftBounceCircle.y))
//     if(unghi>=180&&unghi<=270)
             return unghiFinal;
        else
             return -unghiFinal;
    }
return 0.0;

}
SDL_Rect PrecissionToSDLRect(PrecissionRect oPrecRect)
{
    SDL_Rect oSDLrect;
    oSDLrect.x = (int)oPrecRect.x;
    oSDLrect.y = (int)oPrecRect.y;
    oSDLrect.w = (int)oPrecRect.w;
    oSDLrect.h = (int)oPrecRect.h;
    return oSDLrect;
}

SDL_Point PrecissionToSDLPoint(PrecissionPoint oPrecPoint)
{
    SDL_Point oSDLpt;
    oSDLpt.x = (int)oPrecPoint.x;
    oSDLpt.y = (int)oPrecPoint.y;
    return oSDLpt;
}
