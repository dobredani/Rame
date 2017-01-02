#include "Worm.h"
#include "Texture.h"

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
        WormBody* pCurrentBody = lstWormBody;
        lstWormBody = new WormBody;
        lstWormBody->pNextWormBody = pCurrentBody;
        lstWormBody->ptRenderPosition = (SDL_Point){ptHeadPos.x,ptHeadPos.y + (xi+1)*25}; // <- To Do: function that calculates the position of the body part based on direction, screen constrains and distance to worm head

        lstWormBody->oSpriteRect.y = 1;
        lstWormBody->oSpriteRect.x = 63 + (int)(xWormBodyLength*1.2)%3 * 62; // Pick one of the 3 available body sprites considering the position in the worm body
        lstWormBody->oSpriteRect.h = 61;
        lstWormBody->oSpriteRect.w = 61;
    }
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
    oTexture->Render(ptHeadPos.x, ptHeadPos.y, &oHeadSprite, 0.9);
}
