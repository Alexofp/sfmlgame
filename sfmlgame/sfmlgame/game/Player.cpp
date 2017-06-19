#include "Player.h"
#include "Input.h"
#include "Log.h"
#include "GameWorld.h"
#include "GameWindow.h"
#include "Settings.h"
#include "AnimationManager.h"

Player::Player(int clientId, int nid):Person(nid)
{
	this->clientId = clientId;
	this->isRemote = false;
	realType = Type::Player;
	Log::debug("new player entity");

	Skin skin;
	skin.loadFromFile("resources/skin.json");

	skeleton.setSkin(skin);
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
	updateBody();
}

void Player::localUpdate(float dt)
{
	moveControl = Vec2f();
	if (!isRemote)
	{
		if (Input::getKey(Input::A))
			moveControl.x = -1;
		if (Input::getKey(Input::D))
			moveControl.x = 1;
		if (Input::getKey(Input::W))
			moveControl.y = -1;
		if (Input::getKey(Input::S))
			moveControl.y = 1;

		if (Input::getMouseDown(Input::MouseLeft))
			playAnimation("person_hit");

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

int Player::getClientId()
{
	return clientId;
}

MultiplayerMessage Player::writeInformation()
{
	MultiplayerMessage message(MessageType::PlayerUpdate);
	message.setMessage(new PlayerUpdateMessage(getBodyPos().x, getBodyPos().y, skeleton.getAng(), getBodySpeed().x, getBodySpeed().y, lookPosition.x, lookPosition.y));

	return message;
}

void Player::readInformation(MultiplayerMessage& message)
{
	if (message.getType() == MessageType::PlayerUpdate)
	{
		PlayerUpdateMessage* m = message.getMessage<PlayerUpdateMessage>();

		setBodyPos(Vec2f(m->x, m->y));
		//setBodyAng(m->ang);
		skeleton.setAng(m->ang);
		speed = Vec2f(m->speedx, m->speedy);
		setBodySpeed(Vec2f(m->speedx, m->speedy));
		lookPosition = Vec2f(m->lookx, m->looky);
	}
}

MultiplayerMessage Player::spawnMessage()
{
	MultiplayerMessage message(MessageType::SpawnPlayerEntity);
	message.setMessage(new SpawnPlayerEntityMessage(getNid(),clientId ,getPos().x, getPos().y));

	return message;
}
