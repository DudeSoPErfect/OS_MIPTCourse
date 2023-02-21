/* RU
Программе на стандартном потоке ввода задается текст вида

GET /some_path/script.py?a=123&b=abrakadabra HTTP/1.1
Host: www.example.com

Обратите внимание на последнюю пустую строку.

Необходимо сформировать и вывести на стандартный поток вывода HTTP-ответ, который в случае успеха имеет вид:

HTTP/1.1 200 OK
[содержимое вывода скрипта]
Если указанный файл не существует, то необходимо вывести текст

HTTP/1.1 404 ERROR

Если файл существует, но не является выполняемым, то текст

HTTP/1.1 403 ERROR

У скрипта могут (но не обязаны) быть CGI-параметры, которые ему нужно передавать для обработки.

Необходимо реализовать поддержку только GET-запросов, но не POST.

Гарантируется, что входные данных содержат только синтаксически корректные запросы.

Необходимо реализовать поддержку следующих переменных окружения:

HTTP_HOST
QUERY_STRING
REQUEST_METHOD
SCRIPT_NAME
*/

/* ENG
The program is given a text of the form on the standard input stream

GET /some_path/script.py?a=123&b=abrakadabra HTTP/1.1
Host: www.example.com

Pay attention to the last empty line.

It is necessary to generate and output an HTTP response to the standard output stream, which, if successful, has the form:

HTTP/1.1 200 OK
[script output content]
If the specified file does not exist, then it is necessary to output the text

HTTP/1.1 404 ERROR

If the file exists but is not executable, then the text

HTTP/1.1 403 ERROR

The script may (but does not have to) have CGI parameters that it needs to pass for processing.

It is necessary to implement support for only GET requests, but not POST.

It is guaranteed that the input data contains only syntactically correct queries.

It is necessary to implement support for the following environment variables:

HTTP_HOST
QUERY_STRING
REQUEST_METHOD
SCRIPT_NAME
*/

#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>



int main() {

    char cmd[2048];
    char path[2048];
    char protocol[2048];
    char host[2048];
    char url[2048];

    scanf("%s %s %s", cmd, path, protocol);
    scanf("%s %s", host, url);

    char path_1[2048];
    char query[2048];

    sscanf(path, "%[^?]?%s", path_1, query);

    char real_path[2048] = ".";    
    if (path_1[0] == '/') {
        strcat(real_path, path_1);
    } else {
        strcat(real_path, "/");
        strcat(real_path, path_1);
    }
    
    char http_host[2048] = "HTTP_HOST=";
    char query_string[2048] = "QUERY_STRING=";
    char request_method[2048] = "REQUEST_METHOD=";
    char script_name[2048] = "SCRIPT_NAME=";

    strcat(http_host, url);
    putenv(http_host);
    
    strcat(query_string, query);
    putenv(query_string);

    strcat(request_method, cmd);
    putenv(request_method);

    strcat(script_name, real_path);
    putenv(script_name);

    if (access(real_path, F_OK) == -1) {
        printf("%s 404 ERROR\n\n", protocol);
    } else if (access(real_path, X_OK) == -1) {
        printf("%s 403 ERROR\n\n", protocol);
    } else {
        printf("%s 200 OK\n", protocol);
        fflush(stdout);
        execlp(real_path, real_path, NULL);
    }


    return 0;
}
