#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    void (*callback)();
    int delay_ms;
    int running;
} IntervalArgs;

void* intervalThread(void* args) {
    IntervalArgs* intervalArgs = (IntervalArgs*)args;

    while(intervalArgs->running==1) {
        printf("This thread will be pause.\n");
        usleep(intervalArgs->delay_ms * 1000);
        intervalArgs->callback();
    }

    free(intervalArgs);
    return NULL;
}

void setInterval(void (*callback)(), int delay_ms) {
    pthread_t thread_id;
    IntervalArgs* args = malloc(sizeof(IntervalArgs));
    args->callback = callback;
    args->delay_ms = delay_ms;
    args->running = 1;

    pthread_create(&thread_id, NULL, intervalThread, args);
    pthread_detach(thread_id);
}

void callbackFunc() {
    printf("Calling...\n");
}

int main() {
    printf("Start the interval\n");
    setInterval(callbackFunc, 1000);

    pause();

    return 0;
}
