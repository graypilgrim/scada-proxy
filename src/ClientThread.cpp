#include "ClientThread.hpp"

ClientThread::ClientThread(const std::shared_ptr<Configuration> &configuration,
			 const std::shared_ptr<Buffer> &buffer,
			 const std::shared_ptr<Logger> &logger)
	: Thread(configuration, buffer, logger), data(std::make_shared<ClientData>())
{}

void ClientThread::run() {
	receiveRequest();
	close(socketDescriptor);
}

void ClientThread::receiveRequest()
{
	//TODO: check and make message
	unsigned char messageBuffer[maxBufferSize];
	int returnValue;

	do {
		memset(messageBuffer, 0, sizeof messageBuffer);
		returnValue = read(socketDescriptor, messageBuffer, maxBufferSize);

		switch (returnValue)
		{
		case -1:
			throw std::runtime_error("reading data error");

		case 0:
			break;

		default:
			for (auto i = 0; i < returnValue; ++i)
				std::cout << std::hex << "0x" << static_cast<int>(messageBuffer[i]) << " ";
			std::cout << std::endl;
		}

	} while (returnValue != 0);
}

void ClientThread::sendResponse()
{

}
