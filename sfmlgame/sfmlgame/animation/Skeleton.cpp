#include "Skeleton.h"
#include "Log.h"
#include "GameWindow.h"
#include <SFML/Graphics.hpp>


Skeleton::Skeleton() :
	root("superroot", 0.f, 0.f, 0.f, 0.f)
{
	bones["superroot"] = &root;

	pos = Vec2f();
	scale = 1.f;
	angle = 0.f;
}


Skeleton::~Skeleton()
{
}

void Skeleton::addBone(std::string parent, Bone * bone)
{
	if (bones.find(parent) == bones.end())
	{
		Log::err("Bone with name " + parent + " is not found");
		delete bone;
		return;
	}

	bones[bone->getName()] = bone;
	bones[parent]->addChild(bone);

}

void Skeleton::addBone(Bone * bone)
{
	addBone("superroot", bone);
}

void Skeleton::setPos(Vec2f pos)
{
	this->pos = pos;
}

void Skeleton::setScale(float scale)
{
	this->scale = scale;
}

void Skeleton::setAng(float ang)
{
	this->angle = ang;
}

Vec2f Skeleton::getPos()
{
	return pos;
}

float Skeleton::getScale()
{
	return scale;
}

float Skeleton::getAng()
{
	return angle;
}

sf::Transform Skeleton::getTransform()
{
	sf::Transform transform;
	transform.translate(pos.toSFMLVec());
	transform.rotate(angle);
	transform.scale(sf::Vector2f(scale, scale));

	return transform;
}

Vec2f Skeleton::transformPoint(Vec2f pos)
{
	return getTransform().transformPoint(pos.toSFMLVec());
}

void Skeleton::draw()
{
	sf::Transform transform;
	transform.translate(pos.toSFMLVec());
	transform.rotate(angle);
	transform.scale(sf::Vector2f(scale, scale));

	sf::RenderStates states;
	states.transform = transform;

	auto& window = GameWindow::getInternalHandle();

	for (auto& bone : bones)
	{
		BoneState state = bone.second->getFinalState();

		sf::Vertex vertices[2] =
		{
			sf::Vertex(state.pos.toSFMLVec()),
			sf::Vertex(Vec2f::add(state.pos, Vec2f::fromAngle(state.angle, state.size)).toSFMLVec())
		};
		window.draw(vertices, 2, sf::Lines, states);
	}
}

std::unordered_map<std::string, Bone*>& Skeleton::getBones()
{
	return bones;
}
