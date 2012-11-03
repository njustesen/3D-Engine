#include "SDL.h"
#pragma once

class InputHandler
{
private:
	bool leftDown;
	bool rightDown;
	bool upDown;
	bool downDown;
	bool spaceDown;
	bool shiftDown;
	bool wDown;
	bool sDown;
	bool aDown;
	bool dDown;
	bool controlDown;
public:
	void handleKeyEvent(SDL_Event * sdlEvent);
	bool right();
	bool left();
	bool up();
	bool down();
	bool w();
	bool s();
	bool a();
	bool d();
	bool space();
	bool shift();
	bool control();
	InputHandler(void);
	~InputHandler(void);
};