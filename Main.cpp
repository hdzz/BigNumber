/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Description:
 *			BigNumber Calculator 
 *             Version 5.2.1
 *    > Created Time: 2016-01-17 15:51:33
**/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <memory>
#include <ctime>
using namespace::std;

#include "BigNumber Class.cpp"
#include "Overrided Operators.cpp"
#include "Preprocess.cpp"
#include "Compare BigNumbers.cpp"
#include "Plus.cpp"
#include "Minus.cpp"
#include "Multiply.cpp"
#include "Devide.cpp"
#include "Extended Operations.cpp"
#include "Other Operations.cpp"

#ifndef ACCURACY
#define  ACCURACY  1001
#endif

int main()
{
    BigNumber a("10000");
    a.factorial(a);                      // calculate 10000!
    cout << a << endl;
    
    BigNumber b("2");
    a.power(b, 10000);                   // calculate 2 ^ 10000
    cout << a << endl;
    
    a.circumference_ratio_BBP(1000);     // calculate Pi until 1000th bit after the dot
    cout << a < endl;
    
    BigNumber c("1234567898765432123456789.12345678987654321");
    BigNumber d("9876543212345678987654321.98765432123456789");
    BigNumber e;
    
    e = c + d; cout << e << endl;
    
    e = c - d; cout << e << endl;
    
    e = c * d; cout << e << endl;
    
    e = c / d; cout << e << endl;

    return 0;
}
