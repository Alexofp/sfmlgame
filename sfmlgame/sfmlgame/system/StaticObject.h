#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Vec2f.h"
#include "SimpleSprite.h"
#include "PhysicsWorld.h"
#include <memory>

class GameWorld;

class StaticObject
{
public:
	struct Part
	{
		SimpleSprite sprite;
		Vec2f pos;
		Vec2f size;
		float ang;
		std::string texture;
	};

	enum class CollisionType
	{
		CIRCLE
	};
	struct CircleCollision
	{
		float radius;
	};

	struct CollisionPart
	{
		PhysicsBody* body;
		Vec2f pos;
		CollisionType type;
		CircleCollision circle;
	};

	StaticObject();
	~StaticObject();
	void init(GameWorld* world);

	void setName(std::string name);
	std::string getName();

	void addPart(Part part);
	void addCollisionPart(CollisionPart part);
	void setPos(Vec2f pos);
	void setAng(float ang);
	void setSize(Vec2f size);

	void draw();

private:
	void recalculateTransform();
	std::string name;
	std::vector<Part> parts;
	std::vector<CollisionPart> collisionParts;

	GameWorld* world;
	bool dirty;
	Vec2f pos;
	float angle;
	Vec2f size;
	sf::Transform trans;
};

