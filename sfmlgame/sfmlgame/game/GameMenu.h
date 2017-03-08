#pragma once
#include "State.h"
#include "Gui.h"
#include "Button.h"

class GameMenu :
	public State
{
public:
	GameMenu();
	~GameMenu();

	void update(float dt);
	void draw();
	void handleEvent(sf::Event event);

	void resizeGui();

	void onQuitButton(Button* sender, MouseDownEvent event);
	void onConnectButton(Button* sender, MouseDownEvent event);
	void onHostButton(Button* sender, MouseDownEvent event);
public:
	Gui gui;
};

