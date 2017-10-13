#include "HealthBar.h"
#include "GameWindow.h"


HealthBar::HealthBar()
{
	dirty = true;
	hp = 100;
	maxHp = 100;
	size = Vec2f(100.f, 20.f);
	background.setSize(size.toSFMLVec());
	background.setOrigin(size.toSFMLVec() / 2.f);
	background.setFillColor(sf::Color::Black);
	healthShape.setFillColor(sf::Color::Green);
	healthShape.setOrigin(0.f, size.y / 2.f);
	background.setOutlineColor(sf::Color::Black);
	background.setOutlineThickness(2.f);
}


HealthBar::~HealthBar()
{
}

void HealthBar::setPos(Vec2f pos)
{
	this->pos = pos;

	Vec2f finalPos = getFinalPos();
	background.setPosition(finalPos.toSFMLVec());
	healthShape.setPosition(Vec2f::add(finalPos, Vec2f(-size.x / 2.f, 0.f)).toSFMLVec());
}

void HealthBar::draw()
{
	if (dirty)
	{
		dirty = false;
		updateShape();
	}

	GameWindow::getInternalHandle().draw(background);
	GameWindow::getInternalHandle().draw(healthShape);
}

void HealthBar::setHealth(int hp)
{
	this->hp = hp;
	dirty = true;
}

void HealthBar::setMaxHealth(int hp)
{
	maxHp = hp;
	dirty = true;
}

void HealthBar::updateShape()
{
	float val = (float)hp/maxHp;
	if (val < 0.f)
		val = 0.f;
	if (val > 1.f)
		val = 1.f;

	healthShape.setSize(sf::Vector2f(size.x*val, size.y));
}

Vec2f HealthBar::getFinalPos()
{
	return  Vec2f::add(pos, Vec2f(0.f, 70.f));;
}
