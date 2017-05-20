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

private:
	std::shared_ptr<Configuration> configuration;
};

#endif
