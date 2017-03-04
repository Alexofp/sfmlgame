#include "Server.h"
#include "Log.h"


Server::Server()
{
	socketId = 0;
	pingTimer = 1.f;
	gameTimer = 0.f;
	lastEntityId = 0;
	isserver = false;
}


Server::~Server()
{
}

void Server::listen(int port)
{
	Server& server = get();

	if (server.listener.listen(port) != sf::Socket::Done)
	{
		Log::err("[server] Error while trying to listen");
		return;
	}
	server.isserver = true;
	server.listener.setBlocking(false);
}

void Server::update(float dt)
{
	Server& server = get();

	std::shared_ptr<sf::TcpSocket> socket(new sf::TcpSocket());
	if (server.listener.accept(*socket) == sf::Socket::Done)
	{
		Log::debug("[server] New client with id " + std::to_string(server.socketId) );
		server.selector.add(*socket);

		ClientInformation clientInfo;
		clientInfo.id = server.socketId;
		clientInfo.socket = socket;
		clientInfo.ping = 999;
		sf::Uint8 pingPassword = rand() & 256;
		clientInfo.pingPassword = pingPassword;
		clientInfo.disconnected = false;
		server.clients.push_back(clientInfo);

		socket->setBlocking(false);

		sf::Packet packet;
		packet << (sf::Uint8)Server::MESSAGE_TYPE::SET_CLIENT_ID << (sf::Uint32)server.socketId;
		clientInfo.socket->send(packet);

		if (server.onNewPlayer)
		{
			server.onNewPlayer(clientInfo);
		}


		sf::Packet pingpacket;
		pingpacket << (sf::Uint8)Server::MESSAGE_TYPE::PING << pingPassword;
		send(clientInfo, pingpacket);

		server.socketId++;
	}

	for (auto& client : server.clients)
	{
		sf::Packet packet;
		auto status = client.socket->receive(packet);
		if (status == sf::Socket::Done)
		{
			onEvent(client, packet);
		}
		if (status == sf::Socket::Disconnected)
		{
			Log::debug("[server] Client with id "+std::to_string(client.id)+" has disconnected");
			client.disconnected = true;
		}
	}
	server.clients.erase(
		std::remove_if(server.clients.begin(), server.clients.end(), [](ClientInformation &c) {return c.disconnected; }), server.clients.end());


	server.pingTimer -= dt;
	if (server.pingTimer < 0)
	{
		server.pingTimer = 1.f;

		server.pingClock.restart();
		for (auto& client : server.clients)
		{
			sf::Uint8 pingPassword = rand() & 256;
			client.pingPassword = pingPassword;

			sf::Packet packet;
			packet << (sf::Uint8)Server::MESSAGE_TYPE::PING << pingPassword;
			send(client, packet);
		}

		Log::debug("Pings:");
		for (auto& client : server.clients)
		{
			Log::debug(std::to_string(client.id) + " - " + std::to_string(client.ping) + " ms");
		}
		Log::debug("");
	}

	server.gameTimer -= dt;
	if (server.gameTimer < 0)
	{
		server.gameTimer = 0.03;

		if (server.getGameInfo)
		{
			sf::Packet packet = server.getGameInfo();

			for (auto& client : server.clients)
			{
				sf::Packet p = packet;
				while (client.socket->send(p) == sf::Socket::Partial) {};
			}
		}
	}

}

void Server::onEvent(ClientInformation & client, sf::Packet packet)
{
	Server& server = get();
	sf::Uint8 t;
	packet >> t;
	auto type = (Server::MESSAGE_TYPE)t;

	if (type == Server::MESSAGE_TYPE::PING)
	{
		sf::Uint8 pingPassword;
		packet >> pingPassword;

		if (pingPassword == client.pingPassword)
		{
			int ping = server.pingClock.getElapsedTime().asMilliseconds();
			client.ping = ping;
		}
		else
		{
			client.ping = 999;
		}
	}
	else
	{
		if (server.onPacket)
		{
			server.onPacket(client,type,packet);
		}
	}
}

void Server::send(ClientInformation & client, sf::Packet packet)
{
	client.socket->send(packet);
}

void Server::send(sf::Packet packet)
{
	Server& server = get();
	for (auto& client : server.clients)
	{
		sf::Packet p = packet;
		while (client.socket->send(p) == sf::Socket::Partial) {};
	}
}

void Server::send(ClientInformation & client, MultiplayerMessage& message)
{
	sf::Packet packet;
	packet << (sf::Uint8)Server::MESSAGE_TYPE::MESSAGE;
	message.write(packet);
	Server::send(client, packet);
}

void Server::send(MultiplayerMessage& message)
{
	sf::Packet packet;
	packet << (sf::Uint8)Server::MESSAGE_TYPE::MESSAGE;
	message.write(packet);
	Server::send(packet);
}

bool Server::isServer()
{
	Server& server = get();

	return server.isserver;
}

int Server::getNewEntityId()
{
	Server& server = get();

	return server.lastEntityId++;
}

void Server::setGetInfo(std::function<sf::Packet()> f)
{
	Server& server = get();

	server.getGameInfo = f;
}

void Server::setOnNewPlayer(std::function<void(ClientInformation&)> f)
{
	Server& server = get();

	server.onNewPlayer = f;
}

void Server::setOnPacket(std::function<bool(ClientInformation&, Server::MESSAGE_TYPE, sf::Packet&)> f)
{
	Server& server = get();
	server.onPacket = f;
}

std::vector<ClientInformation>& Server::getClients()
{
	Server& server = get();
	return server.clients;
}

Server& Server::get()
{
	static Server s;
	return s;
}
