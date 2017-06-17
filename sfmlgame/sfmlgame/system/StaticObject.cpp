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
			part.body = ((world->getPhysicsWorld().createStaticCircle(newpos, part.circle.radius*size.x	)));
		}
		if (part.type == CollisionType::BOX)
		{
			part.body = ((world->getPhysicsWorld().createStaticBox(newpos, Vec2f(part.box.size.x*size.x, part.box.size.y*size.x))));
			part.body->setAng(part.box.angle+getAng());
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

	part.shadow.setPos(part.pos);
	part.shadow.setSize(part.size);
	part.shadow.setAng(part.ang);
	part.shadow.setTexture(part.texture);
	part.shadow.setColor(sf::Color(0, 0, 0, 100));

	parts.push_back(part);
}

void StaticObject::addCollisionPart(StaticObject::CollisionPart part)
{
	collisionParts.push_back(part);
}

void StaticObject::setShadowPos(Vec2f pos)
{
	this->shadowPos = pos;
	dirty = true;
}

void StaticObject::setPos(Vec2f pos)
{
	this->pos = pos;
	dirty = true;
}

Vec2f StaticObject::getPos()
{
	return pos;
}

void StaticObject::setAng(float ang)
{
	this->angle = ang;
	dirty = true;
}

float StaticObject::getAng()
{
	return angle;
}

void StaticObject::setSize(Vec2f size)
{
	this->size = size;
	dirty = true;
}

Vec2f StaticObject::getSize()
{
	return size;
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

void StaticObject::drawShadow()
{
	if (dirty)
	{
		dirty = false;
		recalculateTransform();
	}

	sf::RenderStates states;
	states.transform = shadowTrans;
	for (auto& part : parts)
	{
		part.shadow.draw(states);
	}
}

void StaticObject::recalculateTransform()
{
	trans = sf::Transform();
	trans.translate(pos.toSFMLVec());
	trans.rotate(angle);
	trans.scale(size.toSFMLVec());

	shadowTrans = sf::Transform();
	shadowTrans.translate(shadowPos.toSFMLVec());
	shadowTrans.translate(pos.toSFMLVec());
	shadowTrans.rotate(angle);
	shadowTrans.scale(size.toSFMLVec());
}
