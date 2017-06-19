#pragma once
#include "Skeleton.h"
#include "Skin.h"
#include "Animation.h"

class AnimatedSkeleton :
	public Skeleton
{
public:
	AnimatedSkeleton();
	~AnimatedSkeleton();

	void playAnimation(Animation* anim);
	Animation* getAnimation();
	void setSkin(Skin skin);

	void update(float dt);
	void draw();
	void debugDraw();

	float getProgress();
	void setProgress(float p);
	void setSpeed(float speed);
private:
	Skin skin;

	Animation* animation;
	float progress;
	float speed;
};

