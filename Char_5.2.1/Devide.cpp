/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Description:
 *			Devide BigNumber
 *    > Created Time: 2016-01-15 12:15:00
**/

BigNumber& BigNumber::devide(BigNumber &A,BigNumber &B)
{//Devide BigNumber
    // cout<<A<<B;
    release();
    if(A == 0){*this = A;return A;}
    BigNumber C,D,T,R;                       //T used to store the chars of C
    bool flag=false,open=false,end=false;    //R used to store the reverse-order chars of the result
    bool zero=false;
    int count = 0;
    C.dot_erase_copy(A);                     //a copy of A without '.'
    D.dot_erase_copy(B);                     //a copy of B without '.'
    if(A.dot < B.dot) C.push_front(B.dot-A.dot, '0');
    else if(A.dot > B.dot) D.push_front(A.dot-B.dot, '0');
    unsigned char *begin=C.first_free;
    --begin;                                 //let begin point to the first number
    T.push_front(*--begin);
    R.push_back('+');
    while(1){
        if(T > D){
            open = true; flag = false;
            BigNumber Sub,sub,Dis;
            Dis = 1;
            while(Sub.Calculate(D,Dis,'*') < T){
                ++Dis;
                sub = Sub;
            }
            if(Sub == T){
                R.push_back(Dis.val[0]);
                T.release();
            } else {
                --Dis;
                R.push_back(Dis.val[0]);
                T -= sub;
            }
        }else if(T == D){
            open=true;flag=false;
            R.push_back('1');
            T.release();
        }else{
            if((end || open) && flag)
                R.push_back('0');
            flag = true;
            if(begin != C.val){
                while(begin!=C.val&&T.first_free==T.val){
                    zero = true;
                    if(*--begin=='0') R.push_back('0');
                    else break;
                }
                if(begin != C.val){
                    if(zero) T.push_front(*begin);
                    else T.push_front(*--begin);
                    zero = false;
                }else break;
            }else{
                if(T.first_free == T.val) break;
                else if(count++ != ACCURACY){
                         T.push_front('0');
                         if(!end){
                             if((R.first_free-1) == R.val)
                                 R.push_back('0');
                             R.push_back('.');
                             end = true;
                         }
                     }else break;
            }
        }
    }
    reverse_copy(R);
}
