/*

Программа обрабатывать сигнал SIGRTMIN, вместе с которым передается некоторое беззнаковой 32-битное целое число N.

Все остальные сигналы нужно игнорировать.

При получении очередного сигнала нужно уменьшить это число на единицу и отправить его обратно тому процессу, который его послал (используя тот же самый сигнал).

Взаимодействие останавливается при получении значения N==0, после чего нужно корректно завершить работу.

Запрещается использовать signalfd, программа будет компилироваться без поддержки Linux-специфичных расширений.

*/

#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void handler(int n_sig, siginfo_t* inf, void* n) {
    if (inf->si_value.sival_int == 0) {
        exit(0);
    } else {
        inf->si_value.sival_int -= 1;
        sigqueue(inf->si_pid, n_sig, inf->si_value);
    }
}

int main() {

    struct sigaction sa = {
        .sa_sigaction = handler,
        .sa_flags = SA_SIGINFO,
    };
    
    sigset_t mask;
    sigprocmask(SIG_SETMASK, &mask, NULL);
    

    sigaction(SIGRTMIN, &sa, NULL);

    while (1) {
        pause();
    }


    return 0;
}
