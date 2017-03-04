#include "Player.h"
#include "Input.h"
#include "Log.h"
#include "GameWorld.h"

Player::Player(int clientId, int nid):PhysicsEntity(nid)
{
	this->clientId = clientId;
	sprite.setSize(Vec2f(38,26));
	sprite.setTexture("player");
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

	if (newspeed.len() > acc)
	{
		float l = newspeed.len();
		newspeed = Vec2f::mul(newspeed.normalized(), Vec2f(acc, acc));
	}

	speed = Vec2f::sub(speed, Vec2f::mul(speed, Vec2f(dt * 5, dt * 5)));
	if (speed.len()<100)
		speed = Vec2f::add(speed, Vec2f::mul(newspeed, Vec2f(dt, dt)));

	body->setSpeed(speed);
	//setPos(Vec2f::add(getPos(), Vec2f::mul(speed, Vec2f(dt, dt))));


	if (speed.len() > 0.1)
	{
		//setAng(speed.getAngle());
		sprite.setAng(speed.getAngle() + 90);

		skeleton.setAng(speed.getAngle());
	}

	skeleton.update(dt);
	updateBody();

	sprite.setPos(getPos());
	//skeleton.setPos(getPos());
	skeleton.setPos(getPos());
}

void Player::draw()
{
	skeleton.draw();
	//sprite.draw();
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
