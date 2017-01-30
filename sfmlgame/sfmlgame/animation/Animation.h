#pragma once
#include "KeyFrameTimeline.h"
#include <unordered_map>
#include <string>
#include "Skeleton.h"


class Animation
{
public:
	struct BoneInformation
	{
		KeyFrameTimeline xpos;
		KeyFrameTimeline ypos;
		KeyFrameTimeline angle;

	};

	Animation();
	~Animation();

	void apply(Skeleton* skelet, float pos);
	void loadFromFile(std::string path);
	void saveToFile(std::string path);
	void clear();
	void removeKeyframes(float pos);
	void setLength(float length);
	float getLength();
	void setLooped(bool loop);
	bool getLooped();
	BoneInformation& getBoneInfo(std::string bone);
	bool hasBoneInfo(std::string bone);
	KeyFrameTimeline& getXposTimeline(std::string bone);
	KeyFrameTimeline& getYposTimeline(std::string bone);
	KeyFrameTimeline& getAngleTimeline(std::string bone);

private:
	std::unordered_map<std::string, BoneInformation> info;
	float length;
	bool looped;
};

