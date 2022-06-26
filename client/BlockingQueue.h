#ifndef __COMMON_BLOCKINGQUEUE_H__
#define __COMMON_BLOCKINGQUEUE_H__

#include <mutex>
#include <condition_variable>
#include <queue>
#include <deque>
#include <utility>

#include <iostream>

// Implementar el what() con un mensaje descriptivo
class ClosedQueueException: public std::exception {};

typedef std::unique_lock<std::mutex> queueLock_t;

template <class T>
class BlockingQueue{
    std::mutex m;
    std::queue<T> blockedQueue;
    std::condition_variable notEmpty;
    bool closed;
 public:
    BlockingQueue();
    void close();
    void push(T element);
    T pop();
    ~BlockingQueue();
    
    BlockingQueue(const BlockingQueue&) = delete;
    BlockingQueue& operator=(const BlockingQueue&) = delete;

    BlockingQueue(BlockingQueue&&);
    BlockingQueue& operator=(BlockingQueue&&);
};

// Definiciones en header porque los Templates son malas personas.
// O porque no son clases...
template <class T>
BlockingQueue<T>::BlockingQueue(): closed(false) {}

template <class T>
void BlockingQueue<T>::push(T element) {
    if (this->closed)
        throw ClosedQueueException();
    queueLock_t lock(m);
    blockedQueue.push(std::move(element));
    notEmpty.notify_all();
}

// Si hacés un pop de una cola que está cerrada pero aún tiene elementos,
// te tiene que devolver un elemento.
template <class T>
T BlockingQueue<T>::pop() {
    if (this->closed)
        throw ClosedQueueException();
    queueLock_t lock(m);
    // T value;
    notEmpty.wait(lock, [this]{return !blockedQueue.empty() || closed;});
    if (this->closed)
        throw ClosedQueueException();
    T value = std::move(blockedQueue.front());
    blockedQueue.pop();
    return value;
}

// Tomar el lock para esto
template <class T>
void BlockingQueue<T>::close() {
    this->closed = true;
    notEmpty.notify_all();
}

template <class T>
BlockingQueue<T>::~BlockingQueue() {}

template <class T>
BlockingQueue<T>::BlockingQueue(BlockingQueue&& other) :
                           blockedQueue(std::move(other.blockedQueue)),
                           closed(other.closed) {}
template <class T>
BlockingQueue<T>& BlockingQueue<T>::operator=(BlockingQueue&& other) {
    if (this == &other)
        return *this;
    this->blockedQueue = std::move(other.blockedQueue);
    this->closed = other.closed;
    other.closed = true;
    return *this;
}


#endif