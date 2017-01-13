#include "SubMenu.h"

void Dimensions4(SDL_Rect &rect, int x, int y)
{
    rect.w = SCREEN_WIDTH/5;
    rect.h = SCREEN_HEIGHT/7;
    rect.x = x;
    rect.y = y;
}

void Dimensions3(SDL_Rect &rect, int w, int h, int x, int y)
{
    rect.w = w;
    rect.h = h;
    rect.x = x;
    rect.y = y;
}

SubMenu::SubMenu()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    quit = false;
    window2 = NULL;
    window2 = SDL_CreateWindow( "Joc Rame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window2 == NULL )
    {
        std::cout<<"Window2 could not be created! SDL_Error: %s\n"<<SDL_GetError();
        quit = true;
    }
    ScreenSurface = NULL;
    renderer = NULL;
    renderer = SDL_CreateRenderer(window2,-1,SDL_RENDERER_ACCELERATED);

    jucatori_imagine = NULL;
    jucatori_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/Jucatori.bmp");
    Dimensions4(jucatori_rect,SCREEN_WIDTH/4,SCREEN_HEIGHT/6);

    dificultate_imagine = NULL;
    dificultate_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/Dificultate.bmp");
    Dimensions4(dificultate_rect,SCREEN_WIDTH/13,2*jucatori_rect.y);

    tipjoc_imagine = NULL;
    tipjoc_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/TipJoc.bmp");
    Dimensions4(tipjoc_rect,SCREEN_WIDTH/13,3*jucatori_rect.y);

    comenzi_imagine = NULL;
    comenzi_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/comenzi.bmp");
    Dimensions4(comenzi_rect,SCREEN_WIDTH/13,4*jucatori_rect.y);

    inapoi_imagine = NULL;
    inapoi_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/inapoi.bmp");
    Dimensions4(inapoi_rect,SCREEN_WIDTH-SCREEN_WIDTH/4,5*jucatori_rect.y);

    minus_imagine = NULL;
    minus_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/minus.bmp");
    Dimensions3(minus_rect,SCREEN_WIDTH/12, SCREEN_HEIGHT/7, jucatori_rect.x+jucatori_rect.w,jucatori_rect.y);

    numbers_imagine = NULL;
    numbers_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/numbers.bmp");
    Dimensions4(numbers_rect,minus_rect.x+minus_rect.w,jucatori_rect.y);

    plus_imagine = NULL;
    plus_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/plus.bmp");
    Dimensions3(plus_rect,SCREEN_WIDTH/12, SCREEN_HEIGHT/7,numbers_rect.x+numbers_rect.w,jucatori_rect.y);

    gradinita_imagine = NULL;
    gradinita_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/gradinita.bmp");
    Dimensions4(gradinita_rect,SCREEN_WIDTH/13+dificultate_rect.w,2*jucatori_rect.y);

    liceu_imagine = NULL;
    liceu_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/liceu.bmp");
    Dimensions4(liceu_rect,SCREEN_WIDTH/13+2*dificultate_rect.w,2*jucatori_rect.y);

    facultate_imagine = NULL;
    facultate_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/facultate.bmp");
    Dimensions4(facultate__rect,SCREEN_WIDTH/13+3*dificultate_rect.w,2*jucatori_rect.y);

    arcade_imagine = NULL;
    arcade_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/arcade.bmp");
    Dimensions4(arcade_rect,SCREEN_WIDTH/13+tipjoc_rect.w,3*jucatori_rect.y);

    deathmatch_imagine = NULL;
    deathmatch_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/deathmatch.bmp");
    Dimensions4(deathmatch_rect,SCREEN_WIDTH/13+2*tipjoc_rect.w,3*jucatori_rect.y);
}

SubMenu::~SubMenu()
{
    SDL_DestroyWindow( window2 );
    window2 = NULL;
    SDL_Quit();
}

void SubMenu::SubMenuLoop()
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
                if(e.motion.x>=jucatori_rect.x+jucatori_rect.w && e.motion.x<=jucatori_rect.x+jucatori_rect.w+SCREEN_WIDTH/12 && e.motion.y>=jucatori_rect.h && e.motion.y<=2*jucatori_rect.h)
                    nrPlayers--;
                if(e.motion.x>=numbers_rect.x+numbers_rect.w && e.motion.x<=numbers_rect.x+numbers_rect.w+SCREEN_WIDTH/12 && e.motion.y>=jucatori_rect.h && e.motion.y<=2*jucatori_rect.h)
                    nrPlayers++;
                if(e.motion.x>=gradinita_rect.x && e.motion.x<=gradinita_rect.x+gradinita_rect.w && e.motion.y>=gradinita_rect.y && e.motion.y<=gradinita_rect.y+gradinita_rect.h)
                    Difficulty = 1;
                if(e.motion.x>=liceu_rect.x && e.motion.x<=liceu_rect.x+liceu_rect.w && e.motion.y>=liceu_rect.y && e.motion.y<=liceu_rect.y+liceu_rect.h)
                    Difficulty = 2;
                if(e.motion.x>=facultate__rect.x && e.motion.x<=facultate__rect.x+facultate__rect.w && e.motion.y>=liceu_rect.y && e.motion.y<=liceu_rect.y+liceu_rect.h)
                    Difficulty = 3;
                if(e.motion.x>=arcade_rect.x && e.motion.x<=arcade_rect.x+arcade_rect.w && e.motion.y>=arcade_rect.y && e.motion.y<=arcade_rect.y+arcade_rect.h)
                    TypeOfGame = 1;
                if(e.motion.x>=deathmatch_rect.x && e.motion.x<=deathmatch_rect.x+deathmatch_rect.w && e.motion.y>=deathmatch_rect.y && e.motion.y<=deathmatch_rect.y+deathmatch_rect.h)
                    TypeOfGame = 2;
                if(e.motion.x>=comenzi_rect.x && e.motion.x<=comenzi_rect.x+comenzi_rect.w && e.motion.y>=comenzi_rect.y && e.motion.y<=comenzi_rect.y+comenzi_rect.h)
                    {
                        SDL_DestroyWindow(window2);
                        Comenzi comenzi;
                        comenzi.ComenziLoop();
                    }
                if(e.motion.x>=inapoi_rect.x && e.motion.x<=inapoi_rect.x+inapoi_rect.w && e.motion.y>=inapoi_rect.y && e.motion.y<=inapoi_rect.y+inapoi_rect.h)
                    {
                        SDL_DestroyWindow(window2);
                        GameMenu backtomenu;
                        backtomenu.ShowMainMenu();
                    }
                break;
            default:
                break;
            }
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer,jucatori_imagine,nullptr,&jucatori_rect);
            SDL_RenderCopy(renderer,dificultate_imagine,nullptr,&dificultate_rect);
            SDL_RenderCopy(renderer,tipjoc_imagine,nullptr,&tipjoc_rect);
            SDL_RenderCopy(renderer,comenzi_imagine,nullptr,&comenzi_rect);
            SDL_RenderCopy(renderer,inapoi_imagine,nullptr,&inapoi_rect);
            SDL_RenderCopy(renderer,minus_imagine,nullptr,&minus_rect);
            SDL_RenderCopy(renderer,numbers_imagine,nullptr,&numbers_rect);
            SDL_RenderCopy(renderer,plus_imagine,nullptr,&plus_rect);
            SDL_RenderCopy(renderer,gradinita_imagine,nullptr,&gradinita_rect);
            SDL_RenderCopy(renderer,liceu_imagine,nullptr,&liceu_rect);
            SDL_RenderCopy(renderer,facultate_imagine,nullptr,&facultate__rect);
            SDL_RenderCopy(renderer,arcade_imagine,nullptr,&arcade_rect);
            SDL_RenderCopy(renderer,deathmatch_imagine,nullptr,&deathmatch_rect);
            SDL_RenderPresent(renderer);
        }
    }
    cout<<nrPlayers;
}
