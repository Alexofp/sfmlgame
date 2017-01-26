#include "KeyFrameTimeline.h"
#include <iostream>


KeyFrameTimeline::KeyFrameTimeline()
{
	//progress = 0.f;
}


KeyFrameTimeline::~KeyFrameTimeline()
{
}

/*void KeyFrameTimeline::advance(float percent)
{
	progress += percent;
	while (progress > 1.f)
		progress -= 1.f;
}*/

float KeyFrameTimeline::getValue(float progress)
{
	auto high = keyframes.upper_bound(progress);
	auto low = high;
	if (low != keyframes.begin())
	{
		low--;
	}

	//std::cout << "a " << low->first << " " << low->second.value << std::endl;
	//std::cout << "b " << high->first << " " << high->second.value << std::endl;

	if (low == keyframes.end() && high == keyframes.end())
		return 0.f;

	if (low == keyframes.end())
		return high->second.value;
	if (high == keyframes.end())
		return low->second.value;

	if (low->first == high->first)
		return high->second.value;

	float len = high->first - low->first;

	float per = (progress-low->first)/ (high->first - low->first);
	//std::cout << per << std::endl;

	return (low->second.value*(1.f-per))+(high->second.value*per);
}

void KeyFrameTimeline::removeKeyFrame(float pos)
{
	/*if (keyframes.find(pos) != keyframes.end())
	{
		keyframes.erase(pos);
	}*/
	for(auto& keyframe: keyframes)
	{
		float delta = pos - keyframe.first;
		if (abs(delta) < 0.0005f)
		{
			keyframes.erase(keyframe.first);
			return;
		}
			
	}
}

void KeyFrameTimeline::addKeyFrame(float pos, float value, KeyFrame::Type type)
{
	KeyFrame frame{pos,value,type};
	
	keyframes[pos] = frame;
}

std::map<float, KeyFrame>& KeyFrameTimeline::getKeyFrames()
{
	return keyframes;
}