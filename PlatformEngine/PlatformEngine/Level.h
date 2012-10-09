#pragma once
class Level
{
private:
	int level[320][320];

public:
	Level(void);
	void clear();
	int at(int x, int y);
	void insert(int x, int y, int value);
	~Level(void);
};

