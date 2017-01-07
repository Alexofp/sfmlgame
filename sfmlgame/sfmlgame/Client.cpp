#include "Client.h"
#include "Log.h"
#include "Server.h"

Client::Client()
{
	clientid = -1;
}


Client::~Client()
{
}

void Client::connect(std::string address, int port)
{
	Client& client = get();
	sf::Socket::Status status = client.socket.connect(address, port);
	if (status != sf::Socket::Done)
	{
		Log::err("[client] Error while connecting");
	}
	client.socket.setBlocking(false);
}

void Client::onEvent(sf::Packet & packet)
{
	Client& client = get();
	sf::Uint8 t;
	packet >> t;
	auto type = (Server::MESSAGE_TYPE)t;

	if (type == Server::MESSAGE_TYPE::SET_CLIENT_ID)
	{
		if (client.clientid >= 0)
		{
			Log::err("[client] Redefining client id?");
		}

		sf::Uint32 id;
		packet >> id;
		
		client.clientid = id;
		Log::debug("[client] My client id: " + std::to_string(id));
	}
}

void Client::update(float dt)
{
	Client& client = get();
	sf::Packet packet;
	if (client.socket.receive(packet) == sf::Socket::Done)
	{
		onEvent(packet);
	}
}

Client & Client::get()
{
	static Client c;
	return c;
}
