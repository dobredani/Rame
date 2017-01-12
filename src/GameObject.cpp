#include "GameObject.h"

GameObject::GameObject()
{
    xSpeed=0;
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

void GameObject::MoveOffset(double xOffset, double yOffset)
{
    ptPosition.x = ptPosition.x+xOffset;
    ptPosition.y = ptPosition.y+yOffset;
}
