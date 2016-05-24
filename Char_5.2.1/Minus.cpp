/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Description:
 *			Minus two BigNumbers
 *    > Created Time: 2016-01-15 12:12:09
**/

BigNumber& BigNumber::minus(BigNumber &A,BigNumber &B)
{//Minus two BigNumbers
    release();
    // cout << A << B;
    int len_a=0,len_b=0;
    cap=A.len+B.len-1;
    val=alloc.allocate(cap);
    first_free=val;
    alloc.construct(first_free,'0');
    if(A.dot>B.dot){
        int dis=A.dot-B.dot;
        while(dis--) alloc.construct(first_free++,A.val[len_a++]);
        if(!B.dot) {dot=first_free-val;alloc.construct(first_free++,A.val[len_a++]);}
        alloc.construct(first_free,'0');
    }else if(B.dot>A.dot){
              int dis=B.dot-A.dot;
              while(dis--){
                *first_free+=10-(B.val[len_b++]-'0');
                first_free++;
                alloc.construct(first_free,'0'-1);
              }
              if(!A.dot) {dot=first_free-val;alloc.construct(++first_free,'0'-1);*(first_free-1)=B.val[len_b++];}
          }
    while(len_a!=(A.len-1)||len_b!=(B.len-1)){
        if(A.val[len_a]=='.'){
            unsigned char x=*first_free;
            alloc.construct(first_free++,A.val[len_a]);
            dot=first_free-val-1;
            alloc.construct(first_free,x);
            len_a++;len_b++;
        }
        if(len_a!=(A.len-1)) {(*first_free)+=A.val[len_a++]-'0';}
        if(len_b!=(B.len-1)) {(*first_free)-=B.val[len_b++]-'0';}
        if((*first_free-'0')<0){
            *first_free+=10;
            first_free++;
            alloc.construct(first_free,'0'-1);
        }else {first_free++;alloc.construct(first_free,'0');}
    }
    while(*first_free=='0'&&first_free!=val&&*(first_free-1)!='.') alloc.destroy(first_free--);
    alloc.construct(++first_free,'+');
    len=first_free+1-val;
    first_free=val+len;
    return *this;
}
