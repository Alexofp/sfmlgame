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

	void playAnimation(std::string anim);

protected:
	AnimatedSkeleton skeleton;
	Animation* currentAnimation;
	Vec2f moveControl;
	float walkSpeed;
	Vec2f lookPosition;
	std::string state;
};

