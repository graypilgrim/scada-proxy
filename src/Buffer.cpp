#include "Buffer.hpp"

Buffer::Buffer()
{
	threadMutex.lock();
}

void Buffer::pushBack(std::shared_ptr<ClientData> data) {
	std::cout << __FILE__ << " " <<__FUNCTION__ << ": " << "up " << std::endl;
	accessMutex.lock();
	queue.emplace(data);
	accessMutex.unlock();
	threadMutex.unlock();
	std::cout << __FILE__ << " " <<__FUNCTION__ << ": " << "down " << std::endl;
}

std::shared_ptr<ClientData> Buffer::front() {
	return queue.front();
}

void Buffer::popFront() {
	accessMutex.lock();
	queue.pop();

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
