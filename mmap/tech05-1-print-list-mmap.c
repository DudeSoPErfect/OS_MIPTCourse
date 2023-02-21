/* RU

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

/* ENG

The name of the file with binary data in Little-Endian is passed to the program in the command-line argument.

The file stores a single-linked list of elements inside itself:

struct Item {
 int value;
 uint32_t next_pointer;
};
The value field stores the value of the list item, the next_pointer field stores the position in the file (in bytes) indicating the next item. The sign of the last element is the next_pointer value equal to 0.

The location of the first element of the list (if it exists) is strictly in the zero position in the file, the location of the rest is random.

Display the values of the items in the list in a text view.

Use the memory mapping of the file contents.

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
