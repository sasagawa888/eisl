#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "eisl.h"


// data type transfer

int
exact_to_inexact (int x)
{
  int res, tag;
  double val;

  tag = GET_TAG (x);
  switch (tag)
    {
    case INTN:
      res = freshcell ();
      SET_TAG (res, FLTN);
      val = (double) GET_INT (x);
      SET_FLT (res, val);
      return (res);
    case LONGN:
      res = freshcell ();
      SET_TAG (res, FLTN);
      val = (double) GET_LONG (x);
      SET_FLT (res, val);
      return (res);
    case BIGX:
      return (bigx_big_to_flt (x));
    case FLTN:
      return (x);
    default:
      return (x);
    }
  error (OUT_OF_RANGE, "exact_to_inexact", x);
  return (UNDEF);
}

int
numeqp (int x, int y)
{
  int x1, y1;

  // if integer type and address are same, then true.
  if (integerp (x) && integerp (y))
    {
      if (GET_INT (x) == GET_INT (y))
	return (1);
      else
	return (0);
    }
  // if long integer data type and the values are same, then true.
  else if (longnump (x) && longnump (y))
    {
      if (GET_LONG (x) == GET_LONG (y))
	return (1);
      else
	return (0);
    }

  else if (bignump (x) && bignump (y))
    {
      if (bigx_eqp (x, y))
	return (1);
      else
	return (0);
    }
  // if floating point number, consider EPSILON
  else if (floatp (x) && floatp (y))
    {
      if (GET_FLT (x) - DBL_EPSILON <= GET_FLT (y) &&
	  GET_FLT (x) + DBL_EPSILON >= GET_FLT (y))
	return (1);
      else if (GET_FLT (x) >= GET_FLT (y) - DBL_EPSILON &&
	       GET_FLT (x) <= GET_FLT (y) + DBL_EPSILON)
	return (1);
      else
	return (0);
    }
  else
    {
      x1 = exact_to_inexact (x);
      y1 = exact_to_inexact (y);

      if (GET_FLT (x1) - DBL_EPSILON <= GET_FLT (y1) &&
	  GET_FLT (x1) + DBL_EPSILON >= GET_FLT (y1))
	return (1);
      else if (GET_FLT (x1) >= GET_FLT (y1) - DBL_EPSILON &&
	       GET_FLT (x1) <= GET_FLT (y1) - DBL_EPSILON)
	return (1);
      else
	return (0);
    }
}

int
smallerp (int x1, int x2)
{
  if (IS_INTEGER (x1) && IS_INTEGER (x2))
    {
      if (GET_INT (x1) < GET_INT (x2))
	return (1);
      else
	return (0);
    }
  else if (integerp (x1) && bignump (x2))
    return (1);
  else if (longnump (x1) && bignump (x2))
    return (1);
  else if (longnump (x1) && longnump (x2))
    {
      if (GET_LONG (x1) < GET_LONG (x2))
	return (1);
      else
	return (0);
    }
  else if (bignump (x1) && bignump (x2))
    {
      if (bigx_smallerp (x1, x2))
	return (1);
      else
	return (0);
    }
  else
    {
      if (GET_FLT (exact_to_inexact (x1)) < GET_FLT (exact_to_inexact (x2)))
	return (1);
      else
	return (0);
    }
}

int
eqsmallerp (int x1, int x2)
{
  if (integerp (x1) && integerp (x2))
    {
      if (GET_INT (x1) <= GET_INT (x2))
	return (1);
      else
	return (0);
    }
  else if (integerp (x1) && bignump (x2))
    return (1);
  else if (longnump (x1) && bignump (x2))
    return (1);
  else if (longnump (x1) && longnump (x2))
    {
      if (GET_LONG (x1) <= GET_LONG (x2))
	return (1);
      else
	return (0);
    }
  else if (bignump (x1) && bignump (x2))
    {
      if (bigx_smallerp (x1, x2) || bigx_eqp (x1, x2))
	return (1);
      else
	return (0);
    }
  else
    {
      if (GET_FLT (exact_to_inexact (x1)) <= GET_FLT (exact_to_inexact (x2)))
	return (1);
      else
	return (0);
    }
}

int
greaterp (int x1, int x2)
{
  if (smallerp (x2, x1))
    return (1);
  else
    return (0);
}

int
eqgreaterp (int x1, int x2)
{
  if (eqsmallerp (x2, x1))
    return (1);
  else
    return (0);
}

int
positivep (int x)
{

  if (integerp (x) && GET_INT (x) > 0)
    return (1);
  else if (longnump (x) && GET_LONG (x) > 0)
    return (1);
  else if (bignump (x) && bigx_positivep (x))
    return (1);
  else if (floatp (x) && GET_FLT (x) > 0)
    return (1);
  else
    return (0);
}

int
negativep (int x)
{

  if (integerp (x) && GET_INT (x) < 0)
    return (1);
  else if (longnump (x) && GET_LONG (x) < 0)
    return (1);
  else if (bignump (x) && bigx_negativep (x))
    return (1);
  else if (floatp (x) && GET_FLT (x) < 0)
    return (1);
  else
    return (0);
}

int
zerop (int x)
{
  if (integerp (x) && GET_INT (x) == 0)
    return (1);
  else if (floatp (x) && GET_FLT (x) == 0.0)
    return (1);
  else
    return (0);
}

int
positive_zerop (int x)
{
  if (zerop (x) && floatp (x) && !signbit (GET_FLT (x)))
    return (1);
  else if (zerop (x) && floatp (x))
    return (1);
  else
    return (0);
}

int
negative_zerop (int x)
{
  if (zerop (x) && floatp (x) && signbit (GET_FLT (x)))
    return (1);
  else
    return (0);
}


// -----------------------------------
// basic operation

int
plus (int arg1, int arg2)
{
  int tag1, tag2;
  double x1, x2;

  tag1 = GET_TAG (arg1);
  tag2 = GET_TAG (arg2);
  switch (tag1)
    {
    case INTN:
      switch (tag2)
	{
	case INTN:
	  {
	    long long int l;

	    l = (long long int) GET_INT (arg1) +
	      (long long int) GET_INT (arg2);
	    if (SMALL_INT_MIN < l && l < SMALL_INT_MAX)
	      return (makeint ((int) l));
	    else
	      return (makelong (l));
	  }
	case FLTN:
	  {
	    int n;
	    double y1;

	    n = GET_INT (arg1);
	    x1 = (double) n;
	    y1 = GET_FLT (arg2);
	    return (makeflt (x1 + y1));
	  }
	case LONGN:
	  return (bigx_plus
		  (bigx_int_to_big (arg1), bigx_long_to_big (arg2)));
	case BIGX:
	  return (bigx_plus (bigx_int_to_big (arg1), arg2));
	}
      break;
    case LONGN:
      switch (tag2)
	{
	case INTN:
	  return (bigx_plus
		  (bigx_long_to_big (arg1), bigx_int_to_big (arg2)));
	case FLTN:
	  return (plus (exact_to_inexact (arg1), arg2));
	case LONGN:
	  return (bigx_plus
		  (bigx_long_to_big (arg1), bigx_long_to_big (arg2)));
	case BIGX:
	  return (bigx_plus (bigx_long_to_big (arg1), arg2));
	}
      break;
    case BIGX:
      switch (tag2)
	{
	case INTN:
	  return (bigx_plus (arg1, bigx_int_to_big (arg2)));
	case FLTN:
	  return (plus (exact_to_inexact (arg1), arg2));
	case LONGN:
	  return (bigx_plus (arg1, bigx_long_to_big (arg2)));
	case BIGX:
	  return (bigx_plus (arg1, arg2));
	}
      break;
    case FLTN:
      switch (tag2)
	{
	case INTN:
	  {
	    int s;

	    x1 = GET_FLT (arg1);
	    s = GET_INT (arg2);
	    x2 = (double) s;
	    return (makeflt (x1 + x2));
	  }
	case FLTN:
	  {
	    x1 = GET_FLT (arg1);
	    x2 = GET_FLT (arg2);
	    return (makeflt (x1 + x2));
	  }
	case LONGN:
	  return (plus (arg1, exact_to_inexact (arg2)));
	case BIGX:
	  return (plus (arg1, exact_to_inexact (arg2)));
	}
      break;
    default:
      break;
    }
  error (NOT_COMPUTABLE, "+", list2 (arg1, arg2));
  return (UNDEF);
}


int
minus (int arg1, int arg2)
{
  int tag1, tag2;
  double x1, x2;

  tag1 = GET_TAG (arg1);
  tag2 = GET_TAG (arg2);
  switch (tag1)
    {
    case INTN:
      switch (tag2)
	{
	case INTN:
	  {
	    long long int l;

	    l = (long long int) GET_INT (arg1) -
	      (long long int) GET_INT (arg2);
	    if (SMALL_INT_MIN < l && l < SMALL_INT_MAX)
	      return (makeint ((int) l));
	    else
	      return (makelong (l));
	  }

	case FLTN:
	  {
	    int n;
	    double y1;

	    n = GET_INT (arg1);
	    x1 = (double) n;
	    y1 = GET_FLT (arg2);
	    return (makeflt (x1 - y1));
	  }

	case LONGN:
	  return (bigx_minus (bigx_int_to_big (arg1),
			      bigx_long_to_big (arg2)));

	case BIGX:
	  return (bigx_minus (bigx_int_to_big (arg1), arg2));
	}
      break;
    case LONGN:
      switch (tag2)
	{
	case INTN:
	  return (bigx_minus
		  (bigx_long_to_big (arg1), bigx_int_to_big (arg2)));
	case FLTN:
	  return (minus (exact_to_inexact (arg1), arg2));
	case LONGN:
	  return (bigx_minus
		  (bigx_long_to_big (arg1), bigx_long_to_big (arg2)));
	case BIGX:
	  return (bigx_minus (bigx_long_to_big (arg1), arg2));
	}
      break;
    case BIGX:
      switch (tag2)
	{
	case INTN:
	  return (bigx_minus (arg1, bigx_int_to_big (arg2)));
	case FLTN:
	  return (minus (exact_to_inexact (arg1), arg2));
	case LONGN:
	  return (bigx_minus (arg1, bigx_long_to_big (arg2)));
	case BIGX:
	  return (bigx_minus (arg1, arg2));
	}
      break;
    case FLTN:
      switch (tag2)
	{
	case INTN:
	  {
	    int s;

	    x1 = GET_FLT (arg1);
	    s = GET_INT (arg2);
	    x2 = (double) s;
	    return (makeflt (x1 - x2));
	  }
	case FLTN:
	  {
	    x1 = GET_FLT (arg1);
	    x2 = GET_FLT (arg2);
	    return (makeflt (x1 - x2));
	  }
	case LONGN:
	  return (minus (arg1, exact_to_inexact (arg2)));
	case BIGX:
	  return (minus (arg1, exact_to_inexact (arg2)));
	}
      break;
    }
  error (NOT_COMPUTABLE, "-", list2 (arg1, arg2));
  return (UNDEF);
}


int
mult (int arg1, int arg2)
{
  int tag1, tag2;
  double x1, y1, x2;

  tag1 = GET_TAG (arg1);
  tag2 = GET_TAG (arg2);

  switch (tag1)
    {
    case INTN:
      switch (tag2)
	{
	case INTN:
	  {
	    long long int l1, l2, l;

	    l1 = (long long int) GET_INT (arg1);
	    l2 = (long long int) GET_INT (arg2);
	    l = l1 * l2;
	    if (l < SMALL_INT_MAX && l > SMALL_INT_MIN)
	      return (makeint ((int) l));
	    else
	      return (bigx_mult
		      (bigx_int_to_big (arg1), bigx_int_to_big (arg2)));
	  }

	case FLTN:
	  {
	    int n;

	    n = GET_INT (arg1);
	    x1 = (double) n;
	    y1 = GET_FLT (arg2);
	    return (makeflt (x1 * y1));
	  }

	case LONGN:
	  if (GET_INT (arg1) != 0)
	    return (bigx_mult
		    (bigx_long_to_big (arg2), bigx_int_to_big (arg1)));
	  else
	    return (arg1);	// int 0

	case BIGX:
	  return (bigx_mult (arg2, bigx_int_to_big (arg1)));
	}
      break;
    case LONGN:
      switch (tag2)
	{
	case INTN:
	  if (GET_INT (arg2) != 0)
	    return (bigx_mult
		    (bigx_long_to_big (arg1), bigx_int_to_big (arg2)));
	  else
	    return (arg2);	// int 0
	case FLTN:
	  return (mult (exact_to_inexact (arg1), arg2));
	case LONGN:
	  return (bigx_mult
		  (bigx_long_to_big (arg1), bigx_long_to_big (arg2)));
	case BIGX:
	  return (bigx_mult (bigx_long_to_big (arg1), arg2));
	}
      break;
    case BIGX:
      switch (tag2)
	{
	case INTN:
	  return (bigx_mult_i (arg1, arg2));
	case FLTN:
	  return (mult (exact_to_inexact (arg1), arg2));
	case LONGN:
	  return (bigx_mult (arg1, bigx_long_to_big (arg2)));
	case BIGX:
	  return (bigx_mult (arg1, arg2));
	}
      break;
    case FLTN:
      switch (tag2)
	{
	case INTN:
	  {
	    int s;

	    x1 = GET_FLT (arg1);
	    s = GET_INT (arg2);
	    x2 = (double) s;
	    return (makeflt (x1 * x2));
	  }
	case FLTN:
	  {
	    x1 = GET_FLT (arg1);
	    x2 = GET_FLT (arg2);
	    y1 = x1 * x2;
	    if (y1 > DBL_MAX || y1 < -DBL_MAX)
	      error (FLT_OVERF, "*", list2 (arg1, arg2));
	    if (x1 != 0.0 && x2 != 0.0 && y1 > -DBL_MIN && y1 < DBL_MIN)
	      error (FLT_UNDERF, "*", list2 (arg1, arg2));
	    return (makeflt (y1));
	  }
	case LONGN:
	case BIGX:
	  return (mult (arg1, exact_to_inexact (arg2)));
	}
      break;
    }
  error (NOT_COMPUTABLE, "*", list2 (arg1, arg2));
  return (UNDEF);
}

int
quotient (int arg1, int arg2)
{
  int n, s, tag1, tag2;
  double x1, y1, x2;

  tag1 = GET_TAG (arg1);
  tag2 = GET_TAG (arg2);
  switch (tag1)
    {
    case INTN:
      switch (tag2)
	{
	case INTN:
	  {
	    n = GET_INT (arg1);
	    if (n == 0)
	      return (arg1);
	    x1 = (double) n;
	    s = GET_INT (arg2);
	    y1 = (double) s;
	    x2 = x1 / y1;
	    if ((x2 - floor (x2)) == 0.0)
	      return (makeint ((int) x2));
	    else
	      return (makeflt (x1 / y1));
	  }
	case FLTN:
	  {
	    n = GET_INT (arg1);
	    x1 = (double) n;
	    y1 = GET_FLT (arg2);
	    return (makeflt (x1 / y1));
	  }

	case LONGN:
	case BIGX:
	  if (GET_INT (arg1) == 0)
	    return (arg1);
	  else
	    return (quotient
		    (exact_to_inexact (arg1), exact_to_inexact (arg2)));
	}
      break;
    case LONGN:
      switch (tag2)
	{
	case INTN:
	case LONGN:
	  n = quotient (exact_to_inexact (arg1), exact_to_inexact (arg2));
	  x1 = GET_FLT (n);
	  x2 = x1 - ceil (x1);
	  if (x2 == 0.0)
	    {
	      return (divide (arg1, arg2));
	    }
	  else
	    return (n);
	case BIGX:
	  return (quotient
		  (exact_to_inexact (arg1), exact_to_inexact (arg2)));
	case FLTN:
	  return (quotient (exact_to_inexact (arg1), arg2));
	}
      break;
    case BIGX:
      switch (tag2)
	{
	case INTN:
	case LONGN:
	case BIGX:
	  n = quotient (exact_to_inexact (arg1), exact_to_inexact (arg2));
	  x1 = GET_FLT (n);
	  x2 = x1 - ceil (x1);
	  if (x1 == 1.0)
	    return (makeint (1));
	  else if (x1 == -1.0)
	    return (makeint (-1));
	  else if (x2 == 0.0)
	    return (divide (arg1, arg2));
	  else
	    return (n);
	case FLTN:
	  return (quotient (exact_to_inexact (arg1), arg2));
	}
      break;
    case FLTN:
      switch (tag2)
	{
	case INTN:
	  {
	    x1 = GET_FLT (arg1);
	    s = GET_INT (arg2);
	    x2 = (double) s;
	    return (makeflt (x1 / x2));
	  }
	case FLTN:
	  {
	    x1 = GET_FLT (arg1);
	    x2 = GET_FLT (arg2);
	    return (makeflt (x1 / x2));
	  }
	case LONGN:
	case BIGX:
	  return (quotient (arg1, exact_to_inexact (arg2)));

	}
      break;
    }
  error (NOT_COMPUTABLE, "/", list2 (arg1, arg2));
  return (UNDEF);
}


int
divide (int x, int y)
{

  if (integerp (x) && longnump (y))
    return (makeint (0));
  else if (integerp (x) && bignump (y))
    return (makeint (0));
  else if (longnump (x) && bignump (y))
    return (makeint (0));
  else if (integerp (x) && integerp (y))
    return (makeint (GET_INT (x) / GET_INT (y)));
  else if (longnump (x) && integerp (y))
    return (long_int_div (x, y));
  else if (longnump (x) && longnump (y))
    return (long_long_div (x, y));
  else if (bignump (x) && integerp (y))
    return (bigx_div_i (x, y));
  else if (bignump (x) && longnump (y))
    return (bigx_div (x, bigx_long_to_big (y)));
  else if (bignump (x) && bignump (y))
    return (bigx_div (x, y));
  else
    error (ILLEGAL_ARGS, "div", list2 (x, y));

  return (UNDEF);
}

int
s_remainder (int x, int y)
{
  int i;

  if (integerp (x) && integerp (y))
    return (makeint (GET_INT (x) % GET_INT (y)));
  else if (integerp (x) && longnump (y))
    return (x);
  else if (integerp (x) && bignump (y))
    return (x);
  else if (longnump (x) && bignump (y))
    return (x);
  else if (longnump (x) && integerp (y))
    return (long_int_remainder (x, y));
  else if (longnump (x) && longnump (y))
    return (long_long_remainder (x, y));
  else if (bignump (x) && integerp (y))
    return (bigx_remainder_i (x, y));
  else if (bignump (x) && longnump (y))
    {
      i = bigx_long_to_big (y);
      return (minus (x, mult (divide (x, i), i)));
    }
  else if (bignump (x) && bignump (y))
    return (bigx_remainder (x, y));

  error (ILLEGAL_ARGS, "remainder", NIL);
  return (UNDEF);
}


// remainder of longnum and int.
int
long_int_remainder (int x, int y)
{
  long long int m, n, r;


  m = GET_LONG (x);
  n = (long long int) GET_INT (y);
  r = m % n;

  return (makeint ((int) r));
}

// remainder of longnum and longnum.
int
long_long_remainder (int x, int y)
{
  long long int m, n, r;


  m = GET_LONG (x);
  n = GET_LONG (y);
  r = m % n;

  if (llabs (r) < BIGNUM_BASE)
    return (makeint ((int) r));
  else
    return (makelong (r));
}

// divide of longnum and int.
int
long_int_div (int x, int y)
{
  long long int m, n, q;


  m = GET_LONG (x);
  n = (long long int) GET_INT (y);
  q = m / n;

  if (llabs (q) < BIGNUM_BASE)
    return (makeint ((int) q));
  else
    return (makelong (q));
}

// divide of longnum and longnum
int
long_long_div (int x, int y)
{
  long long int m, n, q;


  m = GET_LONG (x);
  n = GET_LONG (y);
  q = m / n;

  if (llabs (q) < BIGNUM_BASE)
    return (makeint ((int) q));
  else
    return (makelong (q));
}

int
absolute (int x)
{
  if (integerp (x))
    return (makeint (abs (GET_INT (x))));
  else if (longnump (x))
    return (makelong (llabs (GET_LONG (x))));
  else if (bignump (x))
    {
      return (bigx_abs (x));
    }
  else if (floatp (x))
    {
      return (makeflt (fabs (GET_FLT (x))));
    }
  error (ILLEGAL_ARGS, "abs", x);
  return (UNDEF);
}

int
angle (int y, int x)
{

  if (positive_zerop (y) && positivep (x))
    return (makeflt (0.0));
  else if (negative_zerop (y) && positivep (x))
    return (makeflt (-0.0));
  else if (positivep (y) && positivep (x))
    return (makeflt
	    (atan
	     (GET_FLT (exact_to_inexact (y)) /
	      GET_FLT (exact_to_inexact (x)))));
  else if (positivep (y) && zerop (x))
    return (makeflt (M_PI_2));
  else if (positivep (y) && negativep (x))
    return (makeflt
	    (M_PI +
	     atan (GET_FLT (exact_to_inexact (y)) /
		   GET_FLT (exact_to_inexact (x)))));
  else if (positive_zerop (y) && negativep (x))
    return (makeflt (M_PI));
  else if (negative_zerop (y) && negativep (x))
    return (makeflt (-M_PI));
  else if (negativep (y) && negativep (x))
    return (makeflt
	    (-M_PI +
	     atan (GET_FLT (exact_to_inexact (y)) /
		   GET_FLT (exact_to_inexact (x)))));
  else if (negativep (y) && zerop (x))
    return (makeflt (-M_PI_2));
  else if (negativep (y) && positivep (x))
    return (makeflt
	    (atan
	     (GET_FLT (exact_to_inexact (y)) /
	      GET_FLT (exact_to_inexact (x)))));
  else if (zerop (y) && positivep (x))
    return (makeflt (0.0));
  else if (zerop (y) && negativep (x))
    return (makeflt (M_PI));
  else if (positive_zerop (y) && positive_zerop (x))
    return (makeflt (+0.0));
  else if (negative_zerop (y) && positive_zerop (x))
    return (makeflt (-0.0));
  else if (positive_zerop (y) && negative_zerop (x))
    return (makeflt (M_PI));
  else if (negative_zerop (y) && negative_zerop (x))
    return (makeflt (-M_PI));
  else if (positive_zerop (y) && zerop (x))
    return (makeflt (M_PI_2));
  else if (negative_zerop (y) && zerop (x))
    return (makeflt (-M_PI_2));
  else
    {
      error (ILLEGAL_ARGS, "angle", list2 (x, y));
      return (UNDEF);
    }
}

// GCD of integer
int
int_gcd (int x, int y)
{
  if (y == 0)
    return (x);

  while (y != 0)
    {
      int r;

      r = x % y;
      x = y;
      y = r;
    }
  return (x);
}

// GCD of number(include bignum)
int
gcd (int x, int y)
{
  if (integerp (x) && integerp (y))
    return (makeint (abs (int_gcd (GET_INT (x), GET_INT (y)))));

  else if (floatp (x) && integerp (y))
    return (makeflt
	    ((double) abs (int_gcd ((int) GET_FLT (x), GET_INT (y)))));

  else if (integerp (x) && floatp (y))
    return (makeflt
	    ((double) abs (int_gcd (GET_INT (x), (int) GET_FLT (y)))));

  else if (floatp (x) && floatp (y))
    return (makeflt
	    ((double) abs (int_gcd (GET_FLT (x), (int) GET_FLT (y)))));

  while (!zerop (y))
    {
      int r;

      r = s_remainder (x, y);
      x = y;
      y = r;

    }
  return (absolute (x));
}

// LCM of integer
int
int_lcm (int m, int n)
{
  if (m == 0 || n == 0)
    return (0);

  return ((m / int_gcd (m, n)) * n);
}

// LCM of number(include bignum)
int
lcm (int x, int y)
{
  int g, d, res;
  if (integerp (x) && integerp (y) && abs (GET_INT (x)) < 10000
      && abs (GET_INT (y)) < 10000)
    // because  x,y < sqrt(BIGNUM_BASE)
    return (makeint (abs (int_lcm (GET_INT (x), GET_INT (y)))));

  else if (floatp (x) && integerp (y))
    return (makeflt
	    ((double) abs (int_lcm ((int) GET_FLT (x), GET_INT (y)))));

  else if (integerp (x) && floatp (y))
    return (makeflt
	    ((double) abs (int_lcm (GET_INT (x), (int) GET_FLT (y)))));

  else if (floatp (x) && floatp (y))
    return (makeflt
	    ((double) abs (int_lcm (GET_FLT (x), (int) GET_FLT (y)))));

  else
    {
      g = gcd (x, y);
      d = divide (absolute (x), g);
      res = mult (d, absolute (y));
      return (res);
    }
}

//newton method for longnum
long long int
isqrt1 (long long int n, long long int init)
{
  long long int s;

  s = init;

  while (s * s > n)
    {
      s = (s + n / s) / 2;
    }
  return (s);
}

//newton method for bignum
int
isqrt2 (int n, int init)
{
  int s;

  s = init;
  while (greaterp (mult (s, s), n))
    {
      //print(s);printf("\n");
      s = divide (plus (s, divide (n, s)), makeint (2));
    }
  return (s);
}

// basic isqrt (for small bignum)
int
isqrt3 (int x)
{
  int len, msb, pointer, init, i;
  long long int lmsb;
  len = get_length (x);
  pointer = get_pointer (x);
  if (len % 2 == 0)
    {
      lmsb =
	(long long int) bigcell[pointer] * BIGNUM_BASE +
	(long long int) bigcell[pointer - 1];
      init = gen_big ();
      len = (len - 2) / 2;
      for (i = 0; i < len; i++)
	{
	  bigcell[big_pt0++] = 0;
	}
      bigcell[big_pt0++] = (int) sqrt (lmsb) + 10000;
      set_sign (init, 1);
      set_pointer (init, big_pt0 - 1);
      set_length (init, len + 1);
    }
  else
    {
      msb = bigcell[pointer];
      init = gen_big ();
      len = (len - 1) / 2;
      for (i = 0; i < len; i++)
	{
	  bigcell[big_pt0++] = 0;
	}
      bigcell[big_pt0++] = (int) sqrt (msb) + 1;
      set_sign (init, 1);
      set_pointer (init, big_pt0 - 1);
      set_length (init, len + 1);
    }

  return (isqrt2 (x, init));

}

int
isqrt4 (int x)
{
  int len, n, p, init;

  len = get_length (x);

  n = 1;
  p = 2;
  while ((len - p) > len / 4)
    {
      n++;
      p = 2 * p;
    }

  init = bigx_shift_left (x, p);
  init = plus (isqrt3 (init), makeint (1));
  init = bigx_shift_right (init, p / 2);

  return (isqrt2 (x, init));


}

int
isqrt (int x)
{
  if (integerp (x))
    return (makeint (floor (sqrt (GET_INT (x)))));
  else if (floatp (x))
    return (makeint (floor (sqrt (GET_FLT (x)))));
  else if (longnump (x))
    {
      long long int n, init;
      n = GET_LONG (x);
      init = (long long int) sqrt (n) + 1;
      return (makeint ((int) isqrt1 (n, init)));
    }
  else
    {
      //if (get_length (x) < 100)
	return (isqrt3 (x));
      //else
	//return (isqrt4 (x));
    }
}


/*
 * try and error for OPEN-MP int mat_mult(int x, int y){ int
 * i,j,k,m,n,o,p,m1,n1,o1,p1,res; double
 * A[MATSIZE][MATSIZE],B[MATSIZE][MATSIZE],C[MATSIZE][MATSIZE];
 * 
 * if(!(length(array_length(x)) == 2 && length(array_length(y)) == 2))
 * error(ILLEGAL_ARGS, "*", list2(x,y)); if(GET_INT(cadr(array_length(x))) 
 * != GET_INT(car(array_length(y)))) error(ILLEGAL_ARGS, "*", list2(x,y));
 * 
 * m1 = car(array_length(x)); n1 = cadr(array_length(x)); o1 =
 * car(array_length(y)); p1 = cadr(array_length(y));
 * 
 * m = GET_INT(m1); n = GET_INT(n1); o = GET_INT(o1); p = GET_INT(p1);
 * if(m>MATSIZE || n>MATSIZE || o>MATSIZE || p>MATSIZE)
 * error(OUT_OF_RANGE,"*",NIL); if(m*p+FREESIZE > fc){ shelterpush(x);
 * shelterpush(y); gbc(); shelterpop(); shelterpop(); } res =
 * makearray(list2(m1,p1),UNDEF); #pragma omp parallel for private(i,j)
 * for(i=0; i<m; i++) for(j=0; j<n; j++) A[i][j] =
 * GET_FLT(matrix_ref(x,n,i,j)); #pragma omp parallel for private(i,j)
 * for(i=0; i<o; i++) for(j=0; j<p; j++) B[i][j] =
 * GET_FLT(matrix_ref(y,p,i,j)); #pragma omp parallel for private(i,j)
 * for(i=0; i<m; i++) for(j=0; j<p; j++) C[i][j] = 0.0; #pragma omp
 * parallel for private(i,j,k) for(i=0; i<m; i++) for(j=0; j<p; j++)
 * for(k=0; k<n; k++) C[i][j] = C[i][j] + A[i][k] * B[k][j];
 * 
 * 
 * for(i=0; i<m; i++) for(j=0; j<p; j++)
 * matrix_set(res,p,i,j,makeflt(C[i][j]));
 * 
 * return(NIL); }
 * 
 * int mat_vec_mult(int x, int y){ int i,j,m,n,res; float
 * A[MATSIZE][MATSIZE],B[MATSIZE],C[MATSIZE];
 * 
 * if(length(array_length(x)) != 2) error(ILLEGAL_ARGS, "*", x);
 * if(GET_INT(cadr(array_length(x))) != vector_length(y))
 * error(ILLEGAL_ARGS, "*", list2(x,y));
 * 
 * m = GET_INT(car(array_length(x))); n = GET_INT(cadr(array_length(x)));
 * if(m>MATSIZE || n>MATSIZE) error(OUT_OF_RANGE,"*",NIL); if(m+FREESIZE > 
 * fc) gbc(); res = makevec(m,UNDEF); #pragma omp parallel for
 * private(i,j) for(i=0; i<m; i++) for(j=0; j<n; j++) A[i][j] =
 * GET_FLT(matrix_ref(x,n,i,j)); #pragma omp parallel for private(i)
 * for(i=0; i<m; i++) B[i] = GET_FLT(vector_ref(y,i)); #pragma omp
 * parallel for private(i) for(i=0; i<m; i++) C[i] = 0.0; #pragma omp
 * parallel for private(i,j) for(i=0; i<m; i++) for(j=0; j<n; j++) C[i] =
 * C[i] + A[i][j] * B[j];
 * 
 * for(i=0; i<m; i++) vector_set(res,i,makeflt(C[i]));
 * 
 * return(res); }
 * 
 * int vec_plus(int x, int y){ int i,size,res; double
 * A[MATSIZE],B[MATSIZE],C[MATSIZE];
 * 
 * if(vector_length(x) != vector_length(y)) error(ILLEGAL_ARGS,"+",
 * list2(x,y));
 * 
 * size = vector_length(x); res = makevec(size,UNDEF);
 * 
 * #pragma omp parallel for private(i) for(i=0; i<size; i++) A[i] =
 * GET_FLT(vector_ref(x,i)); #pragma omp parallel for private(i) for(i=0;
 * i<size; i++) B[i] = GET_FLT(vector_ref(y,i)); #pragma omp parallel for
 * private(i) for(i=0; i<size; i++) C[i] = 0.0; #pragma omp parallel for
 * private(i) for(i=0; i<size; i++) C[i] = A[i] + B[i];
 * 
 * for(i=0; i<size; i++) vector_set(res,i,makeflt(C[i]));
 * 
 * return(res); }
 * 
 * int vec_minus(int x, int y){ int i,size,res; double
 * A[MATSIZE],B[MATSIZE],C[MATSIZE];
 * 
 * if(vector_length(x) != vector_length(y)) error(ILLEGAL_ARGS,"-",
 * list2(x,y));
 * 
 * size = vector_length(x); res = makevec(size,UNDEF);
 * 
 * #pragma omp parallel for private(i) for(i=0; i<size; i++) A[i] =
 * GET_FLT(vector_ref(x,i)); #pragma omp parallel for private(i) for(i=0;
 * i<size; i++) B[i] = GET_FLT(vector_ref(y,i)); #pragma omp parallel for
 * private(i) for(i=0; i<size; i++) C[i] = 0.0; #pragma omp parallel for
 * private(i) for(i=0; i<size; i++) C[i] = A[i] - B[i];
 * 
 * for(i=0; i<size; i++) vector_set(res,i,makeflt(C[i]));
 * 
 * return(res); } 
 */
