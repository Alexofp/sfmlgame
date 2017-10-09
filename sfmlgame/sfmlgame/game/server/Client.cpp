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

void Client::disconnect()
{
	Client& client = get();
	client.socket.disconnect();
	client.clientid = -1;
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
	}else
	if (type == Server::MESSAGE_TYPE::PING)
	{
		sf::Uint8 pingPassword;
		packet >> pingPassword;

		sf::Packet pingpacket;
		pingpacket << (sf::Uint8)Server::MESSAGE_TYPE::PING << pingPassword;
		send(pingpacket);
	}else
	if (type == Server::MESSAGE_TYPE::ENTITY_INFO)
	{
		if (client.onGameInfo)
		{
			client.onGameInfo(packet);
		}
	}
	else
	{
		if (client.onPacket)
		{
			client.onPacket(type, packet);
		}
	}
}

void Client::update(float dt)
{
	Client& client = get();
	for (int i = 0; i < 100; i++)
	{
		sf::Packet packet;
		auto status = client.socket.receive(packet);
		if (status == sf::Socket::Done)
		{
			onEvent(packet);
			continue;
		}
		else if (status == sf::Socket::Partial)
		{
			while (client.socket.receive(packet) == sf::Socket::Partial)
			{

			}
			onEvent(packet);
			continue;
		}
		break;
	}

}

void Client::send(sf::Packet packet)
{
	Client& client = get();
	while (client.socket.send(packet) == sf::Socket::Partial) {};
}

void Client::send(NetEvent event)
{
	sf::Packet packet = event.getPacket();
	send(packet);
}

void Client::setOnGameInfo(std::function<void(sf::Packet&)> f)
{
	Client& client = get();
	client.onGameInfo = f;
}

void Client::setOnPacket(std::function<bool(Server::MESSAGE_TYPE, sf::Packet&)> f)
{
	Client& client = get();
	client.onPacket = f;
}

int Client::getClientId()
{
	Client& client = get();
	return client.clientid;
}

Client & Client::get()
{
	static Client c;
	return c;
}
