/*

Единственным аргументом программы является целое число N>1 - число потоков, которые нужно создать.

На стандартном потоке ввода задается последовательность целых чисел.

Реализуйте программу, которая запускает N потоков, каждый из которых читает числа со стандартного потока ввода, и вычисляет частичные суммы. Учтите, что количество потоков необязательно равно количеству чисел.

На стандартный поток вывода необходимо вывести итоговую сумму всех чисел.

Минимизируйте объем используемой памяти настолько, насколько это возможно. Обратите внимание на ограничение по памяти.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>    
#include <arpa/inet.h>
#include <unistd.h>

void* work(void* arg) {
    int* argu = (int*) arg;
    int val   = 0;
    
    while(scanf("%d", &val) > 0) {
        *argu += val;
    }

    return NULL;
}


int main(int argc, char* argv[]) {

    int N   = atoi(argv[1]);
    int ans = 0;

    pthread_t threads[N];
    int             s[N];

    for (int i = 0; i < N; ++i) {
        s[i] = 0;
    }

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));
    pthread_attr_setguardsize(&attr, 0);

    for (int i = 0; i < N; ++i) {
        pthread_create(&threads[i], &attr, work, &s[i]);
    }

    for (int i = 0; i < N; ++i) {
        pthread_join(threads[i], NULL);
        ans += s[i];
    }

    pthread_attr_destroy(&attr);

    printf("%d\n", ans);

    return 0;
}
