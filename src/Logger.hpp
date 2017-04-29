#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include "Message.hpp"

#include <string>

enum class LoggerVerbosity
{
	VERBOSE,
	NO_VERBOSE
};

class Logger
{
public:
	Logger(LoggerVerbosity verbosity);
	Logger(std::string fileName, LoggerVerbosity verbosity);
	void write(Message *message, bool status);
};

#endif
