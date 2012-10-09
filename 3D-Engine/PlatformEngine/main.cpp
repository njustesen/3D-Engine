#include "SDL.h"
#include <string>
#include "SDL_image.h"
#include "Fireball.h"
#include "MapController.h"
#include "InputController.h"
#include "PhysicsController.h"
#include "Camera.h"
#include "Level.h"
#include "Character.h"
#include "Point2D.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//The attributes of the screen
const extern int SCREEN_WIDTH = 1000;
const extern int SCREEN_HEIGHT = 600;
const extern int SCREEN_BPP = 32;
const extern int TILE_SIZE = 32;
const extern int VISION = 32;
const extern double CHAR_SPEED = 20;
const extern int MONSTER_WIDTH = 24;
const extern int MONSTER_HEIGHT = 32;
const extern double MONSTER_SPEED = 14;
const extern int LEVEL_HEIGHT = 320;
const extern int LEVEL_WIDTH = 320;
const extern int CAMERA_DELAY = 500;
const extern int FPS = 60;
const extern double CHARACTER_JUMP_POWER = 7.8;
const extern int MONSTER_RATE_OF_FIRE = 3800; // HARD = 2500, MEDIUM = 3500, EASY = 4500
const extern int FIREBALL_TIME_ALIVE = 2500;
const extern int FIREBALL_WIDTH = 12;
const extern int FIREBALL_HEIGHT = 12;
const extern int SPAWN_TIME = 2600;

SDL_Surface * FIREBALL_IMAGE;
SDL_Surface * POS_DOT;
SDL_Surface * screen;
MapController * mapController;
Character * character;
vector<GameObject*> * gameObjects;
InputController * inputController;
PhysicsController * physicsController;
Camera * camera;
int timeSinceDeath;

string intToString(int i){
	stringstream out;
	out << i;
	return out.str();
}

SDL_Surface *loadImage( std::string filename ) {
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    
    //Load the image using SDL_image
    loadedImage = IMG_Load( filename.c_str() );
    
    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        
        //Free the old image
        SDL_FreeSurface( loadedImage );
    }
    
    //Return the optimized image
    return optimizedImage;
}

// Blitting function
void applySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;
    
    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;

	//Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

int initGame(){
	//Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return 1;    
    }

	//Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

	//If there was an error in setting up the screen
    if( screen == NULL ){
        return -1;    
    }

	//Set the window caption
    SDL_WM_SetCaption( "Dark something", NULL );

	// Setup controllers
	mapController =  new MapController("level1");

	// Create character
	character = new Character(	mapController->getCharX()*TILE_SIZE+TILE_SIZE/2, 
								mapController->getCharY()*TILE_SIZE+TILE_SIZE-1, 
								20,
								30, 
								CHAR_SPEED,
								0.0);

	timeSinceDeath = 0;

	gameObjects = new vector<GameObject*>;
	gameObjects->push_back(character);
	// Insert all objects in level
	for(int i = 0; i < mapController->getMonsters()->size(); i++){
		gameObjects->push_back(mapController->getMonsters()->at(i));
	}
	FIREBALL_IMAGE = loadImage("../Assets/Anim/Fireball/fireball.png");
	POS_DOT = loadImage("../Assets/Images/pos.png");

	inputController = new InputController();
	physicsController = new PhysicsController(character, gameObjects, mapController->getLevel());	
	camera = new Camera(character->getX(), character->getY());
	
	return 1;
}

void monsterFire(int x, int y, string dir){
	int xs = 3;
	int ys = -3;
	if (dir == "left"){
		xs *= -1;
	}
	gameObjects->push_back(new Fireball(x,y-MONSTER_HEIGHT/2, xs, ys, FIREBALL_IMAGE));
}

void moveCharacter(int ticks){

	int movement = int(character->getSpeed())*ticks/100;
	if (inputController->right()){ // 
		character->setXMovement(movement);
		character->setCurrentAnim(character->getRightAnim());
		if (character->isOnGround()){
			// Update character animation
			character->getCurrentAnim()->tick(ticks);
		}
	}
	if (inputController->left()){ // 
		character->setXMovement(movement*-1);
		character->setCurrentAnim(character->getLeftAnim());
		if (character->isOnGround()){
			// Update character animation
			character->getCurrentAnim()->tick(ticks);
		}
	}
	if (inputController->jump() && character->isOnGround()){
		character->setYMovement(CHARACTER_JUMP_POWER*-1);
	}

	character->setXMovement(character->getXMovement() * 0.9);

	// Spawn?
	if (!character->isAlive()){
		timeSinceDeath+=ticks;
		if (timeSinceDeath > SPAWN_TIME){
			timeSinceDeath = 0;
			character->setX(mapController->getCharX()*TILE_SIZE+TILE_SIZE/2);
			character->setY(mapController->getCharY()*TILE_SIZE+TILE_SIZE-1);
			character->resurrect();
			delete camera;
			camera = new Camera(character->getX(), character->getY());
		}
	}
}

void updateObjects(int ticks){
	for(int i = 0; i < gameObjects->size(); i++){
		gameObjects->at(i)->act(ticks);
	}
}

int update(int ticks){
	ticks = max(1, min(1000,ticks));
	moveCharacter(ticks);
	updateObjects(ticks);
	physicsController->gravity(ticks);
	physicsController->move();
	camera->move(ticks, character);
	return 1;
}

void drawLevel(){
	int xFrom = max(0, (character->getX()/TILE_SIZE)-VISION);
	int xTo = min(LEVEL_WIDTH, (character->getX()/TILE_SIZE)+VISION);

	int yFrom = max(0, (character->getY()/TILE_SIZE)-VISION);
	int yTo = min(LEVEL_WIDTH, (character->getY()/TILE_SIZE)+VISION);

	int cameraOffsetX = camera->getX() - SCREEN_WIDTH/2;
	int cameraOffsetY = camera->getY() - SCREEN_HEIGHT/2;

	for(int y = yFrom; y < yTo; y++){
		for(int x = xFrom; x < xTo; x++){
			int val = mapController->getLevel()->at(x,y);
			if (val > 0){
				applySurface(x*TILE_SIZE - cameraOffsetX, y*TILE_SIZE - cameraOffsetY, mapController->getTileImage(val),screen);
			}
		}
	}
}

void drawObjects(){
	for(int i = 0; i < gameObjects->size(); i++){
		if (gameObjects->at(i)->isAlive()){
			int cameraOffsetX = camera->getX() - SCREEN_WIDTH/2;
			int cameraOffsetY = camera->getY() - SCREEN_HEIGHT/2;

			//Apply the character to the screen
			SDL_Surface * img = gameObjects->at(i)->getCurrentAnim()->getCurrentFrame();

			applySurface( gameObjects->at(i)->getX() - img->w/2 - cameraOffsetX, gameObjects->at(i)->getY() - img->h - cameraOffsetY, img, screen);

			//Position dots
			//applySurface( gameObjects->at(i)->getX() - cameraOffsetX, gameObjects->at(i)->getY() - cameraOffsetY, POS_DOT, screen);
			//Position dots
			//applySurface( gameObjects->at(i)->getX() - gameObjects->at(i)->getWidth()/2 - cameraOffsetX, gameObjects->at(i)->getY() - cameraOffsetY, POS_DOT, screen);
			//Position dots
			//applySurface( gameObjects->at(i)->getX() + gameObjects->at(i)->getWidth()/2 - cameraOffsetX, gameObjects->at(i)->getY() - cameraOffsetY, POS_DOT, screen);
		}
	}
}

int draw(){
	//Load the background
	Sprite* bg = mapController->getBackground();

	//Apply the background to the screen
	applySurface( 0, 0, bg->getImage(), screen);

	// Apply the level to the screen
	drawLevel();

	// Apply Game Objects to the screen
	drawObjects();

	//Update the screen
    if( SDL_Flip( screen ) == -1 ){
        return -1;    
    }

	return 1;
}

int main( int argc, char* args[] ){

	// Init game
	if (initGame() == -1){
		return -1;
	}

	// Prepare timer and stuff
	Uint32 oldTime;
	oldTime = SDL_GetTicks();
	SDL_Event sdlEvent;
	bool quit = false;
	Uint32 loopStarted;

	// Game loop
	while(!quit){
		loopStarted = SDL_GetTicks();

		// Poll events
		while(SDL_PollEvent(&sdlEvent)) {
			switch(sdlEvent.type){
				case SDL_QUIT : quit = true; break;
				case SDL_KEYDOWN : inputController->handleKeyEvent(&sdlEvent); break;
				case SDL_KEYUP : inputController->handleKeyEvent(&sdlEvent); break;
			}
		}

		// Update
		int newTime = SDL_GetTicks();
		int TimeSinceLastFrame = newTime - oldTime;
		oldTime = newTime;
		if (update(TimeSinceLastFrame) == -1){
			return -1;
		}

		// Draw
		if (draw() == -1){
			return -1;
		}	

		if ((SDL_GetTicks() - loopStarted) < 1000/FPS){
			SDL_Delay((1000/FPS) - (SDL_GetTicks() - loopStarted));
		}
	}

    //Quit SDL
    SDL_Quit();
    
    //Return
    return 0;
}

