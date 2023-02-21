/* RU 

Необходимо реализовать программу-сервер, которой передаются два аргумента: номер порта и полный путь к каталогу с данными.

Программа должна прослушивать TCP-соединение на сервере localhost и указанным номером порта.

После получения сигнала SIGTERM или SIGINT сервер должен закончить обработку текущего соединения, если оно есть, после чего корректно завершить свою работу. Если при этом были запущены дочерние процессы - они должны быть завершены самим сервером.

Внимание: в этой задаче признаком конца строк считается пара символов "\r\n", а не одиночный символ '\n'.

Каждое соединение должно обрабатываться следующим образом:

Клиент отправляет строку вида GET ИМЯ_ФАЙЛА HTTP/1.1
Клиент отправляет произвольное количество непустых строк
Клиент отправляет пустую строку

После получения пустой строки от клиента, сервер должен отправить клиенту слеющие данные:

Строку HTTP/1.1 200 OK, если файл существует, или HTTP/1.1 404 Not Found, если файл не существует, или HTTP/1.1 403 Forbidden, если файл существует, но не доступен для чтения
Если файл не является выполняемым, то:

Строку Content-Length: %d, где %d - размер файла в байтах
Пустую строку
Содержимое файла as-is

Если файл является выполняемым, то после вывода строки HTTP/1.1 200 OK нужно выполнить этот файл, перенаправив его стандартный поток вывода клиенту as-is.

После отправки ответа клиенту, нужно закрыть соединение и не нужно ждать ожидать от клиента следующих запросов.

*/

/* ENG

It is necessary to implement a server program to which two arguments are passed: the port number and the full path to the data directory.

The program must listen for a TCP connection on the localhost server and the specified port number.

After receiving the SIGTERM or SIGINT signal, the server must finish processing the current connection, if there is one, and then finish its work correctly. If child processes were started at the same time, they must be terminated by the server itself.

Attention: in this problem, a pair of characters "\r\n" is considered a sign of the end of lines, and not a single character '\n'.

Each connection should be handled as follows:

The client sends a string like GET FILENAME HTTP/1.1
The client sends an arbitrary number of non-empty rows
The client sends an empty string

After receiving an empty string from the client, the server must send the client the following data:

The line HTTP/1.1 200 OK if the file exists, or HTTP/1.1 404 Not Found if the file does not exist, or HTTP/1.1 403 Forbidden if the file exists but is not readable
If the file is not executable, then:

The string Content-Length: %d, where %d is the file size in bytes
Empty string
Contents of the as-is file

If the file is executable, then after the HTTP/1.1 200 OK line is output, you need to execute this file by redirecting its standard output stream to the as-is client.

After sending a response to the client, you need to close the connection and do not need to wait for the next requests from the client.

*/

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>


enum time{
    not_now = -1,
    now = 1,
};

volatile sig_atomic_t time_to_exit = not_now;

void handler (int n_sig) {
    time_to_exit = now;
}

int main(int argc, char* argv[]) {

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {
        .sin_family      = AF_INET,
        .sin_port        = htons(atoi(argv[1])),
        .sin_addr.s_addr = inet_addr("127.0.0.1"),
    };

    struct sigaction sa = {
        .sa_handler = handler,
    };

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    bind(socket_fd, (struct sockaddr*)(&addr), sizeof(addr));
    listen(socket_fd, SOMAXCONN);

    while (time_to_exit != now) {
        int client_fd = accept(socket_fd, NULL, NULL);

        char buff[4096]; 
        char file_name[4096];
        read(client_fd, buff, 4096);
        sscanf(buff, "GET %s HTTP/1.1", file_name);
        

        char path[4096] = {0};
        strcat(path, argv[2]);
        strcat(path, "/");
        strcat(path, file_name);

        if (access(path, F_OK) == -1) {
            write(client_fd, "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n", strlen("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n"));
        } else if (access(path, R_OK) == -1) {
            write(client_fd, "HTTP/1.1 403 Forbidden\r\nContent-Length: 0\r\n\r\n", strlen("HTTP/1.1 403 Forbidden\r\nContent-Length: 0\r\n\r\n"));
        } else {
            struct stat st;
            stat(path, &st);
            write(client_fd, "HTTP/1.1 200 OK\r\n", strlen("HTTP/1.1 200 OK\r\n"));
            if (access(path, X_OK) == -1) {
                write(client_fd, "Content-Length: ", strlen("Content-Length: "));
                dprintf(client_fd, "%ld", st.st_size);
                //write(client_fd, &st.st_size, sizeof(st.st_size));
                write(client_fd, "\r\n\r\n", strlen("\r\n\r\n"));

                int des = open(path, O_RDONLY);
                char an_buff[4096];   

                ssize_t n_bytes = read(des, an_buff, st.st_size);
                write(client_fd, an_buff, n_bytes);
                close(des); 
            }
        }    
        if (access(path, X_OK) != -1) {
            pid_t pid = fork();
            if (pid == 0) {
                dup2(client_fd, STDOUT_FILENO);
                close(client_fd);
                execl(path, "uwu", NULL);
            } 
            waitpid(pid, NULL, 0);
        }   

        shutdown(client_fd, SHUT_RDWR);
        close(client_fd);
    }   

    close(socket_fd);   
    return 0;
}
