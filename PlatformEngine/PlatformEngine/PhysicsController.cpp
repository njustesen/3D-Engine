#include "PhysicsController.h"
#include "Character.h"
#include "Level.h"
#include "main.h"
#include <string>
#include <vector>
using namespace std;

PhysicsController::PhysicsController(void)
{
}

PhysicsController::PhysicsController(Character * chara, vector<GameObject*> * objects, Level * lv)
{
	character = chara;
	level = lv;
	charOnGround = false;
	gameObjects = objects;
}

double round(double number)
{
    return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
}

double PhysicsController::getGravitationalAcceleration(int ticks){
	return ((double)1000/ticks)/200;
}

void PhysicsController::gravity(int ticks){
	for(int i = 0; i < gameObjects->size(); i++){
		if (!gameObjects->at(i)->isOnGround()){
			double yMove = gameObjects->at(i)->getYMovement() + getGravitationalAcceleration(ticks);
			gameObjects->at(i)->setYMovement(yMove);
		}
	}
}

bool PhysicsController::isSolidRightStairs(int tile, int x, int y){
	int relX = x - ((x / TILE_SIZE) * TILE_SIZE);
	int relY = y - ((y / TILE_SIZE) * TILE_SIZE);

	if (relY > relX){
		return true;
	}
	return false;
}

bool PhysicsController::isSolidLeftStairs(int tile, int x, int y){
	int relX = x - ((x / TILE_SIZE) * TILE_SIZE);
	int relY = y - ((y / TILE_SIZE) * TILE_SIZE);

	if (relY > TILE_SIZE - relX){
		return true;
	}
	return false;
}

bool PhysicsController::isDeadly(int tile, string dir){
	if (tile==8 && dir=="down"){
		return true;
	}
	if (tile==9 && dir=="up"){
		return true;
	}
	return false;
}

bool PhysicsController::isSolid(int tile, int x, int y, string dir){
	if (dir=="left" || dir=="right"){
		switch(tile){
		case 0: return false;
		case 6: return isSolidRightStairs(tile, x, y);
		case 7: return isSolidLeftStairs(tile, x, y);
		case 10: return false;
		}
		return true;
	} else {
		switch(tile){
		case 0: return false;
		case 6: return isSolidRightStairs(tile, x, y);
		case 7: return isSolidLeftStairs(tile, x, y);
		case 10: return false;
		}
		return true;
	}
}

int PhysicsController::correctYPosition(int x, int y, int mapValue){
	int relX = x - ((x / TILE_SIZE) * TILE_SIZE);
	int relY = y - ((y / TILE_SIZE) * TILE_SIZE);

	if (mapValue == 1){
		return (y / TILE_SIZE) * TILE_SIZE;
	} else if (mapValue == 6){
		y += relX - relY;
		return y;
	} else if (mapValue == 7){
		y -= (relX) - (TILE_SIZE - relY);
		return y;
	}
	return (y / TILE_SIZE) * TILE_SIZE;
}

double PhysicsController::checkDownwards(GameObject * object, int x, int y, double moveX, double moveY){
	// Calculate positions
	int realX = x + object->getX();
	int realY = y + object->getY();
	int newRealX = realX + int(moveX);
	int newRealY = realY + int(moveY);

	// Check for collisions
	if (moveY > 0){
		// Collision?
		int mapValue = level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE);
		if (isSolid(mapValue, newRealX, newRealY, "down")){
			// Correct position
			newRealY = correctYPosition(newRealX, newRealY, mapValue);
			// Deadly?
			if (isDeadly(mapValue, "down")){
				object->die();
			} else if (object->getBounceEffect() > 0.0 && moveY > 1.6){ // Bounce??
				object->setYMovement(moveY*(-1)*object->getBounceEffect());
				object->setOnGround(false);
				newRealY--;
			} else {
				object->setYMovement(0);
				object->setOnGround(true);
			}
		} else {
			object->setOnGround(false);
		}
	}

	return newRealY - object->getY() - y;
}

double PhysicsController::checkUpwards(GameObject * object, int x, int y, double moveX, double moveY){
	// Calculate positions
	int realX = x + object->getX();
	int realY = y + object->getY();
	int newRealX = realX + int(moveX);
	int newRealY = realY + int(moveY);

	// Check for collisions
	if (moveY < 0){
		// Collision?
		int mapValue = level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE);
		if (isSolid(mapValue, newRealX, newRealY, "up")){
			// Correct position
			newRealY = min(realY, (newRealY / TILE_SIZE) * TILE_SIZE + TILE_SIZE);
			// Deadly?
			if (isDeadly(mapValue, "up")){
				object->die();
			} else if (object->getBounceEffect() > 0){
				object->setYMovement(object->getYMovement()*(-1)*object->getBounceEffect());
			} else {
				if (object->getYMovement() < 0){
					object->setYMovement(0);
				}
			}
		}
	}

	return newRealY - object->getY() - y;
}

double PhysicsController::checkRight(GameObject * object, int x, int y, double moveX, double moveY){
	// Calculate positions
	int realX = x + object->getX();
	int realY = y + object->getY();
	int newRealX = realX + int(moveX);
	int newRealY = realY + int(moveY);

	// Check for collisions
	if (moveX > 0){
		// Collision?
		int mapValue = level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE);
		if (isSolid(mapValue, newRealX, newRealY, "right")){
			// Bounce?
			if (object->getBounceEffect() > 0 && moveX > 1.6){
				object->setXMovement(moveX*(-1)*object->getBounceEffect());
				newRealX = max(realX, ((newRealX / TILE_SIZE) * TILE_SIZE - 1));
			} else {
				// Correct position
				newRealX = max(realX, ((newRealX / TILE_SIZE) * TILE_SIZE - 1));
				object->setXMovement(0);
			}
		}
	}

	return newRealX - object->getX() - x;
}

double PhysicsController::checkLeft(GameObject * object, int x, int y, double moveX, double moveY){
	// Calculate positions
	int realX = x + object->getX();
	int realY = y + object->getY();
	int newRealX = realX + int(moveX);
	int newRealY = realY + int(moveY);

	// Check for collisions
	if (moveX < 0){
		// Collision?
		int mapValue = level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE);
		if (isSolid(mapValue, newRealX, newRealY, "left")){
			// Bounce?
			if (object->getBounceEffect() > 0 && moveX < -1.6){
				object->setXMovement(moveX*(-1)*object->getBounceEffect());
				newRealX = min(realX, (newRealX / TILE_SIZE) * TILE_SIZE + TILE_SIZE);
			} else {
				newRealX = min(realX, (newRealX / TILE_SIZE) * TILE_SIZE + TILE_SIZE);
				object->setXMovement(0);
			}
		}
	}

	return newRealX - object->getX() - x;
}

void PhysicsController::move(){

	for(int i = 0; i < gameObjects->size(); i++){

		// get object properties
		gameObjects->at(i)->setOnGround(false);
		int width = gameObjects->at(i)->getWidth();
		int height = gameObjects->at(i)->getHeight();
		double moveX = gameObjects->at(i)->getXMovement();
		double moveY = gameObjects->at(i)->getYMovement();

		if (gameObjects->at(i)->isAlive()){

			// check for vertical collision
			moveY = checkDownwards(gameObjects->at(i), width / 2, 0, 0, moveY);
			moveY = checkDownwards(gameObjects->at(i), -width / 2, 0, 0, moveY);
			moveY = checkUpwards(gameObjects->at(i), width / 2, -height, 0, moveY);
			moveY = checkUpwards(gameObjects->at(i), -width / 2, -height, 0, moveY);

			// check for horizontal collision
			moveX = checkRight(gameObjects->at(i), width / 2, -1, moveX, moveY);
			moveX = checkRight(gameObjects->at(i), width / 2, -height+1, moveX, moveY);
			moveX = checkLeft(gameObjects->at(i), (width * (-1)) / 2, -1, moveX, moveY);
			moveX = checkLeft(gameObjects->at(i), (width * (-1)) / 2, -height+1, moveX, moveY);

			// Update position
			gameObjects->at(i)->setX(gameObjects->at(i)->getX() + int(moveX));
			gameObjects->at(i)->setY(gameObjects->at(i)->getY() + int(moveY));
		}
	}

	// Check if character hits Fireball
	checkFireballCollision();

}

void PhysicsController::checkFireballCollision(){

	int xDistance = character->getWidth()/2 + FIREBALL_WIDTH/2;
	int yDistance = character->getHeight()/2 + FIREBALL_HEIGHT/2;
	int charY = character->getY() - character->getHeight()/2;
	int charX = character->getX();

	for(int i = 0; i < gameObjects->size(); i++){
		// If fireball
		if (gameObjects->at(i)->getTypeName() == "Fireball" && gameObjects->at(i)->isAlive()){
			// Check collision
			if (charX - gameObjects->at(i)->getX() < xDistance &&
				gameObjects->at(i)->getX() - charX < xDistance){
				
				if (charY - (gameObjects->at(i)->getY() - FIREBALL_HEIGHT/2) < yDistance &&
					(gameObjects->at(i)->getY() - FIREBALL_HEIGHT/2) - charY < yDistance){
						character->die();
				}
			}
		}
	}
}

PhysicsController::~PhysicsController(void)
{
}
