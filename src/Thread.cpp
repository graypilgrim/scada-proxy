#include "Thread.hpp"

#include <cstring>

Thread::Thread(const std::shared_ptr<Configuration> &configuration,
               const std::shared_ptr<Buffer> &buffer,
               const std::shared_ptr<Logger> &logger)
	: configuration(configuration), buffer(buffer), logger(logger)
{}

void Thread::setSocketDescriptor(int socketDescriptor)
{
	this->socketDescriptor = socketDescriptor;
}

std::shared_ptr<Message> Thread::readFromSocket()
{
    int readSigns;

	std::shared_ptr<unsigned char> cachedMessageBuffer = nullptr;
	bool concatenate = false;


	do {
		std::shared_ptr<unsigned char> messageBuffer(new unsigned char[Message::maxMessageSize]);
		memset(messageBuffer.get(), 0, Message::maxMessageSize);
		readSigns = read(socketDescriptor, messageBuffer.get(), Message::maxMessageSize);

		switch (readSigns)
		{
		case -1:
			logger->saveError("Reading data error");
			throw std::runtime_error("reading data error");

		case 0:
			return nullptr;

		default:
			if (concatenate) {
				memcpy(cachedMessageBuffer.get(), messageBuffer.get(), readSigns);
				messageBuffer = cachedMessageBuffer;
			}

			auto message = std::make_shared<Message>(messageBuffer, readSigns);

			if (!message->isReady()) {
				cachedMessageBuffer = messageBuffer;
				concatenate = true;
				continue;
			}

            return message;

			break;
		}

	} while (concatenate);

    return nullptr;
}
