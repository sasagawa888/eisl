#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef __arm__
#include <wiringPi.h>
#include <wiringPiSPI.h>
#endif
#include "eisl.h"

void
initexsubr(void)
{
    defsubr("RANDOM-REAL", f_random_real);
    defsubr("RANDOM", f_random);
    defsubr("NCONC", f_nconc);
    defsubr("FAST-ADDRESS", f_address);
    defsubr("MACROEXPAND-1", f_macroexpand_1);
    defsubr("MACROEXPAND-ALL", f_macroexpand_all);
    defsubr("BACKTRACE", f_backtrace);
    defsubr("BREAK", f_break);
    defsubr("EDIT", f_edit);
    defsubr("FREEDLL", f_freedll);
    defsubr("SYSTEM", f_system);
    defsubr("SUBRP", f_subrp);
    defsubr("MACROP", f_macrop);
    defsubr("FIXNUMP", f_fixnump);
    defsubr("LONGNUMP", f_longnump);
    defsubr("BIGNUMP", f_bignump);
    defsubr("SELF-INTRODUCTION", f_self_introduction);
    defsubr("CLASSP", f_classp);
    defsubr("C-INCLUDE", f_ignore);
    defsubr("C-DEFINE", f_ignore);
    defsubr("C-LANG", f_ignore);
    defsubr("C-OPTION", f_ignore);
    defsubr("HEAPDUMP", f_heapdump);
    defsubr("INSTANCE", f_instance);
    defsubr("MODULESUBST", f_modulesubst);
    defsubr("LINE-ARGUMENT", f_line_argument);
    defsubr("GETENV", f_getenv);
    defsubr("EISL-SUPERP-FOR-COMPILER", f_superp_for_compiler);
    defsubr("EISL-READED-ARRAY-LIST", f_readed_array_list);
    defsubr("EISL-GET-METHOD", f_get_method);
    defsubr("EISL-GET-METHOD-BODY", f_get_method_body);
    defsubr("EISL-GET-METHOD-PRIORITY", f_get_method_priority);
    defsubr("EISL-IGNORE-TOPLEVEL-CHECK", f_ignore_toplevel_check);

#ifdef __arm__
    defsubr("WIRINGPI-SETUP-GPIO", f_wiringpi_setup_gpio);
    defsubr("WIRINGPI-SPI-SETUP-CH-SPEED", f_wiringpi_spi_setup_ch_speed);
    defsubr("PWM-SET-MODE", f_pwm_set_mode);
    defsubr("PWM-SET-RANGE", f_pwm_set_range);
    defsubr("PWM-SET-CLOCK", f_pwm_set_clock);
    defsubr("PIN-MODE", f_pin_mode);
    defsubr("DIGITAL-WRITE", f_digital_write);
    defsubr("DIGITAL-WRITE-BYTE", f_digital_write_byte);
    defsubr("PULL-UP-DN-CONTROL", f_pull_up_dn_control);
    defsubr("DIGITAL-READ", f_digital_read);
    defsubr("DELAY", f_delay);
    defsubr("DELAY-MICROSECONDS", f_delay_microseconds);
#endif

}

// Fast Project
int
f_classp(int arglist)
{
    int             arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(ILLEGAL_ARGS, "classp", arglist);

    if (IS_CLASS(arg1))
	return (T);
    else
	return (NIL);
}


int
f_ignore(int arglist __unused)
{
    return (T);
}


int
f_self_introduction(int arglist __unused)
{
#if __APPLE__
    return (makesym("MACOS"));
#elif defined(__OpenBSD__)
    return (makesym("OPENBSD"));
#else
    return (makesym("LINUX"));
#endif
}


int
f_ignore_toplevel_check(int arglist)
{
    int             arg1;

    arg1 = car(arglist);
    if (arg1 == T)
	ignore_topchk = true;
    else
	ignore_topchk = false;
    return (T);
}

DEF_PREDICATE(METHOD, METHOD)
     int             f_get_method_priority(int arglist)
{
    int             arg1;

    arg1 = car(arglist);
    if (!(IS_METHOD(arg1)))
	error(ILLEGAL_ARGS, "eisl-get-method-priority", arg1);

    return (makeint(GET_OPT(arg1) + 1));
    /*
     * 11=:around  12=:befor 13=:primary 14=:arter
     */
}


int
f_get_method_body(int arglist)
{
    int             arg1;

    arg1 = car(arglist);
    if (!(IS_METHOD(arg1)))
	error(ILLEGAL_ARGS, "get-method-body", arg1);

    return (GET_CAR(arg1));
}

int
f_get_method(int arglist)
{
    int             arg1;

    arg1 = car(arglist);
    if (!genericp(arg1))
	error(ILLEGAL_ARGS, "get-method", arg1);

    return (GET_CDR(GET_CAR(arg1)));
}


int
f_readed_array_list(int arglist)
{
    int             arg1;

    arg1 = car(arglist);
    return (GET_PROP(arg1));
}


int
f_system(int arglist)
{
    int             arg1;

    arg1 = car(arglist);
    if (system(GET_NAME(arg1)) == -1)
	error(SYSTEM_ERR, "system", arg1);
    return (T);
}



int
f_freedll(int arglist __unused)
{
    // dlclose(hmod);
    return (T);
}



int
f_macrop(int arglist)
{
    int             arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "macrop", arglist);
    if (IS_MACRO(GET_CAR(arg1)))
	return (T);
    else
	return (NIL);
}

int
f_fixnump(int arglist)
{
    int             arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "fixnump", arglist);
    if (IS_INTEGER(arg1))
	return (T);
    else
	return (NIL);
}

int
f_longnump(int arglist)
{
    int             arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "longnump", arglist);
    if (IS_LONGNUM(arg1))
	return (T);
    else
	return (NIL);
}

int
f_bignump(int arglist)
{
    int             arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "bignump", arglist);
    if (IS_BIGXNUM(arg1))
	return (T);
    else
	return (NIL);
}


int
f_subrp(int arglist)
{
    int             arg;

    arg = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "subrp", arglist);
    if (IS_SUBR(GET_CAR(arg)))
	return (T);
    else
	return (NIL);
}

int
f_random_real(int arglist)
{
    double          d;

    if (length(arglist) != 0)
	error(WRONG_ARGS, "random-real", arglist);

    d = (double) rand() / RAND_MAX;
    return (makeflt(d));
}

int
f_random(int arglist)
{
    int             arg1,
                    n;

    if (length(arglist) != 1)
	error(WRONG_ARGS, "random", arglist);

    arg1 = car(arglist);
    n = GET_INT(arg1);

    return (makeint(rand() % n));
}

int
f_nconc(int arglist)
{
    int             arg1,
                    arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (length(arglist) != 2)
	error(WRONG_ARGS, "nconc", arglist);

    return (nconc(arg1, arg2));
}

int
f_address(int arglist)
{
    int             arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "address", arglist);

    return (makeint(arg1));
}

int
f_macroexpand_1(int arglist)
{
    int             arg1,
                    args;

    arg1 = caar(arglist);
    args = cdar(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "macroexpand-1", arglist);
    if (!symbolp(arg1))
	error(NOT_SYM, "macroexpand-1", arg1);

    return (macroexpand_1(arg1, args));
}

int
macroexpand_1(int macsym, int args)
{
    int             func,
                    body,
                    macrofunc,
                    varlist,
                    save,
                    res;

    func = GET_CAR(macsym);
    save = ep;
    res = NIL;
    macrofunc = GET_CAR(func);
    varlist = car(GET_CAR(macrofunc));
    if (GET_OPT(func) >= 0) {
	if (length(args) != (int) GET_OPT(func))
	    error(WRONG_ARGS, "macroexpand-1", args);
    } else {
	if (length(args) < (-1 * (int) GET_OPT(func) - 2))
	    error(WRONG_ARGS, "macroexpand-1", args);
    }
    body = cdr(GET_CAR(macrofunc));
    bindarg(varlist, args);
    while (!(IS_NIL(body))) {
	res = eval(car(body));
	body = cdr(body);
    }
    unbind();
    ep = save;
    return (res);
}

int
f_macroexpand_all(int arglist)
{
    int             arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "macroexpand-all", arglist);
    if (listp(arg1) && car(arg1) == makesym("DEFMACRO"))
	return (arg1);
    else
	return (macroexpand_all(arg1));
}


int
macroexpand_all(int sexp)
{

    if (nullp(sexp))
	return (NIL);
    else if (atomp(sexp))
	return (sexp);
    else if (listp(sexp) && car(sexp) == makesym("QUOTE"))
	return (sexp);
    else if (listp(sexp) && macrop(car(sexp)))
	return (macroexpand_all(macroexpand_1(car(sexp), cdr(sexp))));
    else if (listp(sexp))
	return (cons
		(macroexpand_all(car(sexp)), macroexpand_all(cdr(sexp))));

    return (NIL);
}

int
f_backtrace(int arglist)
{
    int             arg1,
                    l;

    if ((l = length(arglist)) != 0 && l != 1)
	error(WRONG_ARGS, "backtrace", arglist);

    arg1 = car(arglist);

    if (l == 0) {
	int             i;

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

int
f_break(int arglist __unused)
{
    puts("break");
    debugger();
    return (T);
}

int
f_instance(int arglist)
{
    int             arg1,
                    addr;

    arg1 = car(arglist);
    addr = get_int(arg1);
    print(addr);
    return (T);
}

// ----------for Raspberry PI
#ifdef __arm__
int
f_wiringpi_setup_gpio(int arglist __unused)
{
    wiringPiSetupGpio();
    return (T);
}

int
f_wiringpi_spi_setup_ch_speed(int arglist)
{
    int             arg1,
                    arg2,
                    x,
                    y;

    if (length(arglist) != 2)
	error(WRONG_ARGS, "wiringpi-spi-setup-ch-speed", arglist);

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "wiringpi-spi-setup-ch-speed", arg1);
    if (!integerp(arg2))
	error(NOT_INT, "wiringpi-spi-setup-ch-speed", arg2);

    x = GET_INT(arg1);
    y = GET_INT(arg2);
    wiringPiSPISetup(x, y);
    return (T);
}

int
f_pwm_set_mode(int arglist)
{
    int             arg1;

    if (length(arglist) != 1)
	error(WRONG_ARGS, "pwm-set-mode", arglist);

    arg1 = car(arglist);

    if (arg1 == makesym("pwm-mode-ms"))
	pwmSetMode(PWM_MODE_MS);
    else if (arg1 == makesym("pwm-mode-bal"))
	pwmSetMode(PWM_MODE_BAL);
    else
	error(WRONG_ARGS, "pwm-set-mode", arg1);

    return (T);
}

int
f_pwm_set_range(int arglist)
{
    int             arg1,
                    x;

    if (length(arglist) != 1)
	error(WRONG_ARGS, "pwm-set-range", arglist);

    arg1 = car(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "pwm-set-range", arg1);

    x = GET_INT(arg1);
    pwmSetRange(x);
    return (T);
}

int
f_pwm_set_clock(int arglist)
{
    int             arg1,
                    x;

    if (length(arglist) != 1)
	error(WRONG_ARGS, "pwm-set-clock", arglist);

    arg1 = car(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "pwm-set-clock", arg1);

    x = GET_INT(arg1);
    pwmSetClock(x);
    return (T);
}

int
f_pin_mode(int arglist)
{
    int             arg1,
                    arg2,
                    x;

    if (length(arglist) != 2)
	error(WRONG_ARGS, "pin-mode", arglist);

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "pin-,mode", arg1);

    x = GET_INT(arg1);
    if (arg2 == makesym("intput"))
	pinMode(x, INPUT);
    else if (arg2 == makesym("output"))
	pinMode(x, OUTPUT);
    else if (arg2 == makesym("pwm-output"))
	pinMode(x, PWM_OUTPUT);
    else
	error(WRONG_ARGS, "pin-mode", arg2);

    return (T);
}

int
f_digital_write(int arglist)
{
    int             arg1,
                    arg2,
                    x,
                    y;

    if (length(arglist) != 2)
	error(WRONG_ARGS, "digital-write", arglist);

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "digital-write", arg1);
    if (!integerp(arg2))
	error(NOT_INT, "digital-write", arg2);

    x = GET_INT(arg1);
    y = GET_INT(arg2);
    digitalWrite(x, y);
    return (T);
}

int
f_digital_write_byte(int arglist)
{
    int             arg1,
                    x;

    if (length(arglist) != 1)
	error(WRONG_ARGS, "digital-write-byte", arglist);

    arg1 = car(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "digital-write-byte", arg1);

    x = GET_INT(arg1);
    digitalWriteByte(x);
    return (T);
}

int
f_pull_up_dn_control(int arglist)
{
    int             arg1,
                    arg2,
                    x,
                    y;

    if (length(arglist) != 2)
	error(WRONG_ARGS, "pull-up-dn-control", arglist);

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "pull-up-dn-control", arg1);
    if (!integerp(arg2))
	error(NOT_INT, "pull-up-dn-control", arg2);

    x = GET_INT(arg1);
    y = GET_INT(arg2);
    pullUpDnControl(x, y);
    return (T);
}

int
f_digital_read(int arglist)
{
    int             arg1,
                    x,
                    res;

    if (length(arglist) != 1)
	error(WRONG_ARGS, "digital-read", arglist);

    arg1 = car(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "digital-read", arg1);

    x = GET_INT(arg1);
    res = digitalRead(x);
    return (makeint(res));
}

int
f_delay(int arglist)
{
    int             arg1,
                    x;

    if (length(arglist) != 1)
	error(WRONG_ARGS, "delay", arglist);

    arg1 = car(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "delay", arg1);

    x = GET_INT(arg1);
    delay(x);
    return (T);
}

int
f_delay_microseconds(int arglist)
{
    int             arg1,
                    x;

    if (length(arglist) != 1)
	error(WRONG_ARGS, "delay-microseconds", arglist);

    arg1 = car(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "delay-microseconds", arg1);

    x = GET_INT(arg1);
    delayMicroseconds(x);
    return (T);
}
#endif

int
f_modulesubst(int arglist)
{
    int             arg1,
                    arg2,
                    arg3;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);

    return (modulesubst(arg1, arg2, arg3));
}

int
f_line_argument(int arglist)
{
    int             arg1,
                    n;

    if (length(arglist) != 1) {
	error(WRONG_ARGS, "line-argument", arglist);
    }
    arg1 = car(arglist);
    n = GET_INT(arg1);
    if (n < gArgC) {
	return makestr(gArgV[n]);
    } else {
	return NIL;
    }
}

int
f_getenv(int arglist)
{
    int             arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1) {
	error(WRONG_ARGS, "getenv", arglist);
    }
    char           *val = getenv(GET_NAME(arg1));
    if (val == NULL) {
	return NIL;
    } else {
	return makestr(val);
    }
}

/*
* f_superp_for_compiler (superp-for-compiler) is used in compiler.lsp. 
* for generate (call-next-method) 
* compare entry-parameter and next-method-parameter.
* when entry-parameter is super-call than next-method-patarmeter, compiler must not generate next-method
* see verify/object.lsp test-case foo-30
*/

int
f_superp_for_compiler(int arglist)
{
    int             arg1,
                    arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);

    if (length(arglist) != 2) {
	error(WRONG_ARGS, "adaptp-for-compiler", arglist);
    }

    if (superp(arg1,arg2))
        return (T);
    else 
        return (NIL);
}

int
superp(int entry, int next)
{

    if (nullp(entry) && nullp(next))
	return (1);
    else if (symbolp(car(entry)))
	return (superp(cdr(entry), cdr(next)));
    else if (subclassp(GET_AUX(cadar(next)), GET_AUX(cadar(entry))))	// subclass
	return (superp(cdr(entry), cdr(next)));
    else
	return (0);
}

