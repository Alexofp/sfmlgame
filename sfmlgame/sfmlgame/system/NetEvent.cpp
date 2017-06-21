#include "NetEvent.h"
#include "Server.h"

NetEvent::NetEvent(int from, int to, std::string type)
{
	fromId = from;
	toId = to;
	this->type = type;
}


NetEvent::~NetEvent()
{
}

sf::Packet NetEvent::getPacket()
{
	sf::Packet packet = sf::Packet();
	packet << (sf::Uint8)Server::MESSAGE_TYPE::EVENT;
	packet << fromId;
	packet << toId;
	packet << type;
	packet.append(data.getData(), data.getDataSize());
	return packet;
}
