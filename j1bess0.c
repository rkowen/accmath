/*
 * J1Bess0(x) computes the regular Bessel function of the First kind of order 1
 *            to the limits of machine accuracy for x real and small
 *
 * by R.K.Owen,Ph.D.  09/03/93
 */

#if 0
#  define TEST
#endif

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#endif

#include "accmath.h"

PRECISION J1Bess0(PRECISION x) {
	PRECISION sum = 0.0, newsum, x2, term;
	PRECISION inc = 2.0, nextinc = 4.0;
	x2 = x*x;
	newsum = term = 0.5*x;

	while (sum != newsum) {
		term *= (-x2/(inc*nextinc));
		inc = nextinc;
		nextinc += (PRECISION) 2.0;
		sum = newsum;
		newsum += term;
	}
	return sum;
}

#ifdef TEST

#include <stdio.h>

void main(void) {
	/* comparison values from tables compiled by Abramowitz & Stegun */
	PRECISION x[] = {0., 0.1, 0.2, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0};
	PRECISION jx[] = {
		0.0,
		0.0499375260,
		0.0995008326,
		0.2422684577,
		0.4400505857,
		0.5579365079,
		0.5767248078,
		0.4970941025,
		0.3390589585};
	PRECISION Jx, dx;
	int i, num = sizeof(x)/sizeof(x[0]);

	for (i = 0; i < num; ++i) {
		Jx = (PRECISION) J1Bess0(x[i]);
		dx = jx[i] - Jx;
		printf("%3.d %15.8f %15.8f %15.8f %15.8e\n",
				i, x[i], jx[i], Jx, dx);
	}
	return;
}
#endif /* TEST */
