#include "Level.h"
#include "main.h"

void Level::clear(){
	for(int y = 0; y < LEVEL_HEIGHT; y++){
		for(int x = 0; x < LEVEL_WIDTH; x++){
			level[y][x] = 0;
		}
	}
}

Level::Level(void)
{
	clear();
}

int Level::at(int x, int y){
	return level[y][x];
}

void Level::insert(int x, int y, int value){
	level[y][x] = value;
}


Level::~Level(void)
{
}
