/* extended functions
 * functions for compiler 
 * functions for compatibility of Common Lisp
 * functions for debug
 * function for profiler
 * functions for Raspbery-PI
 * functions for Chaitin's omega
 * functions for multi-tread
 * functions for multi-process
 * functions for distributed-process
 * functions for TCP/IP
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>


#ifdef __rpi__
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <arpa/inet.h>
#include <sys/types.h>
#endif

#ifdef __rpigpio__
#include <gpiod.h>
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
    def_fsubr("C-INCLUDE", f_ignore);
    def_fsubr("C-DEFINE", f_ignore);
    def_fsubr("C-LANG", f_ignore);
    def_fsubr("C-OPTION", f_ignore);
    def_fsubr("C-RETURN", f_ignore);
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

    def_fsubr("TIME", f_time);
    def_fsubr("TRACE", f_trace);
    def_fsubr("UNTRACE", f_untrace);
    def_fsubr("DEFMODULE", f_defmodule);


    def_subr("TRY", f_try);
    def_subr("READ-EXP", f_read_exp);

    def_subr("MT-CREATE", f_mt_create);
    def_subr("MT-CLOSE", f_mt_close);
    def_fsubr("MT-LET", f_mt_let);
    def_fsubr("MT-CALL", f_mt_call);
    def_fsubr("MT-LOCK", f_mt_lock);
    def_fsubr("MT-EXEC", f_mt_exec);

    def_subr("MP-CREATE", f_mp_create);
    def_subr("MP-CLOSE", f_mp_close);
    def_fsubr("MP-CALL", f_mp_call);
    def_fsubr("MP-EXEC", f_mp_exec);
    def_fsubr("MP-AND", f_mp_and);
    def_fsubr("MP-OR", f_mp_or);
    def_subr("MP-EVAL", f_mp_eval);

    def_subr("DP-CREATE", f_dp_create);
    def_subr("DP-CLOSE", f_dp_close);
    def_subr("DP-HALT", f_dp_halt);
    def_fsubr("DP-CALL", f_dp_call);
    def_fsubr("DP-EXEC", f_dp_exec);
    def_fsubr("DP-AND", f_dp_and);
    def_fsubr("DP-OR", f_dp_or);
    def_subr("DP-EVAL", f_dp_eval);
    def_subr("DP-TRANSFER", f_dp_transfer);
    def_subr("DP-LOAD", f_dp_load);
    def_subr("DP-COMPILE", f_dp_compile);
    def_subr("DP-SETID", f_dp_setid);
    def_subr("DP-SENDERR", f_dp_senderr);
    def_subr("DP-TRACE", f_dp_trace);
    def_subr("DP-UNTRACE", f_dp_untrace);

    def_subr("CREATE-SERVER-SOCKET", f_create_server_socket);
    def_subr("CREATE-CLIENT-SOCKET", f_create_client_socket);
    def_subr("SEND-SOCKET", f_send_socket);
    def_subr("RECV-SOCKET", f_recv_socket);
    def_subr("CLOSE-SOCKET", f_close_socket);

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

#ifdef __rpigpio__
    def_subr("GPIO-INIT", f_gpio_init);
    def_subr("GPIO-SET-MODE", f_gpio_set_mode);
    def_subr("GPIO-WRITE", f_gpio_write);
    def_subr("GPIO-READ", f_gpio_read);
    def_subr("GPIO-EVENT_REQUEST", f_gpio_event_request);
    def_subr("GPIO-EVENT_WAIT", f_gpio_event_wait);
    def_subr("GPIO-EVENT-READ", f_gpio_event_read);
    def_subr("GPIO-CLOSE", f_gpio_close);
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
		 ":r room\n" ":s stepper ON/OFF\n" "other S exps eval");
	} else if (eqp(x, make_sym(":A"))) {
	    RAISE(Restart_Repl);
	} else if (eqp(x, make_sym(":B"))) {
	    for (i = 0; i < BACKSIZE; i++) {
		print(backtrace[i]);
		putchar('\n');
	    }
	} else if (eqp(x, make_sym(":D"))) {
	    for (i = 0; i < thread_num; i++) {
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
	    for (i = 0; i < thread_num; i++) {
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
		      "AP = %d (arglist pointer)\n"
		      "LP = %d (shelter pointer)\n"
		      "Parallel = %d (thread_num)\n"
		      "Thread = %d (current thread)\n",
		      ep[th], dp[th], hp[th], sp[th], ap[th],
		      lp[th], thread_num, th);
	    puts("Free cell ");
	    for (i = 0; i < thread_num; i++) {
		Fmt_print("thread%d = %d\n", i, fc[i]);
	    }
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
    if (length(arglist) != 1)
	goto error;

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
    else {
      error:
	puts("argument:\n"
	     "'sys system function profile\n"
	     "'user user function profile\n"
	     "'pr print result\n"
	     "'cl clear profile data\n"
	     "nil stop profiler and clear result\n");
	error(WRONG_ARGS, "prof", arg1, th);
    }
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
* This function is for development testing code.
*/
int f_eisl_test(int arglist, int th __unused)
{
    int arg1, res;

    arg1 = car(arglist);
    SET_SOCKET(100000, arg1);
    res = GET_SOCKET(100000);
    return (res);
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

    if (arg1 == make_sym("PWM-MODE-MS"))
	pwmSetMode(PWM_MODE_MS);
    else if (arg1 == make_sym("PWM-MODE-BAL"))
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
	error(NOT_INT, "pin-mode", arg1, th);

    x = GET_INT(arg1);
    if (arg2 == make_sym("INPUT"))
	pinMode(x, INPUT);
    else if (arg2 == make_sym("OUTPUT"))
	pinMode(x, OUTPUT);
    else if (arg2 == make_sym("PWM-OUTPUT"))
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

#ifdef __rpigpio__

static struct gpiod_chip *chip = NULL;

int f_gpio_init(int arglist, int th)
{
    if (length(arglist) != 0)
	error(WRONG_ARGS, "gpio-init", arglist, th);
    chip = gpiod_chip_open("/dev/gpiochip0");
    if (chip != NULL)
	return (T);
    else
	return (NIL);
}

int f_gpio_set_mode(int arglist, int th)
{
    int arg1, arg2, res;

    arg1 = car(arglist);	//pin
    arg2 = cadr(arglist);	//mode
    if (length(arglist) != 2)
	error(WRONG_ARGS, "gpio-set-mode ", arglist, th);
    if (!integerp(arg1))
	error(NOT_INT, "gpio-set-mode ", arglist, th);
    if (!(eqp(arg2, make_sym("INPUT")) || eqp(arg2, make_sym("OUTPUT"))))
	error(WRONG_ARGS, "gpio-set-mode ", arglist, th);

    struct gpiod_line *line = gpiod_chip_get_line(chip, GET_INT(arg1));
    if (!line)
	error(SYSTEM_ERR, "gpio-set-mode ", arglist, th);

    if (eqp(arg2, make_sym("INPUT")))	// input
	res = gpiod_line_request_input(line, "easy-islisp");
    else			// output
	res = gpiod_line_request_output(line, "easy-islisp", 0);

    if (res < 0)
	error(SYSTEM_ERR, "gpio-set-mode ", arglist, th);

    return (T);
}

int f_gpio_write(int arglist, int th)
{
    int arg1, arg2, res;

    arg1 = car(arglist);	//pin
    arg2 = cadr(arglist);	//value
    if (length(arglist) != 2)
	error(WRONG_ARGS, "gpio-write", arglist, th);
    if (!integerp(arg1))
	error(NOT_INT, "gpio-write ", arg1, th);
    if (GET_INT(arg1) < 0 || GET_INT(arg1) > 27)
	error(WRONG_ARGS, "gpio-write", arg1, th);
    if (!integerp(arg2))
	error(NOT_INT, "gpio-write ", arg2, th);
    if (!(GET_INT(arg2) == 1 || GET_INT(arg2) == 0))
	error(WRONG_ARGS, "gpio-write", arg2, th);

    struct gpiod_line *line = gpiod_chip_get_line(chip, GET_INT(arg1));
    if (!line)
	error(SYSTEM_ERR, "gpio-write", arglist, th);

    res = gpiod_line_set_value(line, GET_INT(arg2));
    if (res < 0)
	error(SYSTEM_ERR, "gpio-write ", arglist, th);

    return (T);
}

int f_gpio_read(int arglist, int th)
{
    int arg1, res;


    arg1 = car(arglist);	//pin
    if (length(arglist) != 1)
	error(WRONG_ARGS, "gpio-read ", arglist, th);
    if (!integerp(arg1))
	error(NOT_INT, "gpio-read ", arg1, th);
    if (GET_INT(arg1) < 0 || GET_INT(arg1) > 27)
	error(WRONG_ARGS, "gpio-read", arg1, th);

    struct gpiod_line *line = gpiod_chip_get_line(chip, GET_INT(arg1));
    if (!line)
	error(SYSTEM_ERR, "gpio-read ", arglist, th);

    res = gpiod_line_get_value(line);
    return (make_int(res));
}

int f_gpio_event_request(int arglist, int th)
{
    int arg1, arg2, res;


    arg1 = car(arglist);	// pin
    arg2 = cadr(arglist);	// mode
    if (length(arglist) != 2)
	error(WRONG_ARGS, "gpio-event-request ", arglist, th);
    if (!integerp(arg1))
	error(NOT_INT, "gpio-event-request ", arglist, th);
    if (GET_INT(arg1) < 0 || GET_INT(arg1) > 27)
	error(WRONG_ARGS, "gpio-event-request", arg1, th);
    if (!(eqp(arg2, make_sym("RISING")) ||
	  eqp(arg2, make_sym("FALLING")) || eqp(arg2, make_sym("BOTH"))))
	error(WRONG_ARGS, "gpio-event-request ", arglist, th);
    struct gpiod_line *line = gpiod_chip_get_line(chip, GET_INT(arg1));
    if (!line)
	error(SYSTEM_ERR, "gpio-event-request ", arglist, th);

    if (eqp(arg2, make_sym("RISING")))
	res = gpiod_line_request_rising_edge_events(line, "easy-islisp");
    else if (eqp(arg2, make_sym("FALLING")))
	res = gpiod_line_request_falling_edge_events(line, "easy-islisp");
    else
	res = gpiod_line_request_both_edges_events(line, "easy-islisp");

    if (res == 0)
	return (T);
    else
	return (NIL);

    return (NIL);
}

int f_gpio_event_wait(int arglist, int th)
{
    int arg1, arg2, res;


    arg1 = car(arglist);	//pin
    arg2 = cadr(arglist);	//timeout
    if (length(arglist) != 2)
	error(WRONG_ARGS, "gpio-event-wait ", arglist, th);
    if (!integerp(arg1))
	error(NOT_INT, "gpio-event-wait ", arg1, th);
    if (GET_INT(arg1) < 0 || GET_INT(arg1) > 27)
	error(WRONG_ARGS, "gpio-event-wait", arg1, th);
    if (!integerp(arg2))
	error(NOT_INT, "gpio-event-wait ", arg2, th);

    struct gpiod_line *line = gpiod_chip_get_line(chip, GET_INT(arg1));
    if (!line)
	error(SYSTEM_ERR, "gpio-event-wait ", arglist, th);
    struct timespec ts =
	{ GET_INT(arg2) / 1000, (GET_INT(arg2) % 1000) * 1000000 };
    res = gpiod_line_event_wait(line, &ts);
    if (res < 0)
	error(SYSTEM_ERR, "gpio-event-wait ", arglist, th);

    if (res == 1)
	return (T);
    else
	return (NIL);

    return (NIL);
}

int f_gpio_event_read(int arglist, int th)
{
    int arg1;


    arg1 = car(arglist);	//pin
    if (length(arglist) != 1)
	error(WRONG_ARGS, "gpio-event-read ", arglist, th);
    if (!integerp(arg1))
	error(NOT_INT, "gpio-event-read ", arglist, th);

    struct gpiod_line *line = gpiod_chip_get_line(chip, GET_INT(arg1));
    if (!line)
	error(SYSTEM_ERR, "gpio-event-read ", arglist, th);
    struct gpiod_line_event event;
    gpiod_line_event_read(line, &event);
    if (event.event_type == GPIOD_LINE_EVENT_RISING_EDGE)
	return (make_sym("RISING"));
    else if (event.event_type == GPIOD_LINE_EVENT_FALLING_EDGE)
	return (make_sym("FALLING"));
    else
	error(SYSTEM_ERR, "gpio-event-read ", arglist, th);

    return (NIL);
}

int f_gpio_close(int arglist, int th)
{
    if (length(arglist) != 0)
	error(WRONG_ARGS, "gpio-close ", arglist, th);

    gpiod_chip_close(chip);
    chip = NULL;
    return (T);
}

#endif

double getETime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (double) tv.tv_usec * 1e-6;
}



int f_time(int arglist, int th)
{
    int arg1;
    double st, en;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "time", arglist, th);

    st = getETime();
    eval(arg1, 0);
    en = getETime();
    Fmt_print("Elapsed Time(second)=%.6f\n", en - st);
    return (UNDEF);
}

int f_trace(int arglist, int th)
{

    if (nullp(arglist)) {
	return (trace_list);
    } else {
	while (!nullp(arglist)) {
	    if (!symbolp(car(arglist)))
		error(NOT_SYM, "trace", car(arglist), th);
	    if (!member(car(arglist), trace_list)) {
		SET_TR(car(arglist), 1);
		trace_list = cons(car(arglist), trace_list);
	    }
	    arglist = cdr(arglist);
	}
	return (T);
    }
}

int f_untrace(int arglist, int th)
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
		error(NOT_SYM, "untrace", car(arglist), th);
	    SET_TR(car(arglist), 0);
	    SET_TR(GET_CAR(car(arglist)), 0);
	    arglist = cdr(arglist);
	}
	trace_list = remove_list(trace_list, arglist);
    }
    return (T);
}



int f_import(int arglist, int th)
{
    int arg1 = car(arglist);
    if (!stringp(arg1))
	error(NOT_SYM, "import", arg1, th);

    char *str = Str_cat(GET_NAME(arg1), 1, 0, ".o", 1, 0);
    char *fname = library_file(str);
    if (access(fname, R_OK) != -1) {
	f_load(list1(make_str(fname)), 0);
	goto cleanup;
    }

    FREE(str);
    str = Str_cat(GET_NAME(arg1), 1, 0, ".lsp", 1, 0);
    FREE(fname);
    fname = library_file(str);
    if (access(fname, R_OK) != -1) {
	f_load(list1(make_str(fname)), 0);
	goto cleanup;
    }
    FREE(str);
    FREE(fname);
    error(CANT_OPEN, "import", arg1, th);

  cleanup:
    FREE(str);
    FREE(fname);
    return (T);
}


int f_defmodule(int arglist, int th __unused)
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

	eval(modulesubst(car(arg2), arg1, exports), 0);
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

//-----------TCP/IP--------------------

int f_create_client_socket(int arglist, int th)
{
    int arg1, arg2, res, sock;

    arg1 = car(arglist);	//port number
    arg2 = cadr(arglist);	// IP address
    if (length(arglist) != 2)
	error(WRONG_ARGS, "create-client-socket", arglist, th);
    if (!integerp(arg1))
	error(NOT_INT, "create-client-socket", arg1, th);
    if (!stringp(arg2))
	error(NOT_STR, "create-client-socket", arg2, th);


    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
	error(SYSTEM_ERR, "create-client-socket", NIL, th);
    }

    memset((char *) &client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(GET_INT(arg1));

    if (inet_pton(AF_INET, GET_NAME(arg2), &client_addr.sin_addr) < 0)
	error(SYSTEM_ERR, "create-client-socket", NIL, 0);


    if (connect
	(sock, (struct sockaddr *) &client_addr, sizeof(client_addr)) < 0)
    {
	error(SYSTEM_ERR, "create-client-socket", NIL, 0);
    }

    res = make_socket(sock, EISL_SOCKET, "client", NIL);
    return (res);
}

int f_create_server_socket(int arglist, int th)
{
    int arg1, sock0, sock1, res;

    arg1 = car(arglist);	// port number
    if (length(arglist) != 1)
	error(WRONG_ARGS, "create-server-socket", arglist, th);
    if (!integerp(arg1))
	error(NOT_INT, "create-server-socket", arg1, th);

    sock0 = socket(AF_INET, SOCK_STREAM, 0);
    if (sock0 < 0) {
	error(SYSTEM_ERR, "cread-server-socket", NIL, th);
    }

    memset((char *) &server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(GET_INT(arg1));

    if (bind
	(sock0, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
    {
	error(SYSTEM_ERR, "create-server-socket", NIL, th);
    }

    listen(sock0, 5);
    parent_len = sizeof(server_addr);


    sock1 = accept(sock0, (struct sockaddr *) &server_addr, &parent_len);
    if (sock1 < 0) {
	error(SYSTEM_ERR, "create-server-socket", NIL, th);

    }

    res = make_socket(sock1, EISL_SOCKET, "server", sock0);
    return (res);

}

int f_send_socket(int arglist, int th)
{
    int arg1, arg2, n;
    char buf[256];

    arg1 = car(arglist);	//socket
    arg2 = cadr(arglist);	//message string

    if (!socketp(arg1))
	error(WRONG_ARGS, "send-socket", arg1, th);
    if (!stringp(arg2))
	error(NOT_STR, "send-socket", arg2, th);

    strcpy(buf, GET_NAME(arg2));
    n = write(GET_SOCKET(arg1), buf, 256);
    if (n < 0)
	error(SYSTEM_ERR, "send-socket", NIL, th);
    return (T);
}

int f_recv_socket(int arglist, int th)
{
    int arg1, sock, n;
    char buf[STRSIZE];

    arg1 = car(arglist);	//socket
    if (!socketp(arg1))
	error(WRONG_ARGS, "recv-socket", arg1, th);

    sock = GET_SOCKET(arg1);
    memset(buf, 0, sizeof(buf));
    n = read(sock, buf, sizeof(buf) - 1);
    if (n < 0) {
	error(SYSTEM_ERR, "receive from parent", NIL, 0);
    }

    return (make_str(buf));
}

int f_close_socket(int arglist, int th)
{
    int arg1, sock0, sock1;

    arg1 = car(arglist);	//socket
    if (!socketp(arg1))
	error(WRONG_ARGS, "clos-socket", arg1, th);

    sock0 = GET_SOCKET(arg1);
    sock1 = GET_CDR(arg1);
    close(sock0);
    if (!nullp(sock1))
	close(sock1);

    return (T);
}
