/*
 * Erf0(x) computes the error function to the limits of
 *        machine accuracy for x real. Quickly convergent for |x| < 1.
 *
 * by R.K.Owen,Ph.D.  10/08/93
 *
 * Calls: Exp, Sqrt, Pi
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#endif

#include "accmath.h"

#ifdef TEST
#  include <stdio.h>
#endif

PRECISION Erf0(PRECISION x) {
	const PRECISION two = 2.0;
	PRECISION sum = 0.0, newsum = x, x2 = x*x, inc = 1.0, term = x;
	static PRECISION isqpi;
	static char FIRST = (0 == 0);
	int n;

	if (FIRST) {
		FIRST = !FIRST;
#ifdef TEST
		printf("Initializing Erf0\n");
#endif
		isqpi = two/Sqrt(Pi());
	}

	while (sum != newsum) {
		sum = newsum;
		inc += two;
		term *= (two/inc * x2);
		newsum += term;
	}
	return (isqpi * Exp(-x2) * sum);
}

#ifdef TEST

void main(void) {
	PRECISION x, Ex;
	PRECISION Tx[] = {
/* 0.0 */	0.00000000000000,
/* 0.1 */	0.11246291601829,
/* 0.2 */	0.22270258921048,
/* 0.3 */	0.32862675945913,
/* 0.4 */	0.42839235504667,
/* 0.5 */	0.52049987781304,
/* 0.6 */	0.60385609084793,
/* 0.7 */	0.67780119383742,
/* 0.8 */	0.74210096470766,
/* 0.9 */	0.79690821242284,
/* 1.0 */	0.84270079294971,
/* 1.1 */	0.88020506957409,
/* 1.2 */	0.91031397822964,
/* 1.3 */	0.93400794494065,
/* 1.4 */	0.95228511976265,
/* 1.5 */	0.96610514647531,
/* 1.6 */	0.97634838334465,
/* 1.7 */	0.98379045859078,
/* 1.8 */	0.98909050163574,
/* 1.9 */	0.99279042923526,
/* 2.0 */	0.99532226501896,
/* 2.1 */	0.99702053334367,
/* 2.2 */	0.99813715370203,
/* 2.3 */	0.99885682340265,
/* 2.4 */	0.99931148610336,
/* 2.5 */	0.99959304798256,
/* 2.6 */	0.99976396558348,
/* 2.7 */	0.99986566726006,
/* 2.8 */	0.99992498680534,
/* 2.9 */	0.99995890212190,
/* 3.0 */	0.99997790950300 };
	int i;

	printf("should have a  initialization message here:\n");
	for (i = 0; i < sizeof(Tx)/sizeof(Tx[0]); i++) {
		x = .1 * i;
		Ex = (PRECISION) Erf0(x);
		printf("%5.1f %15.8f %15.8f\n", x, Ex, Tx[i]);
	}
	printf("should have no initialization message here:\n");
	for (i = 0; i < sizeof(Tx)/sizeof(Tx[0]); i++) {
		x = .1 * i;
		Ex = (PRECISION) Erf0(x);
		printf("%5.1f %15.8f %15.8f\n", x, Ex, Tx[i]);
	}
	return;
}
#endif /* TEST */
