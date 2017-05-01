#ifndef CLIENT_THREAD_HPP_
#define CLIENT_THREAD_HPP_

#include "Thread.hpp"

class ClientThread : public Thread
{
public:
	ThreadStatus run() override;
};

#endif
