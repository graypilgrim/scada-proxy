#ifndef CLIENT_DATA_HPP_
#define CLIENT_DATA_HPP_

#include "Message.hpp"

#include <memory>
#include <mutex>

class ClientData
{
public:
	ClientData();

	void addRequest(std::unique_ptr<Message> request);
	void addResponse(std::unique_ptr<Message> response);
	void lockClient();
	void unlockClient();

private:
	std::unique_ptr<Message> request;
	std::unique_ptr<Message> response;
	std::unique_ptr<std::mutex> mutex;
};

#endif
