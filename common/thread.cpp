#include "thread.h"
#include <utility>

/*
Pre-Condiciones: -
Post-Condiciones: Constructor de Thread.
*/

Thread::Thread() {
}

/*
Pre-Condiciones: -
Post-Condiciones: Se lanza el thread.
*/

void Thread::start() {
    this->thread = std::thread(&Thread::run, this);
}

/*
Pre-Condiciones: -
Post-Condiciones: Se joinea el thread.
*/

void Thread::join() {
    this->thread.join();
}
/*
Pre-Condiciones: -
Post-Condiciones: Destructor de Thread.
*/

Thread::~Thread() {
}
