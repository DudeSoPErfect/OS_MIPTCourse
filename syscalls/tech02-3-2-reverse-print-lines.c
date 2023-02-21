/* RU

Реализуйте на языке Си программу, которая читает со стандартного потока ввода текст, после чего выводит все строки текста в обратном порядке.

Использование стандартной библиотеки Си запрещено.

Точка входа в программу - функция _start.

Файл может не содержать перевода строки в конце.

*/

/* ENG

Implement a program in C that reads text from a standard input stream, and then outputs all lines of text in reverse order.

The use of the C standard library is prohibited.

The entry point to the program is the _start function.

The file may not contain a line feed at the end.

*/

#include <unistd.h>
#include <sys/syscall.h>
long syscall(long number, ...);

void add_mem(int size);

void _start() {
    int buff_size = 1000;
    long size = 0;
    long nread = 0;
    long buff = syscall(SYS_brk, 0);
    int counter = 0;
    while (1) {
        add_mem(buff_size);
        nread = syscall(SYS_read, 0, buff + buff_size * counter, buff_size);
        
        if (nread == 0) {
            break;
        }
        ++counter;
        size += nread;
    }


    if (size > 0 && ((char*)buff)[size-1] != '\n') {
        add_mem(1);
        ((char*)buff)[size] = '\n';
        size++;
    }   
    
    int index = size - 2;
    while (size > 0) {


        while (index - 1 >= 0 && ((char*)buff)[index-1] != '\n')
            --index;
        syscall(SYS_write, 1, buff + index, size - index);
        size = index--;
    }
    
    syscall(SYS_exit, 0);
}


void add_mem(int size) {
    long offset = syscall(SYS_brk, 0);
    syscall(SYS_brk, offset + size);
}
