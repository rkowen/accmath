/*
 * J0Bess0(x) computes the regular Bessel function of the First kind of order 0
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

PRECISION J0Bess0(PRECISION x) {
	PRECISION sum = 1.0, newsum, x2, term;
	PRECISION inc = 2.0;
	x2 = x*x;
	term = -0.25*x2;
	newsum = 1.0 - term;

	while (sum != newsum) {
		inc += (PRECISION) 2.0;
		term *= (-x2/(inc*inc));
		sum = newsum;
		newsum += term;
	}
	return sum;
}

#ifdef TEST

#include <stdio.h>

void main(void) {
	/* comparison values from tables compiled by Abramowitz & Stegun */
	PRECISION x[] = {0., 0.1, 0.2, 0.5, 1.0, 1.5, 2.0, 2.4, 
				2.4048255577};
	PRECISION jx[] = {
		1.0,
		0.997501562066040,
		0.990024972239576,
		0.938469807240813,
		0.765197686557967,
		0.511827671735918,
		0.223890779141236,
		0.002507683297244,
		0.0};
	PRECISION Jx, dx;
	int i, num = sizeof(x)/sizeof(x[0]);

	for (i = 0; i < num; ++i) {
		Jx = (PRECISION) J0Bess0(x[i]);
		dx = jx[i] - Jx;
		printf("%3.d %15.8f %15.8f %15.8f %15.8e\n",
				i, x[i], jx[i], Jx, dx);
	}
	return;
}
#endif /* TEST */
