#include "GameMenu.h"
#include "fstream"

void Dimensions(SDL_Rect &rect,int w,int h, int x, int y)
{
    rect.w = w;
    rect.h = h;
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
            buton1_imagine->FreeMemory();
            buton2_imagine->FreeMemory();
            buton3_imagine->FreeMemory();
            bNewGame =true;
        }
        if(e.motion.x>=SCREEN_WIDTH/3 && e.motion.x<=SCREEN_WIDTH/3+buton2_rect.w && e.motion.y>=2*buton2_rect.h && e.motion.y<=3*buton2_rect.h)
        {
            bOptions=true;
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
    buton1_imagine = new Texture(oRenderer);
    buton1_imagine->LoadImage("ButoaneMeniu/buton1.bmp");
    Dimensions(buton1_rect,250,100,SCREEN_WIDTH/3,SCREEN_HEIGHT/5);
    buton1_imagine->Render(SCREEN_WIDTH/3,SCREEN_HEIGHT/5,0.0,NULL,1.0);

    buton2_imagine = new Texture(oRenderer);
    buton2_imagine->LoadImage("ButoaneMeniu/buton2.bmp");
    Dimensions(buton2_rect,250,100,SCREEN_WIDTH/3,2*buton1_rect.h);
    buton2_imagine->Render(SCREEN_WIDTH/3,2*SCREEN_HEIGHT/5,0.0,NULL,1.0);

    buton3_imagine = new Texture(oRenderer);
    buton3_imagine->LoadImage("ButoaneMeniu/buton3.bmp");
    Dimensions(buton3_rect,250,100,SCREEN_WIDTH/3,3*buton1_rect.h);
    buton3_imagine->Render(SCREEN_WIDTH/3,3*SCREEN_HEIGHT/5,0.0,NULL,1.0);

}

void GameMenu::ShowOptionsMenu()
{

}
