/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Description:
 *
 *    > Created Time: 2016-01-15 12:19:47
**/

BigNumber& BigNumber::Calculate(BigNumber &A,BigNumber &B,const char &c)
{//Preprocess two BigNumbers before calculating
    bool flag_a, flag_b;
    if(A >= 0) flag_a=true;else flag_a=false;
    if(c == '+'|| c == '*'|| c == '/') {if(B>=0) flag_b=true;else flag_b=false;}
    if(c == '-') {if(B >= 0) flag_b = false; else flag_b = true;}
    A.val[A.len-1]='+';B.val[B.len-1]='+';
    if(c == '+' || c == '-'){
             if(flag_a && flag_b) {plus(A, B);val[len-1]='+';}
             else if(!flag_a && !flag_b) {plus(A, B);val[len-1]='-';}
                  else if(A >= B){
                      if(!flag_a && flag_b) {minus(A, B);if(*this!=0) val[len-1]='-';}
                      else if(flag_a && !flag_b) {minus(A, B);val[len-1]='+';}
                  }else{
                       if(!flag_a && flag_b) {minus(B, A);val[len-1]='+';}
                       else if(flag_a && !flag_b) {minus(B, A);if(*this!=0) val[len-1]='-';}
                  }
    }else{
        if(c == '*') multiply(A, B);
        else devide(A, B);
        if(flag_a == flag_b) val[len-1]='+';
        else {if(*this != 0) val[len-1]='-';}
    }
    if(!flag_a) A.val[A.len-1]='-';
    if(c == '+' && !flag_b) B.val[B.len-1]='-';
    if(c == '-' && flag_b) B.val[B.len-1]='-';
    return *this;
}
