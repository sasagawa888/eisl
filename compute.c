#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "eisl.h"


/* data type transfer */

int exact_to_inexact(int x)
{
    int res, tag;
    double val;

    tag = GET_TAG(x);
    switch (tag) {
    case INTN:
	res = freshcell();
	SET_TAG(res, FLTN);
	val = (double) GET_INT(x);
	SET_FLT(res, val);
	return (res);
    case LONGN:
	res = freshcell();
	SET_TAG(res, FLTN);
	val = (double) GET_LONG(x);
	SET_FLT(res, val);
	return (res);
    case BIGN:
	return (big_big_to_flt(x));
    case FLTN:
	return (x);
    default:
	return (x);
    }
    error(OUT_OF_RANGE, "exact_to_inexact", x);
    return (UNDEF);
}

int numeqp(int x, int y)
{
    int x1, y1;

    /* if integer type and address are same, then true. */
    if (integerp(x) && integerp(y)) {
	if (GET_INT(x) == GET_INT(y))
	    return (1);
	else
	    return (0);
    }
    /* if long integer data type and the values are same, then true. */
    else if (longnump(x) && longnump(y)) {
	if (GET_LONG(x) == GET_LONG(y))
	    return (1);
	else
	    return (0);
    }

    else if (bignump(x) && bignump(y)) {
	if (big_eqp(x, y))
	    return (1);
	else
	    return (0);
    }
    /* if floating point number, consider EPSILON */
    else if (floatp(x) && floatp(y)) {
	if (GET_FLT(x) - DBL_EPSILON <= GET_FLT(y) &&
	    GET_FLT(x) + DBL_EPSILON >= GET_FLT(y))
	    return (1);
	else if (GET_FLT(x) >= GET_FLT(y) - DBL_EPSILON &&
		 GET_FLT(x) <= GET_FLT(y) + DBL_EPSILON)
	    return (1);
	/* when huge number */
	else if (fabs(GET_FLT(x)) > 1e+30
		 && fabs(GET_FLT(x) - GET_FLT(y)) <
		 fabs(GET_FLT(x)) / 100000)
	    return (1);
	else
	    return (0);
    } else {
	x1 = exact_to_inexact(x);
	y1 = exact_to_inexact(y);

	if (GET_FLT(x1) - DBL_EPSILON <= GET_FLT(y1) &&
	    GET_FLT(x1) + DBL_EPSILON >= GET_FLT(y1))
	    return (1);
	else if (GET_FLT(x1) >= GET_FLT(y1) - DBL_EPSILON &&
		 GET_FLT(x1) <= GET_FLT(y1) - DBL_EPSILON)
	    return (1);
	else
	    return (0);
    }
}

int smallerp(int x1, int x2)
{
    if (IS_INTEGER(x1) && IS_INTEGER(x2)) {
	if (GET_INT(x1) < GET_INT(x2))
	    return (1);
	else
	    return (0);
    } else if (integerp(x1) && bignump(x2))
	return (1);
    else if (longnump(x1) && bignump(x2))
	return (1);
    else if (longnump(x1) && longnump(x2)) {
	if (GET_LONG(x1) < GET_LONG(x2))
	    return (1);
	else
	    return (0);
    } else if (bignump(x1) && bignump(x2)) {
	if (big_smallerp(x1, x2))
	    return (1);
	else
	    return (0);
    } else {
	if (GET_FLT(exact_to_inexact(x1)) < GET_FLT(exact_to_inexact(x2)))
	    return (1);
	else
	    return (0);
    }
}

int eqsmallerp(int x1, int x2)
{
    if (integerp(x1) && integerp(x2)) {
	if (GET_INT(x1) <= GET_INT(x2))
	    return (1);
	else
	    return (0);
    } else if (integerp(x1) && bignump(x2))
	return (1);
    else if (longnump(x1) && bignump(x2))
	return (1);
    else if (longnump(x1) && longnump(x2)) {
	if (GET_LONG(x1) <= GET_LONG(x2))
	    return (1);
	else
	    return (0);
    } else if (bignump(x1) && bignump(x2)) {
	if (big_smallerp(x1, x2) || big_eqp(x1, x2))
	    return (1);
	else
	    return (0);
    } else {
	if (GET_FLT(exact_to_inexact(x1)) <= GET_FLT(exact_to_inexact(x2)))
	    return (1);
	else
	    return (0);
    }
}

int greaterp(int x1, int x2)
{
    if (smallerp(x2, x1))
	return (1);
    else
	return (0);
}

int eqgreaterp(int x1, int x2)
{
    if (eqsmallerp(x2, x1))
	return (1);
    else
	return (0);
}

int positivep(int x)
{

    if (integerp(x) && GET_INT(x) > 0)
	return (1);
    else if (longnump(x) && GET_LONG(x) > 0)
	return (1);
    else if (bignump(x) && big_positivep(x))
	return (1);
    else if (floatp(x) && GET_FLT(x) > 0)
	return (1);
    else
	return (0);
}

int negativep(int x)
{

    if (integerp(x) && GET_INT(x) < 0)
	return (1);
    else if (longnump(x) && GET_LONG(x) < 0)
	return (1);
    else if (bignump(x) && big_negativep(x))
	return (1);
    else if (floatp(x) && GET_FLT(x) < 0)
	return (1);
    else
	return (0);
}

int zerop(int x)
{
    if (integerp(x) && GET_INT(x) == 0)
	return (1);
    else if (floatp(x) && GET_FLT(x) == 0.0)
	return (1);
    else
	return (0);
}

int positive_zerop(int x)
{
    if (zerop(x) && floatp(x) && !signbit(GET_FLT(x)))
	return (1);
    else if (zerop(x) && floatp(x))
	return (1);
    else
	return (0);
}

int negative_zerop(int x)
{
    if (zerop(x) && floatp(x) && signbit(GET_FLT(x)))
	return (1);
    else
	return (0);
}


/*
 * basic operation
 */

int plus(int arg1, int arg2)
{
    int tag1, tag2;
    double x1, x2;

    tag1 = GET_TAG(arg1);
    tag2 = GET_TAG(arg2);
    switch (tag1) {
		case INTN:
			switch (tag2) {
				case INTN: {
					long long int l;

					l = (long long int) GET_INT(arg1) +
						(long long int) GET_INT(arg2);
					if (SMALL_INT_MIN < l && l < SMALL_INT_MAX)
						return (make_int((int) l));
					else
						return (make_long(l));
				}
				case FLTN:
					return (plus(exact_to_inexact(arg1), arg2));
				case LONGN:
					return (big_plus(big_int_to_big(arg1), big_long_to_big(arg2)));
				case BIGN:
					return (big_plus(big_int_to_big(arg1), arg2));
			}
			break;
		case LONGN:
			switch (tag2) {
				case INTN:
					return (big_plus(big_long_to_big(arg1), big_int_to_big(arg2)));
				case FLTN:
					return (plus(exact_to_inexact(arg1), arg2));
				case LONGN:
					return (big_plus
						(big_long_to_big(arg1), big_long_to_big(arg2)));
				case BIGN:
					return (big_plus(big_long_to_big(arg1), arg2));
			}
			break;
		case BIGN:
			switch (tag2) {
				case INTN:
					return (big_plus(arg1, big_int_to_big(arg2)));
				case FLTN:
					return (plus(exact_to_inexact(arg1), arg2));
				case LONGN:
					return (big_plus(arg1, big_long_to_big(arg2)));
				case BIGN:
					return (big_plus(arg1, arg2));
			}
			break;
		case FLTN:
			switch (tag2) {
				case FLTN: {
					x1 = GET_FLT(arg1);
					x2 = GET_FLT(arg2);

					double y = x1 + x2;
					if (fabs(y) > DBL_MAX)
						error(FLT_OVERF, "+",  list2(arg1, arg2));

					return (make_flt(y));
				}
				case INTN:
				case LONGN:
				case BIGN:
					return (plus(arg1, exact_to_inexact(arg2)));
			}
			break;
		default:
			break;
    }
    error(NOT_COMPUTABLE, "+", list2(arg1, arg2));
    return (UNDEF);
}


int minus(int arg1, int arg2)
{
    int tag1, tag2;
    double x1, x2;

    tag1 = GET_TAG(arg1);
    tag2 = GET_TAG(arg2);
    switch (tag1) {
		case INTN:
			switch (tag2) {
				case INTN: {
					long long int l;

					l = (long long int) GET_INT(arg1) -
						(long long int) GET_INT(arg2);
					if (SMALL_INT_MIN < l && l < SMALL_INT_MAX)
						return (make_int((int) l));
					else
						return (make_long(l));
				}

				case FLTN: {
					return minus(exact_to_inexact(arg1), arg2);
				}

				case LONGN:
					return (big_minus(big_int_to_big(arg1),
							big_long_to_big(arg2)));

				case BIGN:
					return (big_minus(big_int_to_big(arg1), arg2));
			}
			break;
		case LONGN:
			switch (tag2) {
				case INTN:
					return (big_minus
						(big_long_to_big(arg1), big_int_to_big(arg2)));
				case FLTN:
					return (minus(exact_to_inexact(arg1), arg2));
				case LONGN:
					return (big_minus
						(big_long_to_big(arg1), big_long_to_big(arg2)));
				case BIGN:
					return (big_minus(big_long_to_big(arg1), arg2));
			}
			break;
		case BIGN:
			switch (tag2) {
				case INTN:
					return (big_minus(arg1, big_int_to_big(arg2)));
				case FLTN:
					return (minus(exact_to_inexact(arg1), arg2));
				case LONGN:
					return (big_minus(arg1, big_long_to_big(arg2)));
				case BIGN:
					return (big_minus(arg1, arg2));
			}
			break;
		case FLTN:
			switch (tag2) {
				case FLTN: {
					x1 = GET_FLT(arg1);
					x2 = GET_FLT(arg2);

					double y = x1 - x2;
					if (fabs(y) > DBL_MAX)
						error(FLT_OVERF, "-",  list2(arg1, arg2));

					return (make_flt(y));
				}
				case INTN:
				case LONGN:
				case BIGN:
					return (minus(arg1, exact_to_inexact(arg2)));
			}
			break;
    }
    error(NOT_COMPUTABLE, "-", list2(arg1, arg2));
    return (UNDEF);
}


int mult(int arg1, int arg2)
{
    int tag1, tag2;
    double x1, y1, x2;

    tag1 = GET_TAG(arg1);
    tag2 = GET_TAG(arg2);

    switch (tag1) {
    case INTN:
		switch (tag2) {
			case INTN:
				{
				long long int l1, l2, l;

				l1 = (long long int) GET_INT(arg1);
				l2 = (long long int) GET_INT(arg2);
				l = l1 * l2;
				if (l < SMALL_INT_MAX && l > SMALL_INT_MIN)
					return (make_int((int) l));
				else
					return (big_mult
						(big_int_to_big(arg1), big_int_to_big(arg2)));
				}

			case FLTN: {
				return mult(exact_to_inexact(arg1), arg2);
			}

			case LONGN:
				if (GET_INT(arg1) != 0)
				return (big_mult
					(big_long_to_big(arg2), big_int_to_big(arg1)));
				else
				return (arg1);	/* int 0 */

			case BIGN:
				return (big_mult(arg2, big_int_to_big(arg1)));
		}
		break;
    case LONGN: 
		switch (tag2) {
				case INTN:
					if (GET_INT(arg2) != 0)
					return (big_mult
						(big_long_to_big(arg1), big_int_to_big(arg2)));
					else
					return (arg2);	/* int 0 */
				case FLTN:
					return (mult(exact_to_inexact(arg1), arg2));
				case LONGN:
					return (big_mult
						(big_long_to_big(arg1), big_long_to_big(arg2)));
				case BIGN:
					return (big_mult(big_long_to_big(arg1), arg2));
		}
		break;
    case BIGN: 
		switch (tag2) {
				case INTN:
					return (big_mult_i(arg1, arg2));
				case FLTN:
					return (mult(exact_to_inexact(arg1), arg2));
				case LONGN:
					return (big_mult(arg1, big_long_to_big(arg2)));
				case BIGN:
					return (big_mult(arg1, arg2));
		}
		break;
    case FLTN: 
		switch (tag2) {
			case FLTN: {
				x1 = GET_FLT(arg1);
				x2 = GET_FLT(arg2);
				y1 = x1 * x2;
				if (y1 > DBL_MAX || y1 < -DBL_MAX)
					error(FLT_OVERF, "*", list2(arg1, arg2));
				if (x1 != 0.0 && x2 != 0.0 && y1 > -DBL_MIN
					&& y1 < DBL_MIN)
					error(FLT_UNDERF, "*", list2(arg1, arg2));
				return (make_flt(y1));
			}
			case INTN:
			case LONGN:
			case BIGN:
				return (mult(arg1, exact_to_inexact(arg2)));
		}
		break;
    }
    error(NOT_COMPUTABLE, "*", list2(arg1, arg2));
    return (UNDEF);
}

int quotient(int arg1, int arg2)
{
    int n, s, tag1, tag2;
    double x1, y1, x2;

	if (zerop(arg2))
		error(DIV_ZERO, "quotient", arg2);

    tag1 = GET_TAG(arg1);
    tag2 = GET_TAG(arg2);
    switch (tag1) {
		case INTN:
			switch (tag2) {
				case INTN:
					{
					n = GET_INT(arg1);
					if (n == 0)
						return (arg1);
					x1 = (double) n;
					s = GET_INT(arg2);
					y1 = (double) s;
					x2 = x1 / y1;
					if ((x2 - floor(x2)) == 0.0)
						return (make_int((int) x2));
					else
						return (make_flt(x1 / y1));
					}
				case FLTN:
					return quotient(exact_to_inexact(arg1), arg2);

				case LONGN:
				case BIGN:
					if (GET_INT(arg1) == 0)
					return (arg1);
					else
					return (quotient
						(exact_to_inexact(arg1), exact_to_inexact(arg2)));
			}
			break;
		case LONGN:
			switch (tag2) {
				case INTN:
				case LONGN:
					n = quotient(exact_to_inexact(arg1), exact_to_inexact(arg2));
					x1 = GET_FLT(n);
					x2 = x1 - ceil(x1);
					if (x2 == 0.0) {
					return (divide(arg1, arg2));
					} else
					return (n);
				case BIGN:
					return (quotient
						(exact_to_inexact(arg1), exact_to_inexact(arg2)));
				case FLTN:
					return (quotient(exact_to_inexact(arg1), arg2));
			}
			break;
		case BIGN:
			switch (tag2) {
				case INTN:
				case LONGN:
				case BIGN:
					n = quotient(exact_to_inexact(arg1), exact_to_inexact(arg2));
					x1 = GET_FLT(n);
					x2 = x1 - ceil(x1);
					if (x1 == 1.0)
					return (make_int(1));
					else if (x1 == -1.0)
					return (make_int(-1));
					else if (x2 == 0.0)
					return (divide(arg1, arg2));
					else
					return (n);
				case FLTN:
					return (quotient(exact_to_inexact(arg1), arg2));
			}
			break;
		case FLTN:
			switch (tag2) {
			case FLTN:
				{
				x1 = GET_FLT(arg1);
				x2 = GET_FLT(arg2);
				y1 = x1 / x2;
				if (fabs(y1) > DBL_MAX)
					error(FLT_OVERF, "quotient", list2(arg1, arg2));
				
				if (x1 != 0.0 && x2 != 0.0 && fabs(y1) < DBL_MIN)
					error(FLT_UNDERF, "quotient", list2(arg1, arg2));

				return make_flt(y1);
				}
			case INTN:
			case LONGN:
			case BIGN:
				return (quotient(arg1, exact_to_inexact(arg2)));

			}
			break;
    }
    error(NOT_COMPUTABLE, "/", list2(arg1, arg2));
    return (UNDEF);
}


int divide(int x, int y)
{

    if (integerp(x) && longnump(y))
	return (make_int(0));
    else if (integerp(x) && bignump(y))
	return (make_int(0));
    else if (longnump(x) && bignump(y))
	return (make_int(0));
    else if (integerp(x) && integerp(y))
	return (make_int(GET_INT(x) / GET_INT(y)));
    else if (longnump(x) && integerp(y))
	return (long_int_div(x, y));
    else if (longnump(x) && longnump(y))
	return (long_long_div(x, y));
    else if (bignump(x) && integerp(y))
	return (big_div_i(x, y));
    else if (bignump(x) && longnump(y))
	return (big_div(x, big_long_to_big(y)));
    else if (bignump(x) && bignump(y))
	return (big_div(x, y));
    else
	error(ILLEGAL_ARGS, "div", list2(x, y));

    return (UNDEF);
}

int s_remainder(int x, int y)
{
    int i;

    if (integerp(x) && integerp(y))
	return (make_int(GET_INT(x) % GET_INT(y)));
    else if (integerp(x) && longnump(y))
	return (x);
    else if (integerp(x) && bignump(y))
	return (x);
    else if (longnump(x) && bignump(y))
	return (x);
    else if (longnump(x) && integerp(y))
	return (long_int_remainder(x, y));
    else if (longnump(x) && longnump(y))
	return (long_long_remainder(x, y));
    else if (bignump(x) && integerp(y))
	return (big_remainder_i(x, y));
    else if (bignump(x) && longnump(y)) {
	i = big_long_to_big(y);
	return (minus(x, mult(divide(x, i), i)));
    } else if (bignump(x) && bignump(y))
	return (big_remainder(x, y));

    error(ILLEGAL_ARGS, "remainder", NIL);
    return (UNDEF);
}


/* remainder of longnum and int. */
int long_int_remainder(int x, int y)
{
    long long int m, n, r;


    m = GET_LONG(x);
    n = (long long int) GET_INT(y);
    r = m % n;

    return (make_int((int) r));
}

/* remainder of longnum and longnum. */
int long_long_remainder(int x, int y)
{
    long long int m, n, r;


    m = GET_LONG(x);
    n = GET_LONG(y);
    r = m % n;

    if (llabs(r) < BIGNUM_BASE)
	return (make_int((int) r));
    else
	return (make_long(r));
}

/* divide of longnum and int. */
int long_int_div(int x, int y)
{
    long long int m, n, q;


    m = GET_LONG(x);
    n = (long long int) GET_INT(y);
    q = m / n;

    if (llabs(q) < BIGNUM_BASE)
	return (make_int((int) q));
    else
	return (make_long(q));
}

/* divide of longnum and longnum */
int long_long_div(int x, int y)
{
    long long int m, n, q;


    m = GET_LONG(x);
    n = GET_LONG(y);
    q = m / n;

    if (llabs(q) < BIGNUM_BASE)
	return (make_int((int) q));
    else
	return (make_long(q));
}

int absolute(int x)
{
    if (integerp(x))
	return (make_int(abs(GET_INT(x))));
    else if (longnump(x))
	return (make_long(llabs(GET_LONG(x))));
    else if (bignump(x)) {
	return (big_abs(x));
    } else if (floatp(x)) {
	return (make_flt(fabs(GET_FLT(x))));
    }
    error(ILLEGAL_ARGS, "abs", x);
    return (UNDEF);
}

int angle(int y, int x)
{

    if (positive_zerop(y) && positivep(x))
	return (make_flt(0.0));
    else if (negative_zerop(y) && positivep(x))
	return (make_flt(-0.0));
    else if (positivep(y) && positivep(x))
	return (make_flt
		(atan
		 (GET_FLT(exact_to_inexact(y)) /
		  GET_FLT(exact_to_inexact(x)))));
    else if (positivep(y) && zerop(x))
	return (make_flt(M_PI_2));
    else if (positivep(y) && negativep(x))
	return (make_flt
		(M_PI +
		 atan(GET_FLT(exact_to_inexact(y)) /
		      GET_FLT(exact_to_inexact(x)))));
    else if (positive_zerop(y) && negativep(x))
	return (make_flt(M_PI));
    else if (negative_zerop(y) && negativep(x))
	return (make_flt(-M_PI));
    else if (negativep(y) && negativep(x))
	return (make_flt
		(-M_PI +
		 atan(GET_FLT(exact_to_inexact(y)) /
		      GET_FLT(exact_to_inexact(x)))));
    else if (negativep(y) && zerop(x))
	return (make_flt(-M_PI_2));
    else if (negativep(y) && positivep(x))
	return (make_flt
		(atan
		 (GET_FLT(exact_to_inexact(y)) /
		  GET_FLT(exact_to_inexact(x)))));
    else if (zerop(y) && positivep(x))
	return (make_flt(0.0));
    else if (zerop(y) && negativep(x))
	return (make_flt(M_PI));
    else if (positive_zerop(y) && positive_zerop(x))
	return (make_flt(+0.0));
    else if (negative_zerop(y) && positive_zerop(x))
	return (make_flt(-0.0));
    else if (positive_zerop(y) && negative_zerop(x))
	return (make_flt(M_PI));
    else if (negative_zerop(y) && negative_zerop(x))
	return (make_flt(-M_PI));
    else if (positive_zerop(y) && zerop(x))
	return (make_flt(M_PI_2));
    else if (negative_zerop(y) && zerop(x))
	return (make_flt(-M_PI_2));
    else {
	error(ILLEGAL_ARGS, "angle", list2(x, y));
	return (UNDEF);
    }
}

/* GCD of integer */
int int_gcd(int x, int y)
{
    if (y == 0)
	return (x);

    while (y != 0) {
	int r;

	r = x % y;
	x = y;
	y = r;
    }
    return (x);
}

/* GCD of number(include bignum) */
int gcd(int x, int y)
{
    if (integerp(x) && integerp(y))
	return (make_int(abs(int_gcd(GET_INT(x), GET_INT(y)))));

    else if (floatp(x) && integerp(y))
	return (make_flt
		((double) abs(int_gcd((int) GET_FLT(x), GET_INT(y)))));

    else if (integerp(x) && floatp(y))
	return (make_flt
		((double) abs(int_gcd(GET_INT(x), (int) GET_FLT(y)))));

    else if (floatp(x) && floatp(y))
	return (make_flt
		((double) abs(int_gcd(GET_FLT(x), (int) GET_FLT(y)))));

    while (!zerop(y)) {
	int r;

	r = s_remainder(x, y);
	x = y;
	y = r;

    }
    return (absolute(x));
}

/* LCM of integer */
int int_lcm(int m, int n)
{
    if (m == 0 || n == 0)
	return (0);

    return ((m / int_gcd(m, n)) * n);
}

/* LCM of number(include bignum) */
int lcm(int x, int y)
{
    int g, d, res;
    if (integerp(x) && integerp(y) && abs(GET_INT(x)) < 10000
	&& abs(GET_INT(y)) < 10000)
	// because  x,y < sqrt(BIGNUM_BASE)
	return (make_int(abs(int_lcm(GET_INT(x), GET_INT(y)))));

    else if (floatp(x) && integerp(y))
	return (make_flt
		((double) abs(int_lcm((int) GET_FLT(x), GET_INT(y)))));

    else if (integerp(x) && floatp(y))
	return (make_flt
		((double) abs(int_lcm(GET_INT(x), (int) GET_FLT(y)))));

    else if (floatp(x) && floatp(y))
	return (make_flt
		((double) abs(int_lcm(GET_FLT(x), (int) GET_FLT(y)))));

    else {
	g = gcd(x, y);
	d = divide(absolute(x), g);
	res = mult(d, absolute(y));
	return (res);
    }
}

/* newton method for longnum */
long long int isqrt1(long long int n, long long int init)
{
    long long int s;

    s = init;

    while (s * s > n) {
	s = (s + n / s) / 2;
    }
    return (s);
}

/* newton method for bignum */
int isqrt2(int n, int init)
{
    int s;

    s = init;
    while (greaterp(mult(s, s), n)) {
	//print(s);printf("\n");
	s = divide(plus(s, divide(n, s)), make_int(2));
    }
    return (s);
}

/* basic isqrt (for small bignum) */
int isqrt3(int x)
{
    int len, pointer, init, i;
    len = get_length(x);
    pointer = get_pointer(x);
    if (len % 2 == 0) {
	long long int lmsb =
	    (long long int) bigcell[pointer] * BIGNUM_BASE +
	    (long long int) bigcell[pointer - 1];
	init = gen_big();
	len = (len - 2) / 2;
	for (i = 0; i < len; i++) {
	    bigcell[big_pt0++] = 0;
	}
	bigcell[big_pt0++] = (int) sqrt(lmsb) + 10000;
	set_sign(init, 1);
	set_pointer(init, big_pt0 - 1);
	set_length(init, len + 1);
    } else {
	int msb = bigcell[pointer];
	init = gen_big();
	len = (len - 1) / 2;
	for (i = 0; i < len; i++) {
	    bigcell[big_pt0++] = 0;
	}
	bigcell[big_pt0++] = (int) sqrt(msb) + 1;
	set_sign(init, 1);
	set_pointer(init, big_pt0 - 1);
	set_length(init, len + 1);
    }

    return (isqrt2(x, init));

}


/* idea memo
 even digits
 e.g. isqrt(12345678901234) = 3513641
 goal                     init         value
 isqrt(123456)               -           351
 isqrt(123456789012)   35100          351364
 isqrt(12345678901234) 3513640       3513641 
 
 
 e.g. isqrt(1234567890123) 1111111
 odd digits
 goal                  init        value
 isqrt(12345)             -          111
 isqrt(123456789)      11100       11111
 isqrt(1234567890123)  1111100   1111111

 size of bignum must be 10 or greater
*/
int isqrt4(int x)
{
    int len, len1, len2, init, target, res;

    len = get_length(x);

    if (len % 2 == 0) {
	len1 = 3;
	len2 = 6;
	init = plus(isqrt3(big_take_from_left(x, len2)), make_int(1));
	while (len2 * 2 < len) {
	    len1 = len1 * 2;
	    len2 = len2 * 2;
	    target = big_take_from_left(x, len2);
	    init = big_shift_right(init, len1 - get_length(init));
	    init = plus(isqrt2(target, init), make_int(1));
	}
	len1 = len / 2;
	len2 = len;
	init = big_shift_right(init, len1 - get_length(init));
	res = isqrt2(big_take_from_left(x, len2), init);
	return (res);
    } else {
	len1 = 3;
	len2 = 5;
	init = plus(isqrt3(big_take_from_left(x, len2)), make_int(1));
	while (len2 * 2 - 1 < len) {
	    len1 = len1 + ((len2 * 2 - 1) - len2) / 2;
	    len2 = len2 * 2 - 1;
	    target = big_take_from_left(x, len2);
	    init = big_shift_right(init, len1 - get_length(init));
	    init = plus(isqrt2(target, init), make_int(1));
	}
	len1 = (len + 1) / 2;
	len2 = len;
	init = big_shift_right(init, len1 - get_length(init));
	res = isqrt2(big_take_from_left(x, len2), init);
	return (res);
    }
}


int isqrt(int x)
{
    if (integerp(x))
	return (make_int(floor(sqrt(GET_INT(x)))));
    else if (floatp(x))
	return (make_int(floor(sqrt(GET_FLT(x)))));
    else if (longnump(x)) {
	long long int n, init;
	n = GET_LONG(x);
	init = (long long int) sqrt(n) + 1;
	return (make_int((int) isqrt1(n, init)));
    } else {
	if (get_length(x) < 10)
	    return (isqrt3(x));
	else
	    return (isqrt4(x));
    }
}
