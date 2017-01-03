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

        void SetAngle(double xValue) { xAngle = xValue;}
        bool LoadImage(string sFilePath);
        void FreeMemory();
        void Render(unsigned int xLeft, unsigned int xTop, SDL_Rect* oSpriteRect = NULL, double xZoomFactor = 1.0);

        unsigned int GetWidth() { return xWidth; }
        unsigned int GetHeight() { return xHeight; }

    protected:

    private:
        SDL_Texture* oTexture;
        SDL_Renderer* oRenderer;
        unsigned int xWidth;
        unsigned int xHeight;
        double xAngle = 0;
        SDL_Point ptCenter = {31,31};
};

#endif // TEXTURE_H
