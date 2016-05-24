/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Description:
 *			Other Operations
 *    > Created Time: 2016-01-18 01:57:09
**/

int Convert_to_i(const BigNumber &A)
{
	unsigned char *start = A.val;
	unsigned char *over = A.first_free - 1;
	int count = 1;
	int i = 0;
	while(start != over){
		int mid = *start++ - '0';
		i += count * mid;
		count *= 10;
	}
	return i;
}