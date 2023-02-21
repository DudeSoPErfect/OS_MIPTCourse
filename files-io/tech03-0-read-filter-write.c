/*
Программе в аргументах командной строки передаются три имени файла. Первый аргумент - входной файл, два остальных - выходные.

Реализуйте программу, которая читает символы из первого файла, во второй файл записывает только цифры, а в третий - всё остальное.

Разрешается использовать только низкоуровневый ввод-вывод POSIX.

Если входной файл не существует, то нужно завершить работу с кодом 1.

Если не возможно создать один из выходных файлов, то завершить работу с кодом 2.

При возникновении других ошибок ввода-вывода - завершить работу с кодом 3.

*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char** argv) {
	int r = open(argv[1], O_RDONLY);
	int w1 = open(argv[2], O_RDWR | O_CREAT, 0666);
	int w2 = open(argv[3], O_RDWR | O_CREAT, 0666);
	if (w1 == -1 || w2 == -1)
		return 2;
	if (r == -1)
		return 1;
	while (1) {
		char buff[500];
		ssize_t nread = read(r, buff, sizeof(buff)-1);
		if (nread == -1) {
			return 3;
		} else if (nread == 0) {
			return 0;
		} else {
			for (size_t i = 0; i < nread; i++) {
				if (buff[i] >= '0' && buff[i] <= '9') {
					ssize_t nwrite = write(w1, buff + i, 1);
					if (nwrite != 1) {
						return 3;
					}
				} else {
					ssize_t nwrite = write(w2, buff + i, 1);
					if (nwrite != 1) {
						return 3;
					}
				}
			}
		}
	}
}
