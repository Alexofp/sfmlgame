#include "SimpleSprite.h"
#include "GameWindow.h"
#include "TextureManager.h"

SimpleSprite::SimpleSprite()
{
}


SimpleSprite::~SimpleSprite()
{
}

void SimpleSprite::setPos(Vec2f pos)
{
	box.setPosition(pos.toSFMLVec());
}

void SimpleSprite::setSize(Vec2f size)
{
	box.setSize(size.toSFMLVec());
	box.setOrigin(size.toSFMLVec() / 2.f);
}

void SimpleSprite::setAng(float ang)
{
	box.setRotation(ang);
}

void SimpleSprite::setTexture(std::string texture)
{
	box.setTexture(TextureManager::get(texture));
}

Vec2f SimpleSprite::getPos()
{
	return Vec2f(box.getPosition());
}

Vec2f SimpleSprite::getSize()
{
	return Vec2f(box.getSize());
}

float SimpleSprite::getAng()
{
	return box.getRotation();
}

void SimpleSprite::draw()
{
	GameWindow::getInternalHandle().draw(box);
}
