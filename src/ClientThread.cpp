#include "ClientThread.hpp"

void ClientThread::run() {
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
				std::cout << std::hex << static_cast<int>(messageBuffer[i]) << " ";
			std::cout << std::endl;
		}

	} while (returnValue != 0);

	close(socketDescriptor);
}
