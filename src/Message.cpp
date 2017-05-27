#include "Message.hpp"

#include <cstring>
#include <sstream>
#include <iomanip>

Message::Message(const std::shared_ptr<unsigned char> &content, uint32_t length)
	: content(content), length(length)
{}

unsigned char* Message::getContent()
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

	if (obligatoryDataSize + getOptionalDataLength() != length)
		return false;

	return true;
}

uint32_t Message::getOptionalDataLength()
{
	return content.get()[7] + (content.get()[8] << 4);
}

std::string Message::getCommand()
{
	if (obligatoryDataSize + getOptionalDataLength() < 12)
		return "";

	return printTwoDigitHex(content.get()[12]) + printTwoDigitHex(content.get()[11]);
}

std::string Message::getSubcommand()
{
	if (obligatoryDataSize + getOptionalDataLength() < 14)
		return "";

	return printTwoDigitHex(content.get()[14]) + printTwoDigitHex(content.get()[13]);
}

std::string Message::getData()
{
	if (length < 15)
		return "";

	std::stringstream ss;

	for (uint32_t i = 15; i < length; ++i)
		ss << printTwoDigitHex(content.get()[i]);

	return ss.str();
}

std::string Message::printTwoDigitHex(unsigned char c)
{
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<uint>(c);

	return ss.str();
}

std::string Message::responseStatus()
{
	if (length < 10)
		return "";

	auto status = printTwoDigitHex(content.get()[10]) + printTwoDigitHex(content.get()[9]);

	if (status == "0000")
		return "SUCCESS";

	return "ERROR" + status;
}
