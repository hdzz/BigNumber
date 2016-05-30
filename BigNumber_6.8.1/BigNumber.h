/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Link:     https://www.github.com/UncP
 *    > Description:
 *				BigNumber Version 6.8.1
 *
 *				10000   :  0.080
 *				100000  :  12
 *
 *    > Created Time: 2016-05-30 11:21:57
**/

#ifndef _BIGNUMBER_H_
#define _BIGNUMBER_H_

#include <memory>

const int PER = 1000000000;

class BigNumber
{
	public:
		BigNumber() = default;
		BigNumber(const int);
		BigNumber& operator=(const int);
		BigNumber& operator=(const BigNumber&);
		void release();
		BigNumber& multiply(const BigNumber&, const BigNumber&);
		BigNumber& partial_factorial(const int, const int, const int);
		~BigNumber() { release(); };
	private:
		std::allocator<int> alloc_;
		int  cap_i_  = 0;			 // the amount of the int allocated for integer part
		int *intg_   = nullptr;// the integer part of the BigNumber
		int *free_i_ = nullptr;// the end of the integer part
		int  len_i_  = 0;			 // the length of the integer part
};

#endif /* _BIGNUMBER_H_ */
