/* RU
Реализуйте на языке ассемблера armv8 (AArch64) функцию с меткой f, которая вычисляет значение выражения y=Ax2+Bx+C

Значения A, B, C и x хранятся, соответсвенно, в регистрах x0, x1, x2 и x3.

Результат вычисления выражения сохраните в регистре x0.

Все аргументы и значение выражения представимы 64-разрядными знаковыми целыми числами.

Использовать оперативную память запрещено, - можно использовать только регистры.

*/

/* ENG
Implement in the assembly language armv8 (AArch64) a function with the label f, which calculates the value of the expression y=Ax2+Bx+C

The values A, B, C and x are stored, respectively, in registers x0, x1, x2 and x3.

Save the result of the expression calculation in the x0 register.

All arguments and the value of the expression are represented by 64-bit signed integers.

It is forbidden to use RAM - only registers can be used.

*/

    .text
    .global f

f:
    mul x0, x0, x3
    mul x0, x0, x3
    mul x1, x1, x3
    add x0, x0, x1
    add x0, x0, x2
    ret
