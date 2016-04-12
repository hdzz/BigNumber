/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Description:
 *          factorial
 *          power
 *          fibonacci
 *          circumference_ratio BBP
 *          circumference_ratio GLA
 *    > Created Time: 2016-01-15 12:17:38
**/

BigNumber& BigNumber::factorial(BigNumber &A)
{//Calculate the factorial number
    BigNumber B("1"),C("1"),D("1");
    if(A == 0 || A == 1) {*this = 1; return *this;}
    int count = Convert_to_i(A);
    while(count > 5){
        B *= count;
        --count;
        C *= count;
        --count;
        D *= count;
        --count;
    }
    for(; count > 1; --count) B *= count;
    B *= C;
    *this = B * D;
    return *this;
}

BigNumber& BigNumber::power(BigNumber &A, int num)
{//Calculate the power number
    if(A == 0 || num == 0) {*this = 1;return *this;}
    BigNumber B,C("1");
    B = A;
    int left = num % 10;
    num /= 10;
    for(int i=1; i < 10 && num; ++i)
        A *= B;
    while(num--) C *= A;
    for(; left > 0; --left)
        C *= B;
    *this = C;
    return *this;
}

BigNumber& BigNumber::fibonacci(int num)
{//Calculate the fibonacci number
    BigNumber a("1");
    BigNumber b("1");
    bool flag = (num % 2) ? true : false;
    if(num <= 2) {*this = a;return *this;}
    num=(num - 1)/2;
    while(num--){
        a += b;
        b += b;
    }
    if(flag) *this = a;
    else *this = b;
    return *this;
}

BigNumber& BigNumber::square_root(BigNumber &A)
{//Calculate square_root
 //X = 1/2(x + A/x)
    int count = 0;
    BigNumber x;
    x = A / 2;
    while(count < 5){
        BigNumber y;
        y = A / x;
        x += y;
        x /= 2;
        ++count;
    }
    *this = x;
    return *this;
}

BigNumber& BigNumber::circumference_ratio_BBP(int num)
{//Calculate Pi
 //π = 1/16^k (4/(8k+1) - 2/(8k+4) - 1/(8k+5) -1/(8k+6))  (BBP)
    *this = 0;
    BigNumber quar("4"),doub("2"),per("1");
    int k = 0;
    while(k < num){
        BigNumber S("16");
        S.power(S,k);
        BigNumber powe;
        powe = per / S;
        int di = k << 3;
        BigNumber fir = di + 1;
        BigNumber sec = di + 4;
        BigNumber thr = di + 5;
        BigNumber fou = di + 6;
        fir = quar / fir;
        sec = doub / sec;
        thr = per / thr;
        fou = per / fou;
        fir -= sec;
        fir -= thr;
        fir -= fou;
        fir *= powe;
        *this += fir;
        ++k;
    }
    cut_tail(num);
    return *this;
}

BigNumber& BigNumber::circumference_ratio_GLA(int num, int times)
{//Calculate Pi
    BigNumber a("1"),b("1"),c("2"),t("0.25");
    int p = 1;
    c.square_root(c);
    b /= c;
    int count = 0;
    while(count < times){
        BigNumber a0;
        a0 = a;
        a += b;
        a /= 2;
        b *= a0;
        b.square_root(b);
        a0 -= a;
        a0.power(a0,2);
        a0 *= p;
        t -= a0;
        p *= 2;
        ++count;
        // cout<<a<<b;
        // system("pause");
    }
    *this = a + b;
    power(*this,2);
    t *= 4;
    *this /= t;
    cut_tail(num);
    return *this;
}
