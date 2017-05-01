#include "Configuration.hpp"

#include <sstream>

Configuration::Configuration() {
	serverAddress = "127.0.0.0";
	serverPort = "1280";
	clientPort = "1299";
	logFile = "log.txt";
	maxBufferSize = "0";
	verbosity = LoggerVerbosity::VERBOSE;
}

Configuration::Configuration(std::ifstream &data) {

}
