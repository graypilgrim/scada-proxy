#include "ClientThread.hpp"

#include <iomanip>

ClientThread::ClientThread(const std::shared_ptr<Configuration> &configuration,
			 const std::shared_ptr<Buffer> &buffer,
			 const std::shared_ptr<Logger> &logger)
	: Thread(configuration, buffer, logger), data(std::make_shared<ClientData>())
{}

void ClientThread::run() {
	receiveRequest();
	buffer->pushBack(data);
	std::cout << __FILE__ << __FUNCTION__ << ": " << "i am waiting for response" << std::endl;
	std::cout << __FILE__ << __FUNCTION__ << ": " << "locked" << std::endl;
	data->lockClient();
	std::cout << __FILE__ << __FUNCTION__ << ": " << "unlocked" << std::endl;
	sendResponse();
	std::cout << __FILE__ << __FUNCTION__ << ": " << "i finished connection" << std::endl;
	close(socketDescriptor);
}

void ClientThread::receiveRequest()
{
	readFromSocket(
		[this](const std::shared_ptr<Message> &m){
			logger->saveRequest(m.get());
			data->addRequest(m);
		});
}

void ClientThread::sendResponse()
{
	auto message = data->getResponse();
	auto sentBytes = write(socketDescriptor, message->getContent(), message->getContentLength());

	if (sentBytes < message->getContentLength())
		std::cerr << "Sent less data than expected" << std::endl;
}
