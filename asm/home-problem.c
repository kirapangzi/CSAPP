#include <stdio.h>


//3.60


#if 0


//3.59
//save ebp
// new ebp
// eax = x
// edx = n
// edx -= 0x32 50
// cmp edx 0x5
// if edx > 5 goto 448
// goto 4*edx
// 438 [0,2] eax <<=2 return
// 43d [3] eax >>=2 return
// 442 [4] eax = eax + 2*eax = 3x
// 445 [5] eax *= eax
// 448 [1] eax += 0xa
// 44b return addr restore ebp
int switch_prob(int x, int n)
{
	int result = x;
	switch(n) {
	case 50:
	case 52:
		result <<= 2;
		break;		
	case 53:
		result >>= 2;
		break;	
	case 54:
		result *= 3;
	case 55:
		result *= result;
	case 51:
		result += 0xa;
	default:
		break;
	}
	return result;
}


//3.58
//L17 E
// result = edx = 17 return
//L13 A
// result = edx = *p1
// eax = *p2
// ecx = p1
// *p1 = *p2 return
//L14 B
// edx = p2, eax = *p2
// edx = *p2
// edx += *p1 ecx =p1
// eax = p2
// *p2 = edx return
//L15 C
// edx = p2
// *p2 = 15
// ecx = p1
// edx = *p1 return
//L16 D
// edx = p1
// eax = *p1
// ecx = p2
// *p2 = *p1
// edx =17 return
/* Enumerated type creates set of constants numbered 0 and upward */
typedef enum 
{MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} 
modex_t;
int switch3(int *p1, int *p2, modex_t action)
{
	int result = 0;
	switch(action) {
	case MODE_A:
		result = *p1;
		*p1 = *p2;
		break;
	case MODE_B:
  		result = *p1 + *p2;
  		*p2 = result;
		break;
	case MODE_C:
		*p2 = 15;
		result = *p1;
		break;
	case MODE_D:
		*p2 = *p1;
	case MODE_E:
		result = 17;
		break;
	default:
		result = -1;
		break;
	}
	return result;
}

int cread_alt(int *xp) 
{
	int result = 0;
	int *rp;
	/* conditional move won't let null pointer evaluate */
	rp = xp ? xp : &result;
	return *rp;
}


//3.56
// esi = x
// ebx = n
// edi = -1 = 0xffff ffff
// edx = 1
// L2
// eax = edx
// eax &= x
// edi ^= eax
// ecx = ebx = n
// edx <<= ecx(byte)
// test edx
// if != 0 goto L2
// result = eax = edi
int loop(int x, int n)
{
	int result = -1;
	int mask;
	for (mask = 1; mask != 0; mask <<= (char)n) {
		result ^= mask & x;
	}
	return result;
}

//3.54
// edx = y
// y -= z
// result = y
// res << 31
// res >> 31
// y *= x
// y ^ res
int decode2(int x, int y, int z)
{
	int result;
	y -= z;
	result = y;
	result = (result << 31) >> 31;
	y *= x;
	return result ^ y;
}
#endif

