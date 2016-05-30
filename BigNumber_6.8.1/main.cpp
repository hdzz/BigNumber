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

#include <iostream>
#include <vector>
#include <thread>
#include <ctime>

#include "BigNumber.h"

const int TNUM = 8;
const int FAC  = 10000;

const int interval1 = FAC / TNUM;
const int interval2 = interval1 / (50 * (FAC / 10000));

BigNumber bn1[TNUM];
BigNumber bn2[TNUM / 2];
BigNumber bn3[TNUM / 4];

int main(int arvc, char **argv)
{
	BigNumber test;
	test.partial_factorial(atoi(argv[1]), atoi(argv[2]), 500);
	return 0;

	/* phase 1 */
	std::vector<std::thread> vec1;
	for (size_t i = 0; i < TNUM; ++i) {
		int beg = i * interval1;
		int end = beg + interval1;
		vec1.push_back(std::thread( \
			&BigNumber::partial_factorial, &bn1[i], beg, end, interval2));
	}
	for (size_t i = 0; i < TNUM; ++i)
		vec1[i].join();

	/* phase 2 */
	std::vector<std::thread> vec2;
	for (size_t i = 0; i < TNUM / 2; ++i)
		vec2.push_back(std::thread(&BigNumber::multiply, \
			&bn2[i], std::ref(bn1[i]), std::ref(bn1[7 - i])));
	for (size_t i = 0; i < TNUM / 2; ++i)
		vec2[i].join();

	/* phase 3 */
	std::vector<std::thread> vec3;
	for (size_t i = 0; i < TNUM / 4; ++i)
		vec3.push_back(std::thread(&BigNumber::multiply, \
			&bn3[i], std::ref(bn2[i]), std::ref(bn2[3 - i])));
	for (size_t i = 0; i < TNUM / 4; ++i)
		vec3[i].join();

	BigNumber a;
	a.multiply(bn3[0], bn3[1]);

	return 0;
}
