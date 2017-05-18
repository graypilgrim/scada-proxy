#include "ClientThread.hpp"

void ClientThread::run(int clientSocketDescriptor) {
	std::cout << "I will serve the client" << std::endl;
	while(true) {}
	close(clientSocketDescriptor);
}
