/*
 * Eps() computes machine relative precision (or eps)
 * 
 *
 * by R.K.Owen,Ph.D.  08/14/92
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#endif

#include "accmath.h"

#ifdef TEST
#  include <stdio.h>
#endif

PRECISION Eps(void) {
	const PRECISION half = 0.5, one = 1.0;
	static char FIRST = (char) (0 == 0);
	static PRECISION eps = 1.0;
	PRECISION neweps = half;
	if (FIRST) {
		FIRST = !FIRST;
#ifdef TEST
		printf("Initializing Eps\n");
#endif
		while (one + neweps != one) {
			eps = neweps;
			neweps *= half;
		}
	}
	return eps;
}

#ifdef TEST

void main(void) {
	PRECISION Ex, t1, t2;
	const PRECISION half = 0.5, one = 1.0;

	printf("should have a  initialization message here:\n");
	Ex = (PRECISION) Eps();
	printf("%15.8e\n", Ex);
	printf("should have no initialization message here:\n");
	Ex = (PRECISION) Eps();
	printf("%15.8e\n", Ex);
	t1 = one + Ex;
	t2 =  one + half*Ex;
	t1 -= one;
	t2 -= one;
	printf("%15.8e %15.8e\n", t1, t2);
	return;
}
#endif /* TEST */
