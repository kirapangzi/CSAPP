#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int is_little_endian()
{
	unsigned short data = 0x1234;
	//unsigned char little = 0x34;
	//unsigned char *p = (void *)&data;

	if (*((unsigned char *)&data) == 0x34)
		return 1;
	else
		return 0;
}

int check_endian()
{
	printf("this machine use %s endian\n", is_little_endian()?"little":"big");
}

long long combine_words(long long x, long long y)
{
	return (x & 0xFF) | ((y >> 8) << 8);
}

int check_combine()
{
	printf("combine of 0x%llx and 0x%llx is %llx\n", 0x12, 0xFFFFFFFF, combine_words(0x12,0xFFFFFFFF));
}

unsigned replace_byte(unsigned x, int i, unsigned char b)
{
	unsigned temp = x;
	/* won't change the orignal value */
	unsigned char *p = (void *)&temp;
	if ((i >=0) && (i < sizeof(unsigned))) {
		p[i] = b;
		return temp;
	} else {
		printf("please input right replace position within the unsigned\n");
		return 0;
	}
}

int evaluation(int x)
{
	printf("any bit of x 0x%x equals 1: %s\n", x, (x)?"true":"false");
	printf("any bit of x 0x%x equals 0: %s\n", x, (x ^ (~0))?"true":"false");
	
	int w = sizeof(int)<<3;
	/* Note the signed shift may cause the upper bits to be ones*/
	printf("any bit int lsb of x 0x%x equals 1: %s\n", x, 
		(((unsigned)x << (w-8)) >> (w-8))?"true":"false");
	printf("any bit int lsb of x 0x%x equals 0: %s\n", x, 
		((((unsigned)x << (w-8)) >> (w-8)) ^ 0xFF)?"true":"false");
}

int int_shifts_are_arithmetic_may_bugy()
{
	short i = 0x1;
	short shift_length = (sizeof(short) << 3) - 1;

	/* Note here should cast the result of the first shift */
	short result = (short)(i << shift_length) >> shift_length;
	
	printf("%x shift to be %x, shift back %x\n", i, i << shift_length, result);

	unsigned long long y = i;
	printf("%x shift to be %llx %llx %llx\n", y, y << 15, y << 31, y << 63);
	
	if (result != i)
		return 1;
	else
		return 0;
}

int int_shifts_are_arithmetic()
{
	short i = 0x8000;	
	short shift_length = (sizeof(short) << 3) - 1;
	short result = i >> shift_length;
	
	printf("%x shift to be %x\n", i, result);	
	if (result != 0x1)
		return 1;
	else
		return 0;
}

void fake_use_logic_shift()
{
	unsigned short ui = 0x8000;
	short shift_length = (sizeof(short) << 3) - 1;
	unsigned short uresult = ui >> shift_length;
	
	if (uresult == 0x1)
		printf("%x shift %d length to be %x, it's logic shift \n", ui, shift_length, uresult);
}

unsigned srl(unsigned x, int k)
{
	/* Perform shift arithmetically */
	unsigned xsra = (int)x >> k;
	
	int length = sizeof(unsigned) << 3;
	unsigned mask = (unsigned)(~0) >> k;
	
	if ((k < 0) || (k >= length)) {
		printf("invalid shift length\n");
		return 0;
	}
	printf("orignal 0x%x sra 0x%x result 0x%x\n", x, xsra, xsra & mask);
	return xsra & mask;
}

int sra(int x, int k) {
	/* Perform shift logically */
	int xsrl = (unsigned) x >> k;

	int length = sizeof(int) << 3;
	
	int mask;
	
	if ((k < 0) || (k >= length)) {
		printf("invalid shift length\n");
		return 0;
	}
	
	mask = (int)0x80000000 >> (k - 1);

	printf("orignal 0x%x srl 0x%x result 0x%x\n", x, xsrl, 
		(k == 0)? x :((x >= 0)? xsrl : (xsrl | mask)));

	return (k == 0)? x :((x >= 0)? xsrl : (xsrl | mask));
}

/* Return 1 when any odd bit of x equals 1; 0 otherwise.
Assume w=32. */
int any_odd_one(unsigned x)
{
	unsigned mask_32 = 0x55555555;
	return x && (x & mask_32);
}

int odd_ones(unsigned x)
{
	x ^= x >> 16;
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;
	return x & 1;
}

/*
* Generate mask indicating leftmost 1 in x. Assume w=32.
* For example 0xFF00 -> 0x8000, and 0x6600 --> 0x4000.
* If x = 0, then return 0.
*/
int leftmost_one(unsigned x)
{
	x |= x >> 16;
	x |= x >> 8;
	x |= x >> 4;
	x |= x >> 2;
	x |= x >> 1;
	return x ^ (x >> 1);
}

/* The following code does not run properly on some machines */
int bad_int_size_is_32() {
/* Set most significant bit (msb) of 32-bit machine */
	int set_msb = (int)((long long)1 << 31);
	/* Shift past msb of 32-bit word */
	int beyond_msb = (int)((long long)1 << 32);
	
	/* set_msb is nonzero when word size >= 32
	beyond_msb is zero when word size <= 32 */
	return set_msb && !beyond_msb;
}

/*
* Mask with least signficant n bits set to 1
* Examples: n = 6 --> 0x2F, n = 17 --> 0x1FFFF
* Assume 1 <= n <= w
*/
int lower_one_mask(int n)
{
	int w = sizeof(int) << 3;
	return (unsigned)~0 >> (w - n);
}

/*
* Do rotating left shift. Assume 0 <= n < w
* Examples when x = 0x12345678 and w = 32:
* n=4 -> 0x23456781, n=20 -> 0x67812345
*/
unsigned rotate_left(unsigned x, int n)
{
	int w = sizeof(unsigned) << 3;
	unsigned higher = x >> (w - n);
	unsigned lower = x << n;
	return lower | higher;
}

/*
* Return 1 when x can be represented as an n-bit, 2’s complement
* number; 0 otherwise
* Assume 1 <= n <= w
*/
int fits_bits(int x, int n)
{
	int w = sizeof(int) << 3;
	return n == w || !((unsigned)x >> n);
}

/* Declaration of data type where 4 bytes are packed
into an unsigned */
typedef unsigned packed_t;
/* Extract byte from word. Return as signed integer */
int xbyte(packed_t word, int bytenum);

/* Failed attempt at xbyte */
int xbyte_bugy(packed_t word, int bytenum)
{
	return (word >> (bytenum << 3)) & 0xFF; // always return positive
}

int xbyte(packed_t word, int bytenum)
{
	return (char)((word >> (bytenum << 3)) & 0xFF);
}

/* Copy integer into buffer if space is available */
/* WARNING: The following code is buggy */
void copy_int_bugy(int val, void *buf, int maxbytes) {
	if (maxbytes-sizeof(val) >= 0) // sizeof returns size_t which is unsigned, so max_bytes - sizeof(val) gets a unsigned value and always >= 0
		memcpy(buf, (const void *) &val, sizeof(val));
}

void copy_int(int val, void *buf, int maxbytes) {
	if (maxbytes - (int)sizeof(val) >= 0) 
		memcpy(buf, (const void *) &val, sizeof(val));
}

/* Addition that saturates to TMin or TMax */
int saturating_add(int x, int y)
{
	//long long res = x + y;
	int res2 = x + y;
	int w = sizeof(int) << 3;
	//int shift_sign = w - 1;
	
	int x_signed = (x >> (w - 1)) & 0x1;
	int y_signed = (y >> (w - 1)) & 0x1;
	
	int res2_signed = (res2 >> (w - 1)) & 0x1;
	//int res_signed = (res >> w) & 0x1;
	
	int pos_flow = !x_signed & !y_signed & res2_signed;
	int neg_flow = x_signed & y_signed & !res2_signed;
	
	// this the way how to take condition
	(pos_flow) && (res2 = INT_MAX);
	(neg_flow) && (res2 = INT_MIN);
	
	return res2;
}

int general_tsub_ok_bugy(void *x, void *y, size_t size)
{
	long long real_result = (long long)*(long long *)x - (long long)*(long long *)y;
	long long result;
	if (size == 1)
		result = (char)*(char *)x - (char)*(char *)y;
	else if (size == 2)
		result = (short)*(short *)x - (short)*(short *)y;
	else if (size == 4)
		result = (int)*(int *)x - (int)*(int *)y;
	else {
		printf("not supported\n");
		return 0;
	}
	printf("%x and %x can%s sub to be %x, real %llx\n", 
		*(int *)x, *(int *)y, (real_result == result)?"":"not", result, real_result);
	
	return (real_result == result);
}


/* Determine whether arguments can be subtracted without overflow */
int tsub_ok(int x, int y)
{
	//return general_tsub_ok((void *)&x, (void *)&y, sizeof(int));
	
	long long real_res = (long long)x - (long long)y;
	int res = x - y;

	printf("%x and %x can%s sub to be %x, real %llx\n", 
		x, y, (real_res == res)?"":"not", res, real_res);
	
	return (real_res == res);
}

int signed_high_prod(int x, int y)
{
	long long result = (long long)x * (long long)y;
	//printf("%x %d and %x %d multiplication %llx %lld, higher %x\n", 
		//x, x, y, y, result, result, result>>32);
		
	return result >> 32;
	/*
	int w = sizeof(int) << 3;
	int signed_mask = 0x1 << (w - 1);
	int x_signed = x & signed_mask;
	int y_signed = y & signed_mask;

	if (x_signed && !y_signed) || (!x_signed && y_signed)
	
	unsigned long long result = (unsigned long long)x * (unsigned long long)y;

	unsigned higher = result >> 32;*/

	
}

/*
(x
 . y

) mod 2w = [(x + xw.12w) . (y + yw.12w)] mod 2w (2.18)
= [x . y + (xw.1y + yw.1x)2w + xw.1yw.122w] mod 2w
= (x . y) mod 2w

*/
unsigned int unsigned_high_prod(unsigned x, unsigned y)
{
	unsigned long long result = (unsigned long long)x * (unsigned long long)y;
	int ix = (int)x;
	int iy = (int)y;
	long long higher = signed_high_prod(ix , iy);
	printf("%x %d and %x %d higher1 %llx\n", 
		x, x, y, y, higher);
	higher += (long long)(((unsigned)ix >> 31) * iy) + (long long)(((unsigned)iy >> 31) * ix);
	printf("%x %d and %x %d higher2 %llx\n", 
		x, x, y, y, higher);
	/* so 2pwr 2w won't change result*/
	higher = higher + ((long long)(((unsigned)ix >> 31) *((unsigned)iy >> 31)) << 32);

	printf("%x %d and %x %d multiplication %llx %lld, higher %llx\n", 
		x, x, y, y, result, result, higher);
	
	return (unsigned)higher;
}

unsigned unsigned_high_prod2(unsigned x, unsigned y)
{
	unsigned long long result = (unsigned long long)x * (unsigned long long)y;
	return (unsigned)(result >> 32);
}

int multiply_const(int x, const int k)
{
	switch (k) {
		case 17:
			return ((x << 4) + x);
		case -7:
			return (x - (x << 3));
		case 60:
			return ((x << 6) - (x << 2));
		case -112:
			return ((x << 4) - (x << 7));
		default:
			printf("not support\n");
	}
	return 0;
}

/* Divide by power of two. Assume 0 <= k < w-1 */
int divide_power2(int x, int k)
{
	int w = sizeof(int) << 3;
	
	int signed_mask = 0x1 << (w - 1);
	int x_signed = x & signed_mask;
	int bias = 0;
	(x_signed) && (bias = ((0x1 << k) - 1));
	
	return (x + bias) >> k;	
}

/* not replicate overflow, another realization of threefourths */
int mul3div4_no_overflow(int x)
{
	int x_signed = x & (0x1 << ((sizeof(int)<<3) - 1));
	int bias = 0;
	(x_signed) && (bias = 3);
	//printf("x %x %d\n", x,x);
	//printf("bias %d\n", bias);
	/* found bug here: associativity, should use bracket () of shift*/
	long long mul = (((long long)x << 1) + (long long)x);
	//printf("mul %llx %lld\n", mul, mul);
	long long div = (mul + bias) >> 2;
	//printf("div %llx %lld\n", div, div);
	return (int)div;
}

/* replicate overflow */
int mul3div4(int x)
{
	int mul = (x << 1) + x;	
	printf("mul %x %d\n", mul, mul);
	/* found bug here: shift input error, better use 32 to instead or use previous func*/
	int sign = (mul & (0x1 << ((sizeof(int)<<3) - 1)));
	int bias = 0;
	
	(sign) && (bias = 3);

	//printf("%x %d mul3div4 %x %d %x %d\n", x, x, ((mul + bias) >> 2), ((mul + bias) >> 2),
		 //divide_power2(mul, 2),  divide_power2(mul, 2));
	return ((mul + bias) >> 2);
	//return divide_power2(((x << 1) + x), 2);
}


int get_bias(int x, int k)
{
	int w = sizeof(int) << 3;	
	int signed_mask = 0x1 << (w - 1);
	int x_signed = x & signed_mask;
	int bias = 0;
	(x_signed) && (bias = ((0x1 << k) - 1));
	return bias;
}

int threefourths(int x)
{
	int bias_2 = get_bias(x, 2);
	int bias_1 = get_bias(x, 1);
	return ((x + bias_2) >> 2) + ((x + bias_1) >> 1);
}

/*
 * reference
 * My Solution
 *
 * A: (~0) << n or ~((1 << n) - 1)
 * B: ((1 << n) - 1) << m
 */
int generate_repeat_pattern(int a, int k, int j)
{
	unsigned z = 0xffffffff;
	if (a == 0)
		return z << k;
	else if (a == 0x1)
		return ((z << (k + j)) ^ (z << j));
	else
		return 0;
}

#if 0 
float fpwr2(int x)
{
	/* Result exponent and fraction */
	unsigned exp, frac;
	unsigned u;
	if (x < -149) {
		/* Too small. Return 0.0 */
		exp = 0;
		frac = 0;
	} else if (x < -126) {
		/* Denormalized result */
		exp = 0;
		frac = 0x400000 >> (-x - 126);
	} else if (x < 128) {
		/* Normalized result. */
		exp = x + 127;
		frac = 0;
	} else {
		/* Too big. Return +oo */
		exp = 0xff;
		frac = 0;
	}
	
	/* Pack exp and frac into 32 bits */
	u = exp << 23 | frac;
	/* Return as float */
	return u2f(u);
}
#endif

/* Access bit-level representation floating-point number */
typedef unsigned float_bits;

/* If f is denorm, return 0. Otherwise, return f */
float_bits float_denorm_zero(float_bits f) {
	/* Decompose bit representation into parts */
	unsigned sign = f>>31;
	unsigned exp = f>>23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;
	if (exp == 0) {
		/* Denormalized. Set fraction to 0 */
		frac = 0;
	}
	/* Reassemble bits */
	return (sign << 31) | (exp << 23) | frac;
}

/* Compute -f. If f is NaN, then return f. */
float_bits float_negate(float_bits f)
{
	unsigned sign = f>>31;
	unsigned exp = f>>23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	if ((exp == 0xFF) && (frac != 0))
		return f;
	return (!sign << 31) | (exp << 23) | frac;
}

/* Compute |f|. If f is NaN, then return f. */
float_bits float_absval(float_bits f)
{
	unsigned sign = f>>31;
	unsigned exp = f>>23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	if ((exp == 0xFF) && (frac != 0))
		return f;

	return exp << 23 | frac;
}

/* Compute 2*f. If f is NaN, then return f. */
float_bits float_twice(float_bits f)
{
	unsigned sign = f>>31;
	unsigned exp = f>>23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	if ((exp == 0xFF) && (frac != 0))
		return f;

	if ((exp == 0xFF) && (frac == 0))
		return f;
	else if (exp == 0xFE) {
		exp += 1;
		frac = 0;
	} else if (exp == 0) {
		if (frac & 400000) {
			exp = 1;
			frac = (frac & 0x3FFFFF) << 1;
		} else
			frac = frac << 1;
	} else
		exp += 1;

	return (sign << 31) | (exp << 23) | frac;
}

/* Compute 0.5*f. If f is NaN, then return f. */
float_bits float_half(float_bits f)
{
	unsigned sign = f>>31;
	unsigned exp = f>>23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	//NaN
	if ((exp == 0xFF) && (frac != 0))
		return f;
	//infinite
	if ((exp == 0xFF) && (frac == 0)) {
		return f;
	} else if (exp == 0x1) {
		exp = 0;
		frac += (0x1 << 23);
		frac = frac >> 1;
	} else if (exp == 0)
		frac = frac >> 1;
	else
		exp -= 1;

	return (sign << 31) | (exp << 23) | frac;
}

/*
* Compute (int) f.
* If conversion causes overflow or f is NaN, return 0x80000000
*/
int float_f2i(float_bits f)
{
	unsigned sign = f>>31;
	unsigned exp = f>>23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	unsigned limit = 0x80000000;
	int result = 0;

	// we should avoid multiple shift
	unsigned higher = 0x1 << 23;
	int exp_value = exp -127;
	frac += higher;
	

	//NaN
	if ((exp == 0xFF) && (frac != 0))
		return limit;
	//infinite
	if ((exp == 0xFF) && (frac == 0))
		return limit;
	// overflow
	if (exp_value >= 31)
		return limit;
	
	if (exp_value >= 23) {
		result = (sign << 31) | (frac << (exp_value - 23));
	} else if (exp - 127 >= 0) {
		result = (sign << 31) | (frac >> (23 - exp_value));
	} else 
		result = 0;
	return result;

}

/* Compute (float) i */
float_bits float_i2f(int i)
{
	unsigned sign;
	unsigned exp;
	unsigned frac;

	int j;

	if (i == 0x80000000) {
		sign = 1;
		exp = 127 + 31;
		frac = 0;
		return (sign << 31) | (exp << 23) | frac;
	} 
	if (i == 0) 
		return 0;
	
	sign = (unsigned)i >> 31;
	//remove sign
	if (sign)
		i = -i;
	//get most 
	j = leftmost_one(i);
	frac = i ^ j;
	printf("i %x j %x frac %x\n", i, j, frac);

	j = j >> 1;
	int j_bits = 0;
	while (j != 0) {
		j = j >> 1;
		j_bits++;
	}	
	if (j_bits < 23) 
		frac = frac << (23 - j_bits);
	if (j_bits > 23) {
		frac = frac >> (j_bits -23);
	}
	exp = 127 + j_bits;
	return (sign << 31) | (exp << 23) | frac;
}


int main(int argc, char *argv[])
{
	if (argc > 1) {
		int i = (int)strtoul(argv[1], NULL, 0);
		unsigned k;
		float f1;
		k = float_i2f(i);
		f1 = *(float *)&k;
		printf("%x %d float_i2f %x %f\n", i, i, k, f1);
	}
	
#if 0

	if (argc > 1) {
		unsigned i = strtoul(argv[1], NULL, 0);
		int j = 0;
		float f1;
		j = float_f2i(i);
		f1 = *(float *)&i;
		printf("%x %f float_f2i %d\n", i, f1, j);
	}
	
	unsigned i = 0x40000000;
	float f1;
	f1 = *(float *)&i;
	printf("%x is %f\n",i,f1);



 	
	if (argc > 1) {
		unsigned i = strtoul(argv[1], NULL, 0);
		unsigned j = 0;
		float f1, f2;
		j = float_half(i);
		f1 = *(float *)&i;
		f2 = *(float *)&j;
		printf("%x float_half %x\n", i, j);
		printf("float %.10f float_half %.10f\n", f1, f2);
	} 


	unsigned i;
	for (i = 0; i < UINT_MAX; i++)
		printf("%x float_negate %x\n", i, float_negate(i));

	printf("generate_repeat_pattern %d %d %d is %x\n", 0, 31, 0, generate_repeat_pattern(0,31,0));
	printf("generate_repeat_pattern %d %d %d is %x\n", 1, 4, 4, generate_repeat_pattern(1,4,4));
	printf("generate_repeat_pattern %d %d %d is %x\n", 1, 8, 8, generate_repeat_pattern(1,8,8));

	int test[6] = {0x80000000, 0x7fffffff, 0xffffffff, 0, -5, 5};
	//int test[2] = {-5, 5};
	int i;
	for (i = 0; i < 6; i++)
		printf("%x %d threefourths is by_calc %x %d by_func_threefourths %x %d "
			"by_func_mul3div4_no_overflow %x %d \n", 
			test[i], test[i], (test[i]/4)*3, (test[i]/4)*3, 
			threefourths(test[i]), threefourths(test[i]), 
			mul3div4_no_overflow(test[i]), mul3div4_no_overflow(test[i]));


	//printf("%x %d mul3div4 is by_calc %x %d by_func %x %d\n", 
	//	0x80000000, 0x80000000, (0x80000000 * 3)/4, (0x80000000 * 3)/4, mul3div4(0x80000000), mul3div4(0x80000000));
	printf("%x %d mul3div4 is by_calc %x %d by_func %x %d %x %d\n", 
		0x7FFFFFFF, 0x7FFFFFFF, (0x7FFFFFFF * 3)/4, (0x7FFFFFFF * 3)/4, 
		mul3div4(0x7FFFFFFF), mul3div4(0x7FFFFFFF),
		mul3div4_no_overflow(0x7FFFFFFF), mul3div4_no_overflow(0x7FFFFFFF));
	//printf("%x %d mul3div4 is by_calc %x %d by_func %x %d\n", 
	//	0xFFFFFFFF, 0xFFFFFFFF, (0xFFFFFFFF * 3)/4, (0xFFFFFFFF * 3)/4, mul3div4(0xFFFFFFFF), mul3div4(0xFFFFFFFF));
	//printf("%x %d mul3div4 is by_calc %x %d by_func %x %d\n", 
	//	0, 0, (0 * 3)/4, (0 * 3)/4, mul3div4(0), mul3div4(0));


	printf("%d divide %d is by_shift %d by_calc %d by_func %d\n", 
		-5, 2, (-5>>1), (-5/2), divide_power2(-5, 1));

	int a[5] = {17, -7, 60, -112, 20};
	int i;
	for (i = 0; i < 5; i++)
		printf("%d multiply %d is %d\n", 0x1234, a[i], multiply_const(0x1234, a[i]));

	// test signed_high_prod;
	signed_high_prod(0xFFFFFFFF,0xFFFFFFFF);
	signed_high_prod(0x80000000,0x80000000);
	signed_high_prod(0x80000000,0x7FFFFFFF);
	signed_high_prod(0x7FFFFFFF,0x7FFFFFFF);

	unsigned_high_prod(0xFFFFFFFF,0xFFFFFFFF);
	unsigned_high_prod(0x80000000,0x80000000);
	unsigned_high_prod(0x80000000,0x7FFFFFFF);
	unsigned_high_prod(0x7FFFFFFF,0x7FFFFFFF);

	tsub_ok(0x80000000, 0x7FFFFFFF);
	tsub_ok(0x7FFFFFFF, 0x80000000);
	tsub_ok(0x80000000, 0x1);
	tsub_ok(0x7FFFFFFF, 0xffffffff);

	printf("%x and %x %x saturating_add %x\n", 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF + 0x7FFFFFFF, saturating_add(0x7FFFFFFF, 0x7FFFFFFF));
	//printf("%x and %x saturating_add %x\n", 0xfFFFFFFF, 0xfFFFFFFF, saturating_add(0xfFFFFFFF, 0xfFFFFFFF));
	printf("%x and %x %x saturating_add %x\n", 0x80000000, 0x80000000, 0x80000000 + 0x80000000, saturating_add(0x80000000, 0x80000000));
	//printf("%x and %x saturating_add %x\n", 0xfFFFFFFF, 0x7FFFFFFF, saturating_add(0xfFFFFFFF, 0x7FFFFFFF));

	int i;
	char buf[6] = {0};
	int val;
	unsigned char *p = (void *)&val;
	for (i = 0; i < 4; i++)
		p[i] = 'a' + i;
	for (i = 0; i < 6; i++) {
		copy_int(val, (void *)buf, i);
		printf("after copy buf %s\n", buf);
	}

	int i ;
	for (i = 0; i < 4; i++) {
		printf("the %d of %x is %d\n", i, 0x12345678, xbyte(0x12345678, i));
		printf("the %d of %x is %d\n", i, 0xabcdefab, xbyte(0xabcdefab, i));
	}

	int i;
	for (i = 1; i <= sizeof(int)*8; i++)
		printf("%d bits of %x fit bits can %s \n", i, 0x12345678, fits_bits(0x12345678, i)?"":"not");
	for (i = 1; i <= sizeof(int)*8; i++)
		printf("%d bits of %x fit bits can %s \n", i, 0xffff, fits_bits(0xffff, i)?"":"not");

	int i;
	for (i = 0; i < sizeof(int)*8; i++)
		printf("rotate %d left of %x is %x\n", i, 0x12345678, rotate_left(0x12345678, i));

	int i;
	for (i = 1; i <= sizeof(int)*8; i++)
		printf("lower %d bits mask is %x\n", i, lower_one_mask(i) );

	printf("this machine's int is%s 32 bits\n", bad_int_size_is_32()?"":" not" );
	printf("this machine's long integer is %d bytes\n", sizeof(long) );

	printf("left most one of %x is %x\n", 0, leftmost_one(0));
	printf("left most one of %x is %x\n", 1, leftmost_one(1));
	printf("left most one of %x is %x\n", 0xFFFFFFFF, leftmost_one(0xFFFFFFFF));
	printf("left most one of %x is %x\n", 0x1000, leftmost_one(0x1000));
	printf("left most one of %x is %x\n", 0x333333, leftmost_one(0x333333));

	//check_endian();
	if (argc > 2) {
		long long x = strtoull(argv[1], NULL, 0);
		long long y = strtoull(argv[2], NULL, 0);
		printf("combine of 0x%llx and 0x%llx is %llx\n", x, y, combine_words(x, y));
	} else
		check_combine();

	int i;
	unsigned x = 0x12345678;
	unsigned char b = 0x1F;
	for (i = 0; i < sizeof(unsigned); i++)
		printf("replace byte 0x%x %d byte of 0x%x to be 0x%x\n", x, i, b, 
			replace_byte(x,i,b));
	printf("replace byte 0x%x %d byte of 0x%x to be 0x%x\n", x, 5, b, 
			replace_byte(x,5,b));	

	evaluation(0xFFFFFFFF);
	evaluation(0x0);
	evaluation(0x10FF);
	evaluation(0x1000);
	evaluation(0x10);
	evaluation(INT_MIN);

	printf("this machine's int shifts are %s\n", 
		int_shifts_are_arithmetic()?"arithmetic":"logic");

	fake_use_logic_shift();		


	/* test validity*/
	srl(0x80000000, 2);
	srl(0x80000000, 0);
	srl(0x80000000, 31);
	
	srl(0, 2);
	srl(0, 0);
	srl(0, 31);
	
	srl(0x7FFFFFFF, 2);
	srl(0x7FFFFFFF, 0);
	srl(0x7FFFFFFF, 31);

	srl(0xFFFFFFFF, 2);
	srl(0xFFFFFFFF, 0);
	srl(0xFFFFFFFF, 31);
	
	srl(0x00000101, 2);
	srl(0x00000101, 0);
	srl(0x00000101, 31);

	sra(0x80000000, 2);
	sra(0x80000000, 0);
	sra(0x80000000, 31);
	
	sra(0, 2);
	sra(0, 0);
	sra(0, 31);
	
	sra(0x7FFFFFFF, 2);
	sra(0x7FFFFFFF, 0);
	sra(0x7FFFFFFF, 31);

	sra(0xFFFFFFFF, 2);
	sra(0xFFFFFFFF, 0);
	sra(0xFFFFFFFF, 31);
	
	sra(0x00000101, 2);
	sra(0x00000101, 0);
	sra(0x00000101, 31);

	printf("any odd one in %x is %s\n", 0, any_odd_one(0)?"true":"false");
	printf("any odd one in %x is %s\n", 0xffffffff, any_odd_one(0xffffffff)?"true":"false");
	printf("any odd one in %x is %s\n", 0xAAAAAAAA, any_odd_one(0xAAAAAAAA)?"true":"false");
	printf("any odd one in %x is %s\n", 0x1, any_odd_one(0x1)?"true":"false");
	

	printf("odd ones in %x is %s\n", 0, odd_ones(0)?"true":"false");
	printf("odd ones in %x is %s\n", 0xffffffff, odd_ones(0xffffffff)?"true":"false");
	printf("odd ones in %x is %s\n", 0xAAAAAAAA, odd_ones(0xAAAAAAAA)?"true":"false");
	printf("odd ones in %x is %s\n", 0x1, odd_ones(0x1)?"true":"false");
#endif

	
}
