#include <stdio.h>
#include <pthread.h>
void* thread_function1(void* arg) {
    printf("Hello from Thread 1!\n");
    return NULL;
}

void* thread_function2(void* arg) {
    printf("Hello from Thread 2!\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread_function1, NULL);
    pthread_create(&thread2, NULL, thread_function2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Both threads have completed.\n");
    return 0;
}

