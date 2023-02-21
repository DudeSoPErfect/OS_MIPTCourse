/* RU

Программе передаются два аргумента: строка с IPv4-адресом в стандартной десятичной записи (четыре числа, разделенные точкой), и номер порта.

Программа должна установить соединение с указанным сервером, после чего читать со стандартного потока ввода целые знаковые числа в текстовом формате, и отправлять их в бинарном виде на сервер. Порядок байт - Little Endian.

В ответ на каждое полученное число, сервер отправляет целое число (в таком же формате), и все эти числа необходимо вывести на стандартный поток вывода в текстовом виде.

Если сервер по своей инициативе закроет соединение, то нужно завершить работу с кодом возврата 0.

*/

/* ENG

Two arguments are passed to the program: a string with an IPv4 address in standard decimal notation (four numbers separated by a dot), and the port number.

The program must establish a connection with the specified server, then read signed integers in text format from the standard input stream, and send them in binary form to the server. The byte order is Little Endian.

In response to each received number, the server sends an integer (in the same format), and all these numbers must be output to the standard output stream in text form.

If the server closes the connection on its own initiative, then you need to exit with the return code 0.

*/

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

const int ASCII_MOMENT = 48;

void shutdownAndExit(int socket_fd){
    shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);
    exit(0);
}



int main(int argc, char** argv) {
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(atoi(argv[2])),
        .sin_addr.s_addr = inet_addr(argv[1]),
    };

    connect(socket_fd, (struct sockaddr*)(&addr), sizeof(addr));


    int n_send = 0;
    int n_recieve = 0;
    size_t len = 0;
    while (scanf("%d", &n_send) > 0) {
        char bin_num[40] = {0};
        if (write(socket_fd, &n_send, sizeof(n_send)) < 1) 
            break;
        if (read(socket_fd, &n_recieve, sizeof(n_recieve)) < 1)
            break;
        printf("%d\n", n_recieve);
    }
    
    
    shutdownAndExit;
    return 0;
}
