#include "Buffer.hpp"

void Buffer::pushBack(std::shared_ptr<ClientData> data) {
	mutex.lock();
	queue.emplace(data);
	mutex.unlock();
}

void Buffer::popFront() {
	mutex.lock();
	queue.pop();
	mutex.unlock();
}

bool Buffer::empty() {
	mutex.lock();
	auto res = queue.size();
	mutex.unlock();

	return res == 0;
}
