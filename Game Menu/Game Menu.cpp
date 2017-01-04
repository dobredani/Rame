#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 750;
const int SCREEN_HEIGHT = 500;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

SDL_Window* Game = NULL;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout<<"SDL could not initialize! SDL_Error: %s\n"<<SDL_GetError();
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "Joc Rame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            std::cout<<"Window could not be created! SDL_Error: %s\n"<<SDL_GetError();
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

void close()
{
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
    {
        std::cout<<"Failed to initialize!\n";
    }
    else
    {
        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Renderer* renderer = NULL;
        renderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);

        SDL_Event e;

        SDL_Texture* buton1_imagine = NULL;
        buton1_imagine = IMG_LoadTexture(renderer,"buton1.bmp");

        SDL_Rect buton1_rect;
        buton1_rect.w = 250;
        buton1_rect.h = 100;
        buton1_rect.x = SCREEN_WIDTH/3;
        buton1_rect.y = buton1_rect.h;

        SDL_Texture* buton2_imagine = NULL;
        buton2_imagine = IMG_LoadTexture(renderer,"buton2.bmp");

        SDL_Rect buton2_rect;
        buton2_rect.w = 250;
        buton2_rect.h = 100;
        buton2_rect.x = SCREEN_WIDTH/3;
        buton2_rect.y = 2*buton2_rect.h;

        SDL_Texture* buton3_imagine = NULL;
        buton3_imagine = IMG_LoadTexture(renderer,"buton3.bmp");

        SDL_Rect buton3_rect;
        buton3_rect.w = 250;
        buton3_rect.h = 100;
        buton3_rect.x = SCREEN_WIDTH/3;
        buton3_rect.y = 3*buton3_rect.h;

        //While application is running
        while( !quit )
        {
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                switch(e.type)
                {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(e.motion.x>=SCREEN_WIDTH/3 && e.motion.x<=SCREEN_WIDTH/3+buton1_rect.w && e.motion.y>=buton1_rect.h && e.motion.y<=2*buton1_rect.h)
                    {
                        Game = SDL_CreateWindow( "Joc Rame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
                        //Apply the image
            //SDL_BlitSurface( gXOut, NULL, gScreenSurface, NULL );

            //Update the surface
            //SDL_UpdateWindowSurface( gWindow );
                        //StartGame();
                    }
                    if(e.motion.x>=SCREEN_WIDTH/3 && e.motion.x<=SCREEN_WIDTH/3+buton2_rect.w && e.motion.y>=2*buton2_rect.h && e.motion.y<=3*buton2_rect.h)
                    {
                        //accesare submeniu
                    }
                    if(e.motion.x>=SCREEN_WIDTH/3 && e.motion.x<=SCREEN_WIDTH/3+buton3_rect.w && e.motion.y>=3*buton3_rect.h && e.motion.y<=4*buton3_rect.h)
                    {
                        quit = true;
                    }
                    break;
                default:
                    break;
                }
            }
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer,buton1_imagine,nullptr,&buton1_rect);
            SDL_RenderCopy(renderer,buton2_imagine,nullptr,&buton2_rect);
            SDL_RenderCopy(renderer,buton3_imagine,nullptr,&buton3_rect);
            SDL_RenderPresent(renderer);

        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
