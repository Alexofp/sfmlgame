#include "Vec2i.h"

Vec2i::Vec2i()
{
	x = 0;
	y = 0;
}

Vec2i::Vec2i(int x, int y)
{
	this->x = x;
	this->y = y;
}

Vec2i::Vec2i(sf::Vector2i vec)
{
	x = vec.x;
	y = vec.y;
}

sf::Vector2i Vec2i::toSFMLVec()
{
	return sf::Vector2i(x,y);
}

