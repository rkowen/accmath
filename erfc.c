/*
 * Erfc(x) computes the complementary error function to the limits of
 *        machine accuracy for x real.
 *
 * by R.K.Owen,Ph.D.  10/19/93
 *
 * calls: Exp, Erf0, Erfc0
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#endif

#include "accmath.h"

PRECISION Erfc(PRECISION x) {
	const PRECISION zero = 0.0, one = 1.0, two = 2.0;
	PRECISION result;

/* special case */
	if (x == zero) return one;

/* find sign of x and take absolute value */
	if (x < zero) {
		x = -x;
/* if x >= -1 use Taylor expansion of erf */
		if (x <= one) {
			result = one + Erf0(x);
		} else {
/* if x < -1 use continued fraction of erfc */
			result = two - Exp(-x*x)*Erfc0(x);
		}
	} else {
/* if x <= 1 use Taylor expansion of erf */
		if (x <= one) {
			result = one - Erf0(x);
		} else {
/* if x > 1 use continued fraction of erfc */
			result = Exp(-x*x)*Erfc0(x);
		}
	}
/* final result */
	return result;
}

#ifdef TEST

#include <stdio.h>

void main(void) {
	PRECISION x, Ex, dx;
	PRECISION Tx[] = {
/*-2.0 */	1.99532226501896,
/*-1.9 */	1.99279042923526,
/*-1.8 */	1.98909050163574,
/*-1.7 */	1.98379045859078,
/*-1.6 */	1.97634838334465,
/*-1.5 */	1.96610514647531,
/*-1.4 */	1.95228511976265,
/*-1.3 */	1.93400794494065,
/*-1.2 */	1.91031397822964,
/*-1.1 */	1.88020506957409,
/*-1.0 */	1.84270079294971,
/*-0.9 */	1.79690821242284,
/*-0.8 */	1.74210096470766,
/*-0.7 */	1.67780119383742,
/*-0.6 */	1.60385609084793,
/*-0.5 */	1.52049987781304,
/*-0.4 */	1.42839235504667,
/*-0.3 */	1.32862675945913,
/*-0.2 */	1.22270258921048,
/*-0.1 */	1.11246291601829,
/* 0.0 */	1.00000000000000,
/* 0.1 */	0.88753708398172,
/* 0.2 */	0.77729741078952,
/* 0.3 */	0.67137324054087,
/* 0.4 */	0.57160764495334,
/* 0.5 */	0.47950012218695,
/* 0.6 */	0.39614390915207,
/* 0.7 */	0.32219880616258,
/* 0.8 */	0.25789903529234,
/* 0.9 */	0.20309178757717,
/* 1.0 */	0.15729920705029,
/* 1.1 */	0.11979493042592,
/* 1.2 */	0.08968602177036,
/* 1.3 */	0.06599205505935,
/* 1.4 */	0.04771488023735,
/* 1.5 */	0.03389485352469,
/* 1.6 */	0.02365161665536,
/* 1.7 */	0.01620954140923,
/* 1.8 */	0.01090949836427,
/* 1.9 */	0.00720957076474,
/* 2.0 */	0.00467773498105,
/* 2.1 */	0.00297946665633,
/* 2.2 */	0.00186284629798,
/* 2.3 */	0.00114317659736,
/* 2.4 */	0.00068851389665,
/* 2.5 */	0.00040695201744,
/* 2.6 */	0.00023603441653,
/* 2.7 */	0.00013433273994,
/* 2.8 */	0.00007501319467,
/* 2.9 */	0.00004109787810,
/* 3.0 */	0.00002209049700 };
	PRECISION xx[] = {
		3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
	PRECISION Txx[] = {
		0.74309837234124E-06,
		0.15417257900228E-07,
		0.15374597943197E-11,
		0.21519736702677E-16,
		0.41838256008056E-22,
		0.11224297124221E-28,
		0.41370317088610E-36};
	int i;

	for (i = 0; i < sizeof(Tx)/sizeof(Tx[0]); i++) {
		x = .1 * (i-20);
		Ex = (PRECISION) Erfc(x);
		dx = Tx[i] - Ex;
		printf("%5.1f %15.8f %15.8f %15.8e\n", x, Ex, Tx[i], dx);
	}
	for (i = 0; i < sizeof(Txx)/sizeof(Txx[0]); ++i) {
		Ex = (PRECISION) Erfc(xx[i]);
		dx = Txx[i] - Ex;
		printf("%5.1f %15.8g %15.8g %15.8e\n", xx[i], Ex, Txx[i], dx);
	}
	return;
}
#endif /* TEST */
