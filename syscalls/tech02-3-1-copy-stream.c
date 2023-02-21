/*
Реализуйте на языке Си программу, которая копирует содержимое потока ввода на поток вывода.

Использование стандартной библиотеки Си запрещено, единственная доступная функция - это syscall(2).

Точка входа в программу - функция _start.

Для использования syscall можно включить в текст программы следующее объявление:

long syscall(long number, ...);
*/

#include <unistd.h>
#include <sys/syscall.h>

long syscall(long number, ...);

int _start() {
	while (1) {
		char buff[500];
		long nread=syscall(SYS_read, 0, buff, sizeof(buff)-1);
		if (nread != 0) {
			syscall(SYS_write, 1, buff, nread);
		} else {
			syscall(SYS_exit, 0);
		}
	}
}
