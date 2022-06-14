#include "BlockingQueue.h"
#include <utility>

BlockingQueue::BlockingQueue() {}

void BlockingQueue::push(ClientInput value) {
    {
        std::unique_lock<std::mutex> lock(this->mutex);
        queue.push_back(std::move(value));
    }
    this->emptyCondition.notify_one();
}

ClientInput BlockingQueue::pop() {
    std::unique_lock<std::mutex> lock(this->mutex);
    this->emptyCondition.wait(lock, [=]{ return !this->queue.empty(); });
    ClientInput value = std::move(this->queue.front());
    this->queue.pop_front();
    return value;
}
