/*
Реализуйте функцию

extern void normalize_path(char * path);
которая обрабатывает строки, представляющие пути к файлам (заканчиваются на любой символ, отличный от /) или каталогам (заканчиваются на символ /).

Функция должна привести текст в каноническую форму:

убрать дублирование подряд идущих символов /
обработать фрагменты ./ и ../
Запрещается использовать библиотечные строковые функции.

Запрещается выделять память под новую строку, - используйте уже существующую, аргумент не является константной строкой.

Используйте арифметику указателей; запрещается обращение к символам как к элементам массива.

Примеры
Входные данные
abrakadabra///abc
Результат работы
abrakadabra/abc
Входные данные
/var/log/../lib/./ejexec
Результат работы
/var/lib/ejexec

*/

#include <fcntl.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>

void normalize_path(char * path) {
	uint len = strlen(path);
	char *j = path;
	char *i = path;
	for (size_t k = 0; k < len; ++k) {
		if (i - path >= 2) {
			if (*i == '/' && *(i - 1) == '.' && *(i - 2) == '.') {
				j -= 4;
				while (*j != '/')
					--j;
			++j;
			++i;
			continue;
			}
		}
		if (i - path >= 1) {
			if (*i == '/' && *(i - 1) == '/') {
				++i;
				continue;
			} else if (*i == '/' && *(i - 1) == '.') {
				++i;
				--j;
				continue;
			}
		}

		*j = *i;
		++i;
		++j;
	}
	*j = '\0';
}
