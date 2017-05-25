#include "Message.hpp"

#include <cstring>

Message::Message(const std::shared_ptr<char> &buffer, uint32_t length)
	: buffer(buffer), length(length)
{}

bool Message::isReady()
{
	if (buffer == nullptr)
		throw std::runtime_error("Empty buffer provided");

	std::cout << "DEBUG: " << __FUNCTION__ << "length: " << length << std::endl;

	if (obligatoryDataSize + getOptionalDataLength() != length)
		return false;

	return true;
}

int Message::getOptionalDataLength()
{
	return buffer.get()[7] + (buffer.get()[8] << 4) ;
}
