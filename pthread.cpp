#include <iostream>
#include <pthread.h>

void* magic(void *threadid) {
   int* args = (int *)threadid;
   std::cout << "Hello World! Thread ID, " << args[1] << '\n';
   pthread_exit(NULL);
}

int main() {
    std::cout << "Hello World\n";
    pthread_t thread;
    int* args = new int[3];
    args[0] = 1;
    args[1] = 2;
    args[2] = 3;
    pthread_create(&thread,NULL,PrintHello,(void *)args);
    while (true) {
        // Nothing
    }
    pthread_exit(NULL);
}