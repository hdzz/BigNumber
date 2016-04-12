/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Description:
 *			Compare BigNumbers
 *    > Created Time: 2016-01-15 12:03:41
**/

char Compare(const BigNumber &A,const BigNumber &B)
{//Compare two BigNumber
    if(!A.len && B.len) return '<';
    if(A.len && !B.len) return '>';
    // cout<<A<<B;
    if(A.val[A.len-1] == '+' && B.val[B.len-1] == '-') return '>';
    if(A.val[A.len-1] == '-' && B.val[B.len-1] == '+') return '<';
    bool flag = true;
    if(A.val[A.len-1] == '-') flag = false;
    if((A.len-A.dot)==(B.len-B.dot) || !A.dot || !B.dot){
        if(!A.dot && !B.dot){
            if(A.len > B.len) return flag?'>':'<';
            if(A.len < B.len) return flag?'<':'>';
        }
        if(!A.dot && B.dot){
            if(A.len > (B.len-B.dot-1)) return flag?'>':'<';
            else if(A.len < (B.len-B.dot-1)) return flag?'<':'>';
        }
        if(!B.dot && A.dot){
            if(B.len>(A.len-A.dot-1)) return flag?'<':'>';
            else if(B.len<(A.len-A.dot-1)) return flag?'>':'<';
        }
        int i = A.len - 2;
        int j = B.len - 2;
        while(i >= 0 && j >= 0 && A.val[i] == B.val[j])
            {--i;--j;}
        if(i >= 0 && j >= 0){
            if(A.val[i] > B.val[j]) return flag ? '>' : '<';
            else if(A.val[i] < B.val[j]) return flag ? '<': '>';
        } else {
            if (i >=0 && j < 0 ) return flag ? '>' : '<';
            else if (i < 0 && j >= 0) return flag ? '<': '>';
            else return '=';
        }
    }else if((A.len-A.dot) > (B.len-B.dot)) return flag ? '>' : '<';
          else return flag ? '<' : '>';
}
