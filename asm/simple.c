
#if 0

int exchange(int *xp, int y)
{
	int x = *xp;

	*xp = y;
	return x;
}


int simple_int(int *xp, int y)
{
	int t = *xp + y;
	*xp = t;
	return t;
}

unsigned long simple_unsigned(int *xp, int y)
{
	unsigned long t = *xp + y;
	*xp = (int)t;
	return t;
}



char simple_byte(char *xp, char y)
{
	char t = *xp + y;
	*xp = t;
	return t;
}

short simple_short(short *xp, short y)
{
	short t = *xp + y;
	*xp = t;
	return t;
}

#endif
long simple_long(long *xp, long y)
{
	long t = *xp + y;
	*xp = t;
	return t;
}

#if 0

char *simple_pointer(char **xp, char *y)
{
	char *t;
	*t = **xp + *y;
	**xp = *t;
	return t;
}


float simple_float(float *xp, float y)
{
	float t = *xp + y;
	*xp = t;
	return t;
}

double simple_double(double *xp, double y)
{
	double t = *xp + y;
	*xp = t;
	return t;
}

long double simple_long_double(long double *xp, long double y)
{
	long double t = *xp + y;
	*xp = t;
	return t;
}
#endif

