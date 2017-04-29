#ifndef COMMUNICATION_DATA_
#define COMMUNICATION_DATA_

#include "Message.hpp"

#include <memory>
#include <mutex>

class CommunicationData
{
public:
	void addRequest(std::unique_ptr<Message> request);
	void addResponse(std::unique_ptr<Message> response);
	void unlock();

private:
	std::unique_ptr<Message> request;
	std::unique_ptr<Message> response;
	std::mutex mutex;
};

#endif
