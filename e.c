/*
 * E() computes the natural exponential base e
 *     to machine precision
 *
 * by R.K.Owen,Ph.D.  08/20/92
 */

#include "accmath.h"

#ifdef TEST
#  include <stdio.h>
#endif


PRECISION E(void) {
	static char FIRST = (char) (0 == 0);
	static PRECISION e = 0.0;
	PRECISION newe = 1.0, term = 1.0;
	int i=0;
	if (FIRST) {
		FIRST = !FIRST;
#ifdef TEST
		printf("Initializing E\n");
#endif
		while (e != newe) {
			e = newe;
			i++;
			term /= (PRECISION) i;
			newe += term;
		}
	}
	return e;
}

#ifdef TEST

#include <math.h>

void main(void) {
	PRECISION Ex, ex, dx;

	ex = exp(1.0);
	printf("should have a  initialization message here:\n");
	Ex = (PRECISION) E();
	dx = ex - Ex;
	printf("%15.8f %15.8f %15.8e\n", ex, Ex, dx);
	printf("should have no initialization message here:\n");
	Ex = (PRECISION) E();
	printf("%15.8f %15.8f %15.8e\n", ex, Ex, dx);
	return;
}
#endif /* TEST */
