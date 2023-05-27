#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "eisl.h"
#include "fmt.h"
#include "except.h"
#include "str.h"
#include "mem.h"

static int outc(int c)
{
    return fputc(c, stderr);
}

static inline void ESCERRFRED()
{
    tputs(tparm(set_a_foreground, COLOR_RED), 1, outc);
}

static inline void ESCERRFORG()
{
    tputs(exit_attribute_mode, 1, outc);
}

// -------error------
// for compiler 
int ILOSerror(int fun, int arg)
{
    error(NOT_EXIST_METHOD, GET_NAME(fun), arg);
    return (NIL);
}


void error(int errnum, const char *fun, int arg)
{
    int initargs, i;
    char fun1[SYMSIZE];

#ifndef WITHOUT_CURSES
    // restore repl_flag
    repl_flag = org_repl_flag;
#endif

    // resolve unwind-protect
    if (unwind_pt > 0) {
	unwind_pt--;
	while (unwind_pt >= 0) {
	    apply(unwind_buf[unwind_pt], NIL);
	    unwind_pt--;
	}
	unwind_pt = 0;
	unwind_nest = 0;
    }
    // initialize block-pointer
    block_pt = 0;

    // fold to upper letter.
    for (i = 0; i < (int) strlen(fun); i++) {
	fun1[i] = toupper(fun[i]);
    }
    fun1[i] = '\0';

    // clear generic-function data.
    generic_func = NIL;
    generic_vars = NIL;

    switch (errnum) {
    case DIV_ZERO:
	initargs =
	    list6(make_sym("format-string"),
		  make_str("division by zero at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cdivision_by_zero, initargs), NIL);
	break;
    case UNDEF_VAR:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Unbound variable at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("name"), make_sym("UNDEF-VAR"),
		   make_sym("namespace"), make_sym("VARIABLE"));
	signal_condition(make_instance(cunbound_variable, initargs), NIL);
	break;
    case UNDEF_FUN:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Unbound function at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("name"),
		   make_sym("UNDEF-FUNC"), make_sym("namespace"),
		   make_sym("FUNCTION"));
	signal_condition(make_instance(cundefined_function, initargs),
			 NIL);
	break;
    case UNDEF_DYN:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Unbound dynamic variable at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("name"),
		   make_sym("UNDEF-DYNAMIC-VAR"), make_sym("namespace"),
		   make_sym("DYNAMIC-VARIABLE"));
	signal_condition(make_instance(cunbound_variable, initargs), NIL);
	break;
    case UNDEF_CLASS:
	initargs =
	    list6(make_sym("format-string"), make_str("Unbound class at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cundefined_entity, initargs), NIL);
	break;
    case UNDEF_TAG:
	initargs =
	    list6(make_sym("format-string"), make_str("Unbound tag at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(ccontrol_error, initargs), NIL);
	break;
    case WRONG_ARGS:
	initargs =
	    list6(make_sym("format-string"),
		  make_str("Wrong arguments at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cprogram_error, initargs), NIL);
	break;
    case NOT_EXIST_ARG:
	initargs =
	    list6(make_sym("format-string"),
		  make_str("Not exist argument at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cprogram_error, initargs), NIL);
	break;
    case NOT_NUM:
	initargs =
	    list10(make_sym("format-string"), make_str("Not a number at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cnumber);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case NOT_POSITIVE:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Not a positive number at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cnumber);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case FLT_OVERF:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Floating number overflow at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cfloat);
	signal_condition(make_instance(cfloating_point_overflow, initargs),
			 make_str
			 ("Continuing ignores floating point overflow and the calculation returns infinity"));
	break;
    case FLT_UNDERF:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Floating number underflow at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cfloat);
	signal_condition(make_instance
			 (cfloating_point_underflow, initargs),
			 make_str
			 ("Continuing ignores floating point underflow and the calculation returns zero"));
	break;
    case FLT_OUT_OF_DOMAIN:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Floating number out of domain at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cfloat);
	signal_condition(make_instance(cerror, initargs), NIL);
	break;
    case OUT_OF_REAL:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Number out of real at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cfloat);
	signal_condition(make_instance(cerror, initargs), NIL);
	break;
    case NOT_INT:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Not an integer at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cinteger);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case NOT_FLT:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Not a float number at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cfloat);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case NOT_STR:
	initargs =
	    list10(make_sym("format-string"), make_str("Not a string at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cstring);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case NOT_CHAR:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Not a character at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), ccharacter);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case NOT_LIST:
	initargs =
	    list10(make_sym("format-string"), make_str("Not a list at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), clist);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case NOT_CONS:
	initargs =
	    list10(make_sym("format-string"), make_str("Not a cons at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), ccons);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case NOT_VEC:
	initargs =
	    list10(make_sym("format-string"), make_str("Not a vector at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cbasic_vector);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case NOT_ARR:
	initargs =
	    list10(make_sym("format-string"), make_str("Not an array at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cbasic_array);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case NOT_SYM:
	initargs =
	    list10(make_sym("format-string"), make_str("Not a symbol at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), csymbol);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case NOT_FUNC:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Not a function at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cfunction);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case NOT_STREAM:
	initargs =
	    list10(make_sym("format-string"), make_str("Not a stream at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cstream);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case NOT_STREAM_ERROR:
	initargs =
	    list10(make_sym("format-string"), make_str("Not a stream at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cstream_error);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case NOT_IN_STREAM:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Not an input stream at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cstream);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case NOT_OUT_STREAM:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Not an output stream at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cstream);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case NOT_INSTANCE:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Not an instance at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cobject);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case NOT_CLASS:
	initargs =
	    list10(make_sym("format-string"), make_str("Not a class at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cobject);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case NOT_BASIC_ARRAY:
	initargs =
	    list10(make_sym("format-string"), make_str("Not domain at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cbasic_array);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case NOT_VECARR:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Not a vector or an array at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cgeneral_array_star);
	signal_condition(make_instance(cprogram_error, initargs), NIL);
	break;
    case ILLEGAL_RPAREN:
	initargs =
	    list6(make_sym("format-string"),
		  make_str("Illegal right parenthesis at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cprogram_error, initargs), NIL);
	break;
    case ILLEGAL_INPUT:
	initargs =
	    list6(make_sym("format-string"), make_str("Illegal input at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cprogram_error, initargs), NIL);
	break;
    case ILLEGAL_FORM:
	initargs =
	    list6(make_sym("format-string"), make_str("Illegal form at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cerror, initargs), NIL);
	break;
    case IMPROPER_FORM:
	initargs =
	    list6(make_sym("format-string"), make_str("Illegal form at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cprogram_error, initargs), NIL);
	break;
    case ILLEGAL_ARGS:
	initargs =
	    list6(make_sym("format-string"),
		  make_str("Illegal argument at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cprogram_error, initargs), NIL);
	break;
    case IMPROPER_ARGS:
	initargs =
	    list6(make_sym("format-string"),
		  make_str("Improper arguments at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cerror, initargs), NIL);
	break;
    case OUT_OF_RANGE:
	initargs =
	    list6(make_sym("format-string"), make_str("Out of range at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cprogram_error, initargs), NIL);
	break;
    case OUT_OF_DOMAIN:
	initargs =
	    list6(make_sym("format-string"), make_str("Out of domain at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case NOT_COMPUTABLE:
	initargs =
	    list6(make_sym("format-string"),
		  make_str("Not computable at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case CANT_MODIFY:
	initargs =
	    list6(make_sym("format-string"), make_str("Can't modify at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cprogram_error, initargs), NIL);
	break;
    case CANT_OPEN:
	initargs =
	    list6(make_sym("format-string"),
		  make_str("Can't open a file at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cstream_error, initargs), NIL);
	break;
    case CANT_CREATE:
	initargs =
	    list6(make_sym("format-string"),
		  make_str
		  ("Can't create instance for system defined or abstract class at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cerror, initargs), NIL);
	break;
    case CANT_PARSE:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Can't parse number at "),
		   make_sym("format-arguments"), arg, make_sym("object"),
		   arg, make_sym("string"), arg,
		   make_sym("expected-class"), cnumber);
	signal_condition(make_instance(cparse_error, initargs), NIL);
	break;
    case CANT_ASSURE:
	initargs =
	    list6(make_sym("format-string"), make_str("Can't assure at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case CTRL_OVERF:
	initargs =
	    list6(make_sym("format-string"),
		  make_str("Control stack over flow at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(ccontrol_error, initargs), NIL);
	break;
    case END_STREAM:
	initargs =
	    list8(make_sym("format-string"), make_str("End of stream at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1), make_sym("stream"), arg);
	signal_condition(make_instance(cend_of_stream, initargs), NIL);
	break;
    case MALLOC_OVERF:
	initargs =
	    list6(make_sym("format-string"),
		  make_str("Memory allocate over flow at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cstorage_exhausted, initargs), NIL);
	break;
    case NOT_EXIST_METHOD:
	initargs =
	    list6(make_sym("format-string"),
		  make_str("Not exist matched method at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cerror, initargs), NIL);
	break;
    case HAS_COMMON_CLASS:
	initargs =
	    list6(make_sym("format-string"),
		  make_str("Super class has common parents at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cerror, initargs), NIL);
	break;
    case ILLEGAL_CLASS:
	initargs =
	    list6(make_sym("format-string"),
		  make_str
		  ("Next method allows only primary and :around method at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cclass_error, initargs), NIL);
	break;
    case NOT_TOP_LEVEL:
	initargs =
	    list6(make_sym("format-string"),
		  make_str("Definition must be on top level at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cerror, initargs), NIL);
	break;
    case CANT_REDEFINE:
	initargs =
	    list6(make_sym("format-string"),
		  make_str("Can't modify system defined class at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cerror, initargs), NIL);
	break;
    case STACK_OVERF:
	initargs =
	    list6(make_sym("format-string"), make_str("Stack over flow "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cprogram_error, initargs), NIL);
	break;
    case SHELTER_OVERF:
	initargs =
	    list6(make_sym("format-string"),
		  make_str("Shelter over flow "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cprogram_error, initargs), NIL);
	break;
    case DYNAMIC_OVERF:
	initargs =
	    list6(make_sym("format-string"),
		  make_str("Shelter over flow "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cprogram_error, initargs), NIL);
	break;
    case STACK_UNDERF:
	initargs =
	    list6(make_sym("format-string"), make_str("Stack under flow "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cprogram_error, initargs), NIL);
	break;
    case SHELTER_UNDERF:
	initargs =
	    list6(make_sym("format-string"),
		  make_str("Shelter under flow "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cprogram_error, initargs), NIL);
	break;
    case SYSTEM_ERR:
	initargs =
	    list6(make_sym("format-string"), make_str("system error "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cprogram_error, initargs), NIL);
	break;
    case RESOURCE_ERR:
	gbc();
	initargs =
	    list6(make_sym("format-string"), make_str("resource error "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cprogram_error, initargs), NIL);
	break;
    case SERIOUS_ERR:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Serious condition at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cserious_condition);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case ARITHMETIC_ERR:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Arithmetic error at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), carithmetic_error);
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case DOMAIN_ERR:
	initargs =
	    list10(make_sym("format-string"), make_str("Domain error at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), car(arg),
		   make_sym("expected-class"), cdr(arg));
	signal_condition(make_instance(cdomain_error, initargs), NIL);
	break;
    case UNDEF_ENTITY:
	initargs =
	    list10(make_sym("format-string"),
		   make_str("Undefined entity error at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), cundefined_entity);
	signal_condition(make_instance(cundefined_entity, initargs), NIL);
	break;
    case SIMPLE_ERR:
	initargs =
	    list10(make_sym("format-string"), make_str("Simple error at "),
		   make_sym("format-arguments"), arg, make_sym("function"),
		   make_sym(fun1), make_sym("object"), arg,
		   make_sym("expected-class"), csimple_error);
	signal_condition(make_instance(csimple_error, initargs), NIL);
	break;
    case EXHAUSTED_ERR:
	initargs =
	    list6(make_sym("format-string"),
		  make_str("Exhausted error at "),
		  make_sym("format-arguments"), arg, make_sym("function"),
		  make_sym(fun1));
	signal_condition(make_instance(cstorage_exhausted, initargs), NIL);
	break;
    }
}

/*
 * x = class y = continuable string/NIL 
 */
int signal_condition(int x, int y)
{
    int str, args, fun;

    error_flag = true;
    if (y == NIL)
	SET_OPT(x, NOTCONT);
    else {
	SET_OPT(x, CONTINUABLE);
	TRY heap[x].name = Str_dup(GET_NAME(y), 1, 0, 1);
	EXCEPT(Mem_Failed) error(MALLOC_OVERF, "signal-condition", NIL);
	END_TRY;
    }
    if (ignore_flag) {
	handling_resource_err = false;
	RAISE(Ignored_Error);
    }
    if (open_flag && error_handler == NIL) {
	fclose(GET_PORT(input_stream));
	open_flag = false;
	Fmt_print("around here line=%d column=%d\n", line, column);
    }
    if (error_handler != NIL) {
	int handler;

	handler = car(error_handler);
	/* if error is continuable, hold error_handler */
	if (y == NIL) {
	    error_handler1 = error_handler;
	    error_handler = cdr(error_handler);
	}
	return (apply(handler, list1(x)));
    }
    str = cdr(assoc(make_sym("a"), GET_CDR(x)));
    args = cdr(assoc(make_sym("b"), GET_CDR(x)));
    fun = cdr(assoc(make_sym("c"), GET_CDR(x)));
    output_stream = error_stream;
    if (repl_flag)
	ESCERRFRED();
    fputs(GET_NAME(str), stderr);
    print(fun);
    fputc(' ', stderr);
    print(args);
    fputc('\n', stderr);
    if (repl_flag)
	ESCERRFORG();
    input_stream = standard_input;
    output_stream = standard_output;
    handling_resource_err = false;
    if (!option_flag)
	debugger();
    else {
	puts("Error occurred while executing command line options.");
	option_flag = false;
    }
    RAISE(Restart_Repl);
    return 0;
}

int makeusercond(int cl, int str, int arg)
{
    int initarg;

    initarg = list6(make_sym("format-string"), str,
		    make_sym("format-arguments"), arg,
		    make_sym("function"), make_sym(""));
    return (make_instance(cl, initarg));
}

int get_error_handler(void)
{
    return (error_handler);
}

int set_error_handler(int x)
{
    error_handler = x;
    return (x);
}

int get_error_flag(void)
{
	return (error_flag);
}