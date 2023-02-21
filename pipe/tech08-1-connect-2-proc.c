/* RU
Программе передаётся два аргумента: CMD1 и CMD2. Необходимо запустить два процесса, выполняющих эти команды, и перенаправить стандартный поток вывода CMD1 на стандартный поток ввода CMD2.

В командной строке это эквивалентно CMD1 | CMD2.

Родительский процесс должен завершаться самым последним!
*/

/* ENG
Two arguments are passed to the program: CMD1 and CMD2. It is necessary to start two processes executing these commands and redirect the standard output stream CMD1 to the standard input stream CMD2.

On the command line, this is equivalent to CMD1|CMD2.

The parent process must be completed the very last!
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char** argv) {

    int pipefd[2];
    pipe(pipefd);
    pid_t pid1 = fork();

    
    if (pid1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        execlp(argv[1], argv[1], NULL);
        close(pipefd[1]);   
        return 0;
    }

    pid_t pid2 = fork();

    if (pid2 == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], 0);
        execlp(argv[2], argv[2], NULL);
        close(pipefd[0]);
    }


    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}
