#include "Character.h"
#include "Sprite.h"
#include "main.h"
#include "GameObject.h"
#include "Point2D.h"
#include <vector>
using namespace std;

Character::Character(int xpos, int ypos, int w, int h, double spd, double bounce)
{
	x = xpos;
	y = ypos;
	width = w;
	height = h;
	speed = spd;
	bounceEffect = bounce;
	xMovement = 0.0;
	yMovement = 0.0;
	walkingRight = new Animation(4);
	walkingLeft = new Animation(4);
	dying = new Animation(10);
	alive = true;
	onGround = false;
	setupAnimations();
	typeName = "Character";
}

void Character::setupAnimations(){
	walkingRight->addFrame(loadImage("../Assets/Anim/CharWalkRight/1.png"));
	walkingRight->addFrame(loadImage("../Assets/Anim/CharWalkRight/2.png"));
	walkingRight->addFrame(loadImage("../Assets/Anim/CharWalkRight/3.png"));
	walkingRight->addFrame(loadImage("../Assets/Anim/CharWalkRight/4.png"));
	walkingRight->addFrame(loadImage("../Assets/Anim/CharWalkRight/5.png"));
	walkingRight->addFrame(loadImage("../Assets/Anim/CharWalkRight/6.png"));
	walkingRight->addFrame(loadImage("../Assets/Anim/CharWalkRight/7.png"));
	walkingRight->addFrame(loadImage("../Assets/Anim/CharWalkRight/8.png"));
	walkingRight->addFrame(loadImage("../Assets/Anim/CharWalkRight/9.png"));
	walkingRight->addFrame(loadImage("../Assets/Anim/CharWalkRight/10.png"));
	walkingRight->addFrame(loadImage("../Assets/Anim/CharWalkRight/11.png"));
	walkingRight->addFrame(loadImage("../Assets/Anim/CharWalkRight/12.png"));

	walkingLeft->addFrame(loadImage("../Assets/Anim/CharWalkLeft/1.png"));
	walkingLeft->addFrame(loadImage("../Assets/Anim/CharWalkLeft/2.png"));
	walkingLeft->addFrame(loadImage("../Assets/Anim/CharWalkLeft/3.png"));
	walkingLeft->addFrame(loadImage("../Assets/Anim/CharWalkLeft/4.png"));
	walkingLeft->addFrame(loadImage("../Assets/Anim/CharWalkLeft/5.png"));
	walkingLeft->addFrame(loadImage("../Assets/Anim/CharWalkLeft/6.png"));
	walkingLeft->addFrame(loadImage("../Assets/Anim/CharWalkLeft/7.png"));
	walkingLeft->addFrame(loadImage("../Assets/Anim/CharWalkLeft/8.png"));
	walkingLeft->addFrame(loadImage("../Assets/Anim/CharWalkLeft/9.png"));
	walkingLeft->addFrame(loadImage("../Assets/Anim/CharWalkLeft/10.png"));
	walkingLeft->addFrame(loadImage("../Assets/Anim/CharWalkLeft/11.png"));
	walkingLeft->addFrame(loadImage("../Assets/Anim/CharWalkLeft/12.png"));

	dying->addFrame(loadImage("../Assets/Anim/Dying/1.png"));

	currentAnimation = walkingRight;
}

void Character::act(int ticks){}


Character::~Character(void)
{
}
