/*

Программе передаются три аргумента: имя файла, положительное целое число N - размер квадратной матрицы, и положительное число W - ширина клетки матицы в символах.

Необходимо в указанном файле сформировать текст, который содержит матрицу, состоящую из чисел от 1 до N2, таким образом, чтобы числа заполняли её по спирали, по часовой стрелке.

Числа должны быть выровнены по правой границе ячейки матрицы.

Используйте mmap для записи в файл.

Можно использовать функции форматного вывода для преобразования числа в строку.

Примеры
Входные данные
./solution out.txt 5 5
Результат работы в файле out.txt
    1    2    3    4    5
   16   17   18   19    6
   15   24   25   20    7
   14   23   22   21    8
   13   12   11   10    9
  
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

int how_zeroes_in_num(uint num) {
    uint zeroes = 0;
    while (num > 0) {
        num /= 10;
        ++zeroes;
    }
    return zeroes;
}


int main(int argc, char** argv) {
    char* file_name = argv[1];
    uint N = atoi(argv[2]);
    uint W = atoi(argv[3]);

    uint** matr = (uint**)calloc(N, sizeof(uint*));
    for (size_t i = 0; i < N; i++)
        matr[i] = (uint*)calloc(N, sizeof(uint));

    int Ibeg = 0, Ifin = 0, Jbeg = 0, Jfin = 0;
    
    uint num = 1;
    size_t i = 0;
    size_t j = 0;

    while (num <= N * N){
        matr[i][j] = num++;
        if (i == Ibeg && j < N - Jfin - 1)
            ++j;
        else if (j == N - Jfin - 1 && i < N - Ifin - 1)
            ++i;
        else if (i == N - Ifin - 1 && j > Jbeg)
            --j;
        else
            --i;

        if ((i == Ibeg + 1) && (j == Jbeg) && (Jbeg != N - Jfin - 1)){
            ++Ibeg;
            ++Ifin;
            ++Jbeg;
            ++Jfin;
        };
    }

    int file = open(file_name, O_RDWR | O_CREAT, 0666);
    size_t file_size = N * N * W + N * N; 
    ftruncate(file, file_size);

    char* file_vir_mem = mmap(NULL, file_size, PROT_WRITE | PROT_READ, MAP_SHARED, file, 0);
    

    size_t c = 0;
    for (size_t i = 0; i < N; i++){
        for (size_t j = 0; j < N; j++) {
            for (size_t k = 0; k < W - how_zeroes_in_num(matr[i][j]); k++) {
                sprintf(file_vir_mem + c, " ");
                ++c;
            }
            sprintf(file_vir_mem + c, "%d", matr[i][j]);
            c += how_zeroes_in_num(matr[i][j]);
            
            if (j != N - 1) {
                sprintf(file_vir_mem + c, "\t");
                c+=1;
            }
        }   
        sprintf(file_vir_mem + c, "\n");
        ++c;
    }
    munmap(file_vir_mem, file_size);
    close(file);


    return 0;
}
