/*
 * Pi(x) computes trigonometric constant to the limits of
 *        machine accuracy for x real.
 * 
 *
 * by R.K.Owen,Ph.D.  08/14/92
 */

#include "accmath.h"

#ifdef TEST
#  include <stdio.h>
#endif

/* Use the quickly convergent method discovered by
 * Scotsman John Machin in 1706
 * "Calculus: One and Several Variables, 2nd Ed.", S.L.Salas & E. Hille
 * pg 518
 */
PRECISION Pi(void) {
	static PRECISION pi;
	static char FIRST = (char) (0 == 0);
	PRECISION t1, t2;
	const PRECISION one = 1.0, four = 4.0, five = 5.0, n239 = 239.0;
	if (FIRST) {
		FIRST = !FIRST;
#ifdef TEST
		printf("initializing Pi\n");
#endif
		t1 = one / five;
		t2 = one / n239;
		pi = four*(four*Atan0(t1) - Atan0(t2));
	}
	return pi;
}

#ifdef TEST

#include <math.h>

void main(void) {
	PRECISION px, Px, dx;

	px = (PRECISION) 4.0*atan(1.0);
	printf("should have a  initialization message here:\n");
	Px = (PRECISION) Pi();
	dx = px - Px;
	printf("%15.8f %15.8f %15.8e\n", px, Px, dx);
	printf("should have no initialization message here:\n");
	Px = (PRECISION) Pi();
	printf("%15.8f %15.8f %15.8e\n", px, Px, dx);
	return;
}
#endif /* TEST */
