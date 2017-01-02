#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include "SDL.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class SDLWindow
{
    public:
        SDLWindow();
        virtual ~SDLWindow();

        bool initSDL();
        void closeSDL();

        SDL_Renderer* GetRenderer() { return oRenderer; }
    protected:

    private:
        SDL_Window* oWindow = NULL;
        SDL_Renderer* oRenderer = NULL;
};

#endif // SDLWINDOW_H