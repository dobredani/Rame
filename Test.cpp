#include "GameMenu.h"
#include "Texture.h"
#include "Game.h"
#include "SDLWindow.h"

int main( int argc, char* args[] )
{
    Menu menu;
    menu.MenuLoop();
    SDLWindow oSDLWindow;
    if (!oSDLWindow.initSDL())
    {
        oSDLWindow.closeSDL();
        return 0;
    }

    SDL_Renderer* oRenderer = oSDLWindow.GetRenderer();
    Texture *gSpriteSheetTexture;
    Game *oGame = new Game(6);
    oGame->SetRenderer(oRenderer);
    oGame->SpawnWorms();
    oGame->SetGameMenu(new GameMenu);

    gSpriteSheetTexture = new Texture(oRenderer);

    bool bQuit = false;
    SDL_Event eSDLevent;

    while( !bQuit )
    {
        while( SDL_PollEvent( &eSDLevent ) != 0 )
        {
            if( eSDLevent.type == SDL_QUIT ) bQuit = true;

        }

        //Clear screen
        SDL_SetRenderDrawColor( oRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( oRenderer );

        oGame->RenderWorms();

        //Update screen
        SDL_RenderPresent( oRenderer );
    }

	//Free resources and close SDL
	gSpriteSheetTexture->FreeMemory();
	oSDLWindow.closeSDL();

	return 0;
}
