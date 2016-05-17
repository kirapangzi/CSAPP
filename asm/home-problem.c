#include <stdio.h>


typedef struct ELE *tree_ptr;

struct ELE {
	long val;
	tree_ptr left;
	tree_ptr right;
};

//3.70
long traverse(tree_ptr tp)
{
	long z = -9223372036854775808;
	if (!tp)
		return z;
	long x = tp->val; //rbx
	tp = tp->left;
	long y = traverse(tp);// r12
	tp = tp->right;
	z = traverse(tp);// rax
	z = ((z >= y)? z : y);
	return (z < x)? x : z;	
}
// traverse tp in rdi
// save rbx in rsp - 24
// rbp in rsp -16
// r12 in rsp -8
// alloc rsp -24
// rbp = rdi = tp
// rax = $value -9223372036854775808
// test tp
// if == 0 goto L9
// rbx = tp->val
// rdi p = tp->left
// call traverse
// r12 = rax
// rdi p = tp->right
// call traverse
// r12 : rax
// if r12>=rax rax = r12
// rax : rbx
// if rax < rbx rax = rbx
// L9
// restore rbx,rbp,r12
// dealloc rsp
// return

#if 0
//3.69
//trace tp in rdi
// eax = 0
// test tp
// if == 0 goto L3
// L5
// rax = *tp
// ele = (rdi + 16) /ele.right
// test rdi
// if !=0 goto L5
// L3
// return rax

//get the most right leaf value of the tree
long trace(tree_ptr tp)
{
	long result = 0;
	if (!tp)
		return 0;
	//result = tp->val;
	while (tp->right)
		tp = tp->right;
	return tp->val;
}

//3.68
int good_echo()
{
	char buf[4096] = {0};
	fgets((void *)buf, sizeof(buf), stdin);
	puts((void *)buf);
}

int main()
{
	good_echo();
}


//3.67
union ele {
	struct {
		int *p;
		int y;
	} e1;
	struct {
		int x;
		union ele *next;
	} e2;
};
void proc (union ele *up)
{
     up->e2.next->e1.y= *(up->e2.next->e1.p)-up->e2.x;
}

//3.62
typedef int ** Marray_t;
#define M 10

void transpose(Marray_t A)
{
	int i, j;
	for (i = 0; i < M; i++)
		for (j = 0; j < i; j++) {
			int t = A[i][j];
			A[i][j] = A[j][i];
			A[j][i] = t;
		}
}

//3.61
#if 1
int var_prod_ele(int n, int A[n][n], int B[n][n], int i, int k)
{
   int j;
   int result = 0;
   int *ap=A[i];
   int *bp=&B[0][k];
   for(j = 0; j < n; j++)
   {
	   result += *ap * *bp;
	   ap++;
	   bp+=n;
   }
	return result;
}
#else
int var_prod_ele(int n, int A[n][n], int B[n][n], int i, int k) {
	int j;
	int result = 0;
	for (j = 0; j < n; j++)
		result += A[i][j] * B[j][k];

	return result;
}

#endif

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

