#include "Comenzi.h"


void Dimensions6(SDL_Rect &rect, int x, int y)
{
    rect.w = SCREEN_WIDTH/5;
    rect.h = SCREEN_HEIGHT/8;
    rect.x = x;
    rect.y = y;
}

void Dimensions5(SDL_Rect &rect, int x, int y)
{
    rect.w = SCREEN_WIDTH/10;
    rect.h = SCREEN_HEIGHT/8;
    rect.x = x;
    rect.y = y;
}

Comenzi::Comenzi()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    quit = false;
    window = NULL;
    window = SDL_CreateWindow( "Joc Rame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        std::cout<<"Window2 could not be created! SDL_Error: %s\n"<<SDL_GetError();
        quit = true;
    }
    ScreenSurface = NULL;
    renderer = NULL;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    jucator1_imagine = NULL;
    jucator1_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/jucator1.bmp");
    Dimensions6(jucator1_rect,SCREEN_WIDTH/5,SCREEN_HEIGHT/8);

    jucator2_imagine = NULL;
    jucator2_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/jucator2.bmp");
    Dimensions6(jucator2_rect,SCREEN_WIDTH/5,2*jucator1_rect.y);

    jucator3_imagine = NULL;
    jucator3_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/jucator3.bmp");
    Dimensions6(jucator3_rect,SCREEN_WIDTH/5,3*jucator1_rect.y);

    jucator4_imagine = NULL;
    jucator4_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/jucator4.bmp");
    Dimensions6(jucator4_rect,SCREEN_WIDTH/5,4*jucator1_rect.y);

    jucator5_imagine = NULL;
    jucator5_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/jucator5.bmp");
    Dimensions6(jucator5_rect,SCREEN_WIDTH/5,5*jucator1_rect.y);

    jucator6_imagine = NULL;
    jucator6_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/jucator6.bmp");
    Dimensions6(jucator6_rect,SCREEN_WIDTH/5, 6*jucator1_rect.y);

    a_imagine = NULL;
    a_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/a.bmp");
    Dimensions5(a_rect, jucator1_rect.x+jucator1_rect.w, jucator1_rect.y);

    z_imagine = NULL;
    z_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/z.bmp");
    Dimensions5(z_rect, a_rect.x+a_rect.w,jucator1_rect.y);

    p_imagine = NULL;
    p_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/p.bmp");
    Dimensions5(p_rect,jucator2_rect.x+jucator2_rect.w,2*jucator1_rect.y);

    l_imagine = NULL;
    l_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/l.bmp");
    Dimensions5(l_rect,p_rect.x+p_rect.w,2*jucator1_rect.y);

    left_imagine = NULL;
    left_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/left.bmp");
    Dimensions5(left__rect,jucator3_rect.x+jucator3_rect.w,3*jucator1_rect.y);

    right_imagine = NULL;
    right_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/right.bmp");
    Dimensions5(right_rect,left__rect.x+left__rect.w,3*jucator1_rect.y);

    c_imagine = NULL;
    c_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/c.bmp");
    Dimensions5(c_rect,jucator4_rect.x+jucator4_rect.w,4*jucator1_rect.y);

    v_imagine = NULL;
    v_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/v.bmp");
    Dimensions5(v_rect,c_rect.x+c_rect.w,4*jucator1_rect.y);

    n_imagine = NULL;
    n_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/n.bmp");
    Dimensions5(n_rect,jucator5_rect.x+jucator5_rect.w,5*jucator1_rect.y);

    m_imagine = NULL;
    m_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/m.bmp");
    Dimensions5(m_rect,n_rect.x+n_rect.w,5*jucator1_rect.y);

    r_imagine = NULL;
    r_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/r.bmp");
    Dimensions5(r_rect,jucator6_rect.x+jucator6_rect.w,6*jucator1_rect.y);

    t_imagine = NULL;
    t_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/t.bmp");
    Dimensions5(t_rect,r_rect.x+r_rect.w,6*jucator1_rect.y);

    inapoi_imagine = NULL;
    inapoi_imagine = IMG_LoadTexture(renderer,"ButoaneMeniu/inapoi.bmp");
    Dimensions6(inapoi_rect,SCREEN_WIDTH-250,SCREEN_HEIGHT-100);
}

Comenzi::~Comenzi()
{
    SDL_DestroyWindow( window );
    window = NULL;
    SDL_Quit();
}

void Comenzi::ComenziLoop()
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
                if(e.motion.x>=inapoi_rect.x && e.motion.x<=inapoi_rect.x+inapoi_rect.w && e.motion.y>=inapoi_rect.y && e.motion.y<=inapoi_rect.y+inapoi_rect.h)
                    {
                        SubMenu submenu;
            submenu.SubMenuLoop();
                    }
                break;
            default:
                break;
            }
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer,jucator1_imagine,nullptr,&jucator1_rect);
            SDL_RenderCopy(renderer,jucator2_imagine,nullptr,&jucator2_rect);
            SDL_RenderCopy(renderer,jucator3_imagine,nullptr,&jucator3_rect);
            SDL_RenderCopy(renderer,jucator4_imagine,nullptr,&jucator4_rect);
            SDL_RenderCopy(renderer,jucator5_imagine,nullptr,&jucator5_rect);
            SDL_RenderCopy(renderer,jucator6_imagine,nullptr,&jucator6_rect);
            SDL_RenderCopy(renderer,a_imagine,nullptr,&a_rect);
            SDL_RenderCopy(renderer,z_imagine,nullptr,&z_rect);
            SDL_RenderCopy(renderer,p_imagine,nullptr,&p_rect);
            SDL_RenderCopy(renderer,l_imagine,nullptr,&l_rect);
            SDL_RenderCopy(renderer,left_imagine,nullptr,&left__rect);
            SDL_RenderCopy(renderer,right_imagine,nullptr,&right_rect);
            SDL_RenderCopy(renderer,c_imagine,nullptr,&c_rect);
            SDL_RenderCopy(renderer,v_imagine,nullptr,&v_rect);
            SDL_RenderCopy(renderer,n_imagine,nullptr,&n_rect);
            SDL_RenderCopy(renderer,m_imagine,nullptr,&m_rect);
            SDL_RenderCopy(renderer,r_imagine,nullptr,&r_rect);
            SDL_RenderCopy(renderer,t_imagine,nullptr,&t_rect);
            SDL_RenderCopy(renderer,inapoi_imagine,nullptr,&inapoi_rect);
            SDL_RenderPresent(renderer);
        }
    }
}
