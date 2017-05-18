#ifndef CLIENT_THREAD_HPP_
#define CLIENT_THREAD_HPP_

#include "Thread.hpp"

class ClientThread : public Thread
{
public:
	using Thread::Thread;
	
	void run() override;
};

#endif
