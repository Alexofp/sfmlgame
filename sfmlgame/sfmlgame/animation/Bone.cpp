#include "Bone.h"
#define _USE_MATH_DEFINES
#include <math.h> 
#include "GameWindow.h"
#include <SFML/Graphics/Transform.hpp>

Bone::Bone(std::string name, float x, float y, float a, float l)
{
	this->name = name;
	this->x = x;
	this->y = y;
	this->angle = a;
	this->size = l;
	dirty = true;
}


Bone::~Bone()
{
}

Bone * Bone::getRoot()
{
	Bone* b = this;
	while (b->root)
	{
		b = b->root;
	}
	return b;
}

Bone * Bone::getParent()
{
	return root;
}

void Bone::update()
{
	float parentx = 0.f, parenty = 0.f, parentang = 0.f, parentlen = 1.f;
	if (root != 0)
	{
		parentx = root->finalx;
		parenty = root->finaly;
		parentang = root->finalang;
		parentlen = root->finalsize;
	}
	finalang = parentang + angle + addang;
	finalsize = size;//parentlen * size;

	Vec2f finalVec = Vec2f::add( Vec2f::fromAngle(parentang, x+addx),Vec2f::fromAngle(parentang+90.f, y+addy) );

	finalx = parentx + finalVec.x;//cos(parentang*M_PI / 180.f )*(x) - sin(parentang*M_PI / 180.f)*(x);
	finaly = parenty + finalVec.y;//sin(parentang*M_PI / 180.f)*(y) + cos(parentang*M_PI / 180.f)*(y);

	dirty = false;

	for (auto& bone : childs)
	{
		bone->update();
	}
}

BoneState Bone::getState()
{
	return BoneState{Vec2f(x,y),angle,size};
}

void Bone::setState(BoneState state)
{
	x = state.pos.x;
	y = state.pos.y;
	angle = state.angle;
	size = state.size;
	dirty = true;
}

BoneState Bone::getAnimationState()
{
	return BoneState{ Vec2f(addx,addy),addang,addsize };
}

void Bone::setAnimationState(BoneState state)
{
	addx = state.pos.x;
	addy = state.pos.y;
	addang = state.angle;
	addsize = state.size;
	dirty = true;
}

Bone * Bone::addChild(std::string name, float x, float y, float a, float l)
{
	Bone* bone = new Bone(name, x, y, a, l);
	bone->root = this;

	childs.push_back(std::unique_ptr<Bone>(bone));
	return bone;
}

void Bone::addChild(Bone * bone)
{
	bone->root = this;
	childs.push_back(std::unique_ptr<Bone>(bone));
}

void Bone::debugDraw()
{
	auto& window = GameWindow::getInternalHandle();
	BoneState state = getFinalState();

	sf::Vertex vertices[2] =
	{
		sf::Vertex(state.pos.toSFMLVec()),
		sf::Vertex(Vec2f::add(state.pos, Vec2f::fromAngle(state.angle, state.size)).toSFMLVec())
	};
	window.draw(vertices, 2, sf::Lines);

	for (auto& bone : childs)
	{
		bone->debugDraw();
	}
}

std::string Bone::getName()
{
	return name;
}

BoneState Bone::getFinalState()
{
	if (dirty)
	{
		Bone* root = getRoot();
		root->update();
	}

	return BoneState{ Vec2f(finalx,finaly),finalang,finalsize };
}

std::pair<Vec2f, Vec2f> Bone::getTransformedPos(sf::Transform transform)
{
	BoneState state = getFinalState();

	Vec2f pos1 = state.pos;
	Vec2f pos2 = Vec2f::add(state.pos, Vec2f::fromAngle(state.angle, state.size));

	pos1 = Vec2f( transform.transformPoint(pos1.toSFMLVec()) );
	pos2 = Vec2f( transform.transformPoint(pos2.toSFMLVec()) );

	return std::pair<Vec2f, Vec2f>(pos1, pos2);
}

Vec2f Bone::getRelativePos(sf::Transform transform, Vec2f pos)
{
	BoneState state = getFinalState();

	sf::Transform inv = transform.getInverse();

	sf::Transform inv2;
	inv2.translate(state.pos.toSFMLVec());
	inv2.rotate(state.angle);
	inv2 = inv2.getInverse();

	//magic
	return inv2.transformPoint(inv.transformPoint(pos.toSFMLVec()));
}

Vec2f Bone::getRelativePos(Vec2f pos)
{
	BoneState state = getFinalState();

	Vec2f finalVec = Vec2f::add(Vec2f::fromAngle(state.angle, pos.x), Vec2f::fromAngle(state.angle + 90.f, pos.y));
	return Vec2f::add(finalVec,state.pos);
}

Vec2f Bone::getPosRelativeToParent(Vec2f pos)
{
	float parentx = 0.f, parenty = 0.f, parentang = 0.f, parentlen = 1.f;
	if (root != 0)
	{
		parentx = root->finalx;
		parenty = root->finaly;
		parentang = root->finalang;
		parentlen = root->finalsize;
	}

	Vec2f finalVec = Vec2f::add(Vec2f::fromAngle(parentang, x), Vec2f::fromAngle(parentang + 90.f, y));


	return Vec2f::sub(pos, Vec2f(x,y));
}

void Bone::removeChilds()
{
	childs.clear();
}
