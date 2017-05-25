#include "ClientData.hpp"

ClientData::ClientData()
	: mutex(std::unique_ptr<std::mutex>(new std::mutex))
{}

void ClientData::addRequest(std::unique_ptr<Message> request)
{
	this->request = std::move(request);
}

void ClientData::addResponse(std::unique_ptr<Message> response)
{
	this->response = std::move(response);
}

void ClientData::lockClient()
{
	mutex->lock();
}

void ClientData::unlockClient()
{
	mutex->unlock();
}
