#ifndef CLIENT_THREAD_HPP_
#define CLIENT_THREAD_HPP_

#include "Thread.hpp"

#include <string.h>

class ClientThread : public Thread
{
public:
	ClientThread(const std::shared_ptr<Configuration> &configuration,
	             const std::shared_ptr<Buffer> &buffer,
		         const std::shared_ptr<Logger> &logger);

	void run() override;
	void setAddress(const std::string &address);

private:
	void receiveRequest();
	void sendResponse();

	std::shared_ptr<ClientData> data;
	std::string address;
};

#endif
