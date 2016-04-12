This is a repository for BigNumber Calculator.

Version 5.2.1

it can conduct add, subtract, multiply, divide operations,
basically it can calculate any number no matter how big or how small it is,
as long as there is enough memory to allocate.

For instance, you can initialize two BigNumbers like this,
BigNumber a("12345678987654321"), b("98765432123456789");
then you can input a = a + b; or a = a - b; or a = a * b; or a = a / b;

Apart from the basic operations,
you can calculate the factorial number, the fibonacci number, and the circumference_ratio.

For instance, a.factorial(10000),
then it will calculate the number 1 * 2 *... * 10000;
or a.fibonacci(10000), then it will calculate the 10000th fibonacci number;
or a.circumference_ratio_BBP(1000), then it will calculate Pi 1000bits after the dot.
