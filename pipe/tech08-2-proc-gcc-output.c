/* RU

Программе в качестве аргумента передается имя файла программы на языке Си. 
Необходимо попытаться её скомпилировать с помощью штатного компилятора gcc, 
после чего вывести на стандартный поток вывода: количество строк программы с ошибками (error),
и количество строк программы с предупреждениями (warning). В одной строке может быть найдено несколько ошибок или предупреждений, - нужно вывести именно количество строк.

Запрещено создавать временные файлы для сохранения вывода ошибок компилятора. 
Используйте передачу текста от компилятора через каналы.

*/

/* ENG

The program file name in C is passed to the program as an argument. 
It is necessary to try to compile it using the standard gcc compiler,
and then output to the standard output stream: the number of lines of the program with errors (error),
and the number of lines of the program with warnings (warning). Several errors or warnings can be found in one line - it is necessary to output exactly the number of lines.

It is forbidden to create temporary files to save compiler error output. 
Use text transmission from the compiler via channels.

*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

enum latest_fault {
    war,
    er,
    not_handled = -1,
};

int main(int argc, char** argv) {

    char word[100];
    char warning[] = "warning:";
    char error[] = "error:";
    char where_the_fault_is[4000];
    char format[] = ":%d:%d: ";
    int l1 = strlen(argv[1]);
    int l2 = strlen(format);

    memcpy(where_the_fault_is, argv[1], l1);
    memcpy(where_the_fault_is + l1, format, l2 + 1);
    char buff[4000];

    int pipefd[2];
    pipe(pipefd);

    
    pid_t pid = fork();

    if (pid == 0) {

        close(pipefd[0]);
        dup2(pipefd[1], STDERR_FILENO);
        close(pipefd[1]);
        execlp("gcc", "gcc", argv[1], NULL);
        _exit(0);

    } else {
        waitpid(pid, NULL, 0);
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        

        int prev_err = not_handled;
        int prev_war = not_handled;
        int cur_line = 0, cur_sym = 0;
        int n_line_er = war;
        int n_line_war = war;

        while (scanf("%s", buff) != EOF) {
            if (sscanf(buff, where_the_fault_is, &cur_line, &cur_sym) == 2) {
                scanf("%s", word);
                if (cur_line != prev_err) {
                    if (strcmp(word, error) == 0) {
                        ++n_line_er;
                        prev_err = cur_line;
                    } else if (cur_line != prev_war) {
                        if (strcmp(word, warning) == 0) {
                            ++n_line_war;
                            prev_war = cur_line;
                        }
                    }
                } else if (cur_line != prev_war) {
                    if (strcmp(word, warning) == 0) {
                        ++n_line_war;
                        prev_war = cur_line;
                    } 
                }
            }
            
        }

        setvbuf(stdout, NULL, _IONBF, 0);
        printf("%d %d", n_line_er, n_line_war);
        _exit(0);
    }

    return 0;
}
