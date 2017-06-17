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

void PhysicsBody::setSize(Vec2f size)
{
	this->size = size;
}

Vec2f PhysicsBody::getSize()
{
	if (type == Type::Circle)
	{
		float rad = getRadius();
		return Vec2f(rad*2.f, rad*2.f);
	}
	else if (type == Type::Box)
	{
		return size;
	}
}

std::vector<std::vector<Vec2f>> PhysicsBody::getPoints()
{
	std::vector<std::vector<Vec2f>> result;
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext())
	{
		b2PolygonShape* shape = (b2PolygonShape*)f->GetShape();
		int count = shape->GetVertexCount();

		std::vector<Vec2f> points;
		points.reserve(count);
		for (int i = 0; i < count; i++)
		{
			b2Vec2 vec = body->GetWorldPoint(shape->GetVertex(i));
			points.push_back(Vec2f(vec.x*world->worldToB2World, vec.y * world->worldToB2World));
		}
		result.push_back(points);
	}

	return result;
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

PhysicsBody * PhysicsWorld::createStaticBox(Vec2f pos, Vec2f size)
{
	b2BodyDef bodyDef;
	bodyDef.position = translate(pos);
	bodyDef.type = b2_staticBody;

	b2Body* circleBody = world.CreateBody(&bodyDef);
	circleBody->SetLinearDamping(10.f);

	b2PolygonShape shape;
	shape.SetAsBox(size.x / worldToB2World / 2.f, size.y / worldToB2World / 2.f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	circleBody->CreateFixture(&fixtureDef);

	PhysicsBody* body = new PhysicsBody(this, circleBody, PhysicsBody::Type::Box);
	circleBody->SetUserData(body);
	bodies.push_back(std::unique_ptr<PhysicsBody>(body));

	return body;
}

PhysicsBody * PhysicsWorld::createBox(Vec2f pos, Vec2f size)
{
	b2BodyDef bodyDef;
	bodyDef.position = translate(pos);
	bodyDef.type = b2_dynamicBody;

	b2Body* circleBody = world.CreateBody(&bodyDef);
	circleBody->SetLinearDamping(10.f);

	b2PolygonShape shape;
	shape.SetAsBox(size.x / worldToB2World/2.f, size.y / worldToB2World/2.f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	circleBody->CreateFixture(&fixtureDef);

	PhysicsBody* body = new PhysicsBody(this, circleBody, PhysicsBody::Type::Box);
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
	sf::ConvexShape shape;
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(2.f);

	for (auto& body : bodies)
	{
		if (body->getType() == PhysicsBody::Type::Circle)
		{
			circle.setPosition(body->getPos().toSFMLVec());
			circle.setRadius(body->getRadius() - 2.f);
			circle.setOrigin(circle.getRadius(), circle.getRadius());

			GameWindow::getInternalHandle().draw(circle);
		}
		if (body->getType() == PhysicsBody::Type::Box)
		{
			auto points = body->getPoints();
			for (auto& data : points)
			{
				shape.setPointCount(data.size());
				int i = 0;
				for (auto& point : data)
				{
					shape.setPoint(i, point.toSFMLVec());
					i++;
				}
				GameWindow::getInternalHandle().draw(shape);
			}
		}
	}
}

