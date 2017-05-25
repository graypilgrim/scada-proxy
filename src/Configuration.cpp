#include "Configuration.hpp"

#include <sstream>
#include <algorithm>

Configuration::Configuration()
{
	information["SERVER_ADDRESS"] = "127.0.0.0";
	information["SERVER_PORT"] = "1280";
	information["CLIENT_PORT"] = "1299";
	information["LOG_FILE"] = "log.txt";
	information["MAX_BUFFER_SIZE"] = "0";
	information["VERBOSITY"] = "VERBOSE";
}

Configuration::Configuration(std::ifstream &data) {
	std::string line;

	while(std::getline(data, line)) {
		line.erase(std::remove_if( line.begin(), line.end(),
     [](char c){ return (c =='\r' || c =='\t' || c == ' ' || c == '\n');}), line.end() );
		auto equalSign = line.find("=");
		if (equalSign == static_cast<size_t>(-1))
			throw std::runtime_error("Invalid config file");

		auto key = line.substr(0, equalSign);
		auto value = line.substr(equalSign+1);
		information[key] = value;
	}
}

std::string Configuration::getServerAddress() const {
	return information.at("SERVER_ADDRESS");
}

int Configuration::getServerPort() const {
	return std::stoi(information.at("SERVER_PORT"));
}

int Configuration::getClientPort() const {
	return std::stoi(information.at("CLIENT_PORT"));
}

std::string Configuration::getLogFile() const {
	return information.at("LOG_FILE");
}

std::string Configuration::getMaxBufferSize() const {
	return information.at("MAX_BUFFER_SIZE");
}

bool Configuration::isVerbose() const {
	return information.at("VERBOSITY") == "VERBOSE";
}
