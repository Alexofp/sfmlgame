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

float Vec2f::cross(Vec2f v1, Vec2f v2)
{
	return v1.x*v2.y - v1.y*v2.x;
}

float Vec2f::distance(Vec2f v1, Vec2f v2)
{
	Vec2f delta = Vec2f::sub(v2, v1);
	return sqrt(delta.x*delta.x + delta.y*delta.y);
}

float Vec2f::distanceSquared(Vec2f v1, Vec2f v2)
{
	Vec2f delta = Vec2f::sub(v2, v1);
	return (delta.x*delta.x + delta.y*delta.y);
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

float Vec2f::getX()
{
	return x;
}

float Vec2f::getY()
{
	return y;
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

std::string Vec2f::toString()
{
	return "("+std::to_string(x)+", "+std::to_string(y)+")";
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

Vec2f Vec2f::mul(Vec2f v1, float m)
{
	return Vec2f(v1.x*m, v1.y*m);
}

sf::Packet& operator <<(sf::Packet& packet, const Vec2f& v)
{
	return packet << v.x << v.y;
}

sf::Packet& operator >> (sf::Packet& packet, Vec2f& v)
{
	return packet >> v.x >> v.y;
}