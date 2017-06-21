#pragma once
#include "AliveEntity.h"
class Person :
	public AliveEntity
{
public:
	Person(int nid = -1);
	virtual ~Person();

	virtual void init();
	virtual void draw();
	void updateSkeleton(float dt);

	void playAnimation(std::string anim, int priority = 0);
	void playAttack();
	std::string getCurrentAnimation();
	void attack();

	virtual void handleEvent(int fromId, std::string type, sf::Packet& packet);
	virtual void onDeath();

protected:
	AnimatedSkeleton skeleton;
	Animation* currentAnimation;
	std::string currentAnimationName;
	Vec2f moveControl;
	float walkSpeed;
	Vec2f lookPosition;
	std::string state;
	int currentPriority;
};

