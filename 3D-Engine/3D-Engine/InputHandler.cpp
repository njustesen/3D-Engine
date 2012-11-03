#include "InputHandler.h"

InputHandler::InputHandler(void)
{
	rightDown = false;
	leftDown = false;
	upDown = false;
	downDown = false;
	wDown = false;
	sDown = false;
	aDown = false;
	dDown = false;
	spaceDown = false;
	shiftDown = false;
	controlDown = false;
}

void InputHandler::handleKeyEvent(SDL_Event * sdlEvent){
	if (sdlEvent->type == SDL_KEYDOWN){
		switch(sdlEvent->key.keysym.sym){
			case SDLK_RIGHT : rightDown = true; break;
			case SDLK_LEFT : leftDown = true; break;
			case SDLK_UP : upDown = true; break;
			case SDLK_DOWN : downDown = true; break;
			case SDLK_w : wDown = true; break;
			case SDLK_s : sDown = true; break;
			case SDLK_a : aDown = true; break;
			case SDLK_d : dDown = true; break;
			case SDLK_SPACE : spaceDown = true; break;
			case SDLK_LSHIFT : shiftDown = true; break;
			case SDLK_LCTRL : controlDown = true; break;
		}
	} else if (sdlEvent->type == SDL_KEYUP){
		switch(sdlEvent->key.keysym.sym){
			case SDLK_RIGHT : rightDown = false; break;
			case SDLK_LEFT : leftDown = false; break;
			case SDLK_UP : upDown = false; break;
			case SDLK_DOWN : downDown = false; break;
			case SDLK_w : wDown = false; break;
			case SDLK_s : sDown = false; break;
			case SDLK_a : aDown = false; break;
			case SDLK_d : dDown = false; break;
			case SDLK_LSHIFT : shiftDown = false; break;
			case SDLK_LCTRL : controlDown = false; break;
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

bool InputHandler::w(){
	return wDown;
}

bool InputHandler::s(){
	return sDown;
}

bool InputHandler::a(){
	return aDown;
}

bool InputHandler::d(){
	return dDown;
}

bool InputHandler::space(){
	return spaceDown;
}

bool InputHandler::shift(){
	return shiftDown;
}

bool InputHandler::control(){
	return controlDown;
}

InputHandler::~InputHandler(void)
{
}