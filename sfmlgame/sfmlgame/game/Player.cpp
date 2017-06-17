#include "Player.h"
#include "Input.h"
#include "Log.h"
#include "GameWorld.h"
#include "GameWindow.h"
#include "Settings.h"

Player::Player(int clientId, int nid):AliveEntity(nid)
{
	acceleration = 1000.f;
	maxSpeed = 1000.f;
	this->clientId = clientId;
	speed = Vec2f(0, 0);
	this->isRemote = false;
	realType = Type::Player;
	Log::debug("new player entity");

	walkAnim.loadFromFile("resources/player/walkanim.json");
	hitAnim.loadFromFile("resources/player/hitanim.json");
	hitAnim.setLooped(false);
	skeleton.playerSkeleton();
	skeleton.playAnimation(&walkAnim);

	Skin skin;
	skin.loadFromFile("resources/skin.json");

	skeleton.setSkin(skin);
}


Player::~Player()
{
}

void Player::init()
{
	body = world->getPhysicsWorld().createCircle(getPos(), 40.f);
}

void Player::update(float dt)
{
	updateBody();
}

void Player::localUpdate(float dt)
{
	float acc = 1000;
	Vec2f newspeed;
	if (!isRemote)
	{
		if (Input::getKey(Input::A))
			newspeed.x = -acc;
		if (Input::getKey(Input::D))
			newspeed.x = acc;
		if (Input::getKey(Input::W))
			newspeed.y = -acc;
		if (Input::getKey(Input::S))
			newspeed.y = acc;

		if (Input::getMouseDown(Input::MouseLeft))
			skeleton.playAnimation(&hitAnim);
	}
	targetSpeed = newspeed;

	updateMove(dt);

	if (speed.len() > 0.1)
	{
		skeleton.setAng(speed.getAngle());
	}

	skeleton.setPos(getPos());

	if (!isRemote)
	{
		GameWindow::setCameraCenter(getPos());
	}
}

void Player::draw()
{
	skeleton.draw();
	if (Settings::getBool("render", "debug", false))
		skeleton.debugDraw();
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
	message.setMessage(new PlayerUpdateMessage(getBodyPos().x, getBodyPos().y, skeleton.getAng(), getBodySpeed().x, getBodySpeed().y));

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
		setBodySpeed(Vec2f(m->speedx, m->speedy));
	}
}

MultiplayerMessage Player::spawnMessage()
{
	MultiplayerMessage message(MessageType::SpawnPlayerEntity);
	message.setMessage(new SpawnPlayerEntityMessage(getNid(),clientId ,getPos().x, getPos().y));

	return message;
}
