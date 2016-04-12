#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
#include <iterator>
#include <iomanip>
#define  ACCURACY  20
#define  TEST  cout<<"12345"<<endl;
using namespace::std;

class BigNumber
{    
    friend void Output(BigNumber&,BigNumber&,BigNumber&,const char&);
    friend char Compare(const BigNumber&,const BigNumber&);
    friend int Dot_Info(const BigNumber&);
    friend ostream& operator<<(ostream &os,const BigNumber &A) {os<<A.val<<endl;return os;}
    friend istream& operator>>(istream &is,BigNumber &A)       {is>>A.val;return is;}
    friend bool operator==(const BigNumber &A,int i);
    friend bool operator!=(const BigNumber &A,int i);
    public:
    	BigNumber() {}
        BigNumber(const BigNumber &A) {*this=A;}
        BigNumber(char c) {val.push_back(c);}
        BigNumber(const string &str) {val=str;}
        BigNumber& operator=(const BigNumber &num) {val=num.val;return *this;}
        BigNumber& operator=(int i);
        BigNumber operator+=(const BigNumber &A) {return Calculate(*this,A,'+');}
        BigNumber operator-=(const BigNumber &A) {return Calculate(*this,A,'-');}
        BigNumber operator*=(const BigNumber &A) {return Calculate(*this,A,'*');}
        BigNumber operator/=(const BigNumber &A) {return Calculate(*this,A,'/');}
        BigNumber& operator++() {Calculate(*this,BigNumber('1'),'+');return *this;}
        BigNumber& operator--() {Calculate(*this,BigNumber('1'),'-');return *this;}
        BigNumber operator++(int) {BigNumber B=*this;Calculate(*this,BigNumber('1'),'+');return B;}
        BigNumber operator--(int) {BigNumber B=*this;Calculate(*this,BigNumber('1'),'-');return B;}        
        void output(const BigNumber &A) {cout<<val<<endl<<val.size()<<endl;}
        void output(const size_t);
        void insert_dot(const int&,const int&);
        void dot_delete();
        void resize_if(string::reverse_iterator &);
        void erase();
        BigNumber Calculate(BigNumber,BigNumber,char);
        BigNumber plus(BigNumber,BigNumber);
        BigNumber minus(BigNumber,BigNumber);
        BigNumber multiply(BigNumber,BigNumber);
        BigNumber devide(BigNumber,BigNumber);
        BigNumber factorial(BigNumber);
        ~BigNumber() {val.clear();}
    private:
    	string val;
};

bool operator>(const BigNumber &A,const BigNumber &B) {if(Compare(A,B)=='>') return true;return false;}
bool operator<(const BigNumber &A,const BigNumber &B) {if(Compare(A,B)=='<') return true;return false;}
bool operator==(const BigNumber &A,const BigNumber &B){if(Compare(A,B)=='=') return true;return false;}
bool operator!=(const BigNumber &A,const BigNumber &B){return !(A==B);}
BigNumber operator+(const BigNumber &A,const BigNumber &B)   {BigNumber C;return C.Calculate(A,B,'+');}
BigNumber operator-(const BigNumber &A,const BigNumber &B)   {BigNumber C;return C.Calculate(A,B,'-');}
BigNumber operator*(const BigNumber &A,const BigNumber &B)   {BigNumber C;return C.Calculate(A,B,'*');}
BigNumber operator/(const BigNumber &A,const BigNumber &B)   {BigNumber C;return C.Calculate(A,B,'/');}
bool operator==(const BigNumber &A,int i)
{
    int e;
    string::const_reverse_iterator it=A.val.rbegin();
    do{
        e=i%10;i/=10;
        if(it!=A.val.rend()&&*it++==(e+48)) ;
        else return false;
    }while(i!=0);
    if(it==A.val.rend()) return true;return false;
}
bool operator!=(const BigNumber &A,int i) {return !(A==i);}

inline BigNumber& BigNumber::operator=(int i)
{
    int e;
    val.clear();
    bool flag;
    if(i<0) {i=-i;flag=true;}
    else flag=false;
    do{
        e=i%10;i/=10;
        val.insert(val.begin(),e+48);
    }while(i!=0);
    if(flag) val.insert(val.begin(),'-');
    return *this;
}

inline void BigNumber::output(const size_t width)
{
    string::iterator it=val.begin();
    cout<<setw(width);
    while(it!=val.end())
        cout<<*it++;
    cout<<endl;
}

inline void BigNumber::insert_dot(const int &size,const int &dot)
{
    if(size>dot){
        string::iterator it=val.begin();
        int num=size-dot;
        while(num--) it++;
        val.insert(it,'.');
    }else{
        int num=dot-size;
        while(num--) val.insert(val.begin(),'0');
        val.insert(val.begin(),'.');
        val.insert(val.begin(),'0');
    }
}

inline void BigNumber::dot_delete()
{
    string::iterator it;
    if((it=find(val.begin(),val.end(),'.'))!=val.end()){
        it=val.erase(it);
        if((it-val.begin())==1)
            val.erase(val.begin());
    }
}

inline void BigNumber::resize_if(string::reverse_iterator &it)
{
    if((it+1)==val.rend()){
        val.insert(val.begin(),val.size(),'0');
        it=val.rbegin()+(val.size()/2-1);
    }
}

inline void BigNumber::erase()
{
    string::iterator it=val.begin();
    while(*it=='0'&&(it+1)!=val.end()&&*(it+1)!='.')
        it=val.erase(it);
}

inline BigNumber BigNumber::Calculate(BigNumber A,BigNumber B,char oper)
{
    string::iterator a,b;
    a=A.val.begin();
    b=B.val.begin();
    char symbol=oper;
    char flag_a,flag_b;
    char s;
    if(oper=='-'){
        if(*b=='-') {B.val.erase(b); flag_b='+'; } 
        else {b=B.val.insert(b,'-'); flag_b='-'; } 
        oper='+';
    }
    if(oper=='+'){
        if(*a=='-'){
            A.val.erase(a);
            if(*b=='-'){
                B.val.erase(b);
                this->plus(A,B);
                val.insert(val.begin(),'-');
            }else{
                s=Compare(A,B);
                if(s=='>'){
                    this->minus(A,B);
                    val.insert(val.begin(),'-');
                }else if(s=='<') this->minus(B,A);
                      else val.insert(val.begin(),'0');
            }
        }else{
            if(*b=='-'){
                B.val.erase(b);
                s=Compare(A,B);
                if(s=='>') this->minus(A,B);
                else if(s=='<'){
                    this->minus(B,A);
                    val.insert(val.begin(),'-');
                }else val.insert(val.begin(),'0');
            }else this->plus(A,B);
        }
        return *this;
    }
    if(oper=='*'||oper=='/'){
        flag_a='+';
        flag_b='+';
        if(*a=='-') {A.val.erase(a);flag_a='-';}
        if(*b=='-') {B.val.erase(b); flag_b='-'; } 
        if(oper=='*') multiply(A,B);
        else devide(A,B);
        if(flag_a=='-'&&flag_b!='-') val.insert(val.begin(),'-');
        if(flag_a!='-'&&flag_b=='-') val.insert(val.begin(),'-');
        return *this;
    }
}

inline BigNumber BigNumber::plus(BigNumber A,BigNumber B)
{
    string s(100,48);
    val=s;
	string::reverse_iterator a,b;
    string::reverse_iterator New;
    char fs,bs;
	a=A.val.rbegin();
    b=B.val.rbegin();
    New=val.rbegin();
    int pa=Dot_Info(A),pb=Dot_Info(B);
    int distance=0;
    if((pa-pb)>0){
        distance=pa-pb;
        while(distance--){
            resize_if(New);
            *New++=*a++;
        }
        if(!pb){a++;resize_if(New);*New++='.';}
    }else if((pb-pa)>0){
              distance=pb-pa;
              while(distance--){
                  resize_if(New);
                  *New++=*b++;
              }
              if(!pa){b++;resize_if(New);*New++='.';}
          }
    while(a!=A.val.rend()||b!=B.val.rend()){
        if(*a=='.'){
            a++;b++;
            resize_if(New);
            *(New+1)=*New;
            *New++='.';
        }
        if(a!=A.val.rend()) {*New+=(*a-'0');a++;}
        if(b!=B.val.rend()) {*New+=(*b-'0');b++;}
        resize_if(New);
        if((*New-'0')>=10){
            *New-=10;
            *++New='1';
        }else New++; 
    }
    erase();
    return *this;
}

inline BigNumber BigNumber::minus(BigNumber A,BigNumber B)
{
    string s(100,48);
    val=s;
    string::reverse_iterator a,b;
    string::reverse_iterator New;
    char fs;
    a=A.val.rbegin();
    b=B.val.rbegin();
    New=val.rbegin();
    int pa=Dot_Info(A),pb=Dot_Info(B);
    int distance=0;
    if((pa-pb)>0){
        distance=pa-pb;
        while(distance--){
            resize_if(New);
            *New++=*a++;
        }
        if(!pb){a++;resize_if(New);*New++='.';}
    }else if((pb-pa)>0){
              distance=pb-pa;
              while(distance--){
                  resize_if(New);
                  *New+=10-(*b-'0');
                  *++New='0'-1;
                  b++;
              }
              if(!pa){b++;resize_if(New);*New='.';*++New='0'-1;}
          }
    while(a!=A.val.rend()||b!=B.val.rend()){
        if(*a=='.'){
            a++;b++;
            resize_if(New);
            *(New+1)=*New;
            *New++='.';
        }
        if(a!=A.val.rend()) {*New+=(*a-'0');a++;}
        if(b!=B.val.rend()) {*New-=(*b-'0');b++;}
        resize_if(New);
        if((*New-'0')<0){
            *New+=10;
            *++New='0'-1;
        }else New++;
    }
    erase();
    return *this;
}

inline BigNumber BigNumber::multiply(BigNumber A,BigNumber B)
{
    string::reverse_iterator b=B.val.rbegin();
    int count=0;
    val.clear();
    while(b!=B.val.rend()){
        BigNumber n=*this;
        val.clear();
        string::reverse_iterator a=A.val.rbegin();
        string s(100,48);
        BigNumber m(s);
        string::reverse_iterator New=m.val.rbegin();
        int value=0;
        while(a!=A.val.rend()&&*b!='0'){
            value=(*a-'0')*(*b-'0');
            *New+=(value%10);
            value/=10;
            if((*New-'0')>=10){
                *New-=10;
                value++;
            }
            m.resize_if(New);
            if(value){
                (*++New)+=value;
            }else New++;
            if((*++a)=='.') ++a;
        }
        m.erase();
        m.val.append(count++,'0');
        this->plus(m,n);
        if((*++b)=='.') ++b;
    }
    erase();
    int dot=Dot_Info(A)+Dot_Info(B);
    if(dot) insert_dot(this->val.size(),dot);
    return *this;
}

inline BigNumber BigNumber::devide(BigNumber A,BigNumber B)
{
    BigNumber Sub;
    string::iterator it;
    int count=0;
    bool open=false,end=false,flag=false;
    int da=Dot_Info(A);
    int db=Dot_Info(B);
    if(da>db) B.val.append(da-db,'0');
    else if(da<db) A.val.append(db-da,'0');
    A.dot_delete();
    B.dot_delete();
    it=A.val.begin();
    Sub.val.push_back(*it++);
    val.clear();
    while(1){
        if(Sub>B){
            open=true;flag=false;
            BigNumber Cur,Pre,Int('1');
            while((Cur=B*Int)<Sub){
                Pre=Cur;
                Int++;
            }
            if(Cur==Sub){
                val.push_back(Int.val[0]);
                Sub.val.clear();
            }else{
                Int--;
                val.push_back(Int.val[0]);
                Sub=Sub-Pre;
            }
        }else if(Sub==B){
                  open=true;flag=false;
                  val.push_back('1');
                  Sub.val.clear();
              }else{
                  if((end||open)&&flag)
                      val.push_back('0');
                  flag=true;
                  if(it!=A.val.end()){
                      while(Sub.val.empty()&&it!=A.val.end()&&*it++=='0')
                          val.push_back('0');
                      if(it!=A.val.end())
                        Sub.val.push_back(*it++);
                      else break;
                  }else{
                      if(Sub.val.empty()) break;
                      else if(count++!=ACCURACY){
                               Sub.val.push_back('0');
                               if(!end){
                                   if(val.empty())
                                       val.push_back('0');
                                   val.push_back('.');
                                   end=true;
                               }
                           }else break;
                  }
              }
    }
}

inline BigNumber BigNumber::factorial(BigNumber A)
{
    *this=A;
    while(A!=1){
        multiply(*this,--A);
    }
    return *this;
}

char Compare(const BigNumber &A,const BigNumber &B)
{
    if(A.val[0]!='-'&&B.val[0]=='-') return '>';
    else if(A.val[0]=='-'&&B.val[0]!='-') return '<';
         else{
             string::const_iterator a,b;
             a=A.val.begin();
             b=B.val.begin();
             int da=Dot_Info(A);
             int db=Dot_Info(B);
             int pa=A.val.size()-(da?da+1:0);
             int pb=B.val.size()-(db?db+1:0);
             int flag=1;
             if(*a=='-') flag=0;
             if(pa>pb)
                  return flag?'>':'<';
             else if(pa<pb)
                      return flag?'<':'>';
                  else{
                      while(a!=A.val.end()&&b!=B.val.end()&&*a==*b)
                          {a++;b++;}
                      if(a==A.val.end()&&b==B.val.end())
                          return '=';
                      else if(a==A.val.end()) return flag?'<':'>';
                           else if(b==B.val.end()) return flag?'>':'<';
                                else if(*a>*b) return flag?'>':'<';
                                     else return flag?'<':'>';
                  }
         }
}

void Output(BigNumber &A,BigNumber &B,BigNumber &C,const char &oper)
{
    int a=A.val.size();
    int b=B.val.size();
    int c=C.val.size(); 
    int pa=Dot_Info(A);
    int pb=Dot_Info(B);
    int pc=Dot_Info(C);
    a-=pa;b-=pb;c-=pc;
    const size_t wid=(a>b)?(a>c?a:c):(b>c?b:c);
    cout<<"RESULT"<<endl;
    A.output(wid-a+2-((pa==0)?1:0));
    cout<<oper<<endl;
    B.output(wid-b+2-((pb==0)?1:0));
    cout<<'='<<endl;
    C.output(wid-c+2-((pc==0)?1:0));
    cout<<endl;
}

int Dot_Info(const BigNumber &A)
{
    string::const_iterator fa;
    int da=0;
    if((fa=find(A.val.begin(),A.val.end(),'.'))!=A.val.end())
        while(++fa!=A.val.end())
            da++;
    return da;
}

int main()
{
    BigNumber a("2");
    BigNumber b("-3342553451.00657");
    BigNumber c("20");
    BigNumber d;
    c=a/b;
    cout<<c;
    /*c=a+b;
    cout<<c;
    c=a-b;
    cout<<c;
    c=a*b;
    cout<<c;*/
    //d.factorial(c);
    //d.output(c);    
    system("pause");
    return 0;
}
