#pragma once
#include <unordered_map>
#include <string>
#include "Bone.h"
#include <memory>
#include "Vec2f.h"
#include <SFML\Graphics\Transform.hpp>

class Skeleton
{
public:
	Skeleton();
	~Skeleton();

	void addBone(std::string parent, Bone* bone);
	void addBone(Bone* bone);

	void setPos(Vec2f pos);
	void setScale(float scale);
	void setAng(float ang);

	Vec2f getPos();
	float getScale();
	float getAng();

	sf::Transform getTransform();
	Vec2f transformPoint(Vec2f pos);

	void draw();
	std::unordered_map<std::string, Bone*>& getBones();
private:
	std::unordered_map<std::string, Bone*> bones;
	Bone root;

	Vec2f pos;
	float scale;
	float angle;
};

