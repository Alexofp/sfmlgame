#pragma once
#include "PhysicsWorld.h"

class PhysicsCallbacks
{
public:
	PhysicsCallbacks();
	~PhysicsCallbacks();

	virtual void startContact(PhysicsBody* body) = 0;
	virtual void endContact(PhysicsBody* body) = 0;
};

