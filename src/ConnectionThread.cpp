#include "ConnectionThread.hpp"

#include "ClientThread.hpp"

void ConnectionThread::run() {
	int socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (socketDescriptor < 0)
		throw std::runtime_error("Connection thread cannot open socket");

	sockaddr_in socketData;
	socketData.sin_family = AF_INET;
	socketData.sin_addr.s_addr = INADDR_ANY;
	socketData.sin_port = htons(configuration->getServerPort());

	if (bind(socketDescriptor, (sockaddr *) &socketData, sizeof socketData) == -1)
		throw std::runtime_error("Connection thread cannot bind socket");

	listen(socketDescriptor, 5);

	do {
		int clientSocketDescriptor = accept(socketDescriptor,(sockaddr *) 0,(socklen_t *) 0);

		if (clientSocketDescriptor == -1 )
			throw std::runtime_error("Client connection error");

		auto clientThread = std::make_shared<ClientThread>(configuration, buffer, logger);
		clientThread->setSocketDescriptor(clientSocketDescriptor);
		std::thread t(&ClientThread::run, clientThread);
		t.detach();

	} while(true);


}
