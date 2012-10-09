#include "SDL.h"
#include <string>
#include "SDL_image.h"
#include <vector>
using namespace std;

#pragma once
class Animation
{
private:
	vector<SDL_Surface*> * frames;
	int currentFrame;
	int frameRate;
	int ticks;
public:
	vector<SDL_Surface*> * getFrames();
	void tick(int ticks);
	int getFrameRate();
	SDL_Surface * getCurrentFrame();
	void setFrameRate(int rate);
	void addFrame(SDL_Surface* frame);
	Animation(int rate);
	Animation(vector<SDL_Surface*> * frms, int rate);
	~Animation(void);
};

