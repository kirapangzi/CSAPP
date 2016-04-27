#include <stdio.h>

#define src_t
#define dest_t

// test pp 3.4 and section 2.2.6
// result: casting from 
int main()
{
	//src
	//char c1 = 0xAB;
	char c1 = 0x23;
	//unsigned char c2 = 0x12;
	unsigned char c2 = 0xAB;
	int i1 = 0xABCDABCD;
	unsigned i2 = 0x12341234;

/*
	src_t v;
	dest_t *p;
	*p = (dest_t)v;
*/

	//dest
	int dest1;
	dest1 = (int)c2;

	unsigned dest2;
	dest2 = (unsigned)c2;

	int dest3;
	dest3 = (int)c2;

	char dest4;
	dest4 = (char)i1;
	//printf("%d %x, %d %x\n", i1, i1, dest4, dest4);
	
	unsigned char dest5;
	dest5 = (unsigned char)i2;

	int dest6 = (int)i2;

	printf("%d %d %d %d %d %d\n",
		dest1, dest2, dest3, dest4, dest5, dest6);
	printf("%x %x %x %x %x %x\n",
		dest1, dest2, dest3, dest4, dest5, dest6);
}
