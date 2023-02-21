/* RU

На стандартном потоке ввода задается строка текста, которая состоит слова (последовательности непробельных символов), между которыми может быть произвольное количество пробельных символов, включая перевод строки.

Необходимо посчитать количество слов, если известно, что их не больше, чем 255, и вывести это значение на стандартный поток вывода.

Используйте создание новых процессов таким образом, чтобы каждый процесс читал не более одного слова, например, c помощью scanf("%s", ...).

Вывод результата возможен только из того процесса, который запущен самым первым (т.е. из исходной программы).

Итоговая программа должна вернуться с кодом возврата 0.

Размер каждого слова не превышает 4096 байт.

*/

/* ENG

On a standard input stream, a line of text is set, which consists of words (a sequence of non-whitespace characters), between which there can be an arbitrary number of whitespace characters, including a line feed.

It is necessary to count the number of words, if it is known that there are no more than 255, and output this value to the standard output stream.

Use the creation of new processes in such a way that each process reads no more than one word, for example, using scanf("%s", ...).

The output of the result is possible only from the process that was launched the very first (i.e. from the source program).

The final program should return with a return code of 0.

The size of each word does not exceed 4096 bytes.

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {

    char word[4096];
    size_t num = 0;
    while (scanf("%s", word) != EOF) {
        ++num;
        pid_t pid = fork();
        if (pid != 0) {
            waitpid(pid, NULL, 0);
          
            exit(0);
        }
        
    }



    printf("%ld", num);
    return 0;
}
