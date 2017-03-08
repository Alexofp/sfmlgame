#pragma once
#include <SFML/Graphics.hpp>
#include "Vec2i.h"
#include "Vec2f.h"
#include <functional>

class GameWindow
{
public:
	GameWindow();
	~GameWindow();

	static void open(Vec2i size, bool fullscreen);
	static void close();
	static void handleMessages();
	static void setOnClose(std::function<bool()> func); // bool func() { return true; }
	static void setOnEvent(std::function<void(sf::Event)> func);
	static void clear();
	static void display();
	static bool isOpen();
	static Vec2i getMousePos();
	static Vec2i getSize();
	static sf::RenderWindow& getInternalHandle();
	static bool isFocused();
	static void resizeContent(Vec2i size);
	static void setZoom(float z);
	static float getZoom();
	static void zoom(float z);
	static void setCameraCenter(Vec2f pos);

private:
	static GameWindow& get();
	sf::RenderWindow window;
	std::function<bool()> closeCallback;
	std::function<void(sf::Event)> eventCallback;
	float zoomLevel;
};

