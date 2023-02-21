/*
Программе в аргументе командной строки передается имя файла с бинарными данными в Little-Endian.

Файл хранит внутри себя односвязный список элементов:

struct Item {
  int value;
  uint32_t next_pointer;
};
Поле value храние значение элемента списка, поле next_pointer - позицию в файле (в байтах), указывающую на следующий элемент. Признаком последнего элемента является значение next_pointer, равное 0.

Расположение первого элемента списка (если он существует) - строго в нулевой позиции в файле, расположение остальных - случайным образом.

Выведите на экран через пробел значения элементов в списке в текстовом представлении.

Для работы с файлом использовать только низкоуровневый ввод-вывод POSIX.

*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>

struct Item {
  int value;
  uint32_t next_pointer;
};


int main(int argc, char** argv) {
    int r = open(argv[1], O_RDONLY);
    
    while (1) {
        struct Item a;    
        ssize_t nread = read(r, &a, 8);

        if (nread != 8) {
            return 0;
        }
        //ssize_t nread1 = read(r, a.value, 4);
        //ssize_t nread2 = read(r, a.next_pointer, 4);
        //ssize_t nwrite = write(1, a.value, 4);
        printf("%d ", a.value);
    
        if (a.next_pointer == 0) {
            return 0;
        } else {
            off_t b = lseek(r, a.next_pointer, SEEK_SET);
        }
    }
}
