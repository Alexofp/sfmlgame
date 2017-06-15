#include "StaticObject.h"
#include "GameWindow.h"
#include "GameWorld.h"


StaticObject::StaticObject()
{
	dirty = true;
	pos = Vec2f();
	size = Vec2f(100.f, 100.f);
	angle = 0.f;
}


StaticObject::~StaticObject()
{

}

void StaticObject::init(GameWorld * world)
{
	this->world = world;

	if (dirty)
	{
		dirty = false;
		recalculateTransform();
	}

	for (auto& part : collisionParts)
	{
		Vec2f newpos = trans.transformPoint(part.pos.toSFMLVec());

		if (part.type == CollisionType::CIRCLE)
		{
			part.body = ((world->getPhysicsWorld().createStaticCircle(newpos, part.circle.radius*size.x)));
		}
	}
}

void StaticObject::setName(std::string name)
{
	this->name = name;
}

std::string StaticObject::getName()
{
	return name;
}

void StaticObject::addPart(StaticObject::Part part)
{
	part.sprite.setPos(part.pos);
	part.sprite.setSize(part.size);
	part.sprite.setAng(part.ang);
	part.sprite.setTexture(part.texture);

	parts.push_back(part);
}

void StaticObject::addCollisionPart(StaticObject::CollisionPart part)
{
	collisionParts.push_back(part);
}

void StaticObject::setPos(Vec2f pos)
{
	this->pos = pos;
	dirty = true;
}

void StaticObject::setAng(float ang)
{
	this->angle = ang;
	dirty = true;
}

void StaticObject::setSize(Vec2f size)
{
	this->size = size;
	dirty = true;
}

void StaticObject::draw()
{
	if (dirty)
	{
		dirty = false;
		recalculateTransform();
	}

	sf::RenderStates states;
	states.transform = trans;
	for (auto& part : parts)
	{
		part.sprite.draw(states);
	}
}

void StaticObject::recalculateTransform()
{
	trans = sf::Transform();
	trans.translate(pos.toSFMLVec());
	trans.rotate(angle);
	trans.scale(size.toSFMLVec());
}
