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
		SimpleSprite shadow;
		Vec2f pos;
		Vec2f size;
		float ang;
		std::string texture;
	};

	enum class CollisionType
	{
		CIRCLE,
		BOX
	};
	struct CircleCollision
	{
		float radius;
	};
	struct BoxCollision
	{
		Vec2f size;
		float angle;
	};

	struct CollisionPart
	{
		PhysicsBody* body;
		Vec2f pos;
		CollisionType type;
		CircleCollision circle;
		BoxCollision box;
	};

	StaticObject();
	~StaticObject();
	void init(GameWorld* world);

	void setName(std::string name);
	std::string getName();

	void addPart(Part part);
	void addCollisionPart(CollisionPart part);
	void setShadowPos(Vec2f pos);
	void setPos(Vec2f pos);
	Vec2f getPos();
	void setAng(float ang);
	float getAng();
	void setSize(Vec2f size);
	Vec2f getSize();

	void draw();
	void drawShadow();

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
	sf::Transform shadowTrans;
	Vec2f shadowPos;
};

