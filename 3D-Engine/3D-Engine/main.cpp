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
	camera = new Camera(new Point(700.0f, 700.0f, 700.0f), new Point(0.0f, 0.0f, 0.0f), transformHandler);

	// Add objects - TODO: read from file
	objects = new vector<DrawableObject*>();
	Point *pos = new Point(300.0f, -300.0f, 60.0f);
	DrawableObject *obj = new DrawableObject(pos);
	Point *a = new Point(70.0f, 70.0f, 20.0f);
	Point *b = new Point(10.0f, 80.0f, 16.0f);
	Point *c = new Point(22.0f, 80.0f, 56.0f);
	Triangle *tri = new Triangle(a,b,c);
	obj->addTriangle(tri);
	objects->push_back(obj);

	int i = 0;
}

void update(int ticks){
	if (inputHandler->right()){
		if (inputHandler->control()){
			for (int i = 0; i < objects->size(); i++){
				objects->at(0)->translate(transformHandler, 1.0f, 0.0f, 0.0f);
			}
		} else {
			for (int i = 0; i < objects->size(); i++){
				objects->at(0)->rotateX(transformHandler, 0.1f);
			}
		}
	}

	if (inputHandler->left()){
		if (inputHandler->control()){
			for (int i = 0; i < objects->size(); i++){
				objects->at(0)->translate(transformHandler, -1.0f, 0.0f, 0.0f);
			}
		} else {
			for (int i = 0; i < objects->size(); i++){
				objects->at(0)->rotateX(transformHandler, -0.1f);
			}
		}
	}

	if (inputHandler->up()){
		if (inputHandler->control()){
			for (int i = 0; i < objects->size(); i++){
				objects->at(0)->translate(transformHandler, 0.0f, 1.0f, 0.0f);
			}
		} else if (inputHandler->shift()){
			for (int i = 0; i < objects->size(); i++){
				objects->at(0)->scaleUniform(transformHandler, 1.1f);
			}
		} else {
			for (int i = 0; i < objects->size(); i++){
				objects->at(0)->rotateY(transformHandler, 0.1f);
			}
		}
	}

	if (inputHandler->down()){
		if (inputHandler->control()){
			for (int i = 0; i < objects->size(); i++){
				objects->at(0)->translate(transformHandler, 0.0f, -1.0f, 0.0f);
			}
		} else if (inputHandler->shift()){
			for (int i = 0; i < objects->size(); i++){
				objects->at(0)->scaleUniform(transformHandler, 0.9f);
			}
		} else {
			for (int i = 0; i < objects->size(); i++){
				objects->at(0)->rotateY(transformHandler, -0.1f);
			}
		}
	}

	if (inputHandler->w()){
		if (inputHandler->control()){
			for (int i = 0; i < objects->size(); i++){
				objects->at(0)->translate(transformHandler, 0.0f, 0.0f, 1.0f);
			}
		} else {
			for (int i = 0; i < objects->size(); i++){
				objects->at(0)->rotateZ(transformHandler, 0.1f);
			}
		}
	}

	if (inputHandler->s()){
		if (inputHandler->control()){
			for (int i = 0; i < objects->size(); i++){
				objects->at(0)->translate(transformHandler, 0.0f, 0.0f, -1.0f);
			}
		} else {
			for (int i = 0; i < objects->size(); i++){
				objects->at(0)->rotateZ(transformHandler, -0.1f);
			}
		}
	}
}

void drawLine(int x1, int y1, int x2, int y2, int color){
	/*
	x1 += SCREEN_WIDTH/2;
	x2 += SCREEN_WIDTH/2;
	y1 += SCREEN_HEIGHT/2;
	y2 += SCREEN_HEIGHT/2;
	*/

	// Only draw inside screen
	if (x1 >= 0 && x2 >= 0 && y1 >= 0 && y2 >= 0){
		if (x2 < SCREEN_WIDTH && x2 < SCREEN_WIDTH && y1 < SCREEN_HEIGHT && y2 < SCREEN_HEIGHT){
			Draw_Line(screen, x1, y1, x2, y2, color);
		}
	}
}

void drawObject(DrawableObject *object){

	// Draw all triangles
	for (int i = 0; i < object->getTriangles()->size(); i++){
		int x1 = int(object->getTriangles()->at(i)->getA()->getX());
		int y1 = int(object->getTriangles()->at(i)->getA()->getY());
		int z1 = int(object->getTriangles()->at(i)->getA()->getZ());
		int x2 = int(object->getTriangles()->at(i)->getB()->getX());
		int y2 = int(object->getTriangles()->at(i)->getB()->getY());
		int z2 = int(object->getTriangles()->at(i)->getB()->getZ());
		drawLine(x1, y1, x2, y2, green); 
		int x3 = int(object->getTriangles()->at(i)->getC()->getX());
		int y3 = int(object->getTriangles()->at(i)->getC()->getY());
		int z3 = int(object->getTriangles()->at(i)->getC()->getZ());
		drawLine(x2, y2, x3, y3, green); 
		drawLine(x3, y3, x1, y1, green); 
	}
}

void draw(){
	//Update the screen
    if( SDL_Flip( screen ) == -1 ){
    }

	vector<DrawableObject*> *objectsToDraw = camera->getTransformedObjects(screen, objects);
	
	// Draw objects
	for(int i = 0; i < objects->size(); i++){
		drawObject(objects->at(i));
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