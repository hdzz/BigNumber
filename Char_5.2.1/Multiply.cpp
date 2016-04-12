/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Description:
 *			Multiply two BigNumbers
 *    > Created Time: 2016-01-15 12:12:53
**/

BigNumber& BigNumber::multiply(BigNumber &A,BigNumber &B)
{//Multiply two BigNumbers
    release();
    allocator<unsigned char> all;
    cap = A.len + B.len - 1;
    val = alloc.allocate(cap);
    first_free=val;
    unsigned char *begin = all.allocate(cap);
    unsigned char *ori = begin,*end = begin;
    int count = 0,len_b = 0;
    dot = A.dot + B.dot;
    uninitialized_fill_n(ori,cap,'0');
    ori = begin;
    while(len_b != (B.len-1)){
        if(B.val[len_b]=='.') {++len_b; continue;}
        int len_a = 0;
        end = begin;
        while(len_a != (A.len-1)){
            unsigned int num = (B.val[len_b] - '0')*(A.val[len_a] - '0');
            *end += num % 10;
            num/=10;
            if((*end-'0')>=10){
                *end-=10;
                ++num;
            }
            if(num){
                *++end+=num;
                if((*end-'0') >= 10){
                    *end -= 10;
                    *(end+1) += 1;
                }
            }else ++end;
            if(A.val[++len_a]=='.') ++len_a;
        }
        ++len_b;
        alloc.construct(first_free++, *begin++);
        if(++count==dot) alloc.construct(first_free++,'.');
    }
    while(begin!=end){
        alloc.construct(first_free++,*begin++);
        if(++count==dot) alloc.construct(first_free++,'.');
    }
    alloc.construct(first_free, *begin);
    unsigned char *over = val + cap;
    while(over != first_free) alloc.destroy(--over);
    while(*first_free == '0' && first_free != val && *(first_free-1) != '.') alloc.destroy(first_free--);
    len = first_free + 2 - val;
    first_free = val + len;
    begin = ori + cap;
    while(begin != ori) alloc.destroy(--begin);
    alloc.deallocate(begin, cap);
    return *this;
}
