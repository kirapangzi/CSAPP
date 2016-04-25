/* $begin show-bytes */
#include <stdio.h>
/* $end show-bytes */
#include <stdlib.h>
#include <string.h>
/* $begin show-bytes */

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len) {
    int i;
    for (i = 0; i < len; i++)
	printf(" %.2x", start[i]);    //line:data:show_bytes_printf
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(int)); //line:data:show_bytes_amp1
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float)); //line:data:show_bytes_amp2
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(void *)); //line:data:show_bytes_amp3
}
/* $end show-bytes */

void show_short(short x)
{
	show_bytes((byte_pointer) &x, sizeof(short));
}
void show_long(long x)
{
	show_bytes((byte_pointer) &x, sizeof(long));
}
void show_double(double x)
{
	show_bytes((byte_pointer) &x, sizeof(double));
}



void hexstr_to_binstr(unsigned char *str_in, unsigned char *str_out)
{
        int i = 0;
        unsigned char *p = str_out;
        //printf("hexstr_to_binstr : ", str_in[i]);
        for (i = 0; i < strlen(str_in); i++) {
        	//printf("%c ", str_in[i]);
                switch(toupper(str_in[i])) {
                case '0':
                	sprintf(p, "0000");
                	break;
                case '1':
                	sprintf(p, "0001");
                	break;
                case '2':
                	sprintf(p, "0010");
                	break;
               	case '3':
                	sprintf(p, "0011");
                	break;
                case '4':
                	sprintf(p, "0100");
                	break;
                case '5':
                	sprintf(p, "0101");
                	break;
                case '6':
                	sprintf(p, "0110");
                	break;
                case '7':
                	sprintf(p, "0111");
                	break;
                case '8':
                	sprintf(p, "1000");
                	break;
                case '9':
                	sprintf(p, "1001");
                	break;
                case 'A':
                	sprintf(p, "1010");
                	break;
                case 'B':
                	sprintf(p, "1011");
                	break;
                case 'C':
                	sprintf(p, "1100");
                	break;
                case 'D':
                	sprintf(p, "1101");
                	break;
                case 'E':
                	sprintf(p, "1110");
                	break;
                case 'F':
                	sprintf(p, "1111");
                	break;
                }
                //printf("%s ", p);
                p+=4;
        }
        //printf("\n");
}

void show_binary(void *buf, int size)
{
	unsigned char hex_buf[64] = {0};
        unsigned char bin_buf[64] = {0};
        unsigned char *p = buf;
        int i, j = 0;

	/* on little endian, the most significant value stored at last one byte */
        for (i = size -1 ; i >= 0; i--) {
		sprintf((void *)&hex_buf[j], "%.2x", p[i]);
		j += 2;
	}
	printf("hex string of input buf is 0x%s\n", hex_buf);
	hexstr_to_binstr(hex_buf, bin_buf);
        printf("binary string of input buf is %s\n", bin_buf);

	/*
        int ival = 3510593;
        float fval = (float) ival;
        
        unsigned char hex_buf[64] = {0};
        unsigned char bin_buf[64] = {0};
        
        sprintf(hex_buf, "%.8x", ival);
        printf("hex string of integer is 0x%s\n", hex_buf);
        hexstr_to_binstr(hex_buf, bin_buf);
        printf("binary string of integer is %s\n", bin_buf);

        memset(hex_buf, 0, 64);
        memset(bin_buf, 0, 64);
        int i;
        unsigned char *p = (void *)&fval;        
        unsigned char *value = hex_buf;
        //hex_buf[0] = '\0';
        for (i = sizeof(fval) -1 ; i >= 0; i--) {
		sprintf(value, "%.2x", p[i]);
		value += 2;
	}
	//hex_buf[sizeof(fval)*2] = '\0';
        printf("hex string of float is 0x%s\n", hex_buf);
        hexstr_to_binstr(hex_buf, bin_buf);
        printf("binary string of float is %s\n", bin_buf);*/

}


/* $begin test-show-bytes */
void test_show_bytes(int val) {
    int ival = val;
    float fval = (float) ival;
    int *pval = &ival;
    show_int(ival);
    show_float(fval);
    show_pointer(pval);
}
/* $end test-show-bytes */

void simple_show_a() {
/* $begin simple-show-a */
int val = 0x87654321;
byte_pointer valp = (byte_pointer) &val;
show_bytes(valp, 1); /* A. */
show_bytes(valp, 2); /* B. */
show_bytes(valp, 3); /* C. */
/* $end simple-show-a */
}

void simple_show_b() {
/* $begin simple-show-b */
int val = 0x12345678;
byte_pointer valp = (byte_pointer) &val;
show_bytes(valp, 1); /* A. */
show_bytes(valp, 2); /* B. */
show_bytes(valp, 3); /* C. */
/* $end simple-show-b */
}

void float_eg() {
  int x = 3490593;
  float f = (float) x;
  printf("For x = %d\n", x);
  show_int(x);
  show_float(f);

  x = 3510593;
  f = (float) x;
  printf("For x = %d\n", x);
  show_int(x);
  show_float(f);

}

void string_ueg() {
/* $begin show-ustring */
const char *s = "ABCDEF";
show_bytes((byte_pointer) s, strlen(s)); 
/* $end show-ustring */
}

void string_leg() {
/* $begin show-lstring */
const char *s = "abcdef";
show_bytes((byte_pointer) s, strlen(s)); 
/* $end show-lstring */
}

void show_twocomp() 
{
/* $begin show-twocomp */
    short x = 12345; 
    short mx = -x; 
    
    show_bytes((byte_pointer) &x, sizeof(short)); 
    show_bytes((byte_pointer) &mx, sizeof(short)); 
    show_binary((byte_pointer) &x, sizeof(short));
    show_binary((byte_pointer) &mx, sizeof(short));
/* $end show-twocomp */
}

int main(int argc, char *argv[])
{
    int val = 12345;

    if (argc > 1) {
	if (argc > 1) {
	    val = strtol(argv[1], NULL, 0);
	}
	printf("calling test_show_bytes\n");
	test_show_bytes(val);
    } else {
#if 0    
    	/*
	printf("calling show_twocomp\n");
	show_twocomp();
	printf("Calling simple_show_a\n");
	simple_show_a();
	printf("Calling simple_show_b\n");
	simple_show_b();
	printf("Calling float_eg\n");
	float_eg();
	printf("Calling string_ueg\n");
	string_ueg();
	printf("Calling string_leg\n");
	string_leg();
	*/
	//show_binary();
	/*show_bytes("12345", 6);
	const char *s = "abcdef";
	show_bytes((byte_pointer)s, strlen(s));*/
	//printf("calling show_twocomp\n");
	//show_twocomp();

	/*short int v = -12345;
	unsigned short uv = (unsigned short) v;
	printf("v = %d, uv = %u\n", v, uv);
	show_binary((byte_pointer) &v, sizeof(short));
	show_binary((byte_pointer) &uv, sizeof(unsigned short));*/

	unsigned u = 4294967295u; /* UMax_32 */
	int tu = (int) u;
	printf("u = %u, tu = %d\n", u, tu);
	show_binary((byte_pointer) &u, sizeof(unsigned));
	show_binary((byte_pointer) &tu, sizeof(int));
	

	short sx = -12345; /* -12345 */
	unsigned short usx = sx; /* 53191 */
	int x = sx; /* -12345 */
	unsigned ux = usx; /* 53191 */

	printf("sx = %d:\t", sx);
	show_bytes((byte_pointer) &sx, sizeof(short));
	printf("usx = %u:\t", usx);
	show_bytes((byte_pointer) &usx, sizeof(unsigned short));
	printf("x = %d:\t", x);
	show_bytes((byte_pointer) &x, sizeof(int));
	printf("ux = %u:\t", ux);
	show_bytes((byte_pointer) &ux, sizeof(unsigned));


	short sx = -12345; /* -12345 */
	unsigned uy = sx; /* Mystery! */
	printf("uy = %u:\t", uy);
	show_bytes((byte_pointer) &uy, sizeof(unsigned));
#endif

    int i = 3510593;
    float f = 3510593.0;
    short s = 128;
    long l = 3510593;
    double d = 3510593;

    //printf("i = %d 0x%x, f = %f 0x%x\n", i, i, f, (int)f);
    show_bytes((byte_pointer) &i, sizeof(int));
    show_binary((byte_pointer) &i, sizeof(int));
    show_bytes((byte_pointer) &f, sizeof(float));
    show_binary((byte_pointer) &f, sizeof(float));

    show_short(s);
    show_binary((byte_pointer) &s, sizeof(s));
    show_long(l);
    show_binary((byte_pointer) &l, sizeof(l));
    show_double(d);
    show_binary((byte_pointer) &d, sizeof(d));
    

    }
    return 0;
}
