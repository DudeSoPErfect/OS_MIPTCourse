/* RU
Программе на стандартном потоке ввода передаётся список имён файлов.

Необходимо вывести на стандартный поток вывода имена "неправильных" выполняемых файлов, 
то есть файлов, которые отмечены как исполняемые, но при этом они заведомо не могут быть выполнены в системе 
(не начинаются с корректной строки #!, содержащей запускаемый интерпретатор, и не являются ELF-файлами).

*/

/* ENG
A list of file names is passed to the program on the standard input stream.

It is necessary to output the names of "incorrect" executable files to the standard output stream, 
that is, files that are marked as executable, but at the same time they obviously cannot be executed in the system 
(do not start with the correct string #! containing the interpreter to be run, and are not ELF files).

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
	char buff[PATH_MAX];
	char text[PATH_MAX];
	struct stat s;
	while (fgets(buff, PATH_MAX, stdin) != NULL) {
		buff[strlen(buff) - 1] = '\0';
		lstat(buff, &s);

		if (s.st_mode & S_IXUSR) {

				int file_d = open(buff, O_RDONLY);
				uint number_bytes = 0;
				uint i = 0;
				uint good = 0;
				uint cap = PATH_MAX;
				while ((number_bytes = read(file_d, text + i, cap)) != 0) {
					if (number_bytes == -1) {
						good = 1;
						break;
					}
					i += number_bytes;
					cap -= number_bytes;
				}


				if (good) {
					printf("%s ", buff);
					continue;
				}
				if (text[0] == '#' && text[1] == '!') {
					text[strcspn(text, " \n")] = 0;
	                                if (access(text+2, X_OK | F_OK) != -1)
                                                continue;
				}
				//printf("%d %d %d %d\n", text[0], text[1], text[2], text[3]);
				if (text[0] == 0x7f && text[1] == 'E' && text[2] == 'L' && text[3] == 'F') {
                                    	continue;
				}
				printf("%s ", buff);
		}

	}




	return 0;
}
