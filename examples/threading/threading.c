#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{
    struct thread_data* thread_func_args = (struct thread_data *) thread_param;

    struct timespec ts;
    ts.tv_sec = thread_func_args->obtain_delay_ms / 1000;
    ts.tv_nsec = (thread_func_args->obtain_delay_ms % 1000) * 1E6;
    if (0 == nanosleep(&ts, NULL)) {
        if (0 == pthread_mutex_lock(thread_func_args->mutex)) {
            ts.tv_sec = thread_func_args->release_delay_ms / 1000;
            ts.tv_nsec = (thread_func_args->release_delay_ms % 1000) * 1E6;
            nanosleep(&ts, NULL);
            pthread_mutex_unlock(thread_func_args->mutex);
            thread_func_args->thread_complete_success = true;
        }
    }

    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    struct thread_data *td = malloc(sizeof(struct thread_data));
    td->mutex = mutex;
    td->obtain_delay_ms = wait_to_obtain_ms;
    td->release_delay_ms = wait_to_release_ms;
    td->thread_complete_success = false;

    if (0 != pthread_create(&(td->thread_id), NULL, &threadfunc, td)) {
        free(td);
        return false;
    }
    *thread = td->thread_id;
    return true;
}

