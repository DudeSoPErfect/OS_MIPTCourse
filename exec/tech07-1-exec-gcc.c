/* RU

Программе на стандартном потоке ввода задается выражение в синтаксисе языка Си.

Необходимо вычислить значение этого выражения (итоговый результат представим типом int) и вывести его на стандартный поток вывода.

*/

/* ENG

The program is given an expression in the syntax of the C language on the standard input stream.

It is necessary to calculate the value of this expression (the final result is represented by the int type) and output it to the standard output stream.

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main() {

    char buff[4096] = {0};

    char c_code[] = "#include <stdio.h>\nint main() {\nprintf(\"%%d\", (%s));\nreturn 0;\n}\n";
    scanf("%[^\n]s", buff);
    FILE* file = fopen("prog.c", "wr+");
    
    
    fprintf(file, c_code, buff);
    fclose(file);

    pid_t pid = fork();


    if (pid > 0) {
        waitpid(pid, NULL, 0);
    } else {
        execlp("gcc", "gcc", "prog.c", NULL);
    }  

    pid = fork();

    if (pid > 0) {
        waitpid(pid, NULL, 0);
    } else {
        execlp("./a.out", "./a.out", NULL);
    }
    
    return 0;
}
