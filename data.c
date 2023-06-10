/*
 * predicate for ISLisp data structures
 * operation for data structures
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <float.h>
#include "eisl.h"
#include "mem.h"
#include "fmt.h"
#include "compat/eiffel_stubs.h"

int get_int(int addr)
{
    return (GET_INT(addr));
}

long long int get_long(int addr)
{
    return (GET_LONG(addr));
}

int atomp(int addr)
{
    if (!(IS_LIST(addr)))
	return (1);
    else
	return (0);
}

int numberp(int addr)
{
    if (IS_INTEGER(addr) || IS_FLOAT(addr) || IS_LONGNUM(addr)
	|| IS_BIGNNUM(addr))
	return (1);
    else
	return (0);
}

int integerp(int x)
{
    if (IS_INTEGER(x))
	return (1);
    else
	return (0);
}

int bignump(int x)
{
    if (IS_BIGNNUM(x))
	return (1);
    else
	return (0);
}

int longnump(int x)
{
    if (IS_LONGNUM(x))
	return (1);
    else
	return (0);
}

int floatp(int x)
{
    if (IS_FLOAT(x))
	return (1);
    else
	return (0);
}

int math_integerp(int addr)
{
    if (IS_INTEGER(addr) || IS_LONGNUM(addr) || IS_BIGNNUM(addr))
	return (1);
    else
	return (0);
}


DEF_PREDICATE(SYMBOL, SYM)
int symbolp(int addr)
{
    if (IS_SYMBOL(addr))
	return (1);
    else
	return (0);
}

int listp(int addr)
{
    if (IS_LIST(addr) || IS_NIL(addr))
	return (1);
    else
	return (0);
}

int nullp(int addr)
{
    if (IS_NIL(addr))
	return (1);
    else
	return (0);
}

int eqp(int addr1, int addr2)
{
    if (addr1 == addr2)
	return (1);
    else
	return (0);
}

int eqlp(int addr1, int addr2)
{
    int i, n, ls;

    if (addr1 == addr2)
	return (1);
    else if (numberp(addr1) && numberp(addr2) && math_integerp(addr1)
	     && math_integerp(addr2))
	return (numeqp(addr1, addr2));
    else if (numberp(addr1) && numberp(addr2) && floatp(addr1)
	     && floatp(addr2))
	return (numeqp(addr1, addr2));
    else if (((symbolp(addr1) && symbolp(addr2)))
	     && (SAME_NAME(addr1, addr2)))
	return (1);
    else if (((charp(addr1) && charp(addr2))) && (SAME_NAME(addr1, addr2)))
	return (1);
    else if (((stringp(addr1) && stringp(addr2)))
	     && (SAME_NAME(addr1, addr2)))
	return (1);
    else if (vectorp(addr1) && vectorp(addr2)) {
	if (vector_length(addr1) == vector_length(addr2)) {
	    n = vector_length(addr1);
	    for (i = 0; i < n; i++)
		if (!eqlp(GET_VEC_ELT(addr1, i), GET_VEC_ELT(addr2, i)))
		    return (0);
	    return (1);
	} else
	    return (0);
    } else if (arrayp(addr1) && arrayp(addr2)) {
	if (equalp(array_length(addr1), array_length(addr2))) {
	    ls = array_length(addr1);
	    n = 1;
	    while (!nullp(ls)) {
		n = n * GET_INT(car(ls));
		ls = cdr(ls);
	    }
	    for (i = 0; i < n; i++)
		if (!eqlp(GET_VEC_ELT(addr1, i), GET_VEC_ELT(addr2, i)))
		    return (0);
	    return (1);
	} else
	    return (0);
    }
    return (0);
}

int equalp(int addr1, int addr2)
{
    if (vectorp(addr1) && vectorp(addr2)) {
	if (vector_length(addr1) == vector_length(addr2)) {
	    int i, n;

	    n = vector_length(addr1);
	    for (i = 0; i < n; i++) {
		if (!equalp(GET_VEC_ELT(addr1, i), GET_VEC_ELT(addr2, i)))
		    return (0);
	    }
	    return (1);
	} else
	    return (0);
    } else if (atomp(addr1) && atomp(addr2))
	return (eqlp(addr1, addr2));
    else if (atomp(addr1) && !atomp(addr2))
	return (0);
    else if (!atomp(addr1) && atomp(addr2))
	return (0);
    else if (equalp(car(addr1), car(addr2)) &&
	     equalp(cdr(addr1), cdr(addr2)))
	return (1);
    else
	return (0);

}

int subrp(int addr)
{

    if (IS_SUBR(GET_CAR(addr)))
	return (1);
    else
	return (0);
}

int fsubrp(int addr)
{

    if (IS_FSUBR(GET_CAR(addr)))
	return (1);
    else
	return (0);
}

int functionp(int addr)
{
    int val;

    val = find_dyn(addr);
    if ((val != -1) && IS_FUNC(val))
	return (val);
    val = find_env(addr);
    if ((val != FAILSE) && IS_FUNC(val))
	return (val);
    val = GET_CAR(addr);
    if (IS_FUNC(val))
	return (val);
    else
	return (0);
}

int macrop(int addr)
{
    if (!CELLRANGE(addr))
	return (0);
    else if (!CELLRANGE(GET_CAR(addr)))
	return (0);
    else if (IS_MACRO(GET_CAR(addr)))
	return (1);
    else
	return (0);
}

int genericp(int addr)
{

    if (IS_GENERIC(GET_CAR(addr)))
	return (1);
    else
	return (0);

}

int stringp(int x)
{
    if (IS_STRING(x))
	return (1);
    else
	return (0);
}


DEF_PREDICATE(CHARACTER, CHR)
int charp(int x)
{
    if (IS_CHARACTER(x))
	return (1);
    else
	return (0);
}

int vectorp(int x)
{
    if (IS_VECTOR(x))
	return (1);
    else
	return (0);
}

int arrayp(int x)
{
    if (IS_ARRAY(x))
	return (1);
    else
	return (0);
}


DEF_PREDICATE(STREAM, STREAM)
int streamp(int x)
{
    if (IS_STREAM(x))
	return (1);
    else
	return (0);
}

int string_input_stream_p(int x)
{
    if (streamp(x) && GET_OPT(x) == EISL_INSTR)
	return (1);
    else
	return (0);
}


int input_stream_p(int x)
{
    if (streamp(x)
	&& (GET_OPT(x) == EISL_INPUT ||
	    GET_OPT(x) == EISL_INOUT ||
	    GET_OPT(x) == EISL_INPUT_BIN ||
	    GET_OPT(x) == EISL_INOUT_BIN || GET_OPT(x) == EISL_INSTR))
	return (1);
    else
	return (0);
}

int text_input_stream_p(int x)
{
    if (streamp(x)
	&& (GET_OPT(x) == EISL_INPUT ||
	    GET_OPT(x) == EISL_INOUT || GET_OPT(x) == EISL_INSTR))
	return (1);
    else
	return (0);
}


int binary_input_stream_p(int x)
{
    if (streamp(x)
	&& (GET_OPT(x) == EISL_INPUT_BIN || GET_OPT(x) == EISL_INOUT_BIN))
	return (1);
    else
	return (0);
}

int output_stream_p(int x)
{
    if (streamp(x)
	&& (GET_OPT(x) == EISL_OUTPUT ||
	    GET_OPT(x) == EISL_INOUT ||
	    GET_OPT(x) == EISL_OUTPUT_BIN ||
	    GET_OPT(x) == EISL_INOUT_BIN || GET_OPT(x) == EISL_OUTSTR))
	return (1);
    else
	return (0);
}

int text_output_stream_p(int x)
{
    if (streamp(x)
	&& (GET_OPT(x) == EISL_OUTPUT ||
	    GET_OPT(x) == EISL_INOUT || GET_OPT(x) == EISL_OUTSTR))
	return (1);
    else
	return (0);
}


int binary_output_stream_p(int x)
{
    if (streamp(x)
	&& (GET_OPT(x) == EISL_OUTPUT_BIN || GET_OPT(x) == EISL_INOUT_BIN))
	return (1);
    else
	return (0);
}


int class_symbol_p(int x)
{
    if (IS_SYMBOL(x) && GET_OPT(x) == SYSTEM)
	return (1);
    else
	return (0);
}

int classp(int x)
{
    if (IS_CLASS(x))
	return (1);
    else
	return (0);
}

int subclassp(int x, int y)
{
    if (x == y)
	return (0);
    else if (y == cobject)
	return (1);
    else
	return (subclassp1(x, y));
}

int subclassp1(int x, int y)
{
    if (nullp(x))
	return (0);
    else if (atomp(x)) {
	if (x == y)
	    return (1);
	else if (GET_OPT(x) == USER && y == cstandard_object)
	    return (1);
	else if (GET_OPT(x) == USER && GET_OPT(y) == SYSTEM) {
	    x = cstandard_class;
	    return (subclassp1(x, y));
	} else if (symbolp(x))
	    return (subclassp1(GET_AUX(x), y));
	else if (GET_CAR(x) == NIL)
	    return (0);
	else
	    return (subclassp1(GET_CAR(x), y));
    } else {
	if (subclassp1(car(x), y) || subclassp1(cdr(x), y))
	    return (1);
	else
	    return (0);
    }
}

int has_common_p(int ls)
{
    if (length(ls) < 2)
	return (0);

    while (!nullp(cdr(ls))) {
	if (has_common_p1(car(ls), cadr(ls)))
	    return (1);
	else
	    ls = cdr(ls);
    }
    return (0);
}

int has_common_p1(int x, int y)
{
    if (includep(GET_CAR(GET_AUX(x)), GET_CAR(GET_AUX(y))))
	return (1);
    else if (y != cobject && y != cstandard_class && subclassp(x, y))
	return (1);
    else if (x != cobject && x != cstandard_class && subclassp(y, x))
	return (1);
    else
	return (0);
}

int includep(int x, int y)
{
    while (!nullp(x)) {
	if (member(car(x), y))
	    return (1);
	else
	    x = cdr(x);
    }
    return (0);
}

int has_same_p(int ls)
{
    while (!nullp(ls)) {
	if (member(car(ls), cdr(ls)))
	    return (1);
	else
	    ls = cdr(ls);
    }
    return (0);
}

int has_sys_class_p(int ls)
{
    while (!nullp(ls)) {
	if (GET_OPT(car(ls)) == SYSTEM)
	    return (1);
	else
	    ls = cdr(ls);
    }
    return (0);
}

int not_exist_class_p(int ls)
{
    while (!nullp(ls)) {
	if (GET_AUX(car(ls)) == csymbol)
	    return (1);
	else
	    ls = cdr(ls);
    }
    return (0);
}

int illegal_lambda_p(int ls)
{
    if (!listp(ls) && !nullp(ls))
	return (1);

    if (nullp(ls))
	return (0);
    else if (car(ls) == T)
	return (1);
    else if (car(ls) == NIL)
	return (1);
    else if (eqp(car(ls), make_sym("*PI*")))
	return (1);
    else if (eqp(car(ls), make_sym("*MOST-POSITIVE-FLOAT*")))
	return (1);
    else if (eqp(car(ls), make_sym("*MOST-NEGATIVE-FLOAT*")))
	return (1);
    else if (eqp(car(ls), make_sym(":REST"))
	     && member(make_sym(":REST"), cdr(ls)))
	return (1);
    else if (eqp(car(ls), make_sym("&REST"))
	     && member(make_sym("&REST"), cdr(ls)))
	return (1);
    else if (eqp(car(ls), make_sym(":REST"))
	     && member(make_sym("&REST"), cdr(ls)))
	return (1);
    else if (eqp(car(ls), make_sym("&REST"))
	     && member(make_sym(":REST"), cdr(ls)))
	return (1);
    else if (symbolp(car(ls)) && !eqp(car(ls), make_sym(":REST"))
	     && !eqp(car(ls), make_sym("&REST"))
	     && (STRING_REF(car(ls), 0) == ':'
		 || STRING_REF(car(ls), 0) == '&'))
	return (1);
    else
	return (illegal_lambda_p(cdr(ls)));

}

int undef_parameter_p(int ls)
{

    if (nullp(ls))
	return (0);
    else if (symbolp(car(ls)))
	return (undef_parameter_p(cdr(ls)));
    else if (listp(car(ls))) {
	/* e.g. ((x undef)) undef is only symbol and it's class is (class <symbol>) */
	if (symbolp(cadar(ls)) && GET_AUX(cadar(ls)) == csymbol)
	    return (1);
	else
	    return (undef_parameter_p(cdr(ls)));
    } else
	return (1);
}

int unified_parameter_p(int lamlis, int ls)
{

    if (nullp(lamlis) && nullp(ls))
	return (1);
    else if (nullp(lamlis) && !nullp(ls))
	return (0);
    else if (!nullp(lamlis) && nullp(ls))
	return (0);
    else if ((eqp(car(lamlis), make_sym(":REST"))
	      || eqp(car(lamlis), make_sym("&REST")))
	     && (eqp(car(ls), make_sym(":REST"))
		 || eqp(car(ls), make_sym("&REST"))))
	return (unified_parameter_p(cdr(lamlis), cdr(ls)));
    else if (symbolp(car(lamlis)) && symbolp(car(ls)))
	return (unified_parameter_p(cdr(lamlis), cdr(ls)));
    else if (symbolp(car(lamlis))
	     && (listp(car(ls) && length(car(ls) == 2))))
	return (unified_parameter_p(cdr(lamlis), cdr(ls)));
    else if ((listp(car(lamlis)) && length(car(lamlis)) == 2)
	     && (listp(car(ls) && length(car(ls) == 2))))
	return (unified_parameter_p(cdr(lamlis), cdr(ls)));
    else
	return (0);
    /*
     * check unification lambda-list of generic-function and
     * method-parameter e.g. lambda-list=(x y :rest z) parameter= ((x
     * <integer>)(y <float>) :rest (z <array))
     */

}


int improper_list_p(int ls)
{
    if (nullp(ls))
	return (0);
    else if (atomp(ls))
	return (1);
    else
	return (improper_list_p(cdr(ls)));
}

int duplicate_list_p(int ls)
{
    if (nullp(ls))
	return (0);
    else if (!eqp(car(ls), make_sym("&REST"))
	     && !eqp(car(ls), make_sym(":REST"))
	     && member(car(ls), cdr(ls)))
	return (1);
    else if (eqp(car(ls), make_sym("&REST")) && nullp(cdr(ls)))
	return (1);
    else if (eqp(car(ls), make_sym(":REST")) && nullp(cdr(ls)))
	return (1);
    else if (eqp(car(ls), make_sym("&REST")) && length(cdr(ls)) > 1)
	return (1);
    else if (eqp(car(ls), make_sym(":REST")) && length(cdr(ls)) > 1)
	return (1);
    else if (eqp(car(ls), make_sym("&REST"))
	     || eqp(car(ls), make_sym(":REST")))
	return (duplicate_list_p(cddr(ls)));
    else
	return (duplicate_list_p(cdr(ls)));
}

int symbol_list_p(int ls)
{
    if (nullp(ls))
	return (1);
    else if (!symbolp(car(ls)))
	return (0);
    else if (eqp(car(ls), make_sym("&REST")) && !symbolp(cadr(ls)))
	return (0);
    else if (eqp(car(ls), make_sym(":REST")) && !symbolp(cadr(ls)))
	return (0);
    else
	return (symbol_list_p(cdr(ls)));
}

int has_multiple_call_next_method_p(int x)
{
    int count, ls;

    count = 0;
    ls = x;

    while (!nullp(ls)) {
	if (has_multiple_call_next_method_p1(car(ls)))
	    count++;
	if (has_multiple_call_next_method_p2(car(ls)))
	    return (1);

	ls = cdr(ls);
    }
    if (count >= 2)
	return (1);
    else
	return (0);
}

int has_multiple_call_next_method_p1(int x)
{
    if (nullp(x))
	return (0);
    else if (symbolp(x) && eqp(x, make_sym("CALL-NEXT-METHOD")))
	return (1);
    else if (atomp(x))
	return (0);
    else if (has_multiple_call_next_method_p1(car(x))
	     || has_multiple_call_next_method_p1(cdr(x)))
	return (1);
    else
	return (0);

}

/* e.g. (list (call-next-method) (call-next-method)) */
int has_multiple_call_next_method_p2(int x)
{
    int count, ls;

    count = 0;
    ls = x;
    while (!nullp(ls)) {
	if (has_multiple_call_next_method_p1(car(ls)))
	    count++;

	ls = cdr(ls);
    }
    if (count >= 2)
	return (1);
    else
	return (0);
}

/* --------------list operation--------------------- */

int car(int addr)
{
    return (GET_CAR(addr));
}

int caar(int addr)
{
    return (car(car(addr)));
}

int cdar(int addr)
{
    return (cdr(car(addr)));
}

int cdr(int addr)
{
    return (GET_CDR(addr));
}

int cadr(int addr)
{
    return (car(cdr(addr)));
}

int cddr(int addr)
{
    return (cdr(cdr(addr)));
}

int caddr(int addr)
{
    return (car(cdr(cdr(addr))));
}

int cadar(int addr)
{
    return (car(cdr(car(addr))));
}

int cdddr(int addr)
{
    return (cdr(cdr(cdr(addr))));
}

int caddar(int addr)
{
    return (car(cdr(cdr(car(addr)))));
}

int nth(int n, int addr)
{
    while (n > 0) {
	addr = cdr(addr);
	n--;
    }
    return (car(addr));
}

int cons(int car, int cdr)
{
    int addr;

    addr = freshcell();
    SET_TAG(addr, LIS);
    SET_CAR(addr, car);
    SET_CDR(addr, cdr);
    SET_AUX(addr, ccons);	/* cons class */
    return (addr);
}

/*
int hcons(int car, int cdr)
{
    int addr;

    addr = freshcell();
    SET_TAG(addr, LIS);
    SET_CAR(addr, car);
    SET_CDR(addr, cdr);
    SET_AUX(addr, ccons);	
    return (addr);
}
*/

int length(int addr)
{
    int len = 0;

    while (!nullp(addr) && !atomp(addr)) {
	len++;
	addr = cdr(addr);
    }
    return (len);
}

int list(int arglist)
{
    if (nullp(arglist))
	return (NIL);
    else
	return (cons(car(arglist), list(cdr(arglist))));
}

int assoc(int x, int y)
{
    if (nullp(y))
	return (0);
    else if (eqlp(x, caar(y)))
	return (car(y));
    else
	return (assoc(x, cdr(y)));
}

int assq(int x, int y)
{
    if (nullp(y))
	return (FAILSE);
    else if (eqp(x, caar(y)))
	return (car(y));
    else
	return (assq(x, cdr(y)));
}

int assoc_list_p(int ls)
{
    while (!nullp(ls)) {
	if (!listp(car(ls)))
	    return (0);
	else
	    ls = cdr(ls);
    }
    return (1);
}

int member(int x, int y)
{
    if (nullp(y))
	return (NIL);
    else if (equalp(x, car(y)))
	return (y);
    else
	return (member(x, cdr(y)));
}

int member1(int x, int y, int z)
{
    if (nullp(y))
	return (NIL);
    else if (apply(z, list2(x, car(y))) != NIL)
	return (y);
    else
	return (member1(x, cdr(y), z));
}








/* extension */
int list1(int x)
{
    return (cons(x, NIL));
}


int list2(int x, int y)
{
    return (cons(x, cons(y, NIL)));
}

int list3(int x, int y, int z)
{
    return (cons(x, cons(y, cons(z, NIL))));
}

int list4(int x1, int x2, int x3, int x4)
{
    return (cons(x1, cons(x2, cons(x3, cons(x4, NIL)))));
}

int list6(int x1, int x2, int x3, int x4, int x5, int x6)
{
    return (cons
	    (x1, cons(x2, cons(x3, cons(x4, cons(x5, cons(x6, NIL)))))));
}

int list8(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8)
{
    return (cons(x1, cons(x2, cons(x3, cons(x4, cons(x5,
						     cons(x6,
							  cons(x7,
							       cons(x8,
								    NIL)))))))));
}

int
list10(int x1, int x2, int x3, int x4, int x5,
       int x6, int x7, int x8, int x9, int x10)
{
    return (cons(x1, cons(x2, cons(x3, cons(x4, cons(x5,
						     cons(x6,
							  cons(x7,
							       cons(x8,
								    cons
								    (x9,
								     cons
								     (x10,
								      NIL)))))))))));
}


int
list11(int x1, int x2, int x3, int x4, int x5,
       int x6, int x7, int x8, int x9, int x10, int x11)
{
    return (cons(x1, cons(x2, cons(x3, cons(x4, cons(x5,
						     cons(x6,
							  cons(x7,
							       cons(x8,
								    cons
								    (x9,
								     cons
								     (x10,
								      cons
								      (x11,
								       NIL))))))))))));
}


int reverse(int x)
{
    int res;

    res = NIL;
    while (!nullp(x) && !atomp(x)) {
	res = cons(car(x), res);
	x = cdr(x);
    }
    return (res);
}

int last(int x)
{
    return (car(reverse(x)));
}

int append(int x, int y)
{
    if (nullp(x))
	return (y);
    else
	return (cons(car(x), append(cdr(x), y)));
}

int copy(int x)
{
    if (nullp(x))
	return (NIL);
    else if (x == UNDEF)
	return (make_dummy());
    else if (integerp(x))
	return (make_int(GET_INT(x)));
    else if (floatp(x))
	return (make_flt(GET_FLT(x)));
    else if (charp(x))
	return (make_char(GET_NAME(x)));
    else if (stringp(x))
	return (make_str(GET_NAME(x)));
    else if (listp(x))
	return (cons(copy(car(x)), copy(cdr(x))));
    else
	return (x);
}


int listref(int lis, int n)
{
    while (!(nullp(lis))) {
	if (n == 0) {
	    return (car(lis));
	} else {
	    lis = cdr(lis);
	    n--;
	}
    }
    return (NIL);
}

int listref1(int lis, int n)
{
    while (!(nullp(lis))) {
	if (n == 0) {
	    return (lis);
	} else {
	    lis = cdr(lis);
	    n--;
	}
    }
    return (NIL);
}


int listcopy(int lis)
{
    if (nullp(lis))
	return (NIL);
    else if (!listp(lis))
	return (lis);
    else
	return (cons(car(lis), listcopy(cdr(lis))));
}

int remove_list(int x, int y)
{

    if (nullp(x))
	return (NIL);
    else if (member(car(x), y))
	return (cdr(x));
    else
	return (cons(car(x), remove_list(cdr(x), y)));
}

void vector_set(int v, int n, int obj)
{
    SET_VEC_ELT(v, n, obj);
}

int vector_ref(int v, int n)
{
    return (GET_VEC_ELT(v, n));
}

int vector_length(int v)
{
    return (GET_CDR(v));
}

int array_length(int obj)
{
    return (GET_CDR(obj));
}

/* n=0 ex ((1 2) 3 (4 5)) -> (1 2 3 4 5) */
int flatten(int n, int ls)
{
    if (nullp(ls))
	return (ls);
    else if (n <= 1)
	return (ls);
    else if (atomp(car(ls)))
	return (cons(car(ls), flatten(n, cdr(ls))));
    else
	return (append(flatten(n - 1, car(ls)), flatten(n, cdr(ls))));

}


/* e.g. (1 2 3 4) -> ((1 2)(3 4)) */
int structured(int ls, int st)
{
    return (structured1(ls, reverse(st)));
}

int structured1(int ls, int st)
{
    if (nullp(cdr(st)))
	return (ls);
    else
	return (structured1(structured2(ls, GET_INT(car(st))), cdr(st)));
}

int structured2(int ls, int n)
{
    if (nullp(ls))
	return (NIL);
    else
	return (cons(list_take(ls, n), structured2(list_drop(ls, n), n)));
}

int list_take(int ls, int n)
{
    if (n == 0)
	return (NIL);
    else
	return (cons(car(ls), list_take(cdr(ls), n - 1)));
}

int list_drop(int ls, int n)
{
    if (n == 0)
	return (ls);
    else
	return (list_drop(cdr(ls), n - 1));

}

/* generate array from list. e.g. #na(ls) ls=((1 2)(3 4)) */
int array(int n, int ls)
{
    int dim, res, ls1, i;

    dim = array_dim(n, ls);
    if (n == 0) {
	res = make_arr(dim, ls);
	return (res);
    } else if (n == 1)
	res = make_vec(GET_INT(car(dim)), UNDEF);
    else
	res = make_arr(dim, UNDEF);

    ls1 = flatten(n, ls);
    i = 0;
    while (!nullp(ls1)) {
	SET_VEC_ELT(res, i, car(ls1));
	i++;
	ls1 = cdr(ls1);
    }
    SET_PROP(res, ls);		/* for FAST compiler regist original list */
    return (res);
}

int vector_to_list(int x)
{
    int res, i;

    i = vector_length(x) - 1;
    res = NIL;
    while (i >= 0) {
	res = cons(vector_ref(x, i), res);
	i--;
    }
    return (res);
}

static inline void SET_CHAR(int addr, char x)
{
    REQUIRE(CELLRANGE(addr) && GET_TAG(addr) == CHR);
    heap[addr].name[0] = x;
}

int string_to_vector(int x)
{
    int res, len, i, ref;
    char c;

    len = strlen(GET_NAME(x));
    res = make_vec(len, UNDEF);
    ref = 0;
    i = 0;
    c = STRING_REF(x, i++);
    while (c != NUL) {
	int chr;

	chr = make_char("?");
	SET_CHAR(chr, c);
	vector_set(res, ref++, chr);
	c = STRING_REF(x, i++);
    }
    return (res);
}

int string_to_list(int x)
{
    int i, len, res;

    res = NIL;
    len = string_length(x);
    for (i = 0; i < len; i++) {
	int chr;

	chr = string_ref(x, i);
	res = cons(chr, res);
    }
    return (reverse(res));
}

int substr(int x, int s, int e)
{
    int i, j, pos, c;
    char *str;

    str = ALLOC(((e - s) + 1) * 6);
    /* for unicode allocate 6 byte for 1 char skip to start position */
    i = 0;
    pos = 0;
    while (i < s) {
	c = STRING_REF(x, pos);
	if (isUni1(c)) {
	    pos++;
	    i++;
	} else if (isUni2(c)) {
	    pos = pos + 2;
	    i++;
	} else if (isUni3(c)) {
	    pos = pos + 3;
	    i++;
	} else if (isUni4(c)) {
	    pos = pos + 4;
	    i++;
	} else if (isUni5(c)) {
	    pos = pos + 5;
	    i++;
	} else if (isUni6(c)) {
	    pos = pos + 6;
	    i++;
	}
    }


    j = 0;
    while (i < e) {
	c = STRING_REF(x, pos);
	if (isUni1(c)) {
	    str[j++] = STRING_REF(x, pos++);
	    i++;
	} else if (isUni2(c)) {
	    str[j++] = STRING_REF(x, pos++);
	    str[j++] = STRING_REF(x, pos++);
	    i++;
	} else if (isUni3(c)) {
	    str[j++] = STRING_REF(x, pos++);
	    str[j++] = STRING_REF(x, pos++);
	    str[j++] = STRING_REF(x, pos++);
	    i++;
	} else if (isUni4(c)) {
	    str[j++] = STRING_REF(x, pos++);
	    str[j++] = STRING_REF(x, pos++);
	    str[j++] = STRING_REF(x, pos++);
	    str[j++] = STRING_REF(x, pos++);
	    i++;
	} else if (isUni5(c)) {
	    str[j++] = STRING_REF(x, pos++);
	    str[j++] = STRING_REF(x, pos++);
	    str[j++] = STRING_REF(x, pos++);
	    str[j++] = STRING_REF(x, pos++);
	    str[j++] = STRING_REF(x, pos++);
	    i++;
	} else if (isUni6(c)) {
	    str[j++] = STRING_REF(x, pos++);
	    str[j++] = STRING_REF(x, pos++);
	    str[j++] = STRING_REF(x, pos++);
	    str[j++] = STRING_REF(x, pos++);
	    str[j++] = STRING_REF(x, pos++);
	    str[j++] = STRING_REF(x, pos++);
	    i++;
	}

    }
    str[j] = NUL;
    int res = make_str(str);
    FREE(str);
    return res;
}

int string_length(int addr)
{
    char str[STRSIZE], c;
    int pos, n;

    strcpy(str, GET_NAME(addr));
    pos = 0;
    n = 0;
    c = str[pos];
    while (c != NUL) {
	if (isUni2(c)) {
	    n++;
	    pos = pos + 2;
	} else if (isUni3(c)) {
	    n++;
	    pos = pos + 3;
	} else if (isUni4(c)) {
	    n++;
	    pos = pos + 4;
	} else if (isUni5(c)) {
	    n++;
	    pos = pos + 5;
	} else if (isUni6(c)) {
	    n++;
	    pos = pos + 6;
	} else {
	    n++;
	    pos++;
	}
	c = str[pos];
    }
    return (n);
}


int string_ref(int x, int y)
{
    char str[CHARSIZE];
    int pos, y1;

    pos = 0;
    y1 = 0;
    while (STRING_REF(x, pos) != NUL) {
	if (GET_INT(y) == y1) {
	    if (isUni2(STRING_REF(x, pos))) {
		str[0] = STRING_REF(x, pos);
		str[1] = STRING_REF(x, pos + 1);
		str[2] = NUL;
	    } else if (isUni3(STRING_REF(x, pos))) {
		str[0] = STRING_REF(x, pos);
		str[1] = STRING_REF(x, pos + 1);
		str[2] = STRING_REF(x, pos + 2);
		str[3] = NUL;
	    } else if (isUni4(STRING_REF(x, pos))) {
		str[0] = STRING_REF(x, pos);
		str[1] = STRING_REF(x, pos + 1);
		str[2] = STRING_REF(x, pos + 2);
		str[3] = STRING_REF(x, pos + 3);
		str[4] = NUL;
	    } else if (isUni5(STRING_REF(x, pos))) {
		str[0] = STRING_REF(x, pos);
		str[1] = STRING_REF(x, pos + 1);
		str[2] = STRING_REF(x, pos + 2);
		str[3] = STRING_REF(x, pos + 3);
		str[4] = STRING_REF(x, pos + 4);
		str[5] = NUL;
	    } else if (isUni6(STRING_REF(x, pos))) {
		str[0] = STRING_REF(x, pos);
		str[1] = STRING_REF(x, pos + 1);
		str[2] = STRING_REF(x, pos + 2);
		str[3] = STRING_REF(x, pos + 3);
		str[4] = STRING_REF(x, pos + 4);
		str[5] = STRING_REF(x, pos + 5);
		str[6] = NUL;
	    } else {
		str[0] = STRING_REF(x, pos);
		str[1] = NUL;
	    }
	    return (make_char(str));
	}
	if (isUni2(STRING_REF(x, pos))) {
	    pos = pos + 2;
	    y1++;
	} else if (isUni3(STRING_REF(x, pos))) {
	    pos = pos + 3;
	    y1++;
	} else if (isUni4(STRING_REF(x, pos))) {
	    pos = pos + 4;
	    y1++;
	} else if (isUni5(STRING_REF(x, pos))) {
	    pos = pos + 5;
	    y1++;
	} else if (isUni6(STRING_REF(x, pos))) {
	    pos = pos + 6;
	    y1++;
	} else {
	    pos = pos + 1;
	    y1++;
	}

    }
    return (NIL);
}



/*
 * string_set() It is assumed that the characters to be replaced and the
 * characters to be replaced are the same size. It's incomplete, but it
 * shouldn't be a problem in practice. If you try to do it completely, it 
 * will be complicated. 
 */
int string_set(int x, int y, int z)
{
    char str[STRSIZE];
    int pos, y1;

    pos = 0;
    y1 = 0;
    strcpy(str, GET_NAME(z));
    while (STRING_REF(x, pos) && pos < STRSIZE) {
	if (GET_INT(y) == y1) {
	    if (isUni2(str[0])) {
		STRING_SET(x, pos, str[0]);
		STRING_SET(x, pos + 1, str[1]);
	    } else if (isUni3(str[0])) {
		STRING_SET(x, pos, str[0]);
		STRING_SET(x, pos + 1, str[1]);
		STRING_SET(x, pos + 2, str[2]);
	    } else if (isUni4(str[0])) {
		STRING_SET(x, pos, str[0]);
		STRING_SET(x, pos + 1, str[1]);
		STRING_SET(x, pos + 2, str[2]);
		STRING_SET(x, pos + 3, str[3]);
	    } else if (isUni5(str[0])) {
		STRING_SET(x, pos, str[0]);
		STRING_SET(x, pos + 1, str[1]);
		STRING_SET(x, pos + 2, str[2]);
		STRING_SET(x, pos + 3, str[3]);
		STRING_SET(x, pos + 4, str[4]);
	    } else if (isUni6(str[0])) {
		STRING_SET(x, pos, str[0]);
		STRING_SET(x, pos + 1, str[1]);
		STRING_SET(x, pos + 2, str[2]);
		STRING_SET(x, pos + 3, str[3]);
		STRING_SET(x, pos + 4, str[4]);
		STRING_SET(x, pos + 5, str[5]);
	    } else {
		STRING_SET(x, pos, str[0]);
	    }
	    return (make_char(str));
	}
	if (isUni2(STRING_REF(x, pos))) {
	    pos = pos + 2;
	    y1++;
	} else if (isUni3(STRING_REF(x, pos))) {
	    pos = pos + 3;
	    y1++;
	} else if (isUni4(STRING_REF(x, pos))) {
	    pos = pos + 4;
	    y1++;
	} else if (isUni5(STRING_REF(x, pos))) {
	    pos = pos + 5;
	    y1++;
	} else if (isUni6(STRING_REF(x, pos))) {
	    pos = pos + 6;
	    y1++;
	} else {
	    pos++;
	    y1++;
	}

    }
    return (NIL);
}


int sublis(int x, int s, int e)
{
    int i, res;

    res = NIL;
    i = 0;
    while (!nullp(x)) {
	if (i >= s && i < e)
	    res = cons(copy(car(x)), res);
	i++;
	x = cdr(x);
    }
    return (reverse(res));
}

int subvec(int x, int s, int e)
{
    int i, j, res;

    res = make_vec(e - s, UNDEF);
    j = 0;
    for (i = s; i < e; i++) {
	SET_VEC_ELT(res, j, copy(GET_VEC_ELT(x, i)));
	j++;
    }
    return (res);
}

/*
 * compare priority of argument list of method
 * if x is higher than y, return 1.
 */
int high_priority_p(int x, int y)
{
    int args1, args2, argx, argy, classx, classy;

    if (GET_OPT(x) > GET_OPT(y))	// :around ... etc
	return (0);
    else if (GET_OPT(x) < GET_OPT(y))
	return (1);
    else if (GET_OPT(x) == AFTER && GET_OPT(y) == AFTER) {
	/*
	 * case :after this is reverse case primary when compiling,
	 * compiler chenge order. use (change-priority-for-compiler t) 
	 */
	args1 = car(GET_CAR(x));	/* lambda-list */
	args2 = car(GET_CAR(y));
	while (!nullp(args1)) {
	    argx = car(args1);
	    argy = car(args2);
	    if (atomp(argy)) {	/* case of no class information */
		args1 = cdr(args1);
		args2 = cdr(args2);
	    } else {
		if (atomp(argx))
		    return (1);
		classx = GET_AUX(cadr(argx));
		classy = GET_AUX(cadr(argy));
		if (subclassp(classy, classx))
		    return (1);

		args1 = cdr(args1);
		args2 = cdr(args2);
	    }

	}
	return (0);
    } else {
	args1 = car(GET_CAR(x));	/* lambda-list */
	args2 = car(GET_CAR(y));
	while (!nullp(args1)) {
	    argx = car(args1);
	    argy = car(args2);
	    if (atomp(argx)) {	/* case of no class information */
		args1 = cdr(args1);
		args2 = cdr(args2);
	    } else {
		if (atomp(argy))
		    return (1);
		classx = GET_AUX(cadr(argx));
		classy = GET_AUX(cadr(argy));
		if (subclassp(classx, classy))
		    return (1);

		args1 = cdr(args1);
		args2 = cdr(args2);
	    }

	}
	return (0);
    }
}

void insert_method(int x, int func)
{
    int methods, res;

    methods = GET_CDR(func);
    if (nullp(methods)) {
	SET_CDR(func, list1(x));
	return;
    }
    res = NIL;
    while (!nullp(methods)) {
	if (high_priority_p(car(methods), x)) {
	    res = cons(car(methods), res);
	    methods = cdr(methods);
	} else
	    break;
    }
    res = append(reverse(cons(x, res)), methods);
    SET_CDR(func, res);
    return;
}

void resort_method(int func)
{
    int methods, res;

    methods = GET_CDR(func);
    if (nullp(methods))
	return;

    res = cons(car(methods), NIL);
    methods = cdr(methods);
    while (!nullp(methods)) {
	int temp, x;

	x = car(methods);
	temp = NIL;
	bool high_priority_found = false;
	while (!nullp(res)) {
	    if (high_priority_p(x, car(res))) {
		res = append(reverse(temp), cons(x, res));
		high_priority_found = true;
		break;
	    } else {
		temp = cons(car(res), temp);
		res = cdr(res);
	    }
	}
	if (!high_priority_found) {
	    res = reverse(cons(x, temp));
	}
	methods = cdr(methods);
    }
    SET_CDR(func, res);
}

void redef_generic(void)
{
    int ls;

    ls = generic_list;
    while (!nullp(ls)) {
	resort_method(GET_CAR(car(ls)));
	ls = cdr(ls);
    }
    redef_flag = false;
    return;
}

int method_qualifier_p(int x)
{
    if (eqp(x, make_sym(":BEFORE")) ||
	eqp(x, make_sym(":AFTER")) || eqp(x, make_sym(":AROUND")))
	return (1);
    else
	return (0);
}


/*
 * ----------unicode------------------
 * transform from UTF-8 to unicode
 */
int utf8_to_ucs4(char *p)
{
    int x, x1, x2, x3, res;
    unsigned char uc;

    uc = (unsigned char) *p;
    if (uc <= 0x7f) {
	x = (int) uc;
	return (x);
    } else if (uc >= 0xc0 && uc <= 0xdf) {
	x = (int) (UTF2MSK1 & uc);
	x = x << 6;
	p++;
	uc = (unsigned char) *p;
	x1 = (int) (UTFOMSKO & uc);
	res = x | x1;
	return (res);
    } else if (uc >= 0xe0 && uc <= 0xef) {
	x = (int) (UTF3MSK1 & uc);
	x = x << 12;
	p++;
	uc = (unsigned char) *p;
	x1 = (int) (UTFOMSKO & uc);
	x1 = x1 << 6;
	p++;
	uc = (unsigned char) *p;
	x2 = (int) (UTFOMSKO & uc);
	res = x | x1 | x2;
	return (res);
    } else if (uc >= 0xf0 && uc <= 0xf7) {
	x = (int) (UTF4MSK1 & uc);
	x = x << 18;
	p++;
	uc = (unsigned char) *p;
	x1 = (int) (UTFOMSKO & uc);
	x1 = x1 << 12;
	p++;
	uc = (unsigned char) *p;
	x2 = (int) (UTFOMSKO & uc);
	x2 = x2 << 6;
	p++;
	uc = (unsigned char) *p;
	x3 = (int) (UTFOMSKO & uc);
	res = x | x1 | x2 | x3;
	return (res);
    } else
	return (-1);
}



/* transform from Unicode to UTF-8 */
void ucs4_to_utf8(int n, char *p)
{
    int w, x, y, z;

    if (n <= 0x7f) {
	*p = (char) n;
    } else if (n <= 0x07ff) {
	x = UNI2MSK1 & n;
	x = x >> 6;
	x = UNI2ADD1 | x;
	y = UNI2MSK2 & n;
	y = UNIOADDO | y;
	*p = (char) x;
	p++;
	*p = (char) y;
    } else if (n <= 0xffff) {
	x = UNI3MSK1 & n;
	x = x >> 12;
	x = UNI3ADD1 | x;
	y = UNI3MSK2 & n;
	y = y >> 6;
	y = UNIOADDO | y;
	z = UNI3MSK3 & n;
	z = UNIOADDO | z;
	*p = (char) x;
	p++;
	*p = (char) y;
	p++;
	*p = (char) z;
    } else if (n < 0x1fffff) {
	w = UNI4MSK1 & n;
	w = w >> 18;
	w = UNI4ADD1 | w;
	x = UNI4MSK2 & n;
	x = x >> 12;
	x = UNIOADDO | x;
	y = UNI4MSK3 & n;
	y = y >> 6;
	y = UNIOADDO | y;
	z = UNI4MSK4 & n;
	z = UNIOADDO | z;
	*p = (char) w;
	p++;
	*p = (char) x;
	p++;
	*p = (char) y;
	p++;
	*p = (char) z;
    } else {
	error(OUT_OF_RANGE, "Unicode->UTF-8", NIL);
    }
    p++;
    *p = NUL;
}
