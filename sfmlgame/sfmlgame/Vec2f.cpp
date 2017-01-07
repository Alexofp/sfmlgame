#include "Vec2f.h"
#include <cmath>
#include <assert.h>
#define PI 3.14159265

Vec2f::Vec2f()
{
	x = 0;
	y = 0;
}

Vec2f::Vec2f(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vec2f::Vec2f(sf::Vector2f vec)
{
	x = vec.x;
	y = vec.y;
}

sf::Vector2f Vec2f::toSFMLVec()
{
	return sf::Vector2f(x, y);
}

float Vec2f::len()
{
	return sqrt(x*x+y*y);
}

float Vec2f::dot(Vec2f v1, Vec2f v2)
{
	return v1.x*v2.x + v1.y * v2.y;
}

void Vec2f::normalize()
{
	float l = len();

	assert(l != 0 && "Trying to normalize a zero vector");

	x /= l;
	y /= l;
}

Vec2f Vec2f::normalized()
{
	float l = len();

	assert(l != 0 && "Trying to normalize a zero vector");

	return Vec2f(x / l, y / l);
}

Vec2f Vec2f::fromAngle(float angle, float len)
{
	float rad = angle / 180.f * PI;
	return Vec2f(cos(rad)*len, sin(rad)*len);
}

float Vec2f::getAngle() const
{
	return atan2(y, x) * 180.f / PI;
}

Vec2f Vec2f::add(Vec2f v1, Vec2f v2)
{
	return Vec2f(v1.x + v2.x, v1.y + v2.y);
}

Vec2f Vec2f::sub(Vec2f v1, Vec2f v2)
{
	return Vec2f(v1.x - v2.x, v1.y - v2.y);
}

Vec2f Vec2f::mul(Vec2f v1, Vec2f v2)
{
	return Vec2f(v1.x*v2.x, v1.y*v2.y);
}

Vec2f Vec2f::div(Vec2f v1, Vec2f v2)
{
	return Vec2f(v1.x / v2.x, v1.y / v2.y);
}
