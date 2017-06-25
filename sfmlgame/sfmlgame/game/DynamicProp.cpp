#include "DynamicProp.h"
#include "GameWorld.h"


DynamicProp::DynamicProp(int nid) :PhysicsEntity(nid)
{
	sprite.setSize(Vec2f(80, 80));
	sprite.setTexture("prop_barrel");
	speed = Vec2f(0, 0);
	realType = Type::DynamicProp;
}

DynamicProp::~DynamicProp()
{
}

void DynamicProp::init()
{
	body = world->getPhysicsWorld().createCircle(getPos(), 40.f);
	body->setEntity(this);
}

void DynamicProp::update(float dt)
{
	//speed = Vec2f::sub(speed, Vec2f::mul(speed, Vec2f(dt * 5, dt * 5)));
	//speed.x += rand() % 11 - 5;
	
	//setPos(Vec2f::add(getPos(), Vec2f::mul(speed, Vec2f(dt, dt))));

}

void DynamicProp::localUpdate(float dt)
{
	updateBody();
	sprite.setPos(getPos());
}

void DynamicProp::draw()
{
	sprite.draw();
}

void DynamicProp::writeInformation(sf::Packet & packet)
{
	packet << getBodyPos();
	packet << getBodyAng();
}

void DynamicProp::readInformation(sf::Packet & packet)
{
	Vec2f newpos;
	float newang;
	packet >> newpos >> newang;

	setBodyPos(newpos);
	setBodyAng(newang);
}

void DynamicProp::writeSpawn(sf::Packet & packet)
{
	packet << getBodyPos();
	packet << getBodyAng();
}

void DynamicProp::readSpawn(sf::Packet & packet)
{
	Vec2f newpos;
	float newang;
	packet >> newpos >> newang;

	setBodyPos(newpos);
	setBodyAng(newang);
}