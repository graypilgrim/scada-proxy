#include "Message.hpp"

#include <cstring>

Message::Message(const std::shared_ptr<char> &content, uint32_t length)
	: content(content), length(length)
{}

char* Message::getContent()
{
	return content.get();
}

uint32_t Message::getContentLength()
{
	return length;
}

bool Message::isReady()
{
	if (content == nullptr)
		throw std::runtime_error("Empty content provided");

	std::cout << "DEBUG: " << __FUNCTION__ << "length: " << length << std::endl;

	if (obligatoryDataSize + getOptionalDataLength() != length)
		return false;

	return true;
}

int Message::getOptionalDataLength()
{
	return content.get()[7] + (content.get()[8] << 4) ;
}
