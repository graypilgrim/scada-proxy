#include "Thread.hpp"

Thread::Thread(const std::shared_ptr<Configuration> &configuration,
               const std::shared_ptr<Buffer> &buffer,
               const std::shared_ptr<Logger> &logger)
	: configuration(configuration), buffer(buffer), logger(logger)
{}

void Thread::setSocketDescriptor(int socketDescriptor) {
	this->socketDescriptor = socketDescriptor;
}
