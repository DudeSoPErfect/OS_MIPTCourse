/*

Программе на стандартном потоке ввода передаётся список имён файлов.

Необходимо посчитать суммарный размер в байтах всех файлов, которые являются регулярными.

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
#include <linux/limits.h>

int main(int argc, char** argv) {
	uint64_t number_bytes = 0;
	char buff[PATH_MAX];
	struct stat s;
	while (fgets(buff, PATH_MAX, stdin) != NULL) {
		buff[strlen(buff) - 1] = '\0';

		if (lstat(buff, &s) != 0) {
			continue;
		}

		if (S_ISREG(s.st_mode)) {
			number_bytes += s.st_size;
		}

	}

	printf("%lu", number_bytes);

	return 0;
}
