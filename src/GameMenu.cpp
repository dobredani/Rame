#include "GameMenu.h"
#include "fstream"

void Dimensions(SDL_Rect &rect,int w,int h, int x, int y)
{
    rect.w = w;
    rect.h = h;
    rect.x = x;
    rect.y = y;
}

void Dimensions2(SDL_Rect &rect, int x, int y)
{
    rect.w = SCREEN_WIDTH/5;
    rect.h = SCREEN_HEIGHT/7;
    rect.x = x;
    rect.y = y;
}

GameMenu::GameMenu()
{
    sSettingsFileName = "Settings.ini";
    xPlayersCount = 2;
    xDifficulty = GAME_DIFFICULTY_MEDIUM;
    sGameType = "Arcade";

    oPlayer[0] = new Player;
    oPlayer[0]->sName = "Player1";
    oPlayer[0]->xLeftKeyCode=SDL_SCANCODE_A;
    oPlayer[0]->xRightKeyCode=SDL_SCANCODE_Z;
    oPlayer[0]->bIsAIplayer=false;

    oPlayer[1] = new Player;
    oPlayer[1]->sName = "Player2";
    oPlayer[1]->xLeftKeyCode=SDL_SCANCODE_L;
    oPlayer[1]->xRightKeyCode=SDL_SCANCODE_P;
    oPlayer[1]->bIsAIplayer=false;

    oPlayer[2] = NULL;
    oPlayer[3] = NULL;
    oPlayer[4] = NULL;
    oPlayer[5] = NULL;

}

GameMenu::~GameMenu()
{
    //dtor
}

Player* GameMenu::GetPlayer(unsigned char xPlayer)
{
    return oPlayer[xPlayer];
}

void GameMenu::PollEvent(SDL_Event e)
{
    switch(e.type)
    {
    case SDL_QUIT:
        bExit = true;
        break;
    case SDL_MOUSEBUTTONDOWN:
        if(e.motion.x>=SCREEN_WIDTH/3 && e.motion.x<=SCREEN_WIDTH/3+buton1_rect.w && e.motion.y>=buton1_rect.h && e.motion.y<=2*buton1_rect.h)
        {
            SDL_DestroyTexture(buton1_imagine);
            SDL_DestroyTexture(buton2_imagine);
            SDL_DestroyTexture(buton3_imagine);
            bNewGame =true;
        }
        if(e.motion.x>=SCREEN_WIDTH/3 && e.motion.x<=SCREEN_WIDTH/3+buton2_rect.w && e.motion.y>=2*buton2_rect.h && e.motion.y<=3*buton2_rect.h)
        {
            bOptions=true;
            SDL_Event eOptions;
            GameMenu Options;
            Options.OptionsPollEvent(eOptions);
        }
        if(e.motion.x>=SCREEN_WIDTH/3 && e.motion.x<=SCREEN_WIDTH/3+buton3_rect.w && e.motion.y>=3*buton3_rect.h && e.motion.y<=4*buton3_rect.h)
        {
            bExit = true;
        }
        break;
    default:
        break;
    }
}

void GameMenu::ShowMainMenu()
{
    buton1_imagine = nullptr;
    buton1_imagine= IMG_LoadTexture(oRenderer,"ButoaneMeniu/buton1.bmp");
    Dimensions(buton1_rect,250,100,SCREEN_WIDTH/3,SCREEN_HEIGHT/5);
    SDL_RenderCopy(oRenderer,buton1_imagine,nullptr,&buton1_rect);

    buton2_imagine = nullptr;
    buton2_imagine= IMG_LoadTexture(oRenderer,"ButoaneMeniu/buton2.bmp");
    Dimensions(buton2_rect,250,100,SCREEN_WIDTH/3,2*SCREEN_HEIGHT/5);
    SDL_RenderCopy(oRenderer,buton2_imagine,nullptr,&buton2_rect);

    buton3_imagine = nullptr;
    buton3_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/buton3.bmp");
    Dimensions(buton3_rect,250,100,SCREEN_WIDTH/3,3*SCREEN_HEIGHT/5);
    SDL_RenderCopy(oRenderer,buton3_imagine,nullptr,&buton3_rect);

}

void GameMenu::ShowOptionsMenu()
{
    jucatori_imagine = nullptr;
    jucatori_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/Jucatori.bmp");
    Dimensions2(jucatori_rect,SCREEN_WIDTH/5,SCREEN_HEIGHT/6);
    SDL_RenderCopy(oRenderer,jucatori_imagine,nullptr,&jucatori_rect);

    dificultate_imagine = nullptr;
    dificultate_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/Dificultate.bmp");
    Dimensions2(dificultate_rect,SCREEN_WIDTH/10,2*jucatori_rect.y);
    SDL_RenderCopy(oRenderer,dificultate_imagine,nullptr,&dificultate_rect);

    tipjoc_imagine = nullptr;
    tipjoc_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/TipJoc.bmp");
    Dimensions2(tipjoc_rect,SCREEN_WIDTH/10,3*jucatori_rect.y);
    SDL_RenderCopy(oRenderer,tipjoc_imagine,nullptr,&tipjoc_rect);

    comenzi_imagine = nullptr;
    comenzi_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/comenzi.bmp");
    Dimensions2(comenzi_rect,SCREEN_WIDTH/10,4*jucatori_rect.y);
    SDL_RenderCopy(oRenderer,comenzi_imagine,nullptr,&comenzi_rect);

    inapoi_imagine = nullptr;
    inapoi_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/inapoi.bmp");
    Dimensions2(inapoi_rect,SCREEN_WIDTH-SCREEN_WIDTH/4,5*jucatori_rect.y);
    SDL_RenderCopy(oRenderer,inapoi_imagine,nullptr,&inapoi_rect);

    minus_imagine = nullptr;
    minus_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/minus.bmp");
    Dimensions(minus_rect,SCREEN_WIDTH/12, SCREEN_HEIGHT/7, jucatori_rect.x+jucatori_rect.w,jucatori_rect.y);
    SDL_RenderCopy(oRenderer,minus_imagine,nullptr,&minus_rect);

    numbers_imagine = nullptr;
    numbers_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/numbers.bmp");
    Dimensions2(numbers_rect,minus_rect.x+minus_rect.w,jucatori_rect.y);
    SDL_RenderCopy(oRenderer,numbers_imagine,nullptr,&numbers_rect);

    plus_imagine = nullptr;
    plus_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/plus.bmp");
    Dimensions(plus_rect,SCREEN_WIDTH/12, SCREEN_HEIGHT/7,numbers_rect.x+numbers_rect.w,jucatori_rect.y);
    SDL_RenderCopy(oRenderer,plus_imagine,nullptr,&plus_rect);

    gradinita_imagine = nullptr;
    gradinita_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/gradinita.bmp");
    Dimensions2(gradinita_rect,dificultate_rect.x+dificultate_rect.w,2*jucatori_rect.y);
    SDL_RenderCopy(oRenderer,gradinita_imagine,nullptr,&gradinita_rect);

    liceu_imagine = nullptr;
    liceu_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/liceu.bmp");
    Dimensions2(liceu_rect,gradinita_rect.x+gradinita_rect.w,2*jucatori_rect.y);
    SDL_RenderCopy(oRenderer,liceu_imagine,nullptr,&liceu_rect);

    facultate_imagine = nullptr;
    facultate_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/facultate.bmp");
    Dimensions2(facultate_rect,liceu_rect.x+liceu_rect.w,2*jucatori_rect.y);
    SDL_RenderCopy(oRenderer,facultate_imagine,nullptr,&facultate_rect);

    arcade_imagine = nullptr;
    arcade_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/arcade.bmp");
    Dimensions2(arcade_rect,tipjoc_rect.x+tipjoc_rect.w,3*jucatori_rect.y);
    SDL_RenderCopy(oRenderer,arcade_imagine,nullptr,&arcade_rect);

    deathmatch_imagine = nullptr;
    deathmatch_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/deathmatch.bmp");
    Dimensions2(deathmatch_rect,arcade_rect.x+arcade_rect.w,3*jucatori_rect.y);
    SDL_RenderCopy(oRenderer,deathmatch_imagine,nullptr,&deathmatch_rect);
}

void GameMenu::ShowCommandsMenu()
{
    jucator1_imagine = NULL;
    jucator1_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/jucator1.bmp");
    Dimensions2(jucator1_rect,SCREEN_WIDTH/5,SCREEN_HEIGHT/8);
    SDL_RenderCopy(oRenderer,jucator1_imagine,nullptr,&jucator1_rect);

    jucator2_imagine = NULL;
    jucator2_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/jucator2.bmp");
    Dimensions2(jucator2_rect,SCREEN_WIDTH/5,2*jucator1_rect.y);
    SDL_RenderCopy(oRenderer,jucator2_imagine,nullptr,&jucator2_rect);

    jucator3_imagine = NULL;
    jucator3_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/jucator3.bmp");
    Dimensions2(jucator3_rect,SCREEN_WIDTH/5,3*jucator1_rect.y);
    SDL_RenderCopy(oRenderer,jucator3_imagine,nullptr,&jucator3_rect);

    jucator4_imagine = NULL;
    jucator4_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/jucator4.bmp");
    Dimensions2(jucator4_rect,SCREEN_WIDTH/5,4*jucator1_rect.y);
    SDL_RenderCopy(oRenderer,jucator4_imagine,nullptr,&jucator4_rect);

    jucator5_imagine = NULL;
    jucator5_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/jucator5.bmp");
    Dimensions2(jucator5_rect,SCREEN_WIDTH/5,5*jucator1_rect.y);
    SDL_RenderCopy(oRenderer,jucator5_imagine,nullptr,&jucator5_rect);

    jucator6_imagine = NULL;
    jucator6_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/jucator6.bmp");
    Dimensions2(jucator6_rect,SCREEN_WIDTH/5, 6*jucator1_rect.y);
    SDL_RenderCopy(oRenderer,jucator6_imagine,nullptr,&jucator6_rect);

    a_imagine = NULL;
    a_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/a.bmp");
    Dimensions2(a_rect, jucator1_rect.x+jucator1_rect.w, jucator1_rect.y);
    SDL_RenderCopy(oRenderer,a_imagine,nullptr,&a_rect);

    z_imagine = NULL;
    z_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/z.bmp");
    Dimensions2(z_rect, a_rect.x+a_rect.w,jucator1_rect.y);
    SDL_RenderCopy(oRenderer,z_imagine,nullptr,&z_rect);

    p_imagine = NULL;
    p_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/p.bmp");
    Dimensions2(p_rect,jucator2_rect.x+jucator2_rect.w,2*jucator1_rect.y);
    SDL_RenderCopy(oRenderer,p_imagine,nullptr,&p_rect);

    l_imagine = NULL;
    l_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/l.bmp");
    Dimensions2(l_rect,p_rect.x+p_rect.w,2*jucator1_rect.y);
    SDL_RenderCopy(oRenderer,l_imagine,nullptr,&l_rect);

    left_imagine = NULL;
    left_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/left.bmp");
    Dimensions2(left__rect,jucator3_rect.x+jucator3_rect.w,3*jucator1_rect.y);
    SDL_RenderCopy(oRenderer,left_imagine,nullptr,&left__rect);

    right_imagine = NULL;
    right_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/right.bmp");
    Dimensions2(right_rect,left__rect.x+left__rect.w,3*jucator1_rect.y);
    SDL_RenderCopy(oRenderer,right_imagine,nullptr,&right_rect);

    c_imagine = NULL;
    c_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/c.bmp");
    Dimensions2(c_rect,jucator4_rect.x+jucator4_rect.w,4*jucator1_rect.y);
    SDL_RenderCopy(oRenderer,c_imagine,nullptr,&c_rect);

    v_imagine = NULL;
    v_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/v.bmp");
    Dimensions2(v_rect,c_rect.x+c_rect.w,4*jucator1_rect.y);
    SDL_RenderCopy(oRenderer,v_imagine,nullptr,&v_rect);

    n_imagine = NULL;
    n_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/n.bmp");
    Dimensions2(n_rect,jucator5_rect.x+jucator5_rect.w,5*jucator1_rect.y);
    SDL_RenderCopy(oRenderer,n_imagine,nullptr,&n_rect);

    m_imagine = NULL;
    m_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/m.bmp");
    Dimensions2(m_rect,n_rect.x+n_rect.w,5*jucator1_rect.y);
    SDL_RenderCopy(oRenderer,m_imagine,nullptr,&m_rect);

    r_imagine = NULL;
    r_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/r.bmp");
    Dimensions2(r_rect,jucator6_rect.x+jucator6_rect.w,6*jucator1_rect.y);
    SDL_RenderCopy(oRenderer,r_imagine,nullptr,&r_rect);

    t_imagine = NULL;
    t_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/t.bmp");
    Dimensions2(t_rect,r_rect.x+r_rect.w,6*jucator1_rect.y);
    SDL_RenderCopy(oRenderer,t_imagine,nullptr,&t_rect);

    t_imagine = NULL;
    t_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/t.bmp");
    Dimensions2(t_rect,r_rect.x+r_rect.w,6*jucator1_rect.y);
    SDL_RenderCopy(oRenderer,t_imagine,nullptr,&t_rect);

    inapoi_imagine = NULL;
    inapoi_imagine = IMG_LoadTexture(oRenderer,"ButoaneMeniu/inapoi.bmp");
    Dimensions2(inapoi_rect,SCREEN_WIDTH - 250, SCREEN_HEIGHT - 100);
    SDL_RenderCopy(oRenderer,inapoi_imagine,nullptr,&inapoi_rect);
}

void GameMenu::OptionsPollEvent(SDL_Event e)
{
    switch(e.type)
    {
    case SDL_QUIT:
        bExit = true;
        break;
    case SDL_MOUSEBUTTONDOWN:
        if(e.motion.x>=jucatori_rect.x+jucatori_rect.w && e.motion.x<=jucatori_rect.x+jucatori_rect.w+SCREEN_WIDTH/12 && e.motion.y>=jucatori_rect.h && e.motion.y<=2*jucatori_rect.h)
            nrPlayers--;
        if(e.motion.x>=numbers_rect.x+numbers_rect.w && e.motion.x<=numbers_rect.x+numbers_rect.w+SCREEN_WIDTH/12 && e.motion.y>=jucatori_rect.h && e.motion.y<=2*jucatori_rect.h)
        {
            nrPlayers++;
            cout<<nrPlayers<<" ";
        }
        if(e.motion.x>=gradinita_rect.x && e.motion.x<=gradinita_rect.x+gradinita_rect.w && e.motion.y>=gradinita_rect.y && e.motion.y<=gradinita_rect.y+gradinita_rect.h)
            Difficulty = 1;
        if(e.motion.x>=liceu_rect.x && e.motion.x<=liceu_rect.x+liceu_rect.w && e.motion.y>=liceu_rect.y && e.motion.y<=liceu_rect.y+liceu_rect.h)
            Difficulty = 2;
        if(e.motion.x>=facultate_rect.x && e.motion.x<=facultate_rect.x+facultate_rect.w && e.motion.y>=liceu_rect.y && e.motion.y<=liceu_rect.y+liceu_rect.h)
            Difficulty = 3;
        if(e.motion.x>=arcade_rect.x && e.motion.x<=arcade_rect.x+arcade_rect.w && e.motion.y>=arcade_rect.y && e.motion.y<=arcade_rect.y+arcade_rect.h)
            TypeOfGame = 1;
        if(e.motion.x>=deathmatch_rect.x && e.motion.x<=deathmatch_rect.x+deathmatch_rect.w && e.motion.y>=deathmatch_rect.y && e.motion.y<=deathmatch_rect.y+deathmatch_rect.h)
            TypeOfGame = 2;
        if(e.motion.x>=inapoi_rect.x && e.motion.x<=inapoi_rect.x+inapoi_rect.w && e.motion.y>=inapoi_rect.y && e.motion.y<=inapoi_rect.y+inapoi_rect.h)
        {
            GameMenu backtomenu;
            backtomenu.ShowMainMenu();
            bOptions = false;
        }
        if(e.motion.x>=comenzi_rect.x && e.motion.x<=comenzi_rect.x+comenzi_rect.w && e.motion.y>=comenzi_rect.y && e.motion.y<=comenzi_rect.y+comenzi_rect.h)
        {
            bCommands = true;
            GameMenu commands;
            SDL_Event eCommands;
                commands.ShowCommandsMenu();
                commands.CommandsPollEvent(eCommands);
        }
        break;
    default:
        break;
    }
}

void GameMenu::CommandsPollEvent(SDL_Event e)
{
    switch(e.type)
    {
    case SDL_QUIT:
        bExit = true;
        break;
    case SDL_MOUSEBUTTONDOWN:
        if(e.motion.x>=inapoi_rect.x && e.motion.x<=inapoi_rect.x+inapoi_rect.w && e.motion.y>=inapoi_rect.y && e.motion.y<=inapoi_rect.y+inapoi_rect.h)
        {
            bOptions = true;
        }
        break;
    default:
        break;
    }
}
