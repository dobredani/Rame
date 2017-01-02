#include "SDLWindow.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Texture.h"

#define ANISOTROPIC_FILTERING "2"
#define LINEAR_FILTERING "1"

SDLWindow::SDLWindow()
{
    //ctor
}

SDLWindow::~SDLWindow()
{
    //dtor
}

bool SDLWindow::initSDL()
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, ANISOTROPIC_FILTERING );

    oWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( oWindow == NULL )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    oRenderer = SDL_CreateRenderer( oWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if( oRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    //Initialize renderer color
    SDL_SetRenderDrawColor( oRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
        return false;
    }

	return true;
}

void SDLWindow::closeSDL()
{
	//Free loaded images
	//gSpriteSheetTexture.FreeMemory();

	//Destroy window
	SDL_DestroyRenderer( oRenderer );
	SDL_DestroyWindow( oWindow );
	oWindow = NULL;
	oRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
