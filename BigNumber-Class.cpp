/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Description:
 *			BigNumber Class
 *    > Created Time: 2016-01-15 12:01:06
**/

//            Initialize Method
//     BigNumber\string\int\long long

class BigNumber
{
    friend char Compare(const BigNumber&,const BigNumber&);
    friend int Convert_to_i(const BigNumber&);
    friend ostream& operator<<(ostream&,const BigNumber&);
    friend BigNumber operator%(BigNumber&,const long long);
    public:
    	BigNumber(unsigned char *empty=NULL,int i=0):val(empty),first_free(empty),cap(i),len(i),dot(i) {}
        BigNumber(const BigNumber &A) {*this = A;}
        BigNumber(const string &str);
        BigNumber(int);
        BigNumber(long long);
        BigNumber& operator=(const BigNumber&);
        BigNumber& operator=(int);
        BigNumber& operator=(long long);
        BigNumber& operator-() {if(len!=2||val[0]!='0') val[len-1]=val[len-1]=='+'?'-':'+';return *this;}
        BigNumber& operator++() {BigNumber A,Int("1");A=*this;Calculate(A,Int,'+');return *this;}
        BigNumber& operator--() {BigNumber A,Int("1");A=*this;Calculate(A,Int,'-');return *this;}
        BigNumber operator++(int) {BigNumber A,Int("1");A=*this;Calculate(A,Int,'+');return A;}
        BigNumber operator--(int) {BigNumber A,Int("1");A=*this;Calculate(A,Int,'-');return A;}
        BigNumber& operator+=(BigNumber &A) {BigNumber B;B=*this;Calculate(B,A,'+');return *this;}
        BigNumber& operator-=(BigNumber &A) {BigNumber B;B=*this;Calculate(B,A,'-');return *this;}
        BigNumber& operator*=(BigNumber &A) {BigNumber B;B=*this;Calculate(B,A,'*');return *this;}
        BigNumber& operator/=(BigNumber &A) {BigNumber B;B=*this;Calculate(B,A,'/');return *this;}
        BigNumber& operator+=(long long num) {BigNumber B,C(num);B=*this;Calculate(B,C,'+');return *this;}
        BigNumber& operator-=(long long num) {BigNumber B,C(num);B=*this;Calculate(B,C,'-');return *this;}
        BigNumber& operator*=(long long num) {BigNumber B,C(num);B=*this;Calculate(B,C,'*');return *this;}
        BigNumber& operator/=(long long num) {BigNumber B,C(num);B=*this;Calculate(B,C,'/');return *this;}
        void release();
        void push_front(const unsigned char);
        void push_front(int,const unsigned char);
        void push_back(const unsigned char);
        BigNumber& reverse_copy(BigNumber&);
        BigNumber& dot_erase_copy(BigNumber&);
        void cut_tail(int);
        BigNumber& Calculate(BigNumber&,BigNumber&,const char&);
        BigNumber& plus(BigNumber&,BigNumber&);
        BigNumber& minus(BigNumber&,BigNumber&);
        BigNumber& multiply(BigNumber&,BigNumber&);
        BigNumber& devide(BigNumber&,BigNumber&);
        BigNumber& factorial(BigNumber&);
        BigNumber& power(BigNumber&,int);
        BigNumber& fibonacci(int);
        BigNumber& square_root(BigNumber&);
        BigNumber& circumference_ratio_BBP(int);
        BigNumber& circumference_ratio_GLA(int, int);
        ~BigNumber();
    private:
        allocator<unsigned char> alloc;
        unsigned char *val;
        unsigned char *first_free;
        int cap;
        int len;
        int dot;
};

inline BigNumber::~BigNumber()
{//Destructor
    if(val){
        for(;first_free!=val;)
            alloc.destroy(--first_free);
        alloc.deallocate(val,cap);
    }
    val=first_free=NULL;
    cap=0;
    dot=len=0;
}

BigNumber::BigNumber(const string &str)
{//Initialize BigNumber with string
    cap=str[0]=='-'?str.size():(str.size()+1);
    val=alloc.allocate(cap);
    first_free=val;
    len=str.size();
    dot=0;
    int i=str.size()-1;
    do{
        if(str[i]=='.') dot=str.size()-i-1;
        alloc.construct(first_free++,str[i]);
    }while(i--);
    if(str[0]!='-') {alloc.construct(first_free++,'+');len++;}
}

BigNumber::BigNumber(int num)
{//Initialize BigNumber with integer
    cap=11;
    dot=0;
    val=alloc.allocate(cap);
    first_free=val;
    bool flag=true;
    int e=num%10;
    num/=10;
    if(e<0) e=-e;
    if(num<0) {flag=false;num=-num;}
    alloc.construct(first_free++,e+48);
    while(num){
        e=num%10;
        num/=10;
        alloc.construct(first_free++,e+48);
    }
    if(flag) alloc.construct(first_free++,'+');
    else alloc.construct(first_free++,'-');
    len=first_free-val;
}

BigNumber::BigNumber(long long num)
{//Initialize BigNumber with long long integer
    cap=21;
    dot=0;
    val=alloc.allocate(cap);
    first_free=val;
    bool flag=true;
    long long e=num%10;
    num/=10;
    if(e<0) e=-e;
    if(num<0) {flag=false;num=-num;}
    alloc.construct(first_free++,e+48);
    while(num){
        e=num%10;
        num/=10;
        alloc.construct(first_free++,e+48);
    }
    if(flag) alloc.construct(first_free++,'+');
    else alloc.construct(first_free++,'-');
    len=first_free-val;
}

BigNumber& BigNumber::operator=(int num)
{//Copy an integer
    release();
    cap=11;
    val=alloc.allocate(cap);
    first_free=val;
    bool flag=true;
    int e=num%10;
    num/=10;
    if(e<0) e=-e;
    if(num<0) {flag=false;num=-num;}
    alloc.construct(first_free++,e+48);
    while(num){
        e=num%10;
        num/=10;
        alloc.construct(first_free++,e+48);
    }
    if(flag) alloc.construct(first_free++,'+');
    else alloc.construct(first_free++,'-');
    len=first_free-val;
    dot=0;
}

BigNumber& BigNumber::operator=(long long num)
{//Copy a long long integer
    release();
    cap=21;
    val=alloc.allocate(cap);
    first_free=val;
    bool flag=true;
    long long e=num%10;
    num/=10;
    if(e<0) e=-e;
    if(num<0) {flag=false;num=-num;}
    alloc.construct(first_free++,e+48);
    while(num){
        e=num%10;
        num/=10;
        alloc.construct(first_free++,e+48);
    }
    if(flag) alloc.construct(first_free++,'+');
    else alloc.construct(first_free++,'-');
    len=first_free-val;
    dot=0;
}

BigNumber& BigNumber::operator=(const BigNumber &A)
{//Copy a BigNumber
    int newcap = A.len;
    unsigned char *newval = alloc.allocate(newcap);
    unsigned char *newfirst_free = newval;
    int newlen = A.len;
    int newdot = A.dot;
    int count = 0;
    while(count < A.len) alloc.construct(newfirst_free++,A.val[count++]);
    release();
    cap=newcap;
    val=newval;
    first_free=newfirst_free;
    len=newlen;
    dot=newdot;
    return *this;
}

inline void BigNumber::release()
{//Free BigNumber space
    if(first_free){
        while(first_free != val) alloc.destroy(--first_free);
        alloc.deallocate(val,cap);
    }
    val=first_free=NULL;
    cap=len=dot=0;
}

void BigNumber::push_front(const unsigned char c)
{//Push a character front
    if(!len){
        cap=len=2;
        val=alloc.allocate(cap);
        first_free=val;
        dot=0;
        alloc.construct(first_free++,c);
        alloc.construct(first_free++,'+');
    }else{
        int newcap=len+1;
        int newdot=dot;
        unsigned char *newval=alloc.allocate(newcap);
        unsigned char *newfirst_free=newval;
        unsigned char *oldval=val;
        alloc.construct(newfirst_free++,c);
        while(oldval!=first_free)
            alloc.construct(newfirst_free++,*oldval++);
        release();
        val=newval;
        first_free=newfirst_free;
        cap=len=newcap;
        dot=newdot;
    }
}

void BigNumber::push_front(int num,const unsigned char c)
{//Push multiple characters front
    if(!len){
        cap=len=num+1;
        val=alloc.allocate(cap);
        first_free=val;
        dot=0;
        while(num--) alloc.construct(first_free++,c);
        alloc.construct(first_free++,'+');
    }else{
        int newcap=len+num;
        int newdot=dot;
        unsigned char *newval=alloc.allocate(newcap);
        unsigned char *newfirst_free=newval;
        unsigned char *oldval=val;
        while(num--) alloc.construct(newfirst_free++,c);
        while(oldval!=first_free)
            alloc.construct(newfirst_free++,*oldval++);
        release();
        val=newval;
        first_free=newfirst_free;
        cap=len=newcap;
        dot=newdot;
    }
}

void BigNumber::push_back(const unsigned char c)
{//Push a character back
    if(!len||len>=cap){
        int newcap=cap?(2*cap):2;
        int newdot=dot;
        unsigned char *newval=alloc.allocate(newcap);
        unsigned char *newfirst_free=newval;
        unsigned char *oldval=val;
        while(oldval!=first_free) alloc.construct(newfirst_free++,*oldval++);
        alloc.construct(newfirst_free++,c);
        release();
        val=newval;
        first_free=newfirst_free;
        len=first_free-val;
        cap=newcap;
        dot=newdot;
    }else{alloc.construct(first_free++,c);len++;}
}

BigNumber& BigNumber::reverse_copy(BigNumber &A)
{//Reverse copy
    cap=len=A.len;
    val=alloc.allocate(cap);
    first_free=val;
    dot=0;
    unsigned char *begin=A.first_free;
    while(begin!=A.val){
        alloc.construct(first_free++,*--begin);
        if(*begin=='.') dot=first_free-val-1;
    }
}

BigNumber& BigNumber::dot_erase_copy(BigNumber &A)
{//Copy BigNumber without dot before division
    release();
    cap = A.dot ? (A.len - 1) : A.len;
    len = cap;
    dot = 0;
    val=alloc.allocate(cap);
    first_free = val;
    int count = 0;
    while(count < A.len){
        alloc.construct(first_free++,A.val[count]);
        if(A.val[++count]=='.')
            if(++count == (A.len - 2) && A.val[count] == '0'){
                ++count;
                --len;
            }
    }
    return *this;
}

void BigNumber::cut_tail(int num)
{
    int newcap = num + 3;
    int newdot;
    unsigned char *newval = alloc.allocate(newcap);
    unsigned char *newfirst_free = newval;
    unsigned char *oldval = val;
    while((first_free - oldval) != newcap) ++oldval;
    unsigned char *start = oldval;
    while(oldval != first_free){
        if(*oldval == '.') newdot = oldval - start;
        alloc.construct(newfirst_free++,*oldval++);
    }
    release();
    val=newval;
    first_free=newfirst_free;
    len=first_free-val;
    cap=newcap;
    dot=newdot;
}
