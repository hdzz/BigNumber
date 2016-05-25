/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Link:     https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-05-23 19:46:39
**/

#include <iostream>
#include <memory>

#include "BigNumber.h"

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
	for (int i = len_i_ - 1; i >= 0; --i){
		int value = intg_[i];
		int devide = value + 1;
		int j = (devide > 1) ? (Per / devide) : (Per / 2);
		for (; j > 0 && i != (len_i_ - 1); j /= 10)
			std::cout << 0;
		std::cout << value;
	}
	std::cout << std::endl;
}

void BigNumber::release()
{
	if (intg_) {
		for (int i = 0; i < len_i_; ++i)
			alloc_.destroy(--free_i_);
		alloc_.deallocate(intg_, cap_i_);
	}
	intg_ = free_i_ = nullptr;
	cap_i_ = len_i_ = 0;
}

BigNumber& BigNumber::multiply(BigNumber &A, BigNumber &B)
{
	release();
	cap_i_ = A.len_i_ + B.len_i_ + 1;
	intg_ = alloc_.allocate(cap_i_);
	free_i_ = intg_;
	std::allocator<int> all;
	int *begin = all.allocate(cap_i_);
	int *end = begin, *ori = begin;
	std::uninitialized_fill_n(begin, cap_i_, 0);
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
	while(begin != ori) all.destroy(begin--);
	all.destroy(begin);
	all.deallocate(begin, cap_i_);
	return *this;
}

BigNumber& BigNumber::partial_factorial(const int beg, const int end, \
	const int interval)
{
	BigNumber A(beg);
	int number = (end - beg) / interval;
	int start = 2, over = interval + 1;
	int size = number + 1;
	BigNumber B[size];
	BigNumber C[size];
	BigNumber R[size];
	int gap = beg - interval;
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
	for (int i = 1, j = 0; i < number; ++i, ++j) {
		R[0].multiply(B[0], B[i]);
		B[0] = R[0];
	}
	*this = B[0];
	return *this;
}
