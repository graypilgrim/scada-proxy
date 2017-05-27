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

	void saveMessage(const std::string &message);

	void saveRequest(ClientData *clientData, const std::string &clientAddress);
	void saveResponse(ClientData *clientData, const std::string &clientAddress);

	void saveInfo(const std::string &infoMessage);
	void saveError(const std::string &errorMessage);
	void saveWarning(const std::string &warningMessage);

private:
	std::shared_ptr<Configuration> configuration;
	std::ofstream file;
	std::mutex mutex;
};

#endif
