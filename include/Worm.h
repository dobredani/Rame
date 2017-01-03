#ifndef WORM_H
#define WORM_H
#include "SDL.h"
#include "Texture.h"
#include "PublicStructures.h"

class Worm
{
    public:
        Worm();
        virtual ~Worm();

        void SetDirection(double val) { xDirection = val; }
        void SetSpeed(unsigned char val) { xSpeed = 5+(255-val)/12; }
        void SetHeadPos(PrecissionPoint val) { ptHeadPos = val; }
        void SetTexture(Texture *oValue) { oTexture = oValue; }
        void SetWormIndex(unsigned char xValue) { xWormIndex = xValue; oHeadSprite = {1,1 + xValue * 62,61,61};}
        SDL_Rect GetPreCollisionBox() { return oPreCollisionBox; }
        unsigned short GetWormBodyLength() { return xWormBodyLength; }
        PrecissionPoint GetGravityPoint() { return ptGravityPoint; }

        bool AddBodyParts(unsigned char xParts);
        void Render();
        void Move(long long xFrame);
    protected:

    private:

        struct WormBody{
            PrecissionPoint ptRenderPosition;
            SDL_Rect oSpriteRect;
            WormBody *pNextWormBody;
        };

        double xDirection;
        unsigned char xSpeed;
        PrecissionPoint ptHeadPos;
        WormBody *lstWormBody = NULL;
        SDL_Rect oPreCollisionBox;
        unsigned short xWormBodyLength = 0;
        PrecissionPoint ptGravityPoint;
        Texture *oTexture;
        SDL_Rect oHeadSprite;
        unsigned char xWormIndex;
        unsigned int xWormStretch = 24;

        void RenderWormHead();
};

#endif // WORM_H
