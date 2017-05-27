#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include "Message.hpp"
#include "Configuration.hpp"

#include <string>
#include <memory>

class Logger
{
public:
	Logger(const std::shared_ptr<Configuration> &configuration);

	void saveRequest(Message *message, const std::string &address);
	void saveResponse(Message *message);

private:
	std::shared_ptr<Configuration> configuration;
};

#endif
