#include "ClientThread.hpp"

void ClientThread::run() {
	std::cout << "I will serve the client" << std::endl;
	while(true) {}
	close(socketDescriptor);
}
