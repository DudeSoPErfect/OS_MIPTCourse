/* RU

Напишите программу на языке ассемблера armv8 (AArch64), которая читает со стандартного потока ввода последовательность символов, и выводит только те из них, которые являются десятичными цифрами от 0 до 9.

Можно использовать функции стандартной библиотеки языка Си: getchar_unlocked и putchar_unclocked.

В качестве точки входа можно считать функцию main.

*/

/* ENG

Write a program in the assembly language armv8 (AArch64), which reads a sequence of characters from the standard input stream, and outputs only those of them that are decimal digits from 0 to 9.

You can use the functions of the standard C library: getchar_unlocked and putchar_unclocked.

The main function can be considered as an entry point.

*/

	.text
	.global main

main:
	mov x29, x30

loop:

	bl getchar_unlocked

	cmn w0, #1
	beq end

	cmp w0, 47
	blt loop
	cmp w0, 57
	bgt loop


	bl putchar_unlocked

	b loop
end:	mov x30, x29
	mov x0, 0
	ret
