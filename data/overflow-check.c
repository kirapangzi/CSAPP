#include <stdio.h>
#include <limits.h>


int uadd_ok(unsigned x, unsigned y)
{
	if ((x + y) >= x)
		return 1;
	else
		return 0;
}

int tadd_ok(int x, int y)
{
	int sum = x + y;
	if (x >= 0 && y >= 0) {
		if (sum >= x)
			return 1;
	} else if (x < 0 && y < 0) {
		if (sum < x)
			return 1;
	} else if ((x >= 0 && y < 0) || (x < 0 && y >= 0))
		return 1;

	return 0;
}

int tsub_ok(int x, int y) {
	return tadd_ok(x, -y);
}


#if 0
/* Determine whether arguments can be added without overflow */
int tadd_ok(int x, int y) {
int sum = x+y;
int neg_over = x < 0 && y < 0 && sum >= 0;
int pos_over = x >= 0 && y >= 0 && sum < 0;
return !neg_over && !pos_over;
}


/* Determine whether arguments can be added without overflow */
/* WARNING: This code is buggy. */
int tadd_ok(int x, int y) {
int sum = x+y;
return (sum-x == y) && (sum-y == x);
}
#endif

int main()
{
#if 0
	printf("%u + %u = %u, %s\n", 12345u, 12345u, 12345u+12345u, uadd_ok(12345u,12345u)? "no overflow":"overflow");
	printf("%u + %u = %u, %s\n", 0xffffffffu, 12345u, 0xffffffffu+12345u, uadd_ok(0xffffffffu,12345u)? "no overflow":"overflow");
#endif
	printf("%d + %d = %d, %s\n", 12345, 12345, 12345+12345, tadd_ok(12345,12345)? "no overflow":"overflow");
	printf("%d + %d = %d, %s\n", 0x7fffffff, 0x7fffffff, 0x7fffffff+0x7fffffff, tadd_ok(0x7fffffff,0x7fffffff)? "no overflow":"overflow");
	printf("%d + %d = %d, %s\n", -2147483648, -1, -2147483648+(-1), tadd_ok(-2147483648,-1)? "no overflow":"overflow");
	printf("%d + %d = %d, %s\n", INT_MIN, INT_MIN, INT_MIN+(INT_MIN), tadd_ok(INT_MIN,INT_MIN)? "no overflow":"overflow");

	printf("%d - %d = %d, %s\n", INT_MIN, INT_MIN, INT_MIN-(INT_MIN), tsub_ok(INT_MIN,INT_MIN)? "no overflow":"overflow");
	
}
