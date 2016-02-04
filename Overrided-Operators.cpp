/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Description:
 *			Overrided Operators
 *    > Created Time: 2016-01-15 11:53:58
**/

/*
 *     +  -  *  /：BigNumber\long long
 *     +=  -=  *=  /=:BigNumber\long long
 *     >  >=  <  <=  ==  !=:BigNumber\long long
 *     ++ --
 *     <<
 *     -(取反)
 *     =:BigNumber\int
 *     %:(BigNumber,long long)
 */

ostream& operator<<(ostream &os,const BigNumber &A)
{
    ofstream out("Num.txt");
    int i=A.val[A.len-1]=='+'?A.len-2:A.len-1;
    do{
        cout<<A.val[i];
        out<<A.val[i];
    }while(i--);
    cout<<endl;
    out.close();
    // cout<<endl<<A.cap<<" "<<A.len<<" "<<A.dot<<endl<<endl;
}
BigNumber operator+(BigNumber &A,BigNumber &B) {BigNumber C;C.Calculate(A,B,'+');return C;}
BigNumber operator-(BigNumber &A,BigNumber &B) {BigNumber C;C.Calculate(A,B,'-');return C;}
BigNumber operator*(BigNumber &A,BigNumber &B) {BigNumber C;C.Calculate(A,B,'*');return C;}
BigNumber operator/(BigNumber &A,BigNumber &B) {BigNumber C;C.Calculate(A,B,'/');return C;}
bool operator==(const BigNumber &A,const BigNumber &B) {if(Compare(A,B)=='=')return true; return false;}
bool operator!=(const BigNumber &A,const BigNumber &B) {return !(A==B);}
bool operator>(const BigNumber &A,const BigNumber &B)  {if(Compare(A,B)=='>') return true; return false; }
bool operator<(const BigNumber &A,const BigNumber &B)  {if(Compare(A,B)=='<') return true; return false; }
bool operator>=(const BigNumber &A,const BigNumber &B) {char c=Compare(A,B); if(c=='>'||c=='=') return true; return false;}
bool operator<=(const BigNumber &A,const BigNumber &B) {char c=Compare(A,B); if(c=='<'||c=='=') return true; return false;}
bool operator==(const BigNumber &A,long long num)           {if(A==BigNumber(num)) return true; return false; }
bool operator!=(const BigNumber &A,long long num)           {return !(A==num);}
bool operator>(const BigNumber &A,long long num)            {if(A>BigNumber(num)) return true; return false; }
bool operator<(const BigNumber &A,long long num)            {if(A<BigNumber(num)) return true; return false; }
bool operator>=(const BigNumber &A,long long num)           {if(A>=BigNumber(num)) return true; return false; }
bool operator<=(const BigNumber &A,long long num)           {if(A<=BigNumber(num)) return true; return false; }
BigNumber operator+(BigNumber &A,long long num) {BigNumber B(num),C;C=A+B;return C;}
BigNumber operator-(BigNumber &A,long long num) {BigNumber B(num),C;C=A-B;return C;}
BigNumber operator*(BigNumber &A,long long num) {BigNumber B(num),C;C=A*B;return C;}
BigNumber operator/(BigNumber &A,long long num) {BigNumber B(num),C;C=A/B;return C;}
BigNumber operator%(BigNumber &A,long long num)
{
    BigNumber B(num),C;
    if(!A.dot){
        if(A==0) return A;
        else if(A>0&&A<B) return A;
        else if(A<0&&A>B) return A;
        BigNumber copy,Int("1"),Rev("-1");
        bool flag=true;
        if(A<0) {flag = false;A *= Rev;}
        if(B<0) B*=Rev;
        while((C = B * Int)<A){
            ++Int;
            copy = C;
        }
        if(C==A) {C=0;return C;}
        else {if(flag) C=A-copy;else C=copy-A;return C;}
    }else{
        cerr<<"wrong data type."<<endl;
        exit(0);
    }
}
