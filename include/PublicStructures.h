#ifndef PUBSTRUC_H
#define PUBSTRUC_H
#include <string>
#include <SDL.h>
#include "math.h"


#define GAME_DIFFICULTY_EASY 1;
#define GAME_DIFFICULTY_MEDIUM 2;
#define GAME_DIFFICULTY_HARD 3;
const bool DEBUG_SHOW = false;

using namespace std;

const unsigned char TEXTURE_BORDER = 8;

struct Player{
    string sName;

    SDL_Keycode xLeftKeyCode; // refer to following page for SDL_Keycode documentation:
    SDL_Keycode xRightKeyCode; // https://wiki.libsdl.org/SDL_Keycode
    bool bIsAIplayer;
    };

struct PrecissionPoint{
    double x;
    double y;
    };

struct PrecissionRect{
    double x;
    double y;
    double w;
    double h;
    };

struct PushForce{
    double xStrength;
    double xRadius;
    double xCurve; // coefficient in an exponential equation: used to determine force strength at a certain distance from object
};

struct PullForce{
    double xDirection;
    double xMagnitude;
};

SDL_Rect PrecissionToSDLRect(PrecissionRect oPrecRect);
SDL_Point PrecissionToSDLPoint(PrecissionPoint oPrecPoint);

double GetSegmentAngle(double x1, double y1, double x2, double y2);
double DistanceBetweenPoints(PrecissionPoint ptPoint1,PrecissionPoint ptPoint2);
#endif
