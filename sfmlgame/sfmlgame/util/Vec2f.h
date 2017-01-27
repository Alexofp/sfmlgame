#pragma once
#include <SFML/System/Vector2.hpp>
#include <string>

class Vec2f
{
public:
	Vec2f();
	Vec2f(float x, float y);
	Vec2f(sf::Vector2f vec);

	sf::Vector2f toSFMLVec();
	float len();
	void normalize();
	Vec2f normalized();

	float getX();
	float getY();

	static Vec2f fromAngle(float angle, float len);
	float getAngle() const;

	std::string toString();

	static float dot(Vec2f v1, Vec2f v2);
	static float cross(Vec2f v1, Vec2f v2);
	static float distance(Vec2f v1, Vec2f v2);
	static float distanceSquared(Vec2f v1, Vec2f v2);

	static Vec2f add(Vec2f v1, Vec2f v2);
	static Vec2f sub(Vec2f v1, Vec2f v2);
	static Vec2f mul(Vec2f v1, Vec2f v2);
	static Vec2f div(Vec2f v1, Vec2f v2);

	static Vec2f mul(Vec2f v1, float m);

	float x, y;
};

