#include <iostream>

#include "Buffer.hpp"
#include "Configuration.hpp"
#include "ConnectionThread.hpp"
#include "ServerThread.hpp"

#include <memory>
#include <thread>

int main(int argc, char **argv) {
	std::shared_ptr<Configuration> configuration;

	if (argc > 1) {
		std::ifstream confFile(argv[1], std::ifstream::in);
		if (confFile.good())
			configuration = std::make_shared<Configuration>(confFile);
		else
			throw std::runtime_error("No such file");
	} else
		configuration = std::make_shared<Configuration>();

	auto buffer = std::make_shared<Buffer>();
	auto logger = std::make_shared<Logger>(configuration);

	auto connectionThread = std::make_shared<ConnectionThread>(configuration, buffer, logger);
	std::thread conn(&ConnectionThread::run, *connectionThread);

	auto serverThread = std::make_shared<ServerThread>(configuration, buffer, logger);
	std::thread serv(&ServerThread::run, *serverThread);

	conn.join();
	serv.join();
}
