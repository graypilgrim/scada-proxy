#include "Configuration.hpp"

#include <sstream>
#include <algorithm>
#include <iostream>

Configuration::Configuration()
{
	loadDefaultConfiguration();
}

Configuration::Configuration(std::ifstream &data) {
	loadDefaultConfiguration();

	std::string line;

	while(std::getline(data, line)) {
		line.erase(std::remove_if( line.begin(), line.end(), [](char c){ return (c =='\r' || c =='\t' || c == ' ' || c == '\n');}), line.end() );
		auto equalSign = line.find("=");
		if (equalSign == static_cast<size_t>(-1))
			throw std::runtime_error("Invalid config file");

		auto key = line.substr(0, equalSign);
		auto value = line.substr(equalSign+1);
		information[key] = value;
	}
}

const char *Configuration::getServerAddress() const {
	return information.at("SERVER_ADDRESS").c_str();
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

void Configuration::loadDefaultConfiguration()
{
	information["SERVER_ADDRESS"] = "127.0.0.1";
	information["SERVER_PORT"] = "1281";
	information["CLIENT_PORT"] = "1280";
	information["LOG_FILE"] = "log.txt";
	information["MAX_BUFFER_SIZE"] = "0";
}
