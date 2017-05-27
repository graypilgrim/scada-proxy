#include "Logger.hpp"

#include <iomanip>
#include <ctime>

Logger::Logger(const std::shared_ptr<Configuration> &configuration)
	: configuration(configuration)
{
	file.open(configuration->getLogFile(), std::ofstream::app);
}

void Logger::saveRequest(ClientData *clientData, const std::string &clientAddress)
{
	std::lock_guard<std::mutex> lock(mutex);

	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	file << std::put_time(&tm, "%H:%M:%S %d/%m/%Y ");
	file << clientData->getId() << " ";
	file << clientAddress << " ";
	file << configuration->getServerAddress() << "\n" << std::endl;
}

void Logger::saveResponse(ClientData *clientData, const std::string &clientAddress)
{
	std::lock_guard<std::mutex> lock(mutex);

	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	file << std::put_time(&tm, "%H:%M:%S %d/%m/%Y ");
	file << clientData->getId() << " ";
	file << clientAddress << " ";
	file << configuration->getServerAddress() << "\n" << std::endl;
}
