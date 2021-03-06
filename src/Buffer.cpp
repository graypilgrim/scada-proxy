#include "Buffer.hpp"

BufferCounter::BufferCounter(uint32_t maxQueueSize)
	: count(0), maxCount(maxQueueSize)
{}

void BufferCounter::up()
{
	std::unique_lock<std::mutex> lock(mtx);

	while (count == maxCount)
		cv.wait(lock);


	++count;
	cv.notify_one();
}

void BufferCounter::down()
{
	std::unique_lock<std::mutex> lock(mtx);
	--count;
	cv.notify_one();
}

Buffer::Buffer(uint32_t maxQueueSize)
	: bufferCounter(std::make_shared<BufferCounter>(maxQueueSize))
{
	threadMutex.lock();
	overloadMutex.lock();
}

void Buffer::pushBack(const std::shared_ptr<ClientData> &data) {
	bufferCounter->up();
	std::lock_guard<std::mutex> lock(accessMutex);

	queue.emplace_back(data);

	if (queue.size() == 1)
		threadMutex.unlock();
}

std::shared_ptr<ClientData> Buffer::front() {
	std::lock_guard<std::mutex> lock(accessMutex);
	return queue.front();
}

void Buffer::popFront() {
	std::lock_guard<std::mutex> lock(accessMutex);
	queue.pop_front();
	bufferCounter->down();
}

size_t Buffer::size() {
	std::lock_guard<std::mutex> lock(accessMutex);
	return queue.size();
}

bool Buffer::empty() {
	std::lock_guard<std::mutex> lock(accessMutex);
	return queue.empty();
}

void Buffer::lockServerThread() {
	threadMutex.lock();
}
