/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Description:
 *			BigNumber   Version 5.2.1
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
#ifndef ACCURACY
#define  ACCURACY  101
#endif
#include "Devide.cpp"
#include "Extended Operations.cpp"
#include "Other Operations.cpp"

int main()
{
    clock_t start,end;
    start = clock();
    BigNumber a("16");
    BigNumber b("999999999"),c("1"),d;
    a.factorial(a);
    // a.power(a, 2);
    // a = a * b;
    // a.circumference_ratio_GLA(100, 7);
    // a.circumference_ratio_BBP(100);
    cout<<a;
    end = clock();
    cout<<(end - start)<<endl;
    return 0;
}
