#pragma once
#include "State.h"
#include "Skeleton.h"
#include "Animation.h"
#include "Gui.h"
#include "BlueprintBackground.h"
#include "List.h"
#include "Button.h"
#include "SimpleGuiWindow.h"

class AnimationEditor :
	public State
{
public:
	enum class MouseState
	{
		Nothing,
		GrabbingBone,
		RotatingBone
	};

	AnimationEditor();
	~AnimationEditor();

	void update(float dt);
	void draw();
	void handleEvent(sf::Event event);

	void resizeGui();

	void onBoneSelected(List* sender, ListItem item);
	void onEditModeSelected(List* sender, ListItem item);
	void onSliderMoved(Slider* sender, float value);
	void onJumpButton(Button* sender, MouseDownEvent event);
	void onLengthButton(Button* sender, MouseDownEvent event);
	void onPlayButton(Button* sender, MouseDownEvent event);

	void onKeyframeButton(Button* sender, MouseDownEvent event);
	void onKeyframeAllButton(Button* sender, MouseDownEvent event);
	void onRemoveButton(Button* sender, MouseDownEvent event);
	void onRemoveAllButton(Button* sender, MouseDownEvent event);

	void onNewButton(Button* sender, MouseDownEvent event);
	void onSaveButton(Button* sender, MouseDownEvent event);
	void onLoadButton(Button* sender, MouseDownEvent event);

	void updateKeyframelist();
	void updateAnimation();
	void updateBoneList();

	std::string floatToStr(float f);
	float strToFloat(std::string f, bool trim = true);
	float getCurrentTimePos();
public:
	Skeleton skelet;
	Animation anim;
	Bone* selectedBone;

	Gui gui;
	BlueprintBackground back;

	Vec2f cameraPos;

	MouseState mouseState;

	bool isPlaying;
};

