#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Vec2f.h"
#include <SFML\Graphics\Transform.hpp>

struct BoneState
{
	Vec2f pos;
	float angle;
	float size;
};

class Bone
{
public:
	Bone(std::string name, float x, float y, float a, float l);
	~Bone();

	Bone* getRoot();
	Bone* getParent();
	void update();
	BoneState getState();
	void setState(BoneState state);
	BoneState getAnimationState();
	void setAnimationState(BoneState state);
	Bone* addChild(std::string name, float x, float y, float a, float l);
	void addChild(Bone* bone);
	void debugDraw();
	std::string getName();

	BoneState getFinalState();
	std::pair<Vec2f, Vec2f> getTransformedPos(sf::Transform transform);
	Vec2f getRelativePos(sf::Transform transform, Vec2f pos);
	Vec2f getRelativePos(Vec2f pos);
	Vec2f getPosRelativeToParent(Vec2f pos);

private:
	Bone* root;
	std::vector<std::unique_ptr<Bone> > childs;
	bool dirty;

	std::string name;
	float x,y;
	float angle, size;

	float addx, addy;
	float addang, addsize;

	float finalx, finaly, finalang, finalsize;
};

