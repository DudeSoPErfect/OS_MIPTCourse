/* RU
Задача, аналогичная print-list-posix, но требуется решение под Windows.

Программе в аргументе командной строки передается имя файла с бинарными данными в Little-Endian.

Файл хранит внутри себя односвязный список элементов:

struct Item
{
  int value;
  uint32_t next_pointer;
};
Поле value храние значение элемента списка, поле next_pointer - позицию в файле (в байтах), указывающую на следующий элемент. Признаком последнего элемента является значение next_pointer, равное 0.

Расположение первого элемента списка (если он существует) - строго в нулевой позиции в файле, расположение остальных - случайным образом.

Выведите на экран значения элементов в списке в текстовом представлении.

Для работы с файлом использовать только низкоуровневый ввод-вывод WinAPI.

*/

/* ENG
A task similar to print-list-posix, but a Windows solution is required.

The name of the file with binary data in Little-Endian is passed to the program in the command-line argument.

The file stores a single-linked list of elements inside itself:

struct Item
{
 int value;
 uint32_t next_pointer;
};
The value field stores the value of the list item, the next_pointer field stores the position in the file (in bytes) indicating the next item. The sign of the last element is the next_pointer value equal to 0.

The location of the first element of the list (if it exists) is strictly in the zero position in the file, the location of the rest is random.

Display the values of the items in the list in a text view.

To work with the file, use only low-level WinAPI I/O.

*/

#define _FILE_OFFSET_BITS 64

#include <windows.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    int value;
    uint32_t next_pointer;
} Item;


int main(int argc, char** argv)
{

    const char* r = argv[1];

    HANDLE file = CreateFileA(r, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    OVERLAPPED b = {0};

    Item a;
    while (1) {

        if (!ReadFile(file, &a, sizeof(Item), NULL, &b)) 
            break;
        
    
        printf("%d ", a.value);


        b.Offset = a.next_pointer;
        if (b.Offset == 0)
            break;

    }

    CloseHandle(file);
    return 0;    

}
