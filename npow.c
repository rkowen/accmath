/*
 * Npow(x,N) computes the integer N power of x to the limits of
 *        machine accuracy for x real.
 * 
 *
 * by R.K.Owen,Ph.D.  08/15/92
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#  define _INTEGER_
typedef int INTEGER;
#endif

#include "accmath.h"

PRECISION Npow(PRECISION x, INTEGER N) {
	PRECISION prod = 1.0, bpow;
	const PRECISION zero = 0.0, one = 1.0;
	register PRECISION t;
	INTEGER mask = 1;

	if (N == 0) return one;		/* 0^0 == 1 */
	if (x == zero) return zero;
	if (N < 0) {
		N = -N;
		x = one/x;
	}
	if (N == 1) return x;
	if (N == 2) return x*x;
	if (N == 3) return x*x*x;
	if (N == 4) {
		t = x*x;
		return t*t;
	}

	bpow = x;
	while (N) {
		if (mask & N) prod *= bpow;
		N >>= 1;
		if (!N) break;	/* avoid unnecessary overflow */
		bpow *= bpow;
	}
	return prod;
}

#ifdef TEST

#include <stdio.h>
#include <math.h>

void main(void) {
	PRECISION x, px, Px, dx;
	const PRECISION two = 2.0;
	int i;

	for (i = -10; i <= 10; i++) {
		x = (PRECISION) i;
		px = (PRECISION) pow(two,x);
		Px = (PRECISION) Npow(two,i);
		dx = px - Px;
		printf("%3.d %15.8f %15.8f %15.8e\n", i, px, Px, dx);
	}
	return;
}
#endif /* TEST */
