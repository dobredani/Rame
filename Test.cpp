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
    GameMenu *oGameMenu = new GameMenu;
    oGameMenu->SetRenderer(oRenderer);


    Game *oGame = new Game(6);


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
            oGame->SpawnGameObjects();
            oGame->MoveCritters();
            oGame->MoveWorms();
            oGame->ApplyForces();
            oGame->PreCollision();
            oGame->FeedWorms();
            oGame->AttackWorms();
            oGame->RenderWorms();
            oGame->RenderGameObjects();
        }


        SDL_RenderPresent( oRenderer );
    }

	oSDLWindow.closeSDL();

	return 0;
}
