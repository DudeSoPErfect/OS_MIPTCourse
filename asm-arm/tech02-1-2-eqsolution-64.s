* RU
*Реализуйте на языке ассемблера armv8 (AArch64) функцию solve, с прототипом

*int solve(int64_t A, int B, int C, int D);
      
*которая находит минимальное значение x ∈[0,254], которое является одним из корней уравнения: Ax3+Bx2+Cx+D=0.

*Все аргументы и значение выражения представимы 32-разрядными знаковыми целыми числами.

*Гарантируется, что на тестовых данных существует целочисленное решение.
*/

* ENG
*Implement the solve function in the armv8 (AArch64) assembly language, with a prototype

*int solve(int64_t A, int B, int C, int D);
 
*which finds the minimum value x ∈[0,254], which is one of the roots of the equation: Ax3+Bx2+Cx+D=0.

*All arguments and the value of the expression are represented by 32-bit signed integers.

*It is guaranteed that an integer solution exists on the test data.
*


	.text
	.global solve
solve:
	mov x5, 0
	
	sxtw x1, w1
	sxtw x2, w2
	sxtw x3, w3

	b loop
solve_end:	ret	
loop:	
	
	mul x6, x5, x5
	mul x6, x6, x5 		// x6 = x5^3
	mul x6, x0, x6		// x6 = a * x5^3

	mul x7, x5, x5
	mul x7, x1, x7		// x7 = b * x5^2

	mul x8, x2, x5		// x8 = c * x5
	
	
	add x6, x6, x7		// x6 += x7
	add x6, x6, x8 		// x6 += x8
	add x6, x6, x3		// x6 += d

	cmp x6, 0
	beq end	

	add x5, x5, 1
	cmp x5, 255
	bne loop


end:	mov x0, x5
	beq solve_end
