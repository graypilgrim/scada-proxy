#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include "ClientData.hpp"
#include "Configuration.hpp"

#include <string>
#include <memory>
#include <mutex>

class Logger
{
public:
	Logger(const std::shared_ptr<Configuration> &configuration);
	~Logger();

	void saveRequest(ClientData *clientData, const std::string &clientAddress);
	void saveResponse(ClientData *clientData, const std::string &clientAddress);

private:
	std::shared_ptr<Configuration> configuration;
	std::ofstream file;
	std::mutex mutex;
};

#endif
