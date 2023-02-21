/* RU
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

/* ENG
The name of the file with binary data in Little-Endian is passed to the program in the command line argument.

The file stores a single-linked list of elements inside itself:

struct Item {
 int value;
 uint32_t next_pointer;
};
The value field stores the value of the list item, the next_pointer field stores the position in the file (in bytes) indicating the next item. The sign of the last element is the next_pointer value equal to 0.

The location of the first element of the list (if it exists) is strictly in the zero position in the file, the location of the rest is random.

Display the values of the items in the list in the text view separated by a space.

To work with the file, use only low-level POSIX I/O.

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

        printf("%d ", a.value);
    
        if (a.next_pointer == 0) {
            return 0;
        } else {
            off_t b = lseek(r, a.next_pointer, SEEK_SET);
        }
    }
}
