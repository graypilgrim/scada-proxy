#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

class Configuration
{
public:
	Configuration();
	Configuration(std::ifstream &data);

	const char *getServerAddress() const;
	int getServerPort() const;
	int getClientPort() const;
	std::string getLogFile() const;
	uint64_t getMaxBufferSize() const;

private:
	void loadDefaultConfiguration();

	std::unordered_map<std::string, std::string> information;
};

#endif
