#include "BlockingQueue.h" 

void push(T const& value) {
    {
        std::unique_lock<std::mutex> lock(this->mutex);
        queue.push_front(value);
    }
    this->emptyCondition.notify_one();
}

T pop() {
    std::unique_lock<std::mutex> lock(this->mutex);
    this->emptyCondition.wait(lock, [=]{ return !this->queue.empty(); });
    T value(std::move(this->queue.back()));
    this->queue.pop_back();
    return value;
}
