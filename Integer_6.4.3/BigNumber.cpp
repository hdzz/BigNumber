/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Description:
 *			BigNumber   Version 6.4.3
 *    > Created Time: 2016-01-18 23:01:26
 *	  > Updated Time: 2016-04-09 12:35:09
 *			update information
 *				V 6.2.3		improved factorial
 *				V 6.3.3		karatsuba
 *				V 6.4.3		more improved factorial
**/

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <utility>
#include <cstdlib>
#include <climits>
#include <ctime>
using namespace::std;

#define  Pause  system("pause");

#define  PER  1000000000
#define  Per  100000000

#define  Max(a,b)  ((a > b) ? a : b)

class BigNumber
{
	friend void part(BigNumber&, const int&, BigNumber&, BigNumber&);
	public:
		BigNumber& operator=(const BigNumber&);
		BigNumber& operator=(int&);
		BigNumber() =default;
		BigNumber(int);
		BigNumber(long long);
		BigNumber(vector<int>&);
		BigNumber(BigNumber&);
		void show();
		void release();
		void extend(const int&);
		BigNumber& plus(BigNumber&, BigNumber&);
		BigNumber& minus(BigNumber&, BigNumber&);
		BigNumber& multiply(BigNumber&, BigNumber&);
		BigNumber& karatsuba(BigNumber&, BigNumber&);
		BigNumber& factorial(BigNumber&);
		BigNumber& factorial(BigNumber&, int);
		BigNumber& factorial(BigNumber&, int, bool);
		BigNumber& factorial(const int&);
		~BigNumber();
	private:
		allocator<int> alloc_;
		bool pos_    = true;		// true means the BigNumber is positive
		int  cap_i_  = 0;			// the amount of the int allocated for integer part
		int *intg_   = nullptr;		// the integer part of the BigNumber
		int *free_i_ = nullptr;		// the end of the integer part
		int  len_i_  = 0;			// the length of the integer part
		bool dot_    = false;		// true means the BigNumber decimal part
		int  cap_f_  = 0;			// the amount of the int allocated for decimal part
		int *flot_   = nullptr;		// the decimal part of the BigNumber
		int *free_f_ = nullptr;		// the end of the decimal part
		int  len_f_  = 0;			// the length of the decimal part
};

BigNumber& BigNumber::operator=(const BigNumber &A)
{
	release();
	cap_i_ = A.cap_i_;
	len_i_ = A.len_i_;
	intg_ = alloc_.allocate(cap_i_);
	free_i_ = intg_;
	int count = 0;
	while (count != A.len_i_)
		alloc_.construct(free_i_++, std::move(A.intg_[count++]));
	return *this;
}

BigNumber& BigNumber::operator=(int &num)
{
	int fir = num % PER;
	num /= PER;
	cap_i_ = num ? 2 : 1;
	intg_= alloc_.allocate(cap_i_);
	free_i_ = intg_;
	alloc_.construct(free_i_++, fir);
	if (num) alloc_.construct(free_i_++, num);
	len_i_ = free_i_ - intg_;
	return *this;
}

BigNumber::BigNumber(int num)
{
	int fir = num % PER;
	num /= PER;
	cap_i_ = num ? 2 : 1;
	intg_= alloc_.allocate(cap_i_);
	free_i_ = intg_;
	alloc_.construct(free_i_++, fir);
	if (num) alloc_.construct(free_i_++, num);
	len_i_ = free_i_ - intg_;
}

BigNumber::BigNumber(long long num)
{
	int fir = num % PER;
	num /= PER;
	int sec = 0;
	if (num) {
		sec = num % PER;
		num /= PER;
	}
	cap_i_ = sec ? 4 : 3;
	intg_ = alloc_.allocate(cap_i_);
	free_i_ = intg_;
	alloc_.construct(free_i_++, fir);
	if (sec) alloc_.construct(free_i_++, sec);
	if (num) alloc_.construct(free_i_++, num);
	len_i_ = free_i_ - intg_;
}

BigNumber::BigNumber(vector<int> &v)
{
	cap_i_ = v.size() + 1;
	intg_ = alloc_.allocate(cap_i_);
	free_i_ = intg_;
	for (int i = v.size() - 1; i >= 0; --i)
		alloc_.construct(free_i_++, v[i]);
	len_i_ = free_i_ - intg_;
}

BigNumber::BigNumber(BigNumber &A)
{
	cap_i_ = A.cap_i_;
	len_i_ = A.len_i_;
	intg_ = alloc_.allocate(cap_i_);
	free_i_ = intg_;
	int count = 0;
	while (count != A.len_i_)
		alloc_.construct(free_i_++, std::move(A.intg_[count++]));
}

void BigNumber::show()
{
	ofstream out("TNum.txt");
	for (int i = len_i_ - 1; i >= 0; --i){
		int value = intg_[i];
		int devide = value + 1;
		int j = (devide > 1) ? (Per / devide) : (Per / 2);
		for (; j > 0 && i != (len_i_ - 1); j /= 10) {
			cout << 0;
			out << 0;
		}
		cout << value;
		// cout << value << " ";
        out << value;
	}
    out.close();
	cout << endl;
	// cout << len_i_ << endl;
	// cout << "len " << len_i_ <<"  cap " << cap_i_ << endl;
}

void BigNumber::release()
{
	if (intg_) {
		for (int i = 0; i < len_i_; ++i)
			alloc_.destroy(--free_i_);
		alloc_.deallocate(intg_, cap_i_);
	}
	if (flot_) {
		for (int i = 0; i < len_f_; ++i)
			alloc_.destroy(--free_f_);
		alloc_.deallocate(flot_, cap_f_);
	}
	intg_ = free_i_ = flot_ = free_f_ = nullptr;
	pos_ = dot_ = false;
	cap_i_ = len_i_ = cap_f_ = len_f_ = 0;
}

BigNumber::~BigNumber()
{
	if (intg_) {
		for (int i = 0; i < len_i_; ++i)
			alloc_.destroy(--free_i_);
		alloc_.deallocate(intg_,cap_i_);
	}
	if (flot_) {
		for (int i = 0; i < len_f_; ++i)
			alloc_.destroy(--free_f_);
		alloc_.deallocate(flot_,cap_f_);
	}
	intg_ = free_i_ = flot_ = free_f_ = nullptr;
	pos_ = dot_ = false;
	cap_i_ = len_i_ = cap_f_ = len_f_ = 0;
}

BigNumber& BigNumber::plus(BigNumber &A, BigNumber &B)
{
	release();
	cap_i_ = (A.len_i_ > B.len_i_) ? (A.len_i_ + 2) : (B.len_i_ + 2);
	intg_ = alloc_.allocate(cap_i_);
	free_i_ = intg_;
	int a = 0, b = 0;
	alloc_.construct(free_i_, 0);
	while(a != A.len_i_ || b != B.len_i_) {
		if (a != A.len_i_) *free_i_ += A.intg_[a++];
	    if (b != B.len_i_) *free_i_ += B.intg_[b++];
	    if (*free_i_ >= PER) {
	    	*free_i_ -= PER;
	    	alloc_.construct(++free_i_, 1);
	    } else { alloc_.construct(++free_i_, 0); }
	}
	if (*free_i_ == 0) alloc_.destroy(free_i_);
	else ++free_i_;
	len_i_ = free_i_ - intg_;
	return *this;
}

BigNumber& BigNumber::minus(BigNumber &A, BigNumber &B)
{
	release();
	cap_i_ = (A.len_i_ > B.len_i_) ? (A.len_i_ + 1): (B.len_i_ + 1);
	intg_ = alloc_.allocate(cap_i_);
	free_i_ = intg_;
	int a = 0, b = 0;
	alloc_.construct(free_i_, 0);
	while(a != A.len_i_ || b != B.len_i_) {
		if (a != A.len_i_) *free_i_ += A.intg_[a++];
	    if (b != B.len_i_) *free_i_ -= B.intg_[b++];
	    if (*free_i_ < 0) {
	    	*free_i_ += PER;
	    	alloc_.construct(++free_i_, -1);
	    } else { alloc_.construct(++free_i_, 0); }
	}
	while (*free_i_ == 0) alloc_.destroy(free_i_--);
	++free_i_;
	len_i_ = free_i_ - intg_;
	return *this;
}

BigNumber& BigNumber::multiply(BigNumber &A, BigNumber &B)
{
	release();
	// A.show();
	// B.show();
	cap_i_ = A.len_i_ + B.len_i_ + 1;
	intg_ = alloc_.allocate(cap_i_);
	free_i_ = intg_;
	allocator<int> all;
	int *begin = all.allocate(cap_i_);
	int *end = begin, *ori = begin;
	uninitialized_fill_n(begin, cap_i_, 0);
	begin = end;
	int a = 0;
	while (a != A.len_i_) {
		int b = 0;
		end = begin;
		while (b != B.len_i_) {
			long long s = (long long) A.intg_[a] * B.intg_[b++];
			*end += s % PER;
			s /= PER;
			if (*end >= PER) {
				*end -= PER;
				++s;
			}
			if (s) {
				*++end += s;
				if (*end >= PER) {
					*end -= PER;
					*(end + 1) += 1;
				}
			} else { ++end; }
		}
		++a;
		alloc_.construct(free_i_++, std::move(*begin++));
	}
	while (begin != end)
	    alloc_.construct(free_i_++, std::move(*begin++));
	alloc_.construct(free_i_, std::move(*begin));
	while (*free_i_ == 0) alloc_.destroy(free_i_--);
	++free_i_;
	len_i_ = free_i_ - intg_;
	while(begin != ori) alloc_.destroy(begin--);
	alloc_.destroy(begin);
	alloc_.deallocate(begin, cap_i_);
	return *this;
}

void part(BigNumber &A, const int &m, BigNumber &h, BigNumber &l)
{// part BigNumber by m
	if (A.len_i_ <= m) {
		h = 0;
		l = A;
	} else {
		l.cap_i_ = l.len_i_ = m;
		l.intg_ = l.alloc_.allocate(l.cap_i_);
		l.free_i_ = l.intg_;
		int start = 0;
		while (start != m)
			l.alloc_.construct(l.free_i_++, std::move(A.intg_[start++]));

		h.cap_i_ = h.len_i_ = A.len_i_ - m;
		h.intg_ = h.alloc_.allocate(h.cap_i_);
		h.free_i_ = h.intg_;
		while (start != A.len_i_)
			h.alloc_.construct(h.free_i_++, std::move(A.intg_[start++]));
	}
}

void BigNumber::extend(const int &m)
{
	int old_cap_i   = cap_i_;
	int old_len_i   = len_i_;
	int *old_intg   = intg_;
	int *old_free_i = free_i_;
	cap_i_ += m;
	len_i_ += m;
	intg_ = alloc_.allocate(cap_i_);
	free_i_ = intg_;
	int count = 0;
	while (count++ != m)
		alloc_.construct(free_i_++, 0);
	count = 0;
	while (count != old_len_i)
		alloc_.construct(free_i_++, std::move(old_intg[count++]));
	for (int i = 0; i < old_len_i; ++i)
		alloc_.destroy(--old_free_i);
	alloc_.deallocate(old_intg, old_cap_i);
}

BigNumber& BigNumber::karatsuba(BigNumber &A, BigNumber &B)
{// karatsuba algorithm
	if (A.len_i_ <= 1 || B.len_i_ <= 1)
		return multiply(A, B);
	int M = Max(A.len_i_, B.len_i_);
	int m = M / 2;
	BigNumber ha, hb, la, lb;
	part(A, m, ha, la);
	part(B, m, hb, lb);
	BigNumber z0 = karatsuba(la, lb);
	BigNumber mida, midb;
	mida.plus(la, ha);
	midb.plus(lb, hb);
	BigNumber z1 = karatsuba(mida, midb);
	BigNumber z2 = karatsuba(ha, hb);
	BigNumber z, Z;
	z.plus(z0, z2);
	Z.minus(z1, z);
	z2.extend(m << 1);
	Z.extend(m);
	z.plus(z2, Z);
	plus(z, z0);
	return *this;
}

BigNumber& BigNumber::factorial(BigNumber &A)
{//normal version of factorial
	int fac_num = A.intg_[0];
	if (!fac_num) {*this = 1; return *this; }
	if (fac_num == 1) {*this = A; return *this; }
	BigNumber B(A.intg_[0]), C;
	while (--A.intg_[0]) {
		C.multiply(A, B);
		B = C;
	}
	*this = B;
	return *this;
}

BigNumber& BigNumber::factorial(BigNumber &A, int interval)
{//improved version of factorial
	int end = A.intg_[0];
	if (!end) { *this = 1; return *this; }
	if (end == 1) {*this = A; return *this; }
	int number = end / interval;
	int start = 2, over = interval + 1;
	int size = number + 1;
	BigNumber B[size];
	BigNumber C[size];
	BigNumber R[size];
	int gap = -interval;
	for (int i = 0; i < number; ++i) {
		gap += interval;
		B[i] = gap + 1;
		C[i] = gap + 2;
	}
	while (start != over) {
		for (int i = 0; i < number; ++i) {
			R[i].multiply(B[i], C[i]);
			B[i] = R[i];
			++C[i].intg_[0];
		}
		++start;
	}
	int last = number - 1;
	while (C[last].intg_[0] <= end) {
		R[0].multiply(B[0], C[last]);
		B[0] = R[0];
		++C[last].intg_[0];
	}
	for (int i = 1; i < number; ++i) {
		R[0].multiply(B[0], B[i]);
		B[0] = R[0];
	}
	*this = B[0];
	return *this;
}

BigNumber& BigNumber::factorial(BigNumber &A, int interval, bool merge)
{// more improved version of factorial
	int end = A.intg_[0];
	if (!end) { *this = 1; return *this; }
	if (end == 1) {*this = A; return *this; }
	int number = end / interval;
	int start = 0, over = interval / 2;
	int size = number + 1;
	BigNumber B[size];
	BigNumber C[size];
	BigNumber R[size];
	BigNumber D[size];
	int gap = -interval;
	for (int i = 0; i < number; ++i) {
		gap += interval;
		B[i] = gap + 1;
		C[i] = gap + interval;
		D[i] = 1;
	}
	while (start < over) {
		for (int i = 0; i < number; ++i) {
			R[i].multiply(B[i], C[i]);
			BigNumber temp(D[i]);
			D[i].multiply(R[i], temp);
			++B[i].intg_[0];
			--C[i].intg_[0];
		}
		++start;
	}
	int count = number / 2;
	BigNumber E(1), F;
	number -= 1;
	for (int i = 0; i < count; ++i) {
		F.multiply(D[i], D[number - i]);
		BigNumber temp(E);
		E.multiply(F, temp);
	}
	*this = E;
	return *this;
}

BigNumber& BigNumber::factorial(const int &number)
{

}

int main()
{
  	clock_t start, end;
	vector<int> x = {123456789, 987654321, 123456789, 987654321};
	vector<int> y = {987654321, 123456789, 987654321, 123456789};
    start = clock();
	BigNumber c(100000), d, e;
	d.factorial(c, 1000, true);
	// d.factorial(c, 1000);
	// e.factorial(c);
	// e.show();
	// e.show();
	// d.karatsuba(a, b);
	end = clock();
	d.show();
    cout<<(end - start)<<endl;
    return 0;
}
