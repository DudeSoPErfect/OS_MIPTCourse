/* RU

Программе на стандартный поток ввода задается некоторое арифметическое выражение в синтаксисе языка python3.

Необходимо вычислисть это выражение, и вывести результат.

Использовать дополнительные процессы запрещено.

*/

/* ENG

The program is assigned some arithmetic expression in the syntax of the python3 language to the standard input stream.

It is necessary to calculate this expression, and output the result.

It is forbidden to use additional processes.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    char buff[4096] = {0};
    scanf("%[^\n]s", buff);
    char a[5002] = "print(";
    char b[] = ")";
    strcat(a, buff);
    strcat(a, b);
    execlp("python3", "proc", "-c", a, NULL);
    return 0;
}
