#ifndef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__

#include <mutex>
#include <condition_variable>
#include <deque>
#include "ClientInput.h"

class BlockingQueue {
    std::mutex mutex;
    std::condition_variable emptyCondition;
    std::deque<ClientInput> queue;
 
 public:
    BlockingQueue();
    void push(ClientInput const& value);
    ClientInput pop();
    ~BlockingQueue() = default;
};

#endif
