#include "GameMenu.h"

void Dimensions(SDL_Rect &rect,int w,int h, int x, int y)
{
    rect.w = w;
    rect.h = h;
    rect.x = x;
    rect.y = y;
}

Menu::Menu()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    quit = false;
    window = NULL;
    window = SDL_CreateWindow( "Joc Rame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        std::cout<<"Window could not be created! SDL_Error: %s\n"<<SDL_GetError();
        quit = true;
    }
    ScreenSurface = NULL;
    renderer = NULL;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    buton1_imagine = NULL;
    buton1_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/buton1.bmp");
    Dimensions(buton1_rect,250,100,SCREEN_WIDTH/3,SCREEN_HEIGHT/5);

    buton2_imagine = NULL;
    buton2_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/buton2.bmp");
    Dimensions(buton2_rect,250,100,SCREEN_WIDTH/3,2*buton1_rect.h);

    buton3_imagine = NULL;
    buton3_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/buton3.bmp");
    Dimensions(buton3_rect,250,100,SCREEN_WIDTH/3,3*buton1_rect.h);
}

Menu::~Menu()
{
    SDL_DestroyWindow( window );
    window = NULL;
    SDL_Quit();
}

void Menu::MenuLoop()
{
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
                    SDL_DestroyTexture(buton1_imagine);
                    SDL_DestroyTexture(buton2_imagine);
                    SDL_DestroyTexture(buton3_imagine);
                    //StartGame();
                }
                if(e.motion.x>=SCREEN_WIDTH/3 && e.motion.x<=SCREEN_WIDTH/3+buton2_rect.w && e.motion.y>=2*buton2_rect.h && e.motion.y<=3*buton2_rect.h)
                {
                    //SubMenu submenu;
                    //submenu.SubMenuLoop();
                }
                if(e.motion.x>=SCREEN_WIDTH/3 && e.motion.x<=SCREEN_WIDTH/3+buton3_rect.w && e.motion.y>=3*buton3_rect.h && e.motion.y<=4*buton3_rect.h)
                {
                    quit = true;
                }
                break;
            default:
                break;
            }
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer,buton1_imagine,nullptr,&buton1_rect);
            SDL_RenderCopy(renderer,buton2_imagine,nullptr,&buton2_rect);
            SDL_RenderCopy(renderer,buton3_imagine,nullptr,&buton3_rect);
            SDL_RenderPresent(renderer);
        }
    }
}
