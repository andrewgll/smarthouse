#include "server.h"
#include "handlers/Factory.h"

#include <iostream>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/ServerSocketImpl.h>
#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"
#include "Poco/Util/Application.h"

using namespace Poco::Util;

namespace
{

class ServerSocketImpl: public Poco::Net::ServerSocketImpl
{
public:
	using Poco::Net::SocketImpl::init;
};

class Socket: public Poco::Net::Socket
{
public:
	Socket(const std::string & address)
		: Poco::Net::Socket(new ServerSocketImpl())
	{
		const Poco::Net::SocketAddress socket_address(address);
		ServerSocketImpl * socket = static_cast<ServerSocketImpl*>(impl());
		socket->init(socket_address.af());
		socket->setReuseAddress(true);
		socket->setReusePort(false);
		socket->bind(socket_address, false);
		socket->listen();
	}
};

}

int Server::main(const std::vector<std::string>& args)
{
	Poco::Net::HTTPServerParams::Ptr parameters = new Poco::Net::HTTPServerParams();
	parameters->setTimeout(10000);
	parameters->setMaxQueued(100);
	parameters->setMaxThreads(4);

	const Poco::Net::ServerSocket socket(Socket("localhost:8080"));

	Poco::Net::HTTPServer server(new handlers::Factory(), socket, parameters);
	server.start();
	logger().information("HTTP Server started on port 8080.");
	waitForTerminationRequest();
	logger().information("Closing server...");
	server.stop();
	server.stopAll();
	return Application::EXIT_OK;
}


