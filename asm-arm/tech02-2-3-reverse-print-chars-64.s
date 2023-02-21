/*
Реализуйте программу на языке ассемблера armv8 (AArch64), которая считывает символы со стандартного потока ввода, а затем выводит их в обратном порядке.

Можно использовать функции стандартной библиотеки языка Си: fgetc, fputc, getchar_unlocked, putchar_unlocked, realloc и free.

В качестве точки входа можно считать функцию main.
*/


	.text
	.global main


main:

	mov x29, x30
	mov x1, 1028 //размер инта * количество чисел
	mov x0, 0 //чтобы реаллок работал как каллок

	bl realloc


	mov x7, x0 //realloc pointer
	mov x10, 0  //index
	mov x11, 256 //last index

	adrp x19, stdin


	b loop
loop:
	ldr x0, [x19, #:lo12:stdin]
	bl fgetc

	mov w12, w0 //save char
	cmn w0, #1
	beq end

	cmp x10, x11
	bge mem_inc

	b next
next:
	str w12, [x7, x10, lsl 2]
	add x10, x10, 1
	b loop





mem_inc:
	lsl x1, x11, 3
	mov x0, x7
	bl realloc
	mov x7, x0
	lsl x11, x11, 1
	b next

end:
	sub x10, x10, #1
	cmp x10, 0
	blt freee

	adrp x20, stdout

pr_out:
	ldr x1, [x20, #:lo12:stdout]

	ldr w0, [x7, x10, lsl 2]
	bl fputc

	sub x10, x10, #1
	tbz w10, #31, pr_out
freee:
	mov x0, x7
	bl free

	mov x0, 0
	mov x30, x29
	ret
