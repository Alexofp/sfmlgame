#include "Animation.h"
#include "json.hpp"
#include "Log.h"
#include <fstream>
using json = nlohmann::json;

Animation::Animation()
{
	length = 1.f;

	/*info["root"].angle.addKeyFrame(0.f, 0.f);
	info["root"].angle.addKeyFrame(0.999999f, 720.f);
	info["root"].angle.addKeyFrame(1.f, 0.f);

	info["head"].angle.addKeyFrame(0.f, 0.f);
	info["head"].angle.addKeyFrame(0.999999f, -360.f);
	info["head"].angle.addKeyFrame(1.f, 0.f);

	info["head"].ypos.addKeyFrame(0.f, 10.f);
	info["head"].ypos.addKeyFrame(0.5f, -100.f);
	info["head"].ypos.addKeyFrame(1.f, 10.f);*/
}


Animation::~Animation()
{
}

void Animation::apply(Skeleton * skelet, float pos)
{
	for (auto& b : skelet->getBones())
	{
		Bone* bone = b.second;

		if (info.find(bone->getName()) != info.end())
		{
			BoneInformation boneInfo = info.at(bone->getName());

			BoneState state{ 
				Vec2f(boneInfo.xpos.getValue(pos),boneInfo.ypos.getValue(pos)),
				boneInfo.angle.getValue(pos),
				1.f
			};

			bone->setAnimationState(state);
		}
	}
}

void Animation::loadFromFile(std::string path)
{
	std::ifstream file(path);
	json jsonData;
	file >> jsonData;

	clear();
	setLength(jsonData["length"].get<float>());

	for (json::iterator it = jsonData["data"].begin(); it != jsonData["data"].end(); ++it)
	{
		std::string boneName = it.key();
		for (std::string category : {"x","y","angle"})
		{
			for (auto& v : jsonData["data"][boneName][category])
			{
				
				float value = v["value"].get<float>();
				float time = v["time"].get<float>();;
				std::string interpolation = v["interpolation"].get<std::string>();;

				if (category == "x")
					info[boneName].xpos.addKeyFrame(time, value);
				if (category == "y")
					info[boneName].ypos.addKeyFrame(time, value);
				if (category == "angle")
					info[boneName].angle.addKeyFrame(time, value);
			}
		}
	}

}

void Animation::saveToFile(std::string path)
{
	json jsonData;
	jsonData["length"] = getLength();

	for (auto& i : info)
	{
		//jsonData["data"][i.first][1.f] = {123};
		jsonData["data"][i.first]["x"] = json::array();
		jsonData["data"][i.first]["y"] = json::array();
		jsonData["data"][i.first]["angle"] = json::array();
		for (auto& xposframes : i.second.xpos.getKeyFrames())
		{
			json fr;
			fr["value"] = xposframes.second.value;
			fr["interpolation"] = "linear";

			jsonData["data"][i.first]["x"].push_back({
				{"time", xposframes.first},
				{"value", xposframes.second.value},
				{"interpolation", "linear"}
			}
			);
		}
		for (auto& yposframes : i.second.ypos.getKeyFrames())
		{
			json fr;
			fr["value"] = yposframes.second.value;
			fr["interpolation"] = "linear";

			jsonData["data"][i.first]["y"].push_back({
				{ "time", yposframes.first },
				{ "value", yposframes.second.value },
				{ "interpolation", "linear" }
			}
			);
		}
		for (auto& angleframes : i.second.angle.getKeyFrames())
		{
			json fr;
			fr["value"] = angleframes.second.value;
			fr["interpolation"] = "linear";

			jsonData["data"][i.first]["angle"].push_back({
				{ "time", angleframes.first },
				{ "value", angleframes.second.value },
				{ "interpolation", "linear" }
			}
			);
		}
	}

	std::ofstream o(path);
	o << std::setw(4) << jsonData << std::endl;
}

void Animation::clear()
{
	info.clear();
}

void Animation::removeKeyframes(float pos)
{
	for (auto& i : info)
	{
		i.second.angle.removeKeyFrame(pos);
		i.second.xpos.removeKeyFrame(pos);
		i.second.ypos.removeKeyFrame(pos);
	}
}

void Animation::setLength(float length)
{
	this->length = length;
}

float Animation::getLength()
{
	return length;
}

Animation::BoneInformation & Animation::getBoneInfo(std::string bone)
{
	return info.at(bone);
}

bool Animation::hasBoneInfo(std::string bone)
{
	return info.find(bone)!=info.end();
}

KeyFrameTimeline & Animation::getXposTimeline(std::string bone)
{
	return info[bone].xpos;
}

KeyFrameTimeline & Animation::getYposTimeline(std::string bone)
{
	return info[bone].ypos;
}

KeyFrameTimeline & Animation::getAngleTimeline(std::string bone)
{
	return info[bone].angle;
}
