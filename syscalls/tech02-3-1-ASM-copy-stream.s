/*
Реализуйте на языке ассемблера x86_64 программу, которая копирует содержимое со стандартного потока ввода на стандартный поток вывода.

Использование стандартной библиотеки Си запрещено.

Точка входа в программу - функция _start.

*/

.intel_syntax noprefix

.global _start

.text
_start:
    loop:
        mov rax, 0
        mov rdi, 0
        mov rsi, offset buff
        mov rdx, 2000
        syscall   

        cmp rax, 0
        je end

        mov rdx, rax
        mov rax, 1
        mov rdi, 1
        mov rsi, offset buff
        syscall
        jmp loop
    end:

    mov rax, 60
    mov rdi, 0
    syscall

.bss
buff: .zero 2000
