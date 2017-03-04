#include "PhysicsWorld.h"
#define _USE_MATH_DEFINES
#include <math.h>

PhysicsBody::PhysicsBody(PhysicsWorld * world, b2Body* body)
{
	this->world = world;
	this->body = body;
}

PhysicsBody::~PhysicsBody()
{
	this->world->destroy(this);
}

Vec2f PhysicsBody::getPos()
{
	b2Vec2 pos = this->body->GetPosition();

	return world->translate(pos);
}

void PhysicsBody::setPos(Vec2f pos)
{
	b2Vec2 newpos = world->translate(pos);

	body->SetTransform(newpos, body->GetAngle());
}

float PhysicsBody::getAng()
{
	return body->GetAngle()*180.f/M_PI;
}

void PhysicsBody::setAng(float ang)
{
	body->SetTransform(body->GetPosition(), ang/180.f*M_PI);
}

Vec2f PhysicsBody::getSpeed()
{
	return world->translate(body->GetLinearVelocity());
}

void PhysicsBody::setSpeed(Vec2f speed)
{
	b2Vec2 velocity = world->translate(speed);
	body->SetLinearVelocity(velocity);
}


PhysicsWorld::PhysicsWorld():
	world(b2Vec2(0.f,0.f))
{
	worldToB2World = 10.f;
	timestep = 1.f / 60.f;
	time = 0.f;
}


PhysicsWorld::~PhysicsWorld()
{
}

PhysicsBody * PhysicsWorld::createCircle(Vec2f pos, float radius)
{
	b2BodyDef bodyDef;
	bodyDef.position = translate(pos);
	bodyDef.type = b2_dynamicBody;

	b2Body* circleBody = world.CreateBody(&bodyDef);
	circleBody->SetLinearDamping(10.f);

	b2CircleShape circle;
	circle.m_radius = radius / worldToB2World;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	circleBody->CreateFixture(&fixtureDef);

	PhysicsBody* body = new PhysicsBody(this, circleBody);
	circleBody->SetUserData(body);
	bodies.push_back(std::unique_ptr<PhysicsBody>(body));

	return body;
}

b2Vec2 PhysicsWorld::translate(Vec2f p)
{
	return b2Vec2(p.x/worldToB2World, p.y/worldToB2World);
}

Vec2f PhysicsWorld::translate(b2Vec2 p)
{
	return Vec2f(p.x*worldToB2World, p.y*worldToB2World);
}

void PhysicsWorld::destroy(PhysicsBody * body)
{
	toDestroy.push_back(body);
}

void PhysicsWorld::update(float dt)
{
	time += dt;

	while (time >= timestep)
	{
		time -= timestep;
		world.Step(timestep, 6, 2);
	}
}

