#pragma once
#include <vector>
#include "StaticObject.h"

class GameWorld;

class ObjectHandler
{
public:
	ObjectHandler();
	ObjectHandler(GameWorld* world);
	~ObjectHandler();

	void addObject(StaticObject object);
	void draw();
private:
	GameWorld* world;
	std::vector<StaticObject> objects;
};

