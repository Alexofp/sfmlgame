#pragma once
#include "State.h"
#include "Entity.h"
#include <vector>
#include <memory>

class Game :
	public State
{
public:
	Game();
	~Game();

	void update(float dt);
	void draw();

private:
	std::vector<std::unique_ptr<Entity> > entities;
};

