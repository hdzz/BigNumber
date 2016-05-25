/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Link:     https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-05-23 19:43:51
**/

#ifndef _BIGNUMBER_H_
#define _BIGNUMBER_H_

#include <memory>

const int PER = 1000000000;
const int Per = 100000000;

class BigNumber
{
	public:
		BigNumber& operator=(const BigNumber&);
		BigNumber() = default;
		BigNumber(int);
		BigNumber(BigNumber&);
		void show();
		void release();
		BigNumber& multiply(BigNumber&, BigNumber&);
		BigNumber& partial_factorial(const int, const int, const int);
		~BigNumber() { release(); }
	private:
		std::allocator<int> alloc_;
		int  cap_i_  = 0;
		int *intg_   = nullptr;
		int *free_i_ = nullptr;
		int  len_i_  = 0;
};

#endif /* _BIGNUMBER_H_ */
