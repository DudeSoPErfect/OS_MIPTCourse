/*

Программе передаётся произвольное количество аргументов: CMD1, CMD2, ..., CMDN.

Необходимо реализовать эквивалент запуска их командной строки: CMD1 | CMD2 | ... | CMDN.

Родительский процесс должен завершаться самым последним!

*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {

    if (argc == 2) {
        pid_t pid = fork();
        if (pid == 0) {
            execlp(argv[1], argv[1], NULL);
        } else {
            waitpid(pid, NULL, 0);
            return 0;
        }      
    } else {
        for (size_t i = 0; i < argc - 1; i++) {

            if (i == argc - 2) {
                pid_t pid = fork();

                if (pid == 0) {
                    execlp(argv[i+1], argv[i+1], NULL);
                } else {
                    waitpid(pid, NULL, 0);
                }
            } else {
                int pipefd[2];
                pipe(pipefd);

                pid_t pid = fork();
            
                if (pid == 0) {
                    close(pipefd[0]);
                    dup2(pipefd[1], 1);
                    execlp(argv[i+1], argv[i+1], NULL);
                    //
                } else {
                    waitpid(pid, NULL, 0);
                    close(pipefd[1]);
                    dup2(pipefd[0], 0);
                    close(pipefd[0]);
                }
            }
            
        }
    }

    return 0;
}
