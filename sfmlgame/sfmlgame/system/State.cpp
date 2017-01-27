#include "State.h"
#include "Application.h"

State::State()
{
	app = 0;
}


State::~State()
{
}

void State::pushState(State * state)
{
	if (app)
	{
		app->pushState(state);
	}
}

void State::finish()
{
	finished = true;
}
