#include "InputController.h"

InputController::InputController(void)
{
	rightDown = false;
	leftDown = false;
	upDown = false;
	downDown = false;
	spaceDown = false;
}

void InputController::handleKeyEvent(SDL_Event * sdlEvent){
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

bool InputController::right(){
	return rightDown;
}

bool InputController::left(){
	return leftDown;
}

bool InputController::up(){
	return upDown;
}

bool InputController::down(){
	return downDown;
}

bool InputController::jump(){
	return spaceDown;
}


InputController::~InputController(void)
{
}
