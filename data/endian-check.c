#include <stdio.h>

int main()
{
	//int i = 0x01234567;
	int i = 0xA0B0C0D0;
	unsigned char *p = NULL;
	int loop;
	// should use unsigned char to get the value.
	unsigned char ch;

	p = (void *)&i;
	for (loop = 0; loop < sizeof(i); loop++) {
		ch = p[loop];
		printf("content in %d byte of 0x%x is 0x%.2x %.2x\n", loop, i, p[loop], ch);
		//p++;
	}
}
