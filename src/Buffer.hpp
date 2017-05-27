#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include "ClientData.hpp"
#include "Configuration.hpp"

#include <mutex>
#include <condition_variable>
#include <list>
#include <memory>

class BufferCounter {
public:
	BufferCounter(uint32_t maxQueueSize);
	inline void up();
	inline void down();

private:
	std::mutex mtx;
	std::condition_variable cv;
	uint32_t count;
	uint32_t maxCount;
};

class Buffer
{
public:
	Buffer(uint32_t maxQueueSize);

	void pushBack(const std::shared_ptr<ClientData> &data);
	std::shared_ptr<ClientData> front();
	void popFront();
	size_t size();
	bool empty();

	void lockServerThread();

private:
	std::list<std::shared_ptr<ClientData> > queue;
	std::mutex accessMutex;
	std::mutex overloadMutex;
	std::mutex threadMutex;
	std::shared_ptr<BufferCounter> bufferCounter;
};

#endif
