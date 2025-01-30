### The Set Timout in C with Powerful Thread ###

OS will normally designate at least a thread to process the program.
Thereby usleep() will block the main thread where the execution of
the system happens, it means all the code after the usleep will be
process as usleep ends. So creating new thread is really convinient
to enfore an asyncronous flow of processing.

First lets jump over the main function which is the main entry.

```c
int main() {
    printf("Start calling me after 2 seconds!\n");

    setTimeout(callMe, 2000);

    usleep(3000 * 1000);

    return 0;
}
```

It invokes the setTimeout function and using usleep to block the main
thread so we have time for the setTimeout to be completed.

```c
void callMe() {
    printf("Hi! Lerry.");
}
```

The callMe function is the callback for setTimeout.

```c
typedef struct {
    void (*callback)();
    int delay_ms;
} TimeoutArgs;
```

Declaration of struct for variables needed to store in heap memory.

```c
void setTimeout(void (*callback)(), int delay_ms) {
    pthread_t thread_id;
    TimeoutArgs* args = malloc(sizeof(TimeoutArgs));
    args->callback = callback;
    args->delay_ms = delay_ms;

    pthread_create(&thread_id, NULL, timeoutThread, args);
    pthread_detach(thread_id);
}
```

It accepts two arguments, a callback pointer and the delay in
milliseconds. The thread_id is the new thread. The TimeoutArgs is 
the structure to save callback and delay which now have space in
the heap memory using malloc().

pthread_create() create a new
thread.

pthread_detach() detach that thread from the main thread to work
on it self.

```c
void* timeoutThread(void* args) {
    TimeoutArgs* timeoutArgs = (TimeoutArgs*)args;

    usleep(timeoutArgs->delay_ms * 1000);
    timeoutArgs->callback();

    free(timeoutArgs);
    return NULL;
}
```

So this is the function that the thread will run on. The args
is the pointer in the heap which store data with the structure of
TimeoutArgs. Type cast the args to convert to its original form.
Used the usleep() to delay the execution in that thread. Finally
after a cetain amount of delay the callback will be executed. The
free() function will discard the timeoutArgs in the heap memory to
prevent memory leak. Since the funtion for the thread requires a
return so just return NULL.
