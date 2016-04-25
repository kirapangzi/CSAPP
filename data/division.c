#include <stdio.h>
#include <stdlib.h>

int div16(int x)
{
	/* Compute bias to be either 0 (x >= 0) or 15 (x < 0) */
	int bias = (x >> 31) & 0xF;
	return (x + bias) >> 4;
}

int div32(int x)
{
	int bias = (x >> 31) & 0x1F;
	return (x + bias) >> 5;
}

int main(int argc, char *argv[])
{
	//get input number;
	if (argc > 1) {
		int i;
		for (i = 1; i < argc; i++) {
			int x = atoi(argv[i]);
			printf("%d div16 is %d, div32 is %d\n", x, div16(x), div32(x));
		}
	}
	return 0;
}
