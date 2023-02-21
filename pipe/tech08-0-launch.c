/*
Реализуйте программу, которая принимает два аргумента: CMD - команда для запуска, IN - имя файла, направляемого на ввод.

Программа должна запускать указанную команду, передавая ей на вход содежимое файла IN.

На стандартный поток вывода вывести количество байт, которое было записано запущенной командой в стандартный поток вывода. Вывод самой команды никуда выводить не нужно.
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>


int main(int argc, char** argv) {
    char buff[40000];
    int pipefd[2];

    char* cmd = argv[1];
    char* in  = argv[2];

    pipe(pipefd);
    pid_t pid = fork();

    if (pid > 0) {
        close(pipefd[1]);

        size_t counter = 0;

        while (1) {
            int nread = read(pipefd[0], buff, sizeof(buff));
            counter += nread;
            if (nread == 0)
                break;
        }

        printf("%ld\n", counter);
        close(pipefd[0]);

    } else {
        close(pipefd[0]);

        int in_descriptor = open(in, O_RDONLY);
        dup2(in_descriptor, 0);
        close(in_descriptor);
        dup2(pipefd[1], 1);


        close(pipefd[1]);
        execlp(cmd, cmd, NULL);
        return 0;
    }
}
