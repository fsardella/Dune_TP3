#ifdef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__

#include <mutex>
#include <condition_variable>
#include <deque>

template <typename T>

class BlockingQueue {
    std::mutex mutex;
    std::condition_variable emptyCondition;
    std::deque<T> queue;
 
 public:
    BlockingQueue() = default;
    void push(T const& value);
    T pop();
    ~BlockingQueue() = default;
};

#endif
