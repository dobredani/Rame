#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class Texture
{
    public:
        Texture(SDL_Renderer* argRenderer);
        virtual ~Texture();

        bool LoadImage(string sFilePath);
        void FreeMemory();
        void Render(unsigned int xLeft, unsigned int xTop, double xAngle, SDL_Rect* oSpriteRect = NULL, double xZoomFactor = 1.0);

        unsigned int GetWidth() { return xWidth; }
        unsigned int GetHeight() { return xHeight; }
        void DrawOutlineRect(SDL_Rect oRect, SDL_Color oColor) {SDL_SetRenderDrawColor( oRenderer, oColor.r, oColor.g, oColor.b, oColor.a ); SDL_RenderDrawRect( oRenderer, &oRect );}
        void DrawLine(SDL_Point ptPoint1, SDL_Point ptPoint2, SDL_Color oColor) {SDL_SetRenderDrawColor( oRenderer, oColor.r, oColor.g, oColor.b, oColor.a ); SDL_RenderDrawLine( oRenderer, ptPoint1.x,ptPoint1.y,ptPoint2.x,ptPoint1.y );}

    protected:

    private:
        SDL_Texture* oTexture;
        SDL_Renderer* oRenderer;
        unsigned int xWidth;
        unsigned int xHeight;
        SDL_Point ptCenter;
};

#endif // TEXTURE_H
