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
	void setSkin(Skin skin);

	void update(float dt);
	void draw();

	float getProgress();
	void setProgress(float p);
private:
	Skin skin;

	Animation* animation;
	float progress;
};

