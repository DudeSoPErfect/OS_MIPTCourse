/* RU

Реализуйте функцию с сигнатурой:

          extern size_t
          read_data_and_count(size_t N, int in[N])
        
которая читает данные из файловых дескрипторов in[X] для всех 0 ≤ X < N , и возвращает суммарное количество прочитанных байт из всех файловых дескрипторов.

Скорость операций ввода-вывода у файловых дескрипторов - случайная. Необходимо минимизировать суммарное астрономическое время чтения данных.

По окончании чтения необходимо закрыть все файловые дескрипторы.

*/

/* ENG

Implement a function with a signature:

 extern size_t
read_data_and_count(size_t N, int in[N])

which reads data from file descriptors in[X] for all 0 ≤ X < N , and returns the total number of bytes read from all file descriptors.

The speed of I/O operations for file descriptors is random. It is necessary to minimize the total astronomical data reading time.

At the end of reading, it is necessary to close all file descriptors.

*/

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>

extern size_t read_data_and_count(size_t N, int in[N])
{
    size_t bytes_num = 0;
    size_t n_read = 0;
    size_t handled = 0;
    int epoll = epoll_create1(0);
    char buff[2048];


    for (size_t i = 0; i < N; i++) {
        int fl = fcntl(in[i], F_GETFL);
        fl |= O_NONBLOCK;
        fcntl(in[i], F_SETFL, fl); //set new

        struct epoll_event event = 
        {
            .events = EPOLLIN,
            .data.fd = in[i]
        };

        epoll_ctl(epoll, EPOLL_CTL_ADD, in[i], &event);
    }

    int ready = 0;
    struct epoll_event events[N];
    while (handled < N) {
        ready = epoll_wait(epoll, events, N, -1);
        for (size_t i = 0; i < ready; ++i) {
            n_read = read(events[i].data.fd, buff, 2048);
            if (n_read > 0) {
                bytes_num += n_read;
            } else {
                close(events[i].data.fd);
                ++handled;
            }
        }

    }
    close(epoll);





    return bytes_num; 
}
