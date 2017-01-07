#pragma once
#include <vector>
#include <memory>
#include "State.h"

class Application
{
public:
	Application();
	~Application();

	void pushState(State* state);
	int run();
	std::vector<std::unique_ptr<State> > states;
};

