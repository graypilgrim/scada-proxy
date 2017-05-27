#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <iostream>
#include <memory>

class Message
{
public:
	Message(const std::shared_ptr<unsigned char> &content, uint32_t length);

	unsigned char *getContent();
	uint32_t getContentLength();

	bool isReady();
	uint32_t getOptionalDataLength();
	std::string getCommand();
	std::string getSubcommand();
	std::string getData();
	std::string responseStatus();

	static const uint32_t obligatoryDataSize = 9;
	static const uint32_t optionalDataSize = 65535;
	static const uint32_t maxMessageSize = obligatoryDataSize + optionalDataSize;

private:
	std::string printTwoDigitHex(unsigned char c);

	std::shared_ptr<unsigned char> content;
	uint32_t length;
};

#endif
