//#define NEWBIG 

/* New bignum
* I am designing a new bignum data structure.
*  bigcell[BIGISZE]  array of 32bit integer.
*  big_pt0  pointer of temporaly bignum. 
*  big_pt1  pointer of parmanent bignum.
*  90% of bigcell is temporaly area and rest 10% is parmanent area.
*  in temporaly area rear 10% is working area for divide function.
*  bigcell = [[temporaly80%,temporalyworking10%],parmanent10%]
*  each bignum   elementn ... element1,element0
*  Car-part of the cell has the pointer of MSB.
*  Cdr-part of then cell has the length
*  
*/




/*
 * ported from Normal-Scheme data type BIGX two way list. to become easy
 * to access from LSB and MSB. car=int data of number cdr next pointer to
 * MSB prop prev pointer to LSB prop of MSB store NIL. opt has sign data.
 * plus=1,minus=-1,zero=0. number of data is absolute.
 * 
 * cells = lsb -> ... msb -> NIL aux = cbignum class information 
 */



#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "eisl.h"
#include "fmt.h"
#include "text.h"

#ifdef  NEWBIG

int get_length(int x){
	return(GET_CDR(x));
}

void set_length(int x, int y){
	SET_CDR(x,y);
}

int get_pointer(int x){
	return(GET_CAR(x));
}

void set_pointer(int x, int y){
	SET_CAR(x,y);
}

#endif


#ifdef NEWBIG
//new bignum
int
makebigx(char *bignum)
{
    char            integer[15];
    int             i,
                    j,
                    res,
                    sign,
                    len;

    // check sign
    if (bignum[0] == '-')
	sign = -1;
    else
	sign = 1;
    // remove sign
    if (bignum[0] == '-' || bignum[0] == '+') {
	i = laststr(bignum);
	for (j = 0; j < i; j++)
	    bignum[j] = bignum[j + 1];

	bignum[j] = NUL;
    }
    // length to check long data type
    len = 0;
    // generate bignum data cell
    res = gen_big();

    i = laststr(bignum);
    while (i >= 0) {
	if (i > 8) {
	    for (j = 8; j >= 0; j--) {
		integer[j] = bignum[i];
		i--;
	    }
	    integer[9] = NUL;
		bigcell[big_pt0++] = atoi(integer);
	    len++;
	} else {
	    integer[i + 1] = NUL;
	    while (i >= 0) {
		integer[i] = bignum[i];
		i--;
	    }
		bigcell[big_pt0++] = atoi(integer);
	    len++;
	}
    }

    if (len == 2) {
	long long int   l,
	                m;

	big_pt0 = big_pt0 - 2;
	l = (long long int) bigcell[big_pt0] * BIGNUM_BASE;
	m = (long long int) bigcell[big_pt0+1];
	m = (l + m) * sign;
	SET_TAG(res, LONGN);
	SET_LONG(res, m);
	SET_AUX(res, clongnum);
	return (res);
    } else {
	SET_TAG(res, BIGX);
	set_pointer(res, big_pt0-1);
	set_length(res, len);
	set_sign(res, sign);
	SET_AUX(res, cbignum);
	return (res);
    }
}

#else
//old bignum
int
makebigx(char *bignum)
{
    char            integer[15];
    int             i,
                    j,
                    res,
                    sign,
                    len,
                    msb;

    // check sign
    if (bignum[0] == '-')
	sign = -1;
    else
	sign = 1;
    // remove sign
    if (bignum[0] == '-' || bignum[0] == '+') {
	i = laststr(bignum);
	for (j = 0; j < i; j++)
	    bignum[j] = bignum[j + 1];

	bignum[j] = NUL;
    }
    // length to check long data type
    len = 0;
    // generate orijginal bignum data
    msb = res = gen_big();

    i = laststr(bignum);
    while (i >= 0) {
	if (i > 8) {
	    for (j = 8; j >= 0; j--) {
		integer[j] = bignum[i];
		i--;
	    }
	    integer[9] = NUL;
	    msb = cons_next(atoi(integer), msb);
	    len++;
	} else {
	    integer[i + 1] = NUL;
	    while (i >= 0) {
		integer[i] = bignum[i];
		i--;
	    }
	    msb = cons_next(atoi(integer), msb);
	    len++;
	}
    }

    if (len == 2) {
	long long int   l,
	                m;

	l = (long long int) GET_CAR(next(res)) * BIGNUM_BASE;
	m = (long long int) GET_CAR(res);
	m = (l + m) * sign;
	SET_TAG(res, LONGN);
	SET_LONG(res, m);
	SET_AUX(res, clongnum);
	return (res);
    } else {
	SET_TAG(res, BIGX);
	set_sign(res, sign);
	SET_AUX(res, cbignum);
	return (res);
    }
}

#endif 


#ifdef NEWBIG
//new bignum
void
print_bigx(int x)
{
    int             y,len;
    Text_save_T     save;
    Text_T          txt1 = { 0, NULL }, txt2;
    char            str[SHORT_STRSIZE];

    if (GET_OPT(output_stream) == EISL_OUTSTR) {
	save = Text_save();
    }

    if (get_sign(x) == -1) {
	if (GET_OPT(output_stream) != EISL_OUTSTR) {
	    fputc('-', GET_PORT(output_stream));
	} else {
	    txt1 = Text_put("-");
	}
    }
    y = get_pointer(x); //get pointer of bigcell
	len = get_length(x); //get length of bignum;
    if (GET_OPT(output_stream) != EISL_OUTSTR) {
	Fmt_fprint(GET_PORT(output_stream), "%d", bigcell[y]);
    } else {
	Fmt_sfmt(str, SHORT_STRSIZE, "%d", bigcell[y]);
	txt2 = Text_put(str);
	txt1 = Text_cat(txt1, txt2);
    }
    y--;
	len--;

    do {
	if (GET_OPT(output_stream) != EISL_OUTSTR) {
	    Fmt_fprint(GET_PORT(output_stream), "%09d", bigcell[y]);
	} else {
	    Fmt_sfmt(str, SHORT_STRSIZE, "%09d", bigcell[y]);
	    txt2 = Text_put(str);
	    txt1 = Text_cat(txt1, txt2);
	}
	y--;
	len--;
    } while (len > 0);

    if (GET_OPT(output_stream) == EISL_OUTSTR) {
	char           *out_str = GET_NAME(output_stream);
	size_t          l = strlen(out_str);
	Text_get(out_str + l, STRSIZE - l, txt1);
	Text_restore(&save);
    }
}
#else
//old bignum 
void
print_bigx(int x)
{
    int             y;
    Text_save_T     save;
    Text_T          txt1 = { 0, NULL }, txt2;
    char            str[SHORT_STRSIZE];

    if (GET_OPT(output_stream) == EISL_OUTSTR) {
	save = Text_save();
    }

    if (get_sign(x) == -1) {
	if (GET_OPT(output_stream) != EISL_OUTSTR) {
	    fputc('-', GET_PORT(output_stream));
	} else {
	    txt1 = Text_put("-");
	}
    }
    y = get_msb(x);
    if (GET_OPT(output_stream) != EISL_OUTSTR) {
	Fmt_fprint(GET_PORT(output_stream), "%d", GET_CAR(y));
    } else {
	Fmt_sfmt(str, SHORT_STRSIZE, "%d", GET_CAR(y));
	txt2 = Text_put(str);
	txt1 = Text_cat(txt1, txt2);
    }
    y = prev(y);

    do {
	if (GET_OPT(output_stream) != EISL_OUTSTR) {
	    Fmt_fprint(GET_PORT(output_stream), "%09d", GET_CAR(y));
	} else {
	    Fmt_sfmt(str, SHORT_STRSIZE, "%09d", GET_CAR(y));
	    txt2 = Text_put(str);
	    txt1 = Text_cat(txt1, txt2);
	}
	y = prev(y);
    } while (!nullp(y));

    if (GET_OPT(output_stream) == EISL_OUTSTR) {
	char           *out_str = GET_NAME(output_stream);
	size_t          l = strlen(out_str);
	Text_get(out_str + l, STRSIZE - l, txt1);
	Text_restore(&save);
    }
}
#endif

/*
 * x=new y=link if it is first cell, store the cell, else chain a new
 * cell. last msb cell, it's cdr is NIL 
 */
int
cons_next(int x, int y)
{
    int             res;

    if (GET_PROP(y) == -1) {
	SET_PROP(y, NIL);
	SET_CAR(y, x);
	res = y;
    } else {
	res = freshcell();
	SET_CAR(res, x);
	SET_CDR(y, res);
	SET_PROP(res, y);
	SET_CDR(res, NIL);
    }
    return (res);
}

// x=link y=new
int
cons_prev(int x, int y)
{
    int             res;

    if (GET_AUX(x) == -1) {
	SET_PROP(x, NIL);
	SET_CAR(x, y);
	res = x;
    } else {
	res = freshcell();
	SET_CAR(res, y);
	SET_CDR(res, x);
	SET_PROP(x, res);
	SET_PROP(res, NIL);
    }
    return (res);
}

/*
 * To check first cell, prop=-1. therefor when compute bignum, if it is
 * first cell, store data the cell. or else chain cell with cons_next.
 * 
 */
int
gen_big(void)
{
    int             res;

    res = freshcell();
    SET_CDR(res, NIL);
    SET_PROP(res, -1);
    return (res);
}

// get address of upper digit
int
next(int x)
{
    return (GET_CDR(x));
}

// get address of lower digit
int
prev(int x)
{
    return (GET_PROP(x));
}

// set sign
void
set_sign(int x, int y)
{
    SET_OPT(x, y);
}

// get sign
int
get_sign(int x)
{
    return (GET_OPT(x));
}

int
bigx_positivep(int x)
{
    if (get_sign(x) == 1)
	return (1);
    else
	return (0);
}

int
bigx_negativep(int x)
{
    if (get_sign(x) == -1)
	return (1);
    else
	return (0);
}

/*
 * count number of bignum cell. if value is zero, count is zero. It is
 * reason for matching to division
 * 
 */
int
bigx_length(int x)
{
    int             len,
                    y;

    len = 0;
    y = x;
    do {
	len++;
	y = next(y);
    } while (!nullp(y));
    if (len == 1 && GET_CAR(x) == 0)
	return (0);
    else
	return (len);
}

// get address of MSB
int
get_msb(int x)
{
    while (!nullp(next(x)))
	x = next(x);

    return (x);
}

// garbage collection of unnecessary bignum cell.
void
bigx_gbc(int x)
{
    int             addr;

    addr = x;
    do {
	int             addr1;

	addr1 = next(addr);
	clrcell(addr);
	fc++;
	SET_CDR(addr, hp);
	hp = addr;
	addr = addr1;
    } while (!nullp(addr));
}


#ifdef NEWBIG
//new bignum
int
bigx_eqp(int x, int y)
{
	int len,pointerx,pointery;

	if(get_sign(x) != get_sign(y))
		return(0);
	else if(get_length(x) != get_length(y))
		return(0);

	len = get_length(x);
	pointerx = get_pointer(x);
	pointery = get_pointer(y);
    do {
	if (pointerx != pointery)
	    return (0);

	x--;
	y--;
	len--;
    } while (len > 0);
    if (nullp(x) && nullp(y))
	return (1);
    else
	return (0);
}
#else
//old bignum
int
bigx_eqp(int x, int y)
{
    do {
	if (GET_CAR(x) != GET_CAR(y))
	    return (0);

	x = next(x);
	y = next(y);
    } while (!nullp(x) && !nullp(y));
    if (nullp(x) && nullp(y))
	return (1);
    else
	return (0);
}
#endif

#ifdef NEWBIG
//new bignum
int
bigx_abs_smallerp(int x, int y)
{
    int             len1,
                    len2,
                    pointerx,
                    pointery;

    len1 = get_length(x);
    len2 = get_length(y);

    if (len1 < len2)
	return (1);
    else if (len1 > len2)
	return (0);
    else {
	pointerx = get_pointer(x);
	pointery = get_pointer(y);
	do {
	    if (bigcell[pointerx] < bigcell[pointery])
		return (1);
	    if (bigcell[pointerx] > bigcell[pointery])
		return (0);

	    pointerx--;
	    pointery--;
		len1--;
	} while (len1 > 0);
	return (0);
    }

}
#else
//old bignum
int
bigx_abs_smallerp(int arg1, int arg2)
{
    int             l1,
                    l2,
                    a1,
                    a2;

    l1 = bigx_length(arg1);
    l2 = bigx_length(arg2);


    if (l1 < l2)
	return (1);
    else if (l1 > l2)
	return (0);
    else {
	a1 = get_msb(arg1);
	a2 = get_msb(arg2);
	do {
	    if (GET_CAR(a1) < GET_CAR(a2))
		return (1);
	    if (GET_CAR(a1) > GET_CAR(a2))
		return (0);

	    a1 = prev(a1);
	    a2 = prev(a2);
	} while (!nullp(a1));
	return (0);
    }

}
#endif

#ifdef NEWBIG
//new bignum
int
bigx_smallerp(int x, int y)
{
    
    if (bigx_positivep(x) && bigx_negativep(x))
	return (0);
    else if (bigx_negativep(x) && bigx_positivep(y))
	return (1);
	else if (bigx_positivep(x) && bigx_positivep(y)) 
		return(bigx_abs_smallerp(x,y));
	else if (bigx_negativep(x) && bigx_negativep(y))
		return(bigx_abs_smallerp(y,x));
	else 
	return (0);

    return (0);
}

#else
//old bignum
int
bigx_smallerp(int arg1, int arg2)
{
    int             l1,
                    l2,
                    a1,
                    a2;

    if (bigx_positivep(arg1) && bigx_negativep(arg2))
	return (0);
    if (bigx_negativep(arg1) && bigx_positivep(arg2))
	return (1);

    l1 = bigx_length(arg1);
    l2 = bigx_length(arg2);

    if (l1 == l2 && bigx_positivep(arg1) && bigx_positivep(arg2)) {
	a1 = get_msb(arg1);
	a2 = get_msb(arg2);
	do {
	    if (GET_CAR(a1) < GET_CAR(a2)) {
		return (1);
	    }
	    if (GET_CAR(a1) > GET_CAR(a2)) {
		return (0);
	    }
	    a1 = prev(a1);
	    a2 = prev(a2);
	} while (!nullp(a1));
	return (0);
    } else if (l1 == l2 && bigx_negativep(arg1) && bigx_negativep(arg2)) {
	a1 = get_msb(arg1);
	a2 = get_msb(arg2);
	do {
	    if (GET_CAR(a1) > GET_CAR(a2))
		return (1);
	    if (GET_CAR(a1) < GET_CAR(a2))
		return (0);

	    a1 = prev(a1);
	    a2 = prev(a2);
	} while (!nullp(a1));
	return (0);
    }
    if (bigx_positivep(arg1) && bigx_positivep(arg2)) {
	if (l1 > l2)
	    return (0);
	else if (l1 < l2)
	    return (1);
    } else if (bigx_negativep(arg1) && bigx_negativep(arg2)) {
	if (l1 < l2)
	    return (0);
	else if (l1 > l2)
	    return (1);
    }


    return (0);
}

#endif


// find nth cell address
int
get_nth(int x, int n)
{
    int             m,
                    msb;


    m = 1;
    msb = x;
    while (m <= n) {
	msb = next(msb);
	m++;
    }
    return (msb);
}


// generate bignum data of n-cells
int
gen_n(int n)
{
    int             i,
                    msb,
                    res;

    msb = res = gen_big();
    SET_TAG(res, BIGX);
    SET_CAR(res, 0);
    SET_PROP(res, NIL);
    for (i = 1; i < n; i++)
	msb = cons_next(0, msb);

    return (res);
}


/*
 * cut of head zero cell. at least keep one cell, because possibility of
 * all-zero.
 * 
 */
void
cut_zero(int x)
{
    int             msb,
                    dig;

    dig = bigx_length(x);
    msb = get_msb(x);
    while (GET_CAR(msb) == 0 && dig > 1) {
	msb = prev(msb);
	dig--;
    }
    SET_CDR(msb, NIL);
}

#ifdef NEWBIG
//new bignum
int
bigx_int_to_big(int x)
{
    int             res,
                    y;

    y = GET_INT(x);
	bigcell[big_pt0++] = y;
    res = gen_big();
    SET_TAG(res, BIGX);
	set_pointer(res,big_pt0-1);
	set_length(res,1);
    if (y >= 0)
	set_sign(res, 1);
    else
	set_sign(res, -1);
    return (res);
}

#else
//old bignum
int
bigx_int_to_big(int x)
{
    int             res,
                    y;

    y = GET_INT(x);
    res = gen_big();
    SET_TAG(res, BIGX);
    cons_next(abs(y), res);
    if (y >= 0)
	set_sign(res, 1);
    else
	set_sign(res, -1);
    return (res);
}

#endif

#ifdef NEWBIG
//new bignum
int
bigx_long_to_big(int x)
{
    int             res,
                    i2,
                    i1;
    long long int   l;

    l = GET_LONG(x);
    i2 = llabs(l) % BIGNUM_BASE;
    i1 = llabs(l) / BIGNUM_BASE;
	bigcell[big_pt0++] = i1;
	bigcell[big_pt0++] = i2;
    res = gen_big();
    SET_TAG(res, BIGX);
	set_pointer(res,big_pt0-1);
    if (l >= 0){
	set_sign(res, 1);}
    else{
	set_sign(res, -1);}
	set_length(res,2);
    return (res);
}

#else
//old bignum
int
bigx_long_to_big(int x)
{
    int             res,
                    i2,
                    i1;
    long long int   l;

    l = GET_LONG(x);
    i2 = llabs(l) % BIGNUM_BASE;
    i1 = llabs(l) / BIGNUM_BASE;
    res = gen_big();
    SET_TAG(res, BIGX);
    if (l >= 0)
	set_sign(res, 1);
    else
	set_sign(res, -1);
    cons_next(i1, cons_next(i2, res));
    return (res);
}

#endif


#ifdef NEWBIG
//new bignum
int
bigx_simplify(int x)
{
    int             i1;
    long long int   l,
                    l1,
                    l2;

    if (get_length(x) == 0) {
	return (makeint(0));
    } else if (get_length(x) == 1) {
	i1 = bigcell[get_pointer(x)];
	i1 = i1 * get_sign(x);
	return (makeint(i1));
    } else if (get_length(x) == 2) {
	l1 = bigcell[get_pointer(x)];
	l2 = bigcell[get_pointer(x)+1];
	l = (l1 * BIGNUM_BASE + l2) * get_sign(x);
	return (makelong(l));
    } else
	return (x);
}

#else
//old bignum
int
bigx_simplify(int x)
{
    int             i1;
    long long int   l,
                    l1,
                    l2;

    if (bigx_length(x) == 0) {
	return (makeint(0));
    } else if (bigx_length(x) == 1) {
	i1 = GET_CAR(x);
	i1 = i1 * get_sign(x);
	bigx_gbc(x);
	return (makeint(i1));
    } else if (bigx_length(x) == 2) {
	l2 = GET_CAR(x);
	l1 = GET_CAR(next(x));
	l = (l1 * BIGNUM_BASE + l2) * get_sign(x);
	bigx_gbc(x);
	return (makelong(l));
    } else
	return (x);

}

#endif

#ifdef NEWBIG
// new bignum
// add n-zero-cells to x
int
bigx_shift(int x, int n)
{
    int             res,
                    len,pointer;

	len = get_length(x);
	pointer = get_pointer(x)-len+1; // LSB
    res = gen_big();
    SET_TAG(res, BIGX);
    set_sign(res, get_sign(x));

	int i;
	for(i=0;i<n;i++){
		bigcell[big_pt0++] = 0;
	}
    for(i=0;i<len;i++){
		bigcell[big_pt0++] = bigcell[pointer+i];
	}

    set_pointer(res,big_pt0-1);
	set_length(res,len+n);
    return (res);
}
#else
// oldbignum
// add n-zero-cells to x
int
bigx_shift(int x, int n)
{
    int             res,
                    msb;

    msb = res = gen_big();
    SET_TAG(res, BIGX);
    set_sign(res, get_sign(x));

    while (n > 0) {
	msb = cons_next(0, msb);
	n--;
    }
    do {
	msb = cons_next(GET_CAR(x), msb);
	x = next(x);
    } while (!nullp(x));
    return (res);
}
#endif

#ifdef NEWBIG
//new bignum
int
bigx_abs(int x)
{
    int             res;

    res = gen_big();
    SET_TAG(res, BIGX);
    set_sign(res, 1);
	set_pointer(res,get_pointer(x));
	set_length(res,get_length(x));
    return (res);
}
#else
//old bignum
int
bigx_abs(int x)
{
    int             res,
                    msb;

    msb = res = gen_big();
    SET_TAG(res, BIGX);
    set_sign(res, 1);
    do {
	int             y;

	y = GET_CAR(x);
	msb = cons_next(y, msb);
	x = next(x);
    } while (!nullp(x));

    return (res);
}
#endif

int
bigx_plus(int arg1, int arg2)
{
    int             res;

    res = UNDEF;
    if (bigx_positivep(arg1) && bigx_positivep(arg2)) {
	res = bigx_plus1(arg1, arg2);
	set_sign(res, 1);
    } else if (bigx_negativep(arg1) && bigx_negativep(arg2)) {
	res = bigx_plus1(arg1, arg2);
	set_sign(res, -1);
    } else if (bigx_positivep(arg1) && bigx_negativep(arg2)) {
	if (bigx_abs_smallerp(arg1, arg2)) {
	    res = bigx_minus1(arg2, arg1);
	    set_sign(res, -1);
	} else {
	    res = bigx_minus1(arg1, arg2);
	    set_sign(res, 1);
	}
    } else if (bigx_negativep(arg1) && bigx_positivep(arg2)) {
	if (bigx_abs_smallerp(arg1, arg2)) {
	    res = bigx_minus1(arg2, arg1);
	    set_sign(res, 1);
	} else {
	    res = bigx_minus1(arg1, arg2);
	    set_sign(res, -1);
	}
    }

    if (simp_flag)
	res = bigx_simplify(res);

    return (res);
}

#ifdef NEWBIG
//new bignum
int
bigx_plus1(int arg1, int arg2)
{
    int             len1,len2,pointerx,pointery,
					c,len,
                    res;

	len1 = get_length(arg1);
	len2 = get_length(arg2);
	pointerx = get_pointer(arg1)-len1+1; //LSB
	pointery = get_pointer(arg2)-len2+1; //LSB
    res = gen_big();
    SET_TAG(res, BIGX);
    set_sign(res, 1);
    c = 0;
	len = 0;
    do {
	int             x,
	                y,
	                z,
	                q;

	if(len1 > 0)
		x = bigcell[pointerx];
	else
		x = 0;
	
	if(len2 > 0)
		y = bigcell[pointery];
	else
		y = 0;

	z = x + y + c;
	c = z / BIGNUM_BASE;
	q = z % BIGNUM_BASE;
	bigcell[big_pt0++] = q;
	pointerx++;
	pointery++;
	len1--;
	len2--;
	len++;
    } while (len1 > 0 || len2 > 0);
    if (c != 0)
		bigcell[big_pt0++] = c;
	
	set_pointer(res,big_pt0-1);
	set_length(res,len);
    return (res);
}

#else
//old bignum
int
bigx_plus1(int arg1, int arg2)
{
    int             c,
                    res,
                    msb;

    msb = res = gen_big();
    SET_TAG(res, BIGX);
    set_sign(res, 1);
    c = 0;
    do {
	int             x,
	                y,
	                z,
	                q;

	x = GET_CAR(arg1);
	y = GET_CAR(arg2);
	z = x + y + c;
	c = z / BIGNUM_BASE;
	q = z % BIGNUM_BASE;
	msb = cons_next(q, msb);
	arg1 = next(arg1);
	arg2 = next(arg2);
    } while (!nullp(arg1) && !nullp(arg2));
    if (nullp(arg1))
	bigx_plus2(arg2, c, msb);
    else
	bigx_plus2(arg1, c, msb);
    cut_zero(res);
    return (res);
}
#endif

void
bigx_plus2(int arg, int c, int msb)
{
    do {
	int             q;
	long long int   l;

	l = GET_CAR(arg) + c;
	c = l / BIGNUM_BASE;
	q = l % BIGNUM_BASE;
	msb = cons_next(q, msb);
	arg = next(arg);
    } while (!nullp(arg));
    if (c != 0)
	(void) cons_next(c, msb);
}

int
bigx_minus(int arg1, int arg2)
{
    int             res;

    res = UNDEF;
    if (bigx_positivep(arg1) && bigx_positivep(arg2)) {
	if (bigx_smallerp(arg1, arg2)) {
	    res = bigx_minus1(arg2, arg1);
	    set_sign(res, -1);
	} else {
	    res = bigx_minus1(arg1, arg2);
	    set_sign(res, 1);
	}
    } else if (bigx_positivep(arg1) && bigx_negativep(arg2)) {
	res = bigx_plus1(arg1, arg2);
	set_sign(res, 1);
    } else if (bigx_negativep(arg1) && bigx_positivep(arg2)) {
	res = bigx_plus1(arg1, arg2);
	set_sign(res, -1);
    } else if (bigx_negativep(arg1) && bigx_negativep(arg2)) {
	if (bigx_abs_smallerp(arg1, arg2)) {
	    res = bigx_minus1(arg2, arg1);
	    set_sign(res, 1);
	} else {
	    res = bigx_minus1(arg1, arg2);
	    set_sign(res, -1);
	}
    }
    if (simp_flag)
	res = bigx_simplify(res);

    return (res);
}

#ifdef NEWBIG
// new bignum
// arg1 > arg2
int
bigx_minus1(int arg1, int arg2)
{
    int             len1,len2,pointerx,pointery,len,
	                z,
                    c,
                    res;

	len1 = get_length(arg1);
	len2 = get_length(arg2);
	pointerx = get_pointer(arg1)-len1+1; // LSB
	pointery = get_pointer(arg2)-len2+1; // LSB
    res = gen_big();
    SET_TAG(res, BIGX);
    set_sign(res, 1);
    c = 0;
	len = 0;
    do {
	int             x,
	                y;

	if(len1 > 0)
		x = bigcell[pointerx];
	else 
		x = 0;

	if(len2 > 0)
		y = bigcell[pointery];
	else 
		y = 0;


	if ((x + c - y) < 0) {
	    z = (x + BIGNUM_BASE + c) - y;
	    c = -1;
	} else {
	    z = (x + c) - y;
	    c = 0;
	}
	bigcell[big_pt0++] = z;
	pointerx++;
	pointery++;
	len1--;
	len2--;
	len++;
    } while (len1 > 0 || len2 > 0);

    set_pointer(res,big_pt0-1);
	set_length(res,len);
    return (res);
}

#else
// old bignum
// arg1 > arg2
int
bigx_minus1(int arg1, int arg2)
{
    int             z,
                    c,
                    res,
                    msb;

    msb = res = gen_big();
    SET_TAG(res, BIGX);
    set_sign(res, 1);
    c = 0;
    do {
	int             x,
	                y;

	x = GET_CAR(arg1);
	y = GET_CAR(arg2);
	if ((x + c - y) < 0) {
	    z = (x + BIGNUM_BASE + c) - y;
	    c = -1;
	} else {
	    z = (x + c) - y;
	    c = 0;
	}

	msb = cons_next(z, msb);
	arg1 = next(arg1);
	arg2 = next(arg2);
    } while (!nullp(arg2));

    if (!nullp(arg1))
	bigx_minus2(arg1, c, msb);

    cut_zero(res);
    return (res);
}

#endif


void
bigx_minus2(int arg, int c, int msb)
{
    int             q;

    while (!nullp(arg)) {
	int             x;

	x = GET_CAR(arg);
	if (x + c < 0) {
	    q = x + BIGNUM_BASE + c;
	    c = -1;
	} else {
	    q = x + c;
	    c = 0;
	}
	msb = cons_next(q, msb);
	arg = next(arg);
    }
}


int
bigx_mult(int arg1, int arg2)
{
    int             res;

    res = UNDEF;
    if (bigx_positivep(arg1) && bigx_positivep(arg2)) {
	res = bigx_mult1(arg1, arg2);
	set_sign(res, 1);
    } else if (bigx_positivep(arg1) && bigx_negativep(arg2)) {
	res = bigx_mult1(arg1, arg2);
	set_sign(res, -1);
    } else if (bigx_negativep(arg1) && bigx_positivep(arg2)) {
	res = bigx_mult1(arg1, arg2);
	set_sign(res, -1);
    } else if (bigx_negativep(arg1) && bigx_negativep(arg2)) {
	res = bigx_mult1(arg1, arg2);
	set_sign(res, 1);
    }
    if (simp_flag){
	res = bigx_simplify(res);}

    return (res);
}

#ifdef NEWBIG
//new bignum
int
bigx_mult1(int arg1, int arg2)
{
    int             res,len1,len2,pointerx,pointery,len;
    long long int   x,
                    y,
                    z,
                    l1,
                    l2,
                    c;
	res = gen_big();
	SET_TAG(res,BIGX);
	len1 = get_length(arg1);
	len2 = get_length(arg2);
    len = len1+len2;
    set_sign(res, 1);
	printf("asdf%d %d ", len1, len2);
	return(makeint(3));

	// clear area of calculate
	int i,j;
	for(i=0;i<len;i++)
		bigcell[i+big_pt0] = 0;

    pointery = get_pointer(arg2)-len2+1; //LSB
	for(j=0;j<len2;j++){
		pointerx = get_pointer(arg1)-len1+1; //LSB
		for(i=0;i<len1;i++){
			x = (long long int) bigcell[pointerx+i];
	    	y = (long long int) bigcell[pointery+j];
	    	z = x * y;
	    	l2 = z % BIGNUM_BASE;
	    	l1 = z / BIGNUM_BASE;
	    	l2 = l2 + (long long int) bigcell[big_pt0+j+i];
	    	if (l2 >= BIGNUM_BASE) {
			c = l2 / BIGNUM_BASE;
			l2 = l2 % BIGNUM_BASE;
	    	} else {
			c = 0;
	    	}
	    	l1 = l1 + c + (long long int) bigcell[big_pt0+j+i+1];
			bigcell[big_pt0+j+i] = (int)l2;
	    	bigcell[big_pt0+j+i+1] = (int)l1;
		}
	}
	
	big_pt0 = big_pt0 + len;
	while(bigcell[big_pt0] == 0){
		big_pt0--;
		len--;
	}
	big_pt0++;
	set_pointer(res,big_pt0-1);
	set_length(res,len+1);
    return (res);
}
#else
//old bignum
int
bigx_mult1(int arg1, int arg2)
{
    int             res,
                    dig2,
                    n;
    long long int   x,
                    y,
                    z,
                    l1,
                    l2,
                    c;

    res = gen_n(bigx_length(arg1) + bigx_length(arg2));
    set_sign(res, 1);
    dig2 = arg2;
    n = 0;
    do {
	int             dig1,
	                msb;

	dig1 = arg1;
	msb = get_nth(res, n);
	do {
	    x = (long long int) GET_CAR(dig1);
	    y = (long long int) GET_CAR(dig2);
	    z = x * y;
	    l2 = z % BIGNUM_BASE;
	    l1 = z / BIGNUM_BASE;
	    l2 = l2 + (long long int) GET_CAR(msb);
	    if (l2 >= BIGNUM_BASE) {
		c = l2 / BIGNUM_BASE;
		l2 = l2 % BIGNUM_BASE;
	    } else {
		c = 0;
	    }
	    l1 = l1 + c + (long long int) GET_CAR(next(msb));
	    SET_CAR(msb, (int) l2);
	    SET_CAR(next(msb), (int) l1);
	    dig1 = next(dig1);
	    msb = next(msb);
	} while (!nullp(dig1));
	dig2 = next(dig2);
	n++;
    } while (!nullp(dig2));
    cut_zero(res);
    return (res);
}

#endif

#ifdef NEWBIG
// new bignum
int bigx_div(int arg1, int arg2)
{
    int             res,
                    x,
                    y;

    res = UNDEF;
    // if devidend is smaller than divisor,return 0
    if (bigx_abs_smallerp(arg1, arg2))
	return (makeint(0));

    if (bigx_positivep(arg1) && bigx_positivep(arg2)) {
	res = bigx_div1(arg1, arg2);
    } else if (bigx_positivep(arg1) && bigx_negativep(arg2)) {
	y = bigx_abs(arg2);
	res = bigx_div1(arg1, y);
	set_sign(res, -1);
    } else if (bigx_negativep(arg1) && bigx_positivep(arg2)) {
	x = bigx_abs(arg1);
	res = bigx_div1(x, arg2);
	set_sign(res, -1);
    } else if (bigx_negativep(arg1) && bigx_negativep(arg2)) {
	x = bigx_abs(arg1);
	y = bigx_abs(arg2);
	res = bigx_div1(x, y);
	set_sign(res, 1);
    }

    if (simp_flag)
	res = bigx_simplify(res);
    return (res);
}
#else
int
bigx_div(int arg1, int arg2)
{
    int             res,
                    x,
                    y;

    res = UNDEF;
    // if devidend is smaller than divisor,return 0
    if (bigx_abs_smallerp(arg1, arg2))
	return (makeint(0));

    if (bigx_positivep(arg1) && bigx_positivep(arg2)) {
	res = bigx_div1(arg1, arg2);
    } else if (bigx_positivep(arg1) && bigx_negativep(arg2)) {
	y = bigx_abs(arg2);
	res = bigx_div1(arg1, y);
	set_sign(res, -1);
	bigx_gbc(y);
    } else if (bigx_negativep(arg1) && bigx_positivep(arg2)) {
	x = bigx_abs(arg1);
	res = bigx_div1(x, arg2);
	set_sign(res, -1);
	bigx_gbc(x);
    } else if (bigx_negativep(arg1) && bigx_negativep(arg2)) {
	x = bigx_abs(arg1);
	y = bigx_abs(arg2);
	res = bigx_div1(x, y);
	set_sign(res, 1);
	bigx_gbc(x);
	bigx_gbc(y);
    }

    if (simp_flag)
	res = bigx_simplify(res);
    return (res);
}
#endif

/*
 * Knuth TAOCP fourth. see p88 s=sift is for match digits, ds is divisor,
 * p=plus adding again, bv= if u/v > BIGNUM_BASE, cell of MSB. 
 */

// #define TEST
#ifdef NEWBIG
//new bignum
int
bigx_div1(int arg1, int arg2)
{
    int             s,
                    ss,
                    res,len,
					pointerx,pointery,pointer,save0,save1,
                    i;
    long long int   u,
                    v,
                    l1,
                    l2;

	

    ss = 0;
    // devidend is smaller than 2 times divisor, return 1
    // if quotient is 1, theorem is not hold
    s = bigx_mult1(arg2, bigx_int_to_big(makeint(2)));
    if (bigx_abs_smallerp(arg1, s))
	return (makeint(1));

	
    // following code, calcuration is required in bignum
    // so, stop simplification.
    simp_flag = false;


    res = gen_big();
	SET_TAG(res, BIGX);
    set_sign(res, 1);
	len = get_length(arg1);
	big_pt0 = big_pt0 + len;  // prepare area of answer. 
	set_pointer(res,big_pt0);
	pointerx = get_pointer(arg1); // MSB
	pointery = get_pointer(arg2); //MSB
	save0 = big_pt0;
	big_pt0 = BIGNUM_WORK; // chainge to working area
    // if divisor is smaller, become bigger to hold theolem
    v = (long long int) bigcell[pointery];
    if (v < (BIGNUM_BASE / 2)) {
	long long int   d = BIGNUM_BASE / (v + 1);
	arg1 = bigx_mult1(arg1, bigx_long_to_big(makelong(d)));
	arg2 = bigx_mult1(arg2, bigx_long_to_big(makelong(d)));
    }

    do {
	int             dig1 = get_length(arg1);
	int             dig2 = get_length(arg2);
	if (dig1 > dig2) {
	    l1 = (long long int) bigcell[pointerx];
	    l2 = (long long int) bigcell[pointerx-1];
	    u = l1 * BIGNUM_BASE + l2;
	    v = (long long int) bigcell[pointery];
	} else {
	    u = (long long int) bigcell[pointerx];
	    v = (long long int) bigcell[pointery];
	}
	
	long long int   q = u / v;
	if (q == 1 && dig1 != dig2)
	    q = 10;
	int             ds =
	    bigx_mult1(arg2, bigx_long_to_big(makelong(q)));

	return(makeint(3));
	s = get_length(arg1) - get_length(ds);
	ds = bigx_shift(ds, s);
	int             p = bigx_shift(arg2, s);

	int             t = bigx_minus(arg1, ds);

	arg1 = t;

	print(arg1);
		
		printf("asdf%d %d" , s, ss);
	while (bigx_negativep(arg1)) {
	
	    t = bigx_plus(arg1, p);
	    arg1 = t;
	    q--;
	}
	
	

	save1 = big_pt0;  //save working area pointer
	big_pt0 = save0;  //restore temporarly area pointer
	if ((ss - s) > 1) {
	    i = ss - s;
	    while (i > 1) {
		bigcell[big_pt0--] = 0;
		i--;
	    }
	}
	
	// if q is bigger than BIGNUM_BASE, number span two cells.
	if (q < BIGNUM_BASE) {
		bigcell[big_pt0--] = (int)q;
	} else {
	    l2 = q % BIGNUM_BASE;
	    l1 = q / BIGNUM_BASE;
		bigcell[big_pt0--] = (int)l1;
		bigcell[big_pt0--] = (int)l2;
	}
	ss = s; // s means shift number

	save0 = big_pt0; //save temporarly area pointer
	big_pt0 = save1; //chainge to working area


    } while (!bigx_abs_smallerp(arg1, arg2));

	big_pt0 = save0; //restore temporarly area
	// shift s th
	for(i=0;i<s;i++){
		bigcell[big_pt0--] = 0;
	}
    

    // restore flag
    simp_flag = true;

	//cut zero
	pointer = get_pointer(res);
	while(bigcell[pointer] == 0){
		pointer--;
		len--;
	}
	big_pt0 = pointer + 1;
	set_pointer(res,pointer);
	set_length(res,len);
    return (res);
}
#else 
// old bignum
int
bigx_div1(int arg1, int arg2)
{
    int             s,
                    ss,
                    res,
                    flag1,
                    flag2,
                    i;
    long long int   u,
                    v,
                    l1,
                    l2;
#ifdef TEST
    int             c;
    c = 10;
#endif

    flag1 = 0;
    flag2 = 0;
    ss = 0;
    // devidend is smaller than 2 times divisor, return 1
    // if quotient is 1, theorem is not hold
    s = bigx_mult1(arg2, bigx_int_to_big(makeint(2)));
    if (bigx_abs_smallerp(arg1, s))
	return (makeint(1));

    // following code, calcuration is required in bignum
    // so, stop simlification.
    simp_flag = false;

    res = gen_big();
    // if divisor is smaller, become bigger to hold theolem
    v = (long long int) GET_CAR(get_msb(arg2));
    if (v < (BIGNUM_BASE / 2)) {
	long long int   d = BIGNUM_BASE / (v + 1);
	arg1 = bigx_mult1(arg1, bigx_long_to_big(makelong(d)));
	arg2 = bigx_mult1(arg2, bigx_long_to_big(makelong(d)));
	flag1 = 1;
	flag2 = 1;
    }
#ifdef TEST
    fputs("arg1=", stdout);
    print(arg1);
    putchar('\n');
    fputs("arg2=", stdout);
    print(arg2);
    putchar('\n');
#endif

    do {
	int             dig1 = bigx_length(arg1);
	int             dig2 = bigx_length(arg2);
	if (dig1 > dig2) {
	    l1 = (long long int) GET_CAR(get_msb(arg1));
	    l2 = (long long int) GET_CAR(prev(get_msb(arg1)));
	    u = l1 * BIGNUM_BASE + l2;
	    v = (long long int) GET_CAR(get_msb(arg2));
	} else {
	    u = (long long int) GET_CAR(get_msb(arg1));
	    v = (long long int) GET_CAR(get_msb(arg2));
	}

	long long int   q = u / v;
	if (q == 1 && dig1 != dig2)
	    q = 10;
	int             ds =
	    bigx_mult1(arg2, bigx_long_to_big(makelong(q)));


	s = bigx_length(arg1) - bigx_length(ds);
	ds = bigx_shift(ds, s);
	int             p = bigx_shift(arg2, s);
#ifdef TEST
	printf("q= %I64d (u=%I64d/ v=%I64d)\n", q, u, v);
	fputs("ds=", stdout);
	print(ds);
	putchar('\n');
	fputs("p=", stdout);
	print(p);
	putchar('\n');
	printf("s=%d\n", s);
#endif
	int             t = bigx_minus(arg1, ds);
	if (flag1)
	    bigx_gbc(arg1);	// garbage collection
	arg1 = t;
	flag1 = 1;



	while (bigx_negativep(arg1)) {
	    t = bigx_plus(arg1, p);
	    bigx_gbc(arg1);	// garbage collection
	    arg1 = t;
	    q--;
	}
#ifdef TEST
	fputs("after arg1=", stdout);
	print(arg1);
	putchar('\n');
#endif

	bigx_gbc(ds);		// garbage collection
	bigx_gbc(p);

	if ((ss - s) > 1) {
	    i = ss - s;
	    while (i > 1) {
		res = cons_prev(res, 0);
		i--;
	    }
	}
	// if q is bigger than BIGNUM_BASE, number span two cells.
	if (q < BIGNUM_BASE) {
	    res = cons_prev(res, (int) q);
	} else {
	    l2 = q % BIGNUM_BASE;
	    l1 = q / BIGNUM_BASE;
	    res = cons_prev(cons_prev(res, (int) l1), (int) l2);
	}
	ss = s;
#ifdef TEST
	c--;
	if (c == 0) {
	    DEBUG();
	}
#endif
    } while (!bigx_abs_smallerp(arg1, arg2));

    res = bigx_shift(res, s);

    if (flag2)
	bigx_gbc(arg2);

    // restore flag
    simp_flag = true;
    SET_TAG(res, BIGX);
    set_sign(res, 1);
    cut_zero(res);
    return (res);
}
#endif


int
bigx_big_to_flt(int x)
{
    double          val;
    int             msb,
                    res;

    res = freshcell();
    val = 0.0;
    msb = get_msb(x);
    do {
	int             i;

	i = GET_CAR(msb);
	val = val * (double) BIGNUM_BASE + (double) i;
	msb = prev(msb);
    } while (!nullp(msb));
    val = val * get_sign(x);
    SET_TAG(res, FLTN);
    SET_FLT(res, val);
    return (res);
}

// bignum remainder of bignum and int
int
bigx_remainder_i(int x, int y)
{
    int             msb,
                    sign1,
                    sign2;
    long long int   j,
                    r;


    msb = get_msb(bigx_abs(x));
    sign1 = get_sign(x);

    j = GET_INT(y);
    if (j < 0) {
	j = llabs(j);
	sign2 = -1;
    } else {
	sign2 = 1;
    }

    r = 0;

    do {
	long long int   i;

	i = GET_CAR(msb);
	i = i + r * BIGNUM_BASE;
	if (i >= j)
	    r = i % j;
	else
	    r = i + r;
	msb = prev(msb);
    } while (!nullp(msb));
    return (makeint((int) r * sign1 * sign2));
}

// bignum divide of bignum and int
int
bigx_div_i(int x, int y)
{
    int             res,
                    msb,
                    sign1,
                    sign2;
    long long int   j,
                    r,
                    q;


    res = gen_big();
    msb = get_msb(bigx_abs(x));
    sign1 = get_sign(x);

    j = GET_INT(y);
    if (j < 0) {
	j = llabs(j);
	sign2 = -1;
    } else {
	sign2 = 1;
    }

    r = 0;

    do {
	long long int   i;

	i = GET_CAR(msb);
	i = i + r * BIGNUM_BASE;
	if (i >= j) {
	    r = i % j;
	    q = i / j;
	    res = cons_prev(res, (int) q);
	} else {
	    r = i + r;
	    res = cons_prev(res, 0);
	}
	msb = prev(msb);
    } while (!nullp(msb));
    SET_TAG(res, BIGX);
    cut_zero(res);
    set_sign(res, sign1 * sign2);
    res = bigx_simplify(res);
    return (res);
}

// multple of bignum and int
int
bigx_mult_i(int x, int y)
{
    int             res,
                    msb,
                    sign1,
                    sign2;
    long long int   j,
                    c;


    msb = res = gen_big();
    sign1 = get_sign(x);

    j = GET_INT(y);
    if (j < 0) {
	j = llabs(j);
	sign2 = -1;
    } else {
	sign2 = 1;
    }

    c = 0;

    do {
	long long int   i,
	                z;

	i = GET_CAR(x);
	z = i * j + c;
	if (z >= BIGNUM_BASE) {
	    c = z / BIGNUM_BASE;
	    z = z % BIGNUM_BASE;
	    msb = cons_next((int) z, msb);
	} else {
	    c = 0;
	    msb = cons_next((int) z, msb);
	}
	x = next(x);
    } while (!nullp(x));
    if (c != 0)
	(void) cons_next((int) c, msb);
    SET_TAG(res, BIGX);
    cut_zero(res);
    set_sign(res, sign1 * sign2);
    res = bigx_simplify(res);
    return (res);
}
