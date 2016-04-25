#include <stdio.h>

int bis(int x, int m)
{
	return x | m;
}

int bic(int x, int m)
{
	return x & (~m);
}

int bool_or(int x, int y)
{
	int result = bis(x, y);
	return result;
}

int bool_xor(int x, int y)
{
	int result = bis(bic(x, y), bic(y, x));
	return result;
}

int c_expression_equal(int x, int y)
{
	if (!(x ^ y))
		return 1;
	else
		return 0;
}

int main(int argc, char *argv[])
{
	/*
	int x = 0x87654321;
	printf("boolean op, only least byte: 0x%x \n", x & 0xFF);
	int higher_mask = ~0 ^ 0xFF;
	printf("boolean op, change higher bytes: 0x%x \n", x ^ higher_mask);
	printf("boolean op, all ones least byte: 0x%x \n", x | 0xFF);
	
	if (argc != 3) {
		printf("Usage: %s x y\n", argv[0]);
		return 0;
	}
	
	int x, y;
	sscanf(argv[1], "%x", &x);
	sscanf(argv[1], "%x", &y);*/
	
	printf("%x or %x is %x \n", 0x1111, 0x0001, bool_or(0x1111, 0x0001));
	printf("%x xor %x is %x \n", 0x1111, 0x0001, bool_xor(0x1111, 0x0001));
	
	printf("%x and %x is %s \n", 0x1111, 0x0001, c_expression_equal(0x1111, 0x0001)?"equal":"not equal");
	printf("%x and %x is %s \n", 0x1111, 0x1111, c_expression_equal(0x1111, 0x1111)?"equal":"not equal");
}
