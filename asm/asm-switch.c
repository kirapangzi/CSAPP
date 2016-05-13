#include <stdio.h>

#if 0
int main()
{
	int i;
	int res = 0;
	switch (i) {
		case 100:
			res = 100;
			break;
		case 102:
			res =102;
		case 103:
			res += 103;
			break;
		case 105:
			res = 105;
			break;
		default:
			;
		
	}
	return res;
}
#endif

int switch_eg(int x, int n) {
	int result = x;

	switch (n) {

	case 100:
	result *= 13;
	break;

	 case 102:
	 result += 10;
	/* Fall through */

	case 103:
	result += 11;
	 break;

	case 104:
	 case 106:
	 result *= result;
	 break;

	 default:
	 result = 0;
	 }

	 return result;
}

