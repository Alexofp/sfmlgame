#include "Player.h"
#include "Input.h"
#include "Log.h"
#include "GameWorld.h"
#include "GameWindow.h"
#include "Settings.h"
#include "AnimationManager.h"

Player::Player(int nid):Person(nid)
{
	this->isRemote = false;
	realType = Type::Player;
	Log::debug("new player entity");

	inventory.setSize(Vec2i(10, 10));
	inventory.addItem(Inventory::Item(Vec2i(0, 0), "test"));
	inventory.addItem(Inventory::Item(Vec2i(0, 2), "ak74"));
}


Player::~Player()
{
}

void Player::init()
{
	Person::init();
}

void Player::update(float dt)
{
	updateSkeleton(dt);
}

void Player::localUpdate(float dt)
{
	if (!isRemote)
	{
		moveControl = Vec2f();
		if (Input::getKey(Input::A))
			moveControl.x = -1;
		if (Input::getKey(Input::D))
			moveControl.x = 1;
		if (Input::getKey(Input::W))
			moveControl.y = -1;
		if (Input::getKey(Input::S))
			moveControl.y = 1;

		if (Input::getMouseDown(Input::MouseLeft) || (weapon.info.autoFire && Input::getMouse(Input::MouseLeft)))
			attack();

		lookPosition = Input::getWorldMousePos();
	}

	updateSkeleton(dt);

	if (!isRemote)
	{
		GameWindow::setCameraCenter(getPos());
	}
}

void Player::draw()
{
	Person::draw();
}

void Player::setRemote(bool isRemote)
{
	this->isRemote = isRemote;
}

void Player::setClientId(int clientId)
{
	this->clientId = clientId;
}

int Player::getClientId()
{
	return clientId;
}

void Player::writeInformation(sf::Packet & packet)
{
	packet << getBodyPos();
	packet << getBodySpeed();
	packet << lookPosition;
	packet << moveControl;
}

void Player::readInformation(sf::Packet & packet)
{
	Vec2f newpos;
	Vec2f newspeed;
	Vec2f look;
	Vec2f control;

	packet >> newpos >> newspeed >> look >> control;

	if (isRemote)
	{
		setBodyPos(newpos);
		speed = newspeed;
		setBodySpeed(newspeed);
		lookPosition = look;
		moveControl = control;
	}
}

void Player::writeSpawn(sf::Packet & packet)
{
	packet << (sf::Int16)getClientId();
	packet << getBodyPos();
	packet << getBodySpeed();
	packet << lookPosition;
}

void Player::readSpawn(sf::Packet & packet)
{
	sf::Int16 clientId;
	Vec2f newpos;
	Vec2f newspeed;
	Vec2f look;

	packet >> clientId >> newpos >> newspeed >> look;

	setClientId(clientId);
	setBodyPos(newpos);
	speed = newspeed;
	setBodySpeed(newspeed);
	lookPosition = look;
}