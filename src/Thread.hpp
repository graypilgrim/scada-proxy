#ifndef THREAD_HPP_
#define THREAD_HPP_

enum class ThreadStatus {
	SUCCESS,
	FAIL
};

class Thread
{
public:
	virtual ~Thread() = 0;
	virtual ThreadStatus run() = 0;
};

#endif
