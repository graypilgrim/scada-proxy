#include <iostream>

#include "Buffer.hpp"
#include "Configuration.hpp"
#include "ConnectionThread.hpp"

#include <memory>
#include <thread>

int main() {
	auto configuration = std::make_shared<Configuration>();
	auto buffer = std::make_shared<Buffer>();
	auto logger = std::make_shared<Logger>(configuration);
	auto connectionThread = std::make_shared<ConnectionThread>(configuration, buffer, logger);
	std::thread t(&ConnectionThread::run, *connectionThread);
	t.join();
}
