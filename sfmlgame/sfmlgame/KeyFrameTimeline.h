#pragma once
#include <vector>
#include <map>

struct KeyFrame
{
	enum class Type
	{
		Linear
	};

	float pos;
	float value;
	Type type;
};

class KeyFrameTimeline
{
public:
	KeyFrameTimeline();
	~KeyFrameTimeline();

	//void advance(float percent);
	float getValue(float percent);
	void removeKeyFrame(float pos);

	void addKeyFrame(float pos, float value, KeyFrame::Type type = KeyFrame::Type::Linear);
	std::map<float, KeyFrame>& getKeyFrames();
private:
	std::map<float, KeyFrame> keyframes;
	//float progress;
};

