/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Description:
 *			BigNumber   Version 6.6.1
 *
 *			concurrency
 *
 *    > Created Time: 2016-05-23 19:53:21
**/

#include <iostream>
#include <ctime>
#include <vector>
#include <thread>

#include "BigNumber.h"

const int TNUM = 8;
const int FAC  = 10000;

int main()
{
	time_t begin, end;
	begin = clock();

	/* phase 1 */
	BigNumber bn[TNUM];
	std::vector<std::thread> vec1;
	int interval = FAC / TNUM;
	for (size_t i = 0; i != TNUM; ++i) {
		int beg = i * interval;
		int end = beg + interval;
		vec1.push_back(std::thread(&BigNumber::partial_factorial, \
			&bn[i], beg, end, 250));
	}
	for (size_t i = 0; i != TNUM; ++i)
		vec1[i].join();

	/* phase 2 */
	BigNumber bn2[TNUM / 2];
	std::vector<std::thread> vec2;
	for (size_t i = 0; i != TNUM / 2; ++i)
		vec2.push_back(std::thread(&BigNumber::multiply, \
			&bn2[i], std::ref(bn[i]), std::ref(bn[7 - i])));
	for (size_t i = 0; i != TNUM / 2; ++i)
		vec2[i].join();

	/* phase 3 */
	BigNumber bn3[TNUM / 4];
	std::vector<std::thread> vec3;
	for (size_t i = 0; i != (TNUM / 4); ++i)
		vec3.push_back(std::thread(&BigNumber::multiply, \
			&bn3[i], std::ref(bn2[i]), std::ref(bn2[3 - i])));
	for (size_t i = 0; i != (TNUM / 4); ++i)
		vec3[i].join();

	BigNumber a;
	a.multiply(bn3[0], bn3[1]);

	end = clock();
	std::cout << ((end - begin) / 1000) << std::endl;

	return 0;
}
