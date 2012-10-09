#include "Sprite.h"
#include "SDL.h"
#include <string>
#include "SDL_image.h"


Sprite::Sprite(void)
{
}

Sprite::Sprite(int xpos, int ypos, int height, int width, SDL_Surface* image){
	x = xpos;
	y = ypos;
	h = height;
	w = width;
	img = image;
}

SDL_Surface* Sprite::getImage(){
	return img;
}


Sprite::~Sprite(void)
{
}
