#include "ServerThread.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void ServerThread::run()
{
	std::cout << __FILE__ << " " <<__FUNCTION__ << ": " << "i was started" << std::endl;

	connectToServer();

	while (true) {
		std::cout << __FILE__ << __FUNCTION__ << ": " << "i am running" << std::endl;

		sendRequest();
		receiveResponse();
	}
}

void ServerThread::connectToServer()
{
	socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);

 	if (socketDescriptor < 0)
 		throw std::runtime_error("ServerThread cannot open socket");

	sockaddr_in socketData;
	socketData.sin_family = AF_INET;
	inet_aton(configuration->getServerAddress(), &socketData.sin_addr);
	socketData.sin_port = htons(configuration->getServerPort());

   if (connect(socketDescriptor, (struct sockaddr*)&socketData, sizeof(socketData)) < 0)
		throw std::runtime_error("Server connection error");

}

void ServerThread::sendRequest()
{
	if (buffer->empty())
		buffer->lockServerThread();

	std::cout << __FILE__ << __FUNCTION__ << ": " << "i am sending" << std::endl;

	auto message = buffer->front()->getRequest();
	auto sentBytes = write(socketDescriptor, message->getContent(), message->getContentLength());

	if (sentBytes < message->getContentLength())
		std::cerr << "Sent less data than expected" << std::endl;

	std::cout << __FILE__ << __FUNCTION__ << ": " << "i sent" << std::endl;
}

void ServerThread::receiveResponse()
{
	auto data = buffer->front();

	readFromSocket(
		[&](const std::shared_ptr<Message> &m){
			logger->saveResponse(m.get());
			data->addResponse(m);
			std::cout << std::endl;
		});

	data->unlockClient();
	buffer->popFront();
}
