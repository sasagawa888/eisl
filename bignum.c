/* New bignum
* I am designing a new bignum data structure.
*  bigcell[BIGISZE]  array of 32bit integer.
*  big_pt0  pointer of temporaly bignum. 
*  big_pt1  pointer of parmanent bignum.
*  90% of bigcell is temporaly area and rest 10% is parmanent area.
*  in temporaly area rear 10% is working area for divide function.
*  bigcell = [[temporaly50%,temporalyworking40%],parmanent10%]
*  each bignum   elementn ... element1,element0
*  Car-part of the cell has the pointer of MSB.
*  Cdr-part of then cell has the length
*  
   bigcell[int]                  heap[cell structure]
   |(temporarly)|               |          |
   |LSB  ^      |      |-------<|BIGX(car) |
   |     |      |      |        |          |
   |MSB         |<------        |          |
   |(working)   | big_pt0       |          |
   |            |               |          |
   |(parmanent) | big_pt1       |          |


* NTT-Multiply
* bigcell 32bit integer -> radix 10^3 32bit integer
* bignum-x bignum-y     IFFT(FFT(x)*FFT(y)) -> bigcell 32bit integer(normalize) 
* integer data type uses 64bit integer. Because to avoid overflow in 32bit.
* It will be calculated correctly by multiplying by about 300000 digits.
* if comment out #define NTT, bigx_mult does not use NTT.
*/

#define NTT

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "eisl.h"
#include "fmt.h"
#include "text.h"
#include "complex.h"


#define CHECKBIG0 if(big_pt0<0 || big_pt0>=BIGNUM_PARMA){error(RESOURCE_ERR,"bigcell pt0",big_pt0);}
#define CHECKBIG1 if(big_pt1<0 || big_pt1>=BIGSIZE){error(RESOURCE_ERR,"bigcell pt1",big_pt1);}

#define DEBUG error(RESOURCE_ERR,"debug",NIL);
#define CPRINT(x) printf("%f+%fi\n", creal(x), cimag(x));

int
get_length (int x)
{
  return (GET_CDR (x));
}

void
set_length (int x, int y)
{
  SET_CDR (x, y);
}

int
get_pointer (int x)
{
  return (GET_CAR (x));
}

void
set_pointer (int x, int y)
{
  SET_CAR (x, y);
}


int
makebigx (char *bignum)
{
  char integer[15];
  int i, j, res, sign, len;

  // check sign
  if (bignum[0] == '-')
    sign = -1;
  else
    sign = 1;
  // remove sign
  if (bignum[0] == '-' || bignum[0] == '+')
    {
      i = laststr (bignum);
      for (j = 0; j < i; j++)
	bignum[j] = bignum[j + 1];

      bignum[j] = NUL;
    }
  // length to check long data type
  len = 0;
  // generate bignum data cell
  res = gen_big ();

  i = laststr (bignum);
  while (i >= 0)
    {
      if (i > 8)
	{
	  for (j = 8; j >= 0; j--)
	    {
	      integer[j] = bignum[i];
	      i--;
	    }
	  integer[9] = NUL;
	  CHECKBIG0 bigcell[big_pt1++] = atoi (integer);
	  len++;
	}
      else
	{
	  integer[i + 1] = NUL;
	  while (i >= 0)
	    {
	      integer[i] = bignum[i];
	      i--;
	    }
	  CHECKBIG0 bigcell[big_pt1++] = atoi (integer);
	  len++;
	}
    }

  if (len == 2)
    {
      long long int l, m;

      CHECKBIG0 l = (long long int) bigcell[big_pt1 - 1] * BIGNUM_BASE;
      m = (long long int) bigcell[big_pt1 - 2];
      m = (l + m) * sign;
      SET_TAG (res, LONGN);
      SET_LONG (res, m);
      SET_AUX (res, clongnum);
      return (res);
    }
  else
    {
      SET_TAG (res, BIGX);
      set_pointer (res, big_pt1 - 1);
      set_length (res, len);
      set_sign (res, sign);
      SET_AUX (res, cbignum);
      return (res);
    }
}


void
print_bigx (int x)
{
  int y, len;
  Text_save_T save;
  Text_T txt1 = { 0, NULL }, txt2;
  char str[SHORT_STRSIZE];

  if (GET_OPT (output_stream) == EISL_OUTSTR)
    {
      save = Text_save ();
    }

  if (get_sign (x) == -1)
    {
      if (GET_OPT (output_stream) != EISL_OUTSTR)
	{
	  fputc ('-', GET_PORT (output_stream));
	}
      else
	{
	  txt1 = Text_put ("-");
	}
    }
  y = get_pointer (x);		//get pointer of bigcell
  len = get_length (x);		//get length of bignum;
  if (GET_OPT (output_stream) != EISL_OUTSTR)
    {
      Fmt_fprint (GET_PORT (output_stream), "%d", bigcell[y]);
    }
  else
    {
      Fmt_sfmt (str, SHORT_STRSIZE, "%d", bigcell[y]);
      txt2 = Text_put (str);
      txt1 = Text_cat (txt1, txt2);
    }
  y--;
  len--;

  do
    {
      if (GET_OPT (output_stream) != EISL_OUTSTR)
	{
	  Fmt_fprint (GET_PORT (output_stream), "%09d", bigcell[y]);
	}
      else
	{
	  Fmt_sfmt (str, SHORT_STRSIZE, "%09d", bigcell[y]);
	  txt2 = Text_put (str);
	  txt1 = Text_cat (txt1, txt2);
	}
      y--;
      len--;
    }
  while (len > 0);

  if (GET_OPT (output_stream) == EISL_OUTSTR)
    {
      char *out_str = GET_NAME (output_stream);
      size_t l = strlen (out_str);
      Text_get (out_str + l, STRSIZE - l, txt1);
      Text_restore (&save);
    }
}


int
gen_big (void)
{
  int res;

  res = freshcell ();
  SET_CDR (res, NIL);
  SET_PROP (res, -1);
  return (res);
}

// old bignum
// get address of upper digit
int
next (int x)
{
  return (GET_CDR (x));
}

// old bignum
// get address of lower digit
int
prev (int x)
{
  return (GET_PROP (x));
}

// set sign
void
set_sign (int x, int y)
{
  SET_OPT (x, y);
}

// get sign
int
get_sign (int x)
{
  return (GET_OPT (x));
}

int
bigx_positivep (int x)
{
  if (get_sign (x) == 1)
    return (1);
  else
    return (0);
}

int
bigx_negativep (int x)
{
  if (get_sign (x) == -1)
    return (1);
  else
    return (0);
}



int
bigx_eqp (int x, int y)
{
  int len, pointerx, pointery;

  if (get_sign (x) != get_sign (y))
    return (0);
  else if (get_length (x) != get_length (y))
    return (0);

  len = get_length (x);
  pointerx = get_pointer (x);
  pointery = get_pointer (y);
  do
    {
      if (bigcell[pointerx] != bigcell[pointery])
	return (0);

      pointerx--;
      pointery--;
      len--;
    }
  while (len > 0);

  return (1);

}


int
bigx_abs_smallerp (int x, int y)
{
  int len1, len2, pointerx, pointery;

  len1 = get_length (x);
  len2 = get_length (y);

  if (len1 < len2)
    return (1);
  else if (len1 > len2)
    return (0);
  else
    {
      pointerx = get_pointer (x);
      pointery = get_pointer (y);
      do
	{
	  if (bigcell[pointerx] < bigcell[pointery])
	    return (1);
	  if (bigcell[pointerx] > bigcell[pointery])
	    return (0);

	  pointerx--;
	  pointery--;
	  len1--;
	}
      while (len1 > 0);
      return (0);
    }

}

int
bigx_smallerp (int x, int y)
{

  if (bigx_positivep (x) && bigx_negativep (x))
    return (0);
  else if (bigx_negativep (x) && bigx_positivep (y))
    return (1);
  else if (bigx_positivep (x) && bigx_positivep (y))
    return (bigx_abs_smallerp (x, y));
  else if (bigx_negativep (x) && bigx_negativep (y))
    return (bigx_abs_smallerp (y, x));
  else
    return (0);

  return (0);
}




int
bigx_int_to_big (int x)
{
  int res, y;

  y = GET_INT (x);
  CHECKBIG0 bigcell[big_pt0++] = abs (y);
  res = gen_big ();
  SET_TAG (res, BIGX);
  set_pointer (res, big_pt0 - 1);
  set_length (res, 1);
  if (y >= 0)
    set_sign (res, 1);
  else
    set_sign (res, -1);
  return (res);
}

int
bigx_long_to_big (int x)
{
  int res, i2, i1;
  long long int l;

  l = GET_LONG (x);
  i2 = llabs (l) % BIGNUM_BASE;
  i1 = llabs (l) / BIGNUM_BASE;
  CHECKBIG0 bigcell[big_pt0++] = i2;
  CHECKBIG0 bigcell[big_pt0++] = i1;
  res = gen_big ();
  SET_TAG (res, BIGX);
  set_pointer (res, big_pt0 - 1);
  set_length (res, 2);
  if (l >= 0)
    set_sign (res, 1);
  else
    set_sign (res, -1);
  return (res);
}


int
bigx_simplify (int x)
{
  int i1;
  long long int l, l1, l2;

  if (get_length (x) == 0)
    {
      return (makeint (0));
    }
  else if (get_length (x) == 1)
    {
      i1 = bigcell[get_pointer (x)];
      i1 = i1 * get_sign (x);
      return (makeint (i1));
    }
  else if (get_length (x) == 2)
    {
      l1 = bigcell[get_pointer (x)];
      l2 = bigcell[get_pointer (x) - 1];
      l = (l1 * BIGNUM_BASE + l2) * get_sign (x);
      return (makelong (l));
    }
  else
    return (x);
}

// add n-zero-cells to x
int
bigx_shift (int x, int n)
{
  int res, len, pointer;

  len = get_length (x);
  pointer = get_pointer (x) - len + 1;	// LSB
  res = gen_big ();
  SET_TAG (res, BIGX);
  set_sign (res, get_sign (x));

  int i;
  for (i = 0; i < n; i++)
    {
      CHECKBIG0 bigcell[big_pt0++] = 0;
    }
  for (i = 0; i < len; i++)
    {
      CHECKBIG0 bigcell[big_pt0++] = bigcell[pointer + i];
    }

  set_pointer (res, big_pt0 - 1);
  set_length (res, len + n);
  return (res);
}

int
bigx_to_parmanent (int x)
{
  int len, pointer;

  if(!bignump(x))
      return(x);

  len = get_length (x);
  pointer = get_pointer (x);

  big_pt1 = big_pt1 + len;
  CHECKBIG1 int i;
  for (i = 0; i < len; i++)
    {
      bigcell[big_pt1 - i] = bigcell[pointer - i];
    }

  big_pt1++;
  set_pointer (x, big_pt1 - 1);
  return (x);
}


int
bigx_abs (int x)
{
  int res;

  res = gen_big ();
  SET_TAG (res, BIGX);
  set_sign (res, 1);
  set_pointer (res, get_pointer (x));
  set_length (res, get_length (x));
  return (res);
}

int
bigx_zerop (int x)
{
  int len, pointer;

  len = get_length (x);
  pointer = get_pointer (x);
  while (len > 0)
    {
      if (bigcell[pointer--] != 0)
	return (0);
      len--;
    }
  return (1);
}

int
bigx_plus (int arg1, int arg2)
{
  int res;

  res = UNDEF;
  if (bigx_positivep (arg1) && bigx_positivep (arg2))
    {
      res = bigx_plus1 (arg1, arg2);
      set_sign (res, 1);
    }
  else if (bigx_negativep (arg1) && bigx_negativep (arg2))
    {
      res = bigx_plus1 (arg1, arg2);
      set_sign (res, -1);
    }
  else if (bigx_positivep (arg1) && bigx_negativep (arg2))
    {
      if (bigx_abs_smallerp (arg1, arg2))
	{
	  res = bigx_minus1 (arg2, arg1);
	  set_sign (res, -1);
	}
      else
	{
	  res = bigx_minus1 (arg1, arg2);
	  set_sign (res, 1);
	}
    }
  else if (bigx_negativep (arg1) && bigx_positivep (arg2))
    {
      if (bigx_abs_smallerp (arg1, arg2))
	{
	  res = bigx_minus1 (arg2, arg1);
	  set_sign (res, 1);
	}
      else
	{
	  res = bigx_minus1 (arg1, arg2);
	  set_sign (res, -1);
	}
    }

  if (simp_flag)
    res = bigx_simplify (res);

  return (res);
}


int
bigx_plus1 (int arg1, int arg2)
{
  int len1, len2, pointerx, pointery, c, len, res;

  len1 = get_length (arg1);
  len2 = get_length (arg2);
  pointerx = get_pointer (arg1) - len1 + 1;	//LSB
  pointery = get_pointer (arg2) - len2 + 1;	//LSB
  res = gen_big ();
  SET_TAG (res, BIGX);
  set_sign (res, 1);
  c = 0;
  len = 0;
  do
    {
      int x, y, z, q;

      if (len1 > 0)
	x = bigcell[pointerx];
      else
	x = 0;

      if (len2 > 0)
	y = bigcell[pointery];
      else
	y = 0;

      z = x + y + c;
      c = z / BIGNUM_BASE;
      q = z % BIGNUM_BASE;
      CHECKBIG0 bigcell[big_pt0++] = q;
      pointerx++;
      pointery++;
      len1--;
      len2--;
      len++;
    }
  while (len1 > 0 || len2 > 0);
  if (c != 0)
    {
      CHECKBIG0 bigcell[big_pt0++] = c;
    }
  set_pointer (res, big_pt0 - 1);
  set_length (res, len);
  return (res);
}


int
bigx_minus (int arg1, int arg2)
{
  int res;

  res = UNDEF;
  if (bigx_positivep (arg1) && bigx_positivep (arg2))
    {
      if (bigx_smallerp (arg1, arg2))
	{
	  res = bigx_minus1 (arg2, arg1);
	  set_sign (res, -1);
	}
      else
	{
	  res = bigx_minus1 (arg1, arg2);
	  set_sign (res, 1);
	}
    }
  else if (bigx_positivep (arg1) && bigx_negativep (arg2))
    {
      res = bigx_plus1 (arg1, arg2);
      set_sign (res, 1);
    }
  else if (bigx_negativep (arg1) && bigx_positivep (arg2))
    {
      res = bigx_plus1 (arg1, arg2);
      set_sign (res, -1);
    }
  else if (bigx_negativep (arg1) && bigx_negativep (arg2))
    {
      if (bigx_abs_smallerp (arg1, arg2))
	{
	  res = bigx_minus1 (arg2, arg1);
	  set_sign (res, 1);
	}
      else
	{
	  res = bigx_minus1 (arg1, arg2);
	  set_sign (res, -1);
	}
    }
  if (simp_flag)
    res = bigx_simplify (res);

  return (res);
}


// arg1 > arg2
int
bigx_minus1 (int arg1, int arg2)
{
  int len1, len2, pointerx, pointery, len, z, c, res;


  len1 = get_length (arg1);
  len2 = get_length (arg2);
  pointerx = get_pointer (arg1) - len1 + 1;	// LSB
  pointery = get_pointer (arg2) - len2 + 1;	// LSB
  res = gen_big ();
  SET_TAG (res, BIGX);
  set_sign (res, 1);
  c = 0;
  len = 0;
  do
    {
      int x, y;

      if (len1 > 0)
	x = bigcell[pointerx];
      else
	x = 0;

      if (len2 > 0)
	y = bigcell[pointery];
      else
	y = 0;


      if ((x + c - y) < 0)
	{
	  z = (x + BIGNUM_BASE + c) - y;
	  c = -1;
	}
      else
	{
	  z = (x + c) - y;
	  c = 0;
	}
      CHECKBIG0 bigcell[big_pt0++] = z;
      pointerx++;
      pointery++;
      len1--;
      len2--;
      len++;
    }
  while (len1 > 0 || len2 > 0);

  big_pt0--;
  while (bigcell[big_pt0] == 0 && len > 1)
    {
      big_pt0--;
      len--;
    }

  big_pt0++;
  set_pointer (res, big_pt0 - 1);
  set_length (res, len);
  return (res);
}



int
bigx_mult (int arg1, int arg2)
{
  int res;

  #ifdef NTT
  if (get_length (arg1) + get_length (arg2) > 100)
    return (bigx_ntt_mult (arg1, arg2));
  #endif

  res = UNDEF;
  if (bigx_positivep (arg1) && bigx_positivep (arg2))
    {
      res = bigx_mult1 (arg1, arg2);
      set_sign (res, 1);
    }
  else if (bigx_positivep (arg1) && bigx_negativep (arg2))
    {
      res = bigx_mult1 (arg1, arg2);
      set_sign (res, -1);
    }
  else if (bigx_negativep (arg1) && bigx_positivep (arg2))
    {
      res = bigx_mult1 (arg1, arg2);
      set_sign (res, -1);
    }
  else if (bigx_negativep (arg1) && bigx_negativep (arg2))
    {
      res = bigx_mult1 (arg1, arg2);
      set_sign (res, 1);
    }
  if (simp_flag)
    {
      res = bigx_simplify (res);
    }

  return (res);
}


int
bigx_mult1 (int arg1, int arg2)
{
  int res, len1, len2, pointerx, pointery, len;
  long long int x, y, z, l1, l2, c;


  res = gen_big ();
  SET_TAG (res, BIGX);
  len1 = get_length (arg1);
  len2 = get_length (arg2);
  len = len1 + len2;
  set_sign (res, 1);

  // clear area of calculate
  int i, j;
  for (i = 0; i <= len; i++)
    {
      CHECKBIG0 bigcell[i + big_pt0] = 0;
    }
  pointery = get_pointer (arg2) - len2 + 1;	//LSB
  for (j = 0; j < len2; j++)
    {
      pointerx = get_pointer (arg1) - len1 + 1;	//LSB
      for (i = 0; i < len1; i++)
	{
	  x = (long long int) bigcell[pointerx + i];
	  y = (long long int) bigcell[pointery + j];
	  z = x * y;
	  l2 = z % BIGNUM_BASE;
	  l1 = z / BIGNUM_BASE;
	  l2 = l2 + (long long int) bigcell[big_pt0 + j + i];
	  if (l2 >= BIGNUM_BASE)
	    {
	      c = l2 / BIGNUM_BASE;
	      l2 = l2 % BIGNUM_BASE;
	    }
	  else
	    {
	      c = 0;
	    }
	  l1 = l1 + c + (long long int) bigcell[big_pt0 + j + i + 1];
	  CHECKBIG0 bigcell[big_pt0 + j + i] = (int) l2;
	  bigcell[big_pt0 + j + i + 1] = (int) l1;
	}
    }

  big_pt0 = big_pt0 + len;

  while (bigcell[big_pt0] == 0 && len > 1)
    {
      big_pt0--;
      len--;
    }
  big_pt0++;
  set_pointer (res, big_pt0 - 1);
  set_length (res, len + 1);
  return (res);
}

int
bigx_div (int arg1, int arg2)
{
  int res, x, y;


  res = UNDEF;
  // if devidend is smaller than divisor,return 0
  if (bigx_abs_smallerp (arg1, arg2))
    return (makeint (0));

  if (bigx_positivep (arg1) && bigx_positivep (arg2))
    {
      res = bigx_div1 (arg1, arg2);
    }
  else if (bigx_positivep (arg1) && bigx_negativep (arg2))
    {
      y = bigx_abs (arg2);
      res = bigx_div1 (arg1, y);
      set_sign (res, -1);
    }
  else if (bigx_negativep (arg1) && bigx_positivep (arg2))
    {
      x = bigx_abs (arg1);
      res = bigx_div1 (x, arg2);
      set_sign (res, -1);
    }
  else if (bigx_negativep (arg1) && bigx_negativep (arg2))
    {
      x = bigx_abs (arg1);
      y = bigx_abs (arg2);
      res = bigx_div1 (x, y);
      set_sign (res, 1);
    }

  if (simp_flag)
    res = bigx_simplify (res);
  return (res);
}



int
bigx_div1 (int arg1, int arg2)
{
  int shift, save0, save1, d,
    res, len, q, dividend, subtract, pointerx, pointery, msb1, msb2;
  long long int lmsb1;


  // arg1 < arg2 -> 0
  if (smallerp (arg1, arg2))
    return (makeint (0));

  simp_flag = false;
  pointery = get_pointer (arg2);	//MSB pointer

  // Knuth The art of computer programing D-algorithm
  if (bigcell[pointery] < BIGNUM_BASE / 2)
    {
      d = BIGNUM_BASE / (1 + bigcell[pointery]);
      arg1 = bigx_mult1 (arg1, bigx_int_to_big (makeint (d)));
      arg2 = bigx_mult1 (arg2, bigx_int_to_big (makeint (d)));
    }

  res = gen_big ();
  SET_TAG (res, BIGX);
  set_sign (res, 1);
  len = 0;
  big_pt0 = big_pt0 + get_length (arg1);	// prepare area of answer. 
  set_pointer (res, big_pt0);
  pointery = get_pointer (arg2);	//MSB pointer
  msb2 = bigcell[pointery];	// value of MSB
  dividend = arg1;
  save1 = BIGNUM_WORK;

  do
    {
      save0 = big_pt0;
      big_pt0 = save1;
      shift = get_length (dividend) - get_length (arg2);
      pointerx = get_pointer (dividend);	// MSB
      msb1 = bigcell[pointerx];
      if (msb1 >= msb2)
	{
	  q = msb1 / msb2;

	}
      else
	{
	  lmsb1 =
	    (long long int) bigcell[pointerx] * BIGNUM_BASE +
	    (long long int) bigcell[pointerx - 1];
	  q = (int) (lmsb1 / (long long int) msb2);
	  shift--;
	}


      subtract =
	bigx_shift (bigx_mult1 (arg2, bigx_int_to_big (makeint (q))), shift);
      dividend = bigx_minus (dividend, subtract);

      // e.g. (div 100000000000000000000000000 25000000000000000000000002) = 3 (not 4)
      while (negativep (dividend))
	{
	  dividend = plus (dividend, bigx_shift (arg2, shift));
	  q--;
	}

      save1 = big_pt0;
      big_pt0 = save0;
      CHECKBIG0 bigcell[big_pt0 - len] = q;
      len++;

    }
  while (!bigx_zerop (dividend) && !smallerp (dividend, arg2));

  // when divident is smaller than divisior and shift > 0 insert zero
  //e.q.  div(3000000000000000000,30000000000)
  while (shift > 0)
    {
      CHECKBIG0 bigcell[big_pt0 - len] = 0;
      shift--;
      len++;
    }

  simp_flag = true;
  big_pt0++;
  set_pointer (res, big_pt0 - 1);
  set_length (res, len);
  return (res);
}


int
bigx_remainder (int arg1, int arg2)
{
  int shift,
    res, len, q, dividend, subtract,
    pointerx, pointery, save0, pointer, msb1, msb2;
  long long int lmsb1;


  // arg1 > arg2 -> 0
  if (smallerp (arg1, arg2))
    return (makeint (0));

  res = gen_big ();
  SET_TAG (res, BIGX);
  set_sign (res, 1);
  big_pt0 = big_pt0 + get_length (arg1);	// prepare area of answer. 
  set_pointer (res, big_pt0);
  pointery = get_pointer (arg2);	//MSB pointer
  msb2 = bigcell[pointery];	// value of MSB
  dividend = arg1;
  save0 = big_pt0;
  big_pt0 = BIGNUM_WORK;	// change to working area

  do
    {
      shift = get_length (dividend) - get_length (arg2);
      pointerx = get_pointer (dividend);	// MSB
      msb1 = bigcell[pointerx];
      if (msb1 >= msb2)
	{
	  q = msb1 / msb2;

	}
      else
	{
	  lmsb1 =
	    (long long int) bigcell[pointerx] * BIGNUM_BASE +
	    (long long int) bigcell[pointerx - 1];
	  q = (int) (lmsb1 / (long long int) msb2);
	  shift--;
	}
      subtract =
	bigx_shift (bigx_mult1 (arg2, bigx_int_to_big (makeint (q))), shift);
      dividend = bigx_minus (dividend, subtract);

      // e.g. (div 100000000000000000000000000 25000000000000000000000002) = 3 (not 4)
      while (negativep (dividend))
	{
	  dividend = plus (dividend, bigx_shift (arg2, shift));
	  q--;
	}

    }
  while (!smallerp (dividend, arg2));

  big_pt0 = save0;		//restore pointer
  // copy dividend to big_pt0 temporarly area

  len = get_length (dividend);
  pointer = get_pointer (dividend) - len + 1;	//LSB
  int i;
  for (i = 0; i < len; i++)
    {
      CHECKBIG0 bigcell[big_pt0++] = bigcell[pointer++];
    }
  set_pointer (res, big_pt0 - 1);
  set_length (res, len);
  return (res);
}


int
bigx_big_to_flt (int x)
{
  double val;
  int pointer, len, res;

  res = freshcell ();
  val = 0.0;
  pointer = get_pointer (x);
  len = get_length (x);
  do
    {
      int i;

      i = bigcell[pointer];
      val = val * (double) BIGNUM_BASE + (double) i;
      pointer--;
      len--;
    }
  while (len > 0);
  val = val * get_sign (x);
  SET_TAG (res, FLTN);
  SET_FLT (res, val);
  return (res);
}


// bignum remainder of bignum and int
int
bigx_remainder_i (int x, int y)
{
  int abs, pointer, len, sign1, sign2;
  long long int j, r;

  abs = bigx_abs (x);
  pointer = get_pointer (abs);
  len = get_length (abs);
  sign1 = get_sign (x);

  j = GET_INT (y);
  if (j < 0)
    {
      j = llabs (j);
      sign2 = -1;
    }
  else
    {
      sign2 = 1;
    }

  r = 0;

  do
    {
      long long int i;

      i = bigcell[pointer];
      i = i + r * BIGNUM_BASE;
      if (i >= j)
	r = i % j;
      else
	r = i + r;
      pointer--;
      len--;
    }
  while (len > 0);
  return (makeint ((int) r * sign1 * sign2));
}

int
bigx_div_i (int x, int y)
{
  int res, pointer, msb, len, n, sign1, sign2;
  long long int j, r, q;


  res = gen_big ();
  len = n = get_length (x);
  msb = get_pointer (bigx_abs (x));
  sign1 = get_sign (x);

  j = GET_INT (y);
  if (j < 0)
    {
      j = llabs (j);
      sign2 = -1;
    }
  else
    {
      sign2 = 1;
    }

  r = 0;

  big_pt0 = big_pt0 + len;
  pointer = big_pt0;
  do
    {
      long long int i;

      i = bigcell[msb];
      i = i + r * BIGNUM_BASE;
      if (i >= j)
	{
	  r = i % j;
	  q = i / j;
	  bigcell[pointer--] = (int) q;
	}
      else
	{
	  r = i + r;
	  bigcell[pointer--] = 0;
	}
      msb--;
      n--;
    }
  while (n > 0);
  SET_TAG (res, BIGX);
  while (bigcell[big_pt0] == 0 && len > 1)
    {
      big_pt0--;
      len--;
    }
  big_pt0++;
  set_pointer (res, big_pt0 - 1);
  set_length (res, len);
  set_sign (res, sign1 * sign2);
  if (simp_flag)
    res = bigx_simplify (res);
  return (res);
}


// half of bignum for ISQRT
int
bigx_half (int x)
{
  int res, pointer, msb, len, n, sign;
  int r, q;

  res = gen_big ();
  len = n = get_length (x);
  msb = get_pointer (bigx_abs (x));
  sign = get_sign (x);

  r = 0;

  big_pt0 = big_pt0 + len;
  pointer = big_pt0;
  do
    {
      int i;

      i = bigcell[msb];
      i = i + r * BIGNUM_BASE;
	    r = i % 2;
	    q = i / 2;
	    bigcell[pointer--] = q;
      msb--;
      n--;
    }
  while (n > 0);
  SET_TAG (res, BIGX);
  while (bigcell[big_pt0] == 0 && len > 1)
    {
      big_pt0--;
      len--;
    }
  big_pt0++;
  set_pointer (res, big_pt0 - 1);
  set_length (res, len);
  set_sign (res, sign);
  if (simp_flag)
    res = bigx_simplify (res);
  return (res);
}


// multple of bignum and int
int
bigx_mult_i (int x, int y)
{
  int res, len, pointer, n, sign1, sign2;
  long long int j, c;


  res = gen_big ();
  len = n = get_length (x);
  pointer = get_pointer (x) - len + 1;	//LSB
  sign1 = get_sign (x);

  j = GET_INT (y);
  if (j < 0)
    {
      j = llabs (j);
      sign2 = -1;
    }
  else
    {
      sign2 = 1;
    }

  c = 0;

  do
    {
      long long int i, z;

      i = bigcell[pointer];
      z = i * j + c;
      if (z >= BIGNUM_BASE)
	{
	  c = z / BIGNUM_BASE;
	  z = z % BIGNUM_BASE;

	  CHECKBIG0 bigcell[big_pt0++] = (int) z;
	}
      else
	{
	  c = 0;
	  CHECKBIG0 bigcell[big_pt0++] = (int) z;
	}
      pointer++;
      len--;
    }
  while (len > 0);

  CHECKBIG0 bigcell[big_pt0] = (int) c;
  len = n + 1;
  while (bigcell[big_pt0] == 0 && len > 1)
    {
      big_pt0--;
      len--;
    }
  big_pt0++;

  SET_TAG (res, BIGX);
  set_pointer (res, big_pt0 - 1);
  set_length (res, len);
  set_sign (res, sign1 * sign2);
  res = bigx_simplify (res);
  return (res);
}



/*
* ---------------FFT/NTT----------------------
* FFT with number theory transformation(NTT) for fast multiplication.
* One big cell is decomposed into 3 NTT data.
* Multipliers and multipliers are stored as follows.

  nttx[0]     0  
  nttx[1]     123
  ...         456
  nttx[n/2-1] 789
  nttx[n/2]   0
  ...         0
  nttx[n-1]   0 

* Number data is stored in the first half. The remaining area is filled with 0.
* rest half of the area is filled with 0 to avoid cyclic calculation.

* One NTT DATA is 3 digits in decimal notation.
* It contains 0 ~ 999 data. The data is the remainder of the prime number P.
* It can be stored in 32bit itself, but it is stored in 64bit because it is necessary to calculate the remainder by multiplication.
* At maximum, 999 * 2 ^ 18 (261881856) can be stored in one NTT cell as a remainder of the prime number P.
* NTT is a forward calculation. INTT is the inverse map. 
* Each calculates nttx [] as a vector and returns a value with ntty [] as a vector.
* ntt_set_w_factor calculates the rotation factor in advance and saves it in ntt_factor[][].
* Save the forward rotation factor in ntt_factor [i][0]. Save the rotation factor for inverse mapping in ntt_factor [i][1].
*/
#define NTTSIZE 262144		// 2^18
#define P 1541406721		//prime-number 5880*2^18+1
#define OMEGA 103		//primitive-root (mod P)
long long int nttx[NTTSIZE], ntty[NTTSIZE], nttz[NTTSIZE];	// data area ntty=ntt(nttx),ntty=intt(nttx), nttz is to save data.
long long int ntt_factor[NTTSIZE][2];
int ntti[NTTSIZE];		// index of bit-reversal

// return size of binary. e.g. 7=111 3bit
int
get_bit (int n)
{
  int bit;

  bit = 0;
  while (n >= 2)
    {
      n = n / 2;
      bit++;
    }
  return (bit);
}

//return reversed bit number. e.g.  6=110 -> 011=3
int
bit_reverse (long long int n, int bit)
{
  int binary[32], i;


  for (i = 0; i < bit; i++)
    {
      binary[i] = n % 2;
      n = n / 2;
    }

  n = 0;
  for (i = 0; i < bit; i++)
    {
      n = binary[i] + n * 2;
    }

  return (n);
}

// save index of bit-reverse
void
ntt_set_bit_reverse (long long int n)
{
  int i, bit;

  bit = get_bit (n);
  for (i = 0; i < n; i++)
    {
      ntti[i] = bit_reverse (i, bit);
    }
}

// exponentation x^y (mod z). see SICP
long long int
expmod (long long int x, int y, long long int z)
{
  long long int res, p;

  res = 1;
  p = x;
  while (y > 0)
    {
      if ((y % 2) == 0)
	{
	  p = (p * p) % z;
	  y = y / 2;
	}
      else
	{
	  res = (res * p) % z;
	  y = y - 1;
	}
    }
  return (res);
}

// x+y (mod P)
long long int
plusmod (long long int x, long long int y)
{
  return ((x + y) % P);
}

// x*y (mod P)
long long int
multmod (long long int x, long long int y)
{
  return ((x * y) % P);
}

// x-y (mod P)
long long int
minusmod (long long int x, long long int y)
{
  return ((x - y + P) % P);
}

void
ntt_set_w_factor (int n)
{
  int i, base, base_inv;

  base = expmod (OMEGA, NTTSIZE / n, P);
  base_inv = expmod (base, P - 2, P);
  ntt_factor[0][0] = 1;
  ntt_factor[0][1] = 1;
  for (i = 1; i < n; i++)
    {
      ntt_factor[i][0] = multmod (ntt_factor[i - 1][0], base);
      ntt_factor[i][1] = multmod (ntt_factor[i - 1][1], base_inv);
    }

}


void
ntt1 (int n, int h, int pos, int index)
{

  long long int temp;
  if (h == 0)
    {
      return;
    }
  else
    {
      //recursion
      ntt1 (n, h / 2, pos, index);
      ntt1 (n, h / 2, pos + h, index);
    }
  int i, r;
  r = (n / 2) / h;		//Adjustment ratio with the original
  for (i = 0; i < h; i++)
    {
      temp =
	plusmod (ntty[pos + i],
		 multmod (ntt_factor[i * r][index], ntty[pos + h + i]));
      ntty[pos + h + i] =
	plusmod (ntty[pos + i],
		 multmod (ntt_factor[(i + h) * r][index], ntty[pos + h + i]));
      ntty[pos + i] = temp;
    }

}

void
ntt (int n)
{
  int i;
  for (i = 0; i < n; i++)
    {
      ntty[ntti[i]] = nttx[i];
    }
  ntt1 (n, n / 2, 0, 0);	// n,n/1,0=start-position of vector,0=base-index for forward

}


void
intt (int n)
{
  long long int n_inv;

  int i;
  for (i = 0; i < n; i++)
    {
      ntty[ntti[i]] = nttx[i];
    }
  ntt1 (n, n / 2, 0, 1);	// n,n/1,0=start-position of vector,1=base-index for inverse
  n_inv = expmod (n, P - 2, P);	// n_env is 1/n (mod P). inverse is 1/nΣ...
  for (i = 0; i < n; i++)
    {
      ntty[i] = (ntty[i] * n_inv) % P;
    }
}


//-------mult with NTT-------
int
bigx_ntt_mult (int x, int y)
{
  int pointer, lenx, leny, max_len, ans_len, i, n, half, res;

  lenx = get_length (x);
  leny = get_length (y);
  if (lenx >= leny)
    {
      max_len = lenx;
    }
  else
    {
      max_len = leny;
    }

  ans_len = lenx + leny + 1;
  if (ans_len * 2 * 3 > NTTSIZE)
    error (RESOURCE_ERR, "ntt-mult", makeint (ans_len));

  //prepare NTT data. datasize is twice of max_len
  //Each one bigcell needs 3 NTT data.  n= 2^x >= max_len*2*3
  n = 1;
  while ((max_len * 2 * 3) > n)
    {
      n = 2 * n;
    }
  ntt_set_bit_reverse (n);
  ntt_set_w_factor (n);

  //------ntt(x)-----
  for (i = 0; i < NTTSIZE; i++)
    {
      nttx[i] = 0;
    }

  pointer = get_pointer (x) - lenx + 1;	//LSB
  half = n / 2 - 1;

  for (i = 0; i < lenx; i++)
    {
      //one bigcell separate to three NTT data. NTTBASE is 1000
      nttx[half - (3 * i)] = bigcell[pointer + i] % NTTBASE;
      nttx[half - (3 * i + 1)] = (bigcell[pointer + i] / NTTBASE) % NTTBASE;
      nttx[half - (3 * i + 2)] = bigcell[pointer + i] / (NTTBASE * NTTBASE);
    }

  ntt (n);
  // save to nttz[]
  for (i = 0; i < n; i++)
    {
      nttz[i] = ntty[i];
    }


  //-----ntt(y)--------
  for (i = 0; i < NTTSIZE; i++)
    {
      nttx[i] = 0;
    }

  pointer = get_pointer (y) - leny + 1;	//LSB
  for (i = 0; i < leny; i++)
    {
      nttx[half - (3 * i)] = bigcell[pointer + i] % NTTBASE;
      nttx[half - (3 * i + 1)] = (bigcell[pointer + i] / NTTBASE) % NTTBASE;
      nttx[half - (3 * i + 2)] = bigcell[pointer + i] / (NTTBASE * NTTBASE);
    }

  ntt (n);

  //----mult---------
  for (i = 0; i < n; i++)
    {
      nttx[i] = multmod (ntty[i], nttz[i]);
    }

  //---inverse NTT---
  intt (n);

  //---generate-answer
  res = gen_big ();
  SET_TAG (res, BIGX);
  set_sign (res, get_sign (x) * get_sign (y));
  for (i = 0; i < ans_len; i++)
    {
      bigcell[big_pt0 + i] = 0;
    }

  // normalize
  int pool, carry;
  n = n - 2;
  carry = 0;
  for (i = 0; i < ans_len; i++)
    {
      pool = ((int) ntty[n - (3 * i)] + carry) % NTTBASE;
      carry = ((int) ntty[n - (3 * i)] + carry) / NTTBASE;
      pool =
	pool + (((int) ntty[n - (3 * i + 1)] + carry) % NTTBASE) * NTTBASE;
      carry = ((int) ntty[n - (3 * i + 1)] + carry) / NTTBASE;
      pool =
	pool +
	(((int) ntty[n - (3 * i + 2)] +
	  carry) % NTTBASE) * (NTTBASE * NTTBASE);
      carry = ((int) ntty[n - (3 * i + 2)] + carry) / NTTBASE;
      bigcell[big_pt0++] = pool;
    }

  //zero cut
  big_pt0--;
  while (bigcell[big_pt0] == 0 && ans_len > 0)
    {
      big_pt0--;
      ans_len--;
    }

  big_pt0++;
  set_pointer (res, big_pt0 - 1);
  set_length (res, ans_len);
  return (res);
}


//-----------simple test------------

void
ntt_test ()
{
  int n, i;

  n = 8;

  nttx[0] = 0;
  nttx[1] = 0;
  nttx[2] = 0;
  nttx[3] = 4;
  nttx[4] = 0;
  nttx[5] = 0;
  nttx[6] = 0;
  nttx[7] = 0;
  ntt_set_bit_reverse (n);
  ntt_set_w_factor (n);

  ntt (n);
  for (i = 0; i < n; i++)
    {
      nttz[i] = ntty[i];
    }

  nttx[0] = 0;
  nttx[1] = 0;
  nttx[2] = 0;
  nttx[3] = 5;
  nttx[4] = 0;
  nttx[5] = 0;
  nttx[6] = 0;
  nttx[7] = 0;

  ntt (n);

  for (i = 0; i < n; i++)
    {
      nttx[i] = multmod (nttz[i], ntty[i]);
    }


  intt (n);


  for (i = 0; i < n; i++)
    {
      printf ("%d\n", (int) ntty[i]);
    }


}


/* old code uses complex number
//----------------FFT multiply--------------------------
double complex fftx[FFTSIZE];	// FFT main input&output vector
double complex ffty[FFTSIZE];	// FFT sub vector1 for bit reverse
double complex fftz[FFTSIZE];	// FFT sub vector2 for bit reverse
int ffti[FFTSIZE];		// FFT index for bit_reverse

double complex
cexpt (double complex x, int y)
{
  double complex res, p;

  res = 1.0 + 0 * I;
  p = x;
  while (y > 0)
    {
      if ((y % 2) == 0)
	{
	  p = p * p;
	  y = y / 2;
	}
      else
	{
	  res = res * p;
	  y = y - 1;
	}
    }
  return (res);
}




double complex
w_factor (int n, int i)
{
  double complex z;

  z = cos (2.0 * M_PI / (double) n) - sin (2.0 * M_PI / (double) n) * I;
  return (cexpt (z, i));
}

// for inverse FFT
double complex
iw_factor (int n, int i)
{
  double complex z;

  z = cos (2.0 * M_PI / (double) n) + sin (2.0 * M_PI / (double) n) * I;
  return (cexpt (z, i));
}
*/

/*
void
set_bit_reverse (int n)
{
  int i, bit;

  bit = get_bit (n);
  for (i = 0; i < n; i++)
    {
      ffti[i] = bit_reverse (i, bit);
    }
}

void
fft1 (int n, int pos)
{
  double complex temp;

  if (n == 2)
    {
      temp = fftx[pos] + fftx[pos + 1];
      fftx[pos + 1] = fftx[pos] - fftx[pos + 1];
      fftx[pos] = temp;
    }
  else
    {
      int i, half;
      half = n / 2;
      for (i = 0; i < half; i++)
	{
	  temp = fftx[pos + i] + fftx[pos + half + i];
	  fftx[pos + half + i] =
	    w_factor (n, i) * (fftx[pos + i] - fftx[pos + half + i]);
	  fftx[pos + i] = temp;
	}
      //recursion
      fft1 (half, pos);
      fft1 (half, pos + half);
    }
}

void
fft (int n)
{

  fft1 (n, 0);

}

//inverse FFT
void
ifft1 (int n, int pos)
{
  double complex temp;

  if (n == 2)
    {
      temp = (fftx[pos] + fftx[pos + 1]) / 2;
      fftx[pos + 1] = (fftx[pos] - fftx[pos + 1]) / 2;
      fftx[pos] = temp;
    }
  else
    {
      int i, half;
      half = n / 2;
      for (i = 0; i < half; i++)
	{
	  temp = (fftx[pos + i] + fftx[pos + half + i]) / 2;
	  fftx[pos + half + i] =
	    (iw_factor (n, i) * (fftx[pos + i] - fftx[pos + half + i])) / 2;
	  fftx[pos + i] = temp;
	}
      //recursion
      ifft1 (half, pos);
      ifft1 (half, pos + half);
    }
}

void
ifft (int n)
{

  ifft1 (n, 0);

}


//-------mult with FFT-------
int
bigx_fft_mult (int x, int y)
{
  int pointer, lenx, leny, max_len, ans_len, i, n, res;

  lenx = get_length (x);
  leny = get_length (y);
  if (lenx >= leny)
    {
      max_len = lenx;
    }
  else
    {
      max_len = leny;
    }

  ans_len = lenx + leny + 1;
  if (ans_len * 2 * 3 > FFTSIZE)
    error (RESOURCE_ERR, "fft-mult", makeint (ans_len));

  n = 0;
  // FFTSIZE = 2^16 
  for (i = 16; i > 0; i--)
    {
      //prepare FFT data. datasize is twice of max_len
      //Each one bigcell needs 3 FFT data. 
      if ((max_len * 2 * 3) > pow (2, i))
	{
	  n = pow (2, i + 1);
	  break;
	}
    }
  set_bit_reverse (n);

  //------fft(x)-----
  for (i = 0; i < FFTSIZE; i++)
    {
      fftx[i] = 0;
    }

  pointer = get_pointer (x) - lenx + 1;	//LSB

  for (i = 0; i < lenx; i++)
    {
      //one bigcell separate to three FFT data.
      fftx[3 * i] = (double complex) (bigcell[pointer + i] % FFTBASE);
      fftx[3 * i + 1] =
	(double complex) ((bigcell[pointer + i] / FFTBASE) % FFTBASE);
      fftx[3 * i + 2] =
	(double complex) (bigcell[pointer + i] / (FFTBASE * FFTBASE));
    }

  fft (n);
  // change index of fftx with bit_reverse
  for (i = 0; i < n; i++)
    {
      ffty[ffti[i]] = fftx[i];
    }


  //-----fft(y)--------
  for (i = 0; i < FFTSIZE; i++)
    {
      fftx[i] = 0;
    }

  pointer = get_pointer (y) - leny + 1;	//LSB
  for (i = 0; i < leny; i++)
    {
      fftx[3 * i] = (double complex) (bigcell[pointer + i] % FFTBASE);
      fftx[3 * i + 1] =
	(double complex) ((bigcell[pointer + i] / FFTBASE) % FFTBASE);
      fftx[3 * i + 2] =
	(double complex) (bigcell[pointer + i] / (FFTBASE * FFTBASE));
    }

  fft (n);
  // change index of fftx with bit_reverse
  for (i = 0; i < n; i++)
    {
      fftz[ffti[i]] = fftx[i];
    }


  //----mult---------
  for (i = 0; i < n; i++)
    {
      fftx[i] = ffty[i] * fftz[i];
      //CPRINT(fftx[i]);
    }

  //---inverse FFT---
  ifft (n);
  //bit reverse
  for (i = 0; i < n; i++)
    {
      ffty[ffti[i]] = fftx[i];
    }


  //---generate-answer
  res = gen_big ();
  SET_TAG (res, BIGX);
  set_sign (res, get_sign (x) * get_sign (y));
  for (i = 0; i < ans_len; i++)
    {
      bigcell[big_pt0 + i] = 0;
    }

  // normalize
  int pool, carry;
  carry = 0;
  for (i = 0; i < ans_len; i++)
    {
      pool = (((int) round (creal (ffty[3 * i])) + carry) % FFTBASE);
      carry = ((int) round (creal (ffty[3 * i])) + carry) / FFTBASE;
      pool =
	pool +
	((((int) round (creal (ffty[3 * i + 1])) +
	   carry) % FFTBASE) * FFTBASE);
      carry = ((int) round (creal (ffty[3 * i + 1])) + carry) / FFTBASE;
      pool =
	pool +
	((((int) round (creal (ffty[3 * i + 2])) +
	   carry) % FFTBASE) * (FFTBASE * FFTBASE));
      carry = ((int) round (creal (ffty[3 * i + 2])) + carry) / FFTBASE;
      bigcell[big_pt0++] = pool;
    }

  //zero cut
  big_pt0--;
  while (bigcell[big_pt0] == 0 && ans_len > 0)
    {
      big_pt0--;
      ans_len--;
    }

  big_pt0++;
  set_pointer (res, big_pt0 - 1);
  set_length (res, ans_len);
  return (res);
}
*/
