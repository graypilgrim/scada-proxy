#include "Configuration.hpp"

#include <sstream>

Configuration::Configuration()
{
	information.resize(ConfigurationField::Count);
	information[ConfigurationField::SERVER_ADDRESS] = "127.0.0.0";
	information[ConfigurationField::SERVER_PORT] = "1280";
	information[ConfigurationField::CLIENT_PORT] = "1299";
	information[ConfigurationField::LOG_FILE] = "log.txt";
	information[ConfigurationField::MAX_BUFFER_SIZE] = "0";
	verbose = true;
}

Configuration::Configuration(std::ifstream &data) {
}

std::string Configuration::getServerAddress() const {
	return information[ConfigurationField::SERVER_ADDRESS];
}

int Configuration::getServerPort() const {
	return std::stoi(information[ConfigurationField::SERVER_PORT]);
}

int Configuration::getClientPort() const {
	return std::stoi(information[ConfigurationField::CLIENT_PORT]);
}

std::string Configuration::getLogFile() const {
	return information[ConfigurationField::LOG_FILE];
}

std::string Configuration::getMaxBufferSize() const {
	return information[ConfigurationField::MAX_BUFFER_SIZE];
}

bool Configuration::isVerbose() const {
	return verbose;
}
