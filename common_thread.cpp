#include "common_thread.h"
#include <utility>
#include <sstream>

/*
Pre-Condiciones: -
Post-Condiciones: Constructor de Thread.
*/

Thread::Thread() {
}

void Thread::start() {
   this->thread = std::thread(&Thread::run, this);
}

void Thread::join() {
    this->thread.join();
}

/*
Pre-Condiciones: -
Post-Condiciones: Destructor de Thread.
*/

Thread::~Thread() {
}
