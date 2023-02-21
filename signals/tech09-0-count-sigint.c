/*

Программа при запуске сообщает на стандартный поток вывода свой PID, выталкивает буфер вывода с помощью fflush, после чего начинает обрабатывать поступающие сигналы.

При поступлении сигнала SIGTERM необходимо вывести на стандартный поток вывода целое число: количество ранее поступивших сигналов SIGINT и завершить свою работу.

Семантика повединия сигналов (Sys-V или BSD) считается не определенной.

*/

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

volatile int ans = 0;    


void handler(int n_sig) {
    if (n_sig == SIGTERM) {
        printf("%d\n", ans);
        exit(0);
    }
    if (n_sig == SIGINT) {
        ++ans;
    }
}

int main() {

    struct sigaction sa = {
        .sa_handler = handler,
        .sa_flags = SA_RESTART,
    };
    
    
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    printf("%d\n", getpid());
    fflush(stdout);

    while (1) {
        pause();
    }

    return 0;
}
