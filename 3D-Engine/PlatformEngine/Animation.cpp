#include "Animation.h"
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
using namespace std;

Animation::Animation(int rate)
{
	frames = new vector<SDL_Surface*>();
	frameRate = rate;
	currentFrame = 0;
	ticks = 0;
}

Animation::Animation(vector<SDL_Surface*> * frms, int rate)
{
	frames = frms;
	frameRate = rate;
	currentFrame = 0;
	ticks = 0;
}

void Animation::tick(int t){
	ticks += t;
	if (ticks >= frameRate){
		ticks = 0;
		if (currentFrame >= frames->size()-1){
			currentFrame = 0;
		} else {
			currentFrame++;
		}
	}
}

void Animation::addFrame(SDL_Surface* frame){
	frames->push_back(frame);
}

vector<SDL_Surface*> * Animation::getFrames(){
	return frames;
}

SDL_Surface * Animation::getCurrentFrame(){
	return frames->at(currentFrame);
}

int Animation::getFrameRate(){
	return frameRate;
}

void Animation::setFrameRate(int rate){
	frameRate = rate;
}

Animation::~Animation(void)
{
}
