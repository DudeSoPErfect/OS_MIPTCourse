/* RU

Программе передается аргумент - пароль.

На стандартый поток ввода подаются данные, зашифрованные алгоритмом AES-256-CBC с солью. Для получения начального вектора и ключа из пароля и соли используется алгоритм SHA-256.

Необходимо расшифровать данные и вывести их на стандартый поток вывода.

Используйте API OpenSSL/LibreSSL. Запуск сторонних команд через fork+exec запрещен.

Отправляйте только исходный файл Си-программы с решением.

*/

/* ENG

The password argument is passed to the program.

Data encrypted with the AES-256-CBC algorithm with salt is fed to the standard input stream. The SHA-256 algorithm is used to obtain the initial vector and key from the password and salt.

It is necessary to decrypt the data and output it to a standard output stream.

Use the OpenSSL/LibreSSL API. Running third-party commands via fork+exec is prohibited.

Send only the source file of the C program with the solution.

*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/evp.h>

int main(int argc, char* argv[]) {

    char* pswd = argv[1];

    char  salt[8];
    char  data[16];
    char  vec [16];
    char  key [32];
    
    read(0, data, 16);
    memcpy(salt, data + 8, 8);

    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), salt, pswd, strlen(pswd), 1, key, vec);

    EVP_CIPHER_CTX*    x = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(x, EVP_aes_256_cbc(), NULL, key, vec);
    int size = EVP_CIPHER_CTX_block_size(x);

    char enc[size];
    char dec[size];

    while (1) {
        int n_read = read(0, enc, size);
        if (n_read <= 0) {
            break;
        }

        int n_write = 0;
        EVP_DecryptUpdate(x, dec, &n_write, enc, n_read);

        printf("%.*s", n_write, dec);
        fflush(stdout);

    }
    
    int n_write = 0;

    EVP_DecryptFinal_ex(x, dec, &n_write);
    printf("%.*s", n_write, dec);

    EVP_CIPHER_CTX_free(x);

    return 0;
}
