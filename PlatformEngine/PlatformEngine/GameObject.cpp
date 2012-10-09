#include "GameObject.h"

bool GameObject::isAlive(){
	return alive;
}

bool GameObject::isOnGround(){
	return onGround;
}

void GameObject::die(){
	xMovement = 0.0;
	yMovement = 0.0;
	alive = false;
}

void GameObject::resurrect(){
	xMovement = 0.0;
	yMovement = 0.0;
	alive = true;
}

void GameObject::setOnGround(bool ground){
	onGround = ground;
}

int GameObject::getX(){
	return x;
}

int GameObject::getY(){
	return y;
}

string GameObject::getTypeName(){
	return typeName;
}

double GameObject::getXMovement(){
	return xMovement;
}

double GameObject::getYMovement(){
	return yMovement;
}

double GameObject::getBounceEffect(){
	return bounceEffect;
}

void GameObject::setXMovement(double movement){
	xMovement = movement;
}

void GameObject::setYMovement(double movement){
	yMovement = movement;
}

int GameObject::getWidth(){
	return width;
}

int GameObject::getHeight(){
	return height;
}

double GameObject::getSpeed(){
	return speed;
}

void GameObject::setX(int xpos){
	x = xpos;
}

void GameObject::setY(int ypos){
	y = ypos;
}

void GameObject::setWalkingRightAnim(Animation * animation){
	walkingRight = animation;
}

void GameObject::setWalkingLeftAnim(Animation * animation){
	walkingLeft = animation;
}

void GameObject::setDyingAnim(Animation * animation){
	dying = animation;
}

void GameObject::setCurrentAnim(Animation * animation){
	currentAnimation = animation;
}

Animation * GameObject::getCurrentAnim(){
	return currentAnimation;
}

Animation * GameObject::getRightAnim(){
	return walkingRight;
}

Animation * GameObject::getLeftAnim(){
	return walkingLeft;
}

Animation * GameObject::getDyingAnim(){
	return dying;
}

GameObject::~GameObject(void)
{
}
