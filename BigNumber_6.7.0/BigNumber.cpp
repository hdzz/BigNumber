/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Link:     https://www.github.com/UncP
 *    > Description:
 *				BigNumber Version 6.7.1
 *
 *				10000   :  0.086
 *				100000  :  12.8
 *
 *    > Created Time: 2016-05-27 13:56:25
**/

#include <iostream>
#include <memory>
#include <utility>
#include <climits>

#include "BigNumber.h"

BigNumber::BigNumber(const int num)
{
	cap_i_ = len_i_ = 1;
	intg_= alloc_.allocate(cap_i_);
	free_i_ = intg_;
	alloc_.construct(free_i_++, num);
}

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

BigNumber& BigNumber::operator=(const int num)
{
	cap_i_ = len_i_ = 1;
	intg_= alloc_.allocate(cap_i_);
	free_i_ = intg_;
	alloc_.construct(free_i_++, num);
	return *this;
}

void BigNumber::show()
{
	for (int i = len_i_ - 1; i >= 0; --i) {
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

BigNumber& BigNumber::multiply(const BigNumber &A, const BigNumber &B)
{
	release();
	cap_i_ = A.len_i_ + B.len_i_ + 1;
	intg_ = alloc_.allocate(cap_i_);
	free_i_ = intg_;
	std::allocator<int> all;
	int *begin = all.allocate(cap_i_);
	int *end = begin, *ori = begin;
	std::uninitialized_fill_n(begin, cap_i_, 0);
	int a = 0;
	while (a != A.len_i_) {
		int b = 0;
		end = begin;
		long An = (long) A.intg_[a];
		while (b != B.len_i_) {
			long s = An * B.intg_[b++];
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
	int count = (end - beg) / interval;
	std::shared_ptr<BigNumber> B[count];
	BigNumber C[count];
	int gap = beg - interval;
	for (int i = 0; i != count; ++i) {
		gap += interval;
		B[i] = std::shared_ptr<BigNumber>(new BigNumber(gap + 1));
		C[i] = gap + 2;
	}
	for (int i = 1; i != interval; ++i) {
		for (int j = 0; j != count; ++j) {
			std::shared_ptr<BigNumber> tmp = \
				std::shared_ptr<BigNumber>(new BigNumber());
			(*tmp).multiply(*B[j], C[j]);
			B[j] = tmp;
			++C[j].intg_[0];
		}
	}
	for (int i = 1; i != count; ++i) {
		std::shared_ptr<BigNumber> tmp = \
			std::shared_ptr<BigNumber>(new BigNumber());
		(*tmp).multiply(*B[0], *B[i]);
			B[0] = tmp;
	}
	*this = *B[0];
	return *this;
}
