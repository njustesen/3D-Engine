#include "Monster.h"
#include "main.h"
#include <string>

Monster::Monster(int xpos, int ypos, string dir)
{
	x = xpos;
	y = ypos;
	width = MONSTER_WIDTH;
	height = MONSTER_HEIGHT;
	speed = MONSTER_SPEED;
	bounceEffect = 0.2;
	xMovement = 0.0;
	yMovement = 0.0;
	walkingRight = new Animation(10);
	walkingLeft = new Animation(10);
	dying = new Animation(10);
	alive = true;
	onGround = false;
	timeSinceLastAttack = 0;
	setupAnimations();
	typeName = "Monster";
	direction = dir;
}

void Monster::setupAnimations(){
	walkingRight->addFrame(loadImage("../Assets/Anim/Monster/pipe.png"));

	currentAnimation = walkingRight;
}

void Monster::act(int ticks){
	timeSinceLastAttack += ticks;
	if (timeSinceLastAttack > MONSTER_RATE_OF_FIRE){
		timeSinceLastAttack = 0;
		monsterFire(double(x), double(y), direction);
	}
}

Monster::~Monster(void)
{
}
