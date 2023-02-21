/* RU
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

/* ENG
Implement the function

extern void normalize_path(char * path);
which handles strings representing file paths (ending with any character other than /) or directories (ending with the / character).

The function should bring the text into canonical form:

remove duplication of consecutive characters /
process fragments ./ and ../
It is forbidden to use library string functions.

It is forbidden to allocate memory for a new line, - use an existing one, the argument is not a constant string.

Use pointer arithmetic; it is forbidden to refer to symbols as elements of an array.

Examples
Input data
of abrakadabra///abc
The result of the work
abrakadabra/abc
Input data
/var/log/../lib/./ejexec
Result of the work
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
