#pragma once
#include "State.h"
#include "Gui.h"
#include "Button.h"
#include "EditorTerrain.h"
#include "List.h"

class MapEditor :
	public State
{
public:
	MapEditor();
	~MapEditor();

	void update(float dt);
	void draw();
	void handleEvent(sf::Event event);

	void resizeGui();

	void onTextureSelected(List* sender, ListItem item);
	void onNewButton(Button* sender, MouseDownEvent event);
	void onSaveButton(Button* sender, MouseDownEvent event);
	void onLoadButton(Button* sender, MouseDownEvent event);
private:
	float getRadius();
	sf::Color getColor();

	Gui gui;
	EditorTerrain terrain;
	Vec2f cameraPos;
	int textureMode;
	std::string mapName;
};

