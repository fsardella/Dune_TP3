#ifndef __THREAD_H__
#define __THREAD_H__

#include <thread>

class Thread {
    std::thread thread;
    public:
    Thread();
    void start();
    void join();
    virtual void run() = 0;
    virtual ~Thread();
};

#endif /*__THREAD_H__*/
