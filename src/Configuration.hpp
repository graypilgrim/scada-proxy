#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

#include "Logger.hpp"

#include <fstream>
#include <string>
#include <unordered_map>

class Configuration
{
public:
	Configuration();
	Configuration(std::ifstream &data);

private:
	std::string serverAddress;
	std::string serverPort;
	std::string clientPort;
	std::string logFile;
	std::string maxBufferSize;
	LoggerVerbosity verbosity;
};

#endif
