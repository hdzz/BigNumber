/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Description:
 *			BigNumber   Version 6.6.0
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

const int TNUM = 10;

int main()
{
	// time_t begin, end;
	// begin = clock();

	/* phase 1 */
	BigNumber bn[TNUM];
	std::vector<std::thread> vec;
	for (size_t i = 0; i != TNUM; ++i) {
		int beg = i * 10000;
		int end = beg + 10000;
		vec.push_back(std::thread(&BigNumber::partial_factorial, \
			&bn[i], beg, end, 100));
	}
	for (size_t i = 0; i != TNUM; ++i)
		vec[i].join();

	/* phase 2 */
	BigNumber bn2[5];
	std::vector<std::thread> vec2;
	for (size_t i = 0; i < TNUM; i += 2)
		vec2.push_back(std::thread(&BigNumber::multiply, \
			&bn2[i / 2], std::ref(bn[i]), std::ref(bn[i+1])));
	for (size_t i = 0; i != 5; ++i)
		vec2[i].join();

	/* phase 3 */
	BigNumber bn3[2];
	std::vector<std::thread> vec3;
	for (size_t i = 0; i < 2; ++i)
		vec3.push_back(std::thread(&BigNumber::multiply, \
			&bn3[i], std::ref(bn2[i * 2]), std::ref(bn2[i * 2 + 1])));
	for (size_t i = 0; i != 2; ++i)
		vec3[i].join();

	/* phase 4 */
	BigNumber a, b;
	a.multiply(bn2[4], bn3[0]);
	b.multiply(bn3[1], a);

	// end = clock();
	// std::cout << ((end - begin) / 1000) << std::endl;

    return 0;
}
