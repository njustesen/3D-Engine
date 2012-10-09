#include "GameObject.h"
#include "SDL.h"
#include "Level.h"
#include <string>
#include "SDL_image.h"
#include <vector>
using namespace std;

#pragma once
class MapController
{
private: 
	Level * level;
	Sprite *background;
	SDL_Surface* tileset[100]; 
	int intFromChar(char c);
	int charX;
	int charY;
	vector<GameObject*> * monsters;
	void loadTileset();
public:
	int getCharX();
	int getCharY();
	vector<GameObject*> * getMonsters();
	Level *getLevel();
	SDL_Surface *getTileImage(int tile);
	SDL_Surface *loadTileImage(int tile);
	Sprite *getBackground();
	void loadLevel(string levelName);
	MapController(void);
	MapController(string levelName);
	~MapController(void);
};

