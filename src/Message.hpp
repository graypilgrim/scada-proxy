#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <iostream>
#include <memory>

class Message
{
public:
	Message(const std::shared_ptr<char> &content, uint32_t length);

	char *getContent();
	uint32_t getContentLength();

	bool isReady();
	int getOptionalDataLength();

	static const uint32_t obligatoryDataSize = 9;
	static const uint32_t optionalDataSize = 65535;
	static const uint32_t maxMessageSize = obligatoryDataSize + optionalDataSize;

private:
	std::shared_ptr<char> content;
	uint32_t length;
};

#endif
