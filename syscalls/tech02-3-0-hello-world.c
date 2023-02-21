/* RU
Реализуйте на языке Си программу, которая выводит "Hello, World!".

Использование стандартной библиотеки Си запрещено, единственная доступная функция - это syscall(2).

Точка входа в программу - функция _start.

Для использования syscall можно включить в текст программы следующее объявление:

long syscall(long number, ...);
*/

/* ENG
Implement a C program that outputs "Hello, World!".

The use of the C standard library is prohibited, the only available function is syscall(2).

The entry point to the program is the _start function.

To use syscall, you can include the following declaration in the program text:

long syscall(long number, ...);
*/

#include <unistd.h>
#include <sys/syscall.h>


long syscall(long number, ...);

int _start() {
    const char text[] = "Hello, World!\n";

    syscall(SYS_write, 1, text, sizeof(text)-1);
    syscall(SYS_exit);
}
