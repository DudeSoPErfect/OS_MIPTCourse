/* RU

Программа запускается с двумя целочисленными аргументами: N>0 - количество итераций; и k>0 - количество потоков.

Необходимо создать массив из k вещественных чисел, после чего запустить k потоков, каждый из которых работает со своим элементом массива и двумя соседними.

Каждый поток N раз увеличивает значение своего элемента на 1, увеличивает значение соседа слева на 0.99, и увеличивает значение соседа справа на 1.01.

Для потоков, у которых нет соседей справа (k-1) или слева (0), соседними считать первое и последнее значение массива соответственно.

После того, как все потоки проведут N итераций, необходимо вывести значения всех элементов.

Запрещено использовать глобальные переменные.

Для вывода используйте формат %.10g.

*/

/* ENG

The program starts with two integer arguments: N>0 - the number of iterations; and k>0 - the number of threads.

It is necessary to create an array of k real numbers, and then run k threads, each of which works with its own array element and two neighboring ones.

Each thread increases the value of its element by 1 N times, increases the value of the neighbor on the left by 0.99, and increases the value of the neighbor on the right by 1.01.

For threads that have no neighbors on the right (k-1) or on the left (0), the first and last values of the array are considered neighbors, respectively.

After all threads have performed N iterations, it is necessary to output the values of all elements.

It is forbidden to use global variables.

Use the %.10g format for output.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>    
#include <arpa/inet.h>

typedef struct {
    uint             size;
    double*          data;
    pthread_mutex_t*  mut;
    size_t              k;
} big_struct;


typedef struct {
    big_struct* structur;
    size_t           num;
} not_glob_val;



void* foo(void* arg) {

    not_glob_val* argu = (not_glob_val*)arg;
    double*       arr  = argu->structur->data;
    
    for (int i = 0; i < argu->structur->k; ++i) {
        pthread_mutex_lock(argu->structur->mut);
        arr[((argu->num + 1) % argu->structur->size)] += 0.99;

        arr[argu->num] += 1.00;
        arr[((argu->num + 1) % argu->structur->size)] += 1.01;
        pthread_mutex_unlock(argu->structur->mut);                  
    }

    return NULL;
}

int main(int argc, char* argv[]) {

    int k = atoi(argv[1]);
    int n = atoi(argv[2]);

    double          thr[n];
    pthread_mutex_t mut[n];
    pthread_t   threads[n];
    not_glob_val   argu[n];



    for (int i = 0; i < n; ++i) {
        thr[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        pthread_mutex_init(&mut[i], NULL);
    }
 
    big_struct info;

    info.size = n;
    info.data = thr;
    info.k    = k;
    info.mut  = mut;

    for (int i = 0; i < n; ++i) {
        argu[i].num      =  i;        
        argu[i].structur = &info;
        pthread_create(&threads[i],  NULL, foo, &argu[i]);

    }


    for (int i = 0; i < n; ++i) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < n; ++i) {
        printf("%.10g\n", thr[i]);
    }    

    for (int i = 0; i < n; ++i) {
        pthread_mutex_destroy(&mut[i]);
    }


    return 0;
}
