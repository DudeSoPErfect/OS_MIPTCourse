/*

Программе задается единственный аргумент - номер TCP-порта.

Необходимо принимать входящие соединения на TCP/IPv4 для сервера localhost, читать данные от клиентов в текстовом виде, и отправлять их обратно в текстовом виде, заменяя все строчные буквы на заглавные. Все обрабатываемые символы - из кодировки ASCII.

Одновременных подключений может быть много. Использовать несколько потоков или процессов запрещено.

Сервер должен корректно завершать работу при получении сигнала SIGTERM.

*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>  
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <stdlib.h>


enum handling {
    stay = 0,
    cancel = 1
};

volatile sig_atomic_t status = stay;

void handler(int n_sig) {
    status = cancel;
}

int main(int argc, char* argv[]) {

    struct sigaction sa = {
        .sa_handler = handler,
    };

    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
    

    struct sockaddr_in addr = {
        .sin_family      = AF_INET,
        .sin_port        = htons(atoi(argv[1])),
        .sin_addr.s_addr = inet_addr("127.0.0.1"),
    };

    printf("%d\n", addr.sin_port);

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    bind  (socket_fd, (struct sockaddr*)(&addr), sizeof(addr));
    listen(socket_fd, SOMAXCONN);

    int fl = fcntl(socket_fd, F_GETFL);
    fl |= O_NONBLOCK;
    fcntl(socket_fd, F_SETFL, fl);

    int epoll = epoll_create1(0);
    struct epoll_event event = 
    {
            .events = EPOLLIN,
            .data.fd = socket_fd
    };
    epoll_ctl(epoll, EPOLL_CTL_ADD, socket_fd, &event);

    struct epoll_event events[4096];    

    int ready = 0;
    while(status != cancel) {
        ready = epoll_wait(epoll, events, 4096, -1);
        if (ready == -1) {
            break;
        } else {
            for (int i = 0; i < ready; ++i) {
                if (events[i].data.fd == socket_fd) {
                    int fd = 0;
                    while(1) {
                        fd = accept(socket_fd, NULL, NULL);
                        if (fd == -1) {
                            break;
                        }

                        fl = fcntl(fd, F_GETFL);
                        fl |= O_NONBLOCK;
                        fcntl(fd, F_SETFL, fl);

                        struct epoll_event event = 
                        {
                                .events = EPOLLIN,
                                .data.fd = fd
                        };
                        epoll_ctl(epoll, EPOLL_CTL_ADD, fd, &event);                        

                    } 
                } else {
                    char buff[2048] = {0};

                    int n_read = read(events[i].data.fd, buff, 2048);
                    if (n_read <= 0) {
                        shutdown(events[i].data.fd, SHUT_RDWR);
                        close(events[i].data.fd);

                    } else {
                        for (int i = 0; i < n_read; ++i) {
                            buff[i] = toupper(buff[i]);
                        }

                        int n_write = write(events[i].data.fd, buff, n_read);
                        if (n_write <= 0) {
                            shutdown(events[i].data.fd, SHUT_RDWR);
                            close(events[i].data.fd);                       
                        }
                    }
                }
            }
        }
    }

    close(epoll);
    close(socket_fd);

    return 0;
}
