#include "DynamicProp.h"
#include "GameWorld.h"


DynamicProp::DynamicProp(int nid) :PhysicsEntity(nid)
{
	sprite.setSize(Vec2f(40, 40));
	speed = Vec2f(0, 0);
	realType = Type::DynamicProp;
}

DynamicProp::~DynamicProp()
{
}

void DynamicProp::init()
{
	body = world->getPhysicsWorld().createCircle(getPos(), 20.f);
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

MultiplayerMessage DynamicProp::writeInformation()
{
	MultiplayerMessage message(MessageType::DynamicPropUpdate);
	message.setMessage(new DynamicPropUpdateMessage(getBodyPos().x, getBodyPos().y, getBodyAng()));

	return message;
}

void DynamicProp::readInformation(MultiplayerMessage& message)
{
	if (message.getType() == MessageType::DynamicPropUpdate)
	{
		DynamicPropUpdateMessage* m = message.getMessage<DynamicPropUpdateMessage>();

		setBodyPos(Vec2f(m->x, m->y));
		setBodyAng(m->ang);
	}
}

MultiplayerMessage DynamicProp::spawnMessage()
{
	MultiplayerMessage message(MessageType::SpawnDynamicPropEntity);
	message.setMessage(new SpawnDynamicPropEntityMessage(getNid(), getPos().x, getPos().y));

	return message;
}
