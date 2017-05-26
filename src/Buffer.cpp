#include "Buffer.hpp"

Buffer::Buffer()
{
	threadMutex.lock();
}

void Buffer::pushBack(const std::shared_ptr<ClientData> &data) {
	std::cout << __FILE__ << " " <<__FUNCTION__ << ": " << "up " << std::endl;
	std::lock_guard<std::mutex> lock(accessMutex);
	queue.emplace_back(data);
	if (queue.size() == 1)
		threadMutex.unlock();
	std::cout << __FILE__ << " " <<__FUNCTION__ << ": " << "down " << std::endl;
}

std::shared_ptr<ClientData> Buffer::front() {
	std::lock_guard<std::mutex> lock(accessMutex);
	return queue.front();
}

void Buffer::popFront() {
	std::lock_guard<std::mutex> lock(accessMutex);
	queue.pop_front();
}

bool Buffer::empty() {
	std::lock_guard<std::mutex> lock(accessMutex);
	return queue.empty();
}

void Buffer::lockServerThread() {
	std::cout << __FILE__ << " " <<__FUNCTION__ << ": " << "locking" << std::endl;
	threadMutex.lock();
}
