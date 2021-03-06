#include "Base.h"

Texture::Texture()
{
	// Initialize
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	// Deallocate
	free();
}

bool Texture::loadFromFile( std::string path )
{
	// Get rid of preexisting texture
	free();

	// The final texture
	SDL_Texture* newTexture = NULL;

	// Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if ( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		// Color key image: Magenta
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0x00, 0xFF ) );

		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface( Game::Renderer(), loadedSurface );
		if ( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			// Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	// Return success
	texture = newTexture;
	return texture != NULL;
}

void Texture::free()
{
	// Free texture if it exists
	if ( texture != NULL )
	{
		SDL_DestroyTexture( texture );
		texture = NULL;
		width = 0;
		height = 0;
	}
}

void Texture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	// Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };

	// Set clip rendering dimensions
	if ( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx( Game::Renderer(), texture, clip, &renderQuad, angle, center, flip );
}