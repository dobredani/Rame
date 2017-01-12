#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "PublicStructures.h"
#include "Texture.h"


class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();


        void SetSpeed(unsigned char val) { xSpeed = 5+(255-val)/12; }
        unsigned char GetSpeed() {return xSpeed;}
        void SetDirection(double val) { xDirection = val; }
        double GetDirection() { return xDirection; }
        PrecissionPoint GetPosition() { return ptPosition; }
        void SetPosition(PrecissionPoint val) { ptPosition = val; }
        void SetIndex(unsigned char val) { xIndex = val; }
        void SetDoesDamage(bool val) { bDoesDamage = val; }
        void SetDoesFeed(bool val) { bDoesFeed = val; }
        double GetRadius() { return xRadius; }
        void SetRadius(double val) { xRadius = val; }
        void SetTexture(Texture *val) { oTexture = val; }
        SDL_Rect oSpriteRect;
        PrecissionPoint ptPosition;

        void Render();
    protected:

    private:
        double xRadius;
        Texture *oTexture=NULL;
        bool bDoesDamage = false;
        bool bDoesFeed = false;
        unsigned char xIndex;
        double xDirection;
        unsigned char xSpeed;
};

#endif // GAMEOBJECT_H
