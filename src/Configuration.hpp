#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

#include <fstream>
#include <string>
#include <vector>

enum ConfigurationField
{
	SERVER_ADDRESS,
	SERVER_PORT,
	CLIENT_PORT,
	LOG_FILE,
	MAX_BUFFER_SIZE,
	Count
};

class Configuration
{
public:
	Configuration();
	Configuration(std::ifstream &data);

	std::string getServerAddress() const;
	int getServerPort() const;
	int getClientPort() const;
	std::string getLogFile() const;
	std::string getMaxBufferSize() const;
	bool isVerbose() const;

private:
	std::vector<std::string> information;
	// std::string serverAddress;
	// std::string serverPort;
	// std::string clientPort;
	// std::string logFile;
	// std::string maxBufferSize;
	bool verbose;
};

#endif
