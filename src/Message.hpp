#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <iostream>
#include <memory>

class Message
{
public:
	Message(const std::shared_ptr<char> &buffer);

	bool isReady();

	static const uint32_t maxMessageSize = 65535 + 7;

private:
	std::shared_ptr<char> buffer;
};

#endif
