#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    void (*callback)();
    int delay_ms;
} TimeoutArgs;

void* timeoutThread(void* args) {
    TimeoutArgs* timeoutArgs = (TimeoutArgs*)args;

    usleep(timeoutArgs->delay_ms * 1000);
    timeoutArgs->callback();

    free(timeoutArgs);
    return NULL;
}

void setTimeout(void (*callback)(), int delay_ms) {
    pthread_t thread_id;
    TimeoutArgs* args = malloc(sizeof(TimeoutArgs));
    args->callback = callback;
    args->delay_ms = delay_ms;

    pthread_create(&thread_id, NULL, timeoutThread, args);
    pthread_detach(thread_id);
}

void callMe() {
    printf("Hi! Lerry.");
}

int main() {
    printf("Start calling me after 2 seconds!\n");

    setTimeout(callMe, 2000);

    usleep(3000 * 1000);

    return 0;
}
