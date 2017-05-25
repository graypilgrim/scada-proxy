#include "ServerThread.hpp"

void ServerThread::run()
{
	std::cout << __FILE__ << " " <<__FUNCTION__ << ": " << "i was started" << std::endl;

	while (true) {
		if (buffer->empty())
			buffer->lockServerThread();

		std::cout << __FILE__ << __FUNCTION__ << ": " << "i am running" << std::endl;

		if (!buffer->empty())
			buffer->popFront();

	}
}
