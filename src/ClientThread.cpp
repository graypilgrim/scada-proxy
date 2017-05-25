#include "ClientThread.hpp"

#include <iomanip>

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
	int readSigns;

	std::shared_ptr<char> cachedMessageBuffer = nullptr;
	bool concatenate = false;

	do {
		std::shared_ptr<char> messageBuffer(new char[Message::maxMessageSize]);
		memset(messageBuffer.get(), 0, Message::maxMessageSize);
		readSigns = read(socketDescriptor, messageBuffer.get(), Message::maxMessageSize);

		switch (readSigns)
		{
		case -1:
			throw std::runtime_error("reading data error");

		case 0:
			break;

		default:
			if (concatenate) {
				memcpy(cachedMessageBuffer.get(), messageBuffer.get(), readSigns);
				messageBuffer = cachedMessageBuffer;
			}

			auto message = std::unique_ptr<Message>(new Message(messageBuffer, readSigns));

			if (message->isReady()) {
				logger->saveRequest(message.get());
				data->addRequest(std::move(message));

				for (auto i = 0; i < readSigns; ++i)
					std::cout << std::hex << "0x"  << static_cast<int>(messageBuffer.get()[i]) << " ";
				std::cout << std::endl;

				concatenate = false;

				break;
			}

			cachedMessageBuffer = messageBuffer;
			concatenate = true;
		}

	} while (readSigns != 0);
}

void ClientThread::sendResponse()
{

}
