/* RU

Программе в качестве аргументов передаются N имен текстовых файлов.

Программа должна обрабатывать множество сигналов от SIGRTMIN до SIGRTMAX, причем номер сигнала в диапазоне от SIGRTMIN+1 определяет порядковый номер файла из аргументов:

x = signo - SIGRTMIN; // SIGRTMIN <= signo <= SIGRTMAX
                      // 1 <= x <= SIGRTMAX-SIGRTMIN
                      
При получении очередного сигнала необходимо прочитать одну строку из определенного файла и вывести её на стандартный поток вывода.

При получении сигнала с номером SIGRTMIN, т.е. при номере аргумента, равным 0, - корректно завершить свою работу с кодом 0.

Все остальные сигналы нужно игнорировать.

Если для вывода используются высокоуровневые функции стандартной библиотеки Си, то необходимо выталкивать буфер обмена после вывода каждой строки.

*/

/* ENG

N names of text files are passed to the program as arguments.

The program must process many signals from SIGRTMIN to SIGRTMAX, and the signal number in the range from SIGRTMIN+1 determines the sequence number of the file from the arguments:

x = signo - SIGRTMIN; // SIGRTMIN <= signo <= SIGRTMAX
 // 1 <= x <= SIGRTMAX-SIGRTMIN
 
When receiving the next signal, it is necessary to read one line from a certain file and output it to the standard output stream.

When receiving a signal with the SIGRTMIN number, i.e. with the argument number equal to 0, - correctly terminate its work with the code 0.

All other signals should be ignored.

If high-level functions of the standard C library are used for output, then it is necessary to push the clipboard after each line is output.

*/

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char str_buff[6048] = {0};

volatile sig_atomic_t glob_s;

void handler (int signo) {
    if (signo > SIGRTMIN && signo <= SIGRTMAX) {
        glob_s = signo;
    } else {
        glob_s = SIGRTMIN;
    }
}

int main(int argc, char** argv) {
    
    struct sigaction sa = {
        .sa_handler = handler,
    };
        
    for (int sig_i = SIGRTMIN; sig_i <= SIGRTMAX; ++sig_i) 
        sigaction(sig_i, &sa, NULL);

    while (1)
    {
        pause();

        if (glob_s == SIGRTMIN) {
            exit(0);
        }

        FILE* f = fopen(argv[glob_s - SIGRTMIN], "r");
        fgets(str_buff, 6048, f);
        printf("%s", str_buff);

        fclose(f);
        fflush(stdout);
    }
    
    return 0;
}
