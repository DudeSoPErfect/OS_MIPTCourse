/* RU

Программе передаются два аргумента: имя файла, и текстовая строка для поиска.

Необходимо найти все вхождения строки в бинарном файле, используя отображение на память с помощью системного вызова mmap.

На стандартный поток вывода вывести список всех позиций (с нуля) в файле, где втречаются строка.

*/

/* ENG

Two arguments are passed to the program: the file name, and a text string to search for.

It is necessary to find all occurrences of a string in a binary file using memory mapping using the mmap system call.

Output a list of all positions (from scratch) in the file where the string is found to the standard output stream.

*/

#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {

    char* filename = argv[1];
    char* substr = argv[2];

    struct stat s;
    int file = open(filename, O_RDONLY);
    fstat(file, &s);

    char* file_vir_mem = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, file, 0);

    char* start = file_vir_mem;
    const char* end = file_vir_mem + s.st_size;
    size_t len_substr = strlen(substr);
    
    char* cur = start;

    while ((cur = memmem(cur, end - cur, substr, len_substr)) != NULL) {
        printf("%ld\n", cur - start);
        ++cur;
    }

    munmap((void*)file_vir_mem, s.st_size);
    close(file);

    return 0;
} 
