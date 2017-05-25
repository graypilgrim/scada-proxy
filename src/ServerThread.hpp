#ifndef SERVER_THREAD_HPP_
#define SERVER_THREAD_HPP_

#include "Thread.hpp"

class ServerThread : public Thread
{
public:
	using Thread::Thread;

	void run() override;

private:
	void connectToServer();
};

#endif
