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

private:
	void receiveRequest();
	void sendResponse();

	static const int maxBufferSize = 1024;
	std::shared_ptr<ClientData> data;
};

#endif
