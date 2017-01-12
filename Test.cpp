#include "Texture.h"
#include "Game.h"
#include "SDLWindow.h"

int main( int argc, char* args[] )
{
    SDLWindow oSDLWindow;
    if (!oSDLWindow.initSDL())
    {
        oSDLWindow.closeSDL();
        return 0;
    }

    SDL_Renderer* oRenderer = oSDLWindow.GetRenderer();
//    Texture *gSpriteSheetTexture;
    GameMenu *oGameMenu = new GameMenu;
    oGameMenu->SetRenderer(oRenderer);


    Game *oGame = new Game(6);

//    gSpriteSheetTexture = new Texture(oRenderer);

    bool bQuit = false;
    SDL_Event eSDLevent;

    while( !bQuit )
    {
        while( SDL_PollEvent( &eSDLevent ) != 0 )
        {
            if( eSDLevent.type == SDL_QUIT ) bQuit = true;

            if (oGame->GetGameOver()) oGameMenu->PollEvent(eSDLevent);
        }

        if (oGameMenu->ClickedNewGame())
        {
            oGame = NULL;
            oGame = new Game(2);
            oGame->SetRenderer(oRenderer);
            oGame->SpawnWorms();
            oGame->SetGameMenu(oGameMenu);
            oGame->SetGameOver(false);
        }

        if (oGameMenu->ClickedExit()) bQuit = true;

        //Clear screen
        SDL_SetRenderDrawColor( oRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( oRenderer );

        if (oGame->GetGameOver())
        {
            if (oGameMenu->ClickedOptions())
                oGameMenu->ShowOptionsMenu();
            else
                oGameMenu->ShowMainMenu();
        }
        else
        {
            oGame->MoveWorms();
            oGame->PreCollision();
            oGame->RenderWorms();
        }


        //Update screen
        SDL_RenderPresent( oRenderer );
    }

	//Free resources and close SDL
//	gSpriteSheetTexture->FreeMemory();
	oSDLWindow.closeSDL();

	return 0;
}
