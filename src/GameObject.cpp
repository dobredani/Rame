#include "GameObject.h"

GameObject::GameObject()
{
    xSpeed=0;
    oPushForce.xCurve = 0.9; //0.01 - 0.99
    oPushForce.xRadius = 80;
    oPushForce.xStrength = 2; // small values
    oPullForce.xMagnitude = 0;
    oPullForce.xDirection = 0;
}

GameObject::~GameObject()
{
    //dtor
}

void GameObject::Render()
{
    oTexture->Render(ptPosition.x, ptPosition.y, xDirection+270, &oSpriteRect, 1.0);

    if (DEBUG_SHOW) oTexture->DrawLine(PrecissionToSDLPoint(ptPosition), PrecissionToSDLPoint(ptClosest),(SDL_Color){0,0,0,0});
}

void GameObject::MoveOffset(double xDesiredAngle)
{
    double xAngle;

    xDesiredAngle = xDesiredAngle/(2*M_PI/360);


    if (abs(xDesiredAngle - xDirection)<180)
        if (xDesiredAngle < xDirection)
            xDirection = xDirection - 0.5;
        else
            xDirection = xDirection + 0.5;
    else
        if (xDesiredAngle < xDirection)
            xDirection = xDirection + 0.5;
        else
            xDirection = xDirection - 0.5;


    xAngle = xDirection * (2*M_PI/360);

    ptPosition.x = ptPosition.x+10.0*sin(xAngle)/xSpeed;
    ptPosition.y = ptPosition.y+10.0*cos(xAngle)/xSpeed;
}

void GameObject::ApplyPullForces()
{
    ptPosition.x = ptPosition.x + oPullForce.xMagnitude * sin(oPullForce.xDirection);
    ptPosition.y = ptPosition.y + oPullForce.xMagnitude * cos(oPullForce.xDirection);
    oPullForce.xDirection=0;
    oPullForce.xMagnitude=0;
}

void GameObject::CombinePullForces(PullForce oNewPullForce)
{
    //https://ro.wikipedia.org/wiki/Teorema_cosinusului
    double d1,d2;

    d1 = oPullForce.xMagnitude;
    d2 = oNewPullForce.xMagnitude;
    oPullForce.xMagnitude = sqrt(pow(d1,2) + pow(d2,2) - 2* d1*d2*cos(oPullForce.xDirection - oNewPullForce.xDirection));
    oPullForce.xDirection = oPullForce.xDirection + (oPullForce.xDirection - oNewPullForce.xDirection )/2;

}
