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
    oTexture->Render(ptPosition.x, ptPosition.y, xDirection, &oSpriteRect, 1.0);
}
