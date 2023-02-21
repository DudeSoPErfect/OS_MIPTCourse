/* RU

Программе на стандартном потоке ввода передаётся список имён файлов.

Если файл является символической ссылкой, то нужно вывести абсолютное имя того файла, на который эта ссылка указывает.

Если файл является регулярным, то необходимо создать символическую ссылку в текущем каталоге, приписав в названии файла префикс link_to_.

*/

/* ENG

A list of file names is passed to the program on the standard input stream.

If the file is a symbolic link, then you need to output the absolute name of the file to which this link points.

If the file is regular, then you need to create a symbolic link in the current directory by assigning the prefix link_to_ in the file name.

*/

#define _FILE_OFFSET_BITS 64

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

int main(int argc, char** argv) {
	char buff[PATH_MAX];
	char path[PATH_MAX];
	char prefix[20] = "link_to_";
	struct stat s;
	while (fgets(buff, PATH_MAX, stdin) != NULL) {
		buff[strlen(buff) - 1] = '\0';

		lstat(buff, &s);
		if (S_ISLNK(s.st_mode)) {
				realpath(buff, path);
				printf("%s\n", path);
		} else if (S_ISREG(s.st_mode)) {
				char* result = (char*)calloc(strlen(prefix) + strlen(buff) + 1, sizeof(char));
				memcpy(result, prefix, strlen(prefix));
				memcpy(result + strlen(prefix), buff, strlen(buff) + 1);
				realpath(buff, path);
				symlink(path, result);
				free(result);
		}
	}

	return 0;
}
