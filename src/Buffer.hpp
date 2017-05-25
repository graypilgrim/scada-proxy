#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include "ClientData.hpp"

#include <mutex>
#include <queue>
#include <memory>

class Buffer
{
public:
	Buffer();

	void pushBack(std::shared_ptr<ClientData> data);
	std::shared_ptr<ClientData> front();
	void popFront();
	bool empty();

	void lockServerThread();

private:
	std::queue<std::shared_ptr<ClientData> > queue;
	std::mutex accessMutex;
	std::mutex threadMutex;
};

#endif
