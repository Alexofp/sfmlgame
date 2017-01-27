#pragma once
#include "State.h"
#include "Entity.h"
#include <vector>
#include <memory>
#include "Player.h"
#include "Server.h"
#include <unordered_map>
#include "Terrain.h"

class Game :
	public State
{
public:
	Game();
	~Game();

	void update(float dt);
	void draw();
	void handleEvent(sf::Event event);

	Entity* findEntity(int nid);
	void applyGameInfo(sf::Packet& info);
	bool handlePacket(Server::MESSAGE_TYPE type, sf::Packet& packet);
	sf::Packet getClientInfo();

private:
	std::vector<std::unique_ptr<Entity> > entities;
	std::unordered_map<int, Player*> players;
	Terrain terrain;
};

