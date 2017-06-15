#include "PhysicsWorld.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <SFML\Graphics\CircleShape.hpp>
#include "GameWindow.h"

PhysicsBody::PhysicsBody(PhysicsWorld * world, b2Body* body, Type type)
{
	this->world = world;
	this->body = body;
	this->type = type;
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

float PhysicsBody::getRadius()
{
	return ((b2CircleShape*)body->GetFixtureList()->GetShape())->m_radius*world->worldToB2World;
}

PhysicsBody::Type PhysicsBody::getType()
{
	return type;
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

	PhysicsBody* body = new PhysicsBody(this, circleBody, PhysicsBody::Type::Circle);
	circleBody->SetUserData(body);
	bodies.push_back(std::unique_ptr<PhysicsBody>(body));

	return body;
}

PhysicsBody * PhysicsWorld::createStaticCircle(Vec2f pos, float radius)
{
	b2BodyDef bodyDef;
	bodyDef.position = translate(pos);
	bodyDef.type = b2_staticBody;

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

	PhysicsBody* body = new PhysicsBody(this, circleBody, PhysicsBody::Type::Circle);
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

void PhysicsWorld::debugDraw()
{
	sf::CircleShape circle;
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(sf::Color::Red);
	circle.setOutlineThickness(2.f);

	for (auto& body : bodies)
	{
		if (body->getType() == PhysicsBody::Type::Circle)
		{
			circle.setPosition(body->getPos().toSFMLVec());
			circle.setRadius(body->getRadius() - 2.f);
			circle.setOrigin(circle.getRadius(), circle.getRadius());

			GameWindow::getInternalHandle().draw(circle);
		}
	}
}

