#pragma once
class Application;
#include <SFML\Window\Event.hpp>

class State
{
public:
	State();
	virtual ~State();

	virtual void update(float dt) = 0;
	virtual void draw() = 0;
	virtual void handleEvent(sf::Event event) = 0;

	void pushState(State* state);
	void finish();

	bool finished;
	Application* app;
};

