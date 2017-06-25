#include "Bullet.h"
#include "GameWindow.h"
#include "Log.h"
#include "Server.h"

Bullet::Bullet(PhysicsBody* bullet)
{
	this->bullet = bullet;
	bullet->setTag(this);

	shape.setFillColor(sf::Color::White);
	shape.setRadius(bullet->getRadius());
	shape.setOrigin(bullet->getRadius(), bullet->getRadius());

	destroyed = false;
}


Bullet::~Bullet()
{
}

void Bullet::setPos(Vec2f pos)
{
	bullet->setPos(pos);
}

void Bullet::setSpeed(Vec2f speed)
{
	bullet->setSpeed(speed);
}



void Bullet::update(float dt)
{
	shape.setPosition(bullet->getPos().toSFMLVec());
}

void Bullet::draw()
{
	GameWindow::getInternalHandle().draw(shape);
}

void Bullet::startContact(PhysicsBody* body)
{
	Log::debug("boom");
	//bullet->destroy();
	destroy();

	PhysicsEntity* ent = body->getEntity();
	if (ent)
	{
		if (Server::isInServer())
		{
			NetEvent event(ent->getNid(), ent->getNid(), "hurt");
			ent->sendEvent(event);
		}

	}
}

void Bullet::endContact(PhysicsBody* body)
{
}

void Bullet::destroy()
{
	destroyed = true;
	bullet->destroy();
}

bool Bullet::isDestroyed()
{
	return destroyed;
}
