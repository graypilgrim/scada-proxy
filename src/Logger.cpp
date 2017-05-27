#include "Logger.hpp"

Logger::Logger(const std::shared_ptr<Configuration> &configuration)
	: configuration(configuration)
{}

void Logger::saveRequest(Message *message, const std::string &address)
{

}

void Logger::saveResponse(Message *message)
{

}
