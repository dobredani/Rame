#ifndef WORM_H
#define WORM_H
#include "SDL.h"
#include "Texture.h"
#include "PublicStructures.h"
#include "SDLWindow.h"
#include "GameObject.h"

class Worm
{
    public:
        Worm();
        virtual ~Worm();

//        const unsigned char TEXTURE_BORDER = 8;

        void SetDirection(double val) { xDirection = val; }
        void SetSpeed(unsigned char val) { xSpeed = 5+(255-val)/12; }
        void SetHeadPos(PrecissionPoint val) { ptHeadPos = val; }
        void SetTexture(Texture *oValue) { oTexture = oValue; }
        void SetWormIndex(unsigned char xValue) { xWormIndex = xValue; oHeadSprite = {0 + TEXTURE_BORDER,0 + TEXTURE_BORDER + xValue * 62,63 - TEXTURE_BORDER * 2,63 - TEXTURE_BORDER * 2};}
        void SetPreCollisionBoxColor(SDL_Color oValue) { oPreCollisionBoxColor.r = oValue.r; oPreCollisionBoxColor.g = oValue.g; oPreCollisionBoxColor.b = oValue.b; oPreCollisionBoxColor.a = oValue.a;}
        void SetInPreCollision(bool bValue) {bInPreCollision = bValue; if (!bInPreCollision) {lstCollidingWorms = NULL;} }
        bool GetInPreCollision() {return bInPreCollision;}
        PrecissionRect GetPreCollisionBox() { return oPreCollisionBox; }
        unsigned short GetWormBodyLength() { return xWormBodyLength; }
        PrecissionPoint GetGravityPoint() { return ptGravityPoint; }


        bool AddBodyParts(unsigned char xParts);
        void Render();
        void Move(double xSteer, long long xFrame);
        double BounceScreen();
        void InitialPosition(unsigned char xWorms, unsigned char xBodyParts);
        PrecissionPoint ClosestBodyPart(PrecissionPoint ptPoint);
        void AddCollidingWorm(Worm *oOtherWorm);
        void EatCollidingWorm();
        void ShrinkWorm(unsigned char xParts);


        bool DebugIsNaN();
        bool DebugIsInf(double xNumber);

        PrecissionPoint ptHeadPos;
        PrecissionPoint ptMouth;
    protected:

    private:

        struct WormBody{
            PrecissionPoint ptRenderPosition;
            SDL_Rect oSpriteRect;
            double xDirection;
            WormBody *pNextWormBody;
        };

        struct CollidingWorms{
            Worm *CollidingWorm;
            CollidingWorms* pNext;
        };

//        struct CollidingObjects{
//            GameObject *oCollidingObject;
//            CollidingObjects* pNext;
//        };

        double xDirection;
        unsigned char xSpeed;
        WormBody *lstWormBody = NULL;
        CollidingWorms *lstCollidingWorms=NULL;
//        CollidingObjects *lstCollidingObjects=NULL;

        bool bInPreCollision = false;
        SDL_Color oPreCollisionBoxColor;
        PrecissionRect oPreCollisionBox;
        PrecissionPoint ptGravityPoint;
        unsigned short xWormBodyLength = 0;
        Texture *oTexture;
        SDL_Rect oHeadSprite;
        unsigned char xWormIndex;
        unsigned int xWormStretch = 24;
        unsigned char xBounceRadius = 80;
        double xBodyPartRadius = 32;
        double xZoomFactor = 0.8;
        unsigned char xSpeedUp = 3;
        PrecissionPoint ptLeftBounceCircle;
        PrecissionPoint ptRightBounceCircle;

        void RenderWormHead();
        void CalculateDirectionPosition(WormBody *pBodyPart);
        void CalculateDirectionPosition(WormBody *pBodyPart, PrecissionPoint ptHeadPos);
        void ResetPreCollisionBox() {oPreCollisionBox.x = 0; oPreCollisionBox.y = 0; oPreCollisionBox.w = 0; oPreCollisionBox.h = 0;}
        void CalculatePrecollisionBox(PrecissionPoint ptNewPoint);
        void RemoveBodyParts(unsigned char xRemoveBodyParts);

};

#endif // WORM_H
