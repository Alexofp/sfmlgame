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
	void drawShadow();
	void saveToFile(std::string path);
	void loadFromFile(std::string path);
	void remoteObjectAt(Vec2f pos, float radius);

	void clear();
private:
	GameWorld* world;
	std::vector<StaticObject> objects;
};

