/*
 * Phi(x) computes Fibonaci constant to the limits of
 *        machine accuracy for x real.
 * 
 *
 * by R.K.Owen,Ph.D.  08/15/92
 */

#include "accmath.h"

#ifdef TEST
#  include <stdio.h>
#endif


/* Phi is the limit as successive terms of the Fibonacci series
 * approaches infinity
 */
PRECISION Phi(void) {
	static PRECISION phi = 0.0;
	static char FIRST = (char) (0 == 0);
	const PRECISION half = 0.5, one = 1.0, five = 5.0;
	PRECISION newphi = half;
	if (FIRST) {
		FIRST = !FIRST;
#ifdef TEST
		printf("initializing Phi\n");
#endif
#if 1
	/* direct evaluation */
		phi = half*(one + Sqrt(five));
#else
	/* continued fraction definition */	/* may oscillate */
		while (phi != newphi) {
			phi = newphi;
			newphi = one/(one + newphi);
		}
		phi += one;
#endif
	}
	return phi;
}

#ifdef TEST

#include <math.h>

void main(void) {
	PRECISION px, Px, dx;

	px = (PRECISION) 0.5*(1.0 + sqrt(5.));
	printf("should have a  initialization message here:\n");
	Px = (PRECISION) Phi();
	dx = px - Px;
	printf("%15.8f %15.8f %15.8e\n", px, Px, dx);
	printf("should have no initialization message here:\n");
	Px = (PRECISION) Phi();
	printf("%15.8f %15.8f %15.8e\n", px, Px, dx);
	dx = 1.0 + Px*(1.0 - Px);
	printf("%15.8e\n",dx);
	return;
}
#endif /* TEST */
