#include "SDL.h"
#pragma once

class InputController
{
	bool leftDown;
	bool rightDown;
	bool upDown;
	bool downDown;
	bool spaceDown;

public:
	void handleKeyEvent(SDL_Event * sdlEvent);
	bool right();
	bool left();
	bool up();
	bool down();
	bool jump();
	InputController(void);
	~InputController(void);
};

