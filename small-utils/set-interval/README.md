### Interval in C with thread ###

This is a small code for set interval function as a util for larger
projects. The thread helps to isolate the process of waiting with a
specific time set while other processes could be executed. Since
without threading the main thread is going to be blocked as the OS
only assign a thread for the process.

```c
typedef struct {
    void (*callback)();
    int delay_ms;
    int running;
} IntervalArgs;
```

Structure for the heap memory, as it needs to be saved, these values 
for making it just like a global variables, and because thread requires
a pointer for the arguments. A pointer for a local variable only works
in its scope.

```c
void callbackFunc() {
    printf("Calling...\n");
}

int main() {
    printf("Start the interval\n");
    setInterval(callbackFunc, 1000);

    pause();

    return 0;
}
```

In this case I used pause() to stop the main thread and allowing me to
visualized the process of setInterval.

```c
void setInterval(void (*callback)(), int delay_ms) {
    pthread_t thread_id;
    IntervalArgs* args = malloc(sizeof(IntervalArgs));
    args->callback = callback;
    args->delay_ms = delay_ms;
    args->running = 1;

    pthread_create(&thread_id, NULL, intervalThread, args);
    pthread_detach(thread_id);
}
```

The setInterval function accepts two arguments, the callback and delay.
New thread needs an id. The malloc sets a space in heap memory for global
access and IntervalArgs as the placeholder for it.

pthread_create() create a new thread.
pthread_detach() detach the new thread from the main their to works on its
own.

```c
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
```

This is the function that the thread will run on. The args is a pointer
to the heap memory that will be casted to be back to its original form.
While loop will continously run its block as indefinitely until the program
is terminated or the value in the heap(running) changed to 0 as false.
Function usleep is going to block its thread so don't be worried about
while loop. Lastly the free will get rid the intervalArgs in the heap to
avoid memory leaks.
