#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include "CommunicationData.hpp"

#include <mutex>
#include <queue>
#include <memory>

class Buffer
{
public:
	void pushBack(std::shared_ptr<CommunicationData> data);
	void popFront();
	bool empty();

private:
	std::queue<std::shared_ptr<CommunicationData> > queue;
	std::mutex mutex;
};

#endif
