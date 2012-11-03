#include "SDL.h"
#include "SDL_image.h"
#include "DrawableObject.h"
#include "SDL_draw.h"
#include "TransformHandler.h"
#include "InputHandler.h"
#include "Camera.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

const extern int SCREEN_WIDTH = 1400;
const extern int SCREEN_HEIGHT = 900;
const extern int SCREEN_BPP = 32;
const extern int FPS = 60;

// Colors
Uint32 white;
Uint32 green;

SDL_Surface * screen;
TransformHandler * transformHandler;
InputHandler * inputHandler;
vector<DrawableObject*> * objects;
Camera *camera;

void init(){
	//Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ){
		
    }

	//Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

	//Set the window caption
    SDL_WM_SetCaption( "3D-Engine", NULL );

	//Setup handlers
	transformHandler = new TransformHandler();
	inputHandler = new InputHandler();

	// Setup colors
	white = SDL_MapRGB(screen->format, 255,255,255);
	green = SDL_MapRGB(screen->format, 0,255,0);

	// Create camera
	camera = new Camera(new Point3D(300.0f, 600.0f, 900.0f), new Point3D(0.0f, 0.0f, 0.0f), 60.0f);

	// Add objects - TODO: read from file
	objects = new vector<DrawableObject*>();
	Point3D *pos = new Point3D(0.0f, 100.0f, 0.0f);
	DrawableObject *obj = new DrawableObject(pos);

	Point3D *a1 = new Point3D(0.0f, 0.0f, 100.0f);
	Point3D *b1 = new Point3D(0.0f, 100.0f, 0.0f);
	Point3D *c1 = new Point3D(100.0f, 0.0f, 0.0f);
	Triangle *tri1 = new Triangle(a1,b1,c1);

	Point3D *a2 = new Point3D(0.0f, 0.0f, 100.0f);
	Point3D *b2 = new Point3D(0.0f, -100.0f, 0.0f);
	Point3D *c2 = new Point3D(100.0f, 0.0f, 0.0f);
	Triangle *tri2 = new Triangle(a2,b2,c2);

	Point3D *a3 = new Point3D(0.0f, 0.0f, 100.0f);
	Point3D *b3 = new Point3D(0.0f, 100.0f, 0.0f);
	Point3D *c3 = new Point3D(-100.0f, 0.0f, 0.0f);
	Triangle *tri3 = new Triangle(a3,b3,c3);

	Point3D *a4 = new Point3D(0.0f, 0.0f, 100.0f);
	Point3D *b4 = new Point3D(0.0f, -100.0f, 0.0f);
	Point3D *c4 = new Point3D(-100.0f, 0.0f, 0.0f);
	Triangle *tri4 = new Triangle(a4,b4,c4);

	obj->addTriangle(tri1);
	obj->addTriangle(tri2);
	obj->addTriangle(tri3);
	obj->addTriangle(tri4);

	Point3D *a5 = new Point3D(0.0f, 0.0f, -100.0f);
	Point3D *b5 = new Point3D(0.0f, 100.0f, 0.0f);
	Point3D *c5 = new Point3D(100.0f, 0.0f, 0.0f);
	Triangle *tri5 = new Triangle(a5,b5,c5);

	Point3D *a6 = new Point3D(0.0f, 0.0f, -100.0f);
	Point3D *b6 = new Point3D(0.0f, -100.0f, 0.0f);
	Point3D *c6 = new Point3D(100.0f, 0.0f, 0.0f);
	Triangle *tri6 = new Triangle(a6,b6,c6);

	Point3D *a7 = new Point3D(0.0f, 0.0f, -100.0f);
	Point3D *b7 = new Point3D(0.0f, 100.0f, 0.0f);
	Point3D *c7 = new Point3D(-100.0f, 0.0f, 0.0f);
	Triangle *tri7 = new Triangle(a7,b7,c7);

	Point3D *a8 = new Point3D(0.0f, 0.0f, -100.0f);
	Point3D *b8 = new Point3D(0.0f, -100.0f, 0.0f);
	Point3D *c8 = new Point3D(-100.0f, 0.0f, 0.0f);
	Triangle *tri8 = new Triangle(a8,b8,c8);

	obj->addTriangle(tri5);
	obj->addTriangle(tri6);
	obj->addTriangle(tri7);
	obj->addTriangle(tri8);

	objects->push_back(obj);
}

void update(int ticks){
	if (inputHandler->right()){
		if (inputHandler->control()){
			for (unsigned int i = 0; i < objects->size(); i++){
				transformHandler->translateObjectPosition(objects->at(0), 1.0f, 0.0f, 0.0f);
			}
		} else {
			for (unsigned int i = 0; i < objects->size(); i++){
				transformHandler->rotateObjectY(objects->at(0), 0.1f);
			}
		}
	}

	if (inputHandler->left()){
		if (inputHandler->control()){
			for (unsigned int i = 0; i < objects->size(); i++){
				transformHandler->translateObjectPosition(objects->at(0), -1.0f, 0.0f, 0.0f);
			}
		} else {
			for (unsigned int i = 0; i < objects->size(); i++){
				transformHandler->rotateObjectY(objects->at(0), -0.1f);
			}
		}
	}

	if (inputHandler->up()){
		if (inputHandler->control()){
			for (unsigned int i = 0; i < objects->size(); i++){
				transformHandler->translateObjectPosition(objects->at(0), 0.0f, 1.0f, 0.0f);
			}
		} else if (inputHandler->shift()){
			for (unsigned int i = 0; i < objects->size(); i++){
				transformHandler->scaleObjectUniform(objects->at(0), 1.1f);
			}
		} else {
			for (unsigned int i = 0; i < objects->size(); i++){
				transformHandler->rotateObjectX(objects->at(0), 0.1f);
			}
		}
	}

	if (inputHandler->down()){
		if (inputHandler->control()){
			for (unsigned int i = 0; i < objects->size(); i++){
				transformHandler->translateObjectPosition(objects->at(0), 0.0f, -1.0f, 0.0f);
			}
		} else if (inputHandler->shift()){
			for (unsigned int i = 0; i < objects->size(); i++){
				transformHandler->scaleObjectUniform(objects->at(0), 0.9f);
			}
		} else {
			for (unsigned int i = 0; i < objects->size(); i++){
				transformHandler->rotateObjectX(objects->at(0), -0.1f);
			}
		}
	}

	if (inputHandler->w()){
		if (inputHandler->control()){
			for (unsigned int i = 0; i < objects->size(); i++){
				transformHandler->translateObjectPosition(objects->at(0), 0.0f, 0.0f, 1.0f);
			}
		} else {
			for (unsigned int i = 0; i < objects->size(); i++){
				transformHandler->rotateObjectZ(objects->at(0), 0.1f);
			}
		}
	}

	if (inputHandler->s()){
		if (inputHandler->control()){
			for (unsigned int i = 0; i < objects->size(); i++){
				transformHandler->translateObjectPosition(objects->at(0), 0.0f, 0.0f, -1.0f);
			}
		} else {
			for (unsigned int i = 0; i < objects->size(); i++){
				transformHandler->rotateObjectZ(objects->at(0), -0.1f);
			}
		}
	}
}

void drawLine(int x1, int y1, int x2, int y2, int color){

	// Only draw inside screen
	if (x1 >= 0 && x2 >= 0 && y1 >= 0 && y2 >= 0){
		if (x2 < SCREEN_WIDTH && x2 < SCREEN_WIDTH && y1 < SCREEN_HEIGHT && y2 < SCREEN_HEIGHT){
			Draw_Line(screen, x1, y1, x2, y2, color);
		}
	}
}

void drawObject(DrawableObject *_object){

	for (unsigned int i = 0; i < _object->getTriangles()->size(); i++){
		int x1 = int(_object->getTriangles()->at(i)->getA()->getX());
		int y1 = int(_object->getTriangles()->at(i)->getA()->getY());
		int x2 = int(_object->getTriangles()->at(i)->getB()->getX());
		int y2 = int(_object->getTriangles()->at(i)->getB()->getY());
		drawLine(x1, y1, x2, y2, green); 
		int x3 = int(_object->getTriangles()->at(i)->getC()->getX());
		int y3 = int(_object->getTriangles()->at(i)->getC()->getY());
		drawLine(x2, y2, x3, y3, green); 
		drawLine(x3, y3, x1, y1, green); 
	}
}


void draw(){
	//Update the screen
	
    if( SDL_Flip( screen ) == -1 ){

    }
	SDL_FillRect(screen,NULL, 0x000000); 
	
	// Draw objects
	for(unsigned int i = 0; i < objects->size(); i++){
		
		DrawableObject *clone = objects->at(i)->clone();
		// From object to world coordinates
		transformHandler->translateObject(clone, clone->getPosition()->getX(), clone->getPosition()->getY(), clone->getPosition()->getZ());
		
		// Camera Location Transform
		transformHandler->translateObject(	clone, 
											-camera->getPosition()->getX(), 
											-camera->getPosition()->getY(), 
											-camera->getPosition()->getZ());
		
		// Camera Look Transform
		transformHandler->objectToViewSpace(clone, camera);
		
		// Perspective Transform
		transformHandler->objectToNDC(clone, camera);
		
		// Now map into screen coordinates
		for(unsigned int t = 0; t < clone->getTriangles()->size(); t++){
			float x = clone->getTriangles()->at(t)->getA()->getX();
			float y = clone->getTriangles()->at(t)->getA()->getY();
			clone->getTriangles()->at(t)->getA()->setX( x * (SCREEN_WIDTH/2.0) + (SCREEN_WIDTH/2.0));
			clone->getTriangles()->at(t)->getA()->setY( y * (SCREEN_WIDTH/2.0) + (SCREEN_WIDTH/2.0));

			x = clone->getTriangles()->at(t)->getB()->getX();
			y = clone->getTriangles()->at(t)->getB()->getY();
			clone->getTriangles()->at(t)->getB()->setX( x * (SCREEN_WIDTH/2.0) + (SCREEN_WIDTH/2.0));
			clone->getTriangles()->at(t)->getB()->setY( y * (SCREEN_WIDTH/2.0) + (SCREEN_WIDTH/2.0));

			x = clone->getTriangles()->at(t)->getC()->getX();
			y = clone->getTriangles()->at(t)->getC()->getY();
			clone->getTriangles()->at(t)->getC()->setX( x * (SCREEN_WIDTH/2.0) + (SCREEN_WIDTH/2.0));
			clone->getTriangles()->at(t)->getC()->setY( y * (SCREEN_WIDTH/2.0) + (SCREEN_WIDTH/2.0));
		}
				
		drawObject(clone);
		delete clone;
	}
	
}

int main( int argc, char* args[] ){

	// Initialize
	init();
	
	// Prepare timer and stuff
	Uint32 oldTime = SDL_GetTicks();
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
				case SDL_KEYDOWN : inputHandler->handleKeyEvent(&sdlEvent); break;
				case SDL_KEYUP : inputHandler->handleKeyEvent(&sdlEvent); break;
			}
		}

		// Update
		int newTime = SDL_GetTicks();
		int TimeSinceLastFrame = newTime - oldTime;
		oldTime = newTime;

		update(TimeSinceLastFrame);

		// Draw
		draw();

		if ((SDL_GetTicks() - loopStarted) < 1000/FPS){
			SDL_Delay((1000/FPS) - (SDL_GetTicks() - loopStarted));
		}
	}

    //Quit SDL
    SDL_Quit();
    
    //Return
    return 0;
}