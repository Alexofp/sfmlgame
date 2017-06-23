#include "AnimationEditor.h"
#include "KeyFrameTimeline.h"
#include "Log.h"
#include "Button.h"
#include "List.h"
#include "GameWindow.h"
#include "Input.h"
#include "Util.h"
#include "Slider.h"
#include <set>
#include <sstream>
#include <iomanip>
#include "EditBox.h"

AnimationEditor::AnimationEditor()
{
	isPlaying = false;
	skelet.setPos(Vec2f(0.f, 0.f));
	skelet.setAng(0.f);
	skelet.setScale(1.f);
	//skelet.sideSkeleton();
	skelet.playerSkeleton();

	Skin skin;
	skin.loadFromFile("resources/skin.json");
	skelet.setSkin(skin);

	skelet.playAnimation(&anim);

	{
		Button* button1 = new Button();
		button1->setPos(Vec2f(80.f, 30.f));
		button1->setSize(Vec2f(100.f, 30.f));
		button1->setTextSize(14);
		button1->setTexture("button");
		button1->setText(L"New");
		button1->OnClick(std::bind(&AnimationEditor::onNewButton, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(button1);
	}
	{
		Button* button1 = new Button();
		button1->setPos(Vec2f(200.f, 30.f));
		button1->setSize(Vec2f(100.f, 30.f));
		button1->setTextSize(14);
		button1->setTexture("button");
		button1->setText(L"Save");
		button1->OnClick(std::bind(&AnimationEditor::onSaveButton, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(button1);
	}
	{
		Button* button1 = new Button();
		button1->setPos(Vec2f(320.f, 30.f));
		button1->setSize(Vec2f(100.f, 30.f));
		button1->setTextSize(14);
		button1->setTexture("button");
		button1->setText(L"Load");
		button1->OnClick(std::bind(&AnimationEditor::onLoadButton, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(button1);
	}
	{
		Button* button1 = new Button();
		button1->setPos(Vec2f(440.f, 30.f));
		button1->setSize(Vec2f(100.f, 30.f));
		button1->setTextSize(14);
		button1->setTexture("button");
		button1->setText(L"Skin");
		button1->OnClick(std::bind(&AnimationEditor::onSkinButton, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(button1);
	}
	{
		List* list2 = new List();
		list2->setSize(Vec2f(200.f, 200.f));
		list2->OnListSelect(std::bind(&AnimationEditor::onBoneSelected, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(list2, "bonelist");
		updateBoneList();
	}
	{
		List* list2 = new List();
		list2->setSize(Vec2f(200.f, 200.f));
		gui.add(list2, "keyframelist");
	}
	{
		List* list2 = new List();
		list2->setSize(Vec2f(200.f, 50.f));
		list2->addItem("Position", "pos");
		list2->addItem("Angle", "ang");
		list2->addItem("Skin", "skin");
		list2->OnListSelect(std::bind(&AnimationEditor::onEditModeSelected, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(list2, "editlist");
	}
	{
		Slider* slider = new Slider();
		slider->setSize(Vec2f(100.f, 10.f));
		slider->setVertical(false);
		slider->OnValueChange(std::bind(&AnimationEditor::onSliderMoved, this, std::placeholders::_1, std::placeholders::_2));

		gui.add(slider, "animslider");
	}
	{
		EditBox* edit = new EditBox();
		edit->setText(L"0.000");
		edit->setTextSize(12u);
		edit->setSize(Vec2f(100.f, 30.f));
		edit->setPos(Vec2f(75.f, 130.f));
		edit->setTexture("editbox");
		gui.add(edit, "timeedit");

		Button* button1 = new Button();
		button1->setPos(Vec2f(164.f, 130.f));
		button1->setSize(Vec2f(70.f, 30.f));
		button1->setTextSize(14u);
		button1->setTexture("button");
		button1->setText(L"jump");
		button1->setMult(0.3f);
		button1->OnClick(std::bind(&AnimationEditor::onJumpButton, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(button1);
	}
	{
		EditBox* edit = new EditBox();
		edit->setText(Util::strToWStr(floatToStr(anim.getLength())));
		edit->setTextSize(12u);
		edit->setSize(Vec2f(100.f, 30.f));
		edit->setPos(Vec2f(75.f, 165.f));
		edit->setTexture("editbox");
		gui.add(edit, "lengthedit");

		Button* button1 = new Button();
		button1->setPos(Vec2f(164.f, 165.f));
		button1->setSize(Vec2f(70.f, 30.f));
		button1->setTextSize(14u);
		button1->setTexture("button");
		button1->setText(L"Length");
		button1->setMult(0.3f);
		button1->OnClick(std::bind(&AnimationEditor::onLengthButton, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(button1);
	}
	{
		Button* button1 = new Button();
		button1->setPos(Vec2f(250.f, 130.f));
		button1->setSize(Vec2f(70.f, 30.f));
		button1->setTextSize(14u);
		button1->setTexture("button");
		button1->setText(L"Play");
		button1->setMult(0.3f);
		button1->OnClick(std::bind(&AnimationEditor::onPlayButton, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(button1);
	}
	{
		Button* button1 = new Button();
		//button1->setPos(Vec2f(164.f, 130.f));
		button1->setSize(Vec2f(100.f, 30.f));
		button1->setTextSize(12u);
		button1->setTexture("button");
		button1->setText(L"Keyframe");
		button1->setMult(0.3f);
		button1->OnClick(std::bind(&AnimationEditor::onKeyframeButton, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(button1, "keyframe");
	}
	{
		Button* button1 = new Button();
		//button1->setPos(Vec2f(164.f, 130.f));
		button1->setSize(Vec2f(100.f, 30.f));
		button1->setTextSize(12u);
		button1->setTexture("button");
		button1->setText(L"Keyframe all");
		button1->setMult(0.3f);
		button1->OnClick(std::bind(&AnimationEditor::onKeyframeAllButton, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(button1, "keyframeall");
	}
	{
		Button* button1 = new Button();
		//button1->setPos(Vec2f(164.f, 130.f));
		button1->setSize(Vec2f(100.f, 30.f));
		button1->setTextSize(12u);
		button1->setTexture("button");
		button1->setText(L"Remove");
		button1->setMult(0.3f);
		button1->OnClick(std::bind(&AnimationEditor::onRemoveButton, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(button1, "remove");
	}
	{
		Button* button1 = new Button();
		//button1->setPos(Vec2f(164.f, 130.f));
		button1->setSize(Vec2f(100.f, 30.f));
		button1->setTextSize(12u);
		button1->setTexture("button");
		button1->setText(L"Remove all");
		button1->setMult(0.3f);
		button1->OnClick(std::bind(&AnimationEditor::onRemoveAllButton, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(button1, "removeall");
	}

	mouseState = MouseState::Nothing;
	resizeGui();
}


AnimationEditor::~AnimationEditor()
{
}

void AnimationEditor::resizeGui()
{
	Vec2f size(gui.getView().getSize());

	gui.findById("bonelist")->setPos(Vec2f(size.x - 100.f, size.y - 100.f));
	gui.findById("keyframelist")->setPos(Vec2f(size.x - 304.f, size.y - 100.f));
	gui.findById("editlist")->setPos(Vec2f(size.x - 304.f, size.y - 230.f));
	gui.findById("keyframe")->setPos(Vec2f(size.x - 460.f, size.y - 180.f));
	gui.findById("keyframeall")->setPos(Vec2f(size.x - 460.f, size.y - 140.f));
	gui.findById("remove")->setPos(Vec2f(size.x - 460.f, size.y - 80.f));
	gui.findById("removeall")->setPos(Vec2f(size.x - 460.f, size.y - 40.f));

	gui.findById("animslider")->setPos(Vec2f(size.x/2.f, 80.f));
	gui.findById("animslider")->setSize(Vec2f(size.x-50.f, 40.f));
}

void AnimationEditor::update(float dt)
{
	float cameraSpeed = 200.f;
	if (Input::getKey(Input::A))
		cameraPos.x -= dt*cameraSpeed;
	if (Input::getKey(Input::D))
		cameraPos.x += dt*cameraSpeed;
	if (Input::getKey(Input::W))
		cameraPos.y -= dt*cameraSpeed;
	if (Input::getKey(Input::S))
		cameraPos.y += dt*cameraSpeed;
	GameWindow::setCameraCenter(cameraPos);

	if (isPlaying)
	{
		Slider* slider = ((Slider*)gui.findById("animslider"));

		float prog = slider->getValue();
		skelet.setProgress(prog);

		skelet.update(dt);

		prog = skelet.getProgress();
		slider->setValue(prog);
		std::string text = floatToStr(prog);

		std::wstring wtext = std::wstring(text.begin(), text.end());
		((EditBox*)gui.findById("timeedit"))->setText(wtext);
	}

	if (selectedBone != nullptr)
	{
		Vec2f mousePos = Input::getWorldMousePos();

		if (Input::getKeyDown(Input::G))
			mouseState = MouseState::GrabbingBone;
		if (Input::getKeyDown(Input::R))
			mouseState = MouseState::RotatingBone;
		if (Input::getKeyDown(Input::Escape))
			mouseState = MouseState::Nothing;

		if (mouseState == MouseState::GrabbingBone)
		{
			BoneState state = selectedBone->getAnimationState();
			state.pos = selectedBone->getPosRelativeToParent((selectedBone->getParent()->getRelativePos(skelet.getTransform(), Input::getWorldMousePos())));
			selectedBone->setAnimationState(state);
		}
		if (mouseState == MouseState::RotatingBone)
		{
			BoneState state = selectedBone->getAnimationState();
			state.angle += Input::getWorldMouseDelta().x;
			selectedBone->setAnimationState(state);
		}
		if (mouseState != MouseState::Nothing)
		{
			if (Input::getMouseUp(Input::MouseLeft))
			{
				mouseState = MouseState::Nothing;
			}
		}
	}
	else
	{
		mouseState = MouseState::Nothing;
	}
}

void AnimationEditor::draw()
{
	back.draw();

	skelet.draw();
	skelet.debugDraw();

	if (selectedBone != nullptr)
	{
		auto l = selectedBone->getTransformedPos(skelet.getTransform());
		Util::drawLine(l.first, l.second, sf::Color::Red);

		sf::CircleShape c(1.f);
		c.setFillColor(sf::Color::Red);
		c.setOrigin(1.f, 1.f);
		c.setPosition(l.first.toSFMLVec());
		GameWindow::getInternalHandle().draw(c);
	}

	gui.draw();
}

void AnimationEditor::handleEvent(sf::Event event)
{
	bool handled = gui.handleEvent(event);

	if (event.type == sf::Event::MouseWheelScrolled)
	{
		if (event.mouseWheelScroll.delta > 0)
		{
			GameWindow::zoom(0.9f);
		}
		else
		{
			if (GameWindow::getZoom() < 4.f)
			{
				GameWindow::zoom(1.1f);
			}
		}
	}else
		if (event.type == sf::Event::Resized)
		{
			resizeGui();
		}

	if (handled)
		return;

	if (mouseState == MouseState::Nothing)
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left)
		{
			float minDist = 50.f;
			Bone* closestBone = nullptr;

			for (auto& bonePair : skelet.getBones())
			{
				if (bonePair.first == "superroot")
					continue;

				Bone* bone = bonePair.second;
				auto posPair = bone->getTransformedPos(skelet.getTransform());

				float dist = Util::lineDistanceToPoint(posPair.first, posPair.second, Input::getWorldMousePos());

				if (dist < minDist)
				{
					minDist = dist;
					closestBone = bone;
				}
			}
			selectedBone = closestBone;
			if (selectedBone != nullptr)
			{
				((List*)gui.findById("bonelist"))->setSelected(selectedBone->getName());
				updateKeyframelist();
			}
		}
	}
}

void AnimationEditor::onBoneSelected(List * sender, ListItem item)
{
	selectedBone = skelet.getBones()[item.id];
	updateKeyframelist();
}

void AnimationEditor::onEditModeSelected(List * sender, ListItem item)
{
	updateKeyframelist();
}

void AnimationEditor::onSliderMoved(Slider * sender, float value)
{
	std::string text = floatToStr(value);
	((EditBox*)gui.findById("timeedit"))->setText( std::wstring(text.begin(), text.end()) );
}

void AnimationEditor::onJumpButton(Button * sender, MouseDownEvent event)
{
	EditBox* editBox = (EditBox*)gui.findById("timeedit");
	std::wstring wtext = editBox->getText();
	std::string text(wtext.begin(), wtext.end());

	float f = strToFloat(text);
	text = floatToStr(f);
	f = strToFloat(text);

	wtext = std::wstring(text.begin(), text.end());
	editBox->setText(wtext);

	((Slider*)gui.findById("animslider"))->setValue(f);
	updateAnimation();
}

void AnimationEditor::onLengthButton(Button * sender, MouseDownEvent event)
{
	EditBox* editBox = (EditBox*)gui.findById("lengthedit");
	std::wstring wtext = editBox->getText();
	std::string text(wtext.begin(), wtext.end());

	float f = strToFloat(text, false);
	text = floatToStr(f);
	f = strToFloat(text, false);

	wtext = std::wstring(text.begin(), text.end());
	editBox->setText(wtext);

	anim.setLength(f);
}

void AnimationEditor::onPlayButton(Button * sender, MouseDownEvent event)
{
	isPlaying = !isPlaying;
}

void AnimationEditor::onKeyframeButton(Button * sender, MouseDownEvent event)
{
	auto listitem = ((List*)gui.findById("editlist"))->getSelected();
	auto boneitem = ((List*)gui.findById("bonelist"))->getSelected();
	List* keyframelist = (List*)gui.findById("keyframelist");
	if (listitem == nullptr || boneitem == nullptr)
		return;

	std::string boneName = boneitem->id;
	Bone* bone = skelet.getBones().at(boneitem->id);
	float time = getCurrentTimePos();


	if (listitem->id == "pos")
	{
		if (listitem != nullptr && boneitem != nullptr)
		{
			
			BoneState state = bone->getAnimationState();
			anim.getXposTimeline(boneName).addKeyFrame(time, state.pos.x);
			anim.getYposTimeline(boneName).addKeyFrame(time, state.pos.y);
			updateKeyframelist();
		}
	}
	if (listitem->id == "ang")
	{
		if (listitem != nullptr && boneitem != nullptr)
		{

			BoneState state = bone->getAnimationState();
			anim.getAngleTimeline(boneName).addKeyFrame(time, state.angle);
			updateKeyframelist();
		}
	}

}

void AnimationEditor::onKeyframeAllButton(Button * sender, MouseDownEvent event)
{
	auto listitem = ((List*)gui.findById("editlist"))->getSelected();
	float time = getCurrentTimePos();
	if (listitem == nullptr)
		return;

	if (listitem->id == "pos")
	{
		for (auto& bonePair: skelet.getBones())
		{
			Bone* bone = bonePair.second;
			std::string boneName = bone->getName();
			BoneState state = bone->getAnimationState();
			anim.getXposTimeline(boneName).addKeyFrame(time, state.pos.x);
			anim.getYposTimeline(boneName).addKeyFrame(time, state.pos.y);
		}
		updateKeyframelist();
	}
	if (listitem->id == "ang")
	{
		for (auto& bonePair : skelet.getBones())
		{
			Bone* bone = bonePair.second;
			std::string boneName = bone->getName();
			BoneState state = bone->getAnimationState();
			anim.getAngleTimeline(boneName).addKeyFrame(time, state.angle);
		}
		updateKeyframelist();
	}

}

void AnimationEditor::onRemoveButton(Button * sender, MouseDownEvent event)
{
	auto listitem = ((List*)gui.findById("editlist"))->getSelected();
	auto boneitem = ((List*)gui.findById("bonelist"))->getSelected();
	auto keyitem = ((List*)gui.findById("keyframelist"))->getSelected();
	if (listitem == nullptr || boneitem == nullptr || keyitem == nullptr)
		return;

	List* keyframelist = (List*)gui.findById("keyframelist");
	std::string boneName = boneitem->id;
	Bone* bone = skelet.getBones().at(boneitem->id);
	float time = strToFloat(keyitem->id, false);//getCurrentTimePos();

	if (listitem->id == "pos")
	{
		anim.getXposTimeline(boneName).removeKeyFrame(time);
		anim.getYposTimeline(boneName).removeKeyFrame(time);
		updateKeyframelist();
	}
	if (listitem->id == "ang")
	{
		anim.getAngleTimeline(boneName).removeKeyFrame(time);
		updateKeyframelist();
	}
}

void AnimationEditor::onRemoveAllButton(Button * sender, MouseDownEvent event)
{
	auto listitem = ((List*)gui.findById("editlist"))->getSelected();
	auto keyitem = ((List*)gui.findById("keyframelist"))->getSelected();
	if (listitem == nullptr || keyitem == nullptr)
		return;

	List* keyframelist = (List*)gui.findById("keyframelist");
	//std::string boneName = boneitem->id;
	//Bone* bone = skelet.getBones().at(boneitem->id);
	float time = strToFloat(keyitem->id, false);//getCurrentTimePos();

	
	if (listitem->id == "pos")
	{
		for (auto& bonePair : skelet.getBones())
		{
			Bone* bone = bonePair.second;
			std::string boneName = bone->getName();
			anim.getXposTimeline(boneName).removeKeyFrame(time);
			anim.getYposTimeline(boneName).removeKeyFrame(time);
		}
		updateKeyframelist();
	}
	if (listitem->id == "ang")
	{
		for (auto& bonePair : skelet.getBones())
		{
			Bone* bone = bonePair.second;
			std::string boneName = bone->getName();
			anim.getAngleTimeline(boneName).removeKeyFrame(time);
		}
		updateKeyframelist();
	}
}

void AnimationEditor::onNewButton(Button * sender, MouseDownEvent event)
{
	SimpleGuiWindow* window = new SimpleGuiWindow({
		SimpleWidget::TextLine(L"Are you sure?")
	}, SimpleGuiWindow::Style::OkCancel);
	window->setSize(Vec2f(200.f, 0.f));

	window->OnOk([&](std::unordered_map<std::string, SimpleGuiWindow::Result>& results) {
		
		SimpleGuiWindow* window = new SimpleGuiWindow({
			SimpleWidget::TextLine(L"Select skeleton type"),
			SimpleWidget::ListBox("type", {{"Player skeleton", "player"}, {"Test skeleton", "test"}, {"Legs", "legs"}}, "player")
		}, SimpleGuiWindow::Style::OkCancel);

		window->OnOk([&](std::unordered_map<std::string, SimpleGuiWindow::Result>& results) {
			std::string type = results["type"].listBox.id;

			anim.clear();
			selectedBone = nullptr;
			if (type == "player")
			{
				skelet.playerSkeleton();
				skin.loadFromFile("resources/skin.json");
				skelet.setSkin(skin);
			}
			if (type == "test")
			{
				skelet.sideSkeleton();
			}
			if (type == "legs")
			{
				skelet.legsSkeleton();
				skin.loadFromFile("resources/legsskin.json");
				skelet.setSkin(skin);
			}
			updateBoneList();
			updateKeyframelist();

			return true;
		});

		gui.add(window);

		return true;
	});
	gui.add(window);

}

void AnimationEditor::onSaveButton(Button * sender, MouseDownEvent event)
{
	SimpleGuiWindow* window = new SimpleGuiWindow({
		SimpleWidget::TextLine(L"Select save location"),
		SimpleWidget::EditBox("save",L"path", L"resources/lastanim.json") 
	}, SimpleGuiWindow::Style::OkCancel);

	window->OnOk([&](std::unordered_map<std::string, SimpleGuiWindow::Result>& results) {
		anim.saveToFile(Util::wStrToStr(results["save"].editBox.text));
		return true;
	});
	gui.add(window);
}

void AnimationEditor::onLoadButton(Button * sender, MouseDownEvent event)
{
	SimpleGuiWindow* window = new SimpleGuiWindow({
		SimpleWidget::TextLine(L"Select file location"),
		SimpleWidget::EditBox("load",L"path", L"resources/lastanim.json") 
	}, SimpleGuiWindow::Style::OkCancel);

	window->OnOk([&](std::unordered_map<std::string, SimpleGuiWindow::Result>& results) {
		anim.loadFromFile(Util::wStrToStr(results["load"].editBox.text));
		((EditBox*)gui.findById("lengthedit"))->setText(Util::strToWStr(floatToStr(anim.getLength())));
		updateKeyframelist();
		return true;
	});
	gui.add(window);
}

void AnimationEditor::onSkinButton(Button * sender, MouseDownEvent event)
{
	SimpleGuiWindow* window = new SimpleGuiWindow({
		SimpleWidget::TextLine(L"Select skin file location"),
		SimpleWidget::EditBox("load",L"path", L"resources/skin.json")
	}, SimpleGuiWindow::Style::OkCancel);

	window->OnOk([&](std::unordered_map<std::string, SimpleGuiWindow::Result>& results) {
		Skin skin;
		skin.loadFromFile(Util::wStrToStr(results["load"].editBox.text));
		skelet.setSkin(skin);
		return true;
	});
	gui.add(window);
}

void AnimationEditor::updateKeyframelist()
{
	((List*)gui.findById("keyframelist"))->clearItems();
	auto listitem = ((List*)gui.findById("editlist"))->getSelected();
	auto boneitem = ((List*)gui.findById("bonelist"))->getSelected();
	List* keyframelist = (List*)gui.findById("keyframelist");

	if (listitem != nullptr && boneitem !=nullptr)
	{
		std::string editType = listitem->id;
		std::string boneName = boneitem->id;

		if (!anim.hasBoneInfo(boneName))
			return;

		auto& info = anim.getBoneInfo(boneName);

		if (editType == "pos")
		{
			std::map<float, Vec2f> frames;
			for (auto& KeyFramepair : info.xpos.getKeyFrames())
				frames[KeyFramepair.first].x = KeyFramepair.second.value;
			for (auto& KeyFramepair : info.ypos.getKeyFrames())
				frames[KeyFramepair.first].y = KeyFramepair.second.value;
			
			for (auto& fpair : frames)
			{
				float f = fpair.first;
				std::string str = floatToStr(f)+" ("+floatToStr(fpair.second.x)+","+ floatToStr(fpair.second.y)+")";
				keyframelist->addItem(str,str);
			}
		}
		if (editType == "ang")
		{
			for (auto& fpair : info.angle.getKeyFrames())
			{
				float f = fpair.first;
				std::string str = floatToStr(f)+"  "+ floatToStr(fpair.second.value);
				keyframelist->addItem(str, str);
			}
		}
	}
}

void AnimationEditor::updateAnimation()
{
	float value = ((Slider*)gui.findById("animslider"))->getValue();

	anim.apply(&skelet, value);
}

void AnimationEditor::updateBoneList()
{
	List* bonelist = ((List*)gui.findById("bonelist"));
	bonelist->clearItems();

	for (auto& bonePair : skelet.getBones())
	{
		if (bonePair.first == "superroot")
			continue;
		bonelist->addItem(bonePair.first, bonePair.first);
	}
}

std::string AnimationEditor::floatToStr(float f)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(3) << f;
	std::string s = stream.str();

	return s;
}

float AnimationEditor::strToFloat(std::string f, bool trim)
{
	try
	{
		float n = std::stof(f);
		if (trim)
		{
			if (n < 0.f)
				n = 0.f;
			if (n > 1.f)
				n = 1.f;
		}
		return n;
	}
	catch (std::invalid_argument e)
	{
		return 0.f;
	}
}

float AnimationEditor::getCurrentTimePos()
{
	Slider* slider = ((Slider*)gui.findById("animslider"));

	float prog = slider->getValue();
	return prog;
}
