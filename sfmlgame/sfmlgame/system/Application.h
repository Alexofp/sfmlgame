#pragma once
#include <vector>
#include <memory>
#include "State.h"
#include "GameServer.h"

class Application
{
public:
	Application();
	~Application();

	void pushState(State* state);
	int run();
	void startServer(int port);
	void stopServer();
	std::vector<std::unique_ptr<State> > states;
	bool isServer;
	std::unique_ptr<GameServer> server;
};

