/*
 * Erfc0(x) computes the complementary error function to the limits of
 *        machine accuracy for x real. Quickly convergent for |x| > 1.
 *        The series is asymptotic to erfc(x).
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

PRECISION Erfc0(PRECISION x) {
	const PRECISION one = 1.0, two = 2.0;
	PRECISION sum = 0.0, newsum = 1.0/x,
		x2 = x*x, tx2 = -0.5*newsum*newsum,
		inc = 1.0, term = newsum;
	static PRECISION isqpi;
	static char FIRST = (0 == 0);
	int n;

	if (FIRST) {
		FIRST = !FIRST;
#ifdef TEST
		printf("Initializing Erf0\n");
#endif
		isqpi = one/Sqrt(Pi());
	}

	while (sum != newsum) {
		sum = newsum;
		term *= (inc * tx2);
		inc += two;
		newsum += term;
	}
	return (isqpi * Exp(-x2) * sum);
}

#ifdef TEST

void main(void) {
	PRECISION Ex;
	PRECISION x[] = {
		2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
	PRECISION Tx[] = {
		0.46777349810473E-02,
		0.40695201744496E-03,
		0.22090496998586E-04,
		0.74309837234124E-06,
		0.15417257900228E-07,
		0.15374597943197E-11,
		0.21519736702677E-16,
		0.41838256008056E-22,
		0.11224297124221E-28,
		0.41370317088610E-36};
	int i;

	printf("should have a  initialization message here:\n");
	for (i = sizeof(Tx)/sizeof(Tx[0]) - 1; i > 2; --i) {
		Ex = (PRECISION) Erfc0(x[i]);
		printf("%5.1f %15.8g %15.8g\n", x[i], Ex, Tx[i]);
	}
	printf("should have no initialization message here:\n");
	for (i = sizeof(Tx)/sizeof(Tx[0]) - 1; i > 2; --i) {
		Ex = (PRECISION) Erfc0(x[i]);
		printf("%5.1f %15.8g %15.8g\n", x[i], Ex, Tx[i]);
	}
	return;
}
#endif /* TEST */
