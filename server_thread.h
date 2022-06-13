#ifndef __THREAD_H__
#define __THREAD_H__

#include <thread>

class Thread {
	std::thread thread;
	public:
	Thread();
	void start();
	void join();
    int get_id();
	virtual void run() = 0;
	virtual ~Thread();
};

#endif /*__THREAD_H__*/
