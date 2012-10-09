#include "Fireball.h"
#include "main.h"

Fireball::Fireball(int xpos, int ypos,  double xspeed, double yspeed, SDL_Surface * image)
{
	x = xpos;
	y = ypos;
	xMovement = xspeed;
	yMovement = yspeed;
	width = FIREBALL_WIDTH;
	height = FIREBALL_HEIGHT;
	speed = MONSTER_SPEED;
	bounceEffect = 0.8;
	walkingRight = new Animation(10);
	walkingLeft = new Animation(10);
	dying = new Animation(10);
	alive = true;
	onGround = false;
	timeAlive = 0;
	walkingRight->addFrame(image);
	currentAnimation = walkingRight;
	typeName = "Fireball";
}

void Fireball::setupAnimations(){
}

void Fireball::act(int ticks){
	/*
	timeAlive += ticks;
	if (timeAlive > FIREBALL_TIME_ALIVE){
		die();
	}
	*/
	if ((xMovement < 0.1 && xMovement > -0.1) && (yMovement < 0.1 && yMovement > -0.1) && onGround){
		die();
	}
}

Fireball::~Fireball(void)
{
}
