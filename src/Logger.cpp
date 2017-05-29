#include "Logger.hpp"

#include <iomanip>
#include <ctime>

Logger::Logger(const std::shared_ptr<Configuration> &configuration)
	: configuration(configuration)
{
	file.open(configuration->getLogFile(), std::ofstream::app);
}

void Logger::saveMessage(const std::string &logMessage)
{
	std::lock_guard<std::mutex> lock(mutex);

	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	file << std::put_time(&tm, "%H:%M:%S %d/%m/%Y ");
	file << logMessage << std:endl;
}

void Logger::saveRequest(ClientData *clientData, const std::string &clientAddress)
{
	std::string logMessage = clientData->getId() + " "
						+ clientAddress + " "
						+ configuration->getServerAddress() + " "
						+ clientData->getRequest()->getCommand() + " "
						+ clientData->getRequest()->getSubcommand() + " "
						+ clientData->getRequest()->getData();

	saveMessage(logMessage);
}

void Logger::saveResponse(ClientData *clientData, const std::string &clientAddress)
{
	std::string logMessage = clientData->getId() + " "
						+ clientAddress + " "
						+ configuration->getServerAddress() + " "
						+ clientData->getResponse()->responseStatus();

	saveMessage(logMessage);
}

void Logger::saveInfo(const std::string &infoMessage)
{
	std::string logMessage = "INFO: " + infoMessage;

	saveMessage(logMessage);
}

void Logger::saveError(const std::string &errorMessage)
{
	std::string logMessage = "ERROR: " + errorMessage;

	saveMessage(logMessage);
}

void Logger::saveWarning(const std::string &warningMessage)
{
	std::string logMessage = "WARNING: " + warningMessage;

	saveMessage(logMessage);

	std::cerr << warningMessage << std::endl;
}
