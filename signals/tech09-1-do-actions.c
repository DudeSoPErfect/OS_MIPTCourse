/*

Программа при запуске сообщает на стандартный поток вывода свой PID, после чего читает со стандартного потока вывода целое число - начальное значение, которое затем будет изменяться.

При поступлении сигнала SIGUSR1 увеличить текущее значение на 1 и вывести его на стандартный поток вывода.

При поступлении сигнала SIGUSR2 - умножить текущее значение на -1 и вывести его на стандартный поток вывода.

При поступлении одного из сигналов SIGTERM или SIGINT необходимо завершить свою работу с кодом возврата 0.

Семантика повединия сигналов (Sys-V или BSD) считается не определенной.

Не забывайте выталкивать буфер вывода.

*/

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

volatile int cur_val;

void handler (int n_sig) {
    if (n_sig == SIGUSR1) {
        printf("%d\n", ++cur_val);
        fflush(stdout); 
    } else if (n_sig == SIGUSR2) {
        cur_val *= (-1);
        printf("%d\n", cur_val);
        fflush(stdout); 
    } else if (n_sig == SIGTERM || n_sig == SIGINT) {
        exit(0);
    }
}




int main() {

    struct sigaction sa = {
        .sa_handler = handler,
        .sa_flags = SA_RESTART,
    };
    
    
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    printf("%d\n", getpid());
    fflush(stdout); 
    scanf("%d", &cur_val);

    while (1)
    {
        pause();
    }
    

    return 0;
}
