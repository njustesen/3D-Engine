#include "MapController.h"
#include "GameObject.h"
#include "Monster.h"
#include "SDL.h"
#include "main.h"
#include "Level.h"
#include <string>
#include "SDL_image.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//The surfaces that will be used

MapController::MapController(void)
{

}

MapController::MapController(string levelName)
{
	loadLevel(levelName);
	loadTileset();
}

void MapController::loadTileset()
{
	for (int i = 1; i <= 10; i++){
		tileset[i] = loadTileImage(i);
	}
}

int MapController::intFromChar(char c){
	switch(c){
		case '0' : return 0;
		case '1' : return 1;
		case '2' : return 2;
		case '3' : return 3;
		case '4' : return 4;
		case '5' : return 5;
		case '6' : return 6;
		case '7' : return 7;
		case '8' : return 8;
		case '9' : return 9;
		case 'g' : return 10;
	}
	return 0;
}

void MapController::loadLevel(string levelName){
	// Load background
	background = new Sprite(0,0,0,0, loadImage("../Assets/Images/background.png"));

	// Load level
	level = new Level();
	monsters = new vector<GameObject*>();
	string line;
	ifstream myfile ("../Levels/level1.lv");
	if (myfile.is_open()){
		int y = 0;
		while (myfile.good()){
			getline (myfile,line);
			for (int x = 0; x < line.length(); x++){
				// Remove tabs by dividing - ONLY WORKS FOR SINGLE CHAR TILES!
				int xx = x/2;
				// If character found
				if (line.at(x) == 'c'){
					charX = xx;
					charY = y;
					level->insert(xx, y, 0);
				} else if (line.at(x) == 'L'){
					monsters->push_back(new Monster(xx * TILE_SIZE + TILE_SIZE/2, y * TILE_SIZE + TILE_SIZE, "left"));
					level->insert(xx, y, 0);
				} else if (line.at(x) == 'R'){
					monsters->push_back(new Monster(xx * TILE_SIZE + TILE_SIZE/2, y * TILE_SIZE + TILE_SIZE, "right"));
					level->insert(xx, y, 0);
				} else if (line.at(x) != 9){ // Ignore tabs
					level->insert(xx, y, intFromChar(line.at(x)));
				}
			}
			y++;
		}
		myfile.close();	
	} // ELSE Error 
}

Sprite *MapController::getBackground(){
	return background;
}

Level *MapController::getLevel(){
	return level;
}

int MapController::getCharX(){
	return charX;
}

int MapController::getCharY(){
	return charY;
}

vector<GameObject*> * MapController::getMonsters(){
	return monsters;
}

SDL_Surface *MapController::loadTileImage(int tile){
	string img = "../Assets/Images/";

	stringstream out;
	out << tile;
	string str = out.str();

	img.append(str).append(".png");
	
	return loadImage(img);
}

SDL_Surface *MapController::getTileImage(int tile){
	return tileset[tile];
}

MapController::~MapController(void)
{
}
