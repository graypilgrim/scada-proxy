#ifndef CLIENT_DATA_HPP_
#define CLIENT_DATA_HPP_

#include "Message.hpp"

#include <memory>
#include <mutex>

class ClientData
{
public:
	ClientData();

	void addRequest(const std::shared_ptr<Message> &request);
	std::shared_ptr<Message> getRequest();
	void addResponse(const std::shared_ptr<Message> &response);
	std::shared_ptr<Message> getResponse();
	void lockClient();
	void unlockClient();
	uint64_t getId();

private:
	std::shared_ptr<Message> request;
	std::shared_ptr<Message> response;
	std::mutex mutex;
	uint64_t id;

	static uint64_t counter;
};

#endif
