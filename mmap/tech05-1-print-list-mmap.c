/*

Программе в аргументе командной строки передается имя файла с бинарными данными в Little-Endian.

Файл хранит внутри себя односвязный список элементов:

struct Item {
  int value;
  uint32_t next_pointer;
};
Поле value храние значение элемента списка, поле next_pointer - позицию в файле (в байтах), указывающую на следующий элемент. Признаком последнего элемента является значение next_pointer, равное 0.

Расположение первого элемента списка (если он существует) - строго в нулевой позиции в файле, расположение остальных - случайным образом.

Выведите на экран значения элементов в списке в текстовом представлении.

Используйте отображение содержимого файла на память.

*/

#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

struct Item {
  int value;
  uint32_t next_pointer;
};


int main(int argc, char** argv) {
    int file = open(argv[1], O_RDONLY);
    struct stat s;
    fstat(file, &s);
    
    struct Item* file_vir_mem = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, file, 0);
    struct Item* cur = file_vir_mem;

    while (1) {
        struct Item* a = cur;    

        if (s.st_size < 8)
            break;

        printf("%d ", a->value);
    
        if (a->next_pointer == 0) {
            break;
        } else {
            cur = (struct Item*)(((char*)file_vir_mem) + a->next_pointer);
        }
    }

    munmap(file_vir_mem, s.st_size);
    close(file);
    return 0;
}
