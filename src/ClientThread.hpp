#ifndef CLIENT_THREAD_HPP_
#define CLIENT_THREAD_HPP_

#include "Thread.hpp"

#include <string.h>

class ClientThread : public Thread
{
public:
	using Thread::Thread;

	void run() override;

private:
	static const int maxBufferSize = 1024;
};

#endif
