#ifndef CONNECTION_THREAD_HPP_
#define CONNECTION_THREAD_HPP_

#include "Thread.hpp"

class ConnectionThread : public Thread
{
public:
	ThreadStatus run() override;
};

#endif
