#include <iostream>

#include "Buffer.hpp"
#include "Configuration.hpp"
#include "ConnectionThread.hpp"

#include <memory>
#include <thread>

int main() {
	auto buffer = std::make_shared<Buffer>();
	auto configuration = std::make_shared<Configuration>();
	auto connectionThread = std::make_shared<ConnectionThread>(configuration, buffer);
	std::thread t(&ConnectionThread::run, *connectionThread);
	t.join();
}
