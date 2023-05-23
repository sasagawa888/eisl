/*
 * ISLisp standard syntax functions
 */


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <setjmp.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "eisl.h"
#include "compat/nana_stubs.h"
#include "fmt.h"
#include "str.h"
#include "mem.h"


#define TAGBODY_LEN_MAX 100

void init_syntax(void)
{
    def_fsubr("LAMBDA", f_lambda);
    def_fsubr("LABELS", f_labels);
    def_fsubr("FLET", f_flet);
    def_fsubr("LET", f_let);
    def_fsubr("LET*", f_letstar);
    def_fsubr("SETQ", f_setq);
    def_fsubr("SETF", f_setf);
    def_fsubr("SET-DYNAMIC", f_set_dynamic);
    def_fsubr("DEFCONSTANT", f_defconstant);
    def_fsubr("DEFUN", f_defun);
    def_fsubr("DEFMACRO", f_defmacro);
    def_fsubr("DEFGLOBAL", f_defglobal);
    def_fsubr("DEFDYNAMIC", f_defdynamic);
    def_fsubr("DYNAMIC", f_dynamic);
    def_fsubr("FUNCTION", f_function);
    def_fsubr("FUNCTION*", f_function_star);
    def_fsubr("SYMBOL-FUNCTION", f_symbol_function);
    def_fsubr("CLASS", f_class);
    def_fsubr("SYMBOL-CLASS", f_symbol_class);
    def_fsubr("AND", f_and);
    def_fsubr("OR", f_or);
    def_fsubr("IF", f_if);
    def_fsubr("COND", f_cond);
    def_fsubr("WHILE", f_while);
    def_fsubr("FOR", f_for);
    def_fsubr("BLOCK", f_block);
    def_fsubr("RETURN-FROM", f_return_from);
    def_fsubr("CASE", f_case);
    def_fsubr("CASE-USING", f_case_using);
    def_fsubr("CONVERT", f_convert);
    def_fsubr("PROGN", f_progn);
    def_fsubr("DEFCLASS", f_defclass);
    def_fsubr("DEFGENERIC", f_defgeneric);
    def_fsubr("DEFGENERIC*", f_defgeneric_star);
    def_fsubr("DEFMETHOD", f_defmethod);
    def_fsubr("DYNAMIC-LET", f_dynamic_let);
    def_fsubr("IGNORE-ERRORS", f_ignore_errors);
    def_fsubr("IMPORT", f_import);
    def_fsubr("CATCH", f_catch);
    def_fsubr("THROW", f_throw);
    def_fsubr("TAGBODY", f_tagbody);
    def_fsubr("GO", f_go);
    def_fsubr("UNWIND-PROTECT", f_unwind_protect);
    def_fsubr("WITH-STANDARD-INPUT", f_with_standard_input);
    def_fsubr("WITH-STANDARD-OUTPUT", f_with_standard_output);
    def_fsubr("WITH-ERROR-OUTPUT", f_with_error_output);
    def_fsubr("WITH-HANDLER", f_with_handler);
    def_fsubr("WITH-OPEN-INPUT-FILE", f_with_open_input_file);
    def_fsubr("WITH-OPEN-OUTPUT-FILE", f_with_open_output_file);
    def_fsubr("WITH-OPEN-IO-FILE", f_with_open_io_file);
    def_fsubr("THE", f_the);
    def_fsubr("ASSURE", f_assure);
    def_fsubr("TIME", f_time);
    def_fsubr("TRACE", f_trace);
    def_fsubr("UNTRACE", f_untrace);
    def_fsubr("DEFMODULE", f_defmodule);
}

// --FSUBR-----------
int f_lambda(int arglist)
{

    if (nullp(arglist))
	error(NOT_EXIST_ARG, "lambda", NIL);
    if (duplicate_list_p(car(arglist)))
	error(IMPROPER_ARGS, "lambda", car(arglist));
    if (improper_list_p(car(arglist)))
	error(IMPROPER_ARGS, "lambda", car(arglist));
    if (illegal_lambda_p(car(arglist)))
	error(ILLEGAL_ARGS, "lambda", car(arglist));
    if (!symbol_list_p(car(arglist)))
	error(OUT_OF_DOMAIN, "lambda", car(arglist));

    return (make_func("", arglist));
}

int f_labels(int arglist)
{
    int arg1, arg2, save, func, res, temp;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if (improper_list_p(arglist))
	error(IMPROPER_ARGS, "labels", arglist);
    if (nullp(arglist))
	error(NOT_EXIST_ARG, "labels", NIL);
    if (!listp(arg1))
	error(IMPROPER_ARGS, "labels", arg1);
    temp = arg1;
    while (!nullp(temp)) {
	int temparg1, temparg2;

	temparg1 = car(car(temp));
	temparg2 = cdr(car(temp));
	if (length(car(temp)) < 2)
	    error(IMPROPER_ARGS, "labels", car(temp));
	if (!symbolp(temparg1))
	    error(NOT_SYM, "labels", temparg1);
	if (STRING_REF(temparg1, 0) == ':'
	    || STRING_REF(temparg1, 0) == '&')
	    error(WRONG_ARGS, "labels", temparg1);
	if (duplicate_list_p(car(temparg2)))
	    error(IMPROPER_ARGS, "labels", car(temparg2));
	if (improper_list_p(car(temparg2)))
	    error(IMPROPER_ARGS, "labels", car(temparg2));
	if (illegal_lambda_p(car(temparg2)))
	    error(ILLEGAL_ARGS, "labels", car(temparg2));
	if (!symbol_list_p(car(temparg2)))
	    error(OUT_OF_DOMAIN, "labels", car(temparg2));

	temp = cdr(temp);
    }


    save = ep;
    func = NIL;
    res = NIL;
    while (arg1 != NIL) {
	int sym, val;

	sym = caar(arg1);
	if (!symbolp(sym))
	    error(NOT_SYM, "labels", sym);
	add_lex_env(sym, NIL);
	val = make_func("", cdar(arg1));
	set_lex_env(sym, val);
	func = cons(val, func);
	arg1 = cdr(arg1);
    }
    while (func != NIL) {
	SET_CDR(car(func), ep);
	func = cdr(func);
    }
    while (arg2 != NIL) {
	res = eval(car(arg2));
	arg2 = cdr(arg2);
    }
    ep = save;
    return (res);
}

int f_flet(int arglist)
{
    int arg1, arg2, save, ep1, res, temp;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if (improper_list_p(arglist))
	error(IMPROPER_ARGS, "flet", arglist);
    if (nullp(arglist))
	error(NOT_EXIST_ARG, "flet", NIL);
    if (!listp(arg1))
	error(IMPROPER_ARGS, "flet", arg1);
    temp = arg1;
    while (!nullp(temp)) {
	int temparg1, temparg2;

	temparg1 = car(car(temp));
	temparg2 = cdr(car(temp));
	if (length(car(temp)) < 2)
	    error(IMPROPER_ARGS, "flet", car(temp));
	if (!symbolp(temparg1))
	    error(NOT_SYM, "flet", temparg1);
	if (STRING_REF(temparg1, 0) == ':'
	    || STRING_REF(temparg1, 0) == '&')
	    error(WRONG_ARGS, "flet", temparg1);
	if (duplicate_list_p(car(temparg2)))
	    error(IMPROPER_ARGS, "flet", car(temparg2));
	if (improper_list_p(car(temparg2)))
	    error(IMPROPER_ARGS, "flet", car(temparg2));
	if (illegal_lambda_p(car(temparg2)))
	    error(ILLEGAL_ARGS, "flet", car(temparg2));
	if (!symbol_list_p(car(temparg2)))
	    error(OUT_OF_DOMAIN, "flet", car(temparg2));

	temp = cdr(temp);
    }

    save = ep;
    ep1 = ep;
    res = NIL;
    while (arg1 != NIL) {
	int sym, val;

	sym = caar(arg1);
	if (!symbolp(sym))
	    error(NOT_SYM, "flet", sym);
	ep = save;
	val = make_func("", cdar(arg1));
	ep = ep1;
	add_lex_env(sym, val);
	ep1 = ep;
	arg1 = cdr(arg1);
    }
    while (arg2 != NIL) {
	res = eval(car(arg2));
	arg2 = cdr(arg2);
    }
    ep = save;
    return (res);
}

int f_let(int arglist)
{
    int arg1, arg2, save, res, temp;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if (length(arglist) == 0)
	error(WRONG_ARGS, "let", arglist);
    if (!listp(arg1))
	error(IMPROPER_ARGS, "let", arg1);
    temp = arg1;
    while (!nullp(temp)) {
	int temparg1;

	temparg1 = car(car(temp));
	if (improper_list_p(car(temp)))
	    error(IMPROPER_ARGS, "let", car(temp));
	if (length(car(temp)) != 2)
	    error(IMPROPER_ARGS, "let", car(temp));
	if (!symbolp(temparg1))
	    error(NOT_SYM, "let", temparg1);
	if (temparg1 == T || temparg1 == NIL
	    || temparg1 == make_sym("*PI*")
	    || temparg1 == make_sym("*MOST-POSITIVE-FLOAT*")
	    || temparg1 == make_sym("*MOST-NEGATIVE-FLOAT*"))
	    error(WRONG_ARGS, "let", arg1);
	if (STRING_REF(temparg1, 0) == ':'
	    || STRING_REF(temparg1, 0) == '&')
	    error(WRONG_ARGS, "let", arg1);

	temp = cdr(temp);
    }

    save = ep;
    res = NIL;
    while (arg1 != NIL) {
	int ep1, sym, val;

	ep1 = ep;
	ep = save;
	sym = caar(arg1);
	if (!symbolp(sym))
	    error(NOT_SYM, "let", sym);
	shelter_push(ep1);
	val = eval(cadar(arg1));
	shelter_pop();
	ep = ep1;
	add_lex_env(sym, val);
	arg1 = cdr(arg1);
    }
    while (arg2 != NIL) {
	shelter_push(arg2);
	res = eval(car(arg2));
	shelter_pop();
	arg2 = cdr(arg2);
    }
    ep = save;
    return (res);
}

int f_letstar(int arglist)
{
    int arg1, arg2, save, res, temp;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if (length(arglist) == 0)
	error(WRONG_ARGS, "let*", arglist);
    if (!listp(arg1))
	error(IMPROPER_ARGS, "let*", arg1);
    temp = arg1;
    while (!nullp(temp)) {
	int temparg1;

	temparg1 = car(car(temp));
	if (improper_list_p(car(temp)))
	    error(IMPROPER_ARGS, "let*", car(temp));
	if (length(car(temp)) != 2)
	    error(IMPROPER_ARGS, "let*", car(temp));
	if (!symbolp(temparg1))
	    error(NOT_SYM, "let*", temparg1);
	if (temparg1 == T || temparg1 == NIL
	    || temparg1 == make_sym("*PI*")
	    || temparg1 == make_sym("*MOST-POSITIVE-FLOAT*")
	    || temparg1 == make_sym("*MOST-NEGATIVE-FLOAT*"))
	    error(WRONG_ARGS, "let*", arg1);
	if (STRING_REF(temparg1, 0) == ':'
	    || STRING_REF(temparg1, 0) == '&')
	    error(WRONG_ARGS, "let*", arg1);

	temp = cdr(temp);
    }

    save = ep;
    res = NIL;
    while (arg1 != NIL) {
	int sym;

	sym = caar(arg1);
	if (!symbolp(sym))
	    error(NOT_SYM, "let*", sym);
	add_lex_env(sym, eval(cadar(arg1)));
	arg1 = cdr(arg1);
    }
    while (arg2 != NIL) {
	res = eval(car(arg2));
	arg2 = cdr(arg2);
    }
    ep = save;
    return (res);
}

int f_dynamic_let(int arglist)
{
    int arg1, arg2, save, res, temp;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if (length(arglist) == 0)
	error(WRONG_ARGS, "dynamic-let", arglist);
    if (!listp(arg1))
	error(IMPROPER_ARGS, "dynamic-let", arg1);
    temp = arg1;
    while (!nullp(temp)) {
	int temparg1;

	temparg1 = car(car(temp));
	if (improper_list_p(car(temp)))
	    error(IMPROPER_ARGS, "dynamic-let", car(temp));
	if (length(car(temp)) != 2)
	    error(IMPROPER_ARGS, "dynamic-let", car(temp));
	if (!symbolp(temparg1))
	    error(NOT_SYM, "dynamic-let", temparg1);
	if (temparg1 == T || temparg1 == NIL
	    || temparg1 == make_sym("*PI*")
	    || temparg1 == make_sym("*MOST-POSITIVE-FLOAT*")
	    || temparg1 == make_sym("*MOST-NEGATIVE-FLOAT*"))
	    error(WRONG_ARGS, "dynamic-let", arg1);
	if (STRING_REF(temparg1, 0) == ':'
	    || STRING_REF(temparg1, 0) == '&')
	    error(WRONG_ARGS, "dynamic-let", arg1);

	temp = cdr(temp);
    }

    save = dp;
    res = NIL;
    while (arg1 != NIL) {
	int dp1, sym, val;

	dp1 = dp;
	dp = save;
	shelter_push(dp1);
	sym = caar(arg1);
	if (!symbolp(sym))
	    error(NOT_SYM, "dynamic-let", sym);
	val = eval(cadar(arg1));
	dp = dp1;
	shelter_pop();
	add_dyn_env(sym, val);
	arg1 = cdr(arg1);
    }
    while (arg2 != NIL) {
	res = eval(car(arg2));
	arg2 = cdr(arg2);
    }
    dp = save;
    return (res);
}


int f_setf(int arglist)
{
    int arg1, arg2, newform, var = 0, res;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    newform = NIL;
    if (length(arglist) != 2)
	error(WRONG_ARGS, "setf", arglist);
    if (arg1 == T || arg1 == NIL)
	error(CANT_MODIFY, "setf", arg1);
    if (listp(arg1)
	&& eqlp(make_int(1),
		cdr(assoc(make_sym("read"), GET_AUX(car(arg1))))))
	error(CANT_MODIFY, "setf", arg1);
    if (improper_list_p(arglist))
	error(IMPROPER_ARGS, "setf", arglist);

    if (listp(arg1) && eqp(car(arg1), make_sym("AREF"))) {
	newform = cons(make_sym("SET-AREF"), cons(arg2, cdr(arg1)));
    } else if (listp(arg1) && eqp(car(arg1), make_sym("GAREF"))) {
	newform = cons(make_sym("SET-GAREF"), cons(arg2, cdr(arg1)));
    } else if (listp(arg1) && eqp(car(arg1), make_sym("ELT"))) {
	newform = cons(make_sym("SET-ELT"), cons(arg2, cdr(arg1)));
    } else if (listp(arg1) && eqp(car(arg1), make_sym("PROPERTY"))) {
	newform = cons(make_sym("SET-PROPERTY"), cons(arg2, cdr(arg1)));
    } else if (listp(arg1) && eqp(car(arg1), make_sym("CAR"))) {
	newform = cons(make_sym("SET-CAR"), cons(arg2, cdr(arg1)));
    } else if (listp(arg1) && eqp(car(arg1), make_sym("CDR"))) {
	newform = cons(make_sym("SET-CDR"), cons(arg2, cdr(arg1)));
    } else if (listp(arg1) && eqp(car(arg1), make_sym("DYNAMIC"))) {
	if (improper_list_p(arg1))
	    error(IMPROPER_ARGS, "dynamic", arg1);
	if (length(arg1) != 2)
	    error(IMPROPER_ARGS, "dynamic", arg1);
	newform = cons(make_sym("SET-DYNAMIC"), list2(cadr(arg1), arg2));
    } else if (listp(arg1) && macrop(car(arg1))) {
	var = f_macroexpand_1(list1(arg1));
	return (f_setf(list2(var, arg2)));
    }
    /* (setf (slot-value instance slot-name) value) */
    else if (listp(arg1) && eqp(car(arg1), make_sym("SLOT-VALUE"))) {
	newform = cons(make_sym("SET-SLOT-VALUE"), cons(arg2, cdr(arg1)));
    }
    /* e.g. (setf (access-foo-a x) 100) */
    else if (listp(arg1) && length(arg1) == 2) {
	/* a method returns it's variable name */
	if (functionp(car(arg1)) || genericp(car(arg1))) {
	    var = eval(list2(car(arg1), NIL));
	} else
	    error(IMPROPER_ARGS, "setf", arg1);

	newform =
	    cons(make_sym("SET-SLOT-VALUE"),
		 cons(arg2,
		      list2(cadr(arg1), list2(make_sym("QUOTE"), var))));
    }
    /* e.g. when (setf (foo 1 2) 3) foo was define with (defgeneric (setf foo) (x y z)) */
    else if (listp(arg1)) {
	/* e.g. above case (foo 3 1 2) */
	newform = cons(car(arg1), cons(arg2, cdr(arg1)));
	if (!genericp(car(arg1)))
	    error(ILLEGAL_FORM, "setf", arg1);
    } else if (symbolp(arg1)) {
	newform = cons(make_sym("SETQ"), list2(arg1, arg2));
    } else
	error(IMPROPER_ARGS, "setf", arglist);

    shelter_push(newform);
    res = eval(newform);
    shelter_pop();
    return (res);
}



int f_set_dynamic(int arglist)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = eval(cadr(arglist));
    if (nullp(arglist))
	error(IMPROPER_ARGS, "set-dynamic", arglist);
    if (improper_list_p(arglist))
	error(IMPROPER_ARGS, "set-dynamic", arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "set-dynamic", arglist);
    if (!symbolp(arg1))
	error(NOT_SYM, "set-dynamic", arg1);
    if (STRING_REF(arg1, 0) == ':' || STRING_REF(arg1, 0) == '&')
	error(WRONG_ARGS, "set-dynamic", arg1);

    if (find_dyn(arg1) != FAILSE) {
	set_dyn_env(arg1, arg2);
	return (arg2);
    } else
	error(UNDEF_VAR, "set-dynamic", arg1);

    return (arg2);
}


int f_setq(int arglist)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "setq", arglist);
    if (!symbolp(arg1))
	error(NOT_SYM, "setq", arg1);
    if (GET_OPT(arg1) == CONSTN)
	error(CANT_MODIFY, "setq", arg1);
    if (improper_list_p(arglist))
	error(IMPROPER_ARGS, "setq", arglist);

    arg2 = eval(arg2);
    if (find_env(arg1) != FAILSE)
	set_lex_env(arg1, arg2);
    else if (GET_OPT(arg1) == GLOBAL)
	SET_CDR(arg1, arg2);
    else
	error(UNDEF_VAR, "setq", arg1);

    return (arg2);
}

int f_defconstant(int arglist)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (improper_list_p(arglist))
	error(IMPROPER_ARGS, "defconstant", arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "defconstant", arglist);
    if (!symbolp(arg1))
	error(NOT_SYM, "defconstant", arg1);
    if (arg1 == T || arg1 == NIL || arg1 == make_sym("*PI*") ||
	arg1 == make_sym("*MOST-POSITIVE-FLOAT*")
	|| arg1 == make_sym("*MOST-NEGATIVE-FLOAT*"))
	error(WRONG_ARGS, "defconstant", arg1);
    if (STRING_REF(arg1, 0) == ':' || STRING_REF(arg1, 0) == '&')
	error(WRONG_ARGS, "defconstant", arg1);
    if (!top_flag && !ignore_topchk)
	error(NOT_TOP_LEVEL, "defconstant", arglist);

    SET_CDR(arg1, eval(arg2));
    SET_OPT(arg1, CONSTN);	/* constant */
    return (arg1);

}

int f_defun(int arglist)
{
    int arg1, arg2, val;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if (length(arglist) < 2)
	error(WRONG_ARGS, "defun", arglist);
    if (!symbolp(arg1))
	error(NOT_SYM, "defun", arg1);
    if (IS_SUBR(GET_CAR(arg1)))
	error(CANT_MODIFY, "defun", arg1);
    if (IS_FSUBR(GET_CAR(arg1)))
	error(CANT_MODIFY, "defun", arg1);
    if (STRING_REF(arg1, 0) == ':' || STRING_REF(arg1, 0) == '&')
	error(WRONG_ARGS, "defun", arg1);
    if (duplicate_list_p(car(arg2)))
	error(IMPROPER_ARGS, "defun", car(arg2));
    if (improper_list_p(car(arg2)))
	error(IMPROPER_ARGS, "defun", car(arg2));
    if (illegal_lambda_p(car(arg2)))
	error(ILLEGAL_ARGS, "defun", car(arg2));
    if (!symbol_list_p(car(arg2)))
	error(OUT_OF_DOMAIN, "defun", car(arg2));

    val = make_func(GET_NAME(arg1), arg2);
    SET_CAR(arg1, val);
    return (arg1);
}

int f_defmacro(int arglist)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);

    if (length(arglist) < 2)
	error(WRONG_ARGS, "defmacro", arglist);
    if (!symbolp(arg1))
	error(NOT_SYM, "defmacro", arg1);
    if (GET_OPT(arg1) == CONSTN)
	error(CANT_MODIFY, "defmacro", arg1);
    if (IS_SUBR(GET_CAR(arg1)))
	error(CANT_MODIFY, "defmacro", arg1);
    if (IS_FSUBR(GET_CAR(arg1)))
	error(CANT_MODIFY, "defmacro", arg1);
    if (improper_list_p(arg2)) {
	error(IMPROPER_ARGS, "defmacro", arg2);
    }
    if (duplicate_list_p(car(arg2)))
	error(IMPROPER_ARGS, "defmacro", car(arg2));
    if (improper_list_p(car(arg2))) {
	error(IMPROPER_ARGS, "defmacro", car(arg2));
    }
    if (illegal_lambda_p(car(arg2))) {
	error(ILLEGAL_ARGS, "defmacro", car(arg2));
    }
    if (!symbol_list_p(car(arg2))) {
	error(OUT_OF_DOMAIN, "defmacro", car(arg2));
    }
    if (!top_flag && !ignore_topchk)
	error(NOT_TOP_LEVEL, "defmacro", arglist);


    bind_macro(GET_NAME(arg1), arg2);
    return (arg1);
}

int f_defglobal(int arglist)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (improper_list_p(arglist))
	error(IMPROPER_ARGS, "defglobal", arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "defglobal", arglist);
    if (!symbolp(arg1))
	error(NOT_SYM, "defglobal", arg1);
    if (GET_OPT(arg1) == CONSTN)
	error(CANT_MODIFY, "defglobal", arg1);
    if (STRING_REF(arg1, 0) == ':' || STRING_REF(arg1, 0) == '&')
	error(ILLEGAL_ARGS, "defglobal", arg1);

    arg2 = big_to_parmanent(eval(arg2));
    SET_CDR(arg1, arg2);
    SET_OPT(arg1, GLOBAL);

    return (arg1);
}

int f_defdynamic(int arglist)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (improper_list_p(cdr(arglist)))
	error(IMPROPER_ARGS, "defdynamic", arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "defdynamic", arglist);
    if (!symbolp(arg1))
	error(NOT_SYM, "defdynamic", arg1);
    if (STRING_REF(arg1, 0) == ':' || STRING_REF(arg1, 0) == '&')
	error(WRONG_ARGS, "defdynamic", arg1);


    set_dyn_env(arg1, eval(arg2));
    return (arg1);
}

int f_dynamic(int arglist)
{
    int arg1, res;

    arg1 = car(arglist);
    if (improper_list_p(arglist))
	error(IMPROPER_ARGS, "dynamic", arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "dynamic", arglist);
    if (!symbolp(arg1))
	error(NOT_SYM, "dynamic", arg1);

    res = find_dyn(arg1);
    if (res == FAILSE)
	error(UNDEF_DYN, "dynamic", arg1);

    return (res);
}

int f_and(int arglist)
{

    if (nullp(arglist))
	return (T);
    else if (nullp(cdr(arglist)))
	return (eval(car(arglist)));
    else if (eval(car(arglist)) != NIL)
	return (f_and(cdr(arglist)));
    else
	return (NIL);

}

int f_or(int arglist)
{
    int temp;

    if (nullp(arglist))
	return (NIL);
    else if (nullp(cdr(arglist)))
	return (eval(car(arglist)));
    else if ((temp = eval(car(arglist))) == NIL)
	return (f_or(cdr(arglist)));
    else
	return (temp);

    return (UNDEF);
}

int f_function(int arglist)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "function", arglist);
    if (improper_list_p(arglist))
	error(ILLEGAL_FORM, "function", arglist);

    if (symbolp(arg1)) {
	int res;

	res = find_env(arg1);
	if (IS_FUNC(res))
	    return (res);
	else if (IS_FSUBR(GET_CAR(arg1)))
	    error(UNDEF_FUN, "function", arg1);
	else if (macrop(arg1))
	    error(UNDEF_FUN, "function", arg1);
	else if (GET_CAR(arg1) != NIL)
	    return (GET_CAR(arg1));
	else
	    error(UNDEF_FUN, "function", arg1);
    } else if (listp(arg1) && eqp(car(arg1), make_sym("lambda")))
	return (eval(arg1));
    else
	error(NOT_FUNC, "function", arg1);
    return (UNDEF);
}

/*
 * function* diffrence of function is that return nil
 * defclass uses this function*
 */
int f_function_star(int arglist)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "function*", arglist);
    if (improper_list_p(arglist))
	error(ILLEGAL_ARGS, "function*", arglist);

    if (symbolp(arg1)) {
	int res;

	res = find_env(arg1);
	if (IS_FUNC(res))
	    return (res);
	else if (GET_CAR(arg1) != NIL)
	    return (GET_CAR(arg1));
	else
	    return (NIL);
    } else if (listp(arg1) && eqp(car(arg1), make_sym("lambda")))
	return (eval(arg1));
    else
	return (NIL);
    return (UNDEF);
}

int f_symbol_function(int arglist)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "symbol-function", arglist);

    if (symbolp(arg1)) {
	int sym, res;

	sym = find_env(arg1);
	if (sym == FAILSE && GET_CDR(arg1) != NIL)
	    sym = GET_CDR(arg1);

	if (!symbolp(sym))
	    error(UNDEF_FUN, "symbol-function", arg1);

	res = find_env(sym);
	if (IS_FUNC(res))
	    return (res);
	else if (GET_CAR(sym) != NIL)
	    return (GET_CAR(sym));
	else
	    error(UNDEF_FUN, "symbol-function", sym);
    } else
	error(ILLEGAL_ARGS, "symbol-function", arg1);
    return (UNDEF);
}

int f_class(int arglist)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "class", arglist);
    if (!symbolp(arg1))
	error(NOT_SYM, "class", arglist);
    if (GET_AUX(arg1) == NIL)
	error(UNDEF_CLASS, "class", arg1);
    if (GET_AUX(arg1) == csymbol && GET_OPT(arg1) != SYSTEM)
	error(UNDEF_CLASS, "class", arg1);

    return (GET_AUX(arg1));
}

int f_symbol_class(int arglist)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "symbol-class", arglist);

    if (symbolp(arg1)) {
	int sym;

	sym = find_env(arg1);
	if (sym == FAILSE && GET_CDR(arg1) != NIL)
	    sym = GET_CDR(arg1);

	if (!symbolp(sym))
	    error(UNDEF_CLASS, "symbol-class", arg1);

	if (GET_AUX(sym) == NIL)
	    error(UNDEF_CLASS, "symbol-class", sym);
	if (GET_AUX(sym) == csymbol && GET_OPT(sym) != SYSTEM)
	    error(UNDEF_CLASS, "class", sym);

	return (GET_AUX(sym));
    } else {
	error(ILLEGAL_ARGS, "symbol-class", arg1);
	return (UNDEF);
    }
}



int f_if(int arglist)
{
    int arg1, arg2, arg3, n;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if ((n = length(arglist)) < 2 || n > 3)
	error(WRONG_ARGS, "if", arglist);
    if (improper_list_p(arglist))
	error(WRONG_ARGS, "if", arglist);

    if (length(arglist) == 3)
	arg3 = car(cdr(cdr(arglist)));
    else
	arg3 = NIL;

    if (!(nullp(eval(arg1))))
	return (eval(arg2));
    else {
	return (eval(arg3));
    }
}

int f_cond(int arglist)
{
    int arg1, arg2, arg3;

    if (nullp(arglist))
	return (NIL);

    arg1 = car(arglist);
    arg2 = car(arg1);
    arg3 = cdr(arg1);
    if (nullp(arg1))
	error(IMPROPER_ARGS, "cond", arglist);
    if (improper_list_p(arg1))
	error(IMPROPER_ARGS, "cond", arg1);


    if (length(arg1) == 1 && atomp(arg2) && !nullp(eval(arg2)))
	return (arg2);
    else if (!nullp(eval(arg2)))
	return (f_progn(arg3));
    else
	return (f_cond(cdr(arglist)));
}

int f_while(int arglist)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    while (eval(arg1) != NIL) {
	f_progn(arg2);
    }
    return (NIL);
}

int f_for(int arglist)
{
    int arg1, arg2, arg3, iter, temp, save, res, temparg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = cddr(arglist);
    if (length(arglist) < 2)
	error(WRONG_ARGS, "for", arglist);
    if (!listp(arg1))
	error(NOT_LIST, "for", arg1);
    if (!listp(arg2))
	error(NOT_LIST, "for", arg2);
    if (nullp(arg2))
	error(IMPROPER_ARGS, "for", arg2);

    temp = arg1;
    temparg2 = NIL;
    while (!nullp(temp)) {
	int temp1, temparg1;

	temp1 = car(temp);
	if (!listp(temp1))
	    error(IMPROPER_ARGS, "for", temp1);
	temparg1 = car(temp1);

	if (!symbolp(temparg1))
	    error(NOT_SYM, "for", temparg1);
	if (STRING_REF(temparg1, 0) == ':'
	    || STRING_REF(temparg1, 0) == '&')
	    error(WRONG_ARGS, "for", arg1);
	if (temparg1 == T || temparg1 == NIL
	    || temparg1 == make_sym("*PI*")
	    || temparg1 == make_sym("*MOST-POSITIVE-FLOAT*")
	    || temparg1 == make_sym("*MOST-NEGATIVE-FLOAT*"))
	    error(WRONG_ARGS, "for", temparg1);
	if (length(temp1) != 2 && length(temp1) != 3)
	    error(IMPROPER_ARGS, "for", temp1);
	if (member(temparg1, temparg2))
	    error(IMPROPER_ARGS, "for", temparg1);

	temparg2 = cons(temparg1, temparg2);
	temp = cdr(temp);
    }

    save = ep;

    iter = arg1;
    /* initilize local variable */
    while (iter != NIL) {
	add_lex_env(caar(iter), eval(cadar(iter)));
	iter = cdr(iter);
    }
    /* check condition of end */
    while (eval(car(arg2)) == NIL) {
	int save1;

	save1 = ep;
	shelter_push(arg3);
	f_progn(arg3);		/* do body */
	shelter_pop();
	ep = save1;
	iter = arg1;		/* update local variable */
	temp = NIL;
	while (iter != NIL) {
	    if (!nullp(caddar(iter))) {	/* update part is not null */
		shelter_push(iter);
		shelter_push(temp);
		temp = cons(cons(caar(iter), eval(caddar(iter))), temp);
		shelter_pop();
		shelter_pop();
	    }
	    iter = cdr(iter);
	}
	while (temp != NIL) {
	    set_lex_env(caar(temp), cdar(temp));
	    temp = cdr(temp);
	}
    }
    res = f_progn(cdr(arg2));
    ep = save;
    return (res);
}

int f_block(int arglist)
{
    int arg1, arg2, tag, ret, res, unwind;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if (nullp(arglist))
	error(WRONG_ARGS, "block", arglist);
    if (improper_list_p(arglist) && nullp(arg1))
	error(WRONG_ARGS, "block", arglist);
    if (improper_list_p(arglist))
	error(IMPROPER_ARGS, "block", arglist);
    if (!symbolp(arg1))
	error(NOT_SYM, "block", arg1);


    tag = arg1;

    if (block_pt >= CTRLSTK)
	error(CTRL_OVERF, "block buffer over fllow", NIL);


    block_env[block_pt][0] = ep;	/* save environment */
    block_env[block_pt][1] = tag;	/* save tag symbol */
	block_env[block_pt][2] = unwind_nest; /* save unwind_nest */
    block_tag_check[block_pt] = find_return_from_p(macroexpand_all(arg2));
    /* save flag. if exist return-from 1 else -1 */
    block_pt++;
	unwind = unwind_nest;
    ret = setjmp(block_buf[block_pt - 1]);


    if (ret == 0) {
	res = f_progn(arg2);
	block_pt--;
	return (res);
    } else if (ret == 1) {
	/* while executing occures block & return-from, basicaly return-from resolve clean-up.
	 * But, if remain not-resolved clean-up, block resolve all clean-up.
	 */
	if (unwind == 0 && unwind_pt >= 0) {	
	    unwind_pt--;
	    while (unwind_pt >= 0) {
		apply(unwind_buf[unwind_pt], NIL);
		unwind_pt--;
	    }
	    unwind_pt = 0;
	}
	res = block_arg;
	return (res);
    }
    return (UNDEF);
}

int find_return_from_p(int x)
{
    if (nullp(x))
	return (-1);
    else if (symbolp(x) && eqp(x, make_sym("RETURN-FROM")))
	return (1);
    else if (atomp(x))
	return (-1);
    else if (find_return_from_p(car(x)) == 1
	     || find_return_from_p(cdr(x)) == 1)
	return (1);
    else
	return (-1);

}

int f_return_from(int arglist)
{
    int arg1, arg2, tag;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "return-from", arglist);
    if (!symbolp(arg1))
	error(NOT_SYM, "return-from", arg1);
    tag = arg1;
    block_pt--;
    if (block_env[block_pt][1] != tag)
	error(UNDEF_TAG, "return-from tag not exist", tag);
    if (block_tag_check[block_pt] == -1)
	error(UNDEF_TAG, "return-from tag not exist", tag);

	/* 
     *  while executing unwind-protect, execute clean-up before return-from.
     *  But, block & return-from occures in same unwind_nest level, not execute clean-up.
     */
    if (unwind_nest > 0 &&
	block_env[block_pt][2] !=
	unwind_nest && 
	unwind_pt > 0) {
	unwind_pt--;
	unwind_nest--;
	apply(unwind_buf[unwind_pt], NIL);
    }


    block_arg = f_progn(arg2);
    ep = block_env[block_pt][0];	/* restore environment */
    longjmp(block_buf[block_pt], 1);
}

int f_catch(int arglist)
{
    int arg1, arg2, i, tag, ret, res, save, unwind;

    save = sp;
    arg1 = car(arglist);	/* tag */
    arg2 = cdr(arglist);	/* body */
    if (nullp(arglist))
	error(WRONG_ARGS, "catch", arglist);
    if (arg1 == make_sym("catch"))
	error(WRONG_ARGS, "catch", arglist);
    if (nullp(arg1))
	error(WRONG_ARGS, "catch", arglist);
    if (improper_list_p(arglist))
	error(IMPROPER_ARGS, "catch", arglist);
    tag = eval(arg1);		/* tag symbol */
    if (!symbolp(tag))
	error(IMPROPER_ARGS, "catch", tag);


    if (!member(tag, catch_symbols))
	catch_symbols = cons(tag, catch_symbols);
    
	catch_data[catch_pt][0] = tag;
	catch_data[catch_pt][1] = ep;
	catch_data[catch_pt][2] = unwind_nest;
	cp = catch_pt;
	catch_pt++;
 
    if (catch_pt >= CTRLSTK)
	error(CTRL_OVERF, "catch", tag);

    error_flag = false;		/* reset error_flag */
    unwind = unwind_nest;
    ret = setjmp(catch_jump[catch_pt - 1]);

    if (ret == 0) {
	res = f_progn(arg2);
	/* after execution of arg2 tag arg1 is not neccesally*/
	cp--;
	catch_pt = cp + 1;
	return (res);
    } else if (ret == 1) {
	/* after execution of arg2 tag arg1 is not neccesally*/
	cp--;
	catch_pt = cp + 1;
	/* while executing occures chatch & throw, basicaly throw resolve clean-up.
	 * But, if remain not-resolved clean-up, catch resolve all clean-up.
	 */
	if (unwind == 0 && unwind_pt > 0) {
	    unwind_pt--;
	    while (unwind_pt >= 0) {
		apply(unwind_buf[unwind_pt], NIL);
		unwind_pt--;
	    }
	    unwind_pt = 0;
	    unwind_nest = 0;
	}

	/* while executing catch body, if error occurs restore error-handler */
	if (error_flag) {
	    error_handler = error_handler1;
	    error_flag = false;
	}

	res = catch_arg;
	catch_arg = NIL;
	sp = save;
	/* restore stack pointer. longjump destroy sp */
	return (res);
    }
    return (UNDEF);
}


int f_throw(int arglist)
{
    int arg1, arg2, tag, i;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    tag = eval(arg1);

    if (!symbolp(tag))
	error(IMPROPER_ARGS, "throw", tag);
	if ((i=find_tag(tag)) == FAILSE)
	error(UNDEF_TAG, "throw", tag);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "throw", arglist);
    if (improper_list_p(arglist))
	error(ILLEGAL_FORM, "throw", arglist);

    /* 
     *  while executing unwind-protect, execute clean-up before throw.
     *  But, catch & throw occures in same unwind_nest level, not execute clean-up.
     */
    if (unwind_nest > 0 &&
	catch_data[i][2] != unwind_nest &&
	unwind_pt > 0) {
	unwind_pt--;
	unwind_nest--;
	apply(unwind_buf[unwind_pt], NIL);
    }

    catch_arg = eval(arg2);
    ep = catch_data[i][1];	/* restore environment */
    longjmp(catch_jump[i], 1);
}

int f_tagbody(int arglist)
{
    int prog[TAGBODY_LEN_MAX], tb_line, end, i;

    if (improper_list_p(arglist))
	error(IMPROPER_ARGS, "tagbody", arglist);

    end = 0;
    while (!nullp(arglist)) {
	prog[end] = car(arglist);
	arglist = cdr(arglist);
	end++;
    }

    tb_line = 0;
    while (tb_line < end) {
	if (symbolp(prog[tb_line]))
	    tb_line++;
	else {
	    tagbody_tag = NIL;
	    eval(prog[tb_line]);
	    tb_line++;
	    /* when go was evaled */
	    if (tagbody_tag != NIL) {
		for (i = 0; i < end; i++) {
		    if (tagbody_tag == prog[i]) {
			tagbody_tag = NIL;
			tb_line = i;
			break;
		    }
		}
		if (tagbody_tag != NIL) {
		    error(UNDEF_TAG, "tagbody", tagbody_tag);
		} else {
		    continue;
		}
	    }
	}
    }

    return (NIL);
}

int f_go(int arglist)
{
    int arg1;

    arg1 = car(arglist);
    if (!symbolp(arg1))
	error(NOT_SYM, "go", arg1);
    if (improper_list_p(arglist))
	error(IMPROPER_ARGS, "go", arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "go", arglist);

    tagbody_tag = arg1;
    return (T);
}

/* memo 
 * This is for unwind-protect clean-up.
 * Following clean-up is infinit loop. In Easy-ISLisp this is error forcibly.
 *  (tagbody
 *      tag1
 *      (tagbody
 *       tag2
 *           (unwind-protect (go tag1)
 *			                 (go tag2))))
 * similarly (throw tag) (return-from tag) (go tag)
 *
 * To avoid test case in control.lsp, instantly this is error forcibly.
 * (defun test3 (fun)
 *   (unwind-protect (test4) (funcall fun)))
*/
int has_danger_p(int x){
	if (nullp(x))
		return(0);
	else if (atomp(x))
		return(0);
	else if(listp(x) && 
	        (eqp(car(x),make_sym("GO")) ||
			 eqp(car(x),make_sym("THROW")) ||
			 eqp(car(x),make_sym("RETURN-FROM")) ||
			 eqp(car(x),make_sym("FUNCALL"))))
			 return(1);
	else if(has_danger_p(car(x)) || has_danger_p(cdr(x)))
		return(1);
}


/* unwind-protect memo 
* body know while executing unwind-protect by unwind_nest.
* if throw occurs in body, throw execute clean-up before.
* but, if catch & throw set exist same unwind_nest level,
* throw dos not execute clean-up. 
* Catch save unwind_nest to tag. 
* Throw know current unwind_nest level and catch's unwind_nest level. 
*/
int f_unwind_protect(int arglist)
{
    int arg1, args, res;

    arg1 = car(arglist);	// body
    args = cdr(arglist);	// clean-up
    if (nullp(arglist))
	error(WRONG_ARGS, "unwind-protect", arglist);
    if (improper_list_p(arglist))
	error(WRONG_ARGS, "unwind-protect", arglist);
	if (has_danger_p(args))
	error(UNDEF_TAG, "unwind-protect", args);

    unwind_buf[unwind_pt] = make_func("", cons(NIL, args));	/* make thunk */
    unwind_pt++;
    unwind_nest++;
    res = eval(arg1);
    unwind_nest--;
    unwind_pt--;
    apply(unwind_buf[unwind_pt], NIL);
    return (res);
}


int f_case(int arglist)
{
    int arg1, arg2, key, res, temp;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if (nullp(car(arg2)))
	error(IMPROPER_ARGS, "case", arg2);
    temp = arg2;
    while (!nullp(temp)) {
	int temparg1;

	temparg1 = car(temp);
	if (!listp(temparg1))
	    error(WRONG_ARGS, "case", temparg1);
	if (car(temparg1) == T && length(temp) != 1)
	    error(IMPROPER_ARGS, "case", temparg1);
	if (atomp(car(temparg1)) && car(temparg1) != T)
	    error(IMPROPER_ARGS, "case", temparg1);
	temp = cdr(temp);
    }

    res = NIL;
    key = eval(arg1);
    while (arg2 != NIL) {
	if (caar(arg2) == T) {
	    res = f_progn(cdar(arg2));
	    break;
	} else if (member(key, caar(arg2)) != NIL) {
	    res = f_progn(cdar(arg2));
	    break;
	} else {
	    arg2 = cdr(arg2);
	}
    }
    return (res);
}

int f_case_using(int arglist)
{
    int arg1, arg2, arg3, key, fun, res, temp;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = cddr(arglist);
    if (nullp(car(arg3)))
	error(IMPROPER_ARGS, "case-using", arg3);
    temp = arg3;
    while (!nullp(temp)) {
	int temparg1;

	temparg1 = car(temp);
	if (!listp(temparg1))
	    error(WRONG_ARGS, "case-using", temparg1);
	if (car(temparg1) == T && length(temp) != 1)
	    error(IMPROPER_ARGS, "case-using", temparg1);
	if (atomp(car(temparg1)) && car(temparg1) != T)
	    error(IMPROPER_ARGS, "case-using", temparg1);
	temp = cdr(temp);
    }

    res = NIL;
    key = eval(arg2);
    fun = eval(arg1);
    while (arg3 != NIL) {
	if (caar(arg3) == T) {
	    res = f_progn(cdar(arg3));
	    break;
	} else if (member1(key, caar(arg3), fun) != NIL) {
	    res = f_progn(cdar(arg3));
	    break;
	} else {
	    arg3 = cdr(arg3);
	}
    }
    return (res);
}


int f_progn(int arglist)
{
    int res;

    if (improper_list_p(arglist))
	error(IMPROPER_ARGS, "progn", arglist);
    res = NIL;
    while (arglist != NIL) {
	res = eval(car(arglist));
	arglist = cdr(arglist);
    }
    return (res);
}

int f_defclass(int arglist)
{
    int arg1,
	arg2,
	arg3, arg4, sc, var, val, cl, form, initargs, abstractp, metaclass,
	save;

    arg1 = car(arglist);	/* class-name */
    arg2 = cadr(arglist);	/* super-class */
    arg3 = caddr(arglist);	/* slot-spec */
    arg4 = cdddr(arglist);	/* class-opt */

    if (!symbolp(arg1))
	error(NOT_SYM, "defclass", arg1);
    if (GET_OPT(arg1) == SYSTEM)
	error(CANT_REDEFINE, "defclass", arg1);
    if (GET_OPT(arg1) == CONSTN)
	error(CANT_MODIFY, "defclass", arg1);
    if (IS_FSUBR(GET_CAR(arg1)))
	error(CANT_MODIFY, "defclass", arg1);
    if ((STRING_REF(arg1, 0) == '&') || (STRING_REF(arg1, 0) == ':'))
	error(CANT_MODIFY, "defclass", arg1);
    if (!listp(arg2))
	error(NOT_LIST, "defclass", arg2);
    if (has_same_p(arg2))
	error(IMPROPER_ARGS, "defclass", arg2);
    if (has_sys_class_p(arg2))
	error(IMPROPER_ARGS, "defclass", arg2);
    if (not_exist_class_p(arg2))
	error(UNDEF_CLASS, "defclass", arg2);
    if (has_common_p(arg2))
	error(HAS_COMMON_CLASS, "defclass", arg2);
    if (!listp(arg3))
	error(NOT_LIST, "defclass", arg3);
    if (!top_flag && !ignore_topchk) {
	error(NOT_TOP_LEVEL, "defclass", arglist);
    }

    /* if re define class of global variable, then it's class is <invalid> */
    if (GET_CDR(arg1) != NIL) {
	SET_AUX(GET_CDR(arg1), cinvalid);
	return (arg1);
    }


    sc = arg2;
    if (subclassp(GET_AUX(arg1), cobject))
	redef_flag = true;	/* flag for check redefinition of class */

    var = NIL;
    val = UNDEF;
    initargs = NIL;
    save = ignore_topchk;
    ignore_topchk = true;	/* ignore toplevel check for defgeneric defmethod */
    SET_AUX(arg1, USER);	/* temporary set USER to avoid undef entity error of defmethod 
				   finaly set-aux formal class */
    while (!nullp(arg3)) {
	int sym,
	    ls,
	    reader,
	    writer,
	    accessor, boundp, initform, initarg, initform_flag,
	    initarg_flag;

	initarg = NIL;
	initform_flag = initarg_flag = 0;
	if (!listp(car(arg3)))
	    arg3 = list1(arg3);	/* if form=(a :reader a-read) => ((a :reader a-read)) */
	sym = caar(arg3);
	if ((STRING_REF(sym, 0) == '&') || (STRING_REF(sym, 0) == ':'))
	    error(IMPROPER_FORM, "defclass", sym);
	ls = cdar(arg3);
	if (!listp(car(arg3)))
	    error(ILLEGAL_FORM, "defclass", arg3);

	while (!nullp(ls)) {

	    if (eqp(car(ls), make_sym(":READER"))) {
		reader = cadr(ls);
		if (length(ls) < 2) {
		    error(ILLEGAL_FORM, "defclass", arg3);
		}
		if (symbolp(reader) && STRING_REF(reader, 0) == ':') {
		    error(IMPROPER_FORM, "defclass", arg3);
		}
		/*
		 * (if (not (generic-function-p (function* name)))
		 *     (defgeneric name (x)))
		 * (defmethod name ((x arg1))
		 *    (let ((y (slot-value x 'var))) (if (dummyp y) (cerror "undefined" "reader")) y))
		 *    (set-property 1 'reader 'read))
		 */
		form = list3(make_sym("IF"),
			     list2(make_sym("NOT"),
				   list2(make_sym("GENERIC-FUNCTION-P"),
					 list2(make_sym("FUNCTION*"),
					       reader))),
			     list3(make_sym("DEFGENERIC"), reader,
				   list1(make_sym("x"))));
		eval(form);
		form =
		    list4(make_sym("DEFMETHOD"), reader,
			  list1(list2(make_sym("x"), arg1)),
			  list4(make_sym("LET"),
				list1(list2
				      (make_sym("y"),
				       list3(make_sym("SLOT-VALUE"),
					     make_sym("x"),
					     list2(make_sym("QUOTE"),
						   sym)))),
				list3(make_sym("IF"),
				      list2(make_sym("EISL-DUMMYP"),
					    make_sym("y")),
				      list3(make_sym("CERROR"),
					    make_str("undefined"),
					    make_str("reader"))),
				make_sym("y")));

		eval(form);
		form = list4(make_sym("SET-PROPERTY"),
			     make_int(1),
			     list2(make_sym("QUOTE"), reader),
			     list2(make_sym("QUOTE"), make_sym("READ")));
		eval(form);
	    } else if (eqp(car(ls), make_sym(":WRITER"))) {
		writer = cadr(ls);
		if (length(ls) < 2) {
		    error(ILLEGAL_FORM, "defclass", arg3);
		}
		if (symbolp(writer) && STRING_REF(writer, 0) == ':') {
		    error(IMPROPER_FORM, "defclass", arg3);
		}
		/*
		 * (if (not (generic-function-p (function* name)))
		 * (defgeneric name (x y)))
		 * (defmethod name (x (y arg1))
		 *     (setf (slot-value y 'var) x))
		 */
		form = list3(make_sym("IF"),
			     list2(make_sym("NOT"),
				   list2(make_sym("GENERIC-FUNCTION-P"),
					 list2(make_sym("FUNCTION*"),
					       writer))),
			     list3(make_sym("DEFGENERIC"), writer,
				   list2(make_sym("x"),
					 list2(make_sym("y"), arg1))));
		eval(form);
		form =
		    list4(make_sym("DEFMETHOD"), writer,
			  list2(make_sym("x"), list2(make_sym("y"), arg1)),
			  list3(make_sym("SETF"),
				list3(make_sym("SLOT-VALUE"),
				      make_sym("y"),
				      list2(make_sym("QUOTE"), sym)),
				make_sym("x")));
		eval(form);
	    } else if (eqp(car(ls), make_sym(":ACCESSOR"))) {
		accessor = cadr(ls);
		if (length(ls) < 2) {
		    error(ILLEGAL_FORM, "defclass", arg3);
		}
		if (symbolp(accessor) && STRING_REF(accessor, 0) == ':') {
		    error(IMPROPER_FORM, "defclass", arg3);
		}
		/*
		 * (if (not (generic-function-p (function* name)))
		 *     (defgeneric name (x)))
		 * (defmethod name ((x arg1))
		 *     (let ((y (slot-value x 'var))) (if (dummyp y) (error "undefined" "accessor") y)))
		 * (defmethod name ((x <null>)) for setf syntax
		 *     'var)
		 */
		form = list3(make_sym("IF"),
			     list2(make_sym("NOT"),
				   list2(make_sym("GENERIC-FUNCTION-P"),
					 list2(make_sym("FUNCTION*"),
					       accessor))),
			     list3(make_sym("DEFGENERIC"), accessor,
				   list1(make_sym("x"))));
		eval(form);
		form =
		    list4(make_sym("DEFMETHOD"), accessor,
			  list1(list2(make_sym("x"), arg1)),
			  list4(make_sym("LET"),
				list1(list2
				      (make_sym("y"),
				       list3(make_sym("SLOT-VALUE"),
					     make_sym("x"),
					     list2(make_sym("QUOTE"),
						   sym)))),
				list3(make_sym("IF"),
				      list2(make_sym("EISL-DUMMYP"),
					    make_sym("y")),
				      list3(make_sym("CERROR"),
					    make_str("undefined"),
					    make_str("accessor"))),
				make_sym("y")));

		eval(form);
		form =
		    list4(make_sym("DEFMETHOD"), accessor,
			  list1(list2(make_sym("x"), make_sym("<NULL>"))),
			  list2(make_sym("QUOTE"), sym));
		eval(form);
	    } else if (eqp(car(ls), make_sym(":BOUNDP"))) {
		boundp = cadr(ls);
		if (nullp(boundp)) {
		    error(ILLEGAL_FORM, "defclass", arg3);
		}
		if (symbolp(boundp) && STRING_REF(boundp, 0) == ':') {
		    error(IMPROPER_FORM, "defclass", arg3);
		}
		/*
		 * (if (not (generic-function-p (function* name)))
		 * (defgeneric name (x)))
		 * (defmethod name ((x arg1))
		 *     (not (dummyp (slot-value x 'var))))
		 */
		form = list3(make_sym("IF"),
			     list2(make_sym("NOT"),
				   list2(make_sym("GENERIC-FUNCTION-P"),
					 list2(make_sym("FUNCTION*"),
					       boundp))),
			     list3(make_sym("DEFGENERIC"), boundp,
				   list1(make_sym("x"))));
		eval(form);
		form =
		    list4(make_sym("DEFMETHOD"), boundp,
			  list1(list2(make_sym("x"), arg1)),
			  list2(make_sym("NOT"),
				list2(make_sym("EISL-DUMMYP"),
				      list3(make_sym("SLOT-VALUE"),
					    make_sym("x"),
					    list2(make_sym("QUOTE"),
						  sym)))));
		eval(form);
	    } else if (eqp(car(ls), make_sym(":INITFORM"))) {
		initform = cadr(ls);
		if (length(ls) < 2) {
		    error(ILLEGAL_FORM, "defclass", arg3);
		}
		if (symbolp(initform) && STRING_REF(initform, 0) == ':') {
		    error(IMPROPER_FORM, "defclass", arg3);
		}
		if (initform_flag) {
		    error(ILLEGAL_FORM, "defclass", arg3);
		}
		initform = eval(initform);
		val = initform;
		initform_flag = 1;
	    } else if (eqp(car(ls), make_sym(":INITARG"))) {
		initarg = cadr(ls);
		if (nullp(initarg)) {
		    error(ILLEGAL_FORM, "defclass", arg3);
		}
		if (symbolp(initarg) && STRING_REF(initarg, 0) == ':') {
		    error(IMPROPER_FORM, "defclass", arg3);
		}
		if (initarg_flag) {
		    error(ILLEGAL_FORM, "defclass", arg3);
		}
		initarg_flag = 1;
	    } else
		error(ILLEGAL_FORM, "defclass", ls);

	    ls = cddr(ls);
	}

	var = cons(cons(caar(arg3), val), var);
	initargs = cons(cons(initarg, sym), initargs);
	arg3 = cdr(arg3);
    }

    abstractp = metaclass = NIL;
    int abstractp_flag;
    abstractp_flag = UNDEF;

    while (!nullp(arg4)) {
	int ls;

	if (!listp(car(arg4)))
	    error(ILLEGAL_FORM, "defclass", arg4);
	ls = car(arg4);
	if (eqp(car(ls), make_sym(":ABSTRACTP"))) {
	    abstractp = cadr(ls);
	    if (length(ls) != 2)
		error(ILLEGAL_FORM, "defclass", arg4);
	    if (abstractp != NIL && abstractp != T)
		error(ILLEGAL_FORM, "defclass", arg4);
	    if (abstractp_flag != UNDEF && abstractp != abstractp_flag)
		error(ILLEGAL_FORM, "defclass", arg4);
	    abstractp_flag = abstractp;
	} else if (eqp(car(ls), make_sym(":METACLASS"))) {
	    metaclass = cadr(ls);
	    if (length(ls) != 2)
		error(ILLEGAL_FORM, "defclass", arg4);
	    if (!eqp(metaclass, make_sym("<STANDARD-CLASS>")))
		error(ILLEGAL_FORM, "defclass", arg4);
	} else {
	    error(ILLEGAL_FORM, "defclass", ls);
	}
	arg4 = cdr(arg4);
    }
    cl = make_class(GET_NAME(arg1), sc);
    if (abstractp == T) {
	SET_OPT(cl, ABSTRACT);	/* abstract-class */
    } else if (metaclass == T) {
	SET_OPT(cl, METACLASS);	/* meta-class */
    } else {
	SET_OPT(cl, USER);	/* standard-class */
    }
    SET_CDR(cl, var);
    SET_AUX(cl, initargs);
    SET_AUX(arg1, cl);
    ignore_topchk = save;	/* restore toplevel check */
    return (arg1);
}


int f_defgeneric(int arglist)
{
    int arg1, arg2, arg3, val;

    arg1 = car(arglist);	/* func-name */
    arg2 = cadr(arglist);	/* lambda-list */
    arg3 = cddr(arglist);	/*  body */
    if (symbolp(arg1) && GET_OPT(arg1) == CONSTN) {
	error(CANT_MODIFY, "defgeneric", arg1);
    }
    if (symbolp(arg1) && (functionp(arg1) || subrp(arg1) || fsubrp(arg1))) {
	error(CANT_MODIFY, "defgeneric", arg1);
    }
    if (symbolp(arg1) && (genericp(arg1) && eqp(arg1, make_sym("CREATE")))) {
	error(CANT_MODIFY, "defgeneric", arg1);
    }
    if (symbolp(arg1)
	&& (STRING_REF(arg1, 0) == ':' || STRING_REF(arg1, 0) == '&')) {
	error(WRONG_ARGS, "defgeneric", arg1);
    }
    if (!symbolp(arg1)
	&& (listp(arg1)
	    && !(length(arg1) == 2 && eqp(car(arg1), make_sym("SETF"))
		 && symbolp(cadr(arg1))))) {
	error(ILLEGAL_FORM, "defgeneric", arg1);
    }
    if (!listp(arg2)) {
	error(NOT_LIST, "defgeneric", arg2);
    }
    if (duplicate_list_p(arg2)) {
	error(IMPROPER_ARGS, "defgeneric", arg2);
    }
    if (improper_list_p(arg2)) {
	error(IMPROPER_ARGS, "defgeneric", arg2);
    }
    if (illegal_lambda_p(arg2)) {
	error(ILLEGAL_ARGS, "defgeneric", arg2);
    }
    if (!top_flag && !ignore_topchk) {
	error(NOT_TOP_LEVEL, "defgeneric", arglist);
    }
    /* when (defgeneric (set foo) ...) */
    if (listp(arg1)) {
	arg1 = cadr(arg1);
    }

    if (!member(arg1, generic_list))
	generic_list = hcons(arg1, generic_list);

    val = make_generic(GET_NAME(arg1), arg2, arg3);
    SET_CAR(arg1, val);
    return (arg1);
}

int f_defgeneric_star(int arglist)
{
    int arg1, arg2, arg3, val;

    arg1 = car(arglist);	/* func-name */
    arg2 = cadr(arglist);	/* lambda-list */
    arg3 = cddr(arglist);	/* body */
    if (!symbolp(arg1))
	error(NOT_SYM, "defgeneric", arg1);
    if (GET_OPT(arg1) == CONSTN)
	error(CANT_MODIFY, "defgeneric", arg1);
    if (IS_FUNC(GET_CAR(arg1)))
	error(CANT_MODIFY, "defgeneric", arg1);
    if (IS_SUBR(GET_CAR(arg1)))
	error(CANT_MODIFY, "defgeneric", arg1);
    if (!listp(arg2))
	error(NOT_LIST, "defgeneric", arg2);

    if (!member(arg1, generic_list))
	generic_list = hcons(arg1, generic_list);

    val = make_generic_star(arg2, arg3);
    SET_CAR(arg1, val);
    return (arg1);
}

/*
 * if Generic function, set CDR area method object with insert sorting. 
 */
int f_defmethod(int arglist)
{
    int arg1, arg2, gen;

    arg1 = car(arglist);	/* method-name */
    arg2 = cdr(arglist);	/* parameter-profile */

    if (symbolp(arg1) && (subrp(arg1) || fsubrp(arg1))) {
	error(CANT_MODIFY, "defmethod", arg1);
    }
    if (symbolp(arg1) && (functionp(arg1) || macrop(arg1))) {
	error(ILLEGAL_FORM, "defmethod", arg1);
    }
    if (symbolp(arg1)
	&& (GET_CAR(arg1) == NIL && !member(arg1, generic_list))) {
	error(UNDEF_FUN, "defmethod", arg1);
    }
    if (!symbolp(arg1)
	&& (listp(arg1)
	    && !(length(arg1) == 2 && eqp(car(arg1), make_sym("SETF"))
		 && symbolp(cadr(arg1))))) {
	error(ILLEGAL_FORM, "defmethod", arg1);
    }
    /* when (defmethod (set foo) ...) */
    if (listp(arg1)) {
	arg1 = cadr(arg1);
    }

    if (listp(car(arg2)) && illegal_lambda_p(car(arg2))) {
	error(ILLEGAL_ARGS, "defmethod", arg2);
    }
    if (listp(car(arg2))
	&& !unified_parameter_p(GET_CAR(GET_CAR(arg1)), car(arg2))) {
	error(ILLEGAL_FORM, "defmethod", arg2);
    }
    if (listp(car(arg2)) && undef_parameter_p(car(arg2))) {
	error(UNDEF_CLASS, "defmethod", arg2);
    }
    /* if method-qualifier and method-combination of generic-function is NIL -> error */
    if (symbolp(car(arg2)) && method_qualifier_p(car(arg2))
	&& GET_PROP(GET_CAR(arg1)) == NIL)
	error(IMPROPER_ARGS, "defmethod", arg2);
    if (symbolp(car(arg2)) && !method_qualifier_p(car(arg2))) {
	error(IMPROPER_ARGS, "defmethod", arg2);
    }

    gen = generic_func = GET_CAR(arg1);
    insert_method(make_method(arg2), gen);
    generic_func = NIL;
    return (arg1);
}

int f_ignore_errors(int arglist)
{
    volatile int res, save1, save2;

    ignore_flag = true;
    save1 = input_stream;
    save2 = output_stream;
    TRY res = f_progn(arglist);
    ELSE res = NIL;
    END_TRY;
    ignore_flag = false;
    try_flag = false;
    input_stream = save1;
    output_stream = save2;

    /* 
     * if execute s-exp is (read stream) and occures an error, 
     * ignore_errors must restore original input output stream.
     */
    return res;
}

int f_with_open_input_file(int arglist)
{
    int arg1, arg2, sym, str, n, val, ep1, res;
    FILE *port;

    if (nullp(arglist) || atomp(arglist))
	error(NOT_EXIST_ARG, "with-open-input-file", NIL);
    arg1 = car(arglist);
    arg2 = cdr(arglist);
    sym = car(arg1);		/* stream-name */
    str = eval(cadr(arg1));	/* file-name */
    n = length(arg1);		/* check element */
    if (!(listp(arg1) && (n == 2 || n == 3)))
	error(ILLEGAL_FORM, "with-input-file", arg1);
    if (!symbolp(sym))
	error(NOT_SYM, "with-open-input-file", sym);
    if (!stringp(str))
	error(NOT_STR, "with-open-input-file", str);
    const char *fname = GET_NAME(str);
    if (n == 2)
	port = fopen(fname, "r");
    else
	port = fopen(fname, "rb");
    if (port == NULL) {
	error(CANT_OPEN, "with-open-input-file", str);
	return NIL;
    }
    if (n == 2)
	val = make_stm(port, EISL_INPUT, Str_dup(fname, 1, 0, 1));
    else
	val = make_stm(port, EISL_INPUT_BIN, Str_dup(fname, 1, 0, 1));
    ep1 = ep;
    add_lex_env(sym, val);
    res = f_progn(arg2);
    fclose(port);
    ep = ep1;
    return (res);
}

int f_with_open_output_file(int arglist)
{
    int arg1, arg2, sym, str, n, val, ep1, res;
    FILE *port;

    if (nullp(arglist) || atomp(arglist))
	error(NOT_EXIST_ARG, "with-open-output-file", NIL);
    arg1 = car(arglist);
    arg2 = cdr(arglist);
    sym = car(arg1);		/* stream-name */
    str = eval(cadr(arg1));	/* file-name */
    n = length(arg1);		/* check element */
    if (!(listp(arg1) && (n == 2 || n == 3)))
	error(ILLEGAL_FORM, "with-open-output-file", arg1);
    if (!symbolp(sym))
	error(NOT_SYM, "with-open-output-file", sym);
    if (!stringp(str))
	error(NOT_STR, "with-open-output-file", str);
    const char *fname = GET_NAME(str);
    if (n == 2)
	port = fopen(fname, "w");
    else
	port = fopen(fname, "wb");
    if (port == NULL) {
	error(CANT_OPEN, "with-open-output-file", str);
	return NIL;
    }
    if (n == 2)
	val = make_stm(port, EISL_OUTPUT, Str_dup(fname, 1, 0, 1));
    else
	val = make_stm(port, EISL_OUTPUT_BIN, Str_dup(fname, 1, 0, 1));
    ep1 = ep;
    add_lex_env(sym, val);
    res = f_progn(arg2);
    fclose(port);
    ep = ep1;
    return (res);
}

int f_with_open_io_file(int arglist)
{
    int arg1, arg2, sym, str, n, val, ep1, res;
    FILE *port;

    if (nullp(arglist) || atomp(arglist))
	error(NOT_EXIST_ARG, "with-open-io-file", NIL);
    arg1 = car(arglist);
    arg2 = cdr(arglist);
    sym = car(arg1);		/* stream-name */
    str = eval(cadr(arg1));	/* file-name */
    n = length(arg1);		/* check element */
    if (!(listp(arg1) && (n == 2 || n == 3)))
	error(ILLEGAL_FORM, "with-open-io-file", arg1);
    if (!symbolp(sym))
	error(NOT_SYM, "with-open-io-file", sym);
    if (!stringp(str))
	error(NOT_STR, "with-open-io-file", str);
    const char *fname = GET_NAME(str);
    if (n == 2)
	port = fopen(fname, "a+");
    else
	port = fopen(fname, "ab+");
    if (port == NULL) {
	error(CANT_OPEN, "with-open-io-file", str);
	return NIL;
    }
    if (n == 2)
	val = make_stm(port, EISL_INOUT, Str_dup(fname, 1, 0, 1));
    else
	val = make_stm(port, EISL_INOUT_BIN, Str_dup(fname, 1, 0, 1));
    ep1 = ep;
    add_lex_env(sym, val);
    res = f_progn(arg2);
    fclose(port);
    ep = ep1;
    return (res);
}

int f_with_standard_input(int arglist)
{
    int arg1, arg2, stream, save, res;

    arg1 = car(arglist);
    arg2 = cdr(arglist);

    stream = eval(arg1);
    if (!input_stream_p(stream))
	error(NOT_STREAM, "with-standard-input, stream", stream);

    save = input_stream;
    input_stream = stream;
    res = f_progn(arg2);
    input_stream = save;
    return (res);
}

int f_with_standard_output(int arglist)
{
    int arg1, arg2, stream, save, res;

    arg1 = car(arglist);
    arg2 = cdr(arglist);

    stream = eval(arg1);
    if (!output_stream_p(stream))
	error(NOT_STREAM, "with-standard-output, stream", stream);

    save = output_stream;
    output_stream = stream;
    res = f_progn(arg2);
    output_stream = save;
    return (res);
}

int f_with_error_output(int arglist)
{
    int arg1, arg2, stream, save, res;

    arg1 = car(arglist);
    arg2 = cdr(arglist);

    stream = eval(arg1);
    if (!output_stream_p(stream))
	error(NOT_STREAM, "with-error-output, stream", stream);

    save = output_stream;
    output_stream = stream;
    res = f_progn(arg2);
    output_stream = save;
    return (res);
}

int f_with_handler(int arglist)
{
    int arg1, arg2, res;

    arg1 = car(arglist);
    arg2 = cdr(arglist);

    error_handler = cons(eval(arg1), error_handler);
    res = f_progn(arg2);
    error_handler = cdr(error_handler);
    return (res);
}

int f_convert(int arglist)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(IMPROPER_ARGS, "convert", arglist);
    if (improper_list_p(arglist))
	error(IMPROPER_ARGS, "convert", arglist);
    if (!symbolp(arg2))
	error(NOT_SYM, "convert", arg2);
    if (GET_OPT(arg2) != SYSTEM)
	error(NOT_CLASS, "convert", arg2);

    arg1 = eval(arg1);
    return convert(arg1, arg2);
}


int convert(int arg1, int arg2)
{
    char str[SHORT_STRSIZE], *e;

    switch (GET_TAG(arg1)) {
    case LONGN:
	if (GET_AUX(arg2) == cinteger) {
	    return (arg1);
	} else if (GET_AUX(arg2) == cfloat) {
	    return (exact_to_inexact(arg1));
	} else if (GET_AUX(arg2) == cstring) {
#ifdef __rpi__
	    sprintf(str, "%lld", GET_LONG(arg1));
#else
	    Fmt_sfmt(str, SHORT_STRSIZE, "%D", GET_LONG(arg1));
#endif
	    return (make_str(str));
	}
	break;
    case BIGN:
	if (GET_AUX(arg2) == cinteger) {
	    return (arg1);
	} else if (GET_AUX(arg2) == cfloat) {
	    return (exact_to_inexact(arg1));
	}
	break;
    case INTN:
	if (GET_AUX(arg2) == cinteger) {
	    return (arg1);
	} else if (GET_AUX(arg2) == ccharacter) {
	    ucs4_to_utf8(GET_INT(arg1), str);
	    return (make_char(str));
	} else if (GET_AUX(arg2) == cfloat) {
	    return (exact_to_inexact(arg1));
	} else if (GET_AUX(arg2) == cstring) {
	    Fmt_sfmt(str, SHORT_STRSIZE, "%d", GET_INT(arg1));
	    return (make_str(str));
	}
	break;
    case CHR:
	if (GET_AUX(arg2) == cinteger) {
	    return (make_int(utf8_to_ucs4(GET_NAME(arg1))));
	} else if (GET_AUX(arg2) == csymbol) {
	    return (make_sym(GET_NAME(arg1)));
	} else if (GET_AUX(arg2) == ccharacter) {
	    return (arg1);
	}

	break;
    case FLTN:
	if (GET_AUX(arg2) == cfloat) {
	    return (arg1);
	} else if (GET_AUX(arg2) == cstring) {
	    double x;

	    x = GET_FLT(arg1);
	    snprintf(str, SHORT_STRSIZE, "%g", x);
	    return (make_str(str));
	}
	break;
    case SYM:
	if (GET_AUX(arg2) == csymbol) {
	    return (arg1);
	} else if (GET_AUX(arg2) == cstring) {
	    return (make_str(GET_NAME(arg1)));
	} else if (nullp(arg1) && GET_AUX(arg2) == cgeneral_vector) {
	    return (vector(arg1));
	} else if (nullp(arg1) && GET_AUX(arg2) == clist) {
	    return (arg1);
	}
	break;
    case STR:
	if (GET_AUX(arg2) == cstring) {
	    return (arg1);
	} else if (GET_AUX(arg2) == cinteger) {
	    strncpy(stok.buf, GET_NAME(arg1), BUFSIZE - 1);
	    stok.buf[BUFSIZE - 1] = '\0';

	    if (bignum_token(stok.buf)) {
		return (make_big(stok.buf));
	    } else if (int_token(stok.buf)) {
		return (make_int(strtol(stok.buf, &e, 10)));
	    } else if (bin_token(stok.buf)) {
		return (make_int((int) strtol(stok.buf, &e, 2)));
	    } else if (oct_token(stok.buf)) {
		return (make_int((int) strtol(stok.buf, &e, 8)));
	    } else if (dec_token(stok.buf)) {
		return (make_int((int) strtol(stok.buf, &e, 10)));
	    } else if (hex_token(stok.buf)) {
		return (make_int((int) strtol(stok.buf, &e, 16)));
	    }
	    break;
	} else if (GET_AUX(arg2) == cfloat) {
	    if (flt_token(GET_NAME(arg1)))
		return (make_flt(atof(GET_NAME(arg1))));
	} else if (GET_AUX(arg2) == csymbol) {
	    return (make_sym(GET_NAME(arg1)));
	} else if (GET_AUX(arg2) == cgeneral_vector) {
	    return (string_to_vector(arg1));
	} else if (GET_AUX(arg2) == clist) {
	    return (string_to_list(arg1));
	}
	break;
    case LIS:
	if (GET_AUX(arg2) == clist) {
	    return (arg1);
	} else if (GET_AUX(arg2) == cgeneral_vector) {
	    return (vector(arg1));
	}
	break;
    case VEC:
	if (GET_AUX(arg2) == cgeneral_vector) {
	    return (arg1);
	} else if (GET_AUX(arg2) == clist) {
	    return (vector_to_list(arg1));
	}
	break;
    default:
	VL(("convert tag switch default action"));
    }
    error(OUT_OF_DOMAIN, "convert", arg1);
    return (UNDEF);
}

int f_the(int arglist)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(IMPROPER_ARGS, "the", arglist);
    if (improper_list_p(arglist))
	error(IMPROPER_ARGS, "the", arglist);

    if (GET_AUX(arg1) != NIL)
	return (eval(arg2));
    else
	error(NOT_CLASS, "the", arg1);

    return (UNDEF);
}

int f_assure(int arglist)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(IMPROPER_ARGS, "assure", arglist);
    if (improper_list_p(arglist))
	error(IMPROPER_ARGS, "assure", arglist);

    arg2 = eval(arg2);
    if (GET_AUX(arg1) == GET_AUX(arg2))
	return (arg2);
    else if (subclassp(GET_AUX(arg2), GET_AUX(arg1)))
	return (arg2);
    else
	error(CANT_ASSURE, "assure", arg2);

    return (UNDEF);
}

double getETime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (double) tv.tv_usec * 1e-6;
}



int f_time(int arglist)
{
    int arg1;
    double st, en;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "time", arglist);

    st = getETime();
    eval(arg1);
    en = getETime();
    Fmt_print("Elapsed Time(second)=%.6f\n", en - st);
    return (UNDEF);
}

int f_trace(int arglist)
{

    if (nullp(arglist)) {
	return (trace_list);
    } else {
	while (!nullp(arglist)) {
	    if (!symbolp(car(arglist)))
		error(NOT_SYM, "trace", car(arglist));
	    if (!member(car(arglist), trace_list)) {
		SET_TR(car(arglist), 1);
		trace_list = cons(car(arglist), trace_list);
	    }
	    arglist = cdr(arglist);
	}
	return (T);
    }
}

int f_untrace(int arglist)
{

    if (nullp(arglist)) {
	while (!nullp(trace_list)) {
	    SET_TR(car(trace_list), 0);	/* reset trace tag of symbol */
	    SET_TR(GET_CAR(car(trace_list)), 0);	/* reset trace nest level */
	    trace_list = cdr(trace_list);
	}
    } else {
	while (!nullp(arglist)) {
	    if (!symbolp(car(arglist)))
		error(NOT_SYM, "untrace", car(arglist));
	    SET_TR(car(arglist), 0);
	    SET_TR(GET_CAR(car(arglist)), 0);
	    arglist = cdr(arglist);
	}
	trace_list = remove_list(trace_list, arglist);
    }
    return (T);
}



int f_import(int arglist)
{
    int arg1 = car(arglist);
    if (!stringp(arg1))
	error(NOT_SYM, "import", arg1);

    char *str = Str_cat(GET_NAME(arg1), 1, 0, ".o", 1, 0);
    char *fname = library_file(str);
    if (access(fname, R_OK) != -1) {
	f_load(list1(make_str(fname)));
	goto cleanup;
    }

    FREE(str);
    str = Str_cat(GET_NAME(arg1), 1, 0, ".lsp", 1, 0);
    FREE(fname);
    fname = library_file(str);
    if (access(fname, R_OK) != -1) {
	f_load(list1(make_str(fname)));
	goto cleanup;
    }
    FREE(str);
    FREE(fname);
    error(CANT_OPEN, "import", arg1);

  cleanup:
    FREE(str);
    FREE(fname);
    return (T);
}


int f_defmodule(int arglist)
{
    int arg1, arg2, exports;

    arg1 = car(arglist);	/* module name */
    arg2 = cdr(arglist);	/* body */
    exports = NIL;
    ignore_topchk = true;
    while (!nullp(arg2)) {
	int sexp;

	sexp = car(arg2);
	if (symbolp(car(sexp)) && HAS_NAME(car(sexp), "DEFPUBLIC"))
	    exports = cons(cadr(sexp), exports);
	else if (symbolp(car(sexp)) && HAS_NAME(car(sexp), "IMPORT"))
	    exports = append(cddr(sexp), exports);

	eval(modulesubst(car(arg2), arg1, exports));
	arg2 = cdr(arg2);
    }
    ignore_topchk = false;
    return (T);
}


int modulesubst(int addr, int module, int fname)
{
    int temp;

    if (IS_NIL(addr) || IS_T(addr))
	return (addr);
    else if (numberp(addr))
	return (addr);
    else if (vectorp(addr))
	return (addr);
    else if (arrayp(addr))
	return (addr);
    else if (stringp(addr))
	return (addr);
    else if (charp(addr))
	return (addr);
    else if (class_symbol_p(addr))
	return (addr);
    else if (symbolp(addr)) {
	if (!member(addr, fname) && !eqp(addr, make_sym(":REST"))
	    && !eqp(addr, make_sym("&REST"))
	    && !eqp(addr, make_sym(":READER"))
	    && !eqp(addr, make_sym(":WRITER"))
	    && !eqp(addr, make_sym(":ACCESSOR"))
	    && !eqp(addr, make_sym(":BOUNDP"))
	    && !eqp(addr, make_sym(":INITFORM"))
	    && !eqp(addr, make_sym(":INITARG"))
	    && !eqp(addr, make_sym("*MOST-POSITIVE-FLOAT*"))
	    && !eqp(addr, make_sym("*MOST-NEGATIVE-FLOAT*"))
	    && !eqp(addr, make_sym("*PI*")))
	    return (modulesubst1(addr, module));
	else
	    return (addr);
    } else if (listp(addr)) {
	if ((symbolp(car(addr))) && (HAS_NAME(car(addr), "QUOTE"))) {
	    temp = cadr(addr);
	    if (listp(temp) && symbolp(car(temp))
		&& (HAS_NAME(car(temp), "UNQUOTE")))
		return (cons
			(car(addr),
			 modulesubst(cdr(addr), module, fname)));
	    else
		return (addr);
	} else if ((symbolp(car(addr)))
		   && (HAS_NAME(car(addr), "QUASI-QUOTE")))
	    return (cons
		    (car(addr), modulesubst(cdr(addr), module, fname)));
	else if ((symbolp(car(addr))) && (HAS_NAME(car(addr), "UNQUOTE")))
	    return (cons
		    (car(addr), modulesubst(cdr(addr), module, fname)));
	else if ((symbolp(car(addr)))
		 && (HAS_NAME(car(addr), "UNQUOTE-SPLICING")))
	    return (cons
		    (car(addr), modulesubst(cdr(addr), module, fname)));
	else if (subrp(car(addr)))
	    return (cons
		    (car(addr), modulesubst(cdr(addr), module, fname)));
	else if ((symbolp(car(addr)))
		 && (HAS_NAME(car(addr), "DEFPUBLIC")))
	    return (cons
		    (make_sym("DEFUN"),
		     cons(cadr(addr),
			  modulesubst(cddr(addr), module, fname))));
	else if ((symbolp(car(addr))) && (HAS_NAME(car(addr), "DEFUN")))
	    return (cons
		    (car(addr), modulesubst(cdr(addr), module, fname)));
	else if ((symbolp(car(addr))) && (HAS_NAME(car(addr), ":METHOD")))
	    return (cons
		    (car(addr), modulesubst(cdr(addr), module, fname)));
	else if ((symbolp(car(addr))) && (HAS_NAME(car(addr), "CASE")))
	    return (cons
		    (car(addr),
		     cons(modulesubst(cadr(addr), module, fname),
			  modulesubst_case(cddr(addr), module, fname))));
	else if ((symbolp(car(addr)))
		 && (HAS_NAME(car(addr), "CASE-USING")))
	    return (cons
		    (car(addr),
		     cons(modulesubst(cadr(addr), module, fname),
			  modulesubst_case(cddr(addr), module, fname))));
	else if (fsubrp(car(addr)))
	    return (cons
		    (car(addr), modulesubst(cdr(addr), module, fname)));
	else if (macrop(car(addr)))
	    return (cons
		    (car(addr), modulesubst(cdr(addr), module, fname)));
	else if (genericp(car(addr)))
	    return (cons
		    (car(addr), modulesubst(cdr(addr), module, fname)));
	else
	    return (cons
		    (modulesubst(car(addr), module, fname),
		     modulesubst(cdr(addr), module, fname)));

    }
    return (T);
}

int modulesubst1(int x, int module)
{
    char str[SYMSIZE];

    Fmt_sfmt(str, SYMSIZE, "%s::%s", GET_NAME(module), GET_NAME(x));
    return (make_sym(str));
}


int modulesubst_case(int addr, int module, int fname)
{
    int bodies, newbodies;

    bodies = addr;
    newbodies = NIL;

    while (!nullp(bodies)) {
	int body, newbody;

	body = car(bodies);
	newbody = cons(car(body), modulesubst(cdr(body), module, fname));
	newbodies = cons(newbody, newbodies);

	bodies = cdr(bodies);
    }
    newbodies = reverse(newbodies);
    return (newbodies);
}
