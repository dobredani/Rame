#include "Texture.h"
#include <stdio.h>

using namespace std;

Texture::Texture(SDL_Renderer* argRenderer)
{
    oTexture = NULL;
    oRenderer = argRenderer;
    xWidth = 0;
    xHeight = 0;

	if( oRenderer == NULL )
		printf( "Renderer not available!\n");
}

Texture::~Texture()
{
    FreeMemory();
}

void Texture::FreeMemory()
{
	if( oTexture != NULL )
	{
		SDL_DestroyTexture( oTexture );
		oTexture = NULL;
		xWidth = 0;
		xHeight = 0;
	}
}

bool Texture::LoadImage(string sFilePath)
{
    if (oRenderer == NULL) return false;

    FreeMemory();

	SDL_Texture* oNewTexture = NULL;

	SDL_Surface* oSurface = IMG_Load( sFilePath.c_str() );
	if( oSurface == NULL )
		printf( "Unable to load image %s! SDL_image Error: %s\n", sFilePath.c_str(), IMG_GetError() );
	else
	{
		//Color key image
		SDL_SetColorKey( oSurface, SDL_TRUE, SDL_MapRGB( oSurface->format, 0xFF, 0xFF, 0xFF ) );

        oNewTexture = SDL_CreateTextureFromSurface( oRenderer, oSurface );
		if( oNewTexture == NULL )
			printf( "Unable to create texture from %s! SDL Error: %s\n", sFilePath.c_str(), SDL_GetError() );
		else
		{
			xWidth = oSurface->w;
			xHeight = oSurface->h;
		}

		SDL_FreeSurface( oSurface );
	}

	oTexture = oNewTexture;
	return oTexture != NULL;
}

void Texture::Render(unsigned int xLeft, unsigned int xTop, double xAngle, SDL_Rect* oSpriteRect, double xZoomFactor)
{

    if (oRenderer == NULL) return;

	SDL_Rect renderQuad = { xLeft, xTop, xWidth, xHeight };

	if( oSpriteRect != NULL )
	{
		renderQuad.w = oSpriteRect->w * xZoomFactor;
		renderQuad.h = oSpriteRect->h * xZoomFactor;

//        ptCenter.x = oSpriteRect->x + renderQuad.w/2;
//        ptCenter.y = oSpriteRect->y + renderQuad.h/2;

	}

    ptCenter.x = renderQuad.w/2;
    ptCenter.y = renderQuad.h/2;

	SDL_RenderCopyEx( oRenderer, oTexture, oSpriteRect, &renderQuad, xAngle, &ptCenter, SDL_FLIP_NONE);
}


