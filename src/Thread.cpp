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

void Thread::readFromSocket(const std::function<void(const std::shared_ptr<Message>&)> &loggingAndDataFilling)
{
    std::cout << __FILE__ << __FUNCTION__ << ": " << "up" << std::endl;
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

			auto message = std::make_shared<Message>(messageBuffer, readSigns);

			if (!message->isReady()) {
				cachedMessageBuffer = messageBuffer;
				concatenate = true;
				continue;
			}

            loggingAndDataFilling(message);

			for (auto i = 0; i < readSigns; ++i)
				std::cout << std::hex << "0x"  << static_cast<int>(messageBuffer.get()[i]) << " ";
			std::cout << std::endl;

			break;
		}

	} while (concatenate);

    std::cout << __FILE__ << __FUNCTION__ << ": " << "down" << std::endl;
}
