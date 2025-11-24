/*
 * ISLisp standard builtin functions.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>
#include <dlfcn.h>
#include <limits.h>
#include <unistd.h>
#include "eisl.h"
#include "mem.h"
#include "except.h"
#include "str.h"
#include "text.h"

#define BININT_LEN 64

#ifndef LINE_MAX
#define LINE_MAX 2048
#endif


void init_subr(void)
{
    /* constant */
    bind_const("*PI*", make_flt(M_PI));
    bind_const("*MOST-POSITIVE-FLOAT*", make_flt(DBL_MAX));
    bind_const("*MOST-NEGATIVE-FLOAT*", make_flt(-DBL_MAX));
    bind_const("*POSITIVE-INFINITY*", make_flt(INFINITY));
    bind_const("*NEGATIVE-INFINITY*", make_flt(-INFINITY));

    /* function */
    def_subr("-", f_minus);
    def_subr("*", f_mult);
    def_subr("/=", f_notnumeqp);
    def_subr("+", f_plus);
    def_subr("<", f_smaller);
    def_subr("<=", f_eqsmaller);
    def_subr("=", f_numeqp);
    def_subr(">", f_greater);
    def_subr(">=", f_eqgreater);
    def_subr("ABS", f_abs);
    def_subr("APPEND", f_append);
    def_subr("APPLY", f_apply);
    def_subr("AREF", f_aref);
    def_subr("ARITHMETIC-ERROR-OPERANDS", f_arithmetic_error_operands);
    def_subr("ARITHMETIC-ERROR-OPERATION", f_arithmetic_error_operation);
    def_subr("ARRAY-DIMENSIONS", f_array_dimensions);
    def_subr("ASSOC", f_assoc);
    def_subr("ATAN", f_atan);
    def_subr("ATAN2", f_atan2);
    def_subr("ATANH", f_atanh);
    def_subr("ATOM", f_atomp);
    def_subr("BASIC-ARRAY-P", f_basic_array_p);
    def_subr("BASIC-ARRAY*-P", f_basic_array_star_p);
    def_subr("BASIC-VECTOR-P", f_basic_vector_p);
    def_subr("CALL-NEXT-METHOD", f_call_next_method);
    def_subr("CAR", f_car);
    def_subr("CDR", f_cdr);
    def_subr("CEILING", f_ceiling);
    def_subr("CERROR", f_cerror);
    def_subr("CHAR-INDEX", f_char_index);
    def_subr("CHAR/=", f_char_noteqp);
    def_subr("CHAR<", f_char_smallerp);
    def_subr("CHAR<=", f_char_eqsmallerp);
    def_subr("CHAR=", f_char_eqp);
    def_subr("CHAR>", f_char_greaterp);
    def_subr("CHAR>=", f_char_eqgreaterp);
    def_subr("CHARACTERP", f_characterp);
    def_subr("CLASS-OF", f_class_of);
    def_subr("CLOSE", f_close);
    def_subr("CONDITION-CONTINUABLE", f_condition_continuable);
    def_subr("CONS", f_cons);
    def_subr("CONSP", f_consp);
    def_subr("CONTINUE-CONDITION", f_continue_condition);
    def_subr("COS", f_cos);
    def_subr("COSH", f_cosh);
    def_subr("CREATE-ARRAY", f_create_array);
    def_subr("CREATE-LIST", f_create_list);
    def_subr("CREATE-STRING-INPUT-STREAM", f_create_string_input_stream);
    def_subr("CREATE-STRING-OUTPUT-STREAM", f_create_string_output_stream);
    def_subr("CREATE-STRING", f_create_string);
    def_subr("CREATE-VECTOR", f_create_vector);
    def_subr("CREATE*", f_create_star);
    def_subr("DIV", f_div);
    def_subr("DOMAIN-ERROR-OBJECT", f_domain_error_object);
    def_subr("DOMAIN-ERROR-EXPECTED-CLASS", f_domain_error_expected_class);
    def_subr("ELT", f_elt);
    def_subr("EQ", f_eq);
    def_subr("EQL", f_eql);
    def_subr("EQUAL", f_equal);
    def_subr("ERROR-OUTPUT", f_error_output);
    def_subr("ERROR", f_error);
    def_subr("EVAL", f_eval);
    def_subr("EXP", f_exp);
    def_subr("EXPT", f_expt);
    def_subr("FILE-LENGTH", f_file_length);
    def_subr("FILE-POSITION", f_file_position);
    def_subr("FINISH-OUTPUT", f_finish_output);
    def_subr("FLOAT", f_float);
    def_subr("FLOATP", f_floatp);
    def_subr("FLOOR", f_floor);
    def_subr("FORMAT-CHAR", f_format_char);
    def_subr("FORMAT-FRESH-LINE", f_format_fresh_line);
    def_subr("FORMAT-FLOAT", f_format_float);
    def_subr("FORMAT-INTEGER", f_format_integer);
    def_subr("FORMAT-OBJECT", f_format_object);
    def_subr("FORMAT-TAB", f_format_tab);
    def_subr("FORMAT", f_format);
    def_subr("FUNCALL", f_funcall);
    def_subr("FUNCTIONP", f_functionp);
    def_subr("GAREF", f_garef);
    def_subr("GBC", f_gbc);
    def_subr("GCD", f_gcd);
    def_subr("GENERAL-ARRAY*-P", f_general_array_star_p);
    def_subr("GENERAL-VECTOR-P", f_general_vector_p);
    def_subr("GENERIC-FUNCTION-P", f_generic_function_p);
    def_subr("GENSYM", f_gensym);
    def_subr("GET-INTERNAL-RUN-TIME", f_get_internal_run_time);
    def_subr("GET-INTERNAL-REAL-TIME", f_get_internal_real_time);
    def_subr("GET-OUTPUT-STREAM-STRING", f_get_output_stream_string);
    def_subr("GET-UNIVERSAL-TIME", f_get_universal_time);
    def_subr("IDENTITY", f_identity);
    def_subr("INITIALIZE-OBJECT*", f_initialize_object_star);
    def_subr("INPUT-STREAM-P", f_input_stream_p);
    def_subr("INSTANCEP", f_instancep);
    def_subr("INTEGERP", f_integerp);
    def_subr("INTERNAL-TIME-UNITS-PER-SECOND",
	     f_internal_time_units_per_second);
    def_subr("ISQRT", f_isqrt);
    def_subr("LCM", f_lcm);
    def_subr("LENGTH", f_length);
    def_subr("LIST", f_list);
    def_subr("LISTP", f_listp);
    def_subr("LOAD", f_load);
    def_subr("LOG", f_log);
    def_subr("MAP-INTO", f_map_into);
    def_subr("MAPC", f_mapc);
    def_subr("MAPCAR", f_mapcar);
    def_subr("MAPCAN", f_mapcan);
    def_subr("MAPCON", f_mapcon);
    def_subr("MAPL", f_mapl);
    def_subr("MAPLIST", f_maplist);
    def_subr("MAX", f_max);
    def_subr("MEMBER", f_member);
    def_subr("MIN", f_min);
    def_subr("MOD", f_mod);
    def_subr("NEXT-METHOD-P", f_next_method_p);
    def_subr("NOT", f_not);
    def_subr("NREVERSE", f_nreverse);
    def_subr("NULL", f_nullp);
    def_subr("NUMBERP", f_numberp);
    def_subr("OPEN-INPUT-FILE", f_open_input_file);
    def_subr("OPEN-IO-FILE", f_open_io_file);
    def_subr("OPEN-OUTPUT-FILE", f_open_output_file);
    def_subr("OPEN-STREAM-P", f_open_stream_p);
    def_subr("OUTPUT-STREAM-P", f_output_stream_p);
    def_subr("PARSE-ERROR-STRING", f_parse_error_string);
    def_subr("PARSE-ERROR-EXPECTED-CLASS", f_parse_error_expected_class);
    def_subr("PARSE-NUMBER", f_parse_number);
    def_subr("PREVIEW-CHAR", f_preview_char);
    def_subr("PRINT", f_print);
    def_subr("PROBE-FILE", f_probe_file);
    def_subr("PROPERTY", f_property);
    def_subr("QUIT", f_quit);
    def_subr("QUOTIENT", f_quotient);
    def_subr("READ-BYTE", f_read_byte);
    def_subr("READ-CHAR", f_read_char);
    def_subr("READ-LINE", f_read_line);
    def_subr("READ", f_read);
    def_subr("RECIPROCAL", f_reciprocal);
    def_subr("REMOVE-PROPERTY", f_remove_property);
    def_subr("REVERSE", f_reverse);
    def_subr("ROUND", f_round);
    def_subr("SET-AREF", f_set_aref);
    def_subr("SET-CAR", f_set_car);
    def_subr("SET-CDR", f_set_cdr);
    def_subr("SET-ELT", f_set_elt);
    def_subr("SET-FILE-POSITION", f_set_file_position);
    def_subr("SET-GAREF", f_set_garef);
    def_subr("SET-PROPERTY", f_set_property);
    def_subr("SET-SLOT-VALUE", f_set_slot_value);
    def_subr("SIGNAL-CONDITION", f_signal_condition);
    def_subr("SIMPLE-ERROR-FORMAT-ARGUMENTS",
	     f_simple_error_format_arguments);
    def_subr("SIMPLE-ERROR-FORMAT-STRING", f_simple_error_format_string);
    def_subr("SIN", f_sin);
    def_subr("SINH", f_sinh);
    def_subr("SLOT-VALUE", f_slot_value);
    def_subr("SQRT", f_sqrt);
    def_subr("STANDARD-INPUT", f_standard_input);
    def_subr("STANDARD-OUTPUT", f_standard_output);
    def_subr("STREAM-ERROR-STREAM", f_stream_error_stream);
    def_subr("STREAMP", f_streamp);
    def_subr("STREAM-READY-P", f_stream_ready_p);
    def_subr("STRING-APPEND", f_string_append);
    def_subr("STRING-INDEX", f_string_index);
    def_subr("STRING/=", f_string_noteqp);
    def_subr("STRING<", f_string_smallerp);
    def_subr("STRING<=", f_string_eqsmallerp);
    def_subr("STRING=", f_string_eqp);
    def_subr("STRING>", f_string_greaterp);
    def_subr("STRING>=", f_string_eqgreaterp);
    def_subr("STRINGP", f_stringp);
    def_subr("SUBCLASSP", f_subclassp);
    def_subr("SUBSEQ", f_subseq);
    def_subr("SYMBOLP", f_symbolp);
    def_subr("TAN", f_tan);
    def_subr("TANH", f_tanh);
    def_subr("TRUNCATE", f_truncate);
    def_subr("UNDEFINED-ENTITY-NAME", f_undefined_entity_name);
    def_subr("UNDEFINED-ENTITY-NAMESPACE", f_undefined_entity_namespace);
    def_subr("VECTOR", f_vector);
    def_subr("WRITE-BYTE", f_write_byte);

    /* inner extended functions */
    def_subr("EISL-DUMMYP", f_dummyp);
}



/*
 * initialize generic functions
 */

void init_generic(void)
{
    int lamlis, body;

    lamlis = list3(make_sym("x"), make_sym(":REST"), make_sym("y"));
    body =
	list3(make_sym(":METHOD"),
	      list3(make_sym("x"), make_sym(":REST"), make_sym("y")),
	      list4(make_sym("LET"),
		    list1(list2
			  (make_sym("obj"),
			   list3(make_sym("CREATE*"), make_sym("x"),
				 NIL))),
		    list3(make_sym("INITIALIZE-OBJECT"), make_sym("obj"),
			  make_sym("y")), make_sym("obj")));
    eval(list4(make_sym("DEFGENERIC"), make_sym("CREATE"), lamlis, body),
	 0);
    /*
     * (defgeneric create(x :rest y) (:method (x :rest y) (let ((obj (create* x
     * '()))) (initialize-object obj y) obj)))
     * 
     */

    lamlis = list2(make_sym("x"), make_sym("y"));
    body = list3(make_sym(":METHOD"), list2(make_sym("x"), make_sym("y")),
		 list3(make_sym("INITIALIZE-OBJECT*"), make_sym("x"),
		       make_sym("y")));
    eval(list4
	 (make_sym("DEFGENERIC*"), make_sym("INITIALIZE-OBJECT"), lamlis,
	  body), 0);
    /*
     * (defgeneric* initialize-object(x y) (:method (x y)
     * (initialize-object* x y))) 
     */

    lamlis = list2(make_sym("x"), make_sym("y"));
    body = NIL;
    eval(list4
	 (make_sym("DEFGENERIC*"), make_sym("REPORT-CONDITION"), lamlis,
	  body), 0);
    /*
     * (defgeneric report-condition (x y)) 
     */
}

/* arithmetic function */
int f_plus(int arglist, int th __unused)
{
    int augend;

    augend = make_int(0);

    for (int remaining_operands = arglist;
	 !(IS_NIL(remaining_operands));
	 remaining_operands = cdr(remaining_operands)) {

	int addend = car(remaining_operands);

	augend = plus(augend, addend);
    }
    return (augend);
}

int f_minus(int arglist, int th)
{
    int minuend, n;

    minuend = car(arglist);
    if ((n = length(arglist)) == 0)
	error(WRONG_ARGS, "-", arglist, th);
    if (n == 1)
	return (mult(minuend, make_int(-1)));

    arglist = cdr(arglist);

    for (int remaining_operands = arglist;
	 !(IS_NIL(remaining_operands));
	 remaining_operands = cdr(remaining_operands)) {

	int subtrahend = car(remaining_operands);
	minuend = minus(minuend, subtrahend);
    }
    return (minuend);
}

int f_mult(int arglist, int th __unused)
{
    int multiplicand;

    multiplicand = make_int(1);

    for (int remaining_operands = arglist;
	 !(IS_NIL(remaining_operands));
	 remaining_operands = cdr(remaining_operands)) {

	int multiplier = car(remaining_operands);

	multiplicand = mult(multiplicand, multiplier);
    }
    return (multiplicand);
}

int f_quotient(int arglist, int th __unused)
{
    int dividend;

    dividend = car(arglist);
    arglist = cdr(arglist);

    for (int remaining_operands = arglist;
	 !(IS_NIL(remaining_operands));
	 remaining_operands = cdr(remaining_operands)) {

	int divisor = car(remaining_operands);

	dividend = quotient(dividend, divisor);
    }
    return (dividend);
}

int f_smaller(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "<", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "<", arg1, th);
    if (!numberp(arg2))
	error(NOT_NUM, "<", arg2, th);

    if (smallerp(arg1, arg2))
	return (T);
    else
	return (NIL);
}

int f_eqsmaller(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "<=", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "<=", arg1, th);
    if (!numberp(arg2))
	error(NOT_NUM, "<=", arg2, th);

    if (eqsmallerp(arg1, arg2))
	return (T);
    else
	return (NIL);
}

int f_greater(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, ">", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, ">", arg1, th);
    if (!numberp(arg2))
	error(NOT_NUM, ">", arg2, th);

    if (greaterp(arg1, arg2))
	return (T);
    else
	return (NIL);
}


int f_eqgreater(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, ">=", arglist, th);
    if (length(arglist) != 2)
	error(WRONG_ARGS, ">=", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, ">=", arg1, th);
    if (!numberp(arg2))
	error(NOT_NUM, ">=", arg2, th);

    if (eqgreaterp(arg1, arg2))
	return (T);
    else
	return (NIL);
}

int f_sin(int arglist, int th)
{
    int arg1;
    double val;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "sin", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "sin", arg1, th);
    val = sin(GET_FLT(exact_to_inexact(arg1)));
    return (make_flt(val));
}

int f_cos(int arglist, int th)
{
    int arg1;
    double val;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "cos", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "cos", arg1, th);
    val = cos(GET_FLT(exact_to_inexact(arg1)));
    return (make_flt(val));
}

int f_tan(int arglist, int th)
{
    int arg1;
    double val;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "tan", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "tan", arg1, th);
    val = tan(GET_FLT(exact_to_inexact(arg1)));
    return (make_flt(val));
}

int f_atan(int arglist, int th)
{
    int arg1;
    double val;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "atan", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "atan", arg1, th);
    val = atan(GET_FLT(exact_to_inexact(arg1)));
    return (make_flt(val));
}

int f_sinh(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "sinh", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "sinh", arg1, th);

    double x, y;

    x = GET_FLT(exact_to_inexact(arg1));
    y = sinh(x);
    if (fabs(y) >= DBL_MAX)
	error(FLT_OVERF, "sinh", arg1, th);
    return (make_flt(y));
}

int f_cosh(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "cosh", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "cosh", arg1, th);

    double x, y;

    x = GET_FLT(exact_to_inexact(arg1));
    y = cosh(x);
    if (fabs(y) >= DBL_MAX)
	error(FLT_OVERF, "sinh", arg1, th);
    return (make_flt(y));
}

int f_tanh(int arglist, int th)
{
    int arg1;
    double val;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "tanh", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "tanh", arg1, th);

    val = GET_FLT(exact_to_inexact(arg1));
    val = tanh(val);
    return (make_flt(val));
}

int f_atanh(int arglist, int th)
{
    int arg1;
    double val;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "atanh", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "atanh", arg1, th);
    val = GET_FLT(exact_to_inexact(arg1));
    if (val >= 1.0 || val <= -1.0)
	error(FLT_OUT_OF_DOMAIN, "atanh", arg1, th);
    val = atanh(val);
    return (make_flt(val));
}

int f_floor(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "floor", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "floor", arg1, th);


    if (floatp(arg1)) {
	double x;

	x = floor(GET_FLT(arg1));
	if (x <= 999999999 && x >= -999999999)
	    return (make_int((int) x));
	else if ((long long int) x <= 999999999999999999
		 && (long long int) x >= -999999999999999999)
	    return (make_long((long long int) x));
	else
	    return (make_flt(x));
    } else
	return (arg1);
}

int f_ceiling(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "ceiling", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "ceiling", arg1, th);

    if (floatp(arg1)) {
	double x;

	x = GET_FLT(arg1);
	if (x <= 999999999.0 && x >= -999999999.0)
	    return (make_int((int) ceil(x)));
	else
	    return (make_long((long long int) (ceil(x))));
    } else
	return (arg1);
}

int f_truncate(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "truncate", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "truncate", arg1, th);

    if (floatp(arg1)) {
	double x;

	x = GET_FLT(arg1);
	if (x >= 0 && x <= 999999999.0)
	    return (make_int((int) floor(x)));
	else if (x > 999999999.0)
	    return (make_long((long long int) floor(x)));
	else if (x < 0 && x >= -999999999.0)
	    return (make_int((int) ceil(x)));
	else
	    return (make_long((long long int) ceil(x)));
    } else
	return (arg1);
}


int f_round(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "round", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "round", arg1, th);

    if (floatp(arg1)) {
	double x, f, c;

	x = GET_FLT(arg1);
	f = floor(x);
	c = ceil(x);
	if (x == (f + c) / 2)
	    if (fmod(f, 2.0) == 0.0)
		x = f;
	    else
		x = c;
	else
	    x = round(x);

	if (x <= 999999999.0 && x >= -999999999.0)
	    return (make_int((int) x));
	else if (x <= 999999999999999999.0 && x >= -999999999999999999.0)
	    return (make_long((long long int) x));
    } else
	return (arg1);

    return (NIL);
}

int f_gcd(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "gcd", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "gcd", arg1, th);
    if (!numberp(arg2))
	error(NOT_NUM, "gcd", arg2, th);


    return (gcd(arg1, arg2));
}

int f_lcm(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "lcm", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "lcm", arg1, th);
    if (!numberp(arg2))
	error(NOT_NUM, "lcm", arg2, th);

    return (lcm(arg1, arg2));
}

int f_max(int arglist, int th)
{
    int res;

    res = car(arglist);
    if (!numberp(res))
	error(NOT_NUM, "max", res, th);
    arglist = cdr(arglist);
    while (!nullp(arglist)) {
	int arg1;

	arg1 = car(arglist);
	if (!numberp(arg1))
	    error(NOT_NUM, "max", arg1, th);
	if (greaterp(arg1, res))
	    res = arg1;
	arglist = cdr(arglist);
    }
    return (res);
}

int f_min(int arglist, int th)
{
    int res;

    res = car(arglist);
    if (!numberp(res))
	error(NOT_NUM, "min", res, th);
    arglist = cdr(arglist);
    while (!nullp(arglist)) {
	int arg1;

	arg1 = car(arglist);
	if (!numberp(arg1))
	    error(NOT_NUM, "min", arg1, th);
	if (smallerp(arg1, res))
	    res = arg1;
	arglist = cdr(arglist);
    }
    return (res);

}

int f_float(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "float", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "float", arg1, th);
    return (exact_to_inexact(arg1));
}

int f_floatp(int arglist, int th)
{
    int arg;

    arg = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "floatp", arglist, th);
    if (IS_FLOAT(arg))
	return (T);
    else
	return (NIL);
}


int f_div(int arglist, int th)
{
    int arg1, arg2, q, r;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "div", arglist, th);
    if (!numberp(arg1))
	error(NOT_INT, "div", arg1, th);
    if (!numberp(arg2))
	error(NOT_INT, "div", arg2, th);
    if (zerop(arg2))
	error(DIV_ZERO, "div", arglist, th);

    q = divide(arg1, arg2);
    r = minus(arg1, mult(arg2, q));
    if (zerop(r))
	return (q);
    else if (positivep(arg1) && negativep(arg2))
	return (minus(q, make_int(1)));
    else if (negativep(arg1) && positivep(arg2))
	return (minus(q, make_int(1)));
    else
	return (q);
}

int f_integerp(int arglist, int th)
{
    int arg;

    arg = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "integerp", arglist, th);
    if (math_integerp(arg))
	return (T);
    else
	return (NIL);
}

int f_abs(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "abs", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "abs", arg1, th);
    return (absolute(arg1));
}

int f_mod(int arglist, int th)
{
    int arg1, arg2, div;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "mod", arglist, th);
    if (!integerp(arg1) && !longnump(arg1) && !bignump(arg1))
	error(NOT_INT, "mod", arg1, th);
    if (!integerp(arg2) && !longnump(arg2) && !bignump(arg2))
	error(NOT_INT, "mod", arg2, th);

    div = f_div(arglist, 0);
    return (minus(arg1, mult(arg2, div)));

}

int f_exp(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "exp", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "exp", arg1, th);

    double x, y;

    x = GET_FLT(exact_to_inexact(arg1));
    y = exp(x);

    if (y > DBL_MAX)
	error(FLT_OVERF, "exp", arg1, th);
    if (x < -DBL_MAX)
	error(FLT_UNDERF, "exp", arg1, th);
    return (make_flt(y));
}

int f_log(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "log", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "log", arg1, th);
    if (!positivep(arg1))
	error(OUT_OF_REAL, "log", arglist, th);

    return (make_flt(log(GET_FLT(exact_to_inexact(arg1)))));
}

int f_expt(int arglist, int th)
{
    int arg1, arg2, i;
    double x, y;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "expt", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "expt", arg1, th);
    if (!numberp(arg2))
	error(NOT_NUM, "expt", arg2, th);
    if (zerop(arg1) && negativep(arg2))
	error(IMPROPER_ARGS, "expt", arglist, th);
    if (zerop(arg1) && zerop(arg2) && floatp(arg2))
	error(IMPROPER_ARGS, "expt", arglist, th);
    if (negativep(arg1) && floatp(arg2))
	error(IMPROPER_ARGS, "expt", arglist, th);

    // If base is greater than 1 and exponent is infinite
    // signal overflow condition
    if (greaterp(arg1, make_int(1)) && floatp(arg2)
	&& GET_FLT(arg2) >= DBL_MAX)
	error(FLT_OVERF, "expt", arglist, th);

    // If base is greater than one and the exponent is negative infinite
    // signal underflow condition
    if (greaterp(arg1, make_int(1)) && floatp(arg2)
	&& GET_FLT(arg2) <= -DBL_MAX)
	error(FLT_UNDERF, "expt", arglist, th);

    // If base is infinite and the exponent is greater than one
    // signal overflow condition
    if (greaterp(arg2, make_int(1)) && floatp(arg1)
	&& GET_FLT(arg1) >= DBL_MAX)
	error(FLT_OVERF, "expt", arglist, th);

    // If base is infinite and exponent is negative
    // signal underflow condition
    if (negativep(arg2) && floatp(arg1) && GET_FLT(arg1) >= DBL_MAX)
	error(FLT_UNDERF, "expt", arglist, th);

    // BUG: This behavior should depend on whether the exponent is odd or even.
    // Even exponents should give an overflow condition
    // Odd exponents should give an underflow condition
    //
    // If base is negative infinite and exponent is integer greater than one
    // signal overflow condition
    if (greaterp(arg2, make_int(1)) && floatp(arg1)
	&& GET_FLT(arg1) <= -DBL_MAX)
	error(FLT_OVERF, "expt", arglist, th);

    // If base is negative infinite and exponent is negative 
    // signal underflow condition
    if (negativep(arg2) && floatp(arg1) && GET_FLT(arg1) <= -DBL_MAX)
	error(FLT_UNDERF, "expt", arglist, th);

    if ((integerp(arg1) || longnump(arg1) || bignump(arg1))
	&& integerp(arg2) && GET_INT(arg2) == 0)
	return (make_int(1));

    if (integerp(arg1) && GET_INT(arg1) == 1
	&& (floatp(arg2) || negativep(arg2)))
	return (make_flt(1.0));

    if (integerp(arg1) && GET_INT(arg1) == -1 && floatp(arg2)) {
	x = GET_FLT(arg2);
	if (x - ceil(x) == 0.0 && (int) x % 2 == 0)
	    return (make_flt(1.0));
	else
	    return (make_flt(-1.0));
    }
    if (integerp(arg1) && GET_INT(arg1) == -1 && integerp(arg2)) {
	i = GET_INT(arg2);
	if (i >= 0) {
	    if (i % 2 == 0)
		return (make_int(1));
	    else
		return (make_int(-1));
	} else {
	    if (i % 2 == 0)
		return (make_flt(1.0));
	    else
		return (make_flt(-1.0));
	}
    }
    if (integerp(arg1) && GET_INT(arg1) == -1
	&& (longnump(arg2) || bignump(arg2))) {
	int j, k;

	i = make_int(2);
	j = divide(arg2, i);
	k = minus(arg2, mult(j, i));
	if (positivep(arg2)) {
	    if (zerop(k))
		return (make_int(1));
	    else
		return (make_int(-1));
	} else {
	    if (zerop(k))
		return (make_flt(1.0));
	    else
		return (make_flt(-1.0));
	}
    }
    if ((integerp(arg1) || longnump(arg1) || bignump(arg1))
	&& (integerp(arg2) && GET_INT(arg2) > 0))
	return (expt(arg1, GET_INT(arg2)));

    if ((integerp(arg1) || floatp(arg1)) &&
	(integerp(arg2) || floatp(arg2))) {
	double z;

	arg1 = exact_to_inexact(arg1);
	arg2 = exact_to_inexact(arg2);
	x = GET_FLT(arg1);
	y = GET_FLT(arg2);
	z = pow(x, y);
	return (make_flt(z));
    }
    if (integerp(arg1)
	&& (integerp(arg2) || longnump(arg2) || bignump(arg2))) {
	if (GET_INT(arg1) == 1)
	    return (arg1);
	else if (GET_INT(arg1) == 0)
	    return (arg1);
	else if (GET_INT(arg1) == -1) {
	    if (zerop(s_remainder(arg2, make_int(2))))
		return (make_int(1));
	    else
		return (arg1);
	}
    }
    if (floatp(arg1) && (longnump(arg2) || bignump(arg2))) {
	if (GET_FLT(arg1) == 1.0)
	    return (arg1);
	else if (GET_FLT(arg1) == 0.0)
	    return (arg1);
	else if (GET_FLT(arg1) == -1.0) {
	    if (zerop(s_remainder(arg2, make_int(2))))
		return (make_flt(1.0));
	    else
		return (arg1);
	}
    }
    if (longnump(arg1) && integerp(arg2)) {
	if (GET_INT(arg2) == 1) {
	    x = GET_FLT(exact_to_inexact(arg1));
	    y = x;
	    return (make_flt(y));
	} else if (GET_INT(arg2) == 2) {
	    x = GET_FLT(exact_to_inexact(arg1));
	    y = x * x;
	    return (make_flt(y));
	} else if (GET_INT(arg2) == -1) {
	    x = GET_FLT(exact_to_inexact(arg1));
	    y = 1.0 / x;
	    return (make_flt(y));
	} else if (GET_INT(arg2) == -2) {
	    x = GET_FLT(exact_to_inexact(arg1));
	    y = 1.0 / (x * x);
	    return (make_flt(y));
	}
    }
    if (longnump(arg1) && floatp(arg2)) {
	if (GET_FLT(arg2) == 0.0) {
	    return (make_flt(1.0));
	} else if (GET_FLT(arg2) == 1.0) {
	    x = GET_FLT(exact_to_inexact(arg1));
	    y = x;
	    return (make_flt(y));
	} else if (GET_FLT(arg2) == 2.0) {
	    x = GET_FLT(exact_to_inexact(arg1));
	    y = x * x;
	    return (make_flt(y));
	} else if (GET_FLT(arg2) == -1.0) {
	    x = GET_FLT(exact_to_inexact(arg1));
	    y = 1.0 / x;
	    return (make_flt(y));
	} else if (GET_FLT(arg2) == -2.0) {
	    x = GET_FLT(exact_to_inexact(arg1));
	    y = 1.0 / (x * x);
	    return (make_flt(y));
	}
    }
    if (positivep(arg2))
	error(FLT_OVERF, "expt", arglist, th);
    else
	error(FLT_UNDERF, "expt", arglist, th);
    return (UNDEF);
}

int expt(int x, int y)
{
    int res, p;

    res = make_int(1);
    p = x;
    while (y > 0) {
	if ((y % 2) == 0) {
	    p = mult(p, p);
	    y = y / 2;
	} else {
	    res = mult(res, p);
	    y = y - 1;
	}
    }
    return (res);
}


int f_sqrt(int arglist, int th)
{
    int arg1;
    double x;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "sqrt", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "sqrt", arg1, th);
    if (negativep(arg1))
	error(OUT_OF_DOMAIN, "sqrt", arg1, th);

    x = sqrt(GET_FLT(exact_to_inexact(arg1)));
    if ((integerp(arg1) || longnump(arg1) || bignump(arg1))
	&& ceil(x) == floor(x)) {
	if (x <= 999999999.0)
	    return (make_int((int) x));
	else if (x <= 999999999999999999.0)
	    return (make_long((long long int) x));
	else
	    return (make_flt(x));
    } else
	return (make_flt(x));
}


int f_isqrt(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "isqrt", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "isqrt", arg1, th);
    if (negativep(arg1))
	error(OUT_OF_DOMAIN, "isqrt", arg1, th);
    return (isqrt(arg1));
}

int f_atan2(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "atan2", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "atan2", arg1, th);
    if (!numberp(arg2))
	error(NOT_NUM, "atan2", arg2, th);
    return (angle(arg1, arg2));
}

int f_reciprocal(int arglist, int th)
{
    int arg1;
    double val;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "reciprocal", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "reciprocal", arg1, th);

    val = GET_FLT(exact_to_inexact(arg1));
    if (val == 0.0)
	error(DIV_ZERO, "reciprocal", arg1, th);
    if (fabs(val) > DBL_MAX)
	error(FLT_UNDERF, "reciprocal", arg1, th);
    if (fabs(val) < DBL_MIN)
	error(FLT_OVERF, "reciprocal", arg1, th);
    return (quotient(make_int(1), arg1));
}

int f_numeqp(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "=", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "=", arg1, th);
    if (!numberp(arg2))
	error(NOT_NUM, "=", arg2, th);

    if (numeqp(arg1, arg2))
	return (T);
    else
	return (NIL);
}

int f_notnumeqp(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "/=", arglist, th);
    if (!numberp(arg1))
	error(NOT_NUM, "/=", arg1, th);
    if (!numberp(arg2))
	error(NOT_NUM, "/=", arg2, th);

    if (numeqp(arg1, arg2))
	return (NIL);
    else
	return (T);
}


/* list function */
int f_car(int arglist, int th)
{
    int arg;

    arg = car(arglist);
    if (!(IS_LIST(arg)))
	error(NOT_CONS, "car", arg, th);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "car", arglist, th);
    return (car(arg));
}

int f_cdr(int arglist, int th)
{
    int arg;

    arg = car(arglist);
    if (!(IS_LIST(arg)))
	error(NOT_CONS, "cdr", arg, th);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "cdr", arglist, th);
    return (cdr(arg));
}

int f_cons(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "cons", arglist, th);
    return (cons(arg1, arg2));
}

int f_eq(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "eq", arglist, th);
    if (eqp(arg1, arg2))
	return (T);
    else
	return (NIL);
}

int f_eql(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "eql", arglist, th);
    if (eqlp(arg1, arg2))
	return (T);
    else
	return (NIL);
}

int f_equal(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "equal", arglist, th);
    if (equalp(arg1, arg2))
	return (T);
    else
	return (NIL);
}

int f_not(int arglist, int th)
{
    int arg;

    arg = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "not", arglist, th);
    if (IS_NIL(arg))
	return (T);
    else
	return (NIL);
}

int f_nullp(int arglist, int th)
{
    int arg;

    arg = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "not", arglist, th);
    if (nullp(arg))
	return (T);
    else
	return (NIL);
}

int f_atomp(int arglist, int th)
{
    int arg;

    arg = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "atom", arglist, th);
    if (atomp(arg))
	return (T);
    else
	return (NIL);
}

int f_functionp(int arglist, int th)
{
    int arg;

    arg = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "functionp", arglist, th);
    if (IS_FUNC(arg) || IS_SUBR(arg) || IS_GENERIC(arg)
	|| IS_COMPILED(arg))
	return (T);
    else
	return (NIL);
}

int f_consp(int arglist, int th)
{
    int arg;

    arg = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "consp", arglist, th);
    if (IS_LIST(arg))
	return (T);
    else
	return (NIL);
}


int f_list(int arglist, int th __unused)
{
    return (list(arglist));
}

int f_append(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (!listp(arg1))
	error(NOT_CONS, "append", arg1, th);
    if (length(arg1) >= fc[th]) {
	shelter_push(arglist, th);
	(void) gbc();
	shelter_pop(th);
    }
    if (nullp(arglist))
	return (NIL);
    else if (nullp(cdr(arglist)))
	return (car(arglist));
    else if (nullp(arg1))
	return (f_append(cdr(arglist), th));
    else
	return (append(car(arglist), f_append(cdr(arglist), th)));


}


int f_reverse(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "reverse", arglist, th);
    if (!listp(arg1))
	error(NOT_LIST, "reverse", arg1, th);
    return (reverse(arg1));
}

int f_nreverse(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "nreverse", arglist, th);
    if (!listp(arg1))
	error(NOT_LIST, "nreverse", arg1, th);
    return (nreverse(arg1));
}

int nreverse(int x)
{
    int res;

    res = NIL;
    while (!nullp(x) && !atomp(x)) {
	int y;

	y = cdr(x);
	SET_CDR(x, res);
	res = x;
	x = y;
    }
    return (res);
}

int f_create_list(int arglist, int th)
{
    int arg1, arg2, n;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if ((n = length(arglist)) != 1 && n != 2)
	error(WRONG_ARGS, "create-list", arglist, th);
    if (longnump(arg1) || bignump(arg1))
	error(MALLOC_OVERF, "create-list", arg1, th);
    if (!integerp(arg1))
	error(NOT_INT, "create-list", arg1, th);
    if (GET_INT(arg1) < 0)
	error(NOT_POSITIVE, "create-list", arg1, th);
    if (nullp(arg2))
	arg2 = UNDEF;
    return (create_list(GET_INT(arg1), arg2));
}

int create_list(int x, int y)
{
    if (x == 0)
	return (NIL);
    else
	return (cons(copy(y), create_list(x - 1, y)));
}


int f_length(int arglist, int th)
{
    int arg;

    arg = car(arglist);
    if (!nullp(cdr(arglist)))
	error(WRONG_ARGS, "length", arglist, th);
    if (!listp(arg) && !vectorp(arg) && !stringp(arg))
	error(ILLEGAL_ARGS, "length", arg, th);

    if (listp(arg))
	return (make_int(length(arg)));
    else if (vectorp(arg))
	return (make_int(vector_length(arg)));
    else
	return (make_int(string_length(arg)));

}


int f_set_car(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "set-car", arglist, th);
    if (!(IS_LIST(arg2)))
	error(NOT_CONS, "set-car", arg2, th);
    SET_CAR(arg2, arg1);
    return (arg1);
}

int f_set_cdr(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "set-cdr", arglist, th);
    if (!(IS_LIST(arg2)))
	error(NOT_CONS, "set-cdr", arg2, th);
    SET_CDR(arg2, arg1);
    return (arg1);
}


/* predicate */
int f_symbolp(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "symbolp", arglist, th);
    if (symbolp(arg1))
	return (T);
    else
	return (NIL);
}

int f_numberp(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "numberp", arglist, th);
    if (numberp(arg1))
	return (T);
    else
	return (NIL);
}

int f_listp(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "listp", arglist, th);
    if (listp(arg1))
	return (T);
    else
	return (NIL);
}


int f_member(int arglist, int th __unused)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);

    return (member(arg1, arg2));
}

int f_assoc(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "assoc", arglist, th);
    if (!listp(arg2))
	error(NOT_LIST, "assoc", arg2, th);
    if (!assoc_list_p(arg2))
	error(IMPROPER_ARGS, "assoc", arg2, th);

    return (assoc(arg1, arg2));
}


/* map function */
int f_mapcar(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);

    if (!(IS_FUNC(arg1)) && !(IS_SUBR(arg1)) && !(IS_COMPILED(arg1)))
	error(NOT_FUNC, "mapcar", arg1, th);
    return (mapcar(arg1, arg2, th));
}


int mapcar(int x, int y, int th)
{
    int ls, res, car, cdr;

    ls = y;
    shelter_push(y, th);
    if (nullp(ls) || member(NIL, ls)) {
	res = NIL;
    } else {
	car = apply(x, each_car(y), th);
	cdr = mapcar(x, each_cdr(y), th);
	res = cons(car, cdr);
    }
    shelter_pop(th);
    return res;
}

int each_car(int x)
{
    REQUIRE(GET_TAG(x) == LIS || GET_TAG(x) == SYM);
    if (nullp(x))
	return (NIL);
    else
	return (cons(caar(x), each_car(cdr(x))));
}

int each_cdr(int x)
{
    REQUIRE(GET_TAG(x) == LIS || GET_TAG(x) == SYM);
    if (nullp(x))
	return (NIL);
    else
	return (cons(cdar(x), each_cdr(cdr(x))));
}


int f_mapc(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);

    if (!(IS_FUNC(arg1)) && !(IS_SUBR(arg1)) && !(IS_COMPILED(arg1)))
	error(NOT_FUNC, "mapc", arg1, th);

    return (mapc(arg1, arg2, th));
}

int mapc(int x, int y, int th)
{
    int ls;

    ls = y;
    shelter_push(y, th);
    while (!member(NIL, ls)) {
	shelter_push(ls, th);
	apply(x, each_car(ls), th);
	shelter_pop(th);
	ls = each_cdr(ls);
    }
    shelter_pop(th);
    return (car(y));
}

int f_maplist(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);

    if (!(IS_FUNC(arg1)) && !(IS_SUBR(arg1)) && !(IS_COMPILED(arg1)))
	error(NOT_FUNC, "maplist", arg1, th);

    return (maplist(arg1, arg2));
}


int maplist(int x, int y)
{
    if (member(NIL, y))
	return (NIL);
    else
	return (cons(apply(x, y, 0), maplist(x, maplist1(y))));
}

int maplist1(int y)
{
    int res;

    res = NIL;
    while (y != NIL) {
	if (car(y) == NIL)
	    return (NIL);
	res = cons(cdar(y), res);
	y = cdr(y);
    }
    return (reverse(res));
}


int f_mapl(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if (!(IS_FUNC(arg1)) && !(IS_SUBR(arg1)) && !(IS_COMPILED(arg1)))
	error(NOT_FUNC, "mapl", arg1, th);

    return (mapl(arg1, arg2));
}

int mapl(int x, int y)
{
    int res;

    res = y;
    while (!member(NIL, y)) {
	apply(x, y, 0);
	y = maplist1(y);
    }
    return (car(res));
}


int f_mapcon(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);

    if (!(IS_FUNC(arg1)) && !(IS_SUBR(arg1)) && !(IS_COMPILED(arg1)))
	error(NOT_FUNC, "mapcon", arg1, th);

    return (mapcon(arg1, arg2));
}

int mapcon(int x, int y)
{
    int res;

    if (member(NIL, y))
	return (NIL);
    res = apply(x, y, 0);
    y = maplist1(y);
    while (!member(NIL, y)) {
	res = nconc(res, apply(x, y, 0));
	y = maplist1(y);
    }
    return (res);
}

int f_mapcan(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if (!(IS_FUNC(arg1)) && !(IS_SUBR(arg1)) && !(IS_COMPILED(arg1)))
	error(NOT_FUNC, "mapcan", arg1, th);
    return (mapcan(arg1, arg2));
}


int mapcan(int x, int y)
{
    int res;

    if (member(NIL, y))
	return (NIL);
    res = apply(x, each_car(y), 0);
    y = each_cdr(y);
    while (!member(NIL, y)) {
	res = nconc(res, apply(x, each_car(y), 0));
	y = each_cdr(y);
    }
    return (res);
}

int f_map_into(int arglist, int th)
{
    int arg1, arg2, arg3, arg4, val, i, res;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = cddr(arglist);

    arg4 = NIL;
    if (listp(arg1) && nullp(arg3))
	arg4 = arg1;
    else if (listp(arg1))
	arg4 = map_into_to_list(arg3);
    else if (vectorp(arg1) && nullp(arg3))
	arg4 = vector_to_list(arg1);
    else if (vectorp(arg1))
	arg4 = map_into_to_list(arg3);
    else if (stringp(arg1) && nullp(arg3))
	arg4 = string_to_list(arg1);
    else if (stringp(arg1))
	arg4 = map_into_to_list(arg3);
    else
	error(ILLEGAL_ARGS, "map-into", arg1, th);

    if (IS_FUNC(arg2) && GET_OPT(arg2) == 0)	/* when arg2 is thunk (lambda () ...) */
	val = map_into_thunk(arg2, arg4);
    else
	val = mapcar(arg2, arg4, th);

    res = arg1;
    if (listp(arg1)) {
	while (!nullp(val)) {
	    SET_CAR(res, car(val));
	    res = cdr(res);
	    val = cdr(val);
	}
    } else if (vectorp(arg1)) {
	if (nullp(val))		/* when val is null return arg1 */
	    return (arg1);
	i = 0;
	while (!nullp(val)) {
	    SET_VEC_ELT(res, i, car(val));
	    i++;
	    val = cdr(val);
	}
    } else if (stringp(arg1)) {
	if (nullp(val))		/* when val is null return arg1 */
	    return (arg1);
	i = 0;
	while (!nullp(val)) {
	    if (!charp(car(val)))	/* when val is not char list return arg1 */
		return (arg1);
	    STRING_SET(res, i, GET_CHAR(car(val)));
	    i++;
	    val = cdr(val);
	}
    }
    if (find_env(arg1, th) != FAILSE)
	set_lex_env(arg1, res, th);
    else if (GET_OPT(arg1) == GLOBAL)
	SET_CDR(arg1, res);
    return (arg1);
}

int map_into_thunk(int x, int y)
{
    int temp;
    if (nullp(y))
	return (NIL);
    else {
	temp = apply(x, NIL, 0);
	return (cons(temp, map_into_thunk(x, cdr(y))));
    }
}

int map_into_to_list(int x)
{
    if (nullp(x))
	return (NIL);
    else if (listp(car(x)))
	return (cons(car(x), map_into_to_list(cdr(x))));
    else if (vectorp(car(x)))
	return (cons(vector_to_list(car(x)), map_into_to_list(cdr(x))));
    else if (stringp(car(x)))
	return (cons(string_to_list(car(x)), map_into_to_list(cdr(x))));
    else {
	error(ILLEGAL_ARGS, "map-into", x, 0);
	return (NIL);
    }
}

/* property */
int f_property(int arglist, int th)
{
    int arg1, arg2, arg3, res, n;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if ((n = length(arglist)) != 2 && n != 3)
	error(ILLEGAL_ARGS, "property", arglist, th);
    if (!symbolp(arg1))
	error(NOT_SYM, "property", arg1, th);

    res = assoc(arg2, GET_PROP(arg1));
    if (res == 0)
	return (arg3);
    else
	return (cdr(res));
}

int f_set_property(int arglist, int th __unused)
{
    int arg1, arg2, arg3, res;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    res = assoc(arg3, GET_PROP(arg2));
    if (nullp(res))
	SET_PROP(arg2, cons(cons(arg3, arg1), GET_PROP(arg2)));
    else
	SET_CDR(res, arg1);
    return (arg1);
}

int f_remove_property(int arglist, int th)
{
    int arg1, arg2, val;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "remove-property", arglist, th);
    if (!symbolp(arg1))
	error(NOT_SYM, "remove-property", arg1, th);

    val = assoc(arg2, GET_PROP(arg1));
    if (nullp(val))
	return (NIL);
    else {
	int res;

	res = cdr(val);
	SET_PROP(arg1, remove_prop(arg2, GET_PROP(arg1)));
	return (res);
    }
}

int remove_prop(int x, int lis)
{

    if (car(car(lis)) == x)
	return (cdr(lis));
    else
	return (cons(car(lis), remove_prop(x, cdr(lis))));
}

int f_gensym(int arglist __unused, int th __unused)
{
    int res;
    char str[SYMSIZE];

    sprintf(str, "#:G%d", genint);
    genint++;
    res = make_sym(str);
    return (res);
}

/* input and output */
static inline bool save_repl_flag(void)
{
    bool result = repl_flag;
    repl_flag = false;
    return result;

}

static inline void restore_repl_flag(bool save)
{
    repl_flag = save;
}

int f_read(int arglist, int th)
{
    int arg1, arg2, arg3, save, n, res;
    bool save1;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if ((n = length(arglist)) > 3)
	error(WRONG_ARGS, "read", arglist, th);
    if (n > 0 && !input_stream_p(arg1))
	error(NOT_IN_STREAM, "read", arg1, th);

    save1 = save_repl_flag();
    if (n == 0)
	res = sread();
    else if (n == 1) {
	save = input_stream;
	input_stream = arg1;
	res = sread();
	input_stream = save;
	if (res == FEND) {
	    restore_repl_flag(save1);
	    error(END_STREAM, "read", NIL, th);
	}

    } else {
	save = input_stream;
	input_stream = arg1;
	res = sread();
	input_stream = save;
	if (res == FEND) {
	    restore_repl_flag(save1);
	    if (nullp(arg2) && n == 2)
		return (arg2);
	    else if (nullp(arg2) && n == 3)
		return (arg3);
	    else
		error(END_STREAM, "read", NIL, th);
	}
    }
    restore_repl_flag(save1);
    return (res);
}

int f_read_char(int arglist, int th)
{
    int arg1, arg2, arg3, save, n, res;
    int rc_buf[CHARSIZE];
    bool save1;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if ((n = length(arglist)) > 3)
	error(WRONG_ARGS, "read-char", arglist, th);
    if (GET_PROF(arg1) == EISL_CLOSE)
	error(CANT_OPEN, "read-char", arg1, th);
    if (n > 0 && !text_input_stream_p(arg1))
	error(NOT_IN_STREAM, "read-char", arg1, th);

    save1 = save_repl_flag();
    if (n == 0) {
	rc_buf[0] = readc();
	rc_buf[1] = NUL;
	res = make_char((char *) rc_buf);
    } else if (n == 1) {
	save = input_stream;
	input_stream = arg1;
	rc_buf[0] = readc();
	rc_buf[1] = NUL;
	if (rc_buf[0] == EOF) {
	    restore_repl_flag(save1);
	    input_stream = save;
	    error(END_STREAM, "read-char", NIL, th);
	}
	input_stream = save;
	res = make_char((char *) rc_buf);
    } else {
	save = input_stream;
	input_stream = arg1;
	rc_buf[0] = readc();
	rc_buf[1] = NUL;
	input_stream = save;
	if (rc_buf[0] == EOF) {
	    restore_repl_flag(save1);
	    input_stream = save;
	    if (nullp(arg2) && n == 2)
		return (arg2);
	    else if (nullp(arg2) && n == 3)
		return (arg3);
	    else
		error(END_STREAM, "read-char", NIL, th);
	}
	res = make_char((char *) rc_buf);
    }
    restore_repl_flag(save1);
    return (res);
}

int f_read_byte(int arglist, int th)
{
    int arg1, arg2, arg3, save, n, res;
    bool save1;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if ((n = length(arglist)) > 3)
	error(WRONG_ARGS, "read-byte", arglist, th);
    if (n > 0 && !binary_input_stream_p(arg1))
	error(NOT_IN_STREAM, "read-byte", arg1, th);

    save1 = save_repl_flag();
    if (n == 0) {
	res = readc();
    } else if (n == 1) {
	save = input_stream;
	input_stream = arg1;
	res = readc();
	if (res == EOF) {
	    restore_repl_flag(save1);
	    input_stream = save;
	    error(END_STREAM, "read-byte", NIL, th);
	}
	input_stream = save;
    } else {
	save = input_stream;
	input_stream = arg1;
	res = readc();
	input_stream = save;
	if (res == EOF) {
	    restore_repl_flag(save1);
	    input_stream = save;
	    if (nullp(arg2) && n == 2)
		return (arg2);
	    else if (nullp(arg2) && n == 3)
		return (arg3);
	    else
		error(END_STREAM, "read-byte", NIL, th);
	}
    }
    restore_repl_flag(save1);
    return (make_int(res));
}



int f_preview_char(int arglist, int th)
{
    int arg1, arg2, arg3, save, n, res;
    int pc_buf[CHARSIZE];

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if ((n = length(arglist)) > 3)
	error(WRONG_ARGS, "preview-char", arglist, th);
    if (n > 0 && !input_stream_p(arg1))
	error(NOT_IN_STREAM, "preview-char", arg1, th);

    if (n == 0) {
	pc_buf[0] = readc();
	pc_buf[1] = NUL;
	unreadc(pc_buf[0]);
	res = make_char((char *) pc_buf);
    } else if (n == 1) {
	save = input_stream;
	input_stream = arg1;
	pc_buf[0] = readc();
	pc_buf[1] = NUL;
	if (pc_buf[0] != EOF)
	    unreadc(pc_buf[0]);
	if (pc_buf[0] == EOF) {
	    input_stream = save;
	    error(END_STREAM, "preview-char", NIL, th);
	}
	input_stream = save;
	res = make_char((char *) pc_buf);
    } else {
	save = input_stream;
	input_stream = arg1;
	pc_buf[0] = readc();
	pc_buf[1] = NUL;
	if (pc_buf[0] != EOF)
	    unreadc(pc_buf[0]);
	if (pc_buf[0] == EOF) {
	    input_stream = save;
	    if (nullp(arg2) && n == 2)
		return (arg2);
	    else if (nullp(arg2) && n == 3)
		return (arg3);
	    else
		error(END_STREAM, "preview-char", NIL, th);

	}
	input_stream = save;
	res = make_char((char *) pc_buf);
    }
    return (res);
}

int f_read_line(int arglist, int th)
{
    int arg1, arg2, arg3, n, pos, save, res, c;
    char rl_buf[LINE_MAX];
    bool save1;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if ((n = length(arglist)) > 3)
	error(WRONG_ARGS, "read-line", arglist, th);
    if (n > 0 && !text_input_stream_p(arg1))
	error(NOT_IN_STREAM, "read-line", arg1, th);

    save1 = save_repl_flag();
    if (n == 0) {
	pos = 0;
	c = readc();
	while (c != EOL) {
	    rl_buf[pos] = c;
	    pos++;
	    c = readc();
	}
	rl_buf[pos] = NUL;
	res = make_str(rl_buf);
    } else if (n == 1) {
	pos = 0;
	save = input_stream;
	input_stream = arg1;
	c = readc();
	if (c == EOF) {
	    input_stream = save;
	    restore_repl_flag(save1);
	    error(END_STREAM, "read-line", NIL, th);
	}
	while (c != EOL && c != EOF) {
	    rl_buf[pos] = c;
	    pos++;
	    c = readc();
	}
	rl_buf[pos] = NUL;
	input_stream = save;
	res = make_str(rl_buf);
    } else {
	pos = 0;
	save = input_stream;
	input_stream = arg1;
	c = readc();
	if (c == EOF) {
	    restore_repl_flag(save1);
	    if (nullp(arg2) && n == 2) {
		input_stream = save;
		return (arg2);
	    } else if (nullp(arg2) && n == 3) {
		input_stream = save;
		return (arg3);
	    } else {
		input_stream = save;
		error(END_STREAM, "read-line", NIL, th);
	    }
	}

	while (c != EOL && c != EOF) {
	    rl_buf[pos] = c;
	    pos++;
	    c = readc();
	}
	rl_buf[pos] = NUL;
	input_stream = save;
	res = make_str(rl_buf);
	if (res == FEND && arg2 == NIL)
	    res = arg3;
    }
    restore_repl_flag(save1);
    return (res);
}



int f_load(int arglist, int th)
{
    int arg1, i, exp;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "load", arglist, th);
    if (!stringp(arg1))
	error(NOT_STR, "load", arg1, th);

    if (!process_flag)
	load(arg1, th);
    else {
	// when process_flag == true, sread() use read_stdin.
	// To avoid this problem, change process_flag temporarily.
	process_flag = false;
	load(arg1, th);
	process_flag = true;
    }

    // only parent lisp sends message (load fn) to child lisps.
    if (!process_flag && process_pt > 0) {
	exp = list2(make_sym("load"), arg1);

	for (i = 0; i < process_pt; i++) {
	    write_to_pipe(i, sexp_to_str(exp));
	    read_from_pipe(i);
	}
    }

    return (T);
}

void load(int arg1, int th)
{
    int save1, n;
    bool save2;
    char str[PATH_MAX];

    // object file ex "foo.o"
    n = strlen(GET_NAME(arg1));
    strncpy(str, GET_NAME(arg1), PATH_MAX - 1);
    str[PATH_MAX - 1] = '\0';
    if (str[n - 1] == 'o' && str[n - 2] == '.') {
	dynamic_link(arg1);
	return;
    }
    // text file
    save1 = input_stream;
    save2 = save_repl_flag();
    const char *fname = GET_NAME(arg1);
    input_stream =
	make_stm(fopen(fname, "r"), EISL_INPUT, Str_dup(fname, 1, 0, 1));

    if (GET_PORT(input_stream) == NULL) {
	input_stream = save1;
	restore_repl_flag(save2);
	error(CANT_OPEN, "load", arg1, th);
    }
    open_flag = true;
    line = 1;
    column = 0;
    if (looking_for_shebang) {
	FILE *infile = GET_PORT(input_stream);
	int ch = fgetc(infile);
	switch (ch) {
	case EOF:
	    goto cleanup;
	case '#':
	    ch = fgetc(infile);
	    if (ch != '!' || ch == EOF) {
		goto cleanup;
	    }
	    while (ch != '\n' && ch != EOF) {
		ch = fgetc(infile);
	    }
	    if (ch == EOF) {
		goto cleanup;
	    }
	    break;
	default:
	    ungetc(ch, infile);
	}
	looking_for_shebang = false;
    }
    while (1) {
	int sexp;

	sexp = sread();
	if (sexp == FEND)
	    break;
	top_flag = true;
	restore_repl_flag(save2);
	eval(sexp, th);
	save2 = save_repl_flag();
    }
  cleanup:
    open_flag = false;
    fclose(GET_PORT(input_stream));
    input_stream = save1;
    restore_repl_flag(save2);
    if (redef_flag)
	redef_generic();
    return;
}

int f_print(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "print", arglist, th);
    print(arg1);
    putchar('\n');
    return (NIL);
}



int f_standard_input(int arglist, int th)
{
    if (!nullp(arglist))
	error(WRONG_ARGS, "standard-input", arglist, th);
    return (standard_input);
}

int f_standard_output(int arglist, int th)
{
    if (!nullp(arglist))
	error(WRONG_ARGS, "standard-output", arglist, th);
    return (standard_output);
}

int f_error_output(int arglist, int th)
{
    if (!nullp(arglist))
	error(WRONG_ARGS, "error-output", arglist, th);
    return (standard_error);
}

int f_streamp(int arglist, int th)
{
    int arg;

    arg = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "streamp", arglist, th);
    if (streamp(arg))
	return (T);
    else
	return (NIL);
}

int f_open_stream_p(int arglist, int th)
{
    int arg;

    arg = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "open-stream-p", arglist, th);

    if (streamp(arg) && GET_PROF(arg) == EISL_OPEN)
	return (T);
    else
	return (NIL);
}

int f_input_stream_p(int arglist, int th)
{
    int arg;

    arg = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "input-stream-p", arglist, th);
    if (input_stream_p(arg))
	return (T);
    else
	return (NIL);
}

int f_output_stream_p(int arglist, int th)
{
    int arg;

    arg = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "output-stream-p", arglist, th);
    if (output_stream_p(arg))
	return (T);
    else
	return (NIL);
}

int f_stream_ready_p(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "stream-ready-p", arglist, th);
    if (!input_stream_p(arg1))
	error(NOT_STREAM, "stream-ready-p", arg1, th);
    if (GET_PROF(arg1) == EISL_CLOSE)
	error(CANT_OPEN, "stream-ready-p", arg1, th);

    if (input_stream_p(arg1)) {
	int save, c;

	save = input_stream;
	input_stream = arg1;
	c = readc();
	if (c == EOF) {
	    input_stream = save;
	    if (string_input_stream_p(arg1))
		return (NIL);
	    else
		error(NOT_STREAM, "stream-ready-p", NIL, th);
	}
	unreadc(c);
	input_stream = save;
	return (T);
    }
    return (NIL);
}

/* evaluation function */
int f_eval(int arglist, int th)
{
    int arg1, len;

    arg1 = car(arglist);
    len = length(arglist);
    if (len != 1)
	error(WRONG_ARGS, "eval", arglist, th);

    return (eval(arg1, th));
}

int f_apply(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if (!(IS_FUNC(arg1)) && !(IS_SUBR(arg1)) && !(IS_COMPILED(arg1)))
	error(NOT_FUNC, "apply", arg1, th);
    if (!listp(last(arg2)))
	error(NOT_LIST, "apply", last(arg2), th);

    return (apply(arg1, bind_args(arg2), th));
}

int bind_args(int x)
{
    if (nullp(cdr(x))) {
	if (improper_list_p(car(x)))
	    error(ILLEGAL_ARGS, "apply", car(x), 0);
	return (car(x));
    } else
	return (cons(car(x), bind_args(cdr(x))));
}

int f_funcall(int arglist, int th)
{
    int arg1, arg2, res;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if (!(IS_FUNC(arg1)) && !(IS_SUBR(arg1)) && !(IS_COMPILED(arg1)))
	error(NOT_FUNC, "funcall", arg1, th);
    res = apply(arg1, arg2, th);
    return (res);
}



/* character function */
int f_characterp(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "characterp", arglist, th);
    if (charp(arg1))
	return (T);
    else
	return (NIL);
}



int f_char_eqp(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "char=", arglist, th);
    if (!charp(arg1))
	error(NOT_CHAR, "char=", arg1, th);
    if (!charp(arg2))
	error(NOT_CHAR, "char=", arg2, th);


    if (SAME_NAME(arg1, arg2))
	return (T);
    else
	return (NIL);
}

int f_char_noteqp(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "char/=", arglist, th);
    if (!charp(arg1))
	error(NOT_CHAR, "char/=", arg1, th);
    if (!charp(arg2))
	error(NOT_CHAR, "char/=", arg2, th);


    if (SAME_NAME(arg1, arg2))
	return (NIL);
    else
	return (T);
}

static inline bool SMALLER_NAME(int addr1, int addr2)
{
    return (strcmp(heap[addr1].name, heap[addr2].name) < 0);
}

int f_char_smallerp(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "char<", arglist, th);
    if (!charp(arg1))
	error(NOT_CHAR, "char<", arg1, th);
    if (!charp(arg2))
	error(NOT_CHAR, "char<", arg2, th);


    if (SMALLER_NAME(arg1, arg2))
	return (T);
    else
	return (NIL);
}

int f_char_eqsmallerp(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "char<=", arglist, th);
    if (!charp(arg1))
	error(NOT_CHAR, "char<=", arg1, th);
    if (!charp(arg2))
	error(NOT_CHAR, "char<=", arg2, th);

    if (SMALLER_NAME(arg1, arg2) || SAME_NAME(arg1, arg2))
	return (T);
    else
	return (NIL);
}

static inline bool GREATER_NAME(int addr1, int addr2)
{
    return (strcmp(heap[addr1].name, heap[addr2].name) > 0);
}

int f_char_greaterp(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "char>", arglist, th);
    if (!charp(arg1))
	error(NOT_CHAR, "char>", arg1, th);
    if (!charp(arg2))
	error(NOT_CHAR, "char>", arg2, th);

    if (GREATER_NAME(arg1, arg2))
	return (T);
    else
	return (NIL);
}

int f_char_eqgreaterp(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "char>=", arglist, th);
    if (!charp(arg1))
	error(NOT_CHAR, "char>=", arg1, th);
    if (!charp(arg2))
	error(NOT_CHAR, "char>=", arg2, th);

    if (GREATER_NAME(arg1, arg2) || SAME_NAME(arg1, arg2))
	return (T);
    else
	return (NIL);
}

int f_char_index(int arglist, int th)
{
    int arg1, arg2, arg3, n, i, j, len;
    char c;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if ((n = length(arglist)) != 2 && n != 3)
	error(WRONG_ARGS, "char-index", arglist, th);
    if (!charp(arg1))
	error(NOT_CHAR, "char-index", arg1, th);
    if (!stringp(arg2))
	error(NOT_STR, "char-index", arg2, th);
    if (n == 3 && negativep(arg3))
	error(NOT_POSITIVE, "char-index", arg3, th);
    if (n == 3 && !integerp(arg3))
	error(WRONG_ARGS, "char-index", arg3, th);
    if (n == 3 && GET_INT(arg3) >= string_length(arg2))
	error(WRONG_ARGS, "char-index", arg3, th);


    if (string_length(arg2) == 0)
	return (NIL);

    if (arg3 != NIL)
	j = GET_INT(arg3);
    else
	j = 0;

    c = GET_CHAR(arg1);
    len = strlen(GET_NAME(arg2));
    for (i = j; i < len; i++) {
	if (STRING_REF(arg2, i) == c)
	    break;
    }
    if (i < len)
	return (make_int(i));
    else
	return (NIL);
}


/* string function */
int f_stringp(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "stringp", arglist, th);
    if (stringp(arg1))
	return (T);
    else
	return (NIL);
}

int f_string_eqp(int arglist, int th)
{
    int arg1, arg2;

    if (length(arglist) != 2)
	error(WRONG_ARGS, "string=", arglist, th);
    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (!stringp(arg1))
	error(NOT_STR, "string=", arg1, th);
    if (!stringp(arg2))
	error(NOT_STR, "string=", arg2, th);
    if (SAME_NAME(arg1, arg2))
	return (T);
    else
	return (NIL);
}

int f_string_noteqp(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "string=", arglist, th);
    if (!stringp(arg1))
	error(NOT_STR, "string=", arg1, th);
    if (!stringp(arg2))
	error(NOT_STR, "string=", arg2, th);
    if (SAME_NAME(arg1, arg2))
	return (NIL);
    else
	return (T);
}

int f_elt(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "elt", arglist, th);
    if (!integerp(arg2) && !longnump(arg2))
	error(NOT_INT, "elt", arg2, th);
    if (negativep(arg2))
	error(OUT_OF_DOMAIN, "elt", arg2, th);

    if (listp(arg1)) {
	if (length(arg1) == 0)
	    error(OUT_OF_RANGE, "elt", arg1, th);
	if (integerp(arg2) && length(arg1) <= GET_INT(arg2))
	    error(OUT_OF_RANGE, "elt", arg2, th);
	if (longnump(arg2)
	    && (long long int) length(arg1) <= GET_LONG(arg2))
	    error(OUT_OF_RANGE, "elt", arg2, th);
	return (listref(arg1, GET_INT(arg2)));
    } else if (vectorp(arg1)) {
	if (vector_length(arg1) == 0)
	    error(OUT_OF_RANGE, "elt", arg1, th);
	if (integerp(arg2) && vector_length(arg1) <= GET_INT(arg2))
	    error(OUT_OF_RANGE, "elt", arg2, th);
	if (longnump(arg2)
	    && (long long int) vector_length(arg1) <= GET_LONG(arg2))
	    error(OUT_OF_RANGE, "elt", arg2, th);
	return (vector_ref(arg1, GET_INT(arg2)));
    } else if (stringp(arg1)) {
	if (string_length(arg1) == 0)
	    error(OUT_OF_RANGE, "elt", arg1, th);
	if (integerp(arg2)
	    && ((int) strlen(GET_NAME(arg1)) <= GET_INT(arg2)))
	    error(OUT_OF_RANGE, "elt", arg2, th);
	if (longnump(arg2)
	    && (long long int) strlen(GET_NAME(arg1)) <= GET_LONG(arg2))
	    error(OUT_OF_RANGE, "elt", arg2, th);

	return (string_ref(arg1, arg2));
    }
    return (NIL);
}



int f_set_elt(int arglist, int th)
{
    int arg1, arg2, arg3;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if (length(arglist) != 3)
	error(WRONG_ARGS, "set-elt", arglist, th);
    if (!integerp(arg3) && !longnump(arg3))
	error(NOT_INT, "set-elt", arg3, th);
    if (negativep(arg3))
	error(OUT_OF_DOMAIN, "set-elt", arg2, th);

    if (listp(arg2)) {
	if (length(arg2) == 0)
	    error(OUT_OF_RANGE, "set-elt", arg1, th);
	if (integerp(arg3) && length(arg2) <= GET_INT(arg3))
	    error(OUT_OF_RANGE, "set-elt", arg2, th);
	if (longnump(arg3)
	    && (long long int) length(arg2) <= GET_LONG(arg3))
	    error(OUT_OF_RANGE, "set-elt", arg2, th);
	SET_CAR(listref1(arg2, GET_INT(arg3)), arg1);
    } else if (vectorp(arg2)) {
	if (vector_length(arg2) == 0)
	    error(OUT_OF_RANGE, "set-elt", arg2, th);
	if (integerp(arg3) && vector_length(arg2) <= GET_INT(arg3))
	    error(OUT_OF_RANGE, "set-elt", arg3, th);
	if (longnump(arg3)
	    && (long long int) vector_length(arg2) <= GET_LONG(arg3))
	    error(OUT_OF_RANGE, "set-elt", arg3, th);
	SET_VEC_ELT(arg2, GET_INT(arg3), arg1);
    } else if (stringp(arg2)) {
	if (string_length(arg2) == 0)
	    error(OUT_OF_RANGE, "set-elt", arg2, th);
	if (integerp(arg3)
	    && ((int) strlen(GET_NAME(arg2)) <= GET_INT(arg3)))
	    error(OUT_OF_RANGE, "set-elt", arg3, th);
	if (longnump(arg3)
	    && (long long int) strlen(GET_NAME(arg2)) <= GET_LONG(arg3))
	    error(OUT_OF_RANGE, "set-elt", arg2, th);
	string_set(arg2, arg3, arg1);
    }
    return (arg1);
}


/* string */
int f_string_smallerp(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "string<", arglist, th);
    if (!stringp(arg1))
	error(NOT_STR, "string<", arg1, th);
    if (!stringp(arg2))
	error(NOT_STR, "string<", arg2, th);

    if (SMALLER_NAME(arg1, arg2))
	return (T);
    else
	return (NIL);
}

int f_string_greaterp(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "string>", arglist, th);
    if (!stringp(arg1))
	error(NOT_STR, "string>", arg1, th);
    if (!stringp(arg2))
	error(NOT_STR, "string>", arg2, th);

    if (GREATER_NAME(arg1, arg2))
	return (T);
    else
	return (NIL);
}

int f_string_eqgreaterp(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "string>=", arglist, th);
    if (!stringp(arg1))
	error(NOT_STR, "string>=", arg1, th);
    if (!stringp(arg2))
	error(NOT_STR, "string>=", arg2, th);

    if (GREATER_NAME(arg1, arg2) || SAME_NAME(arg1, arg2))
	return (T);
    else
	return (NIL);

}


int f_string_eqsmallerp(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "string<=", arglist, th);
    if (!stringp(arg1))
	error(NOT_STR, "string<=", arg1, th);
    if (!stringp(arg2))
	error(NOT_STR, "string<=", arg2, th);

    if (SMALLER_NAME(arg1, arg2) || SAME_NAME(arg1, arg2))
	return (T);
    else
	return (NIL);

}

int f_string_append(int arglist, int th)
{
    int arg1;

    if (nullp(arglist))
	return (make_str(""));

    arg1 = car(arglist);
    if (!stringp(arg1))
	error(NOT_STR, "string-append", arg1, th);
    arglist = cdr(arglist);
    if (nullp(arglist))
	return (arg1);
    Text_save_T save = Text_save();
    Text_T txt1 = Text_put(GET_NAME(arg1));
    while (!nullp(arglist)) {
	int arg2;

	arg2 = car(arglist);
	if (!stringp(arg2))
	    error(NOT_STR, "string-append", arg2, th);
	arglist = cdr(arglist);

	Text_T txt2 = Text_put(GET_NAME(arg2));
	txt1 = Text_cat(txt1, txt2);
    }
    char *str = Text_get(NULL, 0, txt1);
    int res = make_str(str);
    free(str);
    Text_restore(&save);
    return res;
}


int f_string_index(int arglist, int th)
{
    int arg1, arg2, arg3, n, i, j, k, len1, len2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if ((n = length(arglist)) != 2 && n != 3)
	error(WRONG_ARGS, "string-index", arglist, th);
    if (!stringp(arg1))
	error(NOT_STR, "string-index", arg1, th);
    if (!stringp(arg2))
	error(NOT_STR, "string-index", arg2, th);
    if (n == 3 && negativep(arg3))
	error(NOT_POSITIVE, "string-index", arg3, th);
    if (n == 3 && !integerp(arg3))
	error(WRONG_ARGS, "string-index", arg3, th);
    if (n == 3 && GET_INT(arg3) >= string_length(arg2))
	error(ILLEGAL_ARGS, "string-index", arg3, th);

    if (string_length(arg1) == 0 && string_length(arg2) == 0)	/* (string-index "" "") */
	return (make_int(0));

    if (string_length(arg2) == 0)
	return (NIL);

    len1 = strlen(GET_NAME(arg1));
    len2 = strlen(GET_NAME(arg2));
    if (n == 3)
	j = GET_INT(arg3);
    else
	j = 0;



    for (i = j; i < len2; i++)
	for (k = 0; k < len1 + 1; k++)
	    if (STRING_REF(arg1, k) == NUL)
		return (make_int(i));
	    else if (STRING_REF(arg1, k) != STRING_REF(arg2, i + k))
		break;


    return (NIL);
}


/* vector and array */
int f_aref(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);

    if (length(arglist) < 1)
	error(WRONG_ARGS, "aref", arglist, th);

    if (stringp(arg1)) {
	if (negativep(car(arg2)))
	    error(OUT_OF_DOMAIN, "aref", arg2, th);
	if (GET_INT(car(arg2)) >= string_length(arg1))
	    error(OUT_OF_RANGE, "aref", arg2, th);
	return (string_ref(arg1, car(arg2)));
    } else if (vectorp(arg1)) {
	if (!indomainp(arg2))
	    error(OUT_OF_DOMAIN, "aref", arg2, th);
	if (!inrangep(arg2, list1(make_int(vector_length(arg1)))))
	    error(OUT_OF_RANGE, "aref", arg2, th);
	return (array_ref(arg1, arg2));
    } else if (arrayp(arg1)) {
	if (!indomainp(arg2))
	    error(OUT_OF_DOMAIN, "aref", arg2, th);
	if (!inrangep(arg2, array_length(arg1)))
	    error(OUT_OF_RANGE, "aref", arg2, th);
	return (array_ref(arg1, arg2));
    } else
	error(NOT_BASIC_ARRAY, "aref", arg1, th);

    return (NIL);
}

int indomainp(int ls)
{
    if (nullp(ls))
	return (1);
    else if (negativep(car(ls)))
	return (0);
    else
	return (indomainp(cdr(ls)));
}


int inrangep(int x, int y)
{

    while (!nullp(x)) {
	if (longnump(car(x) || bignump(car(x))))
	    return (0);
	else if (eqgreaterp(car(x), car(y)) || GET_INT(car(x)) < 0)
	    return (0);
	else if (nullp(y))
	    return (0);

	x = cdr(x);
	y = cdr(y);
    }
    if (nullp(y))
	return (1);
    else
	return (0);
}

int f_garef(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);

    if (vectorp(arg1)) {
	if (!indomainp(arg2))
	    error(OUT_OF_DOMAIN, "garef", arg2, th);
	if (!inrangep(arg2, list1(make_int(vector_length(arg1)))))
	    error(OUT_OF_RANGE, "garef", arg2, th);
	return (array_ref(arg1, arg2));
    } else if (arrayp(arg1)) {
	if (!indomainp(arg2))
	    error(OUT_OF_DOMAIN, "garef", arg2, th);
	if (!inrangep(arg2, array_length(arg1)))
	    error(OUT_OF_RANGE, "garef", arg2, th);
	return (array_ref(arg1, arg2));
    } else
	error(NOT_VECARR, "garef", arg1, th);
    return (NIL);

}

/*
 * obj is array or vector
 * ls is index. e.g. (0 1 1)
 */
int array_ref(int obj, int ls)
{
    int size, index;

    if (vectorp(obj)) {
	size = list1(vector_length(obj));
    } else {
	size = array_length(obj);	/* e.g. #3a(((0 1 2) (3 4 5))) -> (1 2 3) */
    }

    index = 0;
    size = cdr(size);
    while (!nullp(ls)) {
	if (nullp(cdr(ls)))
	    index = index + GET_INT(car(ls));
	else if (GET_INT(car(ls)) != 0)
	    index = index + GET_INT(car(size)) * GET_INT(car(ls));
	/*
	 * else if(GET_INT(car(ls)) == 0) index = index; 
	 */

	size = cdr(size);
	ls = cdr(ls);
    }
    return (vector_ref(obj, index));
}


int f_set_aref(int arglist, int th)
{
    int arg1, arg2, arg3;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = cddr(arglist);


    if (stringp(arg2)) {
	if (negativep(car(arg3)))
	    error(OUT_OF_DOMAIN, "set-aref", arg3, th);
	if (GET_INT(car(arg3)) >= string_length(arg2))
	    error(OUT_OF_RANGE, "set-aref", arg3, th);
	string_set(arg2, car(arg3), arg1);
    } else if (vectorp(arg2)) {
	if (!indomainp(arg3))
	    error(OUT_OF_DOMAIN, "set-aref", arg3, th);
	if (!inrangep(arg3, list1(make_int(vector_length(arg2)))))
	    error(OUT_OF_RANGE, "set-aref", arg3, th);
	array_set(arg2, arg3, arg1);
    } else if (arrayp(arg2)) {
	if (!indomainp(arg3))
	    error(OUT_OF_DOMAIN, "set-aref", arg3, th);
	if (!inrangep(arg3, array_length(arg2)))
	    error(OUT_OF_RANGE, "set-aref", arg3, th);
	array_set(arg2, arg3, arg1);
    } else
	error(ILLEGAL_ARGS, "set-aref", arg2, th);

    return (arg1);
}

int array_set(int obj, int ls, int val)
{
    int size, index;

    if (vectorp(obj)) {
	size = list1(vector_length(obj));
    } else {
	size = array_length(obj);	/* e.g. #3a(((0 1 2) (3 4 5))) -> (1 2 3) */
    }
    index = 0;
    size = cdr(size);
    while (!nullp(ls)) {
	if (nullp(cdr(ls)))
	    index = index + GET_INT(car(ls));
	else if (GET_INT(car(ls)) != 0)
	    index = index + GET_INT(car(size)) * GET_INT(car(ls));
	/*
	 * else if(GET_INT(car(ls)) == 0) index = index; 
	 */

	size = cdr(size);
	ls = cdr(ls);
    }
    vector_set(obj, index, val);
    return (obj);
}

int f_set_garef(int arglist, int th)
{
    int arg1, arg2, arg3;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = cddr(arglist);
    if (GET_AUX(arg2) != cgeneral_vector
	&& GET_AUX(arg2) != cgeneral_array_star)
	error(NOT_VECARR, "set-garef", arg2, th);

    if (vectorp(arg2)) {
	if (!indomainp(arg3))
	    error(OUT_OF_DOMAIN, "set-aref", arg3, th);
	if (!inrangep(arg3, list1(make_int(vector_length(arg2)))))
	    error(OUT_OF_RANGE, "set-aref", arg3, th);
	array_set(arg2, arg3, arg1);
    } else if (arrayp(arg2)) {
	if (!indomainp(arg3))
	    error(OUT_OF_DOMAIN, "set-aref", arg3, th);
	if (!inrangep(arg3, array_length(arg2)))
	    error(OUT_OF_RANGE, "set-aref", arg3, th);
	array_set(arg2, arg3, arg1);
    }

    return (arg1);
}

int f_basic_vector_p(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "basic-vector-p", arglist, th);

    if (!symbolp(arg1) && GET_AUX(arg1) == cbasic_vector)
	return (T);
    else if (!symbolp(arg1) && subclassp(GET_AUX(arg1), cbasic_vector))
	return (T);
    else
	return (NIL);

    return (UNDEF);
}

int f_general_vector_p(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "general-vector-p", arglist, th);

    if (!symbolp(arg1) && GET_AUX(arg1) == cgeneral_vector)
	return (T);
    else if (!symbolp(arg1) && subclassp(GET_AUX(arg1), cgeneral_vector))
	return (T);
    else
	return (NIL);

    return (UNDEF);
}


int f_basic_array_p(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "basic-array-p", arglist, th);

    if (!symbolp(arg1) && GET_AUX(arg1) == cbasic_array)
	return (T);
    else if (!symbolp(arg1) && subclassp(GET_AUX(arg1), cbasic_array))
	return (T);
    else
	return (NIL);

    return (UNDEF);
}

int f_basic_array_star_p(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "basic-array-p", arglist, th);

    if (!symbolp(arg1) && GET_AUX(arg1) == cbasic_array_star)
	return (T);
    else if (!symbolp(arg1) && subclassp(GET_AUX(arg1), cbasic_array_star))
	return (T);
    else
	return (NIL);

    return (UNDEF);
}

int f_general_array_star_p(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "general-array*-p", arglist, th);

    if (!symbolp(arg1) && GET_AUX(arg1) == cgeneral_array_star)
	return (T);
    else if (!symbolp(arg1)
	     && subclassp(GET_AUX(arg1), cgeneral_array_star))
	return (T);
    else
	return (NIL);

    return (UNDEF);
}


int f_array_dimensions(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "array-dimensions", arglist, th);
    if (!vectorp(arg1) && !arrayp(arg1) && !stringp(arg1))
	error(NOT_ARR, "array-dimensions", arg1, th);

    if (vectorp(arg1))
	return (list1(make_int(GET_CDR(arg1))));
    else if (arrayp(arg1))
	return (GET_CDR(arg1));
    else
	return (list1(make_int(strlen(GET_NAME(arg1)))));
}

/*
 * calculation of array's dimension
 * e.g. ((1 2)(3 4)(5 6)) -> (3 2)
 */
int array_dim(int n, int ls)
{
    if (!nullp(ls) && atomp(ls) && n > 0)
	error(ILLEGAL_ARGS, "array", NIL, 0);
    else if (n == 0)
	return (NIL);
    else
	return (cons(make_int(length(ls)), array_dim(n - 1, car(ls))));

    return (UNDEF);
}


int f_vector(int arglist, int th __unused)
{
    return (vector(arglist));
}


int f_create_star(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);	/* class */
    arg2 = cadr(arglist);	/* initargs,vals */
    if (length(arglist) != 2)
	error(WRONG_ARGS, "create", arglist, th);
    if (!(IS_CLASS(arg1)))
	error(NOT_CLASS, "create", arg1, th);
    if (GET_OPT(arg1) == SYSTEM || GET_OPT(arg1) == ABSTRACT)
	error(CANT_CREATE, "create", arg1, th);

    return (make_instance(arg1, arg2));
}

DEF_PREDICATE(INSTANCE, INSTANCE)
int f_slot_value(int arglist, int th)
{
    int arg1, arg2, val;

    arg1 = car(arglist);	/* instance */
    arg2 = cadr(arglist);	/* var */
    if (length(arglist) != 2)
	error(WRONG_ARGS, "slot-value", arglist, th);
    if (!(IS_INSTANCE(arg1)))
	error(NOT_INSTANCE, "slot-value", arg1, th);
    if (!symbolp(arg2))
	error(NOT_SYM, "slot-value", arg2, th);

    val = assoc(arg2, GET_CDR(arg1));
    if (nullp(val))
	error(UNDEF_VAR, "slot-value", arg2, th);


    return (cdr(val));
}

int f_set_slot_value(int arglist, int th)
{
    int arg1, arg2, arg3, val;

    arg1 = car(arglist);	/* value to set */
    arg2 = cadr(arglist);	/* instance */
    arg3 = caddr(arglist);	/* var */
    if (length(arglist) != 3)
	error(WRONG_ARGS, "set-slot-value", arglist, th);
    if (!(IS_INSTANCE(arg2)))
	error(NOT_INSTANCE, "set-slot-value", arg1, th);
    if (!symbolp(arg3))
	error(NOT_SYM, "set-slot-value", arg2, th);

    val = assoc(arg3, GET_CDR(arg2));
    if (nullp(val))
	error(UNDEF_VAR, "set-slot-value", arg3, th);

    set_cdr(val, arg1);
    return (arg1);
}

/* format */
int f_format(int arglist, int th)
{

    int arg1, arg2, args, i, save, n, quote_flag;
    char *str, c;

    arg1 = car(arglist);	/* output-stream */
    arg2 = cadr(arglist);	/* format-string */
    args = cddr(arglist);	/* data */
    quote_flag = 0;
    if (!output_stream_p(arg1))
	error(NOT_OUT_STREAM, "format", arg1, th);
    if (!stringp(arg2))
	error(NOT_STR, "format", arg2, th);

    save = output_stream;
    output_stream = arg1;
    str = Str_dup(GET_NAME(arg2), 1, 0, 1);
    i = 0;
    c = str[i];
    while (c != 0) {
	if (c == '~' && quote_flag == 0) {
	    i++;
	    c = str[i];
	    if (c == 'A') {
		if (nullp(args)) {
		    output_stream = save;
		    error(IMPROPER_ARGS, "format ~A", arg2, th);
		}
		f_format_object(list3(arg1, car(args), NIL), 0);
		args = cdr(args);
	    } else if (c == 'B') {
		if (nullp(args)) {
		    output_stream = save;
		    error(IMPROPER_ARGS, "format ~B", arg2, th);
		}
		f_format_integer(list3(arg1, car(args), make_int(2)), 0);
		args = cdr(args);
	    } else if (c == 'C') {
		if (nullp(args)) {
		    output_stream = save;
		    error(IMPROPER_ARGS, "format ~C", arg2, th);
		}
		f_format_char(list2(arg1, car(args)), 0);
		args = cdr(args);
	    } else if (c == 'D') {
		if (nullp(args)) {
		    output_stream = save;
		    error(IMPROPER_ARGS, "format ~D", arg2, th);
		}
		f_format_integer(list3(arg1, car(args), make_int(10)), 0);
		args = cdr(args);
	    } else if (c == 'G') {
		if (nullp(args)) {
		    output_stream = save;
		    error(IMPROPER_ARGS, "format ~G", arg2, th);
		}
		f_format_float(list2(arg1, car(args)), 0);
		args = cdr(args);
	    } else if (c == 'O') {
		if (nullp(args)) {
		    output_stream = save;
		    error(IMPROPER_ARGS, "format ~O", arg2, th);
		}
		f_format_integer(list3(arg1, car(args), make_int(8)), 0);
		args = cdr(args);
	    } else if (c == 'S') {
		if (nullp(args)) {
		    output_stream = save;
		    error(IMPROPER_ARGS, "format ~S", arg2, th);
		}
		f_format_object(list3(arg1, car(args), T), 0);
		args = cdr(args);
	    } else if (c == 'X') {
		if (nullp(args)) {
		    output_stream = save;
		    error(IMPROPER_ARGS, "format ~X", arg2, th);
		}
		f_format_integer(list3(arg1, car(args), make_int(16)), 0);
		args = cdr(args);
	    } else if (isdigit(c)) {
		n = 0;
		while (isdigit(c)) {
		    n = n * 10 + (c - '0');
		    i++;
		    c = str[i];
		}
		if (c == 'R') {
		    if (nullp(args)) {
			output_stream = save;
			error(IMPROPER_ARGS, "format ~nR", arg2, th);
		    }
		    f_format_integer(list3(arg1, car(args), make_int(n)),
				     0);
		    args = cdr(args);
		} else if (c == 'T') {
		    f_format_tab(list2(arg1, make_int(n)), 0);
		} else
		    error(ILLEGAL_ARGS, "format ~n?", NIL, th);


	    } else if (c == '%') {
		output_char(output_stream, '\n');
		start_flag = false;
		charcnt = 0;
	    } else if (c == '&') {
		f_format_fresh_line(list1(arg1), 0);
	    } else if (c == '~') {
		output_char(output_stream, '~');
		start_flag = false;
		charcnt++;
	    }

	    i++;
	} else if (c == '\\' && str[i + 1] == '\\' && quote_flag == 0) {
	    output_char(output_stream, c);
	    i++;
	    i++;
	    c = str[i];
	    output_char(output_stream, c);
	    i++;
	} else if (c == '\\' && quote_flag == 0)
	    i++;
	else if (c == '\\' && quote_flag == 1) {
	    output_char(output_stream, c);
	    i++;
	    c = str[i];
	    output_char(output_stream, c);
	    i++;
	} else {
	    if (c == '\'' && str[i + 1] == '\'') {
		if (quote_flag == 0)
		    quote_flag = 1;
		else
		    quote_flag = 0;
		c = '"';
		i++;
	    }
	    output_char(output_stream, c);
	    i++;
	    start_flag = false;
	    charcnt++;
	}
	c = str[i];
    }
    output_stream = save;
    free(str);
    return (NIL);
}

static int printr_h(int r, int n, char *b, int *sign)
{
    int i;
    static const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    REQUIRE(r >= 2 && r <= 36);
    *sign = 1;
    if (n == 0) {
	b[0] = '0';
	i = 0;
    } else {
	if (n >= 0)
	    *sign = 1;
	else {
	    *sign = -1;
	    n = abs(n);
	}
	i = 0;
	while (n > 0) {
	    b[i] = digits[n % r];

	    n = n / r;
	    i++;
	}
	i--;
    }
    b[i + 1] = '\0';
    return (i + 1);
}

int fprintr(FILE *p, int r, int n)
{
    int i, sign, len;
    char b[BININT_LEN + 1];

    len = printr_h(r, n, b, &sign);
    i = len - 1;
    if (sign == -1) {
	fputc('-', p);
	len++;
    }
    while (i >= 0) {
	fputc(b[i], p);
	i--;
    }
    return (len);
}

int sprintr(char *str, int r, int n)
{
    int i, j, sign, len;
    char b[BININT_LEN + 1];

    len = printr_h(r, n, b, &sign);
    i = len - 1;
    j = 0;
    if (sign == -1) {
	str[j] = '-';
	j++;
	len++;
    }
    while (i >= 0) {
	str[j] = b[i];
	i--;
	j++;
    }
    str[j] = NUL;
    return (len);
}

int f_format_char(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "format-char", arglist, th);
    if (!text_output_stream_p(arg1))
	error(NOT_OUT_STREAM, "format-char", arg1, th);
    if (!charp(arg2))
	error(NOT_CHAR, "format-char", arg2, th);

    if (GET_OPT(arg1) != EISL_OUTSTR) {
	fputs(GET_NAME(arg2), GET_PORT(arg1));
	charcnt++;
    } else {
	append_str(arg1, GET_NAME(arg2));
	charcnt = charcnt + strlen(GET_NAME(arg2));
    }
    start_flag = false;
    return (NIL);
}

int f_format_fresh_line(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "format-fresh-line", arglist, th);
    if (!text_output_stream_p(arg1))
	error(NOT_STREAM, "format-fresh-line", arg1, th);

    if (!start_flag) {
	int save;

	save = output_stream;
	output_stream = arg1;
	/* output newline char if it cannot be determinned that the output 
	 * stream is at the begining of a fresh line
	 */
	if (GET_OPT(output_stream) == EISL_OUTSTR
	    && strlen(GET_NAME(output_stream)) == 0) {
	    goto skip;
	}
	output_char(output_stream, '\n');
	start_flag = false;
	charcnt = 0;
	/* if output_stream is string-stream, set charcnt 0. */
	if (GET_OPT(output_stream) == EISL_OUTSTR) {
	    SET_PROP(output_stream, 0);
	}

      skip:
	output_stream = save;
    }
    return (NIL);
}


int f_format_float(int arglist, int th)
{
    int arg1, arg2, save, flt;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "format-float", arglist, th);
    if (!text_output_stream_p(arg1))
	error(NOT_OUT_STREAM, "format-float", arg1, th);
    if (!numberp(arg2))
	error(NOT_FLT, "format-float", arg2, th);
    save = output_stream;
    output_stream = arg1;
    flt = exact_to_inexact(arg2);
    print(flt);
    start_flag = false;
    /* count character */
    output_stream = save;
    charcnt = charcnt + strlen(stream_str);
    return (NIL);
}


int f_format_integer(int arglist, int th)
{
    int arg1, arg2, arg3, n, save;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if (length(arglist) != 3)
	error(WRONG_ARGS, "format-integer", arglist, th);
    if (!text_output_stream_p(arg1))
	error(NOT_OUT_STREAM, "format-integer", arg1, th);
    if (!integerp(arg2) && !longnump(arg2) && !bignump(arg2))
	error(NOT_INT, "format-integer", arg2, th);
    if (!integerp(arg3))
	error(NOT_INT, "format-integer", arg3, th);
    if ((n = GET_INT(arg3)) < 2 || n > 36)
	error(IMPROPER_ARGS, "format-integer", arg3, th);

    save = output_stream;
    output_stream = arg1;
    if (integerp(arg2)) {
	int len;

	if (GET_OPT(output_stream) != EISL_OUTSTR)
	    len = fprintr(GET_PORT(arg1), GET_INT(arg3), GET_INT(arg2));
	else {
	    len = sprintr(stream_str, GET_INT(arg3), GET_INT(arg2));
	    append_str(output_stream, stream_str);
	}
	charcnt = charcnt + len;
    } else {
	print(arg2);
	charcnt = charcnt + strlen(stream_str);
    }
    output_stream = save;
    start_flag = false;
    return (NIL);
}

int f_format_object(int arglist, int th)
{
    int arg1, arg2, arg3, save;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);

    if (length(arglist) != 3)
	error(WRONG_ARGS, "format-object", arglist, th);
    if (!text_output_stream_p(arg1))
	error(NOT_OUT_STREAM, "format-object", arglist, th);

    save = output_stream;
    output_stream = arg1;
    if (stringp(arg2)) {
	if (nullp(arg3)) {
	    output_str(arg1, GET_NAME(arg2));
	    charcnt = charcnt + strlen(GET_NAME(arg2));
	} else {
	    if (GET_OPT(arg1) != EISL_OUTSTR) {
		fprintf(GET_PORT(arg1), "\\\"%s\\\"", GET_NAME(arg2));
	    } else {
		sprintf(stream_str, "\\\"%s\\\"",
			 GET_NAME(arg2));
		append_str(arg1, stream_str);
	    }
	    charcnt = charcnt + 4 + strlen(GET_NAME(arg2));
	}
    } else if (charp(arg2)) {
	if (nullp(arg3)) {
	    output_str(arg1, GET_NAME(arg2));
	    charcnt = charcnt + strlen(GET_NAME(arg2));
	} else {
	    if (GET_OPT(arg1) != EISL_OUTSTR)
		fprintf(GET_PORT(arg1), "#\\\\%s", GET_NAME(arg2));
	    else {
		char *str = Str_cat("#\\\\", 1, 0, GET_NAME(arg2), 1, 0);
		append_str(arg1, str);
		free(str);
	    }
	    charcnt = charcnt + 3 + strlen(GET_NAME(arg2));
	}
    } else {
	print(arg2);
	charcnt = charcnt + strlen(stream_str);
    }
    output_stream = save;
    start_flag = false;
    return (NIL);
}

int f_format_tab(int arglist, int th)
{
    int arg1, arg2, n, save;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "format-tab", arglist, th);
    if (!text_output_stream_p(arg1))
	error(NOT_OUT_STREAM, "format-tab", arg1, th);
    if (!integerp(arg2))
	error(IMPROPER_ARGS, "format-tab", arg2, th);
    if (negativep(arg2))
	error(IMPROPER_ARGS, "format-tab", arg2, th);

    save = output_stream;
    output_stream = arg1;

    if (GET_OPT(output_stream) != EISL_OUTSTR)
	n = GET_INT(arg2) - charcnt;
    else
	n = GET_INT(arg2) - GET_PROP(output_stream);

    if (n < 0)
	n = 1;
    while (n > 0) {
	output_char(arg1, ' ');
	n--;
	charcnt++;
    }
    start_flag = false;
    output_stream = save;
    return (NIL);
}


/* file */
int f_open_input_file(int arglist, int th)
{
    int arg1, arg2, n;
    FILE *port;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if ((n = length(arglist)) != 1 && n != 2)
	error(WRONG_ARGS, "open-input-file", arglist, th);
    if (n == 2 && !(integerp(arg2) && get_int(arg2) == 8))
	error(IMPROPER_ARGS, "open-input-file", arglist, th);
    if (!stringp(arg1))
	error(NOT_STR, "open-input-file", arg1, th);

    const char *fname = GET_NAME(arg1);
    if (n == 1)
	port = fopen(fname, "r");
    else
	port = fopen(fname, "rb");

    if (port == NULL)
	error(CANT_OPEN, "open-input-file", arg1, th);

    if (n == 1)
	return (make_stm(port, EISL_INPUT, Str_dup(fname, 1, 0, 1)));
    else
	return (make_stm(port, EISL_INPUT_BIN, Str_dup(fname, 1, 0, 1)));
}

int f_open_output_file(int arglist, int th)
{
    int arg1, arg2, n;
    FILE *port;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if ((n = length(arglist)) != 1 && n != 2)
	error(WRONG_ARGS, "open-output-file", arglist, th);
    if (n == 2 && !(integerp(arg2) && get_int(arg2) == 8))
	error(IMPROPER_ARGS, "open-output-file", arglist, th);
    if (!stringp(arg1))
	error(NOT_STR, "open-output-file", arg1, th);

    const char *fname = GET_NAME(arg1);
    if (n == 1)
	port = fopen(fname, "w");
    else
	port = fopen(fname, "wb");
    if (port == NULL)
	error(CANT_OPEN, "open-output-file", arg1, th);

    if (n == 1)
	return (make_stm(port, EISL_OUTPUT, Str_dup(fname, 1, 0, 1)));
    else
	return (make_stm(port, EISL_OUTPUT_BIN, Str_dup(fname, 1, 0, 1)));
}

int f_open_io_file(int arglist, int th)
{
    int arg1, arg2, n;
    FILE *port;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if ((n = length(arglist)) != 1 && n != 2)
	error(WRONG_ARGS, "open-io-file", arglist, th);
    if (n == 2 && !(integerp(arg2) && get_int(arg2) == 8))
	error(IMPROPER_ARGS, "open-io-file", arglist, th);
    if (!stringp(arg1))
	error(NOT_STR, "open-io-file", arg1, th);

    const char *fname = GET_NAME(arg1);
    if (n == 1)
	port = fopen(fname, "a+");
    else
	port = fopen(fname, "ab+");

    if (port == NULL)
	error(CANT_OPEN, "open-io-file", arg1, th);

    if (n == 1)
	return (make_stm(port, EISL_INOUT, Str_dup(fname, 1, 0, 1)));
    else
	return (make_stm(port, EISL_INOUT_BIN, Str_dup(fname, 1, 0, 1)));
}

int f_close(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "close", arglist, th);
    if (!streamp(arg1))
	error(NOT_STREAM, "close", arg1, th);

    if (GET_OPT(arg1) != EISL_INSTR && GET_OPT(arg1) != EISL_OUTSTR) {
	fclose(GET_PORT(arg1));
	SET_PROF(arg1, EISL_CLOSE);
    } else
	SET_PROF(arg1, EISL_CLOSE);

    start_flag = true;
    return (UNDEF);
}

int f_finish_output(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "finish-output", arglist, th);
    if (!(streamp(arg1)
	  && (GET_OPT(arg1) == EISL_OUTPUT
	      || GET_OPT(arg1) == EISL_OUTSTR)))
	error(NOT_OUT_STREAM, "finish-output", arg1, th);

    if (GET_OPT(arg1) == EISL_OUTPUT)
	fflush(GET_PORT(arg1));
    return (UNDEF);
}


int f_file_length(int arglist, int th)
{
    int arg1, arg2, res;
    FILE *p;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "file-length", arglist, th);
    if (!stringp(arg1))
	error(NOT_STR, "file-length", arg1, th);
    if (!(integerp(arg2) && GET_INT(arg2) == 8))
	error(IMPROPER_ARGS, "file-length", arg2, th);

    p = fopen(GET_NAME(arg1), "rb");
    if (p == NULL) {
	error(CANT_OPEN, "file-length", arg1, th);
	return NIL;
    }

    fseek(p, 0, SEEK_END);
    res = ftell(p);
    fclose(p);
    return (make_int(res));
}

int f_probe_file(int arglist, int th)
{
    int arg1, res;
    FILE *p;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "probe-file", arglist, th);
    if (!stringp(arg1))
	error(NOT_STR, "probe-file", arg1, th);

    res = T;
    p = fopen(GET_NAME(arg1), "rb");
    if (p == NULL)
	res = NIL;

    if (res != NIL)
	fclose(p);

    return (res);
}

int f_file_position(int arglist, int th)
{
    int arg1;
    FILE *p;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "file-position", arglist, th);
    if (!streamp(arg1))
	error(NOT_STREAM, "file-position", arg1, th);

    p = GET_PORT(arg1);
    return (make_int(ftell(p)));

}

int f_set_file_position(int arglist, int th)
{
    int arg1, arg2;
    FILE *p;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "set-file-position", arglist, th);
    if (!streamp(arg1))
	error(NOT_STREAM, "set-file-position", arg1, th);
    if (!integerp(arg2))
	error(IMPROPER_ARGS, "set-file-position", arg2, th);
    if (negativep(arg2))
	error(NOT_POSITIVE, "set-file-position", arg2, th);

    p = GET_PORT(arg1);
    fseek(p, GET_INT(arg2), SEEK_SET);
    return (arg2);
}



int f_write_byte(int arglist, int th)
{
    int arg1, arg2, n;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "write-byte", arglist, th);
    if (!integerp(arg1))
	error(NOT_INT, "write-byte", arg1, th);
    n = GET_INT(arg1);
    if (n < 0 || n > 255)
	error(IMPROPER_ARGS, "write-byte", arg1, th);
    if (!binary_output_stream_p(arg2))
	error(NOT_OUT_STREAM, "write-byte", arg2, th);

    fputc((char) GET_INT(arg1), GET_PORT(arg2));
    return (arg1);
}


/* create-*   */
int f_create_vector(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);

    if (length(arglist) != 1 && length(arglist) != 2)
	error(WRONG_ARGS, "create-vector", arglist, th);
    if (negativep(arg1))
	error(NOT_POSITIVE, "create-vector", arg1, th);
    if (!integerp(arg1))
	error(EXHAUSTED_ERR, "create-vector", arg1, th);
    if (length(arglist) == 1)
	arg2 = UNDEF;

    return (make_vec(GET_INT(arg1), arg2));
}

int f_create_array(int arglist, int th)
{
    int arg1, arg2, temp;

    arg1 = car(arglist);
    arg2 = cadr(arglist);

    temp = 0;
    if (length(arglist) != 1 && length(arglist) != 2
	&& length(arglist) != 3)
	error(OUT_OF_DOMAIN, "create-array", arglist, th);
    if (!listp(arg1))
	error(NOT_LIST, "create-array", arg1, th);
    if ((temp = check_dimension(arg1)) == 1)
	error(OUT_OF_DOMAIN, "create-array", arg1, th);
    if (temp == 2)
	error(EXHAUSTED_ERR, "create-array", arg1, th);
    if (length(arglist) == 1)
	arg2 = UNDEF;

    return (make_arr(arg1, arg2));

}

/* when dimension is domain-error return 1.
 * when dimension is storage-exhausted-error return 2.
 */
int check_dimension(int ls)
{
    while (!nullp(ls)) {
	if (negativep(car(ls)))
	    return (1);
	else if (longnump(car(ls)) || bignump(car(ls)))
	    return (2);
	else if (!integerp(car(ls)))
	    return (1);
	else
	    ls = cdr(ls);
    }
    return (0);
}

int f_create_string(int arglist, int th)
{
    int arg1, arg2, n, i, pos;
    char *str = NULL;
    char c;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if ((n = length(arglist)) != 1 && n != 2)
	error(WRONG_ARGS, "create-string", arglist, th);
    if (!math_integerp(arg1))
	error(NOT_INT, "create-string", arg1, th);
    if (negativep(arg1))
	error(DOMAIN_ERR, "create-string", arg1, th);
    if (longnump(arg1) || bignump(arg1))
	error(EXHAUSTED_ERR, "create-string", arg1, th);
    if (!(charp(arg2) || nullp(arg2)))
	error(NOT_CHAR, "create-string", arg2, th);



    n = GET_INT(arg1);
    if (nullp(arg2))
	c = ' ';
    else
	c = GET_CHAR(arg2);


    if (isUni1(c)) {
	str = malloc(n + 1);
	memset(str, c, n);
	str[n] = NUL;
    } else if (isUni2(c)) {
	str = malloc(2 * n + 1);
	pos = 0;
	for (i = 0; i < n; i++) {
	    str[pos++] = heap[arg2].name[0];
	    str[pos++] = heap[arg2].name[1];
	}
	str[pos] = NUL;
    } else if (isUni3(c)) {
	str = malloc(3 * n + 10);
	pos = 0;
	for (i = 0; i < n; i++) {
	    str[pos++] = heap[arg2].name[0];
	    str[pos++] = heap[arg2].name[1];
	    str[pos++] = heap[arg2].name[2];
	}
	str[pos] = NUL;
    } else if (isUni4(c)) {
	str = malloc(4 * n + 10);
	pos = 0;
	for (i = 0; i < n; i++) {
	    str[pos++] = heap[arg2].name[0];
	    str[pos++] = heap[arg2].name[1];
	    str[pos++] = heap[arg2].name[2];
	    str[pos++] = heap[arg2].name[3];
	}
	str[pos] = NUL;
    } else if (isUni5(c)) {
	str = malloc(5 * n + 10);
	pos = 0;
	for (i = 0; i < n; i++) {
	    str[pos++] = heap[arg2].name[0];
	    str[pos++] = heap[arg2].name[1];
	    str[pos++] = heap[arg2].name[2];
	    str[pos++] = heap[arg2].name[3];
	    str[pos++] = heap[arg2].name[4];
	}
	str[pos] = NUL;
    } else if (isUni6(c)) {
	str = malloc(6 * n + 10);
	pos = 0;
	for (i = 0; i < n; i++) {
	    str[pos++] = heap[arg2].name[0];
	    str[pos++] = heap[arg2].name[1];
	    str[pos++] = heap[arg2].name[2];
	    str[pos++] = heap[arg2].name[3];
	    str[pos++] = heap[arg2].name[4];
	    str[pos++] = heap[arg2].name[5];
	}
	str[pos] = NUL;
    }

    int res = make_str(str);
    free(str);
    return res;

}


int f_parse_number(int arglist, int th)
{
    int arg1, res;
    char *e;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "parse-number", arglist, th);
    if (!stringp(arg1))
	error(NOT_STR, "parse-number", arg1, th);
    if (strcmp(GET_NAME(arg1), "") == 0)
	error(CANT_PARSE, "parse-number", arg1, th);

    replace_stok_buf(GET_NAME(arg1));

    if (bignum_token(stok.buf))
	return (make_big(stok.buf));

    if (dec_token(stok.buf))
	return (make_int((int) strtol(stok.buf, &e, 10)));

    if (int_token(stok.buf))
	return (make_int(strtol(stok.buf, &e, 10)));

    if (flt_token(stok.buf))
	return (make_flt(atof(stok.buf)));

    if ((res = expt_token(stok.buf))) {
	if (res == 2)
	    error(FLT_OVERF, "number-parse", arg1, th);
	else if (res == 3)
	    error(FLT_UNDERF, "number-parse", arg1, th);
	return (make_flt(atof(stok.buf)));
    }

    if (bin_token(stok.buf))
	return (read_bin(stok.buf));

    if (oct_token(stok.buf))
	return (read_oct(stok.buf));

    if (hex_token(stok.buf))
	return (read_hex(stok.buf));


    error(CANT_PARSE, "parse-number", arg1, th);
    return (UNDEF);
}

int f_create_string_input_stream(int arglist, int th)
{
    int arg1, res;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "create-string-input-stream", arglist, th);
    if (!stringp(arg1))
	error(NOT_STR, "create-string-input-stream", arg1, th);

    res = make_stm(stdin, EISL_INSTR, NULL);
    heap[res].name = Str_dup(GET_NAME(arg1), 1, 0, 1);
    if (heap[res].name == NULL){
    error(MALLOC_OVERF, "create-string-input-stream", NIL, th);
    }
    return (res);
}

int f_create_string_output_stream(int arglist, int th)
{
    int res;
    char *str;

    if (length(arglist) != 0)
	error(WRONG_ARGS, "create-string-output-stream", arglist, th);

    res = make_stm(stdout, EISL_OUTSTR, NULL);
    str = (char *) malloc(STRSIZE);
    if (str == NULL){
	error(MALLOC_OVERF, "create-string-output-stream", NIL, th);
    }
    heap[res].name = str;
    heap[res].name[0] = '\0';
    return (res);
}

int f_get_output_stream_string(int arglist, int th)
{
    int arg1, res;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "get-output-stream-string", arglist, th);
    if (!output_stream_p(arg1))
	error(NOT_STR, "get-output-stream-string", arg1, th);

    res = make_str(GET_NAME(arg1));
    heap[arg1].name[0] = '\0';
    return (res);
}



int f_subseq(int arglist, int th)
{
    int arg1, arg2, arg3;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if (length(arglist) != 3)
	error(WRONG_ARGS, "subseq", arglist, th);
    if (!integerp(arg2) && !longnump(arg2))
	error(NOT_INT, "subseq", arg2, th);
    if (!integerp(arg3) && !longnump(arg3))
	error(NOT_INT, "subseq", arg3, th);
    if (negativep(arg2) || negativep(arg3))
	error(OUT_OF_DOMAIN, "subseq", arglist, th);
    if (greaterp(arg2, arg3))
	error(OUT_OF_RANGE, "subseq", arglist, th);



    if (stringp(arg1)) {
	if (((int) strlen(GET_NAME(arg1))) < GET_INT(arg3))
	    error(OUT_OF_RANGE, "subseq", arglist, th);
	return (substr(arg1, GET_INT(arg2), GET_INT(arg3)));
    } else if (listp(arg1)) {
	if (length(arg1) < GET_INT(arg3))
	    error(OUT_OF_RANGE, "subseq", arglist, th);
	return (sublis(arg1, GET_INT(arg2), GET_INT(arg3)));
    } else if (vectorp(arg1)) {
	if (vector_length(arg1) < GET_INT(arg3))
	    error(OUT_OF_RANGE, "subseq", arglist, th);
	return (subvec(arg1, GET_INT(arg2), GET_INT(arg3)));
    }

    error(ILLEGAL_ARGS, "subseq", arg1, th);
    return (UNDEF);
}


int f_identity(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "identity", arglist, th);

    return (arg1);
}

int f_get_universal_time(int arglist, int th)
{
    time_t t;

    if (length(arglist) != 0)
	error(WRONG_ARGS, "get-universal-time", arglist, th);

    t = time(NULL);
    return (make_long((long long int) (t + 70 * 365.25 * 24 * 60 * 60)));
}

int f_get_internal_run_time(int arglist, int th)
{
    clock_t t;

    if (length(arglist) != 0)
	error(WRONG_ARGS, "get-internal-run-time", arglist, th);

    t = clock();
    return (make_int((int) t));
}

int f_get_internal_real_time(int arglist, int th)
{
    time_t t;

    if (length(arglist) != 0)
	error(WRONG_ARGS, "get-internal-real-time", arglist, th);

    t = time(NULL);
    return (make_long((long long int) (t * CLOCKS_PER_SEC)));
}

int f_internal_time_units_per_second(int arglist, int th)
{

    if (length(arglist) != 0)
	error(WRONG_ARGS, "internal-time-units-per-second", arglist, th);

    return (make_int(CLOCKS_PER_SEC));
}


int f_initialize_object_star(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);

    if (length(arglist) != 2)
	error(WRONG_ARGS, "initialize-object*", arglist, th);
    if (!(IS_INSTANCE(arg1)))
	error(NOT_INSTANCE, "initialize-object*", arg1, th);
    if (!listp(arg2))
	error(NOT_LIST, "initialize-object*", arg2, th);

    return (initinst(arg1, arg2));
}

/* controle */
__dead int f_quit(int arglist __unused, int th __unused)
{

    if (parent_flag)
	error(SYSTEM_ERR, "Execute dp-close before quit", NIL, th);

    if (!script_flag) {
	puts("- good bye -");
    }
    RAISE(Exit_Interp);
    exit(EXIT_SUCCESS);
}

/* extension */
static inline void SET_FLAG(int addr, flag x)
{
    REQUIRE(CELLRANGE(addr));
    heap[addr].flag = x;
}

int f_gbc(int arglist, int th)
{
    int n;

    if ((n = length(arglist)) != 0 && n != 1)
	error(WRONG_ARGS, "gbc", arglist, th);
    if (nullp(arglist))
	(void) gbc();
    else if (car(arglist) == T)
	gbc_flag = true;
    else if (car(arglist) == NIL)
	gbc_flag = false;
    else
	error(WRONG_ARGS, "gbc", arglist, th);

    return (T);
}

int f_dummyp(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "dummyp", arg1, th);

    if (GET_TAG(arg1) == DUMMY)
	return (T);
    else
	return (NIL);
}

/* object */
int f_class_of(int arglist, int th)
{
    int arg;

    arg = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "class-of", arglist, th);
    if (nullp(arg))
	return (GET_AUX(arg));
    else if (GET_OPT(arg) == SYSTEM)
	return (cbuilt_in_class);
    else if (GET_OPT(arg) == USER)
	return (cstandard_class);
    else if (symbolp(arg))
	return (csymbol);
    else
	return (GET_AUX(arg));
}

int f_instancep(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "instancep", arglist, th);
    if (!classp(arg2))
	error(NOT_CLASS, "instancep", arg2, th);



    if (symbolp(arg1) && arg1 != NIL && arg1 != T) {
	if (arg2 == csymbol)
	    return (T);
	else if (subclassp(csymbol, arg2))
	    return (T);
	else
	    return (NIL);
    } else if (IS_GENERIC(arg1) && strcmp(GET_NAME(arg1), "CREATE") == 0) {
	/* (instancep #'create (class <standard-generic-function>)) => NIL) */
	if (subclassp(GET_AUX(arg1), arg2))
	    return (T);
	else
	    return (NIL);
    } else if (GET_OPT(arg1) == USER && arg2 == cstandard_class)
	/* user defined class instance is standard-class */
	return (T);
    else if (GET_AUX(arg1) == arg2)
	return (T);
    else if (subclassp(GET_AUX(arg1), arg2))
	return (T);
    else if (GET_OPT(arg1) == SYSTEM && arg2 == cbuilt_in_class)
	return (T);
    else
	return (NIL);
}

int f_subclassp(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "subclassp", arglist, th);
    if (!classp(arg1))
	error(NOT_CLASS, "subclassp", arg2, th);
    if (!classp(arg2))
	error(NOT_CLASS, "subclassp", arg2, th);


    if (subclassp(arg1, arg2))
	return (T);
    else
	return (NIL);
}


int f_generic_function_p(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "generic-function-p", arglist, th);

    if (IS_GENERIC(arg1))
	return (T);
    else
	return (NIL);
}



int f_next_method_p(int arglist, int th)
{
    int method;

    if (generic_func == NIL)
	error(UNDEF_FUN, "next-method-p", NIL, th);
    if (length(arglist) != 0)
	error(WRONG_ARGS, "next-method-p", arglist, th);

    method = cdr(next_method);
    while (!nullp(method)) {
	int varlist;

	varlist = car(GET_CAR(car(method)));
	if (adaptp(varlist, generic_vars)) {
	    return (T);
	}
	method = cdr(method);
    }
    return (NIL);
}

int f_call_next_method(int arglist, int th)
{
    int varlist, body, res, pexist = 0, qexist = 0, caller, save1, save2;

    if (generic_func == NIL)
	error(UNDEF_FUN, "call-next-method", NIL, th);
    if (length(arglist) != 0)
	error(WRONG_ARGS, "call-next-method", arglist, th);
    if (nullp(cdr(next_method)))
	error(IMPROPER_ARGS, "call-next-method",
	      GET_CAR(car(next_method)), th);
    if (GET_OPT(car(next_method)) != AROUND
	&& GET_OPT(car(next_method)) != PRIMARY) {
	error(IMPROPER_ARGS, "call-next-method",
	      GET_CAR(car(next_method)), th);
    }

    res = NIL;
    varlist = NIL;
    save1 = next_method;
    caller = car(next_method);
    next_method = cdr(next_method);
    if (GET_OPT(caller) == PRIMARY) {
	pexist = 1;
	while (!nullp(next_method)) {
	    varlist = car(GET_CAR(car(next_method)));
	    /* match(x,y) if sameclass or subclass return 1 else 0 */
	    if (adaptp(varlist, generic_vars)) {
		varlist = genlamlis_to_lamlis(varlist);
		body = cdr(GET_CAR(car(next_method)));
		bind_arg(varlist, generic_vars, th);
		while (!nullp(body)) {
		    res = eval(car(body), th);
		    body = cdr(body);
		}
		unbind(th);
		goto exit;
	    }
	    next_method = cdr(next_method);
	}
    } else {
	while (!nullp(next_method)) {
	    varlist = car(GET_CAR(car(next_method)));
	    /* match(x,y) if sameclass or subclass return 1 else 0 */
	    if (adaptp(varlist, generic_vars)) {
		if (GET_OPT(car(next_method)) == AROUND
		    || GET_OPT(car(next_method)) == BEFORE
		    || GET_OPT(car(next_method)) == AFTER) {
		    qexist = 1;
		}
		if (GET_OPT(car(next_method)) == PRIMARY) {
		    pexist = 1;
		}
		/* if only qualifier or sameclass-primary, eval method */
		if ((GET_OPT(car(next_method)) == AROUND
		     || GET_OPT(car(next_method)) == BEFORE
		     || GET_OPT(car(next_method)) == AFTER)
		    || GET_OPT(car(next_method)) == PRIMARY) {
		    varlist = genlamlis_to_lamlis(varlist);
		    body = cdr(GET_CAR(car(next_method)));
		    save2 = multiple_call_next_method;
		    multiple_call_next_method =
			has_multiple_call_next_method_p(body);
		    bind_arg(varlist, generic_vars, th);
		    while (!nullp(body)) {
			res = eval(car(body), th);
			body = cdr(body);
		    }
		    multiple_call_next_method = save2;
		    unbind(th);
		}
		if (GET_OPT(car(next_method)) == AROUND) {
		    goto exit;
		}
	    }
	    next_method = cdr(next_method);
	}
      exit:
	if (pexist == 0 && qexist == 0)
	    error(NOT_EXIST_METHOD, "call-next-method", generic_vars, th);

	if (multiple_call_next_method) {
	    next_method = save1;
	}


	return (res);
    }
    return (NIL);
}



/* condition */
int f_error(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);	/* error-string */
    arg2 = cdr(arglist);	/* obj */

    if (!stringp(arg1))
	error(NOT_STR, "error", arg1, th);

    return (signal_condition
	    (makeusercond(csimple_error, arg1, arg2), NIL, th));
}

int f_cerror(int arglist, int th)
{
    int arg1, arg2, arg3;

    arg1 = car(arglist);	/* continue-string */
    arg2 = cadr(arglist);	/* error-string */
    arg3 = cddr(arglist);	/* obj */
    if (!stringp(arg1))
	error(NOT_STR, "error", arg1, th);
    if (!stringp(arg2))
	error(NOT_STR, "error", arg2, th);

    return (signal_condition(makeusercond(cerror, arg2, arg3), arg1, th));
}


int f_signal_condition(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "signal-condition", arglist, th);

    /* if arg2 is not nil, it means continuable error. 
     *  signal_condition must stop continuation.
     *  So,pop error_handler. and move control to outer error_hander.
     */
    if (arg2 != NIL)
	error_handler = cdr(error_handler);

    return (signal_condition(arg1, arg2, th));
}

int f_simple_error_format_string(int arglist, int th)
{
    int arg1, vars, val;

    arg1 = car(arglist);
    if (!subclassp(GET_AUX(arg1), cerror) && GET_AUX(arg1) != cerror)
	error(SIMPLE_ERR, "simple-error-format-string", arg1, th);

    vars = GET_CDR(arg1);
    val = cdr(assq(make_sym("a"), vars));
    return (val);
}

int f_simple_error_format_arguments(int arglist, int th)
{
    int arg1, vars, val;

    arg1 = car(arglist);
    if (!subclassp(GET_AUX(arg1), cerror) && GET_AUX(arg1) != cerror)
	error(SIMPLE_ERR, "simple-error-format-arguments", arg1, th);

    vars = GET_CDR(arg1);
    val = cdr(assq(make_sym("b"), vars));
    return (val);
}

int f_arithmetic_error_operation(int arglist, int th)
{
    int arg1, fun;

    arg1 = car(arglist);
    if (!subclassp(GET_AUX(arg1), cerror) && GET_AUX(arg1) != cerror)
	error(ARITHMETIC_ERR, "arithmetic-error-operation", arg1, th);

    fun = GET_CAR(cdr(assoc(make_sym("c"), GET_CDR(arg1))));
    return (fun);
}


int f_arithmetic_error_operands(int arglist, int th)
{
    int arg1, fun;

    arg1 = car(arglist);
    if (!subclassp(GET_AUX(arg1), cerror) && GET_AUX(arg1) != cerror)
	error(ARITHMETIC_ERR, "arithmetic-error-operands", arg1, th);

    fun = cdr(assoc(make_sym("b"), GET_CDR(arg1)));
    return (fun);
}

int f_domain_error_object(int arglist, int th)
{
    int arg1, fun;

    arg1 = car(arglist);
    if (!subclassp(GET_AUX(arg1), cerror) && GET_AUX(arg1) != cerror)
	error(DOMAIN_ERR, "domain-error-object", cons(arg1, cdomain_error),
	      th);

    fun = cdr(assoc(make_sym("f"), GET_CDR(arg1)));
    return (fun);
}

int f_domain_error_expected_class(int arglist, int th)
{
    int arg1, fun;

    arg1 = car(arglist);
    if (!subclassp(GET_AUX(arg1), cerror) && GET_AUX(arg1) != cerror)
	error(DOMAIN_ERR, "domain-error-expected-class",
	      cons(arg1, cdomain_error), th);

    fun = cdr(assoc(make_sym("g"), GET_CDR(arg1)));
    return (fun);
}

int f_parse_error_string(int arglist, int th)
{
    int arg1, fun;

    arg1 = car(arglist);
    if (!subclassp(GET_AUX(arg1), cerror) && GET_AUX(arg1) != cerror)
	error(DOMAIN_ERR, "parse-error-string", cons(arg1, cparse_error),
	      th);

    fun = cdr(assoc(make_sym("h"), GET_CDR(arg1)));
    return (fun);
}


int f_parse_error_expected_class(int arglist, int th)
{
    int arg1, fun;

    arg1 = car(arglist);
    if (!subclassp(GET_AUX(arg1), cerror) && GET_AUX(arg1) != cerror)
	error(DOMAIN_ERR, "parse-error-expected-class",
	      cons(arg1, cparse_error), th);

    fun = cdr(assoc(make_sym("g"), GET_CDR(arg1)));
    return (fun);
}


int f_stream_error_stream(int arglist, int th)
{
    int arg1, fun;

    arg1 = car(arglist);
    if (!subclassp(GET_AUX(arg1), cerror) && GET_AUX(arg1) != cerror)
	error(NOT_STREAM_ERROR, "stream-error-stream", arg1, th);

    fun = cdr(assoc(make_sym("i"), GET_CDR(arg1)));
    return (fun);
}

int f_undefined_entity_name(int arglist, int th)
{
    int arg1, fun;

    arg1 = car(arglist);
    if (!subclassp(GET_AUX(arg1), cerror) && GET_AUX(arg1) != cerror)
	error(UNDEF_ENTITY, "undefined-entity-name", arg1, th);

    fun = cdr(assoc(make_sym("j"), GET_CDR(arg1)));
    return (fun);
}

int f_undefined_entity_namespace(int arglist, int th)
{
    int arg1, fun;

    arg1 = car(arglist);
    if (!subclassp(GET_AUX(arg1), cerror) && GET_AUX(arg1) != cerror)
	error(UNDEF_ENTITY, "undefined-entity-namespace", arg1, th);

    fun = cdr(assoc(make_sym("k"), GET_CDR(arg1)));
    return (fun);
}

int f_condition_continuable(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);

    if (!subclassp(GET_AUX(arg1), cerror) && GET_AUX(arg1) != cerror)
	error(SERIOUS_ERR, "condition-continuable", arg1, th);

    if (GET_OPT(arg1) == NOTCONT)
	return (NIL);
    else
	return (make_str(GET_NAME(arg1)));
}

int f_continue_condition(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);

    if (GET_OPT(arg1) != CONTINUABLE)
	error(ILLEGAL_FORM, "continue-condition", arg1, th);

    /* memo
     *  if error is continuable signal_condition set_jump
     *  continue-condition longjump to signal_condition. 
     */
    cont_arg = arg2;
    longjmp(cont_buf, 1);
}
