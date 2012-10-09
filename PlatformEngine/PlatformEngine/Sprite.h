#include "SDL.h"
#include <string>
#include "SDL_image.h"

#pragma once
class Sprite
{
private:
	SDL_Surface * img;
	int x;
	int y;
	int h;
	int w;

public:
	int getX();
	int getY();
	int getHeight();
	int getWidth();
	SDL_Surface * getImage();
	Sprite(void);
	Sprite(int xpos, int ypos, int height, int width, SDL_Surface * image);
	~Sprite(void);
};

