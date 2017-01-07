#pragma once
#include <SFML/Graphics.hpp>
#include "Vec2i.h"
#include <functional>

class GameWindow
{
public:
	GameWindow();
	~GameWindow();

	static void open(Vec2i size);
	static void close();
	static void handleMessages();
	static void setOnClose(std::function<bool()> func); // bool func() { return true; }
	static void clear();
	static void display();
	static bool isOpen();
	static Vec2i getMousePos();
	static sf::RenderWindow& getInternalHandle();

private:
	static GameWindow& get();
	sf::RenderWindow window;
	std::function<bool()> closeCallback;
};

