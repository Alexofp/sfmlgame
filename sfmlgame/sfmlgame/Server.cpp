#include "Server.h"
#include "Log.h"


Server::Server()
{
	socketId = 0;
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
		socket->setBlocking(false);
		clientInfo.socket = socket;
		server.clients.push_back(clientInfo);

		sf::Packet packet;
		packet << (sf::Uint8)Server::MESSAGE_TYPE::SET_CLIENT_ID << (sf::Uint32)server.socketId;
		clientInfo.socket->send(packet);

		server.socketId++;
	}
}

Server& Server::get()
{
	static Server s;
	return s;
}
