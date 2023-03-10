/* RU

Программе передается аргумент - целое число N > 0.

Необходимо создать N-1 дополнительных процессов таким образом, чтобы у каждого процесса было не более одного дочернего процесса.

Каждый из процессов должен вывести на стандартный поток ввода ровно одно число таким образом, чтобы вы выходе получилась строка:

1 2 3 4 ... N
Внимание! В этой задаче будет сравнение с учетом пробельных символов. Между числами должен быть ровно один пробел, а завершается строка символом перевода строки.

*/

/* ENG

An argument is passed to the program - an integer N > 0.

It is necessary to create N-1 additional processes so that each process has no more than one child process.

Each of the processes must output exactly one number to the standard input stream so that the output is a string:

1 2 3 4 ... N
Attention! In this task, there will be a comparison taking into account whitespace characters. There must be exactly one space between the numbers, and the line ends with a newline character.

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char *argv[]) {
    
    int N = atoi(argv[1]);
    for (size_t i = 0; i < N; ++i) {
        pid_t pid = fork();
        
        if (pid != 0) {
            wait(0);      
            return 0;  
        }
            
        if (i != N - 1)
            printf("%lu ", i+1);
        else
            printf("%lu\n", i+1);
        fflush(stdout);
    }
    return 0;
}
