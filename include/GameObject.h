#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "PublicStructures.h"
#include "Texture.h"


class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();

        PushForce GetPushForce() {return oPushForce;}
        void SetSpeed(unsigned char val) { xSpeed = 5+(255-val)/12; }
        unsigned char GetSpeed() {return xSpeed;}
        void SetDirection(double val) { xDirection =(2*M_PI - val)/(2*M_PI)*360; }
        double GetDirection() { return xDirection; }
        PrecissionPoint GetPosition() { return ptPosition; }
        void SetPosition(PrecissionPoint val) { ptPosition = val; }
        void SetIndex(unsigned char val) { xIndex = val; }
        unsigned char GetIndex() {return xIndex;}
        void SetDoesDamage(bool val) { bDoesDamage = val; }
        void SetDoesFeed(bool val) { bDoesFeed = val; }
        double GetRadius() { return xRadius; }
        void SetRadius(double val) { xRadius = val; }
        void SetTexture(Texture *val) { oTexture = val; }
        SDL_Rect oSpriteRect;
        PrecissionPoint ptPosition;
        PrecissionPoint ptClosest;

        void Render();
        void MoveOffset(double xDesiredAngle);
        void CombinePullForces(PullForce oNewPullForce);
        void ApplyPullForces();
    protected:

    private:
        double xRadius;
        double xDirection;
        Texture *oTexture=NULL;
        bool bDoesDamage = false;
        bool bDoesFeed = false;
        unsigned char xIndex;
        unsigned char xSpeed;

        PushForce oPushForce;
        PullForce oPullForce;
};

#endif // GAMEOBJECT_H
