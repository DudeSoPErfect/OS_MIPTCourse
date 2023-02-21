/*

Напишите программу на языке ассемблера armv8 (AArch64), которая читает со стандартного потока ввода последовательность символов, и выводит только те из них, которые являются десятичными цифрами от 0 до 9.

Можно использовать функции стандартной библиотеки языка Си: getchar_unlocked и putchar_unclocked.

В качестве точки входа можно считать функцию main.

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
