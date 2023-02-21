/*
Реализуйте на языке ассемблера armv8 (AArch64) функцию calculate, 
которая вычисляет значение выражения: R = ( A * B ) + ( C * D ),
где A, B, C, и D - это глобальные переменные типа uint64_t, объявленные во внешнем модуле компиляции, 
а R, - глобальная переменная типа uint64_t в текущем модуле компиляции.

*/

	.text
	.global calculate
	.global R

calculate:
	adr x0, A
	adr x1, B
	adr x2, C
	adr x3, D

	ldr x0, [x0]
	ldr x1, [x1]
	ldr x2, [x2]
	ldr x3, [x3]

	mul x0, x0, x1
	mul x2, x2, x3
	add x0, x0, x2

	adr x1, R
	str x0, [x1]
	ret
.bss

R:	.long 0
