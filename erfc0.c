/*
 * Erfc0(x) computes exp(z^2) * complementary error function
 *        to the limits of
 *        machine accuracy for x real. Quickly convergent for x > 1.
 *        Uses the continued fraction expansion.
 *
 * by R.K.Owen,Ph.D.  10/19/93
 *
 * Calls: Sqrt, Pi
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
	const PRECISION zero = 0.0,half = 0.5, one = 1.0, two = 2.0,
		scale = 128.0, iscale = 0.0078125;
	PRECISION An2, An1 = zero, An = one, Bn2, Bn1 = one, Bn = x,
		Cn1 = one, Cn = An/Bn, an = zero;
	static PRECISION isqpi;
	static char FIRST = (0 == 0);

	if (FIRST) {
		FIRST = !FIRST;
#ifdef TEST
		printf("Initializing Erfc0\n");
#endif
		isqpi = one/Sqrt(Pi());
	}

	while (Cn != Cn1) {
		An2 = An1;	/* advance numerator/denominators */
		An1 = An;
		Bn2 = Bn1;
		Bn1 = Bn;
		an += half;
		An = x * An1 + an * An2;
		Bn = x * Bn1 + an * Bn2;
		while (Abs(An) > scale && Abs(Bn) > scale) { /* rescale */
			An  *= iscale;
			An1 *= iscale;
			Bn  *= iscale;
			Bn1 *= iscale;
		}
		Cn1 = Cn;
		Cn = An/Bn;
	}

	return (isqpi * Cn);
}

#ifdef TEST

#include <math.h>

void main(void) {
	PRECISION Ex, dx;
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

	for (i = 0; i < sizeof(Tx)/sizeof(Tx[0]); ++i) {
		Tx[i] *= exp(x[i]*x[i]);
	}
	printf("should have an initialization message here:\n");
	for (i = 0; i < sizeof(Tx)/sizeof(Tx[0]); ++i) {
		Ex = (PRECISION) Erfc0(x[i]);
		dx = Tx[i] - Ex;
		printf("%5.1f %15.8g %15.8g %15.8e\n", x[i], Ex, Tx[i], dx);
	}
	printf("should have no initialization message here:\n");
	for (i = 0; i < sizeof(Tx)/sizeof(Tx[0]); ++i) {
		Ex = (PRECISION) Erfc0(x[i]);
		dx = Tx[i] - Ex;
		printf("%5.1f %15.8g %15.8g %15.8e\n", x[i], Ex, Tx[i], dx);
	}
	return;
}
#endif /* TEST */
