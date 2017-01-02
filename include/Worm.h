#ifndef WORM_H
#define WORM_H
#include "SDL.h"
#include "Texture.h"

class Worm
{
    public:
        Worm();
        virtual ~Worm();

        void SetDirection(double val) { xDirection = val; }
        void SetSpeed(double val) { xSpeed = val; }
        void SetHeadPos(SDL_Point val) { ptHeadPos = val; }
        void SetTexture(Texture *oValue) { oTexture = oValue; }
        SDL_Rect GetPreCollisionBox() { return oPreCollisionBox; }
        unsigned short GetWormBodyLength() { return xWormBodyLength; }
        SDL_Point GetGravityPoint() { return ptGravityPoint; }

        bool AddBodyParts(unsigned char xParts);
        void Render();
    protected:

    private:

        struct WormBody{
            SDL_Point ptRenderPosition;
            SDL_Rect oSpriteRect;
            WormBody *pNextWormBody;
        };

        double xDirection;
        double xSpeed;
        SDL_Point ptHeadPos;
        WormBody *lstWormBody = NULL;
        SDL_Rect oPreCollisionBox;
        unsigned short xWormBodyLength = 0;
        SDL_Point ptGravityPoint;
        Texture *oTexture;
        SDL_Rect oHeadSprite = {1,1,61,61};

        void RenderWormHead();
};

#endif // WORM_H
