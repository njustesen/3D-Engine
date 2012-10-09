#include "InputHandler.h"

InputHandler::InputHandler(void)
{
	rightDown = false;
	leftDown = false;
	upDown = false;
	downDown = false;
	spaceDown = false;
}

void InputHandler::handleKeyEvent(SDL_Event * sdlEvent){
	if (sdlEvent->type == SDL_KEYDOWN){
		switch(sdlEvent->key.keysym.sym){
			case SDLK_RIGHT : rightDown = true; break;
			case SDLK_LEFT : leftDown = true; break;
			case SDLK_UP : upDown = true; break;
			case SDLK_DOWN : downDown = true; break;
			case SDLK_SPACE : spaceDown = true; break;
		}
	} else if (sdlEvent->type == SDL_KEYUP){
		switch(sdlEvent->key.keysym.sym){
			case SDLK_RIGHT : rightDown = false; break;
			case SDLK_LEFT : leftDown = false; break;
			case SDLK_UP : upDown = false; break;
			case SDLK_DOWN : downDown = false; break;
			case SDLK_SPACE : spaceDown = false; break;
		}
	}
}

bool InputHandler::right(){
	return rightDown;
}

bool InputHandler::left(){
	return leftDown;
}

bool InputHandler::up(){
	return upDown;
}

bool InputHandler::down(){
	return downDown;
}

InputHandler::~InputHandler(void)
{
}