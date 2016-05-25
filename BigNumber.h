/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Link:     https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-05-25 22:07:33
**/

#ifndef _BIGNUMBER_H_
#define _BIGNUMBER_H_

#include <memory>

#define  PER  1000000000
#define  Per  100000000

class BigNumber
{
	public:
		BigNumber(int);
		BigNumber() = default;
		BigNumber& operator=(const BigNumber&);
		BigNumber(const BigNumber&);
		void show();
		void release();
		BigNumber& multiply(const BigNumber&, const BigNumber&);
		BigNumber& partial_factorial(const int, const int, const int);
		~BigNumber() { release(); };
	private:
		std::allocator<int> alloc_;
		int  cap_i_  = 0;				// the amount of the int allocated for integer part
		int *intg_   = nullptr; // the integer part of the BigNumber
		int *free_i_ = nullptr;	// the end of the integer part
		int  len_i_  = 0;				// the length of the integer part
};

#endif /* _BIGNUMBER_H_ */
