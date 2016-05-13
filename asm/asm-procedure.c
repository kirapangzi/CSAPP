#include <stdio.h>

#if 0
void callee_p(void *p);

long long callee(int  i, long l, long long ll)//, double d)
{
	long long res = i + l + ll;
	return res;
}

void * caller(int  i, long l, long long ll)
{
	//int i;
	//long l;
	//long long ll;
	//int array[128] = {0};
	int j = 0;

	//void *p = &j;

	callee_p(&j);

	//ll = callee(i, l, ll);

	return &j;
}
int iteration(int i)
{
	printf("hello\n");
}

int P(int x)
{
	int y = x*x;
	int z = Q(y);
	return y + z;
}





int swap_add(int *xp, int *yp)
{
	int x = *xp;
	int y = *yp;

	*xp = y;
	*yp = x;
	return x + y;
}

int caller(int arg1, int arg2)
{
	//int arg1 = 534;
	//int arg2 = 1057;
	int sum = swap_add(&arg1, &arg2);
	int diff = arg1 - arg2;

	return sum * diff;
}

#endif

int rfact(int n)
{
	int result;
	if (n <= 1)
		result = 1;
	else
		result = n * rfact(n - 1);

	return result;
}


