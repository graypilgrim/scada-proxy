#ifndef SERVER_THREAD_HPP_
#define SERVER_THREAD_HPP_

#include "Thread.hpp"

class ServerThread : public Thread
{
public:
	ThreadStatus run() override;
};

#endif
