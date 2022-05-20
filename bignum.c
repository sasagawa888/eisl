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
* Memo 
* bigx_div function is immutable. However, this consumes a large amount of cell area.
* I will change to destructive assignment to reduce cell consumption.
*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "eisl.h"
#include "fmt.h"
#include "text.h"


#define CHECKBIG(x) if(big_pt0<0 || big_pt0>=BIGSIZE){printf("point%d ",x);error(RESOURCE_ERR,"bigcell",big_pt0);}

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
		CHECKBIG(1)
		bigcell[big_pt0++] = atoi(integer);
	    len++;
	} else {
	    integer[i + 1] = NUL;
	    while (i >= 0) {
		integer[i] = bignum[i];
		i--;
	    }
		CHECKBIG(2)
		bigcell[big_pt0++] = atoi(integer);
	    len++;
	}
    }

    if (len == 2) {
	long long int   l,
	                m;

	CHECKBIG(3)
	l = (long long int) bigcell[big_pt0-1] * BIGNUM_BASE;
	m = (long long int) bigcell[big_pt0-2];
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


int
gen_big(void)
{
    int             res;

    res = freshcell();
    SET_CDR(res, NIL);
    SET_PROP(res, -1);
    return (res);
}

// old bignum
// get address of upper digit
int
next(int x)
{
    return (GET_CDR(x));
}

// old bignum
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
	if (bigcell[pointerx] != bigcell[pointery])
	    return (0);

	pointerx--;
	pointery--;
	len--;
    } while (len > 0);

	return (1);

}


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




int
bigx_int_to_big(int x)
{
    int             res,
                    y;

    y = GET_INT(x);
	CHECKBIG(4)
	bigcell[big_pt0++] = abs(y);
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
	CHECKBIG(5)
	bigcell[big_pt0++] = i2;
	CHECKBIG(6)
	bigcell[big_pt0++] = i1;
    res = gen_big();
    SET_TAG(res, BIGX);
	set_pointer(res,big_pt0-1);
	set_length(res,2);
    if (l >= 0)
	set_sign(res, 1);
    else
	set_sign(res, -1);
    return (res);
}


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
	l2 = bigcell[get_pointer(x)-1];
	l = (l1 * BIGNUM_BASE + l2) * get_sign(x);
	return (makelong(l));
    } else
	return (x);
}

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
		CHECKBIG(7)
		bigcell[big_pt0++] = 0;
	}
    for(i=0;i<len;i++){
		CHECKBIG(8)
		bigcell[big_pt0++] = bigcell[pointer+i];
	}

    set_pointer(res,big_pt0-1);
	set_length(res,len+n);
    return (res);
}

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
	CHECKBIG(9)
	bigcell[big_pt0++] = q;
	pointerx++;
	pointery++;
	len1--;
	len2--;
	len++;
    } while (len1 > 0 || len2 > 0);
    if (c != 0){
		CHECKBIG(10)
		bigcell[big_pt0++] = c;
	}
	set_pointer(res,big_pt0-1);
	set_length(res,len);
    return (res);
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
	CHECKBIG(11)
	bigcell[big_pt0++] = z;
	pointerx++;
	pointery++;
	len1--;
	len2--;
	len++;
    } while (len1 > 0 || len2 > 0);

	big_pt0--;
	while(bigcell[big_pt0] == 0 && len > 1){
		big_pt0--;
		len--;
	}
	
	big_pt0++;
    set_pointer(res,big_pt0-1);
	set_length(res,len);
    return (res);
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

	// clear area of calculate
	int i,j;
	for(i=0;i<=len;i++){
		CHECKBIG(12)
		bigcell[i+big_pt0] = 0;
	}
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
			CHECKBIG(13)
			bigcell[big_pt0+j+i] = (int)l2;
	    	bigcell[big_pt0+j+i+1] = (int)l1;
		}
	}
	
	big_pt0 = big_pt0 + len;
	
	while(bigcell[big_pt0] == 0 && len > 1){
		big_pt0--;
		len--;
	}
	big_pt0++;
	set_pointer(res,big_pt0-1);
	set_length(res,len+1);
    return (res);
}

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



int
bigx_div1(int arg1, int arg2)
{
    int             shift,save0,save1,
                    res,len,q,dividend,subtract,
					pointerx,pointery,
                    msb1,msb2;
    long long int   lmsb1;


	// arg1 > arg2 -> 0
	if(smallerp(arg1,arg2))
		return(makeint(0));

    res = gen_big();
	SET_TAG(res, BIGX);
    set_sign(res, 1);
	len = 0;
	big_pt0 = big_pt0 + get_length(arg1);  // prepare area of answer. 
	set_pointer(res,big_pt0);
	pointery = get_pointer(arg2); //MSB pointer
	msb2 = bigcell[pointery];  // value of MSB
	dividend = arg1;
	simp_flag = false;
	save1 = BIGNUM_WORK;

    
	do {
	save0 = big_pt0;
	big_pt0 = save1;
	shift = get_length(dividend) - get_length(arg2);
	pointerx = get_pointer(dividend); // MSB
	msb1 = bigcell[pointerx];
	if(msb1 >= msb2){
		q = msb1 / msb2;
		
	}
	else{
		lmsb1 = (long long int)bigcell[pointerx]*BIGNUM_BASE + (long long int)bigcell[pointerx-1];
		q = (int)(lmsb1 / (long long int) msb2);
		shift--;
	}

	subtract = bigx_shift(bigx_mult1(arg2,bigx_int_to_big(makeint(q))),shift);
	dividend = bigx_minus(dividend,subtract);
	
	// e.g. (div 100000000000000000000000000 25000000000000000000000002) = 3 (not 4)
	while(negativep(dividend)){
		dividend = plus(dividend,bigx_shift(arg2,shift));
		q--;
	}

	save1 = big_pt0;
	big_pt0 = save0;
	CHECKBIG(14)
	bigcell[big_pt0-len] = q;
	len++;

	} while(!smallerp(dividend,arg2));

	// when divident is smaller than divisior and shift > 0 insert zero
	//e.q.  div(3000000000000000000,30000000000)
    while(shift > 0){
			CHECKBIG(15)
			bigcell[big_pt0-len] = 0;
			shift--;
			len++;
	}
	
	simp_flag = true;
	big_pt0++;
	set_pointer(res,big_pt0-1);
	set_length(res,len);
	return(res);
}


int
bigx_remainder(int arg1, int arg2)
{
    int             shift,
                    res,len,q,dividend,subtract,
					pointerx,pointery,save0,pointer,
                    msb1,msb2;
    long long int   lmsb1;


	// arg1 > arg2 -> 0
	if(smallerp(arg1,arg2))
		return(makeint(0));

    res = gen_big();
	SET_TAG(res, BIGX);
    set_sign(res, 1);
	big_pt0 = big_pt0 + get_length(arg1);  // prepare area of answer. 
	set_pointer(res,big_pt0);
	pointery = get_pointer(arg2); //MSB pointer
	msb2 = bigcell[pointery];  // value of MSB
	dividend = arg1;
	save0 = big_pt0;
	big_pt0 = BIGNUM_WORK; // change to working area
    
	do {
	shift = get_length(dividend) - get_length(arg2);
	pointerx = get_pointer(dividend); // MSB
	msb1 = bigcell[pointerx];
	if(msb1 >= msb2){
		q = msb1 / msb2;
		
	}
	else{
		lmsb1 = (long long int)bigcell[pointerx]*BIGNUM_BASE + (long long int)bigcell[pointerx-1];
		q = (int)(lmsb1 / (long long int) msb2);
		shift--;
	}
	subtract = bigx_shift(bigx_mult1(arg2,bigx_int_to_big(makeint(q))),shift);
	dividend = bigx_minus(dividend,subtract);

	// e.g. (div 100000000000000000000000000 25000000000000000000000002) = 3 (not 4)
	while(negativep(dividend)){
		dividend = plus(dividend,bigx_shift(arg2,shift));
		q--;
	}

	} while(!smallerp(dividend,arg2));

	big_pt0 = save0; //restore pointer
	// copy dividend to big_pt0 temporarly area

	len = get_length(dividend);
	pointer = get_pointer(dividend)-len+1; //LSB
	int i;
	for(i=0;i<len;i++){
		CHECKBIG(16)
		bigcell[big_pt0++] = bigcell[pointer++];
	}
	set_pointer(res,big_pt0-1);
	set_length(res,len);
	return(res);
}


int
bigx_big_to_flt(int x)
{
    double          val;
    int             pointer,len,
                    res;

    res = freshcell();
    val = 0.0;
    pointer = get_pointer(x);
	len = get_length(x);
    do {
	int             i;

	i = bigcell[pointer];
	val = val * (double) BIGNUM_BASE + (double) i;
	pointer--;
	len--;
    } while (len > 0);
    val = val * get_sign(x);
    SET_TAG(res, FLTN);
    SET_FLT(res, val);
    return (res);
}


// bignum remainder of bignum and int
int
bigx_remainder_i(int x, int y)
{
    int             abs,pointer,len,
                    sign1,
                    sign2;
    long long int   j,
                    r;

	abs = bigx_abs(x);
    pointer = get_pointer(abs);
	len = get_length(abs);
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

	i = bigcell[pointer];
	i = i + r * BIGNUM_BASE;
	if (i >= j)
	    r = i % j;
	else
	    r = i + r;
	pointer--;
	len--;
    } while (len > 0);
    return (makeint((int) r * sign1 * sign2));
}

int
bigx_div_i(int x, int y)
{
    int             res,pointer,
                    msb,len,n,
                    sign1,
                    sign2;
    long long int   j,
                    r,
                    q;


    res = gen_big();
	len = n = get_length(x);
    msb = get_pointer(bigx_abs(x));
    sign1 = get_sign(x);

    j = GET_INT(y);
    if (j < 0) {
	j = llabs(j);
	sign2 = -1;
    } else {
	sign2 = 1;
    }

    r = 0;

	big_pt0 = big_pt0 + len;
	pointer = big_pt0;
    do {
	long long int   i;

	i = bigcell[msb];
	i = i + r * BIGNUM_BASE;
	if (i >= j) {
	    r = i % j;
	    q = i / j;
		bigcell[pointer--] = (int) q;
	} else {
	    r = i + r;
		bigcell[pointer--] = 0;
	}
	msb--;
	n--;
    } while (n > 0);
    SET_TAG(res, BIGX);
    while(bigcell[big_pt0] == 0 && len > 1){
		big_pt0--;
		len--;
	}
	big_pt0++;
	set_pointer(res,big_pt0-1);
	set_length(res,len);
    set_sign(res, sign1 * sign2);
	if(simp_flag)
    res = bigx_simplify(res);
    return (res);
}


// multple of bignum and int
int
bigx_mult_i(int x, int y)
{
    int             res,
                    len,pointer,n,
                    sign1,
                    sign2;
    long long int   j,
                    c;


    res = gen_big();
	len = n = get_length(x);
	pointer = get_pointer(x)-len+1; //LSB
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

	i = bigcell[pointer];
	z = i * j + c;
	if (z >= BIGNUM_BASE) {
	    c = z / BIGNUM_BASE;
	    z = z % BIGNUM_BASE;

		CHECKBIG(17)
		bigcell[big_pt0++] = (int)z;
	} else {
	    c = 0;
		CHECKBIG(18)
		bigcell[big_pt0++] = (int)z;
	}
	pointer++;
	len--;
    } while (len > 0);

	CHECKBIG(19)
	bigcell[big_pt0] = (int)c;
	len = n + 1;
	while(bigcell[big_pt0] == 0 && len > 1){
		big_pt0--;
		len--;
	}
	big_pt0++;

    SET_TAG(res, BIGX);
    set_pointer(res,big_pt0-1);
	set_length(res,len);
    set_sign(res, sign1 * sign2);
    res = bigx_simplify(res);
    return (res);
}
