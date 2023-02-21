/* RU
Реализуйте Lock-Free односвязный список из элементов:

typedef struct Item {
  struct Item *next;
  int64_t      value;
} item_t;

Программа принимает в качестве аргумента значения N - количество потоков, и k - количество элементов, создаваемых каждым потоком.

Этих потоков может быть очень много - несколько десятков!

Каждый поток должен добавить в односвязный список k элементов со значениями от i*k до (i+1)*k, где i - это номер потока от 0 до N.

После завершения работы всех потоков выведите все значения полученного односвязного списка.

Запрещено использовать мьютексы, семафоры или активное ожидание.

Минимизируйте используемый объем памяти.

Для уменьшения времени простоя используйте sched_yield в конце каждой итерации.
*/

/* ENG
Implement a Lock-Free singly linked list of elements:

typedef struct Item {
 struct Item *next;
 int64_t value;
} item_t;

The program takes as an argument the values N - the number of threads, and k - the number of elements created by each thread.

There can be a lot of these streams - several dozen!

Each thread must add k elements with values from i*k to (i+1)*k to the simply connected list, where i is the number of the thread from 0 to N.

After all threads are finished, output all the values of the resulting single-linked list.

It is forbidden to use mutexes, semaphores or active waiting.

Minimize the amount of memory used.

To reduce downtime, use the sched_yield at the end of each iteration.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>    
#include <arpa/inet.h>
#include <unistd.h>
#include <stdatomic.h>

typedef struct Item {
  struct Item  *next;
  int64_t      value;
} item_t;

typedef struct {
    int    start;
    item_t** top;
    int        k;
} big_str;

enum vals {
    beg = -1,
};

void* work(void* arg) {

    big_str* argu = (big_str*) arg;

    for (int i = 0; i < argu->k; ++i) {
        item_t* new_one = calloc(1, sizeof(item_t));
        new_one->next  = *(argu->top);
        new_one->value = argu->start + i;
        while (!atomic_compare_exchange_strong(argu->top, &new_one->next, new_one))
        {
            sched_yield();
        }
        
    }


    return NULL;
}


int main(int argc, char* argv[]) {

    int N  = atoi(argv[1]);
    int k  = atoi(argv[2]);

    pthread_t threads[N];

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));
    pthread_attr_setguardsize(&attr, 0);

    big_str arr[N];

    item_t* top = calloc(1, sizeof(item_t));
    top->value  = beg;
    top->next   = NULL;

    for (int i = 0; i < N; ++i) {
        arr[i].top   = &top;
        arr[i].k     = k;
        arr[i].start = k * i;
        pthread_create(&threads[i], &attr, work, arr + i);
    }

    for (int i = 0; i < N; ++i) {
        pthread_join(threads[i], NULL);
    }    

    while(top->value != -1) {
        printf("%ld\n", top->value);
        item_t* old_one = top;
        top = top->next;
        free(old_one);
    }

    free(top);
    pthread_attr_destroy(&attr);

    return 0;
}
