/* RU
Реализуйте программу, которая принимает два аргумента: CMD - команда для запуска, IN - имя файла, направляемого на ввод.

Программа должна запускать указанную команду, передавая ей на вход содежимое файла IN.

На стандартный поток вывода вывести количество байт, которое было записано запущенной командой в стандартный поток вывода. Вывод самой команды никуда выводить не нужно.
*/

/* ENG
Implement a program that takes two arguments: CMD is the command to run, IN is the name of the file to be sent for input.

The program must run the specified command, passing the contents of the IN file to it as input.

Output to the standard output stream the number of bytes that was written by the running command to the standard output stream. The output of the command itself does not need to be output anywhere.
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
