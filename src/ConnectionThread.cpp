#include "ConnectionThread.hpp"

#include "ClientThread.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void ConnectionThread::run() {
	socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (socketDescriptor < 0) {
		logger->saveError("ConnectionThread cannot open socket");
		throw std::runtime_error("ConnectionThread cannot open socket");
	}

	sockaddr_in socketData;
	socketData.sin_family = AF_INET;
	socketData.sin_addr.s_addr = INADDR_ANY;
	socketData.sin_port = htons(configuration->getClientPort());

	if (bind(socketDescriptor, (sockaddr *) &socketData, sizeof socketData) == -1) {
		logger->saveError("ConnectionThread cannot bind socket");
		throw std::runtime_error("ConnectionThread cannot bind socket");
	}

	listen(socketDescriptor, 5);

	do {
		auto clientSocketData = std::make_shared<sockaddr_in>();
		unsigned int clientSocketDataLength = sizeof(*clientSocketData);
		int clientSocketDescriptor = accept(socketDescriptor,(sockaddr *) clientSocketData.get(), &clientSocketDataLength);

		char dst[20];
		auto addr = inet_ntop(AF_INET, &clientSocketData->sin_addr, dst, 20);

		if (clientSocketDescriptor == -1 ) {
			logger->saveError("Client connection error");
			throw std::runtime_error("Client connection error");
		}

		auto clientThread = std::make_shared<ClientThread>(configuration, buffer, logger);
		clientThread->setSocketDescriptor(clientSocketDescriptor);
		clientThread->setAddress(addr);
		std::thread t(&ClientThread::run, clientThread);
		t.detach();

	} while(true);
}
