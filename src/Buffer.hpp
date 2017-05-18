#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include "ClientData.hpp"

#include <mutex>
#include <queue>
#include <memory>

class Buffer
{
public:
	void pushBack(std::shared_ptr<ClientData> data);
	void popFront();
	bool empty();

private:
	std::queue<std::shared_ptr<ClientData> > queue;
	std::mutex mutex;
};

#endif
