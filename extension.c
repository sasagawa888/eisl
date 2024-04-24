/* extended functions
 * functions for compiler 
 * functions for compatibility of Common Lisp
 * functions for debug
 * function for profiler
 * functions for Raspbery-PI
 * functions for Chaitin's omega
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#ifdef __rpi__
#include <wiringPi.h>
#include <wiringPiSPI.h>
#endif
#include "eisl.h"
#include "mem.h"
#include "fmt.h"
#include "except.h"
#include "str.h"
#include "text.h"

void init_exsubr(void)
{
    def_subr("RANDOM-REAL", f_random_real);
    def_subr("RANDOM", f_random);
    def_subr("SET-RANDOM", f_set_random);
    def_subr("NCONC", f_nconc);
    def_subr("FAST-ADDRESS", f_address);
    def_subr("MACROEXPAND-1", f_macroexpand_1);
    def_subr("MACROEXPAND-ALL", f_macroexpand_all);
    def_subr("BACKTRACE", f_backtrace);
    def_subr("BREAK", f_break);
    def_subr("EDIT", f_edit);
    def_subr("FREEDLL", f_freedll);
    def_subr("SYSTEM", f_system);
    def_subr("SUBRP", f_subrp);
    def_subr("MACROP", f_macrop);
    def_subr("FUNCP", f_funcp);
    def_subr("FIXNUMP", f_fixnump);
    def_subr("LONGNUMP", f_longnump);
    def_subr("BIGNUMP", f_bignump);
    def_subr("SELF-INTRODUCTION", f_self_introduction);
    def_subr("CLASSP", f_classp);
    def_subr("C-INCLUDE", f_ignore);
    def_subr("C-DEFINE", f_ignore);
    def_subr("C-LANG", f_ignore);
    def_subr("C-OPTION", f_ignore);
    def_subr("HEAPDUMP", f_heapdump);
    def_subr("INSTANCE", f_instance);
    def_subr("LINE-ARGUMENT", f_line_argument);
    def_subr("GETENV", f_getenv);
    def_subr("PROF", f_prof);
    def_subr("EISL-MODULESUBST", f_modulesubst);
    def_subr("EISL-SUPERP-FOR-COMPILER", f_superp_for_compiler);
    def_subr("EISL-READED-ARRAY-LIST", f_readed_array_list);
    def_subr("EISL-GET-METHOD", f_get_method);
    def_subr("EISL-GET-METHOD-BODY", f_get_method_body);
    def_subr("EISL-GET-METHOD-PRIORITY", f_get_method_priority);
    def_subr("EISL-IGNORE-TOPLEVEL-CHECK", f_ignore_toplevel_check);
    def_subr("EISL-TEST", f_eisl_test);
    def_subr("EISL-GET-MYSELF", f_get_myself);

    def_subr("TRY", f_try);
    def_subr("READ-EXP", f_read_exp);

    def_subr("MP-CREATE", f_mp_create);
    def_subr("MP-EXEC", f_mp_exec);
    def_subr("MP-CLOSE", f_mp_close);
    def_fsubr("MP-CALL", f_mp_call);

#ifdef __rpi__
    def_subr("WIRINGPI-SETUP-GPIO", f_wiringpi_setup_gpio);
    def_subr("WIRINGPI-SPI-SETUP-CH-SPEED", f_wiringpi_spi_setup_ch_speed);
    def_subr("PWM-SET-MODE", f_pwm_set_mode);
    def_subr("PWM-SET-RANGE", f_pwm_set_range);
    def_subr("PWM-SET-CLOCK", f_pwm_set_clock);
    def_subr("PIN-MODE", f_pin_mode);
    def_subr("DIGITAL-WRITE", f_digital_write);
    def_subr("DIGITAL-WRITE-BYTE", f_digital_write_byte);
    def_subr("PULL-UP-DN-CONTROL", f_pull_up_dn_control);
    def_subr("DIGITAL-READ", f_digital_read);
    def_subr("DELAY-SECONDS", f_delay);
    def_subr("DELAY-MICROSECONDS", f_delay_microseconds);
#endif

}

/* Fast Project 
 * functions for compiler
 */
int f_classp(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(ILLEGAL_ARGS, "classp", arglist, th);

    if (IS_CLASS(arg1))
	return (T);
    else
	return (NIL);
}


int f_ignore(int arglist __unused, int th __unused)
{
    return (T);
}


int f_self_introduction(int arglist __unused, int th __unused)
{
#if __APPLE__
    return (make_sym("MACOS"));
#elif defined(__OpenBSD__)
    return (make_sym("OPENBSD"));
#elif defined(__FreeBSD__)
    return (make_sym("FREEBSD"));
#elif defined(__linux__)
    return (make_sym("LINUX"));
#else
#error "Unknown system"
#endif
}


int f_ignore_toplevel_check(int arglist, int th __unused)
{
    int arg1;

    arg1 = car(arglist);
    if (arg1 == T)
	ignore_topchk = true;
    else
	ignore_topchk = false;
    return (T);
}

DEF_PREDICATE(METHOD, METHOD)
int f_get_method_priority(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (!(IS_METHOD(arg1)))
	error(ILLEGAL_ARGS, "eisl-get-method-priority", arg1, th);

    return (make_int(GET_OPT(arg1) + 1));
    /* 11=:around  12=:befor 13=:primary 14=:arter */
}


int f_get_method_body(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (!(IS_METHOD(arg1)))
	error(ILLEGAL_ARGS, "get-method-body", arg1, th);

    return (GET_CAR(arg1));
}

int f_get_method(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (!genericp(arg1))
	error(ILLEGAL_ARGS, "get-method", arg1, th);

    return (GET_CDR(GET_CAR(arg1)));
}


int f_readed_array_list(int arglist, int th __unused)
{
    int arg1;

    arg1 = car(arglist);
    return (GET_PROP(arg1));
}


int f_system(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (system(GET_NAME(arg1)) == -1)
	error(SYSTEM_ERR, "system", arg1, th);
    return (T);
}



int f_freedll(int arglist __unused, int th __unused)
{
    // dlclose(hmod);
    return (T);
}

int f_macrop(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "macrop", arglist, th);
    if (IS_MACRO(GET_CAR(arg1)))
	return (T);
    else
	return (NIL);
}


int f_funcp(int arglist, int th)
{
    int arg;

    arg = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "funcp", arglist, th);
    if (IS_FUNC(GET_CAR(arg)))
	return (T);
    else
	return (NIL);
}


int f_fixnump(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "fixnump", arglist, th);
    if (IS_INTEGER(arg1))
	return (T);
    else
	return (NIL);
}

int f_longnump(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "longnump", arglist, th);
    if (IS_LONGNUM(arg1))
	return (T);
    else
	return (NIL);
}

int f_bignump(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "bignump", arglist, th);
    if (IS_BIGNNUM(arg1))
	return (T);
    else
	return (NIL);
}


int f_subrp(int arglist, int th)
{
    int arg;

    arg = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "subrp", arglist, th);
    if (IS_SUBR(GET_CAR(arg)))
	return (T);
    else
	return (NIL);
}

int f_macroexpand_1(int arglist, int th)
{
    int arg1, args;

    arg1 = caar(arglist);
    args = cdar(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "macroexpand-1", arglist, th);
    if (!symbolp(arg1))
	error(NOT_SYM, "macroexpand-1", arg1, th);

    return (macroexpand_1(arg1, args, th));
}

int macroexpand_1(int macsym, int args, int th)
{
    int func, body, macrofunc, varlist, save, res;

    func = GET_CAR(macsym);
    save = ep[th];
    res = NIL;
    macrofunc = GET_CAR(func);
    varlist = car(GET_CAR(macrofunc));
    if (GET_OPT(func) >= 0) {
	if (length(args) != (int) GET_OPT(func))
	    error(WRONG_ARGS, "macroexpand-1", args, th);
    } else {
	if (length(args) < (-1 * (int) GET_OPT(func) - 2))
	    error(WRONG_ARGS, "macroexpand-1", args, th);
    }
    body = cdr(GET_CAR(macrofunc));
    bind_arg(varlist, args, th);
    while (!(IS_NIL(body))) {
	res = eval(car(body), th);
	body = cdr(body);
    }
    unbind(th);
    ep[th] = save;
    return (res);
}

int f_macroexpand_all(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "macroexpand-all", arglist, th);
    if (listp(arg1) && car(arg1) == make_sym("DEFMACRO"))
	return (arg1);
    else
	return (macroexpand_all(arg1, th));
}


int macroexpand_all(int sexp, int th)
{

    if (nullp(sexp))
	return (NIL);
    else if (atomp(sexp))
	return (sexp);
    else if (listp(sexp) && car(sexp) == make_sym("QUOTE"))
	return (sexp);
    else if (listp(sexp) && macrop(car(sexp)))
	return (macroexpand_all
		(macroexpand_1(car(sexp), cdr(sexp), th), th));
    else if (listp(sexp))
	return (cons
		(macroexpand_all(car(sexp), th),
		 macroexpand_all(cdr(sexp), th)));

    return (NIL);
}

int f_modulesubst(int arglist, int th __unused)
{
    int arg1, arg2, arg3;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);

    return (modulesubst(arg1, arg2, arg3));
}

int f_line_argument(int arglist, int th)
{
    if (length(arglist) >= 2) {
	error(WRONG_ARGS, "line-argument", arglist, th);
    }

    if (length(arglist) == 0) {
	int i, res;
	res = make_vec(gArgC, UNDEF);

	for (i = 0; i < gArgC; i++) {
	    SET_VEC_ELT(res, i, make_str(gArgV[i]));
	}

	return res;
    } else {
	int arg1 = car(arglist);
	int n = GET_INT(arg1);
	if (n < gArgC) {
	    return make_str(gArgV[n]);
	} else {
	    return NIL;
	}
    }
}

int f_getenv(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1) {
	error(WRONG_ARGS, "getenv", arglist, th);
    }
    char *val = getenv(GET_NAME(arg1));
    if (val == NULL) {
	return NIL;
    } else {
	return make_str(val);
    }
}


/*
 * f_superp_for_compiler (superp-for-compiler) is used in compiler.lsp. 
 * for generate (call-next-method) 
 * compare entry-parameter and next-method-parameter.
 * when entry-parameter is super-call than next-method-patarmeter, compiler must not generate next-method
 * see verify/object.lsp test-case foo-30
 */

int f_superp_for_compiler(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);

    if (length(arglist) != 2) {
	error(WRONG_ARGS, "eisl-superp-for-compiler", arglist, th);
    }

    if (superp(arg1, arg2))
	return (T);
    else
	return (NIL);
}

int superp(int entry, int next)
{

    if (nullp(entry) && nullp(next))
	return (1);
    else if (symbolp(car(entry)))
	return (superp(cdr(entry), cdr(next)));
    else if (subclassp(GET_AUX(cadar(next)), GET_AUX(cadar(entry))))	/* subclass */
	return (superp(cdr(entry), cdr(next)));
    else if (eqp(GET_AUX(cadar(next)), GET_AUX(cadar(entry))))	/* same class */
	return (superp(cdr(entry), cdr(next)));
    else
	return (0);
}



/*
 * extended funcstions 
 * random number
 */
int f_random_real(int arglist, int th)
{
    double d;

    if (length(arglist) != 0)
	error(WRONG_ARGS, "random-real", arglist, th);

    d = (double) rand() / RAND_MAX;
    return (make_flt(d));
}

int f_random(int arglist, int th)
{
    int arg1, n;

    if (length(arglist) != 1)
	error(WRONG_ARGS, "random", arglist, th);

    arg1 = car(arglist);
    n = GET_INT(arg1);

    return (make_int(rand() % n));
}

int f_set_random(int arglist, int th)
{
    int arg1, n;

    if (length(arglist) != 1)
	error(WRONG_ARGS, "set-random", arglist, th);

    arg1 = car(arglist);
    if (!numberp(arg1))
	error(NOT_NUM, "set-random", arg1, th);

    n = GET_INT(arg1);
    if (n < 0)
	error(ILLEGAL_ARGS, "set-random", n, th);

    srand(n);
    return (arg1);
}

/*
 *  nconc compatible with Common Lisp
 */

int f_nconc(int arglist, int th)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "nconc", arglist, th);

    return (nconc(arg1, arg2));
}

int nconc(int x, int y)
{
    int ls;

    if (nullp(x))
	return (y);

    ls = x;
    while (!nullp(cdr(ls))) {
	ls = cdr(ls);
    }
    SET_CDR(ls, y);
    return (x);
}


int f_address(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "address", arglist, th);

    return (make_int(arg1));
}

/*
 * functions for debugging
 *
 */
int f_backtrace(int arglist, int th)
{
    int arg1, l;

    if ((l = length(arglist)) != 0 && l != 1)
	error(WRONG_ARGS, "backtrace", arglist, th);

    arg1 = car(arglist);

    if (l == 0) {
	int i;

	for (i = 0; i < BACKSIZE; i++) {
	    print(backtrace[i]);
	    putchar('\n');
	}
    } else if (arg1 == T)
	back_flag = true;
    else if (arg1 == NIL)
	back_flag = false;

    return (T);
}

int f_break(int arglist __unused, int th)
{
    puts("break");
    debugger(th);
    return (T);
}

/* --------debug--------------- */
void debugger(int th)
{
    int i, j;

    puts("debug mode ?(help)");
    while (1) {
	fputs(">>", stdout);
	int x = sread();
	if (eqp(x, make_sym("?"))) {
	    puts("?  help\n"
		 ":a abort\n"
		 ":b backtrace\n"
		 ":d dynamic environment\n"
		 ":e environment\n"
		 ":i identify examining symbol\n"
		 ":q quit\n"
		 ":r room\n"
         ":s stepper ON/OFF\n"
         "other S exps eval");
	} else if (eqp(x, make_sym(":A"))) {
	    RAISE(Restart_Repl);
	} else if (eqp(x, make_sym(":B"))) {
	    for (i = 0; i < BACKSIZE; i++) {
		print(backtrace[i]);
		putchar('\n');
	    }
	} else if (eqp(x, make_sym(":D"))) {
	    for (i = 0; i < worker_count; i++) {
		Fmt_print("thread%d = ", i);
		for (j = 0; j < dp[i]; j++) {
		    print(dynamic[j][0][i]);
		    printf("=");
		    print(dynamic[j][1][i]);
		    printf(" ");
		}
		putchar('\n');
	    }
	} else if (eqp(x, make_sym(":E"))) {
	    for (i = 0; i <= worker_count; i++) {
		Fmt_print("thread%d = ", i);
		print(ep[i]);
		putchar('\n');
	    }
	} else if (eqp(x, make_sym(":I"))) {
	    print(examin_sym);
	    putchar('\n');
	} else if (eqp(x, make_sym(":Q"))) {
	    return;
	} else if (eqp(x, make_sym(":R"))) {
	    Fmt_print("EP = %d (environment pointer)\n"
		      "DP = %d (dynamic pointer)\n"
		      "HP = %d (heap pointer)\n"
		      "SP = %d (stack pointer)\n"
		      "FC = %d (free counter)\n"
		      "AP = %d (arglist pointer)\n"
		      "LP = %d (shelter pointer)\n"
		      "Parallel = %d (worker_count)\n"
              "Thread = %d (current thread)\n",
		      ep[th], dp[th], hp, sp[th], fc, ap[th], lp[th], worker_count, th);
	} else if (eqp(x, make_sym(":S"))) {
	    if (stepper_flag == 0) {
		puts("stepper ON. enter 'q' to quit stepper");
		stepper_flag = 1;
	    } else {
		puts("stepper OFF");
		stepper_flag = 0;
	    }
	} else {
	    print(eval(x, 0));
	    putchar('\n');
	}
    }
}

int f_instance(int arglist, int th __unused)
{
    int arg1, addr;

    arg1 = car(arglist);
    addr = get_int(arg1);
    print(addr);
    return (T);
}

int f_heapdump(int arglist, int th __unused)
{
    int arg;

    arg = GET_INT(car(arglist));
    heapdump(arg, arg + 10);
    return (T);
}

DEF_GETTER(flag, FLAG, flag, NIL)
void cellprint(int addr)
{
    switch (GET_FLAG(addr)) {
    case FRE:
	fputs("FRE ", stdout);
	break;
    case USE:
	fputs("USE ", stdout);
	break;
    }
    switch (GET_TAG(addr)) {
    case EMP:
	puts("EMP");
	break;
    case INTN:
	Fmt_print("INTN   %d\n", GET_INT(addr));
	break;
    case FLTN:
	Fmt_print("FLTN   %f\n", GET_FLT(addr));
	break;
    case LONGN:
	Fmt_print("LONGN  %D\n", GET_LONG(addr));
	break;
    case BIGN:
	Fmt_print("BIGN   %d\n", GET_CAR(addr));
	break;
    case SYM:
	Fmt_print("SYM    %07d %07d %07d %s\n", GET_CAR(addr),
		  GET_CDR(addr), GET_AUX(addr), GET_NAME(addr));
	break;
    case STR:
	Fmt_print("STR    %07d %07d %07d %s\n", GET_CAR(addr),
		  GET_CDR(addr), GET_AUX(addr), GET_NAME(addr));
	break;
    case LIS:
	Fmt_print("LIS    %07d %07d %07d\n", GET_CAR(addr), GET_CDR(addr),
		  GET_AUX(addr));
	break;
    case SUBR:
	Fmt_print("SUBR   %07d %07d %07d\n", GET_CAR(addr), GET_CDR(addr),
		  GET_AUX(addr));
	break;
    case FSUBR:
	Fmt_print("FSUBR  %07d %07d %07d\n", GET_CAR(addr), GET_CDR(addr),
		  GET_AUX(addr));
	break;
    case FUNC:
	Fmt_print("FUNC   %07d %07d %07d\n", GET_CAR(addr), GET_CDR(addr),
		  GET_AUX(addr));
	break;
    case MACRO:
	Fmt_print("MACRO  %07d %07d %07d\n", GET_CAR(addr), GET_CDR(addr),
		  GET_AUX(addr));
	break;
    case CLASS:
	Fmt_print("CLASS  %07d %07d %07d %s\n", GET_CAR(addr),
		  GET_CDR(addr), GET_AUX(addr), GET_NAME(addr));
	break;
    case GENERIC:
	Fmt_print("GENE   %07d %07d %07d\n", GET_CAR(addr), GET_CDR(addr),
		  GET_AUX(addr));
	break;
    default:
	Fmt_print("cellprint(%d) tag switch default action\n", addr);
    }
}

/* heap dump */
void heapdump(int start, int end)
{
    int i;

    puts("addr    F   TAG    CAR     CDR     AUX     NAME");
    for (i = start; i <= end; i++) {
	Fmt_print("%07d ", i);
	cellprint(i);
    }
}


/*
 * profiler
 */
int f_prof(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (!symbolp(arg1))
	error(NOT_SYM, "prof", arg1, th);

    if (arg1 == NIL) {
	profiler_set(0);
	profiler_clear();
    } else if (eqp(arg1, make_sym("CL")))
	profiler_clear();
    else if (eqp(arg1, make_sym("SYS")))
	profiler_set(1);
    else if (eqp(arg1, make_sym("USER")))
	profiler_set(2);
    else if (eqp(arg1, make_sym("PR")))
	profiler_print();
    else
	error(WRONG_ARGS, "prof", arg1, th);

    return (T);
}

/*
 * profiler
 * To improve builtin function or user-defined function
 * (prof x) extended function
 * (prof nil) stop profiling. prof_sw = 0;
 * (prof 'sys) start profiling for built-in function. prof_sw = 2;
 * (prof 'user) start profiling for unser-defined function. prof_sw = 1;
 * (prof 'print) print profile data
 *  when start profiler set prof_dt index to prof part of symbol. and save symbol address to prof_sym.
 *  eval count elapsed time and send to profiler the elapsed time data. profiler save elapsed time to prof_dt.
 *  (prof nil) clear prof part of symbols and reset prof_pt.   
*/

void profiler(int sym, double time)
{
    int i;

    i = GET_PROF(sym);
    if (i == NIL) {
	SET_PROF(sym, prof_pt);
	prof_sym[prof_pt++] = sym;
    }
    prof_dt0[i] = prof_dt0[i] + time;
    prof_dt1[i]++;
}

void profiler_clear()
{
    int i;

    for (i = 1; i < prof_pt; i++) {
	SET_PROF(prof_sym[i], NIL);
	prof_dt0[i] = 0;
	prof_dt1[i] = 0;
    }

    prof_pt = 1;
}

void profiler_set(int sw)
{
    prof_sw = sw;
}

void print_space(int x)
{
    int len, i;

    len = strlen(GET_NAME(x));
    for (i = len; i < 21; i++)
	printf(" ");
}

void profiler_print()
{
    int i;

    printf("function-name           elapsed-time      executions\n");
    for (i = 1; i < prof_pt; i++) {
	print(prof_sym[i]);
	print_space(prof_sym[i]);
	printf("%12f\t%12d\n", prof_dt0[i], prof_dt1[i]);
    }
}

/*
* f_eisl_test is test function for new code.
* for example FFT IFFT.
* This function is for development testing code.
*/
int f_eisl_test(int arglist, int th __unused)
{
    int arg1, arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);

    return (big_karatsuba_mult(arg1, arg2));
}

int f_get_myself(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);
    if (!symbolp(arg1))
	error(NOT_SYM, "eisl-get-myself", arg1, th);

    if (IS_FUNC(GET_CAR(arg1)))
	return (cons
		(make_sym("DEFUN"), cons(arg1, GET_CAR(GET_CAR(arg1)))));
    else if (IS_MACRO(GET_CAR(arg1)))
	return (cons
		(make_sym("DEFMACRO"),
		 cons(arg1, GET_CAR(GET_CAR(GET_CAR(arg1))))));

    return (NIL);
}

/* for Raspberry PI 
 * wiringpi for GPIO 
 */
#ifdef __rpi__
int f_wiringpi_setup_gpio(int arglist __unused, int th __unused)
{
    wiringPiSetupGpio();
    return (T);
}

int f_wiringpi_spi_setup_ch_speed(int arglist, int th)
{
    int arg1, arg2, x, y;

    if (length(arglist) != 2)
	error(WRONG_ARGS, "wiringpi-spi-setup-ch-speed", arglist, th);

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "wiringpi-spi-setup-ch-speed", arg1, th);
    if (!integerp(arg2))
	error(NOT_INT, "wiringpi-spi-setup-ch-speed", arg2, th);

    x = GET_INT(arg1);
    y = GET_INT(arg2);
    wiringPiSPISetup(x, y);
    return (T);
}

int f_pwm_set_mode(int arglist, int th)
{
    int arg1;

    if (length(arglist) != 1)
	error(WRONG_ARGS, "pwm-set-mode", arglist, th);

    arg1 = car(arglist);

    if (arg1 == make_sym("pwm-mode-ms"))
	pwmSetMode(PWM_MODE_MS);
    else if (arg1 == make_sym("pwm-mode-bal"))
	pwmSetMode(PWM_MODE_BAL);
    else
	error(WRONG_ARGS, "pwm-set-mode", arg1, th);

    return (T);
}

int f_pwm_set_range(int arglist, int th)
{
    int arg1, x;

    if (length(arglist) != 1)
	error(WRONG_ARGS, "pwm-set-range", arglist, th);

    arg1 = car(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "pwm-set-range", arg1, th);

    x = GET_INT(arg1);
    pwmSetRange(x);
    return (T);
}

int f_pwm_set_clock(int arglist, int th)
{
    int arg1, x;

    if (length(arglist) != 1)
	error(WRONG_ARGS, "pwm-set-clock", arglist, th);

    arg1 = car(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "pwm-set-clock", arg1, th);

    x = GET_INT(arg1);
    pwmSetClock(x);
    return (T);
}

int f_pin_mode(int arglist, int th)
{
    int arg1, arg2, x;

    if (length(arglist) != 2)
	error(WRONG_ARGS, "pin-mode", arglist, th);

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "pin-,mode", arg1, th);

    x = GET_INT(arg1);
    if (arg2 == make_sym("intput"))
	pinMode(x, INPUT);
    else if (arg2 == make_sym("output"))
	pinMode(x, OUTPUT);
    else if (arg2 == make_sym("pwm-output"))
	pinMode(x, PWM_OUTPUT);
    else
	error(WRONG_ARGS, "pin-mode", arg2, th);

    return (T);
}

int f_digital_write(int arglist, int th)
{
    int arg1, arg2, x, y;

    if (length(arglist) != 2)
	error(WRONG_ARGS, "digital-write", arglist, th);

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "digital-write", arg1, th);
    if (!integerp(arg2))
	error(NOT_INT, "digital-write", arg2, th);

    x = GET_INT(arg1);
    y = GET_INT(arg2);
    digitalWrite(x, y);
    return (T);
}

int f_digital_write_byte(int arglist, int th)
{
    int arg1, x;

    if (length(arglist) != 1)
	error(WRONG_ARGS, "digital-write-byte", arglist, th);

    arg1 = car(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "digital-write-byte", arg1, th);

    x = GET_INT(arg1);
    digitalWriteByte(x);
    return (T);
}

int f_pull_up_dn_control(int arglist, int th)
{
    int arg1, arg2, x, y;

    if (length(arglist) != 2)
	error(WRONG_ARGS, "pull-up-dn-control", arglist, th);

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "pull-up-dn-control", arg1, th);
    if (!integerp(arg2))
	error(NOT_INT, "pull-up-dn-control", arg2, th);

    x = GET_INT(arg1);
    y = GET_INT(arg2);
    pullUpDnControl(x, y);
    return (T);
}

int f_digital_read(int arglist, int th)
{
    int arg1, x, res;

    if (length(arglist) != 1)
	error(WRONG_ARGS, "digital-read", arglist, th);

    arg1 = car(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "digital-read", arg1, th);

    x = GET_INT(arg1);
    res = digitalRead(x);
    return (make_int(res));
}

int f_delay(int arglist, int th)
{
    int arg1, x;

    if (length(arglist) != 1)
	error(WRONG_ARGS, "delay", arglist, th);

    arg1 = car(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "delay", arg1, th);

    x = GET_INT(arg1);
    delay(x);
    return (T);
}

int f_delay_microseconds(int arglist, int th)
{
    int arg1, x;

    if (length(arglist) != 1)
	error(WRONG_ARGS, "delay-microseconds", arglist, th);

    arg1 = car(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "delay-microseconds", arg1, th);

    x = GET_INT(arg1);
    delayMicroseconds(x);
    return (T);
}
#endif



/*
* extended functions try/3 and read-exp/0
* To understand Mr. Chaitin's book "The LIMITS of MATHEMATICA"
*/

int program;


int f_try(int arglist, int th)
{
    int arg1, arg2, arg3, arg4, pos, c, bit, i, res, save1, save2;
    char str[STRSIZE];

    arg1 = car(arglist);	//time 
    arg2 = cadr(arglist);	//sexp
    arg3 = caddr(arglist);	// binary
    arg4 = caddr(cdr(arglist));	//print switch

    if (!integerp(arg1)
	&& !(symbolp(arg1) && arg1 == make_sym("NO-TIME-LIMIT")))
	error(ILLEGAL_ARGS, "try", arg1, th);
    if (!listp(arg2))
	error(NOT_LIST, "try", arg2, th);
    if (!listp(arg3))
	error(NOT_LIST, "try", arg3, th);

    pos = 0;
    while (!nullp(arg3)) {
	bit = 8;
	c = 0;
	while (bit > 0) {
	    i = GET_INT(car(arg3));
	    c = 2 * c + i;
	    arg3 = cdr(arg3);
	    bit--;
	}
	if (c >= 32 && c < 127) {	/* ommit control code and unicode */
	    str[pos] = c;
	    pos++;
	}

    }

    if (pos == 0) {
	return (list3(make_sym("FAILSE"), make_sym("OUT-OF-DATA"), NIL));
    }

    str[pos] = EOL;
    pos++;
    str[pos] = NUL;

    program = make_stm(stdin, EISL_INSTR, NULL);
    TRY heap[program].name = Str_dup(str, 1, 0, 1);
    EXCEPT(Mem_Failed) error(MALLOC_OVERF, "try", NIL, th);
    END_TRY;

    save1 = input_stream;
    save2 = output_stream;

    if (arg1 == make_sym("NO-TIME-LIMIT")) {
	ignore_flag = true;
	TRY res = eval(arg2, 0);
	ELSE res = UNDEF;
	END_TRY;
	ignore_flag = false;
	if (res == UNDEF)
	    res = make_sym("FAILSE");
	else if (res == FEND)
	    res = make_sym("FAILSE");
    } else {
	try_timer = getETime() + (double) GET_INT(arg1) * 0.000001;
	try_res = NIL;
	try_flag = true;
	ignore_flag = true;
	TRY res = eval(arg2, th);
	ELSE res = UNDEF;
	END_TRY;
	ignore_flag = false;
	try_flag = false;
	if (res == UNDEF) {
	    res =
		list3(make_sym("FAILSE"), make_sym("OUT-OF-DATA"),
		      try_res);
	    if (arg4 == make_sym("OUT-OF-DATA")) {
		printf("%s", str);
	    }
	} else if (res == FEND) {
	    res =
		list3(make_sym("FAILSE"), make_sym("OUT-OF-TIME"),
		      try_res);
	    if (arg4 == make_sym("OUT-OF-TIME"))
		printf("%s", str);
	} else {
	    res = list3(make_sym("SUCCESS"), res, try_res);
	    if (arg4 == make_sym("SUCCESS"))
		printf("%s", str);
	}
    }

    input_stream = save1;
    output_stream = save2;
    return (res);
}


int f_read_exp(int arglist, int th)
{
    int res, save;

    if (!nullp(arglist))
	error(ILLEGAL_ARGS, "read-exp", arglist, th);


    save = input_stream;
    input_stream = program;
    TRY res = sread();
    ELSE res = UNDEF;
    END_TRY;
    input_stream = save;

    return (res);
}



//-----------multi process-----------

#define R (0)
#define W (1)


// 1st arg is count of process
int f_mp_create(int arglist, int th)
{
	int arg1,n,i;

    arg1 = car(arglist);
    n = GET_INT(arg1);
    if (length(arglist) != 1)
        error(ILLEGAL_ARGS, "mp-create", arglist, th);
    if (n > PROCSIZE)
        error(CANT_CREATE, "mp-create", n, th);

    for(i=0;i<n;i++){
	    if(pipe(pipe_p2c[i]) == -1){
		    error(CANT_CREATE, "mp-create pipe_p2c", NIL, th);
	    }
        if(pipe(pipe_c2p[i]) == -1){
		    error(CANT_CREATE, "mp-create pipe_c2p", NIL, th);
	    }

	    pid[i] = fork();
	    if(pid[i] == -1){
		    error(CANT_CREATE, "mp-create fork", NIL, th);
	    }   
	    if (pid[i] == 0) { // child 
            close(pipe_p2c[i][W]);
            close(pipe_c2p[i][R]);
            if(dup2(pipe_p2c[i][R], STDIN_FILENO) == -1)
                error(CANT_CREATE, "mp-create dup2 stdin", NIL, th);
            if(dup2(pipe_c2p[i][W], STDOUT_FILENO) == -1)
                error(CANT_CREATE, "mp-create dup2 stdout", NIL, th);
            close(pipe_p2c[i][R]);
            close(pipe_c2p[i][W]);
            execl("/usr/local/bin/eisl", "eisl", "-r", "-p",  NULL);
            exit(1);
	
        } 
        close(pipe_p2c[i][R]);
        close(pipe_c2p[i][W]);

	    process_pt++;
    }

	return(T);
}


int sexp_to_str(int x)
{
    int save,res;
    char *str;

    res = make_stm(stdout, EISL_OUTSTR, NULL);
    TRY str = (char *) ALLOC(STRSIZE);
    EXCEPT(Mem_Failed)
	error(MALLOC_OVERF, "create-string-output-stream", NIL, 0);
    END_TRY;
    heap[res].name = str;
    heap[res].name[0] = '\0';

    save = output_stream;
    output_stream = res;
    print(x);
    res = output_stream;
    output_stream = save;
    return(res);
}

void write_to_pipe(int n,int x)
{
    int i,j,pos,c,err;
    char buffer1[7],buffer2[STRSIZE];

    strcpy(buffer2,GET_NAME(x));

    i = 0;
    pos = 0;
    for(j=0;j<7;j++)
            buffer1[j] = 0;
    c = buffer2[pos];
    while(1){
        while(i < 7 && c != 0)
        {
            buffer1[i] = c;
            i++;
            pos++;
            c = buffer2[pos];
            
        }
        // write to pipe
        err = write(pipe_p2c[n][W], buffer1, sizeof(buffer1));

        if(c == 0)
            break;

        i = 0;
        for(j=0;j<7;j++)
            buffer1[j] = 0;
    }
}

int str_to_sexp(int x)
{
    int stm,save,res;

    stm = make_stm(stdin, EISL_INSTR, NULL);
    TRY heap[stm].name = Str_dup(GET_NAME(x), 1, 0, 1);
    EXCEPT(Mem_Failed) error(MALLOC_OVERF, "create-string-input-stream",
			     NIL, 0);
    END_TRY;

    save = input_stream;
    input_stream = stm;
    res = sread();
    input_stream = save;
    return (res);
}

// fsubr (mp-call fun arg1 arg2 ... argn)
int f_mp_call(int arglist, int th)
{
    int arg1,arg2,res,n,i,args;
    char buffer[256];

    arg1 = car(arglist); //fun
    arg2 = cdr(arglist); //args
    n = length(arg2);

    i = 0;
    while(!nullp(arg2)){
        write_to_pipe(i,sexp_to_str(car(arg2)));
        arg2 = cdr(arg2);
        i++;
    }

    args = NIL;
    for(i=n-1;i>=0;i--){
        // set nonblock mode
        int flags = fcntl(pipe_c2p[i][R], F_GETFL, 0);
        fcntl(pipe_c2p[i][R], F_SETFL, flags | O_NONBLOCK);

        int bytes_read;
        // wait until get result
        while ((bytes_read = read(pipe_c2p[i][R], buffer, 256)) == -1 && errno == EAGAIN);
        buffer[bytes_read] = '\0';

        args = cons(str_to_sexp(make_str(buffer)),args);
    }

    res = apply(eval(arg1,th), args, th);
    return(res);
}

// (mp-exec 0 "(time (" "tarai 1" "0 5 0))")
// 1st is process number
// rest are string(length 7) atom
int f_mp_exec(int arglist, int th)
{
	int arg1,arg2,n,res;
    char buffer[256];

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if(length(arglist) < 2)
        error(ILLEGAL_ARGS, "mp-exec", arglist, th);
    if(!integerp(arg1))
        error(NOT_INT, "mp-exec", arg1, th);
    n = GET_INT(arg1);
    if(!(n < process_pt))
        error(ILLEGAL_ARGS, "mp-exec", n, th);
    
    
    while(!nullp(arg2)){
        write(pipe_p2c[n][W], GET_NAME(car(arg2)), sizeof(GET_NAME(car(arg2))));
        arg2 = cdr(arg2);
    }
    
    // set nonblock mode
    int flags = fcntl(pipe_c2p[n][R], F_GETFL, 0);
    fcntl(pipe_c2p[n][R], F_SETFL, flags | O_NONBLOCK);

    
    int bytes_read;
    // wait until get result
    while ((bytes_read = read(pipe_c2p[n][R], buffer, 256)) == -1 && errno == EAGAIN);

    buffer[bytes_read] = '\0';
    res = make_sym(buffer);
    
    return(res);
}


// close all process 
int f_mp_close(int arglist, int th)
{
    int i;

    for(i=0;i<process_pt;i++){
        char data[] = "(quit)";
        write(pipe_p2c[i][W], data, sizeof(data));
    }

    process_pt = 0;
    return(T);
}

