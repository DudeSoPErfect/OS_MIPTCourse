/* RU
Реализуйте программу на языке ассемблера armv8 (AArch64), которая вычисляет сумму двух целых 32-битных десятичных чисел.

Можно использовать функции стандартной библиотеки языка Си scanf и printf.

В качестве точки входа можно считать функцию main.

*/

/* ENG
Implement an armv8 (AArch64) assembly language program that calculates the sum of two 32-bit decimal integers.

You can use the functions of the standard C library scanf and printf.

The main function can be considered as an entry point.

*/


	.text
	.global main

main:
	mov x20, x30
	mov x19, x29

	adr x0, int
	adr x1, var1
	adr x2, var2
	bl scanf


	adr x1, var1
	ldr x1, [x1]
	adr x2, var2
        ldr x2, [x2]


	add w1, w1, w2
	adr x0, pr_int
	bl printf


	mov x30, x20
	mov x29, x19
	mov x0, 0
	ret


.data

int:	.string "%d %d"
pr_int:	.string "%d\n"
var1:	.long 0
var2:	.long 0
