#include "AnimatedSkeleton.h"
#include "GameWindow.h"
#include <algorithm>

AnimatedSkeleton::AnimatedSkeleton():
	Skeleton()
{
	animation = nullptr;
}


AnimatedSkeleton::~AnimatedSkeleton()
{
}

void AnimatedSkeleton::playAnimation(Animation * anim)
{
	animation = anim;
	progress = 0.f;
}

Animation * AnimatedSkeleton::getAnimation()
{
	return animation;
}

void AnimatedSkeleton::setSkin(Skin skin)
{
	this->skin = skin;
}

void AnimatedSkeleton::update(float dt)
{
	if (animation != nullptr)
	{
		progress += dt / animation->getLength();
		if (animation->getLooped())
		{
			while (progress > 1.f)
				progress -= 1.f;
		}
		else
		{
			if (progress > 1.f)
				progress = 1.f;
		}

		animation->apply(this, progress);
	}
}

struct SkinSortedElement
{
	SkinPart* part;
	std::string boneName;
};

void AnimatedSkeleton::draw()
{
	//Skeleton::draw();
	sf::Transform transform;
	transform.translate(pos.toSFMLVec());
	transform.rotate(angle);
	transform.scale(sf::Vector2f(scale, scale));

	sf::RenderStates states;
	states.transform = transform;

	auto& window = GameWindow::getInternalHandle();

	std::vector<SkinSortedElement> elements;
	for (auto& vecPair : skin.getParts())
	{
		SkinSortedElement element;
		element.boneName = vecPair.first;
		element.part = &vecPair.second[0];
		elements.push_back(element);
	}
	std::sort(elements.begin(), elements.end(),
		[](SkinSortedElement& a, SkinSortedElement& b) { return a.part->z > b.part->z; }
	);

	for (auto& element : elements)
	{
		std::string boneName = element.boneName;

		if (bones.find(boneName) == bones.end())
			continue;
		Bone* bone = bones.at(boneName);
		BoneState state = bone->getFinalState();

		sf::Transform boneTransform = transform;
		boneTransform.translate(state.pos.toSFMLVec());
		boneTransform.rotate(state.angle);

		for (auto& item : element.part->items)
		{
			window.draw(item.shape, boneTransform);
		}
	}
}

void AnimatedSkeleton::debugDraw()
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

float AnimatedSkeleton::getProgress()
{
	return progress;
}

void AnimatedSkeleton::setProgress(float p)
{
	progress = p;
}
