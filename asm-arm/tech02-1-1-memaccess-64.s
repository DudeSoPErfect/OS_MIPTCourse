/* RU
Реализуйте на языке ассемблера armv8 (AArch64) функцию с сигнатурой:

int sum(int x0, size_t N, int *X)
Функция должна вычислять значение x0+∑xi, где 0≤i<N

Обратите внимание на то, что тип int имеет размер 32 бит, а тип size_t - 64 бит.
*/

/* ENG
Implement an armv8 (AArch64) assembly language function with the signature:

int sum(int x0, size_t N, int *X)
The function should calculate the value x0+∑xi, where 0≤i<N

Note that the int type has a size of 32 bits, and the size_t type is 64 bits.
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
	
