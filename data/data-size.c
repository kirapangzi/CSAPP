#include <stdio.h>

int main()
{
	char ch;
	short int si;
	int i;
	long int li;
	long long int lli;
	
	char *p;
	int *ip;
	
	float f;
	double d;
	
	size_t s;

	printf("size of char is %d\n", sizeof(ch));
	printf("size of short int is %d\n", sizeof(si));
	printf("size of int is %d\n", sizeof(i));
	printf("size of long int is %d\n", sizeof(li));
	printf("size of long long int is %d\n", sizeof(lli));
	printf("size of char pointer is %d\n", sizeof(p));
	printf("size of int pointer is %d\n", sizeof(ip));
	printf("size of float is %d\n", sizeof(f));
	printf("size of double is %d\n", sizeof(d));
	printf("size of size_t is %d\n", sizeof(s));
}
