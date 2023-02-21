/*
Реализуйте на языке ассемблера armv8 (AArch64) функцию с сигнатурой:

int sum(int x0, size_t N, int *X)
Функция должна вычислять значение x0+∑xi, где 0≤i<N

Обратите внимание на то, что тип int имеет размер 32 бит, а тип size_t - 64 бит.
*/

	.text
	.global sum

sum:
	mov x3, 0
	eor x4, x4, x4
	b loop

//w0 - x0, x1 - N, w2 - *X, x3 - i, w4 -address

loop:
	cmp x3, x1
	beq end
	
	eor x4, x4, x4
	ldr w4, [x2, x3, lsl 2]
	add w0, w0, w4
	add x3, x3, 1
	
	b loop


end:	
	ret
	
