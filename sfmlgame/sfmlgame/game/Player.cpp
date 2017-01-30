#include "Player.h"
#include "Input.h"
#include "Log.h"

Player::Player(int nid):Entity(nid)
{
	sprite.setSize(Vec2f(38,26));
	sprite.setTexture("player");
	speed = Vec2f(0, 0);
	this->isRemote = false;
	realType = Type::Player;
	type = SyncType::Player;
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

void Player::update(float dt)
{

}

void Player::localUpdate(float dt)
{
	float acc = 300;
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
	setPos(Vec2f::add(getPos(), Vec2f::mul(speed, Vec2f(dt, dt))));


	if (speed.len() > 0.1)
	{
		//setAng(speed.getAngle());
		sprite.setAng(speed.getAngle() + 90);

		skeleton.setAng(speed.getAngle());
	}

	skeleton.update(dt);
	sprite.setPos(getPos());
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

void Player::writeInformation(sf::Packet & packet)
{
	packet << getPos().x << getPos().y << skeleton.getAng();
}

void Player::readInformation(sf::Packet & packet)
{
	float x,y,ang;
	packet >> x >> y >> ang;

	setPos(Vec2f(x, y));
	sprite.setAng(ang);
	skeleton.setAng(ang);
}