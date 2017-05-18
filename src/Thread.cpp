#include "Thread.hpp"

Thread::Thread(const std::shared_ptr<Configuration> &configuration,
	           const std::shared_ptr<Buffer> &buffer)
	: configuration(configuration), buffer(buffer)
{}
