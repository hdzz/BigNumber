/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Link:     https://www.github.com/UncP
 *    > Description:
 *				BigNumber Version 6.7.1
 *
 *    > Created Time: 2016-05-27 13:56:25
**/

#include <iostream>
#include <vector>
#include <thread>
#include <ctime>

#include "BigNumber.h"

const int TNUM = 8;
const int FAC  = 10000;

int main()
{
	clock_t beg, end;
	const int interval1 = FAC / TNUM;
	const int interval2 = interval1 / (50 * (FAC / 10000));

	beg = clock();

	/* phase 1 */
	BigNumber bn1[TNUM];
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
	BigNumber bn2[TNUM / 2];
	std::vector<std::thread> vec2;
	for (size_t i = 0; i < TNUM / 2; ++i)
		vec2.push_back(std::thread(&BigNumber::multiply, \
			&bn2[i], std::ref(bn1[i]), std::ref(bn1[7 - i])));
	for (size_t i = 0; i < TNUM / 2; ++i)
		vec2[i].join();

	/* phase 3 */
	BigNumber bn3[TNUM / 4];
	std::vector<std::thread> vec3;
	for (size_t i = 0; i < TNUM / 4; ++i)
		vec3.push_back(std::thread(&BigNumber::multiply, \
			&bn3[i], std::ref(bn2[i]), std::ref(bn2[3 - i])));
	for (size_t i = 0; i < TNUM / 4; ++i)
		vec3[i].join();

	BigNumber a;
	a.multiply(bn3[0], bn3[1]);

	end = clock();
	std::cout << (end - beg) / 1000 << std::endl;

	return 0;
}
