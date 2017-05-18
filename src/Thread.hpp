#ifndef THREAD_HPP_
#define THREAD_HPP_

#include "Configuration.hpp"
#include "Buffer.hpp"

#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <memory>
#include <thread>
#include <iostream>

class Thread
{
public:
	Thread(const std::shared_ptr<Configuration> &configuration,
	       const std::shared_ptr<Buffer> &buffer);
	virtual ~Thread(){};
	virtual void run() = 0;

protected:
	std::shared_ptr<Configuration> configuration;
	std::shared_ptr<Buffer> buffer;
};

#endif
