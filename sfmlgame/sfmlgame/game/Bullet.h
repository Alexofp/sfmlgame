#pragma once
#include "PhysicsWorld.h"
#include <SFML/Graphics/CircleShape.hpp>
#include "PhysicsCallbacks.h"

class Bullet: public PhysicsCallbacks
{
public:
	Bullet(PhysicsBody* bullet);
	~Bullet();

	void setPos(Vec2f pos);
	void setSpeed(Vec2f speed);

	void update(float dt);
	void draw();

	void startContact(PhysicsBody* body);
	void endContact(PhysicsBody* body);

	void destroy();
	bool isDestroyed();
	float aliveTimer;
private:
	PhysicsBody* bullet;
	sf::CircleShape shape;
	bool destroyed;
};

