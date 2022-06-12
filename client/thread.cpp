#include "thread.h"
#include <utility>

/*
Pre-Condiciones: -
Post-Condiciones: Constructor de Thread.
*/

Thread::Thread() {
}

void Thread::start() {
   //printf("esta aca\n");
   this->thread = std::thread(&Thread::run, this);
   //printf("y aca ya se fue\n");
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
