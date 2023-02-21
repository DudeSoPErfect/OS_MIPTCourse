/*

Определите экспериментальным способом, какое максимальное колчичество процессов можно запустить с установленными в ejudge лимитами.

Запрещается использовать getrlimit, и другие явные способы определения ограничений.

*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    size_t i = 1;
    while (pid = fork() >= 0) {
        ++i;
    }
    if (pid == -1) { 
        printf("%d", counter);
    } else {
        int stat;
        waitpid(pid, &stat, 0);
    }
    printf("%lu\n", i);
}
