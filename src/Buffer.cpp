#include "Buffer.hpp"

Buffer::Buffer()
{
	threadMutex.lock();
}

void Buffer::pushBack(const std::shared_ptr<ClientData> &data) {
	std::cout << __FILE__ << " " <<__FUNCTION__ << ": " << "up " << std::endl;
	accessMutex.lock();
	queue.emplace_back(data);
	auto unlockThread = queue.size() == 1;
	accessMutex.unlock();

	if (unlockThread)
		threadMutex.unlock();
	std::cout << __FILE__ << " " <<__FUNCTION__ << ": " << "down " << std::endl;
}

std::shared_ptr<ClientData> Buffer::front() {
	accessMutex.lock();
	auto ret = queue.front();
	accessMutex.unlock();
	return ret;
}

void Buffer::popFront() {
	accessMutex.lock();
	queue.pop_front();
	accessMutex.unlock();
}

bool Buffer::empty() {
	accessMutex.lock();
	auto res = queue.size();
	std::cout << __FILE__ << " " <<__FUNCTION__ << ": " << "size " << queue.size() << std::endl;
	accessMutex.unlock();

	return res == 0;
}

void Buffer::lockServerThread() {
	std::cout << __FILE__ << " " <<__FUNCTION__ << ": " << "locking" << std::endl;
	threadMutex.lock();
}
