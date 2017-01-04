#ifndef PUBSTRUC_H
#define PUBSTRUC_H
#include <string>
#include <SDL.h>
#include "math.h"

#define GAME_DIFFICULTY_EASY 1;
#define GAME_DIFFICULTY_MEDIUM 2;
#define GAME_DIFFICULTY_HARD 3;

using namespace std;

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

double GetSegmentAngle(double x1, double y1, double x2, double y2);

#endif
