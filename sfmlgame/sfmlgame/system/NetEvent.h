#pragma once
#include <SFML/Network.hpp>
class NetEvent
{
public:
	NetEvent(int from, int to, std::string type);
	~NetEvent();
	sf::Packet getPacket();

	int fromId;
	int toId;
	std::string type;
	sf::Packet data;
};

