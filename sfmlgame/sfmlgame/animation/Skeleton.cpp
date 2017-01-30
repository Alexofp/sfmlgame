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

void Skeleton::clear()
{
	root.removeChilds();
	bones.clear();

	bones["superroot"] = &root;
}

void Skeleton::playerSkeleton()
{
	clear();

	addBone(new Bone("root", 0.f, 0.f, 0.f, 20.f));
	addBone("root", new Bone("head", 0.f, 0.f, 0.f, 21.f));

	addBone("root", new Bone("larm", 4.f, -36.f, -30.f, 20.f));
	addBone("root", new Bone("rarm", 4.f, 36.f, 30.f, 20.f));

	addBone("larm", new Bone("lforearm", 28.1f, 5.5f, 30.f, 20.f));
	addBone("rarm", new Bone("rforearm", 28.1f, -5.5f, -30.f, 20.f));

	addBone("lforearm", new Bone("lhand", 31.5f, 1.5f, 9.f, 20.f));
	addBone("rforearm", new Bone("rhand", 31.5f, -1.5f, -9.f, 20.f));
}

void Skeleton::sideSkeleton()
{
	clear();

	addBone(new Bone("root", 0.f, 0.f, 0.f, 100.f));
	addBone("root", new Bone("larm", 10.f, 10.f, 80.f, 50.f));
	addBone("root", new Bone("rarm", 10.f, -10.f, -40.f, 50.f));
	addBone("root", new Bone("head", -10.f, 0.f, -90.f, 30.f));

	addBone("larm", new Bone("llarm", 60.f, 0.f, -80.f, 40.f));
	addBone("rarm", new Bone("rrarm", 60.f, 0.f, 00.f, 40.f));

	addBone("root", new Bone("lleg", 100.f, 10.f, 40.f, 50.f));
	addBone("root", new Bone("rleg", 100.f, -10.f, -40.f, 50.f));

	addBone("lleg", new Bone("llleg", 60.f, 0.f, -10.f, 50.f));
	addBone("rleg", new Bone("rrleg", 60.f, 0.f, 10.f, 50.f));
}
